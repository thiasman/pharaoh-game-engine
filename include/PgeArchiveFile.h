
/*! $Id$
 *  @file   PgeArchiveFile.h
 *  @author Chad M. Draper
 *  @date   November 3, 2008
 *  @brief  Provides file-like data access to objects in an archive.
 *
 */

#ifndef PGEARCHIVEFILE_H
#define PGEARCHIVEFILE_H

#include "PgeTypes.h"
#include "PgeSharedPtr.h"
#include <fstream>
//#include <unzip.h>
//#include "CanopicUnzip.h"
#include "physfs.h"

namespace PGE
{
    /** @class ArchiveFile
        Allows reading a resource file from an archive.  This is the base class
        from which all archive file types should be derived.
    */
    class _PgeExport ArchiveFile
    {
        friend class ArchiveManager;

    protected:
        PHYSFS_File*    mFile;          ///< Pointer to the file in the archive
        UInt32          mFileLength;    /**< The seek method in PhysFS only offsets from the
                                                start of the file.  We will mimic offsets from
                                                the current position and the end.
                                        */
        String          mFileName;      ///< Stores the full name of the file
        String          mFilePath;      ///< Path to the file

        /** Constructor */
        ArchiveFile( const String& fileName, bool isStream = false );

    public:
        enum SeekMode { Begin, Current, End };
        typedef SharedPtr< ArchiveFile > ArchiveFilePtr;
        /** Destructor */
        virtual ~ArchiveFile();

        /** Get the length of the file in bytes. */
        UInt32 Length();

        /** Open the data for reading */
        //virtual bool Open( const String& archiveLocation, const String& fileName, bool isStream = false );

        /** Go to a given position in the file */
        virtual bool Seek( UInt32 pos, SeekMode mode );

        /** Read a block of data from the file */
        virtual UInt32 Read( void* buffer, UInt32 size );

        /** Get the current position in the file */
        virtual UInt32 Tell();

        /** Get the name of the archive file */
        String GetFileName() const;
        /** Get the path to the archive file */
        String GetFilePath() const;

    private:
        /** Close the file */
        virtual void Close();
    };

} // namespace PGE

#endif // PGEARCHIVEFILE_H
