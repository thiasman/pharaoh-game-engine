
/*! $Id$
 *  @file   PgePlatformFactory.h
 *  @author Chad M. Draper
 *  @date   May 22, 2008
 *  @brief  Generates platform-dependent objects.
 *
 */

#ifndef PGEPLATFORMFACTORY_H
#define PGEPLATFORMFACTORY_H

#include "PgePlatform.h"

namespace PGE
{
    class BaseWindowSystem;

    /** @class PlatformFactory
        The platform factory is a class which will generate new platform-
        specific objects.  This includes the window, audio, and networking
        systems.  Note that all returned objects are created on the heap, and
        it is up to the calling class to free the returned object's memory.  It
        is advisable to use a shared pointer for the new object, which will take
        care of cleanup.

        All of the methods here are pure virtual, so they must be implemented in
        the derived class.  However, not all instances will need every object to
        be created (for instance, a layout tool might not need audio or network
        capabilities.)  In these cases, the sub-classed method could return a
        NULL pointer, so it is important to check the validity of the returned
        pointers from the factory.
    */
    class _PgeExport PlatformFactory
    {
    public:
        PlatformFactory();
        virtual ~PlatformFactory();

        /** Create a window system */
        virtual BaseWindowSystem* CreateWindowSystem() const = 0;

    protected:

    private:

    }; // class PlatformFactory

} // namespace PGE

#endif // PGEPLATFORMFACTORY_H
