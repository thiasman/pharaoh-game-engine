
/*! $Id$
 *  @file   PgeArchiveHandler.h
 *  @author Chad M. Draper
 *  @date   November 3, 2008
 *
 */

#include "PgeArchiveHandler.h"
#include "PgeArchiveFile.h"
#include "PgeDirSearch.h"

namespace PGE
{
    ////////////////////////////////////////////////////////////////////////////
    // ArchiveHandler
    ////////////////////////////////////////////////////////////////////////////

    //Constructor
    ArchiveHandler::ArchiveHandler()
    {
        //ctor
    }

    //Destructor
    ArchiveHandler::~ArchiveHandler()
    {
        //dtor
    }

    ////////////////////////////////////////////////////////////////////////////
    // DirectoryArchiveHandler
    ////////////////////////////////////////////////////////////////////////////

    //Constructor
    DirectoryArchiveHandler::DirectoryArchiveHandler()
        : ArchiveHandler()
    {
        mType = "directory";
    }

    //Destructor
    DirectoryArchiveHandler::~DirectoryArchiveHandler()
    {
        //dtor
    }

    //searchDirectory
    Int DirectoryArchiveHandler::searchDirectory( const String& path, StringVector* files, bool recurse )
    {
        _finddata_t findData;
        String mask = path + "/*.*";
        long handle = _findfirst( mask.c_str(), &findData );
        long result = 0;
        while ( handle != -1 && result != -1 )
        {
            String dir = findData.name;
            if ( dir != "." && dir != ".." )
            {
                if ( ( findData.attrib & _A_SUBDIR ) && recurse )
                {
                    searchDirectory( path + "/" + findData.name, files, recurse );
                }
                else
                    files->push_back( path + "/" + findData.name );
            }

            result = _findnext( handle, &findData );
        }

        return files->size();
    }

    //FindFiles
    Int DirectoryArchiveHandler::FindFiles( const String& archiveLocation, StringVector* files, bool recurse )
    {
        // Find the files:
        Int count = searchDirectory( archiveLocation, files, recurse );

        // Go through the files and remove the directory from the name
        StringVector::iterator fileIter = files->begin();
        Int length = archiveLocation.length() + 1;
        for ( fileIter; fileIter != files->end(); fileIter++ )
        {
            fileIter->erase( 0, length );
        }
        return count;
    }

    //CreateArchiveFile
    ArchiveFile* DirectoryArchiveHandler::CreateArchiveFile( const String& archiveLocation, const String& fileName, bool isStream )
    {
        return new PhysicalFile( archiveLocation, fileName, isStream );
    }

    ////////////////////////////////////////////////////////////////////////////
    // ZipArchiveHandler
    ////////////////////////////////////////////////////////////////////////////

    //Constructor
    ZipArchiveHandler::ZipArchiveHandler()
        : ArchiveHandler()
    {
        mType = "zip";
    }

    //Destructor
    ZipArchiveHandler::~ZipArchiveHandler()
    {
        //dtor
    }

    //FindFiles
    Int ZipArchiveHandler::FindFiles( const String& archiveLocation, StringVector* files, bool recurse )
    {
        unzFile zipFile;
        zipFile = unzOpen( archiveLocation.c_str() );
        if ( !zipFile )
            return 0;

        int status = unzGoToFirstFile( zipFile );
        while ( status == UNZ_OK )
        {
            unz_file_info fileInfo;
            unzGetCurrentFileInfo( zipFile, &fileInfo, NULL, 0, NULL, 0, NULL, 0 );
            if ( fileInfo.size_filename > 0 && fileInfo.uncompressed_size > 0 )
            {
                char* fileName = new char [ fileInfo.size_filename + 1 ];
                memset( fileName, 0, fileInfo.size_filename + 1 );
                unzGetCurrentFileInfo( zipFile, &fileInfo, fileName, fileInfo.size_filename + 1, NULL, 0, NULL, 0 );
                files->push_back( String( fileName ) );
            }

            status = unzGoToNextFile( zipFile );
        }

        return files->size();
    }

    //CreateArchiveFile
    ArchiveFile* ZipArchiveHandler::CreateArchiveFile( const String& archiveLocation, const String& fileName, bool isStream )
    {
        return new ZipFile( archiveLocation, fileName, isStream );
    }

} // namespace PGE
