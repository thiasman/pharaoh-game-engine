
/*! $
 *  @file   PgeTileMap.cpp
 *  @author Chad M. Draper
 *  @date   August 13, 2008
 *
 */

#include "PgeTileMap.h"
#include "PgeViewport.h"
#include "PgeMath.h"
#include "PgeTextureManager.h"
#include "PgeArchiveFile.h"
#include "PgeArchiveManager.h"
#include "PgeXmlArchiveFile.h"
//#include "PgeStringUtil.h"

#if PGE_PLATFORM == PGE_PLATFORM_WIN32
#   include <windows.h>
#endif

#include <gl/gl.h>
#include <gl/glu.h>

//#include "PgeLogFileManager.h"
#include "cmd/StringUtil.h"
using cmd::StringUtil;

namespace PGE
{
    ////////////////////////////////////////////////////////////////////////////
    // TileSequence
    ////////////////////////////////////////////////////////////////////////////

    //Constructor
    TileSequence::TileSequence( Real frameRate )
    {
    }

    //Destructor
    TileSequence::~TileSequence()
    {
    }

    //operator=
    TileSequence& TileSequence::operator=( const TileSequence& src )
    {
        mName       = src.mName;
        mFrameRate  = src.mFrameRate;
        mCurrentFrame = src.mCurrentFrame;

        mSequence.assign( src.mSequence.begin(), src.mSequence.end() );

        return *this;
    }

    //ReadMap
    void TileSequence::ReadSequence( TiXmlNode* mapNode, const String& setID, UInt32 setIndex )
    {
    }

    //Prepare
    void TileSequence::Prepare( Real elapsedMS )
    {
    }

    //Render
    void TileSequence::Render()
    {
        assert( mCurrentFrame >= 0 && mCurrentFrame < mSequence.size() );
    }


    ////////////////////////////////////////////////////////////////////////////
    // TileMap
    ////////////////////////////////////////////////////////////////////////////

    TileMap::TileMap()
        : mIdentifier( "" ), mDepth( 0 ), mTilesetDepth( 0 )
    {
        //ctor
    }

    TileMap::TileMap( const Point2Df& tileSize )
        : mIdentifier( "" ), mDepth( 0 ), mTilesetDepth( 0 )
    {
        SetTileSize( tileSize );
    }

    TileMap::~TileMap()
    {
        //dtor
    }

    //operator=-----------------------------------------------------------------
    const TileMap& TileMap::operator=( const TileMap& src )
    {
        mTileSize   = src.mTileSize;
        mTileCount  = src.mTileCount;
        mMapSize    = src.mMapSize;
        mIdentifier = src.mIdentifier;
        mTileSetID  = src.mTileSetID;
        mDepth      = src.mDepth;
        mTilesetDepth = src.mTilesetDepth;

        mTileMap.assign( src.mTileMap.begin(), src.mTileMap.end() );

        return *this;
    }

    //operator<-----------------------------------------------------------------
    bool TileMap::operator<( const TileMap& src ) const
    {
        if ( mTilesetDepth == src.mTilesetDepth )
            return mDepth < src.mDepth;
        return mTilesetDepth < src.mTilesetDepth;
    }

    //operato><-----------------------------------------------------------------
    bool TileMap::operator>( const TileMap& src ) const
    {
        if ( mTilesetDepth == src.mTilesetDepth )
            return mDepth > src.mDepth;
        return mTilesetDepth > src.mTilesetDepth;
    }

    //GenerateMap---------------------------------------------------------------
    void TileMap::GenerateMap( const String& setID, const Point2Df& tileSize, const Point2D& tileCount )
    {
        mTileSize = tileSize;
        mTileCount = tileCount;

        // Calculate the physical size of the tile map
        mMapSize = tileSize * mTileCount;

        TileManager::TileSetData setData;
        setData.mTileCount = mTileCount.x * mTileCount.y;
        setData.mDisplayListBase = glGenLists( setData.mTileCount );
        assert( setData.mDisplayListBase != 0 );

        TileManager::GetSingleton().AddTileSet( setID, setData );
        mIdentifier = "debug";
        mTileSetID  = setID;

        // Allocate the array for the tiles:
        mTileMap.resize( mTileCount.x * mTileCount.y );

        Colorf mColorGrid[] = { Colorf( 1.0, 0.0, 0.0, 1.0 ), Colorf( 0.0, 1.0, 0.0, 1.0 ),
                                Colorf( 0.0, 0.0, 1.0, 1.0 ), Colorf( 1.0, 1.0, 1.0, 1.0 ) };
        Real hColorDiff = 1.0 / Real( mTileCount.x - 1 );
        Real vColorDiff = 1.0 / Real( mTileCount.y - 1 );
        Colorf leftColor, rightColor;


        // Ratios for the texture coordinates
        Real texCoordMaxX = 1.0;
        Real texCoordMaxY = 1.0;
        Real texCoordXDiff = texCoordMaxX / Real( tileCount.x );
        Real texCoordYDiff = texCoordMaxY / Real( tileCount.y );

        // Generate the remaining tiles
        UInt32 count = 0;
        for ( Int y = 0; y < mTileCount.y; y++ )
        {
            leftColor = mColorGrid[ 0 ].Lerp( mColorGrid[ 1 ], y / Real( mTileCount.y ) );
            rightColor = mColorGrid[ 2 ].Lerp( mColorGrid[ 3 ], y / Real( mTileCount.y ) );

            for ( Int x = 0; x < mTileCount.x; x++ )
            {
                glNewList( setData.mDisplayListBase + count, GL_COMPILE );
                glBegin( GL_QUADS );
                {
                    // Add the tile:
                    Tile newTile;
                    newTile.tileIndex = y * mTileCount.x + x;
                    mTileMap.at( y * mTileCount.x + x ) = newTile;

                    Colorf color = leftColor.Lerp( rightColor, x / Real( mTileCount.x ) );

                    //glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
                    glColor4fv( &color.r );

                    glTexCoord2f( x * texCoordXDiff, y * texCoordYDiff );
                    glVertex3f( 0.0f, 0.0f, 0.0f );

                    glTexCoord2f( x * texCoordXDiff, ( y + 1 ) * texCoordYDiff );
                    glVertex3f( 0.0f, tileSize.y, 0.0f );

                    glTexCoord2f( ( x + 1 ) * texCoordXDiff, ( y + 1 ) * texCoordYDiff );
                    glVertex3f( tileSize.x, tileSize.y, 0.0f );

                    glTexCoord2f( ( x + 1 ) * texCoordXDiff, y * texCoordYDiff );
                    glVertex3f( tileSize.x, 0.0f, 0.0f );
                }
                glEnd();

                glBegin( GL_LINE_LOOP );
                {
                    glColor3f( 0.0, 0.0, 0.0 );

                    // Add the vertex:
                    glVertex3f( 0.0f, 0.0f, 0.0f );
                    glVertex3f( 0.0f, tileSize.y, 0.0f );
                    glVertex3f( tileSize.x, tileSize.y, 0.0f );
                    glVertex3f( tileSize.x, 0.0f, 0.0f );
                }
                glEnd();

                glTranslatef( mTileSize.x, 0, 0 );
                glEndList();
                ++count;
            }
        }
    }

    //SetTileSize
    void TileMap::SetTileSize( const Point2Df& tileSize )
    {
        mTileSize = tileSize;
        mMapSize = mTileSize * mTileCount;
    }

    //ReadMap
    void TileMap::ReadMap( TiXmlNode* mapNode, const String& setID, UInt32 setIndex )
    {
        if ( !mapNode )
            return;

        mTilesetDepth = setIndex;
        mDepth       = StringUtil::ToInt( XmlArchiveFile::GetItemValue( mapNode->FirstChild( "index" ) ) );
        mIdentifier  = XmlArchiveFile::GetItemValue( mapNode->FirstChild( "identifier" ) );
        mTileSetID   = setID;
        mTileCount.x = StringUtil::ToInt( XmlArchiveFile::GetItemValue( mapNode->FirstChild( "width" ) ) );
        mTileCount.y = StringUtil::ToInt( XmlArchiveFile::GetItemValue( mapNode->FirstChild( "height" ) ) );

        mMapSize = mTileSize * mTileCount;

        // Allocate the array for the tiles:
        mTileMap.resize( mTileCount.x * mTileCount.y );

        TiXmlNode* cellNode = mapNode->FirstChild( "cellList" );
        if ( cellNode )
        {
            cellNode = cellNode->FirstChild( "cell" );
            int curCell = 0;
            while ( cellNode )
            {
                int tileNum = StringUtil::ToInt( XmlArchiveFile::GetItemValue( cellNode->FirstChild( "tileNumber" ) ) );
                int boundsCode = StringUtil::ToInt( XmlArchiveFile::GetItemValue( cellNode->FirstChild( "bounds" ) ) );
                int mapCode = StringUtil::ToInt( XmlArchiveFile::GetItemValue( cellNode->FirstChild( "mapCode" ) ) );

                //lfm << "tile # = " << tileNum << ", bounds = " << boundsCode << ", mapCode = " << mapCode << std::endl;

                // Add the tile:
                Tile newTile;
                newTile.tileIndex = tileNum;
                newTile.boundsCode = boundsCode;
                newTile.mapCode = mapCode;
                mTileMap.at( curCell++ ) = newTile;

                cellNode = cellNode->NextSibling( "cell" );
            }
        }
    }

    //SetTilesetIndex-----------------------------------------------------------
    void TileMap::SetTilesetIndex( UInt32 index )
    {
        mTilesetDepth = index;
    }

    //GetTilesetIndex-----------------------------------------------------------
    UInt32 TileMap::GetTilesetIndex() const
    {
        return mTilesetDepth;
    }

    //SetDepth------------------------------------------------------------------
    void TileMap::SetDepth( Real depth )
    {
        mDepth = depth;
    }

    //GetDepth------------------------------------------------------------------
    UInt32 TileMap::GetDepth() const
    {
        return mDepth;
    }

    //RenderTileSpan------------------------------------------------------------
    void TileMap::RenderTileSpan( TileArray::const_iterator& tileIter, const UInt32& displayListBase, UInt32 count ) const
    {
        Int curTile = count;
        while ( tileIter != mTileMap.end() && curTile >= 0 )
        {
            if ( tileIter->tileIndex < 0 )
            {
                // Negative values indicate a sequence...
                Int seqIndex = Math::Abs( tileIter->tileIndex );
                glCallList( displayListBase );
            }
            else
                glCallList( displayListBase + tileIter->tileIndex );

//            glCallList( displayListBase + tileIter->tileIndex );

            // Increment the tile iterator and decrement the count
            ++tileIter;
            --curTile;
        }
    }

    //Render--------------------------------------------------------------------
    void TileMap::Render( UInt32 displayListBase, const Point2Df& offset, const Viewport& viewport ) const
    {
        TextureItem* textureItem = TextureManager::GetSingleton().GetTextureItemPtr( mTileSetID );
        if ( textureItem )
        {
            UInt32 texID = textureItem->GetID();
            glBindTexture( GL_TEXTURE_2D, texID );
        }

        Point2D displayTiles( Math::Ceil( viewport.GetSize().x / mTileSize.x ),
                              Math::Ceil( viewport.GetSize().y / mTileSize.y ) );
        displayTiles.x = Math::Clamp( displayTiles.x, 0, mTileCount.x );
        displayTiles.y = Math::Clamp( displayTiles.y, 0, mTileCount.y );

        // Find the first tile to render:
        Point2D startTile = -offset / mTileSize;
        startTile.x = Math::Clamp( startTile.x, 0, mTileCount.x - displayTiles.x );
        startTile.y = Math::Clamp( startTile.y, 0, mTileCount.y - displayTiles.y );
        Point2D endTile;
        endTile.x = Math::Ceil( ( viewport.GetSize().x - offset.x ) / mTileSize.x );
        endTile.y = Math::Ceil( ( viewport.GetSize().y - offset.y ) / mTileSize.y );
        endTile.x = Math::Clamp( endTile.x, 0, mTileCount.x - 1 );
        endTile.y = Math::Clamp( endTile.y, 0, mTileCount.y - 1 );

        // Iterate over the tile rows and render spans of tiles
        UInt32 spanCount = ( endTile.x - startTile.x );
        //Point2Df rowPosition = offset + ( startTile * mTileSize );
        Point2Df rowPosition = offset;
        if ( mMapSize.x < viewport.GetSize().x )
            rowPosition.x = ( viewport.GetSize().x - mMapSize.x ) / 2.0;
        if ( mMapSize.y < viewport.GetSize().y )
            rowPosition.y = ( viewport.GetSize().y - mMapSize.y ) / 2.0;

        // Get the display list base containing the tiles for this map
        //UInt32 displayListBase = TileManager::GetSingleton().GetTileSetBase( mTileMapSetName );

        UInt32 startIndex = startTile.y * mTileCount.x + startTile.x;
        glPushMatrix();
        Point2D offsetInt( rowPosition.x + startTile.x * mTileSize.x, rowPosition.y + startTile.y * mTileSize.y );
        //glTranslatef( rowPosition.x + startTile.x * mTileSize.x, rowPosition.y + startTile.y * mTileSize.y, 0 );
        glTranslatef( offsetInt.x, offsetInt.y, 0 );
        for ( int tileY = startTile.y; tileY <= endTile.y; tileY++ )
        {
            // Get the iterator:
            TileArray::const_iterator tileIter = mTileMap.begin() + startIndex;

            // Render the tile span:
            glPushMatrix();
                RenderTileSpan( tileIter, displayListBase, spanCount );
            glPopMatrix();
            glTranslatef( 0, mTileSize.y, 0 );

            //rowPosition.y += mTileSize.y;
            startIndex += mTileCount.x;
        }
        glPopMatrix();
    }

    //Render--------------------------------------------------------------------
    void TileMap::Render( const Point2Df& offset, const Viewport& viewport ) const
    {
        TextureItem* textureItem = TextureManager::GetSingleton().GetTextureItemPtr( mTileSetID );
        if ( textureItem )
        {
            UInt32 texID = textureItem->GetID();
            glBindTexture( GL_TEXTURE_2D, texID );
        }

        UInt32 displayListBase = TileManager::GetSingleton().GetTileSetBase( mTileSetID );
        Point2D displayTiles( Math::Ceil( viewport.GetSize().x / mTileSize.x ),
                              Math::Ceil( viewport.GetSize().y / mTileSize.y ) );
        displayTiles.x = Math::Clamp( displayTiles.x, 0, mTileCount.x );
        displayTiles.y = Math::Clamp( displayTiles.y, 0, mTileCount.y );

        // Find the first tile to render:
        Point2D startTile = -offset / mTileSize;
        startTile.x = Math::Clamp( startTile.x, 0, mTileCount.x - displayTiles.x );
        startTile.y = Math::Clamp( startTile.y, 0, mTileCount.y - displayTiles.y );
        Point2D endTile;
        endTile.x = Math::Ceil( ( viewport.GetSize().x - offset.x ) / mTileSize.x );
        endTile.y = Math::Ceil( ( viewport.GetSize().y - offset.y ) / mTileSize.y );
        endTile.x = Math::Clamp( endTile.x, 0, mTileCount.x - 1 );
        endTile.y = Math::Clamp( endTile.y, 0, mTileCount.y - 1 );

        // Iterate over the tile rows and render spans of tiles
        UInt32 spanCount = ( endTile.x - startTile.x );
        //Point2Df rowPosition = offset + ( startTile * mTileSize );
        Point2Df rowPosition = offset;
        if ( mMapSize.x < viewport.GetSize().x )
            rowPosition.x = ( viewport.GetSize().x - mMapSize.x ) / 2.0;
        if ( mMapSize.y < viewport.GetSize().y )
            rowPosition.y = ( viewport.GetSize().y - mMapSize.y ) / 2.0;

        // Get the display list base containing the tiles for this map
        //UInt32 displayListBase = TileManager::GetSingleton().GetTileSetBase( mTileMapSetName );

        UInt32 startIndex = startTile.y * mTileCount.x + startTile.x;
        glPushMatrix();
        Point2D offsetInt( rowPosition.x + startTile.x * mTileSize.x, rowPosition.y + startTile.y * mTileSize.y );
        //glTranslatef( rowPosition.x + startTile.x * mTileSize.x, rowPosition.y + startTile.y * mTileSize.y, 0 );
        glTranslatef( offsetInt.x, offsetInt.y, 0 );
        for ( int tileY = startTile.y; tileY <= endTile.y; tileY++ )
        {
            // Get the iterator:
            TileArray::const_iterator tileIter = mTileMap.begin() + startIndex;

            // Render the tile span:
            glPushMatrix();
                RenderTileSpan( tileIter, displayListBase, spanCount );
            glPopMatrix();
            glTranslatef( 0, mTileSize.y, 0 );

            //rowPosition.y += mTileSize.y;
            startIndex += mTileCount.x;
        }
        glPopMatrix();
    }

    ////////////////////////////////////////////////////////////////////////////
    // TileManager
    ////////////////////////////////////////////////////////////////////////////

    // Instantiate the singleton instance
    template<> TileManager* Singleton< TileManager >::mInstance = 0;

    //Constructor
    TileManager::TileManager()
    {
    }

    //Destructor
    TileManager::~TileManager()
    {
    }

    //GetSingleton
    TileManager& TileManager::GetSingleton()
    {
        assert( mInstance );
        return *mInstance;
    }

    //GetSingletonPtr
    TileManager* TileManager::GetSingletonPtr()
    {
        return mInstance;
    }

    //AddTileSet
    void TileManager::AddTileSet( const String& key, const TileSetData& data )
    {
        mTileSetMap[ key ] = data;
    }

    //GenerateTiles
    UInt32 TileManager::GenerateTiles( const String& fileName, const String& setID, const Point2D& tileSize, const Point2D& tileCount, const UInt32& totalTiles )
    {
        // Make sure the image is not already in the tile manager
        TileSetMap::const_iterator iter = mTileSetMap.find( setID );
        if ( iter == mTileSetMap.end() )
        {
            // Generate the display list
            // NOTE: The tile created at index 0 is empty, and is essentially a 100% transparent tile.
            TileSetData setData;
            setData.mTileCount = totalTiles + 1;
            setData.mDisplayListBase = glGenLists( setData.mTileCount );
            setData.mImageFileName = fileName;
            if ( setData.mDisplayListBase == 0 )
                return 0;

            // Load the image in the texture manager:
            TextureManager::GetSingleton().LoadImage( fileName, GL_NEAREST, GL_NEAREST, false, true );
            TextureItem* textureItem = TextureManager::GetSingleton().GetTextureItemPtr( fileName );
            if ( !textureItem )
                return 0;

            AddTileSet( setID, setData );

            // Generate tile 0:
            glNewList( setData.mDisplayListBase, GL_COMPILE );
            glTranslatef( tileSize.x, 0, 0 );
            glEndList();

            // Ratios for the texture coordinates
            Real texCoordMaxX = ( tileSize.x * tileCount.x ) / Real( textureItem->GetWidth() );
            Real texCoordMaxY = ( tileSize.y * tileCount.y ) / Real( textureItem->GetHeight() );
            Real texCoordXDiff = texCoordMaxX / Real( tileCount.x );
            Real texCoordYDiff = texCoordMaxY / Real( tileCount.y );

            // Generate the remaining tiles
            UInt32 count = 1;
            Real texCoordY = 0;
            for ( Int y = 0; y < tileCount.y; y++ )
            {
                Real texCoordX = 0;
                for ( Int x = 0; x < tileCount.x; x++ )
                {
                    glNewList( setData.mDisplayListBase + count, GL_COMPILE );
                    glBegin( GL_QUADS );
                    {
                        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

                        //glTexCoord2f( x * texCoordXDiff, y * texCoordYDiff );
                        glTexCoord2f( texCoordX, texCoordY );
                        glVertex3f( 0.0f, 0.0f, 0.0f );

                        //glTexCoord2f( x * texCoordXDiff, ( y + 1 ) * texCoordYDiff );
                        glTexCoord2f( texCoordX, texCoordY + texCoordYDiff );
                        glVertex3f( 0.0f, tileSize.y, 0.0f );

                        //glTexCoord2f( ( x + 1 ) * texCoordXDiff, ( y + 1 ) * texCoordYDiff );
                        glTexCoord2f( texCoordX + texCoordXDiff, texCoordY + texCoordYDiff );
                        glVertex3f( tileSize.x, tileSize.y, 0.0f );

                        //glTexCoord2f( ( x + 1 ) * texCoordXDiff, y * texCoordYDiff );
                        glTexCoord2f( texCoordX + texCoordXDiff, texCoordY );
                        glVertex3f( tileSize.x, 0.0f, 0.0f );
                    }
                    glEnd();
                    glTranslatef( tileSize.x, 0, 0 );
                    glEndList();
                    ++count;
                    texCoordX += texCoordXDiff;
                }
                texCoordY += texCoordYDiff;
            }

            // Return the number of generated tiles
            return count - 1;
        }
        return 0;
    }

    //GenerateTiles
    UInt32 TileManager::GenerateTiles( const String& fileName, const String& setID, const std::vector< Point2D >& tilePositions, const std::vector< Point2D >& tileSizes )
    {
        // Make sure the image is not already in the tile manager
        TileSetMap::const_iterator iter = mTileSetMap.find( setID );
        if ( iter == mTileSetMap.end() )
        {
            // The number of tiles is the minimum of the number of positions
            // and sizes.
            UInt32 numTiles = Math::IMin( tilePositions.size(), tileSizes.size() );

            // Generate the display list
            // NOTE: The tile created at index 0 is empty, and is essentially a 100% transparent tile.
            TileSetData setData;
            setData.mTileCount = numTiles;
            setData.mDisplayListBase = glGenLists( setData.mTileCount );
            setData.mImageFileName = fileName;
            if ( setData.mDisplayListBase == 0 )
                return 0;

            // Load the image in the texture manager:
            TextureManager::GetSingleton().LoadImage( fileName, GL_NEAREST, GL_NEAREST, false, true );
            TextureItem* textureItem = TextureManager::GetSingleton().GetTextureItemPtr( fileName );
            if ( !textureItem )
                return 0;

            AddTileSet( setID, setData );

            // Unlike a map laid out in a grid, where tile 0 is empty, ALL tiles
            // in this version associate to an area of the source image.  If a
            // blank tile is desired, then the source should be designed to
            // provide one.

            // Generate the tiles:
            UInt32 count = 0;
            while ( count < numTiles )
            {
                // The given position and size should be in pixels.  These need
                // to be converted to normalized coordinates
                Point2D tilePosition = tilePositions[ count ];
                Point2D tileSize = tileSizes[ count ];
                Real posX   = tilePosition.x / textureItem->GetOriginalWidth();
                Real posY   = tilePosition.y / textureItem->GetOriginalHeight();
                Real sizeX  = tileSize.x / textureItem->GetOriginalWidth();
                Real sizeY  = tileSize.y / textureItem->GetOriginalHeight();

                glNewList( setData.mDisplayListBase + count, GL_COMPILE );
                glBegin( GL_QUADS );
                {
                    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

                    glTexCoord2f( posX, posY );
                    glVertex3f( 0.0f, 0.0f, 0.0f );

                    glTexCoord2f( posX, posY + sizeY );
                    glVertex3f( 0.0f, tileSize.y, 0.0f );

                    glTexCoord2f( posX + sizeX, posY + sizeY );
                    glVertex3f( tileSize.x, tileSize.y, 0.0f );

                    glTexCoord2f( posX + sizeX, posY );
                    glVertex3f( tileSize.x, 0.0f, 0.0f );
                }
                glEnd();
                glTranslatef( tileSize.x, 0, 0 );
                glEndList();

                ++count;
            }

            // Return the number of generated tiles
            return count - 1;
        }

        return 0;
    }

    //Remove
    bool TileManager::Remove( const String& name )
    {
        // Make sure the image exists in the manager
        TileSetMap::const_iterator iter = mTileSetMap.find( name );
        if ( iter != mTileSetMap.end() )
        {
            // Remove the image from the texture manager:
            if ( TextureManager::GetSingleton().RemoveImage( name ) )
            {
                // Remove the display list for this image
                glDeleteLists( iter->second.mDisplayListBase, iter->second.mTileCount );

                // Delete the item from the map
                mTileSetMap.erase( name );
            }
        }
        return true;
    }

    //GetTileSetBase
    UInt32 TileManager::GetTileSetBase( const String& name )
    {
        TileSetMap::const_iterator iter = mTileSetMap.find( name );
        if ( iter != mTileSetMap.end() )
        {
            return iter->second.mDisplayListBase;
        }
        return 0;
    }

} // namespace PGE
