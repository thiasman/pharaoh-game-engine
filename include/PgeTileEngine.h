
/*! $Id$
 *  @file   PgeTileEngine.h
 *  @author Chad M. Draper
 *  @date   May 9, 2008
 *  @brief  Handles a tile game level.
 *
 */

#ifndef PGETILEENGINE_H
#define PGETILEENGINE_H

#include "PgeBaseGameEngine.h"

namespace PGE
{
    /** @class Level Engine
        This class will load a configuration for a tile game level, and handle
        all processing for that level.
    */
    class _PgeExport TileEngine : public BaseGameEngine
    {
    public:
        TileEngine();
        virtual ~TileEngine();

        /** Handle additional initialization for a user engine */
        virtual void AdditionalInit();

        /** Handle the actual work of preparing the frame */
        virtual void DoPrepareFrame( Real32 elapsedMS );

        /** Handle the actual work of rendering the frame */
        virtual void DoRenderFrame();

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
