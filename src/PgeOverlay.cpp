
/*! $Id$
 *  @file   PgeOverlay.cpp
 *  @author Chad M. Draper
 *  @date   April 6, 2009
 *
 */

#include "PgeOverlay.h"
#include "PgeOverlayElement.h"
#include "PgeException.h"
#include "PgeStringUtil.h"

#if PGE_PLATFORM == PGE_PLATFORM_WIN32
#   include <windows.h>
#endif

#include <gl/gl.h>
#include <gl/glu.h>

namespace PGE
{
    //Constructor
    Overlay::Overlay()
        : mIsVisible( false ), mAcceptsInput( false ), mActiveElement( 0 )
    {
    }

    //AddElement
    void Overlay::AddElement( OverlayElement* elem, const String& name )
    {
        // Make sure there isn't already an element with this name
        ElementMap::iterator iter = mElements.find( name );
        if ( iter == mElements.end() )
        {
            mElements[ name ] = ElementPtr( elem );
        }
    }

    //GetElement
    OverlayElement* Overlay::GetElement( const String& name )
    {
        try
        {
            ElementMap::iterator iter = mElements.find( mActiveElement );
            if ( iter == mElements.end() )
                return 0;
            return iter->second.Get();
        }
        catch ( std::exception& e )
        {
            String msg = "Overlay::GetElement: key = " + name + ".";
            throw Exception( msg );
        }
        return 0;
    }

    //GetActiveElement
    OverlayElement* Overlay::GetActiveElement()
    {
        // Attempt to get the active element:
        try
        {
            // Make sure we have some elements:
            if ( mElements.size() == 0 )
                return 0;

            // Make sure the index is valid:
            ElementMap::iterator iter;
            if ( mActiveElement == StringUtil::BLANK )
                iter = mElements.begin();
            else
                iter = mElements.find( mActiveElement );
            if ( iter == mElements.end() )
                return 0;
            return iter->second.Get();
        }
        catch ( std::exception& e )
        {
            String msg = "Overlay::GetActiveElement: key = " + mActiveElement + ".";
            throw Exception( msg );
        }
        return 0;
    }

    void Overlay::Render()
    {
        if ( !IsVisible() )
            return;

        // Push the depth buffer:
        glPushAttrib( GL_DEPTH_BUFFER_BIT );

        // If there are any 3D elements (meaning that the depth buffer is
        // needed), we should clear the depth buffer before rendering.  Otherwise
        // we can simple disable depth testing and enable blending.

        ElementMap::iterator elemIter = mElements.begin();
        for ( elemIter; elemIter != mElements.end(); elemIter++ )
        {
            elemIter->second->Render();
        }

        // Restore the depth buffer:
        glPopAttrib(  );
    }

    //KeyPressed
    bool Overlay::KeyPressed( const OIS::KeyEvent& e )
    {
        // Make sure the overlay can accept input:
        if ( !AcceptsInput() )
            return false;

        // If the key pressed was the 'TAB' key, then cycle through the elements:
        if ( e.key == OIS::KC_TAB )
        {
            //--mActiveElement = ( mActiveElement + 1 ) % mElements.size();
        }

        // Get the active element:
        OverlayElement* activeElem = GetActiveElement();
        if ( activeElem )
        {
            return activeElem->KeyPressed( e );
        }
        return false;
    }

    //KeyReleased
    bool Overlay::KeyReleased( const OIS::KeyEvent& e )
    {
        // Make sure the overlay can accept input:
        if ( !AcceptsInput() )
            return false;

        // Get the active element:
        OverlayElement* activeElem = GetActiveElement();
        if ( activeElem )
        {
            return activeElem->KeyReleased( e );
        }
        return false;
    }

    //MouseMoved
    bool Overlay::MouseMoved( const OIS::MouseEvent& e )
    {
        // Make sure the overlay can accept input:
        if ( !AcceptsInput() )
            return false;

        // Get the active element:
        OverlayElement* activeElem = GetActiveElement();
        if ( activeElem )
        {
            return activeElem->MouseMoved( e );
        }
        return false;
    }

    //MousePressed
    bool Overlay::MousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID id )
    {
        // Make sure the overlay can accept input:
        if ( !AcceptsInput() )
            return false;

        // Iterate over all elements to find the element in which this event
        // occurred.  If it was not in any of the elements, then we don't need
        // to do anything.
        ElementMap::iterator elemIter = mElements.begin();
        for ( elemIter; elemIter != mElements.end(); elemIter++ )
        {
        }
        return false;
    }

    //MouseReleased
    bool Overlay::MouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID id )
    {
        // Make sure the overlay can accept input:
        if ( !AcceptsInput() )
            return false;

        // Get the active element:
        OverlayElement* activeElem = GetActiveElement();
        if ( activeElem )
        {
            return activeElem->MouseReleased( e, id );
        }
        return false;
    }

    //AxisMoved
    bool Overlay::AxisMoved( const OIS::JoyStickEvent& e, int axis )
    {
        // Make sure the overlay can accept input:
        if ( !AcceptsInput() )
            return false;

        // Get the active element:
        OverlayElement* activeElem = GetActiveElement();
        if ( activeElem )
        {
            return activeElem->AxisMoved( e, axis );
        }
        return false;
    }

    //PovMoved
    bool Overlay::PovMoved( const OIS::JoyStickEvent& e, int index )
    {
        // Make sure the overlay can accept input:
        if ( !AcceptsInput() )
            return false;

        // Get the active element:
        OverlayElement* activeElem = GetActiveElement();
        if ( activeElem )
        {
            return activeElem->PovMoved( e, index );
        }
        return false;
    }

    //Vector3Moved
    bool Overlay::Vector3Moved( const OIS::JoyStickEvent& e, int index )
    {
        // Make sure the overlay can accept input:
        if ( !AcceptsInput() )
            return false;

        // Get the active element:
        OverlayElement* activeElem = GetActiveElement();
        if ( activeElem )
        {
            return activeElem->Vector3Moved( e, index );
        }
        return false;
    }

    //SliderMoved
    bool Overlay::SliderMoved( const OIS::JoyStickEvent& e, int index )
    {
        // Make sure the overlay can accept input:
        if ( !AcceptsInput() )
            return false;

        // Get the active element:
        OverlayElement* activeElem = GetActiveElement();
        if ( activeElem )
        {
            return activeElem->SliderMoved( e, index );
        }
        return false;
    }

    //ButtonPressed
    bool Overlay::ButtonPressed( const OIS::JoyStickEvent& e, int button )
    {
        // Make sure the overlay can accept input:
        if ( !AcceptsInput() )
            return false;

        // Iterate over all elements to find the element in which this event
        // occurred.  If it was not in any of the elements, then we don't need
        // to do anything.
        ElementMap::iterator elemIter = mElements.begin();
        for ( elemIter; elemIter != mElements.end(); elemIter++ )
        {
        }
        return false;
    }

    //ButtonReleased
    bool Overlay::ButtonReleased( const OIS::JoyStickEvent& e, int button )
    {
        // Make sure the overlay can accept input:
        if ( !AcceptsInput() )
            return false;

        // Get the active element:
        OverlayElement* activeElem = GetActiveElement();
        if ( activeElem )
        {
            return activeElem->ButtonReleased( e, button );
        }
        return false;
    }

} // namespace PGE
