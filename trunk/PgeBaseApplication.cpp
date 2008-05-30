
/*! $Id$
 *  @file   PgeBaseApplication.cpp
 *  @author Chad M. Draper
 *  @date   May 22, 2008
 *
 */

#include "../include/PgePlatform.h"
#include "../version.h"
#include "../include/PgeTypes.h"
#include "../include/PgeBaseApplication.h"
#include "../include/PgePlatformFactory.h"
#include "../include/PgeBaseWindowSystem.h"
#include "../include/PgeBaseWindowListener.h"

#include "PgePoint2D.h"
#include "PgeMatrix2D.h"
#include "PgeMath.h"

#include "cmd/LogFileManager.h"
cmd::LogFileManager cmd::LogFileManager::mInstance;

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

    void BaseApplication::Run()
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        lfm.CreateLog( "Pharaoh.log", true, cmd::LogFile::Everything );
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "main(...)" );

        try
        {
            assert( !mPlatformFactory.IsNull() );

            mWindow.SetNull();
            mWindow = SharedPtr< BaseWindowSystem >( mPlatformFactory->CreateWindowSystem() );
            assert( !mWindow.IsNull() );

            // Add the window listener:
            mWindow->AddWindowListener( this );
            mWindow->Init();
            mGameManager.Init();

            // Get the window ID
            size_t winHnd = 0;
            mWindow->GetCustomAttribute( "WINDOW", &winHnd );
            lfm << "Window handle = " << winHnd << std::endl;

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

        if ( mWindow->IsActive() )
            lfm << "Window activated\n";
        else
            lfm << "Window deactivated\n";
    }

} // namespace PGE
