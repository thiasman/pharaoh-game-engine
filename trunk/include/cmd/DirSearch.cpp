
/////////////////////////////////////////////////////////////////////
// $Id$
//
// DirSearch.cpp -- Implementation file for directory searching methods.
//

#include "DirSearch.h"

#if PGE_PLATFORM != PGE_PLATFORM_WIN32

/** In windows, an integer value gets returned from _findfirst, that is passed
    to _findnext and _findclose.  This is a representation of a pointer to a
    structure defining the search state.  The search state contains the current
    directory, search pattern, etc.
*/
struct _SearchData_t
{
    char*   pattern;        /** Search pattern */
    char*   directory;      /** Current directory */
    char*   curFileName;    /** Most recently found filename */
    int     dirLength;      /** Length of the directory string */
    DIR     dirFD;          /** Directory handle.  Returned by opendir */

    // The Ogre version has a string pointer, curfn, which doesn't seem to be
    // doing anything.  Just a heads up as it might be needed later.
};

//_findfirst
long _findfirst( const char *pattern, struct _finddata_t *data )
{
    // Create the search data:
    _SearchData_t* sd = new _SearchData_t;
    sd->pattern = 0;
    sd->curFileName = 0;

    // Attempt to separate the file mask from the directory
    const char* mask = strrchr( pattern, '/' );
    if ( mask )
    {
        // Allocate the directory name pointer
        sd->dirLength = mask - pattern;
        mask++;
        sd->directory = new char [ sd->dirLength + 1 ];
        sd->directory[ sd->dirLength ] = '\0';
    }
    else
    {
        // Apparently no directory separators, so the entire pattern is the mask
        mask = pattern;

        // The directory is the current working directory, or '.'
        sd->directory = strdup( "." );
        sd->dirLength = 1;
    }

    // Open the directory:
    sd->dirFD = opendir( sd->directory );
    if ( !sd->dirFD )
    {
        _findclose((long)sd);
        return -1;
    }

    // *nix doesn't need *.* for a wildcard the way windows uses it.  Just use\
    // '*'
    if ( strcmp( mask, "*.*" ) == 0 )
        mask += 2;

    // Store the pattern as the current mask
    sd->pattern = strdup( mask );

    // Get the first entry:
    if ( _findnext( long(sd), data ) < 0 )
    {
        _findclose( (long)sd );
        return -1;
    }

    // Return the search data:
    return long( sd );
}

//_findnext
int _findnext( long id, struct _finddata_t *data )
{
    // Get the search data by casting the id:
    _SearchData_t* sd = (_SearchData_t*)id;

    // Loop until we either find an entry, or there are no more entries left
    dirent* entry;
    while ( true )  // careful!!!
    {
        // Get the entry.  If unable to read an entry, return error.
        if ( !( entry = readdir( sd->dirFD ) ) )
            return -1;

        // If the entry matches the filename pattern, break out of the loop.
        // This is the next entry.
        if ( fnmatch( sd->pattern, entry, 0 ) == 0 )
            break;
    }

    // Set the filename:
    if ( sd->curFileName )
        delete sd->curFileName;
    data->name = sd->curFileName = strdup( entry->d_name );

    // Fill in the full path name:
    size_t nameLength = strlen( entry->d_name );
    char* pathName = new char [ nameLength + 1 + sd->dirLength + 1 ];
    sprintf( pathName, "%s/%s", sd->directory, entry->d_name );

    // Using the full path name, check the status of the file to see if it is a
    // subdirectory
    struct stat stat_buf;
    if ( stat( pathName, &stat_buf ) )
    {
        // An error occurred, so just set it as an empty file:
        data->attrib = _A_NORMAL;
        data->size   = 0;
    }
    else
    {
        // Flag this as either a subdirectory or as a normal file
        if ( S_ISDIR( stat_buf.st_mode ) )
            data->attrib = _A_SUBDIR;
        else
            data->attrib = _A_NORMAL;

        // File size:
        data->size = stat_buf.st_size;
    }

    delete pathName;

    // In *nix, files that start with a '.' are hidden
    if ( data->name[ 0 ] == '.' )
        data->attrib |= _A_HIDDEN;

    return 0;
}

//_findclose
int _findclose( long id )
{
    // Get the search data by casting the id:
    _SearchData_t* sd = (_SearchData_t*)id;

    // If the directory is open (not null), attempt to close it:
    int retVal = ( sd->dirFD ) ? closedir( sd->dirFD ) : 0;
    delete sd->pattern;
    delete sd->directory;
    if ( sd->curFileName )
        delete sd->curFileName;
    delete sd;

    return retVal;
}

#endif  // !Windows
