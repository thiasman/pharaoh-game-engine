
/*! $Id$
 *  @file   PgeBaseInputListener.h
 *  @author Chad M. Draper
 *  @date   June 2, 2008
 *  @brief  Base listener for input.  Sub-class this in order to receive input
 *          via events.
 *
 */

#ifndef PGEBASEINPUTLISTENER_H
#define PGEBASEINPUTLISTENER_H

#include <vector>

#include "PgePlatform.h"
#include "PgeTypes.h"
#include "PgeSharedPtr.h"

#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISJoyStick.h>
#include <OISInputManager.h>

namespace PGE
{
    /** @class BaseInputListener
        The base input listener will initialize the input system, and receive
        callbacks for input events, when using buffered input.  For unbuffered
        input, it will allow checking the state of keys, buttons, axes, etc.

        @remarks
            Subclass the base input listener in order to receive input events
            directly in a class.  If using unbuffered input, create an input
            listener object, and use that to check the state of the input.  It
            might be desireable to create a subclass that is a singleton when
            using unbuffered input, so that the input manager will only need to
            be created once.

        @remarks
            The current implementation of the input listener requires OIS,
            available at http://www.sourceforge.net/projects/wgois.  At the
            present time, this is embedded into the core engine, so switching
            input systems will involve a bit more work.  However, the reason for
            using OIS is that it is platform-independent and is actually a
            wrapper for the platform's input system (e.g. DirecInput on Windows.)
            Since the idea of the engine is to allow separating the window
            system, I wanted an input system that wasn't tied to a specific
            window system.  In the future, it might be possible to abstract the
            input so that a project may use it's own system, but for now, OIS
            will suffice.
    */
    class BaseInputListener : public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener
    {
    public:
        /** Default constructor */
        BaseInputListener();
        /** Constructor */
        BaseInputListener(size_t winHandle);
        /** Destructor */
        virtual ~BaseInputListener();

        /** Capture the input for the current frame.  This <B>MUST</B> be called
            each frame before checking input.
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

        virtual bool keyPressed( const OIS::KeyEvent& e )       { return true; }
        virtual bool keyReleased( const OIS::KeyEvent& e )      { return true; }

        virtual bool mouseMoved( const OIS::MouseEvent& e )     { return true; }
        virtual bool mousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID id )   { return true; }
        virtual bool mouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID id )  { return true; }

        virtual bool axisMoved( const OIS::JoyStickEvent& e, int axis )         { return true; }
        virtual bool posMoved( const OIS::JoyStickEvent& e, int index )         { return true; }
        virtual bool vector3Moved( const OIS::JoyStickEvent& e, int index )     { return true; }
        virtual bool sliderMoved( const OIS::JoyStickEvent& e, int index )      { return true; }
        virtual bool buttonPressed( const OIS::JoyStickEvent& e, int button )   { return true; }
        virtual bool buttonReleased( const OIS::JoyStickEvent& e, int button )  { return true; }

    protected:
        /** Initialize the input listener to handle the platform's input */
        void Init( size_t winHandle );
        /** Initialize the input listener to handle the platform's input */
        void Init( OIS::ParamList& pl );

    private:
        //typedef SharedPtr< OIS::InputManager >  InputManagerPtr;
        typedef SharedPtr< OIS::Keyboard >  KeyboardPtr;
        typedef SharedPtr< OIS::Mouse >     MousePtr;
        typedef SharedPtr< OIS::JoyStick >  JoyStickPtr;

        //InputManagerPtr mInputManager;  /**< Active input manager */
        OIS::InputManager* mInputManager;
        KeyboardPtr     mKeyboard;      /**< Active keyboard */
        MousePtr        mMouse;         /**< Active mouse */
        std::vector< JoyStickPtr > mJoySticks;  /**< Array of all joysticks attached to the system. */
        std::vector< JoyStickPtr >::iterator    mJoyStickIter;
        std::vector< JoyStickPtr >::iterator    mJoyStickIterEnd;

    }; // class BaseInputListener

} // namespace PGE

#endif // PGEBASEINPUTLISTENER_H
