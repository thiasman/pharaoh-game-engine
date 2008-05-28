
/*! $Id$
 *  @file   PgeBaseWindowSystem.h
 *  @author Chad M. Draper
 *  @date   May 1, 2008
 *  @brief  Defines the base class implementation's windowing system.
 *
 */

#ifndef PGEBASEWINDOWSYSTEM_H_INCLUDED
#define PGEBASEWINDOWSYSTEM_H_INCLUDED

#include <string>

#include "PgeTypes.h"
#include "PgeException.h"
#include "PgeGameManager.h"

namespace PGE
{
    /** @class BaseWindowSystem
        Base class for the windowing system.  This should be overridden to
        accommodate the display system (ie. SDL, wxWidgets, Win32, X, etc.)
    */
    class _PgeExport BaseWindowSystem
    {
    protected:

        unsigned long   mWidth;         /**< Width of the window */
        unsigned long   mHeight;        /**< Height of the window */
        String          mTitle;         /**< Title of the window */
        bool            mIsMinimized;   /**< Indicates if the window is minimized (game should pause) */
        bool            mIsPaused;      /**< Indicates if the gameplay should pause */
        bool            mQuit;          /**< Indicates if the application should quit */

        GameManager     mGameManager;   /**< Manages the game states */

    protected:
        /** Update any logic (i.e. AI processing) */
        //void Logic();

        /** Update the display */
        //void Render();

        /** Set the window size */
        void SetSize( const unsigned long& w, const unsigned long& h );

        /** Handle user input */
        virtual void HandleInput()          = 0;

        /** Create the surface */
        virtual void CreateSurface()        = 0;

    public:
        /** Default Constructor */
        BaseWindowSystem();

        /** Destructor */
        virtual ~BaseWindowSystem();

        /** Initialize the engine */
        virtual void Init();

        /** Start the game loop */
        void Run();

        /** Set the window title */
        virtual void SetTitle( const String& title );
        /** Get the window title */
        const String& GetTitle() const;

        /** Get the display surface */
        /*SDL_Surface* GetSurface() const;*/

        /** Get the frame rate */
        unsigned long GetFPS() const;

        /** Get a string containing the version information */
        String GetVersion() const;

        /** Shut down the engine and free allocated memory */
        virtual void Shutdown()                             { mQuit = true; }

        /** Render the next frame */
        virtual void RenderFrame();

        /** Determine if the window is closed.  This will let us cancel the
            program if the user clicked the 'x' on the title bar.
        */
        virtual bool IsClosed() const                       { return mQuit; }

        /** Get a custom attribute that has been set for the window */
        virtual void GetCustomAttribute( const String& name, void* data );

    protected:
        ////////////////////////////////////////////////////////////////////////
        // Virtual methods:
        ////////////////////////////////////////////////////////////////////////

        /** Handle additional initialization for a user engine */
        virtual void AdditionalInit()                       { }

        /** Perform calculation/thinking
            @param  elapsedTime     Time in milliseconds since the last update
        */
        //virtual void UpdateLogic( Real32 elapsedTime )    { }

        /** Some rendering surfaces require the surface be locked before
            rendering.
        */
        virtual void LockSurface()                          { }

        /** If a surface was locked prior to rendering, it will need to be
            unlocked after rendering.
        */
        virtual void UnlockSurface()                        { }

        /** Render the current display
        */
        //virtual void DoRender(  )                             { }

        /** Make the window active */
        virtual void MakeActive()                           { }

        /** Make the window inactive */
        virtual void MakeInactive()                         { }

        /** Handle a keyboard key being released
            @param  key             Key which was released
        */
        virtual void KeyUp( const int& key )                { }

        /** Handle a keyboard key being pressed
            @param  key             Key which was pressed
        */
        virtual void KeyDown( const int& key )              { }

        /** Handle a mouse move
            @param  button          Specifies which, if any, button is currently down
            @param  X               X-coordinate of the mouse
            @param  Y               Y-coordinate of the mouse
            @param  relX            Relative x offset (in pixels) from the previous position
            @param  relY            Relative x offset (in pixels) from the previous position
        */
        virtual void MouseMove( const int& button,
                                const int& X,
                                const int& Y,
                                const int& relX,
                                const int& relY )           { }

        /** Handle a mouse button being released
            @param  button          Specifies which button was released
            @param  X               X-coordinate of the mouse
            @param  Y               Y-coordinate of the mouse
            @param  relX            Relative x offset (in pixels) from the previous position
            @param  relY            Relative x offset (in pixels) from the previous position
        */
        virtual void MouseButtonUp( const int& button,
                                const int& X,
                                const int& Y,
                                const int& relX,
                                const int& relY )           { }

        /** Handle a mouse button being pressed
            @param  button          Specifies which button was pressed
            @param  X               X-coordinate of the mouse
            @param  Y               Y-coordinate of the mouse
            @param  relX            Relative x offset (in pixels) from the previous position
            @param  relY            Relative x offset (in pixels) from the previous position
        */
        virtual void MouseButtonDown( const int& button,
                                const int& X,
                                const int& Y,
                                const int& relX,
                                const int& relY )           { }

    }; // class BaseWindowSystem

} // namespace PGE

#endif // PGEBASEWINDOWSYSTEM_H_INCLUDED
