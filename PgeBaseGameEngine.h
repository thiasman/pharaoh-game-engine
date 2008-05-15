
/*! $Id$
 *  @file   PgeBaseGameEngine.h
 *  @author Chad M. Draper
 *  @date   May 14, 2008
 *  @brief  Provides the base class for the OpenGL rendering system.  This
 *          should be overridden in order to customize the functionality of the
 *          class (for instance, side-scrolling, 3D, etc.)
 *
 */

#ifndef PGEBASERENDERENGINE_H
#define PGEBASERENDERENGINE_H

#include "PgeTypes.h"
#include "PgeTimer.h"
#include "PgePoint2D.h"
#include "PgePoint3D.h"

namespace PGE
{
    /** @class BaseGameEngine
        Provides the base for the rendering engine.  This should be sub-classed
        in order to customize what the engine can do.
    */
    class BaseGameEngine
    {
    private:
        unsigned long   mLastTick;      /**< Tick value when the last frame was rendered */
        unsigned long   mTickCounter;   /**< Counts ticks for calculating the FPS */
        Timer           mTimer;
        unsigned long   mFrameCounter;  /**< Frame counter for calculating the FPS */
        unsigned long   mCurrentFPS;    /**< Last calculated frame rate */

        Point2D         mDisplaySize;   /**< Size of the display area */

    public:
        BaseGameEngine();
        virtual ~BaseGameEngine();

        /** Get the frame rate */
        unsigned long GetFPS() const;

        /** Initialize the engine */
        void Init();

        /** Pause the game engine */
        virtual void Pause();

        /** Unpause the game */
        virtual void Unpause();

        /** Prepare the frame for rendering
            @brief
                Any AI or motion needs to be updated for the frame.
        */
        void PrepareFrame();

        /** Render the frame */
        void RenderFrame();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // Virtual methods:
        ////////////////////////////////////////////////////////////////////////

        /** Handle additional initialization for a user engine */
        virtual void AdditionalInit()                       { }

        /** Shut down the engine and free allocated memory */
        virtual void Shutdown()                             { }

        /** Handle the actual work of preparing the frame */
        virtual void DoPrepareFrame( Real32 elapsedMS )     { }

        /** Handle the actual work of rendering the frame */
        virtual void DoRenderFrame()                        { }

    }; // class BaseGameEngine

} // namespace PGE

#endif // PGEBASERENDERENGINE_H
