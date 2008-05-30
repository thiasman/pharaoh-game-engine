
/*! $Id$
 *  @file   PgeSDLPlatformFactory.cpp
 *  @author Chad M. Draper
 *  @date   May 22, 2008
 *
 */

#include "PgeSDLPlatformFactory.h"
#include "PgeSDLWindowSystem.h"

namespace PGE
{
    SDLPlatformFactory::SDLPlatformFactory()
    {
        //ctor
    }

    SDLPlatformFactory::~SDLPlatformFactory()
    {
        //dtor
    }

    //CreateWindowSystem--------------------------------------------------------
    BaseWindowSystem* SDLPlatformFactory::CreateWindowSystem() const
    {
        return new SDLWindowSystem();
    }

} // namespace PGE
