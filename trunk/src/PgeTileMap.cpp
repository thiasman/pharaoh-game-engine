
/*! $
 *  @file
 *  @author
 *  @date
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

#include "cmd/LogFileManager.h"
using cmd::LogFileManager;
using cmd::LogFileSection;

//#include "PgeLogFileManager.h"
#include "cmd/StringUtil.h"
using cmd::StringUtil;

namespace PGE
{
    TileMap::TileMap()
        : mIdentifier( "" ), mDepth( 0 )
    {
        //ctor
    }

    TileMap::TileMap( const Point2Df& tileSize )
        : mIdentifier( "" ), mDepth( 0 )
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

        mVertices.assign( src.mVertices.begin(), src.mVertices.end() );
        mColors.assign( src.mColors.begin(), src.mColors.end() );
        mTextureCoords.assign( src.mTextureCoords.begin(), src.mTextureCoords.end() );
        mTileMap.assign( src.mTileMap.begin(), src.mTileMap.end() );

        return *this;
    }

    //operator<-----------------------------------------------------------------
    bool TileMap::operator<( const TileMap& src ) const
    {
        return mDepth < src.mDepth;
    }

    //operato><-----------------------------------------------------------------
    bool TileMap::operator>( const TileMap& src ) const
    {
        return mDepth > src.mDepth;
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

        // Allocate the array for the tiles:
        mTileMap.resize( mTileCount.x * mTileCount.y );

        Colorf mColorGrid[] = { Colorf( 1.0, 0.0, 0.0, 1.0 ), Colorf( 0.0, 1.0, 0.0, 1.0 ),
                                Colorf( 0.0, 0.0, 1.0, 1.0 ), Colorf( 1.0, 1.0, 1.0, 1.0 ) };
        Real hColorDiff = 1.0 / Real( mTileCount.x - 1 );
        Real vColorDiff = 1.0 / Real( mTileCount.y - 1 );
        Colorf leftColor, rightColor;
        mColors.clear();


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
                    //mColors.push_back( color );
                    //Int colorIndex = mColors.size() - 1;

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
    void TileMap::ReadMap( TiXmlNode* mapNode )
    {
//        LogFileManager& lfm = LogFileManager::GetSingleton();
//        LogFileSection sect( lfm.GetDefaultLog(), "TileMap::ReadMap(...)" );

        if ( !mapNode )
            return;

        mDepth       = StringUtil::ToInt( XmlArchiveFile::GetItemValue( mapNode->FirstChild( "index" ) ) );
        mIdentifier  = XmlArchiveFile::GetItemValue( mapNode->FirstChild( "identifier" ) );
        mTileCount.x = StringUtil::ToInt( XmlArchiveFile::GetItemValue( mapNode->FirstChild( "width" ) ) );
        mTileCount.y = StringUtil::ToInt( XmlArchiveFile::GetItemValue( mapNode->FirstChild( "height" ) ) );

        mMapSize = mTileSize * mTileCount;

        // Allocate the array for the tiles:
        mTileMap.resize( mTileCount.x * mTileCount.y );

        //lfm << "index = " << index << ", id = " << id << ", width = " << width << ", height = " << height << std::endl;

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

    //SetDepth------------------------------------------------------------------
    void TileMap::SetDepth( Real depth )
    {
        mDepth = depth;
    }

    //GetDepth------------------------------------------------------------------
    Real TileMap::GetDepth() const
    {
        return mDepth;
    }

    //RenderTileSpan------------------------------------------------------------
    void TileMap::RenderTileSpan( TileArray::const_iterator& tileIter, const UInt32& displayListBase, UInt32 count ) const
    {
//        LogFileManager& lfm = LogFileManager::GetSingleton();
//        LogFileSection sect( lfm.GetDefaultLog(), "TileMap::Render(...)" );

        Int curTile = count;
        while ( tileIter != mTileMap.end() && curTile >= 0 )
        {
//            lfm << "curTile = " << ( count - curTile ) << ", index = " << tileIter->tileIndex << std::endl;
            glCallList( displayListBase + tileIter->tileIndex );

            // Increment the tile iterator and decrement the count
            ++tileIter;
            --curTile;
        }
    }

    //Render--------------------------------------------------------------------
    void TileMap::Render( UInt32 displayListBase, const Point2Df& offset, const Viewport& viewport ) const
    {
        LogFileManager& lfm = LogFileManager::getInstance();
        LogFileSection sect( lfm.GetDefaultLog(), "TileMap::Render(...)" );

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
lfm << "start tile = " << startTile << ", end tile = " << endTile << std::endl;

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
//lfm << "offset = " << offsetInt << std::endl;
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


    ////////////////////////////////////////////////////////////////////////////
    // TileMapCollection
    ////////////////////////////////////////////////////////////////////////////

    //Constructor---------------------------------------------------------------
    TileMapCollection::TileMapCollection()
        : mPrimaryMap( 0 )
    {
    }

    //Destructor----------------------------------------------------------------
    TileMapCollection::~TileMapCollection()
    {
        delete mPrimaryMap;
    }

    //AddTileMap----------------------------------------------------------------
    void TileMapCollection::AddTileMap( TileMap& map )
    {
        // Add the map to the set:
        mTileMaps.insert( map );

        if ( !mPrimaryMap )
        {
            mPrimaryMap = new TileMap();
            *mPrimaryMap = map;
        }
        else if ( map.mDepth == 0 && mPrimaryMap->mDepth != 0 )
            *mPrimaryMap = map;
    }

    //GetTileMap----------------------------------------------------------------
    bool TileMapCollection::GetTileMap( Real depth, TileMap* map ) const
    {
        TileMapSet::const_iterator mapIter = mTileMaps.begin();
        for ( mapIter; mapIter != mTileMaps.end(); mapIter++ )
        {
            if ( mapIter->mDepth == depth )
            {
                *map = *mapIter;
                return true;
            }
        }
        return false;
    }

    //Render--------------------------------------------------------------------
    void TileMapCollection::Render( Point2Df& primaryOffset, const Viewport& viewport ) const
    {
        LogFileManager& lfm = LogFileManager::getInstance();
        LogFileSection sect( lfm.GetDefaultLog(), "TileMapCollection::Render(...)" );

        // If there is no map set, we can either assert, or we can ignore this
        // and pretend the developer had other plans.  We'll give the developer
        // the benefit of the doubt, and just return from this method without
        // doing anything...
        if ( mPrimaryMap == 0 )
            return;
        //assert( mPrimaryMap != 0 );

        if ( mIsTextured )
            glEnable( GL_TEXTURE_2D );

        // Get the display list base for this tileset:
        UInt32 displayListBase = TileManager::GetSingleton().GetTileSetBase( mIdentifier );

        // Go over the tile maps and calculate their offsets, then render the map.
        TileMapSet::const_iterator mapIter = mTileMaps.begin();
        Point2D viewSize = viewport.GetSize();
        primaryOffset.x = Math::Clamp( primaryOffset.x, viewSize.x - mPrimaryMap->mMapSize.x, 0 );
        primaryOffset.y = Math::Clamp( primaryOffset.y, viewSize.y - mPrimaryMap->mMapSize.y, 0 );
        for ( mapIter; mapIter != mTileMaps.end(); mapIter++ )
        {
            // Calculate the ratio between the current map and the primary map
            Real ratioX = ( mPrimaryMap->mMapSize.x - viewSize.x ) / ( mapIter->mMapSize.x - viewSize.x );
            Real ratioY = ( mPrimaryMap->mMapSize.y - viewSize.y ) / ( mapIter->mMapSize.y - viewSize.y );

            // Calculate the offset of the current map using the offset for the
            // primary map and the ratios
            Point2Df curOffset( primaryOffset.x / ratioX, primaryOffset.y / ratioY );
            curOffset.x = Math::Clamp( curOffset.x, viewSize.x - mapIter->mMapSize.x, 0 );
            curOffset.y = Math::Clamp( curOffset.y, viewSize.y - mapIter->mMapSize.y, 0 );

lfm << "map offset = " << curOffset << ", primary offset = " << primaryOffset << ", map size = " << mPrimaryMap->mMapSize << ", viewSize = " << viewSize << ", ratioX = " << ratioX << ", ratioY = " << ratioY << std::endl;
//curOffset = Point2Df( 0, 0 );
            mapIter->Render( displayListBase, curOffset, viewport );
        }

        if ( mIsTextured )
            glDisable( GL_TEXTURE_2D );
    }

    //ReadTileset
    void TileMapCollection::ReadTileset( TiXmlNode* tilesetNode, const String& baseDir )
    {
//        LogFileManager& lfm = LogFileManager::GetSingleton();
//        LogFileSection sect( lfm.GetDefaultLog(), "TileMap::ReadTileset(...)" );

        if ( !tilesetNode )
            return;

        // Read some configuration settings regarding the tileset

        // Index and ID:
        mIndex = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "index" ) ) );
        mIdentifier = XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "identifier" ) );

        // Tile information
        mTileSize.x = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "tileWidth" ) ) );
        mTileSize.y = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "tileHeight" ) ) );
        mImageFile = baseDir + "/" + XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "tileBitmap" ) );
        //mTileCount.x = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "tileSetBitmapWidth" ) ) );
        //mTileCount.y = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "tileSetBitmapHeight" ) ) );
        mTileCount.x = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "horizontalTileCount" ) ) );
        mTileCount.y = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "verticalTileCount" ) ) );
        int overlap = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "overlap" ) ) );
        int tileCount = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "tileCount" ) ) );

        // Create the source tiles:
        mIsTextured = ArchiveManager::GetSingleton().Exists( mImageFile );
        String tileName = ( mIsTextured ) ? mImageFile : mIdentifier;
        //String tileID = mIdentifier;
        TileManager::GetSingleton().GenerateTiles( tileName, mIdentifier, mTileSize, mTileCount, tileCount );

        // Sequence data
        int seqCount = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "sequenceCount" ) ) );

        // Map data
        int mapCount = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "mapCount" ) ) );
        TiXmlNode* maplistNode = tilesetNode->FirstChild( "mapList" );
        if ( maplistNode )
        {
            TiXmlNode* mapNode = maplistNode->FirstChild( "map" );
            while ( mapNode )
            {
                TileMap tileMap( mTileSize );
                tileMap.ReadMap( mapNode );
                AddTileMap( tileMap );
                mapNode = mapNode->NextSibling( "map" );
            }
        }
    }

    void TileMapCollection::GenerateDefaultTileset( const String& textureName, const Point2Df& tileSize, const Point2D& tileCount )
    {
        // Check if the tiles are textured.  This is a naive test, and
        // isn't foolproof.
        mImageFile  = textureName;
        mIsTextured = ArchiveManager::GetSingleton().Exists( textureName );

        mTileSize   = tileSize;
        mTileCount  = tileCount;
        mIndex      = 0;
        mIdentifier = "default";

        // Load the texture
        if ( mIsTextured )
            TextureManager::GetSingleton().LoadImage( mImageFile, GL_NEAREST, GL_NEAREST, false, true );

/*
        // Create the source tiles:
        //String tileID = ( mIsTextured ) ? mImageFile : mIdentifier;
        String tileID = mIdentifier;
        TileManager::GetSingleton().GenerateTiles( tileID, mTileSize, mTileCount, mTileCount.x * mTileCount.y );

        // Map data
        TileMap tileMap( mTileSize );
        tileMap.GenerateDefaultMap( mTileCount );
        AddTileMap( tileMap );
*/

        // Generate the map:
        TileMap tileMap;
        tileMap.GenerateMap( mIdentifier, PGE::Point2Df( 32, 32 ), PGE::Point2D( 20, 20 ) );
        tileMap.SetDepth( 0 );
        AddTileMap( tileMap );
    }

} // namespace PGE
