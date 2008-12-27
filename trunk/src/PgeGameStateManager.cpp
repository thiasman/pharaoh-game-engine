
/*! $Id$
 *  @file   PgeGameStateManager.h
 *  @author Chad M. Draper
 *  @date   May 30, 2008
 *
 */

#include "PgeGameStateManager.h"
#include "PgeBaseWindowSystem.h"

//#include "PgeLogFileManager.h"

namespace PGE
{
    GameStateManager::GameStateManager( GameStateFactory* stateFactory )
        : mStateFactory( StateFactoryPtr( stateFactory ) ),
          mIsClosed( false ),
          mDisplaySize( 1, 1 )
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
        newState->SetID( stateType );

        // Start the game
        StartGame( newState );
    }

    //StartGame-----------------------------------------------------------------
    void GameStateManager::StartGame( BaseGameState* state )
    {
        // Resources need to be setup, input and audio needs to be initialized, etc.

        // Attach the state as an input listener
        InputManager::getSingletonPtr()->AddInputListener( state, state->GetID() );

        // Switch to the first state:
        ChangeState( state );
    }

    //ChangeState---------------------------------------------------------------
    void GameStateManager::ChangeState( const String& stateType )
    {
        // Create the new state
        BaseGameState* newState = mStateFactory->CreateState( stateType );
        newState->SetID( stateType );

        // Change states
        ChangeState( newState );
    }

    //ChangeState---------------------------------------------------------------
    void GameStateManager::ChangeState( BaseGameState* state )
    {
        // Shutdown and remove the active state
        if ( !mStates.empty() )
        {
            // Remove the state as an input listener
            InputManager::getSingletonPtr()->RemoveInputListener( mStates.back()->GetID() );

            // Shutdown the state
            mStates.back()->Destroy();
            mStates.pop_back();
        }

        // Attach the state as an input listener
        InputManager::getSingletonPtr()->AddInputListener( state, state->GetID() );

        // Add the new state to the stack
        mStates.push_back( StatePtr( state ) );

        // Activate the new state
        mStates.back()->Init();

        // Give the state the window size:
        mStates.back()->SetWindowSize( mDisplaySize.x, mDisplaySize.y );
    }

    //PushState-----------------------------------------------------------------
    void GameStateManager::PushState( const String& stateType )
    {
        // Create the new state
        BaseGameState* newState = mStateFactory->CreateState( stateType );
        newState->SetID( stateType );

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

        // Attach the state as an input listener
        InputManager::getSingletonPtr()->AddInputListener( state, state->GetID() );

        // Add the new state to the stack
        mStates.push_back( StatePtr( state ) );

        // Activate the new state
        mStates.back()->Init();

        // Give the state the window size:
        mStates.back()->SetWindowSize( mDisplaySize.x, mDisplaySize.y );
    }

    //PopState------------------------------------------------------------------
    void GameStateManager::PopState()
    {
        // This method is commonly used to resume an application that has been paused.

        // Shutdown and remove the active state
        if ( !mStates.empty() )
        {
            // Remove the state as an input listener
            InputManager::getSingletonPtr()->RemoveInputListener( mStates.back()->GetID() );

            // Shutdown the state
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
        // Get the window metrics:
        int x, y, z, width, height;
        win->GetMetrics( x, y, z, width, height );
        mDisplaySize = Point2D( width, height );

        if ( !mStates.empty() )
            mStates.back()->SetWindowSize( width, height );

        // Resize the mouse's area:
        InputManager::getSingleton().SetWindowSize( width, height );
    }

    //WindowClosed--------------------------------------------------------------
    void GameStateManager::WindowClosed( BaseWindowSystem* win )
    {
        mIsClosed = true;
    }

    //WindowFocusChanged--------------------------------------------------------
    void GameStateManager::WindowFocusChanged( BaseWindowSystem* win )
    {
/*
        LogFileManager& lfm = LogFileManager::GetSingleton();
        LogFileSection sect( lfm.GetDefaultLog(), "GameStateManager::WindowFocusChanged(...)" );

        if ( win->IsActive() )
            lfm << "Window activated\n";
        else
            lfm << "Window deactivated\n";
*/
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

    //keyPressed----------------------------------------------------------------
    bool GameStateManager::KeyPressed( const OIS::KeyEvent& e )
    {
        return true;
    }

    //keyReleased---------------------------------------------------------------
    bool GameStateManager::KeyReleased( const OIS::KeyEvent& e )
    {
        // If the escape key was pressed, quit the application:
        if ( e.key == OIS::KC_ESCAPE )
            mIsClosed = true;

        return true;
    }

} // namespace PGE
