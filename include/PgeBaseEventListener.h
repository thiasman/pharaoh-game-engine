
/*! $Id$
 *  @file   PgeBaseEventListener.cpp
 *  @author Chad M. Draper
 *  @date   May 21, 2008
 *  @brief  Contains the definition of the base listener class.
 *
 */

#ifndef PGEBASELISTENER_H
#define PGEBASELISTENER_H

#include "PgePlatform.h"
#include "PgeTypes.h"
#include "PgeSharedPtr.h"
#include <vector>
#include <map>

namespace PGE
{
    /** @class BaseEvent
        Events fired by the listeners should be derived from this.  Sub-classes
        can provide extra data, for example, a mouse-click event would give the
        location of the click, and a key event would give the ID of the key that
        triggered the event.
    */
    class _PgeExport BaseEvent
    {
    private:
        String      mName;          /**< Name of the event.  Used to distinguish the event type. */

    public:
        /** Default constructor */
        BaseEvent( const String& name );

        /** Get the event name */
        String GetName() const;
    };

    /** @class BaseEventHandler
        Any class that can receive and handle messages should be derived from
        this base class.  The listener will maintain a list of assigned
        potential handlers, and when an event is triggered, send the event along
        to all handlers.  If a specific handler does not care about the event,
        it is ignored.
    */
    class _PgeExport BaseEventHandler
    {
    protected:
        typedef void (*EventHandlerFunc)( const BaseEvent* event );
        std::map< String, EventHandlerFunc >            mHandlerFuncs;
        std::map< String, EventHandlerFunc >::iterator  mHandlerFuncIter;

    public:
        /** Default constructor */
        BaseEventHandler()              { }
        virtual ~BaseEventHandler()     { }

        /** Receive notification from a listener that an event has taken place.
            It is up to the handler to decide whether anything should be done
            with it.
        */
        virtual void HandleEvent( const BaseEvent& event );

    }; // class BaseEventHandler

    /** @class BaseListener
        This class provides the base interface for all listeners.  It should
        be sub-classed as necessary.
    */
    class _PgeExport BaseListener
    {
    private:
        typedef SharedPtr< BaseEventHandler > HandlerPtr;
        std::vector< HandlerPtr > mHandlers;        /**< Vector of potential event handlers */
        std::vector< HandlerPtr >::iterator mHandlerIter;   /**< Iterator for traversing the potential event handlers */

    public:
        /** Default constructor */
        BaseListener();
        virtual ~BaseListener()         { }

        /** Announce to the listener that an event has occurred.  This event
            will then be sent along to all potential handlers.
        */
        virtual void AnnounceEvent( const BaseEvent& event );

    protected:
        /** Alert handlers of a new event. */
        void alertHandlers( const BaseEvent& event );

    }; // class BaseListener

} // namespace PGE

#endif // PGEBASELISTENER_H
