
/////////////////////////////////////////////////////////////////////
// $Id$
//
// DirSearch.h -- Header file for directory searching methods.
//
// Author       : Chad M. Draper
// Date         : June 10, 2008
// Description  : Implements cross-platform directory searching by mimicking
//                  Windows' _findfirst, _findnext, etc. methods.
//
/////////////////////////////////////////////////////////////////////
// Update Log
//      Date            Description
//      ----            ----------
//      2008-06-10      Initial implementation
//

#ifndef DIRSEARCH_H_INCLUDED
#define DIRSEARCH_H_INCLUDED

#include "PgePlatform.h"

// Include the proper headers for the operating system.  If Windows, then we
// can skip the code implementation and just use the existing headers.
#if defined( __WIN32__ ) || defined( _WIN32 )
#   include <windows.h>
#   include <direct.h>
#   include <io.h>
#else
#   include <sys/types.h>
#   include <dirent.h>

/** Theses methods attempt to replicate the functionality of _findfirst,
    _findnext, etc. on Windows in a cross-platform manner.  Their usage is
    intended to be identical to the Windows counterparts.
*/

/** @struct _finddata_t
    A Simple structure to hold information about the found file.
*/
struct _finddata_t
{
    char*   name;           /**< Name of the found file */
    int     attrib;         /**< Attributes of the found file */
    unsigned long size;     /**< Size of the file */
};

/** Attribute flags */
#define _A_NORMAL   0x00
#define _A_RDONLY   0x01
#define _A_HIDDEN   0x02
#define _A_SYSTEM   0x04
#define _A_SUBDIR   0x10
#define _A_ARCH     0x20

/** Find the first file that matches the given pattern
    @param  pattern     File-matching pattern to look for.  May contain wildcards '?' and '*'.
    @param  data        _finddata_t structure filled with the information of the found file.
    @return -1 if an error occurred.  Otherwise, the return value is a handle that can be
            used in subsequent _findnext or _findclose calls.
*/
long _findfirst( const char *pattern, struct _finddata_t *data );

/** Find the next file that matches the original pattern used in _findfirst
    @param  id          Value returned by a previous _findfirst call.
    @param  data        _finddata_t structure filled with the information of the found file.
    @return -1 if an error occurred and 0 if successful.
    @remarks
        It is <B>VITAL</B> that _findfirst is called before calling _findnext.
*/
int _findnext( long id, struct _finddata_t *data );

/** Close the file finding operation
    @param  id          Value called by the initial call to _findfirst
    @return -1 if an error occurred and 0 if successful.
*/
int _findclose( long id );


#endif // !Windows


#endif // DIRSEARCH_H_INCLUDED
