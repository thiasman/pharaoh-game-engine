
/*! $Id$
 *  @file   PgeBaseEngine.cpp
 *  @author Chad M. Draper
 *  @date   May 1, 2008
 *
 */

#include "version.h"
#include "PgeBaseEngine.h"
#include "PgeException.h"

#include <windows.h>

namespace PGE
{
    //Constructor---------------------------------------------------------------
    BaseEngine::BaseEngine()
        : mLastTick( 0 ),
          mTickCounter( 0 ),
          mFrameCounter( 0 ),
          mCurrentFPS( 0 ),
          mWidth( 800 ),
          mHeight( 600 ),
          mTitle( "" ),
          mIsMinimized( false ),
          mIsPaused( false )
    {
    }

    //Destructor----------------------------------------------------------------
    BaseEngine::~BaseEngine()
    {
        SDL_Quit();
    }

    //SetSize-------------------------------------------------------------------
    void BaseEngine::SetSize( const unsigned long& w, const unsigned long& h )
    {
        mWidth  = w;
        mHeight = h;

        CreateSurface();
    }

    // CreateSurface------------------------------------------------------------
    void BaseEngine::CreateSurface()
    {
        mSurface = SDL_SetVideoMode( mWidth, mHeight, 0, SDL_SWSURFACE );
    }

    //Init----------------------------------------------------------------------
    void BaseEngine::Init()
    {
        // Register SDL_Quit to be called at exit
        atexit( SDL_Quit );

        // Initialize the video
        if ( SDL_Init( SDL_INIT_VIDEO ) )
        {
            std::string msg = std::string( "Unable to initialize SDL: " ) + SDL_GetError();
            throw Exception( msg );
        }

        // Create a window with the specified height and width:
        SetSize( mWidth, mHeight );
        if ( !mSurface )
        {
            std::string msg = std::string( "Unable to setup video: " ) + SDL_GetError();
            throw Exception( msg );
        }

        // Perform any additional initialization required by the sub-classed engine
        AdditionalInit();
    }

    //Run-----------------------------------------------------------------------
    void BaseEngine::Run()
    {
        // Get the start time:
        mLastTick   = SDL_GetTicks();
        mQuit       = false;

        while ( !mQuit )
        {
            // Handle user input
            HandleInput();

            if ( mIsMinimized )
            {
                // If the window is minimized, the game is paused.
                WaitMessage();
            }
            else
            {
                // Update the logic:
                DoLogic();

                // Update the display:
                DoRender();
            }
        }

        // Cleanup and terminate:
        Shutdown();
    }

    //HandleInput---------------------------------------------------------------
    void BaseEngine::HandleInput()
    {
        SDL_Event event;
        while ( SDL_PollEvent( &event ) )
        {
            switch ( event.type )
            {
            case SDL_KEYDOWN:
                {
                    // If the escape key was pressed, terminate the application.
                    // All other key processing gets passed to the derived class.
                    if ( event.key.keysym.sym == SDLK_ESCAPE )
                    {
                        mQuit = true;
                        break;
                    }

                    KeyDown( event.key.keysym.sym );
                }
                break;

            case SDL_KEYUP:
                KeyUp( event.key.keysym.sym );
                break;

            case SDL_QUIT:
                mQuit = true;
                break;

            case SDL_MOUSEMOTION:
                MouseMove( event.button.button,
                            event.motion.x,
                            event.motion.y,
                            event.motion.xrel,
                            event.motion.yrel );
                break;

            case SDL_MOUSEBUTTONUP:
                MouseButtonUp( event.button.button,
                            event.motion.x,
                            event.motion.y,
                            event.motion.xrel,
                            event.motion.yrel );
                break;

            case SDL_MOUSEBUTTONDOWN:
                MouseButtonDown( event.button.button,
                            event.motion.x,
                            event.motion.y,
                            event.motion.xrel,
                            event.motion.yrel );
                break;

            case SDL_ACTIVEEVENT:
                if ( event.active.state & SDL_APPACTIVE )
                {
                    if ( event.active.gain )
                    {
                        mIsMinimized = false;
                        MakeActive();
                    }
                    else
                    {
                        mIsMinimized = true;
                        MakeInactive();
                    }
                }
                break;
            }
        }
    }

    //DoLogic-------------------------------------------------------------------
    void BaseEngine::DoLogic()
    {
        // Get the elapsed time:
        unsigned long curTick = SDL_GetTicks();
        unsigned long elapsedTicks = curTick - mLastTick;
        mLastTick = curTick;

        UpdateLogic( elapsedTicks );

        // Update the tick counter:
        mTickCounter += elapsedTicks;
    }

    //DoRender------------------------------------------------------------------
    void BaseEngine::DoRender()
    {
        // Update the frame counter:
        ++mFrameCounter;

        if ( mTickCounter > 1000 )
        {
            mCurrentFPS = mFrameCounter;
            mFrameCounter = 0;
            mTickCounter = 0;
        }

        // Fill the background:
        SDL_FillRect( mSurface, 0, SDL_MapRGB( mSurface->format, 0, 0, 0 ) );

        // Lock surface if necessary:
        if ( SDL_MUSTLOCK( mSurface ) )
        {
            if ( SDL_LockSurface( mSurface ) < 0 )
                return;
        }

        // Render the scene:
        Render( GetSurface() );

        // Unlock the surface:
        if ( SDL_MUSTLOCK( mSurface ) )
        {
            SDL_UnlockSurface( mSurface );
        }

        // Update the screen:
        SDL_Flip( mSurface );
    }

    //SetTitle------------------------------------------------------------------
    void BaseEngine::SetTitle( const std::string& title )
    {
        mTitle = title;
        SDL_WM_SetCaption( mTitle.c_str(), 0 );
    }

    //GetTitle------------------------------------------------------------------
    const std::string& BaseEngine::GetTitle() const
    {
        return mTitle;
    }

    //GetSurface----------------------------------------------------------------
    SDL_Surface* BaseEngine::GetSurface() const
    {
        return mSurface;
    }

    //GetFPS--------------------------------------------------------------------
    unsigned long BaseEngine::GetFPS() const
    {
        return mCurrentFPS;
    }

    //GetVersion----------------------------------------------------------------
    std::string BaseEngine::GetVersion() const
    {
        std::string version = "";

        return version;
    }

} // namespace PGE
