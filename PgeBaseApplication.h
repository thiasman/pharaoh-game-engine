
/*! $Id$
 *  @file   PgeBaseApplication.h
 *  @author Chad M. Draper
 *  @date   May 22, 2008
 *  @brief  Base class for the application.
 *
 */

#ifndef PGEBASEAPPLICATION_H
#define PGEBASEAPPLICATION_H

#include "PgeSharedPtr.h"

namespace PGE
{
    class PlatformFactory;

    /** @class BaseApplication
        The application is where the game really gets started.  The main
        function will create the application, passing it a platform factory so
        as to create the platform-dependent classes (such as the window) then
        the application class will take over for the duration of the game.  This
        class may be sub-classed as desired (such as for non-game uses,) but in
        many cases, will be fine as it is, provided all configuration files use
        the default naming scheme.
    */
    class _PgeExport BaseApplication
    {
    public:
        BaseApplication( PlatformFactory* factory );
        virtual ~BaseApplication();

        /** Start the application.  This will enter a loop that will run until
            the user closes the application.  Each iteration of the loop will
            update logic, listen for events, and update the display.
        */
        virtual void Run();

    protected:
        SharedPtr< PlatformFactory >    mPlatformFactory;

    private:
    };

} // namespace PGE

#endif // PGEBASEAPPLICATION_H
