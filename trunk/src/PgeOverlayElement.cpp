
/*! $Id$
 *  @file   PgeOverlayElement.cpp
 *  @author Chad M. Draper
 *  @date   April 6, 2009
 *
 */

#include "PgeOverlayElement.h"

namespace PGE
{
    //Constructor
    OverlayElement::OverlayElement()
        : mIsVisible( true ), mAcceptsInput( true )
    {
    }

    bool OverlayElement::HitTest( const Point2Df& pt )
    {
        if ( pt.x < mNormalCoords.x || pt.y < mNormalCoords.y ||
             pt.x >= mNormalCoords.x + mNormalCoords.width ||
             pt.y >= mNormalCoords.y + mNormalCoords.height )
        {
             return false;
        }
        return true;
    }

    //Render
    void OverlayElement::Render()
    {
    }

    //KeyPressed
    bool OverlayElement::KeyPressed( const OIS::KeyEvent& e )
    {
        return true;
    }

    //KeyReleased
    bool OverlayElement::KeyReleased( const OIS::KeyEvent& e )
    {
        return true;
    }

    //MouseMoved
    bool OverlayElement::MouseMoved( const OIS::MouseEvent& e )
    {
        return true;
    }

    //MousePressed
    bool OverlayElement::MousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID id )
    {
        return true;
    }

    //MouseReleased
    bool OverlayElement::MouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID id )
    {
        return true;
    }

    //AxisMoved
    bool OverlayElement::AxisMoved( const OIS::JoyStickEvent& e, int axis )
    {
        return true;
    }

    //PovMoved
    bool OverlayElement::PovMoved( const OIS::JoyStickEvent& e, int index )
    {
        return true;
    }

    //Vector3Moved
    bool OverlayElement::Vector3Moved( const OIS::JoyStickEvent& e, int index )
    {
        return true;
    }

    //SliderMoved
    bool OverlayElement::SliderMoved( const OIS::JoyStickEvent& e, int index )
    {
        return true;
    }

    //ButtonPressed
    bool OverlayElement::ButtonPressed( const OIS::JoyStickEvent& e, int button )
    {
        return true;
    }

    //ButtonReleased
    bool OverlayElement::ButtonReleased( const OIS::JoyStickEvent& e, int button )
    {
        return true;
    }

} // namespace PGE
