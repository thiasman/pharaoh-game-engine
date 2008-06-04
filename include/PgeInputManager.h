
/*! $Id$
 *  @file   PgeInputManager.h
 *  @author Chad M. Draper
 *  @date   June 4, 2008
 *  @brief  Handles input for the application.
 *
 */

#ifndef PGEINPUTMANAGER_H
#define PGEINPUTMANAGER_H

#include <map>

#include "PgePlatform.h"
#include "PgeTypes.h"
#include "PgeSharedPtr.h"

#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISJoyStick.h>
#include <OISInputManager.h>

namespace PGE
{
    class BaseInputListener;

    /** @class InputManager
        Initializes and handles the input for the application.

        @remarks
            The current implementation of the input listener requires OIS,
            available at http://www.sourceforge.net/projects/wgois.  At the
            present time, this is embedded into the core engine, so switching
            input systems will involve a bit more work.  However, the reason for
            using OIS is that it is platform-independent and is actually a
            wrapper for the platform's input system (e.g. DirectInput on Windows.)
            Since the idea of the engine is to allow separating the window
            system, I wanted an input system that wasn't tied to a specific
            window system.  In the future, it might be possible to abstract the
            input so that a project may use it's own system, but for now, OIS
            will suffice.

        @remarks
            The input manager is a singleton, enabling it to be accessed from
            anywhere in the app.  It will be initialized on the first use.

        @remarks
            Input listeners pass input events from the manager to the class that
            is interested in the input (the manager itself can't do much with it.)
            The input manager can pretty much have an unlimited number of
            listeners, and the events will be pumped through all attached
            listeners.
    */
    class _PgeExport InputManager : public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener
    {
    public:
        /** Destructor */
        virtual ~InputManager();

        /** Get a pointer to the input manager instance */
        static InputManager* getSingletonPtr();

        /** Get an instance of the input manager */
        static InputManager& getSingleton();

        /** Initialize the input manager to handle the platform's input
            This <B>MUST</B> be called before the input manager can be used.
        */
        void Init( size_t winHandle );
        /** Initialize the input manager to handle the platform's input
            This <B>MUST</B> be called before the input manager can be used.
        */
        void Init( OIS::ParamList& pl );

        /** Capture the input for the current frame.  This <B>MUST</B> be called
            each frame before input can be checked.
        */
        void Capture();

        /** Set window size.
            @remarks
                The mouse requires the size of the window in order to accurately
                give the mouse coordinates.
        */
        void SetWindowSize( int w, int h );

        /** Get a pointer to the keyboard
            @remarks
                By getting a pointer directly to the keyboard, more direct
                functionality is possible.  This is necessary in order to work
                with unbuffered input.
        */
        OIS::Keyboard*  GetKeyboard() const;

        /** Get a pointer to the mouse
            @remarks
                By getting a pointer directly to the mouse, more direct
                functionality is possible.  This is necessary in order to work
                with unbuffered input.
        */
        OIS::Mouse*     GetMouse() const;

        /** Get a pointer to the joystick
            @param  index       Index of the joystick to retrieve
            @remarks
                By getting a pointer directly to the joystick, more direct
                functionality is possible.  This is necessary in order to work
                with unbuffered input.
        */
        OIS::JoyStick*  GetJoystick( unsigned int index ) const;

        /** Get the number of joysticks attached to the system */
        int GetJoystickCount() const;

        /** Attach an input listener to this listener.  When an event is
            triggered, it will be sent to all attached listeners.
        */
        void AddInputListener( BaseInputListener* listener, const String& instanceName );

        /** Remove an attached listener.  This should be done whenever a listener
            is destroyed so as to avoid sending messages to non-existant objects.
        */
        void RemoveInputListener( const String& instanceName );

    protected:
    private:
        /** Constructor
            @remarks
                The input manager is a singleton, therefore the constructor is
                private, and cannot be instantiated outside this class.
        */
        InputManager();
        InputManager( const InputManager& )     { }
        InputManager& operator=( const InputManager& );

        static InputManager* mInstance;

        //typedef SharedPtr< OIS::InputManager >  InputManagerPtr;
        typedef SharedPtr< OIS::Keyboard >  KeyboardPtr;
        typedef SharedPtr< OIS::Mouse >     MousePtr;
        typedef SharedPtr< OIS::JoyStick >  JoyStickPtr;

        //InputManagerPtr mInputManager;  /**< Active input manager */
        OIS::InputManager* mOISInputManager;
        KeyboardPtr     mKeyboard;      /**< Active keyboard */
        MousePtr        mMouse;         /**< Active mouse */
        std::vector< JoyStickPtr > mJoySticks;  /**< Array of all joysticks attached to the system. */
        std::vector< JoyStickPtr >::iterator    mJoyStickIter;
        std::vector< JoyStickPtr >::iterator    mJoyStickIterEnd;

        /** There can be multiple input listeners attached to the input manager.
            The input manager actually registers itself as a listener to OIS,
            but when an event is triggered, it will iterate over the list of
            attached listeners and send the event along to them.
        */
        std::map< String, BaseInputListener* >              mListeners;
        std::map< String, BaseInputListener* >::iterator    mListenersIter;
        std::map< String, BaseInputListener* >::iterator    mListenersEnd;

    private:
        /** Key pressed */
        bool keyPressed( const OIS::KeyEvent& e );
        /** Key released */
        bool keyReleased( const OIS::KeyEvent& e );

        /** Mouse moved */
        bool mouseMoved( const OIS::MouseEvent& e );
        /** Mouse button pressed */
        bool mousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID id );
        /** Mouse button released */
        bool mouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID id );

        /** Joystick axis moved */
        bool axisMoved( const OIS::JoyStickEvent& e, int axis );
        /** Joystick pov moved */
        bool povMoved( const OIS::JoyStickEvent& e, int index );
        /** Joystick 3D vector moved */
        bool vector3Moved( const OIS::JoyStickEvent& e, int index );
        /** Joystick slider moved */
        bool sliderMoved( const OIS::JoyStickEvent& e, int index );
        /** Joystick button pressed */
        bool buttonPressed( const OIS::JoyStickEvent& e, int button );
        /** Joystick button released */
        bool buttonReleased( const OIS::JoyStickEvent& e, int button );

    };

} // namespace PGE

#endif // PGEINPUTMANAGER_H
