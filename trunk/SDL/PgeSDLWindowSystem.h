
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
        //void Init();

        /** Set the window title */
        virtual void SetTitle( const String& title );

        /** Get a custom attribute that has been set for the window */
        virtual void GetCustomAttribute( const String& name, void* data );

    protected:

        /** Handle additional initialization for a user engine */
        virtual void AdditionalInit();

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

        /** Get the window handle */
        int _getWindowHandle() const;
    };

} // namespace PGE

#endif // PGESDLWINDOWSYSTEM_H
