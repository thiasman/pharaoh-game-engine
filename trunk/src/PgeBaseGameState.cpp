
/*! $Id$
 *  @file   PgeBaseGameState.cpp
 *  @author Chad M. Draper
 *  @date   May 30, 2008
 *
 */

#include "PgeBaseGameState.h"
#include "PgeMath.h"

namespace PGE
{
    BaseGameState::BaseGameState()
        : mID( RandomString::GetRandomString( 10 ) )
    {
        //ctor
    }

    BaseGameState::~BaseGameState()
    {
        //dtor
    }

} // namespace PGE
