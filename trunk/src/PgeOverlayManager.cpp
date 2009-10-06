
/*! $Id$
 *  @file   PgeOverlayManager.cpp
 *  @author Chad M. Draper
 *  @date   March 16, 2009
 *
 */

#include "PgeOverlayManager.h"
#include "PgeOverlay.h"
#include "PgeException.h"
#include "PgeStringUtil.h"
#include "PgeBaseWindowSystem.h"

#include "cmd/LogFileManager.h"

namespace PGE
{

    // Instantiate the singleton instance
    template<> OverlayManager* Singleton< OverlayManager >::mInstance = 0;

    //Constructor
    OverlayManager::OverlayManager(void)
        : mActiveOverlay( StringUtil::BLANK )
    {
    }

    //Destructor
    OverlayManager::~OverlayManager(void)
    {
    }

    //AddOverlay
    void OverlayManager::AddOverlay( Overlay* overlay, const String& overlayName )
    {
        // Make sure there isn't already an overlay with this name
        OverlayMap::iterator iter = mOverlays.find( overlayName );
        if ( iter == mOverlays.end() )
        {
            mOverlays[ overlayName ] = OverlayPtr( overlay );
        }
    }

    //GetOverlay
    Overlay* OverlayManager::GetOverlay( const String& overlayName )
    {
        try
        {
            //OverlayMap::iterator iter = mOverlays.find( mActiveOverlay );
            OverlayMap::iterator iter = mOverlays.find( overlayName );
            if ( iter == mOverlays.end() )
                return 0;
            return iter->second.Get();
        }
        catch ( std::exception& e )
        {
            String msg = "OverlayManager::GetOverlay: key = " + overlayName + ".";
            throw Exception( msg );
        }
        return 0;
    }

    Overlay* OverlayManager::GetActiveOverlay()
    {
        // Attempt to get the active element:
        try
        {
            // Make sure we have some elements:
            if ( mOverlays.size() == 0 )
                return 0;

            // Make sure the index is valid:
            OverlayMap::iterator iter;
            if ( mActiveOverlay == StringUtil::BLANK )
                iter = mOverlays.begin();
            else
                iter = mOverlays.find( mActiveOverlay );
            if ( iter == mOverlays.end() )
                return 0;
            return iter->second.Get();
        }
        catch ( std::exception& e )
        {
            String msg = "OverlayManager::GetActiveOverlay: key = " + mActiveOverlay + ".";
            throw Exception( msg );
        }
        return 0;
    }

    void OverlayManager::Render()
    {
        // Prepare for rendering overlays

        // Render the overlays
        OverlayMap::iterator overlayIter = mOverlays.begin();
        for ( overlayIter; overlayIter != mOverlays.end(); overlayIter++ )
        {
            overlayIter->second->Render();
        }
    }

    //GetSingleton
    OverlayManager& OverlayManager::GetSingleton()
    {
        assert( mInstance );
        return *mInstance;
    }

    //GetSingletonPtr
    OverlayManager* OverlayManager::GetSingletonPtr()
    {
        return mInstance;
    }

    //WindowSizeChanged
    void OverlayManager::WindowSizeChanged( BaseWindowSystem* win )
    {
        int x, y, z, w, h;
        win->GetMetrics( x, y, z, w, h );
        mViewport.SetPosition( x, y );
        mViewport.SetSize( w, h );
    }

    //KeyPressed
    bool OverlayManager::KeyPressed( const OIS::KeyEvent& e )
    {
        // Get the active element:
        Overlay* active = GetActiveOverlay();
        if ( active )
        {
            return active->KeyPressed( e );
        }
        return false;
    }

    //KeyReleased
    bool OverlayManager::KeyReleased( const OIS::KeyEvent& e )
    {
        // Get the active element:
        Overlay* active = GetActiveOverlay();
        if ( active )
        {
            return active->KeyReleased( e );
        }
        return false;
    }

    //MouseMoved
    bool OverlayManager::MouseMoved( const OIS::MouseEvent& e )
    {
        // Get the active element:
        Overlay* active = GetActiveOverlay();
        if ( active )
        {
            return active->MouseMoved( e );
        }
        return false;
    }

    //MousePressed
    bool OverlayManager::MousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID id )
    {
        // Iterate over all elements to find the element in which this event
        // occurred.  If it was not in any of the elements, then we don't need
        // to do anything.
        OverlayMap::iterator overlayIter = mOverlays.begin();
        for ( overlayIter; overlayIter != mOverlays.end(); overlayIter++ )
        {
        }
        return false;

        //// Get the active element:
        //Overlay* active = GetActiveOverlay();
        //if ( active )
        //{
        //    return active->MousePressed( e, id );
        //}
        //return false;
    }

    //MouseReleased
    bool OverlayManager::MouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID id )
    {
        // Get the active element:
        Overlay* active = GetActiveOverlay();
        if ( active )
        {
            return active->MouseReleased( e, id );
        }
        return false;
    }

    //AxisMoved
    bool OverlayManager::AxisMoved( const OIS::JoyStickEvent& e, int axis )
    {
        // Get the active element:
        Overlay* active = GetActiveOverlay();
        if ( active )
        {
            return active->AxisMoved( e, axis );
        }
        return false;
    }

    //PovMoved
    bool OverlayManager::PovMoved( const OIS::JoyStickEvent& e, int index )
    {
        // Get the active element:
        Overlay* active = GetActiveOverlay();
        if ( active )
        {
            return active->PovMoved( e, index );
        }
        return false;
    }

    //Vector3Moved
    bool OverlayManager::Vector3Moved( const OIS::JoyStickEvent& e, int index )
    {
        // Get the active element:
        Overlay* active = GetActiveOverlay();
        if ( active )
        {
            return active->Vector3Moved( e, index );
        }
        return false;
    }

    //SliderMoved
    bool OverlayManager::SliderMoved( const OIS::JoyStickEvent& e, int index )
    {
        // Get the active element:
        Overlay* active = GetActiveOverlay();
        if ( active )
        {
            return active->SliderMoved( e, index );
        }
        return false;
    }

    //ButtonPressed
    bool OverlayManager::ButtonPressed( const OIS::JoyStickEvent& e, int button )
    {
        // Iterate over all elements to find the element in which this event
        // occurred.  If it was not in any of the elements, then we don't need
        // to do anything.
        OverlayMap::iterator overlayIter = mOverlays.begin();
        for ( overlayIter; overlayIter != mOverlays.end(); overlayIter++ )
        {
        }
        return false;
    }

    //ButtonReleased
    bool OverlayManager::ButtonReleased( const OIS::JoyStickEvent& e, int button )
    {
        // Get the active element:
        Overlay* active = GetActiveOverlay();
        if ( active )
        {
            return active->PovMoved( e, button );
        }
        return false;
    }

} // namespace PGE
