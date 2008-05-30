
/*! $Id$
 *  @file   DemoApp.h
 *  @author Chad M. Draper
 *  @date   May 30, 2008
 *  @brief  Example of sub-classing the application class.
 *
 */

#ifndef DEMOAPP_H_INCLUDED
#define DEMOAPP_H_INCLUDED

#include "PgeBaseApplication.h"
#include "PgeSharedPtr.h"
#include "PgeGameStateManager.h"
#include "PgePlatformFactory.h"
#include "PgeBaseWindowSystem.h"
#include "version.h"

#include "DemoGameState.h"
#include "DemoGameStateFactory.h"

#include "cmd/LogFileManager.h"

using namespace PGE;

class DemoApp : public PGE::BaseApplication
{
public:
    DemoApp( PlatformFactory* factory )
        : BaseApplication( factory ),
          mStateManager( new PGE::GameStateManager( new DemoGameStateFactory() ) )
    {
    }

    /** Start the application.  This will enter a loop that will run until
        the user closes the application.  Each iteration of the loop will
        update logic, listen for events, and update the display.
    */
    void Run()
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoApp::Run(...)" );

        assert( !mStateManager.IsNull() );

        mWindow->SetTitle( "Loading..." );

        std::string title = std::string( "Welcome to Pharaoh Game Engine - " ) + AutoVersion::FULLVERSION_STRING;
        mWindow->SetTitle( title );

        // Start the start manager:
        mStateManager->StartGame( "demo" );

        while ( !mStateManager->IsClosing() )
        {
            // Run the window message pump:
            mWindow->MessagePump();

            // Update the logic:
            mStateManager->Update( mTimer.GetElapsedTime() );
            //mGameManager.PrepareFrame();

            // Lock the surface before rendering:
            lfm << "Lock surface...\n";
            mWindow->LockSurface();

            // Update the display:
            mStateManager->Render();
            //mGameManager.RenderFrame();

            // Unlock the surface before rendering:
            mWindow->UnlockSurface();
        }
        mWindow->Shutdown();

        mWindow->SetTitle( "Goodbye." );
    }

protected:
    /** Perform additional initialization for the application-specific
        case.
    */
    void AdditionalInit()
    {
        try
        {
            assert( !mWindow.IsNull() );

            // Add the state manager as a listener to the window
            mWindow->AddWindowListener( mStateManager.Get() );
        }
        catch ( std::exception& e )
        {
        }
    }

private:
    typedef SharedPtr< PGE::GameStateManager >  StateManagerPtr;
    StateManagerPtr mStateManager;

}; // class DemoApp

#endif // DEMOAPP_H_INCLUDED
