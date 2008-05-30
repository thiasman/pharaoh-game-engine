
/*! $Id$
 *  @file   PgeSDLPlatformFactory.cpp
 *  @author Chad M. Draper
 *  @date   May 22, 2008
 *
 */

#include "SDL/PgeSDLPlatformFactory.h"
#include "SDL/PgeSDLWindowSystem.h"

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
