
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
        glEnable( GL_CULL_FACE );
        glCullFace( GL_BACK );

        // Set the background color:
        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

        // Enable blending:
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glEnable( GL_BLEND );

        // Set the size of the viewport:
        glViewport( 0, 0, mWidth, mHeight );

        // Clear the display:
        glClear( GL_COLOR_BUFFER_BIT );

        // Reset the projection matrix, and set it for orthographic display:
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( 0.0f, static_cast<float>( mWidth ), static_cast<float>( mHeight ), 0.0f, -1.0f, 1.0f );

        // Reset the modelview matrix:
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
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
        glClear( GL_COLOR_BUFFER_BIT );
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        PGE::Real walkSpeed = 100;
        mPosition += mVelocity * walkSpeed * elapsedMS;

        // Update the scene:
        mTileMapScene.Update( elapsedMS );
    }

    void TileGameState::Render()
    {
        mTileMapScene.Render( mPosition, mViewport );
    }

    //LoadTileStudioXML
    void TileGameState::LoadTileStudioXML( const String& fileName )
    {
        // Get a pointer to the archive file so we can start reading
        String baseDir, fileTitle;
        StringUtil::SplitFilename( fileName, baseDir, fileTitle );
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
        if ( projNode )
        {
            TiXmlNode* node;
            //node = projNode->FirstChild( "tileSetCount" );
            //if ( node )
            //{
            //    int tileSetCount = StringUtil::ToInt( XmlArchiveFile::GetItemValue( node ) );
            //}
            node = projNode->FirstChild( "tileSetList" );
            if ( node )
            {
                TiXmlNode* tilesetNode = node->FirstChild( "tileset" );
                while ( tilesetNode )
                {
                    mTileMapScene.ReadTileset( tilesetNode, baseDir );
                    tilesetNode = tilesetNode->NextSibling( "tileset" );
                }
            }
        }
    }

} // namespace PGE
