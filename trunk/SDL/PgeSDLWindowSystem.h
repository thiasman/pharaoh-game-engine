
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
#include <SDL.h>
#endif

#include "../PgeBaseWindowSystem.h"

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
        virtual ~SDLWindowSystem();

        /** Initialize the engine */
        void Init();

        /** Set the window title */
        virtual void SetTitle( const String& title );

    protected:
        /** Handle user input */
        virtual void HandleInput();

        /** Create the surface */
        virtual void CreateSurface();

        /** Some rendering surfaces require the surface be locked before
            rendering.
        */
        virtual void LockSurface();

        /** If a surface was locked prior to rendering, it will need to be
            unlocked after rendering.
        */
        virtual void UnlockSurface();

    };

} // namespace PGE

#endif // PGESDLWINDOWSYSTEM_H
