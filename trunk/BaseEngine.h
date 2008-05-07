
/*! $Id$
 *  @file   BaseEngine.h
 *  @author Chad M. Draper
 *  @date   May 1, 2008
 *  @brief  Defines the base class for the tile-based game engine,
 *
 */

#ifndef BASEENGINE_H_INCLUDED
#define BASEENGINE_H_INCLUDED

#include <string>

#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

namespace PGE
{
    /** @class BaseEngine
        Base class for the engine.  This doesn't know or care about how the
        engine is to be implemented, but provides the interface that can be
        customized to the game's needs.
    */
    class BaseEngine
    {
    private:
        unsigned long   mLastTick;      /**< Tick value when the last frame was rendered */
        unsigned long   mTickCounter;   /**< Counts ticks for calculating the FPS */
        unsigned long   mFrameCounter;  /**< Frame counter for calculating the FPS */
        unsigned long   mCurrentFPS;    /**< Last calculated frame rate */

        unsigned long   mWidth;         /**< Width of the window */
        unsigned long   mHeight;        /**< Height of the window */
        std::string     mTitle;         /**< Title of the window */
        bool            mIsMinimized;   /**< Indicates if the window is minimized (game should pause) */
        bool            mIsPaused;      /**< Indicates if the gameplay should pause */
        bool            mQuit;          /**< Indicates if the application should quit */

        SDL_Surface*    mSurface;       /**< Rendering surface */

    protected:
        /** Update any logic (i.e. AI processing) */
        void DoLogic();

        /** Update the display */
        void DoRender();

        /** Set the window size */
        void SetSize( const unsigned long& w, const unsigned long& h );

        /** Handle user input */
        void HandleInput();

    public:
        /** Default Constructor */
        BaseEngine();

        /** Destructor */
        virtual ~BaseEngine();

        /** Initialize the engine */
        void Init();

        /** Start the game loop */
        void Run();

        /** Set the window title */
        void SetTitle( const std::string& title );
        /** Get the window title */
        const std::string& GetTitle() const;

        /** Get the display surface */
        SDL_Surface* GetSurface() const;

        /** Get the frame rate */
        unsigned long GetFPS() const;

        /** Get a string containing the version information */
        std::string GetVersion() const;

        ////////////////////////////////////////////////////////////////////////
        // Virtual methods:
        ////////////////////////////////////////////////////////////////////////

        /** Handle additional initialization for a user engine */
        virtual void AdditionalInit()                       { }

        /** Perform calculation/thinking
            @param  elapsedTime     Time in milliseconds since the last update
        */
        virtual void Update( unsigned long elapsedTime )    { }

        /** Render the current display
            @param  surface         Surface onto which to render the display
        */
        virtual void Render( SDL_Surface* surface )         { }

        /** Shut down the engine and free allocated memory */
        virtual void Shutdown()                             { }

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

    }; // class BaseEngine

} // namespace PGE

#endif // BASEENGINE_H_INCLUDED
