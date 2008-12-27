
/*! $Id$
 *  @file   PgeAudiereArchiveFile.h
 *  @author Chad M. Draper
 *  @date   November 7, 2008
 *  @brief  Provides an interface between an archive file and audiere::File.
 *
 */
#ifndef PGEAUDIEREARCHIVEFILE_H
#define PGEAUDIEREARCHIVEFILE_H

#include "PgeTypes.h"
#include "PgeSharedPtr.h"
#include "audiere.h"
#include <fstream>
#include <stdio.h>

namespace PGE
{
    class ArchiveFile;

    /** @class AudiereArchiveFile
        Allows Audiere to use an archive file as the source.  This class is
        derived from audiere::RefImplementation<audiere::File>, and has an
        ArchiveFile member.  The implementation of the audiere::File class
        wraps the archive file.
    */
    class _PgeExport AudiereArchiveFile : public audiere::RefImplementation<audiere::File>
    {
    protected:
        typedef SharedPtr< ArchiveFile > ArchiveFilePtr;
        //std::ifstream   mFileStream;
        ArchiveFilePtr  mArchiveFile;

    public:
        AudiereArchiveFile();
        AudiereArchiveFile( const String& fileName );

        virtual ~AudiereArchiveFile();

        /** Open a file for reading. */
        bool Open( const String& fileName );

        /**
         * Read size bytes from the file, storing them in buffer.
         *
         * @param buffer  buffer to read into
         * @param size    number of bytes to read
         *
         * @return  number of bytes successfully read
         */
        ADR_METHOD(int) read( void* buffer, int size );

        /**
         * Jump to a new position in the file, using the specified seek
         * mode.  Remember: if mode is END, the position must be negative,
         * to seek backwards from the end of the file into its contents.
         * If the seek fails, the current position is undefined.
         *
         * @param position  position relative to the mode
         * @param mode      where to seek from in the file
         *
         * @return  true on success, false otherwise
         */
        ADR_METHOD(bool) seek( int position, SeekMode mode );

        /**
         * Get current position within the file.
         *
         * @return  current position
         */
        ADR_METHOD(int) tell();
    };

} // namespace PGE

#endif // PGEAUDIEREARCHIVEFILE_H
