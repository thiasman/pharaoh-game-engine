
/*! $Id$
 *  @file   PgeSDLPlatformFactory.h
 *  @author Chad M. Draper
 *  @date   May 22, 2008
 *  @brief  Generates SDL-specific objects
 *
 */

#ifndef PGESDLPLATFORMFACTORY_H
#define PGESDLPLATFORMFACTORY_H

#include "../PgePlatformFactory.h"

namespace PGE
{
    class BaseWindowSystem;

    /** @class SDLPlatformFactory
        The SDL platform factory generates the platform-specific objects for
        using SDL.
    */
    class SDLPlatformFactory : public PlatformFactory
    {
    public:
        SDLPlatformFactory();
        virtual ~SDLPlatformFactory();

        /** Create a window system */
        BaseWindowSystem* CreateWindowSystem() const;

    protected:
    private:
    };

} // namespace PGE

#endif // PGESDLPLATFORMFACTORY_H
