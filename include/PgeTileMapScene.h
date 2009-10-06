
/*! $Id$
 *  @file   PgeTileMapScene.h
 *  @author Chad M. Draper
 *  @date   January 19, 2009
 *  @brief  A scene is made up of multiple layers of tile maps.
 *
 */

#ifndef PgeTileMapScene_H_
#define PgeTileMapScene_H_

#include <vector>
#include <set>
#include <map>
#include "PgeTileSet.h"

namespace PGE
{
    /** @class TileMapScene
        A collection of tile maps which compose a scene, such as a multi-layered
        level.

        The tile map scene maintains all tiles in a level.  The tiles are sorted by
        depth, with the primary map being 0.  Maps in front of the primary map
        will have a negative depth, and those behind it are positive.

        @remarks
            While the scene will read the tile sets from the data file, it only
            needs to store the appropriate map from within each tileset.  When
            reading the scene, the necessary map index should be given (default
            is 0.)  It will then iterate over each tileset, and attempt to
            retrieve the requested map.  If there is no map with the desired
            index, then it proceeds to the next tileset, skipping the map.

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
            There can be multiple tile map groups.  While it may be unusual to
            have more than 1, there is no requirement that there be only 1.
    */
    class TileMapScene
    {
    private:
        typedef std::multiset< TileSet, std::greater< TileSet > > TileSetMultiSet;
        TileSetMultiSet mTileSets;
        TileSet*        mPrimaryTileSet;

    public:
        /** Constructor */
        TileMapScene();
        /** Constructor */
        TileMapScene( TiXmlNode* projectNode, const String& baseDir, UInt32 mapNum = 0 );

        /** Read the maps that compose this scene
            @param  projectNode         Pointer to the 'project' node of the map file
            @param  mapNum              Number (index) of the map to read for this scene.
        */
        void ReadScene( TiXmlNode* projectNode, const String& baseDir, UInt32 mapNum = 0 );

        /** Update the scene based on elapsed time */
        void Update( PGE::Real32 elapsedMS );

        /** Render the scene */
        void Render( Point2Df& offset, const Viewport& viewport );

        /** Read a tileset block from a tile map file */
        void ReadTileset( TiXmlNode* tilesetNode, const String& baseDir, UInt32 mapNum = 0 );

        /** Generate a default tile set for demo purposes.  This tileset may
            or may not have a texture applied to it.
        */
        void GenerateDefaultTileset( const String& textureName, const Point2Df& tileSize, const Point2D& tileCount );

        /** Add a tile set to the manager */
        void AddTileSet( TileSet& set );

    }; // class TileMapScene

} // namespace PGE
#endif  // PgeTileMapScene_H_
