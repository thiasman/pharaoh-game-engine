
/*! $Id$
 *  @file   PgeTileSet.h
 *  @author Chad M. Draper
 *  @date   January 27, 2009
 *  @brief  A tile set is a set of tiles from a single image, and anything that
 *          uses those tiles.
 *
 */

#ifndef PgeTileSet_H_
#define PgeTileSet_H_

#include "PgeTypes.h"
#include "PgeViewport.h"
#include "PgeStringUtil.h"

class TiXmlNode;

namespace PGE
{
    /** @class TileSet

        The tileset contains all tiles from a given source texture, and anything
        that uses those tiles.  This includes maps and sequences.
    */
    class _PgeExport TileSet
    {
    public:
        UInt32      mIndex;                 ///< Index of the tileset

    protected:
        String      mIdentifier;            ///< ID name of the tileset
        Point2D     mTileSize;              ///< Size of the tiles in the tileset

        String      mImageName;             ///< Name of the texture image file
        Point2D     mImageSize;             ///< Dimensions of the texture image file
        Point2D     mGridSize;              ///< Horizontal and vertical size of the grid containing the tiles (source image)
        UInt32      mOverlap;               ///< Amount which the tiles overlap each other
        UInt32      mTileCount;             ///< Number of tiles in the set

        UInt32      mDisplayListBase;       ///< Base index of the display list for this tile set

        /** @struct TileMapItem
            Defines an item in a tile map (a single tile)
        */
        struct TileMapItem
        {
            Int     tileIndex;              ///< Index of the tile to display
            Int     boundsCode;             ///< Indicates which sides of the tile are a boundary
            Int     mapCode;                ///< Indicates special tiles

            /** Constructor */
            TileMapItem()
                : tileIndex( 0 ), boundsCode( 0 ), mapCode( 0 )
            {
            }
        };

        /** @typedef TileMap
            Defines an array of tile map items as the tile map
        */
        typedef std::vector< TileMapItem >  TileMap;
        mutable TileMap     mTileMap;
        Point2D     mTileMapSize;           ///< Dimensions of the tile map

        /** @class Sequence
            Defines a tile sequence.  A tile sequence is a collection of
            tiles that are displayed consecutively, following a delay.
        */
        class Sequence
        {
        private:
            Real    frameRate;      ///< Frames-per-second
            Real    secondsPerFrame; ///< Inverse frame rate.  Indicates how long each frame is held.
            Int     curFrame;       ///< Next frame to render in the sequence
            Real    frameTime;      ///< Current time on the current frame.  Once this value has exceeded secondsPerFrame, the current frame is incremented, and this value is set to fmod( frameTime, secondsPerFrame ).

        public:
            Int     index;          ///< Index of the sequence

            /** @struct FrameData
                Per-frame data
            */
            struct FrameData
            {
                Int     delay;
                Int     tileNumber; ///< Index of the tile used for this frame
            };

            /** @typedef FrameSequence
                A collection of FrameData, defining the sequence.
            */
            typedef std::vector< FrameData > FrameSequence;
            FrameSequence mSequence;    ///< Frames in the sequence

            /** Constructor */
            Sequence( Real fps = 12 );

            /** Assignment operator */
            Sequence& operator=( const Sequence& src );

            /** Set the frame rate */
            void SetFrameRate( Real fps );
            /** Get the frame rate */
            Real GetFrameRate() const;

            /** Read a sequence */
            void ReadSequence( TiXmlNode* seqNode );

            /** Prepare the sequence for the next render operation.  This takes
                an elapsed time, and sets the index for the next frame in the
                sequence to render.
            */
            void Prepare( Real32 elapsedMS );

            /** Render the current frame in the sequence.  All transformations
                should have already been performed.
            */
            void Render( UInt32 displayListBase );
        };

        /** @typedef SequenceArray
            Defines an array of sequences.  Sequences are referenced in the map
            by the inverse of their index, and there is no sequence at index 0.
        */
        typedef std::vector< Sequence > SequenceArray;
        mutable SequenceArray mSequences;

        /** Generate the tiles in the tileset */
        bool _generateTiles();

        /** Read a tile map */
        bool _readTileMap( TiXmlNode* mapNode );

        /** Read a sequence */
        bool _readSequence( TiXmlNode* seqNode );

        /** Render a span of consecutive tiles in the same row */
        void _renderTileSpan( TileMap::const_iterator& tileIter, const UInt32& displayListBase, UInt32 count ) const;

    public:
        /** Constructor */
        TileSet();
        /** Constructor */
        TileSet( TiXmlNode* tilesetNode, const String& baseDir, UInt32 mapIndex );
        /** Destructor */
        ~TileSet();

        /** Assignment operator */
        TileSet& operator=( const TileSet& src );

        /** Less-than operator */
        bool operator<( const TileSet& src ) const;

        /** Greater-than operator */
        bool operator>( const TileSet& src ) const;

        /** Get the size of the map */
        Point2D GetMapSize() const;
        /** Get the size of the tiles */
        const Point2D& GetTileSize() const;
        /** Get the size of the map grid (number of horizontal/vertical cells.) */
        const Point2D& GetMapGridSize() const;

        /** Read a tileset */
        bool ReadTileSet( TiXmlNode* tilesetNode, const String& baseDir, UInt32 mapIndex );

        /** Release all data allocated by the tileset */
        void Release();

        /** Update the scene based on elapsed time (prepare any sequences) */
        void Update( PGE::Real32 elapsedMS );

        /** Render the tileset.

            Rendering a tileset means to render the tilemap, and any sequences
            which are currently visible.
        */
        void Render( const Point2Df& offset, const Viewport& viewport ) const;

    }; // class TileSet

} // namespace PGE

#endif  // PgeTileSet_H_
