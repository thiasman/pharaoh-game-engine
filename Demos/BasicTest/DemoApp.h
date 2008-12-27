
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
#include "PgeArchiveManager.h"
#include "version.h"

#include "PgeAudioManager.h"
#include "../AudioSystems/Audiere/PgeAudiereAudioSystem.h"

#include "DemoGameState.h"
#include "DemoGameStateFactory.h"

#include "cmd/LogFileManager.h"
using cmd::LogFileManager;
using cmd::LogFileSection;
//#include "PgeLogFileManager.h"

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
//        PGE::LogFileManager& lfm = PGE::LogFileManager::GetSingleton();
//        PGE::LogFileSection sect( lfm.GetDefaultLog(), "DemoApp::Run(...)" );

        int frameCount = 0;

        mWindow->SetTitle( "Loading..." );

        std::string title = std::string( "Welcome to Pharaoh Game Engine - " ) + AutoVersion::FULLVERSION_STRING;
        mWindow->SetTitle( title );

        // Start the start manager:
        mStateManager->StartGame( "demo" );

        InputManager* inputMgr = InputManager::getSingletonPtr();

        AudioManager* audioMgr = AudioManager::getSingletonPtr();
        int soundIndex = audioMgr->CreateStream2D( "Mists_of_Time.ogg", true );
        int channelIndex = 0;
        audioMgr->Play( "Mists_of_Time.ogg", channelIndex );

        //audioMgr->Play( soundIndex, channelIndex );
        mTimer.Restart();
        Timer fpsTimer;
        Real32 elapsedTime = 0;
        while ( !mStateManager->IsClosing() )
        {
            Real timerElapsed = mTimer.GetElapsedTime() / 1000.0;
            //lfm << "timerElapsed = " << timerElapsed << std::endl;

            // Capture input:
            inputMgr->Capture();

            // Run the window message pump:
            mWindow->MessagePump();

            // Update the logic:
            mStateManager->Update( timerElapsed );
            //mStateManager->Update( mTimer.GetTotalTime() / 1000.0 );

            // Lock the surface before rendering:
            mWindow->LockSurface();


            // Update the display:
            mStateManager->Render();

            // Unlock the surface before rendering:
            mWindow->UnlockSurface();

            // Update frame rate every second:
            elapsedTime = fpsTimer.GetTotalTime() / 1000.0;
            if ( elapsedTime < 1.0 )
                frameCount++;
            else
            {
//                lfm << "Frame Rate: " << Real32( frameCount / elapsedTime ) << ", frame count = " << frameCount << ", elapsedTime = " << elapsedTime << std::endl;
                frameCount = 0;
                fpsTimer.Restart();
            }
            //mTimer.Restart();
        }
        audioMgr->StopAll();
        mWindow->Shutdown();

        mWindow->SetTitle( "Goodbye." );
    }

protected:
    /** Perform additional initialization for the application-specific
        case.
    */
    void AdditionalInit()
    {
        LogFileManager& lfm = LogFileManager::getInstance();
        //LogFileManager& lfm = LogFileManager::GetSingleton();
        LogFileSection sect( lfm.GetDefaultLog(), "DemoApp::AdditionalInit(...)" );

        try
        {
            // Add the state manager as a listener to the window
            assert( !mWindow.IsNull() );
            mWindow->AddWindowListener( mStateManager.Get() );

            // Pass the window dimensions to the state manager
            mStateManager->WindowSizeChanged( mWindow.Get() );

            // Add the state manager as an input listener
            assert( !mStateManager.IsNull() );
            InputManager::getSingletonPtr()->AddInputListener( mStateManager.Get(), "State Manager" );

            // Initialize the audio manager:
            //BaseAudioSystem* audioSys = new AudiereAudioSystem();
            //AudioManager::getSingletonPtr()->Init( audioSys );
            AudioManager::getSingletonPtr()->Init( new AudiereAudioSystem() );

            PGE::ArchiveManager* archiveMgr = PGE::ArchiveManager::GetSingletonPtr();
            String baseDir = PGE::ArchiveManager::GetSingleton().GetApplicationDir();
            archiveMgr->AddArchive( baseDir + "media" );
            archiveMgr->AddArchive( baseDir + "media/data.zip" );
            //lfm << *archiveMgr << std::endl;
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
