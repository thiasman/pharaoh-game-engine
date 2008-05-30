
/*! $Id$
 *  @file   PgeSDLWindowSystem.h
 *  @author Chad M. Draper
 *  @date   May 14, 2008
 *  @brief  Implements a window system using SDL.
 *
 */

#ifndef PGESDLWINDOWSYSTEM_H
#define PGESDLWINDOWSYSTEM_H

#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include "PgeBaseWindowSystem.h"

namespace PGE
{
    class SDLWindowSystem : public BaseWindowSystem
    {
    private:
        SDL_Surface*    mSurface;       /**< Rendering surface */

    public:
        /** Constructor */
        SDLWindowSystem();
        /** Destructor */
        ~SDLWindowSystem();

        /** Initialize the engine */
        //void Init();

        /** Set the window title */
        void SetTitle( const String& title );

        /** Get a custom attribute that has been set for the window */
        void GetCustomAttribute( const String& name, void* data );

        /** Get the dimensions, placement, and z-order of the window
            @param  x               X-coordinate of the window
            @param  y               Y-coordinate of the window
            @param  z               z-order of the window
            @param  width           Width of the window
            @param  height          Height of the window
        */
        void GetMetrics( int& x, int& y, int& z, int& width, int& height ) const;

        /** Some rendering surfaces require the surface be locked before
            rendering.
        */
        void LockSurface();

        /** If a surface was locked prior to rendering, it will need to be
            unlocked after rendering.
        */
        void UnlockSurface();

        /** Pump messages through the window queue.  It is necessary to call
            this each frame so that the messages get processed.
        */
        virtual void MessagePump();

    protected:

        /** Handle additional initialization for a user engine */
        void AdditionalInit();

        /** Handle user input */
        void HandleInput();

        /** Create the surface */
        void CreateSurface();

        /** Get the window handle */
        int _getWindowHandle() const;
    };

} // namespace PGE

#endif // PGESDLWINDOWSYSTEM_H
