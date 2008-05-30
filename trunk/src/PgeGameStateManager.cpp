
/*! $Id$
 *  @file   PgeGameStateManager.h
 *  @author Chad M. Draper
 *  @date   May 30, 2008
 *
 */

#include "PgeGameStateManager.h"
#include "PgeBaseWindowSystem.h"

#include "cmd/LogFileManager.h"

namespace PGE
{
    GameStateManager::GameStateManager( GameStateFactory* stateFactory )
        : mStateFactory( StateFactoryPtr( stateFactory ) ),
          mIsClosed( false )
    {
        //ctor
    }

    GameStateManager::~GameStateManager()
    {
        //dtor
    }

    //StartGame-----------------------------------------------------------------
    void GameStateManager::StartGame( const String& stateType )
    {
        // Create the new state
        BaseGameState* newState = mStateFactory->CreateState( stateType );

        // Start the game
        StartGame( newState );
    }

    //StartGame-----------------------------------------------------------------
    void GameStateManager::StartGame( BaseGameState* state )
    {
        // Resources need to be setup, input and audio needs to be initialized, etc.

        // Switch to the first state:
        ChangeState( state );
    }

    //ChangeState---------------------------------------------------------------
    void GameStateManager::ChangeState( const String& stateType )
    {
        // Create the new state
        BaseGameState* newState = mStateFactory->CreateState( stateType );

        // Change states
        ChangeState( newState );
    }

    //ChangeState---------------------------------------------------------------
    void GameStateManager::ChangeState( BaseGameState* state )
    {
        // Shutdown and remove the active state
        if ( !mStates.empty() )
        {
            mStates.back()->Destroy();
            mStates.pop_back();
        }

        // Add the new state to the stack
        mStates.push_back( StatePtr( state ) );

        // Activate the new state
        mStates.back()->Init();
    }

    //PushState-----------------------------------------------------------------
    void GameStateManager::PushState( const String& stateType )
    {
        // Create the new state
        BaseGameState* newState = mStateFactory->CreateState( stateType );

        // Push the new state
        PushState( newState );
    }

    //PushState-----------------------------------------------------------------
    void GameStateManager::PushState( BaseGameState* state )
    {
        // NOTE: This method will probably be used less often than ChangeState,
        //       but is typically used when pausing the application.

        // Pause the current state
        if ( !mStates.empty() )
        {
            mStates.back()->Pause();
        }

        // Add the new state to the stack
        mStates.push_back( StatePtr( state ) );

        // Activate the new state
        mStates.back()->Init();
    }

    //PopState------------------------------------------------------------------
    void GameStateManager::PopState()
    {
        // This method is commonly used to resume an application that has been paused.

        // Shutdown and remove the active state
        if ( !mStates.empty() )
        {
            mStates.back()->Destroy();
            mStates.pop_back();
        }

        // Resume the now-active state:
        if ( !mStates.empty() )
            mStates.back()->Resume();
    }

    //WindowSizeChanged---------------------------------------------------------
    void GameStateManager::WindowSizeChanged( BaseWindowSystem* win )
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "GameStateManager::WindowSizeChanged(...)" );

        // Get the window metrics:
        int x, y, z, width, height;
        win->GetMetrics( x, y, z, width, height );

        lfm << "Window position = ( " << x << ", " << y << ", " << z << " ), size = ( " << width << ", " << height << " )\n";
    }

    //WindowClosed--------------------------------------------------------------
    void GameStateManager::WindowClosed( BaseWindowSystem* win )
    {
        mIsClosed = true;
    }

    //WindowFocusChanged--------------------------------------------------------
    void GameStateManager::WindowFocusChanged( BaseWindowSystem* win )
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "GameStateManager::WindowFocusChanged(...)" );

        if ( win->IsActive() )
            lfm << "Window activated\n";
        else
            lfm << "Window deactivated\n";
    }

    //Update--------------------------------------------------------------------
    void GameStateManager::Update( Real32 elapsedMS )
    {
        if ( !mStates.empty() )
            mStates.back()->Update( elapsedMS );
    }

    //Render--------------------------------------------------------------------
    void GameStateManager::Render()
    {
        if ( !mStates.empty() )
            mStates.back()->Render();
    }

} // namespace PGE
