
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

    /** @class TileMap
        Maintains tiles in a grid, forming the tile map.
    */
    class _PgeExport TileMap
    {
    protected:
        friend class TileMapCollection;

        /** @struct Tile
            Store values pertaining to the tile.
        */
        struct Tile
        {
            UInt32  tileIndex;              ///< Index to the tile in the display list
            UInt32  boundsCode;             ///< Code defining boundary of the cell
            UInt32  mapCode;                ///< Indicates special tiles in the map
            //UInt32  vertexIndices[ 4 ];     ///< Indices for the posiions of the tile corners
            //UInt32  colorIndices[ 4 ];      ///< Indices for the colors of the tile corners
            //UInt32  textureIndices[ 4 ];    ///< Indices for the texture coordinates of the tile corners
        };

        std::vector< Point3Df >     mVertices;          ///< Vertex positions
        std::vector< Colorf >       mColors;            ///< Colors for the vertices
        std::vector< Point2Df >     mTextureCoords;     ///< Texture coordinates for the vertices

        /** @typedef TileArray
            An array of tiles
        */
        typedef std::vector< Tile > TileArray;
        std::vector< Tile >         mTileMap;           ///< Indices for the tiles
        String                      mIdentifier;        ///< Name of the tile set used for this map

        //UInt32                      mTileDispList;      ///< Display list for the tiles

        Point2Df                    mTileSize;          ///< Dimensions of the tils
        Point2D                     mTileCount;         ///< Number of tiles in the map grid
        Point2Df                    mMapSize;           ///< Dimensions of the map (equal to mTileSize * mTileCount)
        Real                        mDepth;             ///< Depth of the tilemap (indicates the render order)

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
        void ReadMap( TiXmlNode* mapNode );

        /** Set the size of the tiles.  The map needs to know this in order to
            perform view clipping.
        */
        void SetTileSize( const Point2Df& tileSize );

        /** The the depth of the tile map */
        void SetDepth( Real depth );
        /** Get the depth of the tile map */
        Real GetDepth() const;

        /** Render the tile map */
        //void Render() const;
        /** Render the tile map */
        void Render( UInt32 displayListBase, const Point2Df& offset, const Viewport& viewport ) const;

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

    /** @class TileMapCollection
        A collection of tile maps.

        The tile map collection maintains all tiles in a set.  The tiles are sorted by
        depth, with the primary map being 0.  Tiles in front of the primary map
        will have a negative depth, and those behind it are positive.

        @note
            Scrolling is done by calculating a ratio of the current level's size
            compared to the primary map.  The offset of the primary map is given
            explicitly to the render method (the minimum offset being 0, and the
            maximum offset being the map size minus the viewport size.  The
            offset of a given map can be calculated as follows:

                (For horizontal offset.  Vertical is similar.)
                <code>
                ratio = ( primary_width - viewport_width )/ ( cur_map_width - viewport_width );
                map_offset = primary_offset / ratio;
                </code>

        @note
            There is no requirement that there be a map with depth of 0.  In the
            event that there is no map at depth = 0, the first map added to the
            manager will be the primary map.

        @note
            There can be multiple tile map managers.  While it may be unusual to
            have more than 1, there is no requirement that there be only 1.
    */
    class _PgeExport TileMapCollection
    {
    private:
        typedef std::multiset< TileMap, std::less< TileMap > > TileMapSet;
        TileMapSet  mTileMaps;
        TileMap*    mPrimaryMap;

        UInt32      mIndex;         ///<
        String      mIdentifier;    ///<
        Point2Df    mTileSize;      ///< Size of the source tiles
        Point2D     mTileCount;     ///< Number of source tiles
        String      mImageFile;     ///< Name of the texture file
        bool        mIsTextured;    /**< Indicates if the tile set is textured
                                         (it usually would be...)
                                    */

    public:
        /** Constructor */
        TileMapCollection();
        /** Destructor */
        ~TileMapCollection();

        /** Add a tile map to the manager */
        void AddTileMap( TileMap& map );

        /** Get the first map at a given depth
            @param  depth           Depth of the requested map
            @param  map             TileMap found at the requested depth
            @return true if tile map was found and map was set.  false otherwise.
        */
        bool GetTileMap( Real depth, TileMap* map ) const;

        /** Render the tile maps, starting with the deepest map and moving
            forward.

            @note
                primaryOffset will be clamped to the bounds of the tile.  This
                prevents the offset from going beyond its allowable range.
        */
        void Render( Point2Df& primaryOffset, const Viewport& viewport ) const;

        /** Read a tileset block from a tile map file */
        void ReadTileset( TiXmlNode* tilesetNode, const String& baseDir );

        /** Generate a default tile set for demo purposes.  This tileset may
            or may not have a texture applied to it.
        */
        void GenerateDefaultTileset( const String& textureName, const Point2Df& tileSize, const Point2D& tileCount );
    };
} // namespace PGE

#endif // PGETILEMAP_H
