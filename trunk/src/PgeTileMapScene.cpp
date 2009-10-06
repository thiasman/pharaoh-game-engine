
/*! $
 *  @file   PgeTileMapScene.cpp
 *  @author Chad M. Draper
 *  @date   January 19, 2009
 *
 */

#include "PgeTileMapScene.h"
//#include "PgeStringUtil.h"
#include "PgeViewport.h"
#include "PgeMath.h"
#include "PgeTextureManager.h"
#include "PgeArchiveFile.h"
#include "PgeArchiveManager.h"
#include "PgeXmlArchiveFile.h"

#if PGE_PLATFORM == PGE_PLATFORM_WIN32
#   include <windows.h>
#endif

#include <gl/gl.h>
#include <gl/glu.h>

#include "cmd/StringUtil.h"
using cmd::StringUtil;

namespace PGE
{

    //Constructor
    TileMapScene::TileMapScene()
        : mPrimaryTileSet( 0 )
    {
    }

    //Constructor
    TileMapScene::TileMapScene( TiXmlNode* setListNode, const String& baseDir, UInt32 mapNum )
        : mPrimaryTileSet( 0 )
    {
    }

    //ReadScene
    void TileMapScene::ReadScene( TiXmlNode* setListNode, const String& baseDir, UInt32 mapNum )
    {
        if ( setListNode )
        {
            // Get the number of tilesets so that we can allocate the map size
            TiXmlNode* node = setListNode->FirstChild( "tileSetCount" );
            if ( node )
            {
                int tileSetCount = StringUtil::ToInt( XmlArchiveFile::GetItemValue( node ) );
            }
            node = setListNode->FirstChild( "tileSetList" );
            if ( node )
            {
                TiXmlNode* tilesetNode = node->FirstChild( "tileset" );
                while ( tilesetNode )
                {
                    // Read the tileset and get the desired map.
                    ReadTileset( tilesetNode, baseDir, mapNum );
                }
            }
        }
    }

    //Update
    void TileMapScene::Update( PGE::Real32 elapsedMS )
    {
        // Update the tilesets
        TileSetMultiSet::iterator iter = mTileSets.begin();
        for ( iter; iter != mTileSets.end(); iter++ )
        {
            iter->Update( elapsedMS );
        }
    }

    //Render
    void TileMapScene::Render( Point2Df& offset, const Viewport& viewport )
    {
        // If there is no map set, we can either assert, or we can ignore this
        // and pretend the developer had other plans.  We'll give the developer
        // the benefit of the doubt, and just return from this method without
        // doing anything...
        if ( mPrimaryTileSet == 0 )
            return;
        glEnable( GL_TEXTURE_2D );

        // Go over the tile maps and calculate their offsets, then render the map.
        TileSetMultiSet::const_iterator mapIter = mTileSets.begin();
        Point2D viewSize = viewport.GetSize();
        Point2D primaryMapSize = mPrimaryTileSet->GetMapSize();
        offset.x = Math::Clamp( offset.x, viewSize.x - primaryMapSize.x, 0 );
        offset.y = Math::Clamp( offset.y, viewSize.y - primaryMapSize.y, 0 );
        for ( mapIter; mapIter != mTileSets.end(); mapIter++ )
        {
            // Calculate the ratio between the current map and the primary map
            Point2D curMapSize = mapIter->GetMapSize();
            Real ratioX = 1.0, ratioY = 1.0;
            if ( curMapSize.x != viewSize.x && primaryMapSize.x != viewSize.x )
                ratioX = ( primaryMapSize.x - viewSize.x ) / Real( curMapSize.x - viewSize.x );
            if ( curMapSize.y != viewSize.y && primaryMapSize.y != viewSize.y )
                ratioY = ( primaryMapSize.y - viewSize.y ) / Real( curMapSize.y - viewSize.y );

            // Calculate the offset of the current map using the offset for the
            // primary map and the ratios
            Point2Df curOffset( offset.x / ratioX, offset.y / ratioY );
            curOffset.y = Math::Clamp( curOffset.y, viewSize.y - curMapSize.y, 0 );

            mapIter->Render( curOffset, viewport );
        }

        glDisable( GL_TEXTURE_2D );
    }

    //ReadTileset
    void TileMapScene::ReadTileset( TiXmlNode* tilesetNode, const String& baseDir, UInt32 mapNum )
    {
        if ( !tilesetNode )
            return;

        // Read the tilesets and add them to the scene:
        TileSet set( tilesetNode, baseDir, mapNum );
        AddTileSet( set );
    }

    void TileMapScene::GenerateDefaultTileset( const String& textureName, const Point2Df& tileSize, const Point2D& tileCount )
    {
        //// Check if the tiles are textured.  This is a naive test, and
        //// isn't foolproof.
        //mImageFile  = textureName;
        //mIsTextured = ArchiveManager::GetSingleton().Exists( textureName );

        //mTileSize   = tileSize;
        //mTileCount  = tileCount;
        //mIndex      = 0;
        //mIdentifier = "default";

        //// Load the texture
        //if ( mIsTextured )
        //    TextureManager::GetSingleton().LoadImage( mImageFile, GL_NEAREST, GL_NEAREST, false, true );

        //// Generate the map:
        //TileMap tileMap;
        //tileMap.GenerateMap( mIdentifier, PGE::Point2Df( 32, 32 ), PGE::Point2D( 20, 20 ) );
        //tileMap.SetDepth( 0 );
        //AddTileMap( tileMap );
    }

    void TileMapScene::AddTileSet( TileSet& set )
    {
        // Add the map to the set:
        mTileSets.insert( set );

        if ( !mPrimaryTileSet )
        {
            mPrimaryTileSet = new TileSet();
            *mPrimaryTileSet = set;
        }
        else if ( set.mIndex == 0 && mPrimaryTileSet->mIndex != 0 )
            *mPrimaryTileSet = set;
    }

} // namespace PGE
