
/*! $Id$
 *  @file   DemoGameStateFactory.h
 *  @author Chad M. Draper
 *  @date   May 30, 2008
 *  @brief  Create game states used by this application.
 *
 */

#ifndef DEMOGAMESTATEFACTORY_H_INCLUDED
#define DEMOGAMESTATEFACTORY_H_INCLUDED

#include "PgeTypes.h"
#include "PgeBaseGameState.h"

// Possible states:
#include "DemoGameState.h"

class DemoGameStateFactory : public PGE::GameStateFactory
{
public:
    /** Create a new game state given the state's type */
    PGE::BaseGameState* CreateState( const PGE::String& type )
    {
        return new DemoGameState();
    }

};

#endif // DEMOGAMESTATEFACTORY_H_INCLUDED
