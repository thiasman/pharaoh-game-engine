
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

#include "PgeAudioManager.h"
#include "../AudioSystems/Audiere/PgeAudiereAudioSystem.h"

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

        mWindow->SetTitle( "Loading..." );

        std::string title = std::string( "Welcome to Pharaoh Game Engine - " ) + AutoVersion::FULLVERSION_STRING;
        mWindow->SetTitle( title );

        // Start the start manager:
        mStateManager->StartGame( "demo" );

        InputManager* inputMgr = InputManager::getSingletonPtr();
        AudioManager* audioMgr = AudioManager::getSingletonPtr();
        int soundIndex = audioMgr->CreateSound2D( "media/boom.mp3", true );
        int channelIndex = 0;
        audioMgr->Play( soundIndex, channelIndex );
        while ( !mStateManager->IsClosing() )
        {
            // Capture input:
            inputMgr->Capture();

            // Run the window message pump:
            mWindow->MessagePump();

            // Update the logic:
            mStateManager->Update( mTimer.GetElapsedTime() );

            // Lock the surface before rendering:


            // Update the display:
            mStateManager->Render();

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
            // Add the state manager as a listener to the window
            assert( !mWindow.IsNull() );
            mWindow->AddWindowListener( mStateManager.Get() );

            // Add the state manager as an input listener
            assert( !mStateManager.IsNull() );
            InputManager::getSingletonPtr()->AddInputListener( mStateManager.Get(), "State Manager" );

            // Initialize the audio manager:
            //BaseAudioSystem* audioSys = new AudiereAudioSystem();
            //AudioManager::getSingletonPtr()->Init( audioSys );
            AudioManager::getSingletonPtr()->Init( new AudiereAudioSystem() );
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
