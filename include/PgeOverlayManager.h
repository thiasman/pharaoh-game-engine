
/*! $Id$
 *  @file   PgeOverlayManager.h
 *  @author Chad M. Draper
 *  @date   March 16, 2009
 *  @brief  Keeps track of all overlays used by the current scene.
 *
 */

#ifndef PGEOVERLAYMANAGER_H
#define PGEOVERLAYMANAGER_H

#include "PgeSingleton.h"
#include "PgeBaseInputListener.h"
#include "PgeBaseWindowListener.h"
#include "PgeViewport.h"
#include "PgeRect.h"
#include "PgeSharedPtr.h"

namespace PGE
{
    class Overlay;

    /** @class OverlayManager
        Maintains the overlays connected to the current scene

        The OverlayManager stores the overlays, and handles much of the dirty
        work for dealing with overlays.  It will insure that they are rendered
        in the proper order and pass appropriate input commands to them.

        @par
        In order to insure that the overlays are rendered on top of the scene,
        it is necessary to call the OverlayManager::Render method <em>after</em>
        the rest of the scene has been rendered.

        @par
        An overlay should be listening for input commands, as it may be used for
        GUI controls.  However, because only the active element (in the active
        overlay) should receive input key-stroke input, and the top-most element
        (in the top-most overlay) should receive mouse-clicks, we cannot allow
        the overlays to just receive input commands by themselves.  Instead,
        the OverlayManager will receive the input, then pass it along to the
        appropriate overlay.  For instance, say we have some overlapping windows
        and the user clicks the mouse in an area that is shared by multiple
        windows.  The OverlayManager starts with the top-most overlay, and begins
        iterating over the list.  For each overlay, it will do a HitTest, to
        see if the click is in any of that overlay's elements.  If it was, then
        the click information is sent to that overlay for processing, and we
        can stop iterating.
    */
    class _PgeExport OverlayManager : public BaseWindowListener, public BaseInputListener, public Singleton< OverlayManager >
    {
    protected:
        typedef SharedPtr< Overlay >        OverlayPtr;
        typedef std::map< String, OverlayPtr > OverlayMap;
        OverlayMap  mOverlays;          ///< All overlays
        Viewport    mViewport;          ///< Position and size of the display

        String  mActiveOverlay;         ///< Name of the currently active overlay

        /** Get a pointer to the active overlay */
        Overlay* GetActiveOverlay();

    public:
        OverlayManager(void);
        ~OverlayManager(void);

        /** Override singleton retrieval to avoid link errors */
        static OverlayManager& GetSingleton();
        /** Override singleton pointer retrieval to avoid link errors */
        static OverlayManager* GetSingletonPtr();

        /** Convert a point to unit coordinates (0..1) based on the size of the display */
        Point2Df GetUnitPoint( const Point2Df& pt ) const;
        /** Convert a rect to unit coordinates (0..1) based on the size of the display */
        Viewport GetUnitViewport( const RectF& rect ) const;

        /** Add an overlay to the manager */
        void AddOverlay( Overlay* overlay, const String& overlayName );

        /** Get an overlay by name */
        Overlay* GetOverlay( const String& overlayName );

        /** Render the visible overlays */
        void Render();

        //----------------------------------------------------------------------
        // From BaseWindowListener
        //----------------------------------------------------------------------

        /** Window has changed size */
        void WindowSizeChanged( BaseWindowSystem* win );

        //----------------------------------------------------------------------
        // From BaseInputListener
        //----------------------------------------------------------------------

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

    }; // class OverlayManager

} // namespace PGE

#endif  // PGEOVERLAYMANAGER_H
