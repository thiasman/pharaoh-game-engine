
/*! $Id$
 *  @file   PgeTileMap.h
 *  @author Chad M. Draper
 *  @date   August 13, 2008
 *  @brief  Maintains a set of tiles, which form the grid, or tile map.
 *
 */

#ifndef PGETILEMAP_H
#define PGETILEMAP_H

#include <vector>
#include <set>
#include <map>
#include "PgeTypes.h"
#include "PgePoint2D.h"
#include "PgePoint3D.h"
#include "PgeColor.h"
#include "PgeSharedPtr.h"
#include "PgeSingleton.h"

class TiXmlNode;

namespace PGE
{
    class Viewport;

    /** @class TileSequence
        A sequence is a group of tiles that are displayed as an animated sprite.
        TileStudio apparently does not specify a frame rate for the speed of
        displaying the sequence, so this class will allow a user-defined speed,
        and have a default rate of 30 frames-per-second.

        @note
            In the data file, sequences will be defined with a positive index,
            but when being referenced in the map, the index (tileNumber) will be
            negative.  For instance, the first sequence (index=1) will be placed
            in the map with tileNumber=-1.  When a negative tile is encountered,
            it is assumed to be a sequence, so the absolute value is used to
            index the sequence.
    */
    class _PgeExport TileSequence
    {
    protected:
        struct FrameData
        {
            Int     tileIndex;              ///< Index of the tile used for the frame
            UInt32  boundsCode;             ///< Boundary code for the sequence
            Int     frameDelay;             ///< Indicates delay in animation speed.  Not sure how useful this is...
        };

        String      mName;                  ///< Name of the sprite
        Real        mFrameRate;             ///< Animation speed of the sequence
        Int         mCurrentFrame;          ///< Index of the current frame
        typedef std::vector< FrameData > FrameType;
        FrameType   mSequence;              ///< Collection of frames that make up the sequence

    public:
        /** Constructor */
        TileSequence( Real frameRate = 30.0 );
        /** Destructor */
        ~TileSequence();

        /** Assignment operator */
        TileSequence& operator=( const TileSequence& src );

        /** Read a sequence from a tile map file */
        void ReadSequence( TiXmlNode* mapNode, const String& setID, UInt32 setIndex );

        /** Prepare the sequence for rendering

            This takes an elapsed time (milliseconds) parameter, which is used
            to update the current frame in the sequence, based on the frame rate.
        */
        void Prepare( Real elapsedMS );

        /** Render the current frame of the sequence.

            Sequences should be rendered as part of a tile map.  As such,
            the transformation should be ready for the sequence to simply be
            rendered to the display.

            @remarks
                This simply renders the current frame in the sequence.  To
                update the frame based on elapsed time, <pre>Prepare</pre>
                must be called before rendering.
        */
        void Render();
    };

    /** @class TileMap
        Maintains tiles in a grid, forming the tile map.
    */
    class _PgeExport TileMap
    {
    protected:
        friend class TileMapGroup;
        friend class TileMapScene;

        /** @struct Tile
            Store values pertaining to the tile.
        */
        struct Tile
        {
            SInt32  tileIndex;              ///< Index to the tile in the display list
            UInt32  boundsCode;             ///< Code defining boundary of the cell
            UInt32  mapCode;                ///< Indicates special tiles in the map
            //UInt32  vertexIndices[ 4 ];     ///< Indices for the posiions of the tile corners
            //UInt32  colorIndices[ 4 ];      ///< Indices for the colors of the tile corners
            //UInt32  textureIndices[ 4 ];    ///< Indices for the texture coordinates of the tile corners
        };

        /** @typedef TileArray
            An array of tiles
        */
        typedef std::vector< Tile > TileArray;
        std::vector< Tile >         mTileMap;           ///< Indices for the tiles
        String                      mIdentifier;        ///< Name of the tile set used for this map
        String                      mTileSetID;         ///< Name of the tile set

        //UInt32                      mTileDispList;      ///< Display list for the tiles

        Point2Df                    mTileSize;          ///< Dimensions of the tiles
        Point2D                     mTileCount;         ///< Number of tiles in the map grid
        Point2Df                    mMapSize;           ///< Dimensions of the map (equal to mTileSize * mTileCount)
        UInt32                      mDepth;             ///< Depth of the tilemap (indicates the render order)
        UInt32                      mTilesetDepth;      ///< Depth of the tileset containing this map (primary index for render order)

        /** Render a horizontal span of tiles */
        void RenderTileSpan( TileArray::const_iterator& tileIter, const UInt32& displayListBase, UInt32 count ) const;


    public:
        /** Constructor */
        TileMap();
        /** Constructor */
        TileMap( const Point2Df& tileSize );
        /** Destructor */
        virtual ~TileMap();

        /** Assignment operator */
        const TileMap& operator=( const TileMap& src );

        /** Less-than operator */
        bool operator<( const TileMap& src ) const;

        /** Greater-than operator */
        bool operator>( const TileMap& src ) const;

        /** Create the tile map grid */
        void GenerateMap( const String& setID, const Point2Df& tileSize, const Point2D& tileCount );

        /** Read a tile map from a tile map file */
        void ReadMap( TiXmlNode* mapNode, const String& setID, UInt32 setIndex );

        /** Set the size of the tiles.  The map needs to know this in order to
            perform view clipping.
        */
        void SetTileSize( const Point2Df& tileSize );

        /** The index of the containing tileset */
        void SetTilesetIndex( UInt32 index );
        /** Get the index of the containing tileset */
        UInt32 GetTilesetIndex() const;
        /** The the depth of the tile map */
        void SetDepth( Real depth );
        /** Get the depth of the tile map */
        UInt32 GetDepth() const;

        /** Render the tile map */
        //void Render() const;
        /** Render the tile map */
        void Render( UInt32 displayListBase, const Point2Df& offset, const Viewport& viewport ) const;
        void Render( const Point2Df& offset, const Viewport& viewport ) const;

    private:
    }; // class TileMap

    /** @class TileManager
        Stores tiles, making it possible to only load a give image file once.

        In theory, it is possible for a multiple tile maps to use the same set
        of tiles.  This means, they use the same image file, and the image file
        is broken into the same tiles.  Since we shouldn't need to load an image
        and divide it into tiles any more often than necessary, the manager
        allows us to store the tiles, and have them accessible to multiple maps.
        It will take an image file and, if not already loaded, load it and
        generate a display list using the tile size and count.  When a map
        renders, it should get the id for the display list from the tile
        manager by using the image name.
    */
    class _PgeExport TileManager : public Singleton< TileManager >
    {
    private:
        friend class TileMap;

        /** @struct TileSetData
            Each tile set will have a display list generated for it.  The index
            for this list needs to be associated with the file name so it may
            be accessed easily.
        */
        struct TileSetData
        {
            UInt32  mDisplayListBase;       ///< Base index of the display list
            UInt32  mTileCount;             ///< Number of tiles in the display list
            String  mImageFileName;         ///< Name of the texture file
        }; // TileSetData

        /** @typedef TileSetMap
            Associates the display list index with the image file name.
        */
        typedef std::map< String, TileSetData > TileSetMap;
        TileSetMap  mTileSetMap;

        /** Add a tile set's data */
        void AddTileSet( const String& key, const TileSetData& data );

    public:
        /** Constructor */
        TileManager();
        /** Destructor */
        ~TileManager();

        /** Override singleton retrieval to avoid link errors */
        static TileManager& GetSingleton();
        /** Override singleton pointer retrieval to avoid link errors */
        static TileManager* GetSingletonPtr();

        /** Load an image and generate the tile set for it.  This method assumes
            the tiles are laid out in a grid in the source image, and that they
            are all the same size with no spacing in between them.
        */
        UInt32 GenerateTiles( const String& fileName, const String& setID, const Point2D& tileSize, const Point2D& tileCount, const UInt32& totalTiles );

        /** Generate tiles from an image where the tile sizes and positions are
            arbitrary.  This version allows different sized tiles to be in the
            same source image, and there may be space between tiles.
        */
        UInt32 GenerateTiles( const String& fileName, const String& setID, const std::vector< Point2D >& tilePositions, const std::vector< Point2D >& tileSizes );

        /** Remove and unload a tileset and image */
        bool Remove( const String& name );

        /** Get the base of a tile set */
        UInt32 GetTileSetBase( const String& name );

    }; // class TileManager

} // namespace PGE

#endif // PGETILEMAP_H
