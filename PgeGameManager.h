
/*! $
 *  @file
 *  @author
 *  @date
 *  @brief
 *
 */

#ifndef PGEGAMEMANAGER_H
#define PGEGAMEMANAGER_H

#include "PgeSharedPtr.h"
#include "PgeBaseGameEngine.h"
#include "PgeBaseWindowSystem.h"

namespace PGE
{
    class GameManager
    {
    private:
        typedef SharedPtr< BaseGameEngine >     GameEnginePtr;
        typedef SharedPtr< BaseWindowSystem >   WindowSystemPtr;

        GameEnginePtr       mCurGameEngine;
        WindowSystemPtr     mWindowSystem;

    public:
        GameManager( BaseWindowSystem* windowSys );
        virtual ~GameManager();
    protected:

    }; // class GameManager

} // namespace PGE

#endif // PGEGAMEMANAGER_H
