
/*! $Id$
 *  @file   PgeBaseWindowListener.h
 *  @author Chad M. Draper
 *  @date   May 29, 2008
 *  @brief  Base class listening to windows events.
 *
 */

#ifndef PGEBASEWINDOWLISTENER_H
#define PGEBASEWINDOWLISTENER_H


namespace PGE
{
    // Forward declaration of the window system
    class BaseWindowSystem;

    /** @class BaseWindowListener
        @remarks
            Class used to convey messages from a window system to the client.

            To use this class, the window listener object <B>MUST</B> be
            attached to the window system.  The window system will dispatch
            events to the listener, which can then pass them along to the client.

            As an example, let's say changes in the window size are important to
            the application.  The base application will derive from
            BaseWindowListener (among other listeners) and implement the
            SizeChanged(...) method.  Since the application class will have
            created the window, it then attaches itself as a listener.  In the
            window system class's message pump, it should look for the size
            changed event, and call the listener's SizeChanged(...) method.
            This calls the application's SizeChanged(...) method, and the
            application can do with it as it pleases.  For example, it might
            pass it on to the current rendering state so that it can resize the
            display, and it might notify the mouse listener so it can resize the
            mouse's area.

        @note
            The callback methods in the listener all take a pointer to the
            window sending the event (i.e. the window passes itself as a
            parameter.)  This allows the client to query whatever information
            it needs from that window.
    */
    class _PgeExport BaseWindowListener
    {
    public:
        virtual ~BaseWindowListener()   { }

        /** Window has changed size */
        virtual void WindowSizeChanged( BaseWindowSystem* win )     { }

        /** Window position has changed */
        virtual void WindowPosChanged( BaseWindowSystem* win )      { }

        /** Window has been closed */
        virtual void WindowClosed( BaseWindowSystem* win )          { }

        /** Window has gained or lost focus
            @remarks
                Minimizing the window should also cause a loss of focus.  It is
                up to the client how to deal with this.  That is, if a game
                should be paused whenever the window loses focus, only when
                minimized, or never (as far as window events are concerned.)
                Likewise, restoring a minimized window should cause it to regain
                focus.
        */
        virtual void WindowFocusChanged( BaseWindowSystem* win )    { }

    protected:
    private:
    };

} // namespace PGE

#endif // PGEBASEWINDOWLISTENER_H
