
/*! $Id$
 *  @file   PgeTileEngine.h
 *  @author Chad M. Draper
 *  @date   May 9, 2008
 *  @brief  Handles a tile game level.
 *
 */

#ifndef PGETILEENGINE_H
#define PGETILEENGINE_H

#include "PgeBaseRenderEngine.h"

namespace PGE
{
    /** @class Level Engine
        This class will load a configuration for a tile game level, and handle
        all processing for that level.
    */
    class TileEngine : public BaseRenderEngine
    {
    public:
        TileEngine();
        virtual ~TileEngine();

//        /** Handle additional initialization for a user engine */
//        virtual void AdditionalInit();
//
//        /** Render the current display
//            @param  surface         Surface onto which to render the display
//        */
//        virtual void Render(  );
//
//    protected:
//
//        /** Create the surface */
//        virtual void CreateSurface();

    private:
    }; // class TileEngine

} // namespace PGE

#endif // PGETILEENGINE_H
