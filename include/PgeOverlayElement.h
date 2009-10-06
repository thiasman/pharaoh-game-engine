
/*! $Id$
 *  @file   PgeOverlayElement.h
 *  @author Chad M. Draper
 *  @date   April 6, 2009
 *  @brief  Base class for elements that may be placed in an overlay.
 *
 */

#ifndef PGEOVERLAYELEMENT_H
#define PGEOVERLAYELEMENT_H

#if ( PGE_PLATFORM == PGE_PLATFORM_WIN32 )
#   include <windows.h>
#endif

#include "PgePlatform.h"
#include "PgeTypes.h"
#include "PgeRect.h"

#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISJoyStick.h>

namespace PGE
{
    class _PgeExport OverlayElement
    {
    protected:
        bool    mIsVisible;         ///< Indicates if the overlay is currently being rendered
        bool    mAcceptsInput;      ///< Indicates if the overlay accepts input, or if it is for display only
        Rect    mNormalCoords;      /**< Position and size of the element using unit values (0-1).  Note that
                                         this will resize the elements with the display.  An element on a 4:3
                                         monitor will occupy the same percentage of the display as the element
                                         on a 16:9 display, but their aspect ratios will be different.
                                    */

    public:
        /** Constructor */
        OverlayElement();

        /** IsVisible
            Returns whether the overlay is currently being displayed.
        */
        bool IsVisible() const      { return mIsVisible; }

        /** Show or hide the overlay */
        void Show( bool isVisible ) { mIsVisible = isVisible; }

        /** HitTest
            Determine if the normalized point <pre>pt</pre> lies within the
            element.  Note that the points coordinates must be converted to
            unit values prior to calling the hit test.
        */
        virtual bool HitTest( const Point2Df& pt );

        /** AcceptsInput
            Returns whether the overlay may accept user input.  This is also
            dependent on whether the overlay is visible, so if the overlay is
            currently hidden, this will return false.
        */
        bool AcceptsInput() const   { return mIsVisible && mAcceptsInput; }

        /** Set the flag to accept or ignore input */
        void AcceptInput( bool accept ) { mAcceptsInput = accept; }

        /** Render the element */
        virtual void Render();

        /** Key pressed */
        virtual bool KeyPressed( const OIS::KeyEvent& e );
        /** Key released */
        virtual bool KeyReleased( const OIS::KeyEvent& e );

        /** Mouse moved */
        virtual bool MouseMoved( const OIS::MouseEvent& e );
        /** Mouse button pressed */
        virtual bool MousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID id );
        /** Mouse button released */
        virtual bool MouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID id );

        /** Joystick axis moved */
        virtual bool AxisMoved( const OIS::JoyStickEvent& e, int axis );
        /** Joystick pov moved */
        virtual bool PovMoved( const OIS::JoyStickEvent& e, int index );
        /** Joystick 3D vector moved */
        virtual bool Vector3Moved( const OIS::JoyStickEvent& e, int index );
        /** Joystick slider moved */
        virtual bool SliderMoved( const OIS::JoyStickEvent& e, int index );
        /** Joystick button pressed */
        virtual bool ButtonPressed( const OIS::JoyStickEvent& e, int button );
        /** Joystick button released */
        virtual bool ButtonReleased( const OIS::JoyStickEvent& e, int button );

    }; // class OverlayElement

} // namespace PGE

#endif  // PGEOVERLAYELEMENT_H
