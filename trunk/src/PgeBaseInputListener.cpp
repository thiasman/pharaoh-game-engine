
/*! $Id$
 *  @file   PgeBaseInputListener.h
 *  @author Chad M. Draper
 *  @date   June 2, 2008
 *
 */

#include "PgeBaseInputListener.h"

namespace PGE
{

    //Constructor---------------------------------------------------------------
    BaseInputListener::BaseInputListener()
        : mInputManager( 0 )
    {
    }

    //Constructor---------------------------------------------------------------
    BaseInputListener::BaseInputListener(size_t winHandle)
    {
        //ctor
        Init( winHandle );
    }

    //Destructor----------------------------------------------------------------
    BaseInputListener::~BaseInputListener()
    {
        //dtor
//        if ( !mInputManager.IsNull() )
//            OIS::InputManager::destroyInputSystem( mInputManager.Get() );
        if ( mInputManager )
            OIS::InputManager::destroyInputSystem( mInputManager );
    }

    //Capture-------------------------------------------------------------------
    void BaseInputListener::Capture()
    {
        if ( !mKeyboard.IsNull() )
            mKeyboard->capture();
        if ( !mMouse.IsNull() )
            mMouse->capture();
        if ( mJoySticks.size() > 0 )
        {
            mJoyStickIter       = mJoySticks.begin();
            mJoyStickIterEnd    = mJoySticks.end();
            while ( mJoyStickIter != mJoyStickIterEnd )
            {
                (*mJoyStickIter)->capture();
                ++mJoyStickIter;
            }
        }
    }

    //SetWindowSize-------------------------------------------------------------
    void BaseInputListener::SetWindowSize( int w, int h )
    {
        const OIS::MouseState mouseState = mMouse->getMouseState();
        mouseState.width = w;
        mouseState.height = h;
    }

    //GetKeyboard---------------------------------------------------------------
    OIS::Keyboard*  BaseInputListener::GetKeyboard() const
    {
        assert( !mKeyboard.IsNull() );
        return mKeyboard.Get();
    }

    //GetMouse------------------------------------------------------------------
    OIS::Mouse*     BaseInputListener::GetMouse() const
    {
        assert( !mMouse.IsNull() );
        return mMouse.Get();
    }

    //GetJoystick---------------------------------------------------------------
    OIS::JoyStick*  BaseInputListener::GetJoystick( unsigned int index ) const
    {
        assert( mJoySticks.size() <= index );
        assert( !mJoySticks.at( index ).IsNull() );
        return mJoySticks.at( index ).Get();
    }

    //GetJoystickCount----------------------------------------------------------
    int BaseInputListener::GetJoystickCount() const
    {
        return static_cast<int>( mJoySticks.size() );
    }

    //Init---------------------------------------------------------------
    void BaseInputListener::Init( size_t winHandle )
    {
        //mInputManager = InputManagerPtr( OIS::InputManager::createInputSystem( winHandle ) );
        mInputManager = ( OIS::InputManager::createInputSystem( winHandle ) );
        mInputManager->enableAddOnFactory( OIS::InputManager::AddOn_All );

        mKeyboard = KeyboardPtr( (OIS::Keyboard*)mInputManager->createInputObject( OIS::OISKeyboard, true ) );
        mKeyboard->setEventCallback( this );

        mMouse = MousePtr( (OIS::Mouse*)mInputManager->createInputObject( OIS::OISMouse, true ) );
        mMouse->setEventCallback( this );
    }

    //Init---------------------------------------------------------------
    void BaseInputListener::Init( OIS::ParamList& pl )
    {
        //mInputManager = InputManagerPtr( OIS::InputManager::createInputSystem( winHandle ) );
        mInputManager = ( OIS::InputManager::createInputSystem( pl ) );
        mInputManager->enableAddOnFactory( OIS::InputManager::AddOn_All );

        mKeyboard = KeyboardPtr( (OIS::Keyboard*)mInputManager->createInputObject( OIS::OISKeyboard, true ) );
        mKeyboard->setEventCallback( this );

        mMouse = MousePtr( (OIS::Mouse*)mInputManager->createInputObject( OIS::OISMouse, true ) );
        mMouse->setEventCallback( this );
    }

} // namespace PGE
