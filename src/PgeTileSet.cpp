
/*! $Id$
 *  @file   PgeTileSet.cpp
 *  @author Chad M. Draper
 *  @date   January 27, 2009
 *
 */

#include "PgeTileSet.h"
#include "PgeTextureManager.h"
#include "PgeMath.h"
#include "PgeArchiveFile.h"
#include "PgeArchiveManager.h"
#include "PgeXmlArchiveFile.h"


namespace PGE
{

    ////////////////////////////////////////////////////////////////////////////
    // class TileSet::Sequence
    ////////////////////////////////////////////////////////////////////////////

    //Constructor
    TileSet::Sequence::Sequence( Real fps )
        : frameRate( fps )
    {
        SetFrameRate( frameRate );
    }

    //operator=
    TileSet::Sequence& TileSet::Sequence::operator=( const TileSet::Sequence& src )
    {
        frameRate       = src.frameRate;
        secondsPerFrame = src.secondsPerFrame;
        curFrame        = src.curFrame;
        frameTime       = src.frameTime;
        index           = src.index;

        mSequence.assign( src.mSequence.begin(), src.mSequence.end() );
        return *this;
    }

    //SetFrameRate
    void TileSet::Sequence::SetFrameRate( Real fps )
    {
        frameRate   = frameRate;
        secondsPerFrame = 1.0 / fps;
    }

    //GetFrameRate
    Real TileSet::Sequence::GetFrameRate() const
    {
        return frameRate;
    }

    //ReadSequence
    void TileSet::Sequence::ReadSequence( TiXmlNode* seqNode )
    {
        index   = StringUtil::ToInt( XmlArchiveFile::GetItemValue( seqNode->FirstChild( "index" ) ) );
        mSequence.clear();

        // Read the frame data:
        TiXmlNode* frameListNode = seqNode->FirstChild( "frameList" );
        if ( frameListNode )
        {
            TiXmlNode* frameNode = frameListNode->FirstChild( "frame" );
            while ( frameNode )
            {
                FrameData frame;
                frame.delay     = StringUtil::ToInt( XmlArchiveFile::GetItemValue( frameNode->FirstChild( "frameDelay" ) ) );
                frame.tileNumber = StringUtil::ToInt( XmlArchiveFile::GetItemValue( frameNode->FirstChild( "tileNumber" ) ) );
                mSequence.push_back( frame );

                frameNode = frameNode->NextSibling( "frame" );
            }
        }

        if ( mSequence.size() > 0 )
        {
            curFrame = 0;
            frameTime = 0;
        }
    }

    //Prepare
    void TileSet::Sequence::Prepare( Real32 elapsedMS )
    {
        frameTime += elapsedMS;
        Int frameOffset = frameTime / secondsPerFrame;
        frameTime = Math::Mod( frameTime, secondsPerFrame );
        curFrame  = Math::IModRange( curFrame + frameOffset, 0, mSequence.size() );
        //curFrame = Math::ModRange( curFrame + 1, 0, mSequence.size() );
    }

    //Render
    void TileSet::Sequence::Render( UInt32 displayListBase )
    {
        assert( curFrame >= 0 && curFrame < mSequence.size() );

        // Index of the tile used for the current frame:
        Int frameTileIndex = mSequence[ curFrame ].tileNumber;

        // Render the tile:
        glCallList( displayListBase + frameTileIndex );
    }


    ////////////////////////////////////////////////////////////////////////////
    // class TileSet
    ////////////////////////////////////////////////////////////////////////////

    //Constructor
    TileSet::TileSet()
        : mIdentifier( "" ),
          mImageName( "" ),
          mTileCount( 0 ),
          mOverlap( 0 ),
          mDisplayListBase( 0 )
    {
    }

    //Constructor
    TileSet::TileSet( TiXmlNode* tilesetNode, const String& baseDir, UInt32 mapIndex )
        : mIdentifier( "" ),
          mImageName( "" ),
          mTileCount( 0 ),
          mOverlap( 0 ),
          mDisplayListBase( 0 )
    {
        ReadTileSet( tilesetNode, baseDir, mapIndex );
    }

    //Destructor
    TileSet::~TileSet()
    {
        Release();
    }

    //_generateTiles
    bool TileSet::_generateTiles()
    {
        // Make sure the texture is loaded
        TextureManager::GetSingleton().LoadImage( mImageName, GL_NEAREST, GL_NEAREST, false, true );
        TextureItem* textureItem = TextureManager::GetSingleton().GetTextureItemPtr( mImageName );
        if ( !textureItem )
            return false;

        // Generate the display list
        // NOTE: The tile created at index 0 is empty, and is essentially a 100% transparent tile.
        mDisplayListBase = glGenLists( mTileCount );
        if ( mDisplayListBase == 0 )
            return false;

        // Generate tile 0:
        glNewList( mDisplayListBase, GL_COMPILE );
        glTranslatef( mTileSize.x, 0, 0 );
        glEndList();

        // Ratios for the texture coordinates
        Real texCoordMaxX = ( mTileSize.x * mGridSize.x ) / Real( textureItem->GetWidth() );
        Real texCoordMaxY = ( mTileSize.y * mGridSize.y ) / Real( textureItem->GetHeight() );
        Real texCoordXDiff = texCoordMaxX / Real( mGridSize.x );
        Real texCoordYDiff = texCoordMaxY / Real( mGridSize.y );

        // Generate the remaining tiles
        UInt32 count = 1;
        Real texCoordY = 0;
        for ( Int y = 0; y < mGridSize.y; y++ )
        {
            Real texCoordX = 0;
            for ( Int x = 0; x < mGridSize.x; x++ )
            {
                glNewList( mDisplayListBase + count, GL_COMPILE );
                glBegin( GL_QUADS );
                {
                    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

                    //glTexCoord2f( x * texCoordXDiff, y * texCoordYDiff );
                    glTexCoord2f( texCoordX, texCoordY );
                    glVertex3f( 0.0f, 0.0f, 0.0f );

                    //glTexCoord2f( x * texCoordXDiff, ( y + 1 ) * texCoordYDiff );
                    glTexCoord2f( texCoordX, texCoordY + texCoordYDiff );
                    glVertex3f( 0.0f, mTileSize.y, 0.0f );

                    //glTexCoord2f( ( x + 1 ) * texCoordXDiff, ( y + 1 ) * texCoordYDiff );
                    glTexCoord2f( texCoordX + texCoordXDiff, texCoordY + texCoordYDiff );
                    glVertex3f( mTileSize.x, mTileSize.y, 0.0f );

                    //glTexCoord2f( ( x + 1 ) * texCoordXDiff, y * texCoordYDiff );
                    glTexCoord2f( texCoordX + texCoordXDiff, texCoordY );
                    glVertex3f( mTileSize.x, 0.0f, 0.0f );
                }
                glEnd();
                glTranslatef( mTileSize.x, 0, 0 );
                glEndList();
                ++count;
                texCoordX += texCoordXDiff;
            }
            texCoordY += texCoordYDiff;
        }

        return true;
    }

    //_readTileMap
    bool TileSet::_readTileMap( TiXmlNode* mapNode )
    {
        // Get the map dimensions
        mTileMapSize.x = StringUtil::ToInt( XmlArchiveFile::GetItemValue( mapNode->FirstChild( "width" ) ) );
        mTileMapSize.y = StringUtil::ToInt( XmlArchiveFile::GetItemValue( mapNode->FirstChild( "height" ) ) );

        // Set the map size:
        mTileMap.resize( mTileMapSize.x * mTileMapSize.y );

        TiXmlNode* cellNode = mapNode->FirstChild( "cellList" );
        if ( cellNode )
        {
            int curTile = 0;
            cellNode = cellNode->FirstChild( "cell" );
            while ( cellNode )
            {
                TileMapItem tile;
                tile.tileIndex  = StringUtil::ToInt( XmlArchiveFile::GetItemValue( cellNode->FirstChild( "tileNumber" ) ) );
                tile.boundsCode = StringUtil::ToInt( XmlArchiveFile::GetItemValue( cellNode->FirstChild( "bounds" ) ) );
                tile.mapCode    = StringUtil::ToInt( XmlArchiveFile::GetItemValue( cellNode->FirstChild( "mapCode" ) ) );
                mTileMap[ curTile++ ] = tile;

                cellNode = cellNode->NextSibling( "cell" );
            }
        }

        return true;
    }

    //_readSequence
    bool TileSet::_readSequence( TiXmlNode* seqNode )
    {
        // Read the sequence:
        Sequence seq;
        seq.ReadSequence( seqNode );

        // Make sure the sequence array is big enough:
        if ( seq.index < mSequences.size() )
            mSequences[ seq.index ] = seq;

        return true;
    }

    void TileSet::_renderTileSpan( TileMap::const_iterator& tileIter, const UInt32& displayListBase, UInt32 count ) const
    {
        Int curTile = count;
        while ( tileIter != mTileMap.end() && curTile >= 0 )
        {
            if ( tileIter->tileIndex < 0 )
            {
                // Negative values indicate a sequence...
                Int seqIndex = Math::Abs( tileIter->tileIndex );
                if ( seqIndex < mSequences.size() )
                {
                    mSequences[ seqIndex ].Render( displayListBase );
                }
            }
            else
                glCallList( displayListBase + tileIter->tileIndex );

            // Increment the tile iterator and decrement the count
            ++tileIter;
            --curTile;
        }
    }

    //operator=
    TileSet& TileSet::operator=( const TileSet& src )
    {
        mIndex      = src.mIndex;
        mIdentifier = src.mIdentifier;
        mTileSize   = src.mTileSize;
        mImageName  = src.mImageName;
        mImageSize  = src.mImageSize;
        mGridSize   = src.mGridSize;
        mOverlap    = src.mOverlap;
        mTileCount  = src.mTileCount;
        mDisplayListBase = src.mDisplayListBase;

        mTileMap.assign( src.mTileMap.begin(), src.mTileMap.end() );
        mTileMapSize = src.mTileMapSize;

        mSequences.assign( src.mSequences.begin(), src.mSequences.end() );

        return *this;
    }

    //operator<
    bool TileSet::operator<( const TileSet& src ) const
    {
        return mIndex < src.mIndex;
    }

    //operator>
    bool TileSet::operator>( const TileSet& src ) const
    {
        return mIndex > src.mIndex;
    }

    //GetMapSize
    Point2D TileSet::GetMapSize() const
    {
        return mTileMapSize * mTileSize;
    }

    //GetTileSize
    const Point2D& TileSet::GetTileSize() const
    {
        return mTileSize;
    }

    //GetMapGridSize
    const Point2D& TileSet::GetMapGridSize() const
    {
        return mTileMapSize;
    }

    //Read a tileset
    bool TileSet::ReadTileSet( TiXmlNode* tilesetNode, const String& baseDir, UInt32 mapIndex )
    {
        if ( !tilesetNode )
            return false;

        // Read some configuration settings regarding the tileset

        // Index and ID:
        mIndex      = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "index" ) ) );
        mIdentifier = XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "identifier" ) );

        // Tile information
        mTileSize.x = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "tileWidth" ) ) );
        mTileSize.y = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "tileHeight" ) ) );
        mImageName  = baseDir + "/" + XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "tileBitmap" ) );
        mImageName  = StringUtil::FixPath( mImageName );

        mGridSize.x = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "horizontalTileCount" ) ) );
        mGridSize.y = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "verticalTileCount" ) ) );
        mOverlap    = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "overlap" ) ) );
        mTileCount  = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "tileCount" ) ) );

        // Create the source tiles:
        bool isTextured = ArchiveManager::GetSingleton().Exists( mImageName );
        if ( isTextured )
        {
            // Use the path to the texture as the tileset name.  This will make it
            // more unique than just the ID from the xml file.
            mIdentifier = mImageName;
        }
        //String tileName = mIdentifier;
        if ( !_generateTiles() )
            return false;

        // Sequence data
        int seqCount = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "sequenceCount" ) ) );
        mSequences.resize( seqCount + 1 );
        TiXmlNode* seqlistNode = tilesetNode->FirstChild( "sequenceList" );
        if ( seqlistNode )
        {
            TiXmlNode* seqNode = seqlistNode->FirstChild( "sequence" );
            int curSeq = 0;
            while ( seqNode )
            {
                _readSequence( seqNode );

                seqNode = seqlistNode->NextSibling( "sequence" );
            }
        }

        // Map data
        int mapCount = StringUtil::ToInt( XmlArchiveFile::GetItemValue( tilesetNode->FirstChild( "mapCount" ) ) );
        TiXmlNode* maplistNode = tilesetNode->FirstChild( "mapList" );
        if ( maplistNode && mapIndex < mapCount )
        {
            TiXmlNode* mapNode = maplistNode->FirstChild( "map" );
            int curMap = 0;
            while ( mapNode && curMap < mapIndex )
            {
                mapNode = mapNode->NextSibling( "map" );
            }

            if ( mapNode && curMap == mapIndex )
            {
                _readTileMap( mapNode );
            }
        }

        return true;
    }

    //Release
    void TileSet::Release()
    {
    }

    //Update
    void TileSet::Update( Real32 elapsedMS )
    {
        // Prepare the sequences
        SequenceArray::iterator iter = mSequences.begin();
        for ( iter; iter != mSequences.end(); iter++ )
        {
            iter->Prepare( elapsedMS );
        }
    }

    //Render
    void TileSet::Render( const Point2Df& offset, const Viewport& viewport ) const
    {
        // Check that a texture image has been loaded, and then bind the texture
        // to the current context
        TextureItem* textureItem = TextureManager::GetSingleton().GetTextureItemPtr( mImageName );
        if ( textureItem )
        {
            UInt32 texID = textureItem->GetID();
            glBindTexture( GL_TEXTURE_2D, texID );
        }

        Point2D displayTiles( Math::Ceil( viewport.GetSize().x / mTileSize.x ),
                              Math::Ceil( viewport.GetSize().y / mTileSize.y ) );
        displayTiles.x = Math::Clamp( displayTiles.x, 0, mTileMapSize.x );
        displayTiles.y = Math::Clamp( displayTiles.y, 0, mTileMapSize.y );

        // Find the first tile to render:
        Point2D startTile = -offset / mTileSize;
        startTile.x = Math::Clamp( startTile.x, 0, mTileMapSize.x - displayTiles.x );
        startTile.y = Math::Clamp( startTile.y, 0, mTileMapSize.y - displayTiles.y );
        Point2D endTile;
        endTile.x = Math::Ceil( ( viewport.GetSize().x - offset.x ) / mTileSize.x );
        endTile.y = Math::Ceil( ( viewport.GetSize().y - offset.y ) / mTileSize.y );
        endTile.x = Math::Clamp( endTile.x, 0, mTileMapSize.x - 1 );
        endTile.y = Math::Clamp( endTile.y, 0, mTileMapSize.y - 1 );

        // Iterate over the tile rows and render spans of tiles
        UInt32 spanCount = ( endTile.x - startTile.x );
        Point2Df rowPosition = offset;
        Point2Df mapSize = mTileMapSize * mTileSize;
        if ( mapSize.x < viewport.GetSize().x )
            rowPosition.x = ( viewport.GetSize().x - mapSize.x ) / 2.0;
        if ( mapSize.y < viewport.GetSize().y )
            rowPosition.y = ( viewport.GetSize().y - mapSize.y ) / 2.0;

        UInt32 startIndex = startTile.y * mTileMapSize.x + startTile.x;
        glPushMatrix();
        Point2D offsetInt( rowPosition.x + startTile.x * mTileSize.x, rowPosition.y + startTile.y * mTileSize.y );
        glTranslatef( offsetInt.x, offsetInt.y, 0 );
        for ( int tileY = startTile.y; tileY <= endTile.y; tileY++ )
        {
            // Get the iterator:
            TileMap::const_iterator tileIter = mTileMap.begin() + startIndex;

            // Render the tile span:
            glPushMatrix();
                _renderTileSpan( tileIter, mDisplayListBase, spanCount );
            glPopMatrix();
            glTranslatef( 0, mTileSize.y, 0 );

            startIndex += mTileMapSize.x;
        }
        glPopMatrix();
    }

} // namespace PGE
