
/*! $Id$
 *  @file   PgeBaseApplication.cpp
 *  @author Chad M. Draper
 *  @date   May 22, 2008
 *
 */

#include "PgePlatform.h"
#include "version.h"
#include "PgeTypes.h"
#include "PgeBaseApplication.h"
#include "PgePlatformFactory.h"
#include "PgeBaseWindowSystem.h"
#include "PgeBaseWindowListener.h"

#include "PgePoint2D.h"
#include "PgeMatrix2D.h"
#include "PgeMath.h"

#include "cmd/StringUtil.h"
#include "cmd/LogFileManager.h"

namespace PGE
{
    BaseApplication::BaseApplication( PlatformFactory* factory )
        : mPlatformFactory( factory )
    {
        //ctor
    }

    BaseApplication::~BaseApplication()
    {
        //dtor
    }

    //Init----------------------------------------------------------------------
    void BaseApplication::Init()
    {
        // Create the window:
        _createWindow();

        // Get the window ID
        mWindow->GetCustomAttribute( "WINDOW", &mWindowHandle );
        //BaseInputListener::Init( mWindowHandle );

        OIS::ParamList pl;
        String hndStr = cmd::StringUtil::toString( mWindowHandle );
        pl.insert( std::make_pair( String( "WINDOW" ), hndStr ) );
#if PGE_PLATFORM == PGE_PLATFORM_WIN32
        pl.insert( std::make_pair( String( "w32_mouse" ), String( "DISCL_FOREGROUND" ) ) );
        pl.insert( std::make_pair( String( "w32_mouse" ), String( "DISCL_NONEXCLUSIVE" ) ) );
#endif
        BaseInputListener::Init( pl );

        // Perform additional initialization:
        AdditionalInit();
    }

    //_createWindow-------------------------------------------------------------
    void BaseApplication::_createWindow()
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "BaseApplication::_createWindow(...)" );
        try
        {
            assert( !mPlatformFactory.IsNull() );

            mWindow.SetNull();
            mWindow = SharedPtr< BaseWindowSystem >( mPlatformFactory->CreateWindowSystem() );
            assert( !mWindow.IsNull() );

            // Add the window listener:
            mWindow->AddWindowListener( this );
            mWindow->Init();
        }
        catch ( std::exception& e )
        {
            lfm << e.what() << std::endl;
        }
    }

    void BaseApplication::Run()
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "BaseApplication::Run(...)" );

/*
        try
        {
            assert( !mWindow.IsNull() );

            mGameManager.Init();

            // Get the window ID
            size_t winHnd = 0;
            mWindow->GetCustomAttribute( "WINDOW", &winHnd );

            //PGE::TileEngine engine;
            mWindow->SetTitle( "Loading..." );

            std::string title = std::string( "Welcome to Pharaoh Game Engine - " ) + AutoVersion::FULLVERSION_STRING;
            mWindow->SetTitle( title );

            mWindow->Run();

            while ( !mWindow->IsClosed() )
            {
                // Run the window message pump:
                mWindow->MessagePump();

                // Update the logic:
                //DoLogic();
                mGameManager.PrepareFrame();

                // Lock the surface before rendering:
                mWindow->LockSurface();

                // Update the display:
                //DoRender();
                mGameManager.RenderFrame();

                // Unlock the surface before rendering:
                mWindow->UnlockSurface();

                //mWindow->RenderFrame();
            }
            mWindow->Shutdown();

            mWindow->SetTitle( "Goodbye." );

        }
        catch ( std::exception& e )
        {
            lfm << e.what() << std::endl;
        }
*/
    }

    //WindowSizeChanged---------------------------------------------------------
    void BaseApplication::WindowSizeChanged( BaseWindowSystem* win )
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "BaseApplication::WindowSizeChanged(...)" );

        // Get the window metrics:
        int x, y, z, width, height;
        win->GetMetrics( x, y, z, width, height );

        lfm << "Window position = ( " << x << ", " << y << ", " << z << " ), size = ( " << width << ", " << height << " )\n";
    }

    //WindowClosed--------------------------------------------------------------
    void BaseApplication::WindowClosed( BaseWindowSystem* win )
    {
    }

    //WindowFocusChanged--------------------------------------------------------
    void BaseApplication::WindowFocusChanged( BaseWindowSystem* win )
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "BaseApplication::WindowFocusChanged(...)" );

        if ( win->IsActive() )
            lfm << "Window activated\n";
        else
            lfm << "Window deactivated\n";
    }

    //keyPressed----------------------------------------------------------------
    bool BaseApplication::keyPressed( const OIS::KeyEvent& e )
    {
        return true;
    }

    //keyReleased---------------------------------------------------------------
    bool BaseApplication::keyReleased( const OIS::KeyEvent& e )
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "BaseApplication::keyReleased(...)" );
        lfm << "Key: " << e.key << ", " << ((OIS::Keyboard*)(e.device))->getAsString(e.key) << ", Character = " << (char)e.text << std::endl;

        return true;
    }

} // namespace PGE
