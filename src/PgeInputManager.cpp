
/*! $Id$
 *  @file   PgeInputManager.cpp
 *  @author Chad M. Draper
 *  @date   June 4, 2008
 *
 */

#include "PgeInputManager.h"
#include "PgeBaseInputListener.h"

namespace PGE
{
    // Instantiate the instance
    InputManager* InputManager::mInstance = 0;

    //Constructor---------------------------------------------------------------
    InputManager::InputManager()
        : mOISInputManager( 0 )
    {
        //ctor
    }

    //Destructor----------------------------------------------------------------
    InputManager::~InputManager()
    {
        //delete mOISInputManager;
        delete mInstance;
    }

    //getSingletonPtr-----------------------------------------------------------
    InputManager* InputManager::getSingletonPtr()
    {
        if ( !mInstance )
            mInstance = new InputManager();
        return mInstance;
    }

    //getSingleton--------------------------------------------------------------
    InputManager& InputManager::getSingleton()
    {
        if ( !mInstance )
            mInstance = new InputManager();
        return *mInstance;
    }

    //Capture-------------------------------------------------------------------
    void InputManager::Capture()
    {
        if ( !mKeyboard.IsNull() )
            mKeyboard->capture();
        if ( !mMouse.IsNull() )
            mMouse->capture();
        if ( mJoySticks.size() > 0 )
        {
            mJoyStickIter   = mJoySticks.begin();
            mJoyStickEnd    = mJoySticks.end();
            while ( mJoyStickIter != mJoyStickEnd )
            {
                (*mJoyStickIter)->capture();
                ++mJoyStickIter;
            }
        }
    }

    //SetWindowSize-------------------------------------------------------------
    void InputManager::SetWindowSize( int w, int h )
    {
        assert( !mMouse.IsNull() );
        const OIS::MouseState& mouseState = mMouse->getMouseState();
        mouseState.width = w;
        mouseState.height = h;
    }

    //GetKeyboard---------------------------------------------------------------
    OIS::Keyboard*  InputManager::GetKeyboard() const
    {
        assert( !mKeyboard.IsNull() );
        return mKeyboard.Get();
    }

    //GetMouse------------------------------------------------------------------
    OIS::Mouse*     InputManager::GetMouse() const
    {
        assert( !mMouse.IsNull() );
        return mMouse.Get();
    }

    //GetJoystick---------------------------------------------------------------
    OIS::JoyStick*  InputManager::GetJoystick( unsigned int index ) const
    {
        assert( mJoySticks.size() > index );
        assert( !mJoySticks.at( index ).IsNull() );
        return mJoySticks.at( index ).Get();
    }

    //GetJoystickCount----------------------------------------------------------
    int InputManager::GetJoystickCount() const
    {
        return static_cast<int>( mJoySticks.size() );
    }

    //Init----------------------------------------------------------------------
    void InputManager::Init( size_t winHandle )
    {
        if ( !mOISInputManager )
        {
            //mInputManager = InputManagerPtr( OIS::InputManager::createInputSystem( winHandle ) );
            mOISInputManager = ( OIS::InputManager::createInputSystem( winHandle ) );
            mOISInputManager->enableAddOnFactory( OIS::InputManager::AddOn_All );

            if ( mOISInputManager->getNumberOfDevices( OIS::OISKeyboard ) > 0 )
            {
                mKeyboard = KeyboardPtr( (OIS::Keyboard*)mOISInputManager->createInputObject( OIS::OISKeyboard, true ) );
                mKeyboard->setEventCallback( this );
            }
            if ( mOISInputManager->getNumberOfDevices( OIS::OISMouse ) > 0 )
            {
                mMouse = MousePtr( (OIS::Mouse*)mOISInputManager->createInputObject( OIS::OISMouse, true ) );
                mMouse->setEventCallback( this );
            }
            if ( mOISInputManager->getNumberOfDevices( OIS::OISJoyStick ) > 0 )
            {
                // Resize the joystick array to hold them all
                mJoySticks.resize( mOISInputManager->getNumberOfDevices( OIS::OISJoyStick ) );

                // Create the joysticks
                mJoyStickIter = mJoySticks.begin();
                mJoyStickEnd  = mJoySticks.end();
                while ( mJoyStickIter != mJoyStickEnd )
                {
                    (*mJoyStickIter) = JoyStickPtr( static_cast< OIS::JoyStick* >( mOISInputManager->createInputObject( OIS::OISJoyStick, true ) ) );
                    (*mJoyStickIter)->setEventCallback( this );
                    ++mJoyStickIter;
                }
            }
        }
    }

    //Init----------------------------------------------------------------------
    void InputManager::Init( OIS::ParamList& pl )
    {
        if ( !mOISInputManager )
        {
            //mInputManager = InputManagerPtr( OIS::InputManager::createInputSystem( winHandle ) );
            mOISInputManager = ( OIS::InputManager::createInputSystem( pl ) );
            mOISInputManager->enableAddOnFactory( OIS::InputManager::AddOn_All );

            if ( mOISInputManager->getNumberOfDevices( OIS::OISKeyboard ) > 0 )
            {
                mKeyboard = KeyboardPtr( (OIS::Keyboard*)mOISInputManager->createInputObject( OIS::OISKeyboard, true ) );
                mKeyboard->setEventCallback( this );
            }
            if ( mOISInputManager->getNumberOfDevices( OIS::OISMouse ) > 0 )
            {
                mMouse = MousePtr( (OIS::Mouse*)mOISInputManager->createInputObject( OIS::OISMouse, true ) );
                mMouse->setEventCallback( this );
            }
            if ( mOISInputManager->getNumberOfDevices( OIS::OISJoyStick ) > 0 )
            {
                // Resize the joystick array to hold them all
                mJoySticks.resize( mOISInputManager->getNumberOfDevices( OIS::OISJoyStick ) );

                // Create the joysticks
                mJoyStickIter = mJoySticks.begin();
                mJoyStickEnd  = mJoySticks.end();
                while ( mJoyStickIter != mJoyStickEnd )
                {
                    (*mJoyStickIter) = JoyStickPtr( static_cast< OIS::JoyStick* >( mOISInputManager->createInputObject( OIS::OISJoyStick, true ) ) );
                    (*mJoyStickIter)->setEventCallback( this );
                    ++mJoyStickIter;
                }
            }
        }
    }

    //keyPressed----------------------------------------------------------------
    bool InputManager::keyPressed( const OIS::KeyEvent& e )
    {
        // Dispatch the message to attached listeners
        mListenersEnd = mListeners.end();
        for ( mListenersIter = mListeners.begin(); mListenersIter != mListenersEnd; ++mListenersIter )
        {
            mListenersIter->second->KeyPressed( e );
        }
        return true;
    }
    //keyReleased---------------------------------------------------------------
    bool InputManager::keyReleased( const OIS::KeyEvent& e )
    {
        // Dispatch the message to attached listeners
        mListenersEnd = mListeners.end();
        for ( mListenersIter = mListeners.begin(); mListenersIter != mListenersEnd; ++mListenersIter )
        {
            mListenersIter->second->KeyReleased( e );
        }
        return true;
    }

    //mouseMoved----------------------------------------------------------------
    bool InputManager::mouseMoved( const OIS::MouseEvent& e )
    {
        // Dispatch the message to attached listeners
        mListenersEnd = mListeners.end();
        for ( mListenersIter = mListeners.begin(); mListenersIter != mListenersEnd; ++mListenersIter )
        {
            mListenersIter->second->MouseMoved( e );
        }
        return true;
    }
    //mousePressed--------------------------------------------------------------
    bool InputManager::mousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID id )
    {
        // Dispatch the message to attached listeners
        mListenersEnd = mListeners.end();
        for ( mListenersIter = mListeners.begin(); mListenersIter != mListenersEnd; ++mListenersIter )
        {
            mListenersIter->second->MousePressed( e, id );
        }
        return true;
    }
    //mouseReleased-------------------------------------------------------------
    bool InputManager::mouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID id )
    {
        // Dispatch the message to attached listeners
        mListenersEnd = mListeners.end();
        for ( mListenersIter = mListeners.begin(); mListenersIter != mListenersEnd; ++mListenersIter )
        {
            mListenersIter->second->MouseReleased( e, id );
        }
        return true;
    }

    //axisMoved-----------------------------------------------------------------
    bool InputManager::axisMoved( const OIS::JoyStickEvent& e, int axis )
    {
        // Dispatch the message to attached listeners
        mListenersEnd = mListeners.end();
        for ( mListenersIter = mListeners.begin(); mListenersIter != mListenersEnd; ++mListenersIter )
        {
            mListenersIter->second->AxisMoved( e, axis );
        }
        return true;
    }
    //povMoved------------------------------------------------------------------
    bool InputManager::povMoved( const OIS::JoyStickEvent& e, int index )
    {
        // Dispatch the message to attached listeners
        mListenersEnd = mListeners.end();
        for ( mListenersIter = mListeners.begin(); mListenersIter != mListenersEnd; ++mListenersIter )
        {
            mListenersIter->second->PovMoved( e, index );
        }
        return true;
    }
    //vector3Moved--------------------------------------------------------------
    bool InputManager::vector3Moved( const OIS::JoyStickEvent& e, int index )
    {
        // Dispatch the message to attached listeners
        mListenersEnd = mListeners.end();
        for ( mListenersIter = mListeners.begin(); mListenersIter != mListenersEnd; ++mListenersIter )
        {
            mListenersIter->second->Vector3Moved( e, index );
        }
        return true;
    }
    //sliderMoved---------------------------------------------------------------
    bool InputManager::sliderMoved( const OIS::JoyStickEvent& e, int index )
    {
        // Dispatch the message to attached listeners
        mListenersEnd = mListeners.end();
        for ( mListenersIter = mListeners.begin(); mListenersIter != mListenersEnd; ++mListenersIter )
        {
            mListenersIter->second->SliderMoved( e, index );
        }
        return true;
    }
    //buttonPressed-------------------------------------------------------------
    bool InputManager::buttonPressed( const OIS::JoyStickEvent& e, int button )
    {
        // Dispatch the message to attached listeners
        mListenersEnd = mListeners.end();
        for ( mListenersIter = mListeners.begin(); mListenersIter != mListenersEnd; ++mListenersIter )
        {
            mListenersIter->second->ButtonPressed( e, button );
        }
        return true;
    }
    //buttonReleased------------------------------------------------------------
    bool InputManager::buttonReleased( const OIS::JoyStickEvent& e, int button )
    {
        // Dispatch the message to attached listeners
        mListenersEnd = mListeners.end();
        for ( mListenersIter = mListeners.begin(); mListenersIter != mListenersEnd; ++mListenersIter )
        {
            mListenersIter->second->ButtonReleased( e, button );
        }
        return true;
    }

    //AddInputListener----------------------------------------------------------
    void InputManager::AddInputListener( BaseInputListener* listener, const String& instanceName )
    {
        // Add the listener only if it is not already attached
        mListenersIter = mListeners.find( instanceName );
        if ( mListenersIter == mListeners.end() )
        {
            mListeners[ instanceName ] = listener;
        }
    }

    // RemoveListener-----------------------------------------------------------
    void InputManager::RemoveInputListener( const String& instanceName )
    {
        // Remove the listener only if it exists
        mListenersIter = mListeners.find( instanceName );
        if ( mListenersIter != mListeners.end() )
        {
            mListeners.erase( mListenersIter );
        }
    }

} // namespace PGE
