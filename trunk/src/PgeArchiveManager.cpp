
/*! $Id$
 *  @file   PgeResourceManager.cpp
 *  @author Chad M. Draper
 *  @date   November 3, 2008
 *
 */

#include "PgeArchiveManager.h"
#include "PgeArchiveFile.h"
#include "physfs.h"
#include <sstream>
//#include "PgeStringUtil.h"

//#include "PgeLogFileManager.h"

#include "cmd/StringUtil.h"
using cmd::StringUtil;

namespace PGE
{
    // Instantiate the singleton instance
    template<> ArchiveManager* Singleton< ArchiveManager >::mInstance = 0;

    //Constructor
    ArchiveManager::ArchiveManager()
    {
        PHYSFS_init( 0 );
    }

    //Destructor
    ArchiveManager::~ArchiveManager()
    {
        PHYSFS_deinit();
    }

    //GetSingleton
    ArchiveManager& ArchiveManager::GetSingleton()
    {
        assert( mInstance );
        return *mInstance;
    }

    //GetSingletonPtr
    ArchiveManager* ArchiveManager::GetSingletonPtr()
    {
        return mInstance;
    }

    String ArchiveManager::GetApplicationDir() const
    {
        return PHYSFS_getBaseDir();
    }

    //AddArchive
    Int ArchiveManager::AddArchive( const String& archiveLocation )
    {
        PHYSFS_addToSearchPath( archiveLocation.c_str(), 1 );
        return 1;
    }

    //CreateArchiveFile
    ArchiveFile* ArchiveManager::CreateArchiveFile( const String& resName )
    {
        String fileList = ToString();
        return new ArchiveFile( resName );
    }

    //Exists
    bool ArchiveManager::Exists( const String& resName ) const
    {
//        String fixedName = StringUtil::StandardizePath( resName );
        String fixedName = StringUtil::FixPath( resName );
        String fileList = ToString();
        return PHYSFS_exists( fixedName.c_str() );
        //PHYSFS_File* file = PHYSFS_openRead( fixedName.c_str() );
        //if ( file )
        //{
        //    PHYSFS_close( file );
        //    return( true );
        //}
        //return false;
    }

    //ToString
    std::string ArchiveManager::ToString() const
    {
        std::stringstream stream;
        char** files = PHYSFS_enumerateFiles("");
        char** curFile;
        for ( curFile = files; *curFile != NULL; curFile++ )
        {
            stream << "Resource: " << *curFile << std::endl;
        }

        return stream.str();
    }

} // namespace PGE
