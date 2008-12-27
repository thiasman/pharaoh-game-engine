
/*! $Id$
 *  @file   PgeResourceManager.h
 *  @author Chad M. Draper
 *  @date   November 3, 2008
 *  @brief  Keeps a record of resources available to the application.
 *
 */

#ifndef PGERESOURCEMANAGER_H
#define PGERESOURCEMANAGER_H

#include "PgeTypes.h"
#include "PgeSingleton.h"

namespace PGE
{
    /** @class ResourceManager
        The resource manager keeps track of resource "files" that may be
        accessed by the application.  These may be in a directory, a zip archive,
        or
    */
    class ResourceManager : public Singleton< TextureManager >
    {
    public:
        ResourceManager();
        virtual ~ResourceManager();
    };

} // namespace PGE

#endif // PGERESOURCEMANAGER_H
