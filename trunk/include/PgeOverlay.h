
/*! $Id$
 *  @file   PgeOverlay.h
 *  @author Chad M. Draper
 *  @date   April 6, 2009
 *  @brief  Base class for overlays.
 *
 */

#ifndef PGEOVERLAY_H
#define PGEOVERLAY_H

#if ( PGE_PLATFORM == PGE_PLATFORM_WIN32 )
#   include <windows.h>
#endif

#include "PgePlatform.h"
#include "PgeSharedPtr.h"
#include "PgeTypes.h"

#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISJoyStick.h>

namespace PGE
{
    class OverlayElement;

    /** @class Overlay

        The overlay class allows us to render layers on top of the scene.
        Typical uses are for displaying user stats (health, lives remaining,
        etc.)  They may also be used for displaying 3D elements on top of the
        scene, such as the cockpit of an airplane, or the dashboard of a race
        car.  The overlay itself will fill the entire frame, but since it is
        the elements that are rendered, and not the overlay, then only those
        areas that contain an element will have something rendered.

        @par
        Overlays will receive input commands from the overlay manager, but not
        as an input listener.  All input listeners receive every command, so
        that they can do processing as necessary.  It is not desireable for each
        overlay to process every command.  For instance, in a UI situation where
        two elements in separate overlays overlap, we would want a mouse click
        to only affect the top-most element, and others should ignore the click.
        Similarly, keyboard entries should only go to the active element, and
        not to each overlay.

    */
    class _PgeExport Overlay
    {
    protected:
        typedef SharedPtr< OverlayElement >     ElementPtr;
        typedef std::map< String, ElementPtr >  ElementMap;
        ElementMap  mElements;

        String  mActiveElement;     ///< Index of the active element
        bool    mIsVisible;         ///< Indicates if the overlay is currently being rendered
        bool    mAcceptsInput;      ///< Indicates if the overlay accepts input, or if it is for display only

    public:
        /** Constructor */
        Overlay();

        /** IsVisible
            Returns whether the overlay is currently being displayed.
        */
        bool IsVisible() const      { return mIsVisible; }

        /** Show or hide the overlay */
        void Show( bool isVisible ) { mIsVisible = isVisible; }

        /** AcceptsInput
            Returns whether the overlay may accept user input.  This is also
            dependent on whether the overlay is visible, so if the overlay is
            currently hidden, this will return false.
        */
        bool AcceptsInput() const   { return mIsVisible && mAcceptsInput; }

        /** Set the flag to accept or ignore input */
        void AcceptInput( bool accept ) { mAcceptsInput = accept; }

        /** Add an element to the overlay */
        void AddElement( OverlayElement* elem, const String& name );

        /** Get a pointer to a named element */
        OverlayElement* GetElement( const String& name );

        /** Get a pointer to the active element.  If there is no active element,
            then the last element is returned.
        */
        OverlayElement* GetActiveElement();

        /** Render the elements in this overlay */
        void Render();

        /** Key pressed */
        bool KeyPressed( const OIS::KeyEvent& e );
        /** Key released */
        bool KeyReleased( const OIS::KeyEvent& e );

        /** Mouse moved */
        bool MouseMoved( const OIS::MouseEvent& e );
        /** Mouse button pressed */
        bool MousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID id );
        /** Mouse button released */
        bool MouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID id );

        /** Joystick axis moved */
        bool AxisMoved( const OIS::JoyStickEvent& e, int axis );
        /** Joystick pov moved */
        bool PovMoved( const OIS::JoyStickEvent& e, int index );
        /** Joystick 3D vector moved */
        bool Vector3Moved( const OIS::JoyStickEvent& e, int index );
        /** Joystick slider moved */
        bool SliderMoved( const OIS::JoyStickEvent& e, int index );
        /** Joystick button pressed */
        bool ButtonPressed( const OIS::JoyStickEvent& e, int button );
        /** Joystick button released */
        bool ButtonReleased( const OIS::JoyStickEvent& e, int button );

    }; // class Overlay

} // namespace PGE

#endif  // PGEOVERLAY_H
