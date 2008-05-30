
/*! $Id$
 *  @file   PgeBaseEventListener.cpp
 *  @author Chad M. Draper
 *  @date   May 21, 2008
 *
 */

#include "PgeBaseEventListener.h"

namespace PGE
{
    ////////////////////////////////////////////////////////////////////////////
    // BaseEvent
    ////////////////////////////////////////////////////////////////////////////

    //Constructor---------------------------------------------------------------
    BaseEvent::BaseEvent( const String& name )
        : mName( name )
    {
    }

    //GetName-------------------------------------------------------------------
    String BaseEvent::GetName() const
    {
        return mName;
    }

    ////////////////////////////////////////////////////////////////////////////
    // BaseEventHandler
    ////////////////////////////////////////////////////////////////////////////

    //HandleEvent---------------------------------------------------------------
    void BaseEventHandler::HandleEvent( const BaseEvent& event )
    {
        // If the event has a handler, call the handler to process the event
        mHandlerFuncIter = mHandlerFuncs.find( event.GetName() );
        if ( mHandlerFuncIter != mHandlerFuncs.end() )
        {
            (*mHandlerFuncIter->second)( &event );
        }
    }


    ////////////////////////////////////////////////////////////////////////////
    // BaseListener
    ////////////////////////////////////////////////////////////////////////////

    // Constructor--------------------------------------------------------------
    BaseListener::BaseListener()
    {
    }

    //AnnounceEvent-------------------------------------------------------------
    void BaseListener::AnnounceEvent( const BaseEvent& event )
    {
        alertHandlers( event );
    }

    //alertHandlers-------------------------------------------------------------
    void BaseListener::alertHandlers( const BaseEvent& event )
    {
        // Iterate over the list of potential handlers, and pass the event on to
        // them for processing.
        for ( mHandlerIter = mHandlers.begin(); mHandlerIter != mHandlers.end(); mHandlerIter++ )
        {
            (*mHandlerIter)->HandleEvent( event );
        }
    }
}
