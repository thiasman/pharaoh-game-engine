
/*! $Id$
 *  @file   PgeArchiveFile.h
 *  @author Chad M. Draper
 *  @date   November 3, 2008
 *
 */

#include "PgeArchiveFile.h"
//#include "PgeStringUtil.h"
#include "physfs.h"

#include "cmd/StringUtil.h"
using cmd::StringUtil;

#include "PgeArchiveManager.h"

namespace PGE
{
    ////////////////////////////////////////////////////////////////////////////
    // ArchiveFile
    ////////////////////////////////////////////////////////////////////////////

    ArchiveFile::ArchiveFile( const String& fileName, bool isStream )
        : mFile( 0 )
    {
//        mFileName = StringUtil::StandardizePath( fileName );
        mFileName = StringUtil::FixPath( fileName );
        String temp;
//        StringUtil::SplitFilename( mFileName, mFilePath, temp );
        StringUtil::SplitFilename( mFileName, &mFilePath, &temp );
//        if ( ArchiveManager::GetSingleton().Exists( mFileName ) )
        {
            mFile = PHYSFS_openRead( mFileName.c_str() );
            mFileLength = Length();
        }
    }

    ArchiveFile::~ArchiveFile()
    {
        Close();
    }

    //GetLength
    UInt32 ArchiveFile::Length()
    {
        bool exists = ArchiveManager::GetSingleton().Exists( mFileName );
        assert( mFile );
        return PHYSFS_fileLength( mFile );
    }

    bool ArchiveFile::Seek( UInt32 pos, SeekMode mode )
    {
        assert( mFile );

        UInt32 seekPos = Tell();    // Default: do nothing
        switch ( mode )
        {
        case Begin:
            seekPos = pos;
            break;

        case Current:
            seekPos += pos;
            break;

        case End:
            seekPos += ( mFileLength - 1 );
            break;
        }

        int err = PHYSFS_seek( mFile, seekPos );
        return ( err != 0 );
    }

    UInt32 ArchiveFile::Read( void* buffer, UInt32 size )
    {
        assert( mFile );
        return PHYSFS_read( mFile, buffer, 1, size );
    }

    UInt32 ArchiveFile::Tell()
    {
        assert( mFile );
        return PHYSFS_tell( mFile );
    }

    void ArchiveFile::Close()
    {
        if ( mFile )
        {
            PHYSFS_close( mFile );
            mFile = 0;
        }
    }

    //GetFileName
    String ArchiveFile::GetFileName() const
    {
        return mFileName;
    }

    //GetFilePath
    String ArchiveFile::GetFilePath() const
    {
        return mFilePath;
    }

} // namespace PGE
