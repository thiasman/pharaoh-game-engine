
/*! $Id$
 *  @file   PgeArchiveHandler.h
 *  @author Chad M. Draper
 *  @date   November 3, 2008
 *  @brief  Base class for the archive handlers, as well as standard handlers
 *          for directories and zip files.
 *
 */
#ifndef PGEARCHIVEHANDLER_H
#define PGEARCHIVEHANDLER_H

#include "PgeTypes.h"

namespace PGE
{
    class ArchiveFile;

    /** @class ArchiveHandler
        Base class for the archive handlers.

        An archive handler will perform tasks specific to an archive.  It takes
        care of searching for files and getting file information.  It also
        creates the archive resource object, which allows reading from the
        archive.
    */
    class ArchiveHandler
    {
    protected:
        String      mType;          ///< Identifies the archive type (i.e. "directory", "zip", etc.)

    public:
        /** Constructor */
        ArchiveHandler();
        /** Destructor */
        virtual ~ArchiveHandler();

        /** Get the archive type */
        virtual String TypeDesc() const = 0;

        /** Search the archive for all files, and optionally search the sub-
            folders.

            @param  archiveLocation     Root of the archive
            @param  files       String vector of found files (directory names
                                are <b>NOT</b> included, but the file's relative
                                path is.  That is, a folder named 'images' is
                                not in the vector, but images/background.jpg
                                would be.)
            @param  recurse     Indicates if sub-folders should be searched.
            @return Number of files found.
        */
        virtual Int FindFiles( const String& archiveLocation, StringVector* files, bool recurse = true ) = 0;

        /** Create an archive file for a file in this archive so the data
            may be accessed.  If the file is not in this archive, then null is
            returned.
        */
        virtual ArchiveFile* CreateArchiveFile( const String& archiveLocation, const String& fileName, bool isStream ) = 0;
    };

    /** @class DirectoryArchiveHandler
        Archive handler for physical files on disk.
    */
    class DirectoryArchiveHandler : public ArchiveHandler
    {
    private:
        /** Helper function for searching a directory for files. */
        Int searchDirectory( const String& path, StringVector* files, bool recurse = true );

    public:
        /** Constructor */
        DirectoryArchiveHandler();
        /** Destructor */
        virtual ~DirectoryArchiveHandler();

        /** Get the archive type */
        static String Type()        { return "directory"; }
        /** Get the archive type */
        virtual String TypeDesc() const { return Type(); }

        /** Search the archive for all files, and optionally search the sub-
            folders.

            @param  archiveLocation     Root of the archive
            @param  files       String vector of found files (directory names
                                are <b>NOT</b> included, but the file's relative
                                path is.  That is, a folder named 'images' is
                                not in the vector, but images/background.jpg
                                would be.)
            @param  recurse     Indicates if sub-folders should be searched.
            @return Number of files found.
        */
        virtual Int FindFiles( const String& archiveLocation, StringVector* files, bool recurse = true );

        /** Create an archive file for a file in this archive so the data
            may be accessed.  If the file is not in this archive, then null is
            returned.
        */
        virtual ArchiveFile* CreateArchiveFile( const String& archiveLocation, const String& fileName, bool isStream );
    };

    /** @class ZipArchiveHandler
        Archive handler for files in a zip archive.
    */
    class ZipArchiveHandler : public ArchiveHandler
    {
    public:
        /** Constructor */
        ZipArchiveHandler();
        /** Destructor */
        virtual ~ZipArchiveHandler();

        /** Get the archive type */
        static String Type()        { return "zip"; }
        /** Get the archive type */
        virtual String TypeDesc() const { return Type(); }

        /** Search the archive for all files, and optionally search the sub-
            folders.

            @param  archiveLocation     Root of the archive
            @param  files       String vector of found files (directory names
                                are <b>NOT</b> included, but the file's relative
                                path is.  That is, a folder named 'images' is
                                not in the vector, but images/background.jpg
                                would be.)
            @param  recurse     Indicates if sub-folders should be searched.
            @return Number of files found.
        */
        virtual Int FindFiles( const String& archiveLocation, StringVector* files, bool recurse = true );

        /** Create an archive file for a file in this archive so the data
            may be accessed.  If the file is not in this archive, then null is
            returned.
        */
        virtual ArchiveFile* CreateArchiveFile( const String& archiveLocation, const String& fileName, bool isStream );
    };

} // namespace PGE

#endif // PGEARCHIVEHANDLER_H
