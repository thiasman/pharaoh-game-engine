
/*! $Id$
 *  @file   PgeTileGameState.cpp
 *  @author Chad M. Draper
 *  @date   November 17, 2008
 *
 */

#include "PgeTileGameState.h"
#include "PgeTextureManager.h"
#include "PgeMath.h"
#include "PgeColor.h"
#include "PgePoint2D.h"
#include "PgeTypes.h"
#include "PgeArchiveManager.h"
#include "PgeXmlArchiveFile.h"
//#include "PgeStringUtil.h"

#include "tinyxml.h"

#include "cmd/LogFileManager.h"
using cmd::LogFileManager;
using cmd::LogFileSection;

//#include "PgeLogFileManager.h"
#include "cmd/StringUtil.h"
using cmd::StringUtil;

namespace PGE
{
    TileGameState::TileGameState()
        : mTexID( 0 ),
          mVelocity( PGE::Point2Df::ZERO ),
          mAngle( 0 ),
          mWidth( 0 ),
          mHeight( 0 )
    {
    }

    TileGameState::~TileGameState()
    {
    }

    void TileGameState::Init()
    {
//        LogFileManager& lfm = LogFileManager::GetSingleton();
//        LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::Init()" );

        //glEnable( GL_TEXTURE_2D );
        glEnable( GL_CULL_FACE );
        glCullFace( GL_BACK );
    //glCullFace( GL_FRONT );

        // Set the background color:
        //PGE::Colorf col = PGE::Colorf::RandomRGB();
        //glClearColor( col.r, col.g, col.b, col.a );
        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

        // Enable blending:
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glEnable( GL_BLEND );
        //glAlphaFunc( GL_GREATER,0.0f );
        //glEnable( GL_ALPHA_TEST );

        // Set the size of the viewport:
        glViewport( 0, 0, mWidth, mHeight );

        // Clear the display:
        glClear( GL_COLOR_BUFFER_BIT );

        // Reset the projection matrix, and set it for orthographic display:
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( 0.0f, static_cast<float>( mWidth ), static_cast<float>( mHeight ), 0.0f, -1.0f, 1.0f );
        //glOrtho( -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f );

        // Reset the modelview matrix:
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

//        TextureManager::GetSingleton().LoadImage( mTextureName );

//        TileMap tileMap;
//        //mTileMap.GenerateMap( PGE::Point2Df( 32, 32 ), PGE::Point2D( 200, 200 ) );
//        tileMap.GenerateMap( PGE::Point2Df( 32, 32 ), PGE::Point2D( 20, 20 ) );
//        //mTileMap.LoadMap( "test01/test01.xml" );
//        tileMap.SetDepth( 0 );
//        mTileSet.AddTileMap( tileMap );
//        mTileSet.GenerateDefaultTileset( mTextureName, PGE::Point2Df( 32, 32 ), PGE::Point2D( 20, 20 ) );
    }

    //SetWindowPosition
    void TileGameState::SetWindowSize( PGE::UInt32 w, PGE::UInt32 h )
    {
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();

        mWidth = w;
        mHeight = h;
        mViewport.SetSize( w, h );
        glViewport( 0, 0, mWidth, mHeight );
        glOrtho( 0.0f, static_cast<float>( mWidth ), static_cast<float>( mHeight ), 0.0f, -1.0f, 1.0f );

        glMatrixMode( GL_MODELVIEW );
    }

    void TileGameState::Update( PGE::Real32 elapsedMS )
    {
        LogFileManager& lfm = LogFileManager::getInstance();
        LogFileSection sect( lfm.GetDefaultLog(), "TileGameState::Update(...)" );

        glClear( GL_COLOR_BUFFER_BIT );
        //glRotatef( elapsedMS * 360.0f / 2000.0f, 0.0f, 0.0f, 1.0f );
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        //glRotatef( mAngle, 0.0f, 0.0f, 1.0f );

        PGE::Real walkSpeed = 100;
        mPosition += mVelocity * walkSpeed * elapsedMS;
        //mPosition += mVelocity;
        //glTranslatef( mPosition.x, mPosition.y, 0.0 );
        lfm << "elapsedMS = " << elapsedMS << ", velocity = " << mVelocity << ", position = " << mPosition << std::endl;
        //glTranslatef( mVelocity.x * elapsedMS, mVelocity.y * elapsedMS, 0.0 );
    }

    void TileGameState::Render()
    {
        PGE::TextureItem* texItem = PGE::TextureManager::GetSingleton().GetTextureItemPtr( mTextureName );
        PGE::UInt32 texID = texItem->GetID();
        glBindTexture( GL_TEXTURE_2D, texID );

        float aspectRatio = texItem->GetWidth() / float( texItem->GetHeight() );
        float w = 1.0f, h = 1.0f;
        if ( aspectRatio < 1.0 )
        {
            w = aspectRatio;
            h = 1.0;
        }
        else
        {
            w = 1.0;
            h = 1.0f / aspectRatio;
        }

        mTileMapCollection.Render( mPosition, mViewport );
    }

    //LoadTileStudioXML
    void TileGameState::LoadTileStudioXML( const String& fileName )
    {
//        LogFileManager& lfm = LogFileManager::GetSingleton();
//        LogFileSection sect( lfm.GetDefaultLog(), "TileGameState::LoadMap(...)" );

        // Get a pointer to the archive file so we can start reading
        String baseDir, fileTitle;
//        StringUtil::SplitFilename( fileName, baseDir, fileTitle );
        StringUtil::SplitFilename( fileName, &baseDir, &fileTitle );
        XmlArchiveFile doc( ArchiveManager::GetSingleton().CreateArchiveFile( fileName ) );
        if ( doc.LoadFile() )
        {
            TiXmlNode* node = doc.FirstChild( "project" );
            while ( node )
            {
                ReadProject( node, baseDir );
                node = node->NextSibling( "project" );
            }
        }
    }

    //ReadProject
    void TileGameState::ReadProject( TiXmlNode* projNode, const String& baseDir )
    {
//        LogFileManager& lfm = LogFileManager::GetSingleton();
//        LogFileSection sect( lfm.GetDefaultLog(), "TileGameState::ReadProject(...)" );

        if ( projNode )
        {
            TiXmlNode* node = projNode->FirstChild( "tileSetCount" );
            if ( node )
            {
                int tileSetCount = StringUtil::ToInt( XmlArchiveFile::GetItemValue( node ) );
//                lfm << "tile set count = " << tileSetCount << std::endl;
            }
            node = projNode->FirstChild( "tileSetList" );
            if ( node )
            {
                TiXmlNode* tilesetNode = node->FirstChild( "tileset" );
                while ( tilesetNode )
                {
                    mTileMapCollection.ReadTileset( tilesetNode, baseDir );
                    tilesetNode = tilesetNode->NextSibling( "tileset" );
                }
            }
        }
    }

} // namespace PGE
