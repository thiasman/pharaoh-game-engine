
/*! $Id$
 *  @file   PgeBaseApplication.h
 *  @author Chad M. Draper
 *  @date   May 22, 2008
 *  @brief  Base class for the application.
 *
 */

#ifndef PGEBASEAPPLICATION_H
#define PGEBASEAPPLICATION_H

#include "PgeSharedPtr.h"
#include "PgeBaseWindowListener.h"
#include "PgeBaseInputListener.h"
#include "PgeInputManager.h"
#include "PgeTimer.h"

namespace PGE
{
    class PlatformFactory;
    class BaseWindowSystem;

    /** @class BaseApplication
        The application is where the game really gets started.  The main
        function will create the application, passing it a platform factory so
        as to create the platform-dependent classes (such as the window) then
        the application class will take over for the duration of the game.  This
        class may be sub-classed as desired (such as for non-game uses,) but in
        many cases, will be fine as it is, provided all configuration files use
        the default naming scheme.

        @remarks
            The class is derived from BaseInputListener, but no input event
            methods are handled.  In order to process input events, the class
            should be subclassed, and the events should be handled there.
    */
    class _PgeExport BaseApplication : public BaseWindowListener, public BaseInputListener
    {
    public:
        BaseApplication( PlatformFactory* factory );
        virtual ~BaseApplication();

        /** Initialize the application.  This is where the window will be
            created.
        */
        void Init();

        /** Start the application.  This will enter a loop that will run until
            the user closes the application.  Each iteration of the loop will
            update logic, listen for events, and update the display.
        */
        virtual void Run();

        ////////////////////////////////////////////////////////////////////////
        // Inherited from BaseWindowListener
        ////////////////////////////////////////////////////////////////////////

        /** Window has changed size */
        virtual void WindowSizeChanged( BaseWindowSystem* win );

        /** Window has been closed */
        virtual void WindowClosed( BaseWindowSystem* win );

        /** Window has gained or lost focus
            @remarks
                Minimizing the window should also cause a loss of focus.  It is
                up to the client how to deal with this.  That is, if a game
                should be paused whenever the window loses focus, only when
                minimized, or never (as far as window events are concerned.)
                Likewise, restoring a minimized window should cause it to regain
                focus.
        */
        virtual void WindowFocusChanged( BaseWindowSystem* win );

    protected:
        SharedPtr< PlatformFactory >    mPlatformFactory;
        SharedPtr< BaseWindowSystem >   mWindow;
        //SharedPtr< BaseWindowListener > mWindowListener;

        Timer           mTimer;         /**< Timer used by the application.  Individual states may use additional timers. */
        size_t          mWindowHandle;  /**< Id of the window associated with this app. */

        /** Perform additional initialization for the application-specific
            case.
        */
        virtual void AdditionalInit()   { }

    private:
        /** Create the window */
        void _createWindow();
    };

} // namespace PGE

#endif // PGEBASEAPPLICATION_H
