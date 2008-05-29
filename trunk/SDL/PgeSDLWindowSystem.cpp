
/*! $Id$
 *  @file   PgeSDLWindowSystem.cpp
 *  @author Chad M. Draper
 *  @date   May 14, 2008
 *
 */

#include <SDL/SDL_syswm.h>

#include "../PgePlatform.h"
#include "../PgeException.h"
#include "PgeSDLWindowSystem.h"
#include "../PgeBaseWindowListener.h"

#include "cmd/LogFileManager.h"

namespace PGE
{

    SDLWindowSystem::SDLWindowSystem()
    {
        //ctor
    }

    SDLWindowSystem::~SDLWindowSystem()
    {
        //dtor
        SDL_Quit();
    }

//    //Init----------------------------------------------------------------------
//    void SDLWindowSystem::Init()
//    {
//        // Register SDL_Quit to be called at exit
//        atexit( SDL_Quit );
//
//        // Initialize the video
//        if ( SDL_Init( SDL_INIT_VIDEO ) )
//        {
//            String msg = std::string( "Unable to initialize SDL: " ) + SDL_GetError();
//            throw Exception( msg );
//        }
//
//        // Create a window with the specified height and width:
//        SetSize( mWidth, mHeight );
//        if ( !mSurface )
//        {
//            String msg = std::string( "Unable to setup video: " ) + SDL_GetError();
//            throw Exception( msg );
//        }
//
//        // Perform any additional initialization required by the sub-classed engine
//        AdditionalInit();
//    }

    //AdditionalInit------------------------------------------------------------
    void SDLWindowSystem::AdditionalInit()
    {
        // Register SDL_Quit to be called at exit
        atexit( SDL_Quit );

        // Initialize the video
        if ( SDL_Init( SDL_INIT_VIDEO ) )
        {
            String msg = std::string( "Unable to initialize SDL: " ) + SDL_GetError();
            throw Exception( msg );
        }

        // Create a window with the specified height and width:
        SetSize( mWidth, mHeight );
        if ( !mSurface )
        {
            String msg = std::string( "Unable to setup video: " ) + SDL_GetError();
            throw Exception( msg );
        }

        // SDL does not trigger an activation event when the window is first
        // created, so do it ourselves:
        MakeActive();
        std::vector< BaseWindowListener* >::iterator iter = mWindowListeners.begin();
        while ( iter != mWindowListeners.end() )
        {
            (*iter)->WindowFocusChanged( this );
            iter++;
        }

    }

    //HandleInput---------------------------------------------------------------
    void SDLWindowSystem::HandleInput()
    {
    }

    // CreateSurface------------------------------------------------------------
    void SDLWindowSystem::CreateSurface()
    {
        // OpenGL double buffering:
        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

        mSurface = SDL_SetVideoMode( mWidth, mHeight, 0, SDL_HWSURFACE | SDL_OPENGL );
    }

    //SetTitle------------------------------------------------------------------
    void SDLWindowSystem::SetTitle( const String& title )
    {
        BaseWindowSystem::SetTitle( title );

        SDL_WM_SetCaption( mTitle.c_str(), 0 );
    }

    //LockSurface---------------------------------------------------------------
    void SDLWindowSystem::LockSurface()
    {
        // Fill the background:
        SDL_FillRect( mSurface, 0, SDL_MapRGB( mSurface->format, 0, 0, 0 ) );

        // Lock surface if necessary:
        if ( SDL_MUSTLOCK( mSurface ) )
        {
            if ( SDL_LockSurface( mSurface ) < 0 )
                return;
        }
    }

    //LockSurface---------------------------------------------------------------
    void SDLWindowSystem::UnlockSurface()
    {
        // Unlock the surface:
        if ( SDL_MUSTLOCK( mSurface ) )
        {
            SDL_UnlockSurface( mSurface );
        }

        // Update the screen:
        SDL_GL_SwapBuffers();
        //SDL_Flip( mSurface );
    }

    //GetCustomAttribute--------------------------------------------------------
    void SDLWindowSystem::GetCustomAttribute( const String& name, void* data )
    {
        if ( name == "WINDOW" )
        {
            int* handle = (int*)( data );
            *handle = _getWindowHandle();
            return;
        }
    }

    //_getWindowHandle----------------------------------------------------------
    int SDLWindowSystem::_getWindowHandle() const
    {
        SDL_SysWMinfo sysInfo;
        SDL_VERSION( &sysInfo.version );
        if ( !SDL_GetWMInfo( &sysInfo ) )
            return 0;
        return int( sysInfo.window );
    }

    void SDLWindowSystem::GetMetrics( int& x, int& y, int& z, int& width, int& height ) const
    {
#if PGE_PLATFORM == PGE_PLATFORM_WIN32
        // Get the window handle
        SDL_SysWMinfo sysInfo;
        SDL_VERSION( &sysInfo.version );
        if ( SDL_GetWMInfo( &sysInfo ) )
        {
            HWND hWnd = sysInfo.window;
            RECT rc;
            GetWindowRect( hWnd, &rc );
            x = rc.left;
            y = rc.top;
            width = rc.right - rc.left;
            height = rc.bottom - rc.top;

            // Iterate over the windows to find the z-order:
            z = 0;
            HWND curHwnd = GetTopWindow( NULL );
            while ( curHwnd != NULL && curHwnd != sysInfo.window )
            {
                ++z;
                curHwnd = GetNextWindow( curHwnd, GW_HWNDNEXT );
            }
        }
#else
        // For non-windows systems, zero out the position and depth, and use the
        // dimensions of the surface.
        if ( mSurface )
        {
            x = 0;
            y = 0;
            z = 0;
            width = mSurface.w;
            height = mSurface.h;
        }
#endif
    }

    //MessagePump---------------------------------------------------------------
    void SDLWindowSystem::MessagePump()
    {
        SDL_Event event;

        while ( SDL_PollEvent( &event ) )
        {
            switch ( event.type )
            {
/*
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
*/

/*
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
*/

            case SDL_QUIT:
                {
                    mQuit = true;
                    std::vector< BaseWindowListener* >::iterator iter = mWindowListeners.begin();
                    while ( iter != mWindowListeners.end() )
                    {
                        (*iter)->WindowClosed( this );
                        iter++;
                    }
                }
                break;

            case SDL_VIDEORESIZE:
                {
                    std::vector< BaseWindowListener* >::iterator iter = mWindowListeners.begin();
                    while ( iter != mWindowListeners.end() )
                    {
                        (*iter)->WindowSizeChanged( this );
                        iter++;
                    }
                }
                break;

            case SDL_ACTIVEEVENT:
                {
                    if ( event.active.state & SDL_APPACTIVE || event.active.state & SDL_APPINPUTFOCUS )
                    {
                        if ( event.active.gain )
                        {
                            if ( event.active.state & SDL_APPACTIVE )
                                mIsMinimized = false;
                            MakeActive();
                        }
                        else
                        {
                            if ( event.active.state & SDL_APPACTIVE )
                                mIsMinimized = true;
                            MakeInactive();
                        }

                        std::vector< BaseWindowListener* >::iterator iter = mWindowListeners.begin();
                        while ( iter != mWindowListeners.end() )
                        {
                            (*iter)->WindowFocusChanged( this );
                            iter++;
                        }
                    }
                }
                break;
            }
        }
    }

} // namespace PGE
