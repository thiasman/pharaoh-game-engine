
/*! $Id$
 *  @file   PgeResourceManager.h
 *  @author Chad M. Draper
 *  @date   November 3, 2008
 *  @brief  An archive is a location that contains resource "files".  This could
 *          be a directory or zip file.  The archive manager keeps track of
 *          archives which have been added to the application, and what "files"
 *          are in them.  This allows files to be accessed by name, without the
 *          full path.
 *
 */

#ifndef PGEARCHIVEMANAGER_H
#define PGEARCHIVEMANAGER_H


#include "PgeTypes.h"
#include "PgeSharedPtr.h"
#include "PgeSingleton.h"

#include <map>
#include <ostream>

namespace PGE
{
    class ArchiveFile;

    /** @class ArchiveManager

        The archive manager keeps track of all archives which have been added.
        It also examines the contents of these archives so that a resource may
        be referenced by name, rather than the full path.  This means that a
        resource that exists in a zip file can be referenced the same as a
        resource in a directory.

        @remarks
            The actual archive type and its associated handler methods are
            abstracted to allow user-defined archive types.  However, directory,
            individual file, and zip files come standard.
    */
    class _PgeExport ArchiveManager : public Singleton< ArchiveManager >
    {
    private:

    protected:
        /** Generate a string representation of the class */
        std::string ToString() const;

    public:
        ArchiveManager();
        virtual ~ArchiveManager();

        /** Override singleton retrieval to avoid link errors */
        static ArchiveManager& GetSingleton();
        /** Override singleton pointer retrieval to avoid link errors */
        static ArchiveManager* GetSingletonPtr();

        /** Get the base directory of the application */
        String GetApplicationDir() const;

        /** Add an archive to the manager.  This will search the archive for all
            files, and add the files to the manager.
        */
        Int AddArchive( const String& archiveLocation );

        /** Get an archive file pointer for a given resource.  If the resource
            is not in the archive manager, null is returned.

            @param  resName         Name of the resource as it appears in the manager.  For
                                    directory archives, this is the full file path <b>after</b>
                                    the archive name (for instance, if the file is in
                                    c:/media/images/background.jpg, and the archive is
                                    c:/media, then the resource name is images/background.jpg.)
            @param  isStream        Indicates if the files is to be streamed, or if all data
                                    should be loaded into the archive file's buffer.  If it
                                    is being streamed, no data is read at this time.
        */
        ArchiveFile* CreateArchiveFile( const String& resName );

        /** Check whether a file exists in the archive */
        bool Exists( const String& resName ) const;


        /** Write the manager contents to a stream. */
        inline friend std::ostream& operator<<( std::ostream& stream, const ArchiveManager& src )
        {
            std::ostream::sentry opfx(stream);
            if ( !opfx )
                return stream;
            stream << src.ToString();
            return stream;
        }
    };

} // namespace PGE

#endif // PGEARCHIVEMANAGER_H
