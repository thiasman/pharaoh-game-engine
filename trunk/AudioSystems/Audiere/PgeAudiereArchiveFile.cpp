
/*! $Id$
 *  @file   PgeAudiereArchiveFile.h
 *  @author Chad M. Draper
 *  @date   November 7, 2008
 *
 */

#include "PgeAudiereArchiveFile.h"
#include "PgeArchiveFile.h"
#include "PgeArchiveManager.h"

//#include "PgeLogFileManager.h"

namespace PGE
{
    AudiereArchiveFile::AudiereArchiveFile()
    {
    }

    AudiereArchiveFile::AudiereArchiveFile( const String& fileName )
        : mArchiveFile( ArchiveFilePtr( ArchiveManager::GetSingleton().CreateArchiveFile( fileName ) ) )
    {
        //ctor
        Open( fileName );
    }

    AudiereArchiveFile::~AudiereArchiveFile()
    {
//        LogFileManager& lfm = LogFileManager::GetSingleton();
//        LogFileSection sect( lfm.GetDefaultLog(), "AudiereArchiveFile::~AudiereArchiveFile()" );

        //mFileStream.close();
        //fclose( mFile );
    }

    bool AudiereArchiveFile::Open( const String& fileName )
    {
        mArchiveFile.SetNull();
        mArchiveFile = ArchiveFilePtr( ArchiveManager::GetSingleton().CreateArchiveFile( fileName ) );
        return !mArchiveFile.IsNull();
//        if ( mFileStream.is_open() )
//            mFileStream.close();
//        mFileStream.open( filename.c_str(), std::ios::in | std::ios::binary );
//        return mFileStream.is_open();
    }

    int AudiereArchiveFile::read(void* buffer, int size)
    {
        if ( mArchiveFile.IsNull() )
            return 0;
//        LogFileManager& lfm = LogFileManager::GetSingleton();
//        LogFileSection sect( lfm.GetDefaultLog(), "AudiereArchiveFile::read(...)" );
        int bytesRead = mArchiveFile->Read( buffer, size );
        return bytesRead;

        /*
        if ( !mFileStream.is_open() )
            return 0;
        mFileStream.read( (char*)buffer, size );
        int bytesRead = mFileStream.gcount();

        // If the read put the position past the end of the file, then the file
        // stream will have an eof error set.  This needs to be cleared, or we
        // will be unable to do anything with the file.
        mFileStream.clear();
        return bytesRead;
        */
    }

    bool AudiereArchiveFile::seek(int position, SeekMode mode)
    {
        if ( mArchiveFile.IsNull() )
            return false;

        switch ( mode )
        {
        case audiere::File::BEGIN:
            return mArchiveFile->Seek( position, ArchiveFile::Begin );

        case audiere::File::CURRENT:
            return mArchiveFile->Seek( position, ArchiveFile::Current );

        case audiere::File::END:
            return mArchiveFile->Seek( position, ArchiveFile::End );
        }
        return false;

        /*
        if ( !mFileStream.is_open() )
            return false;

        switch ( mode )
        {
        case audiere::File::BEGIN:
            mFileStream.seekg( position, std::ios::beg );
            break;

        case audiere::File::CURRENT:
            mFileStream.seekg( position, std::ios::cur );
            break;

        case audiere::File::END:
            mFileStream.seekg( position, std::ios::end );
            break;

        default:
            return false;
        }
        return true;
        */
    }

    int AudiereArchiveFile::tell()
    {
        if ( mArchiveFile.IsNull() )
            return 0;
        //int pos = mFileStream.tellg();
        int pos = mArchiveFile->Tell();
        return pos;
    }

} // namespace PGE
