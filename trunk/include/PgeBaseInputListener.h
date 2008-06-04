
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

        @remarks
            Subclass the base input listener in order to receive input events
            directly in a class.  If using unbuffered input, it will be
            necessary to query the device state directly from the input manager,
            like so:
                <code>
                OIS::Keyboard* kbd = InputManager::getSingleton().GetKeyboard();<BR>
                if ( kbd->isKeyDown( KC_ESCAPE ) )<BR>
                    exit(0);<BR>
                </code>

        @remarks
            OIS provides methods for getting information about an event, such as
            getting the text representation of a key press.  These require
            getting a pointer to the device, similar to the example of using
            unbuffered input above.

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
    */
    class BaseInputListener
    {
    public:
        /** Destructor */
        virtual ~BaseInputListener();

        /** Key pressed */
        virtual bool KeyPressed( const OIS::KeyEvent& e )                             { return true; }
        /** Key released */
        virtual bool KeyReleased( const OIS::KeyEvent& e )                            { return true; }

        /** Mouse moved */
        virtual bool MouseMoved( const OIS::MouseEvent& e )                           { return true; }
        /** Mouse button pressed */
        virtual bool MousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID id )  { return true; }
        /** Mouse button released */
        virtual bool MouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID id ) { return true; }

        /** Joystick axis moved */
        virtual bool AxisMoved( const OIS::JoyStickEvent& e, int axis )               { return true; }
        /** Joystick pov moved */
        virtual bool PovMoved( const OIS::JoyStickEvent& e, int index )               { return true; }
        /** Joystick 3D vector moved */
        virtual bool Vector3Moved( const OIS::JoyStickEvent& e, int index )           { return true; }
        /** Joystick slider moved */
        virtual bool SliderMoved( const OIS::JoyStickEvent& e, int index )            { return true; }
        /** Joystick button pressed */
        virtual bool ButtonPressed( const OIS::JoyStickEvent& e, int button )         { return true; }
        /** Joystick button released */
        virtual bool ButtonReleased( const OIS::JoyStickEvent& e, int button )        { return true; }

    protected:

    private:

    }; // class BaseInputListener

} // namespace PGE

#endif // PGEBASEINPUTLISTENER_H
