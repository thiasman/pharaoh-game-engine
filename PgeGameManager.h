
/*! $Id$
 *  @file   PgeGameManager.h
 *  @author Chad M. Draper
 *  @date   May 15, 2008
 *  @brief  Manages the game states.
 *
 */

#ifndef PGEGAMEMANAGER_H
#define PGEGAMEMANAGER_H

#include "PgeSharedPtr.h"
#include "PgeBaseGameEngine.h"
#include "PgeTileEngine.h"

namespace PGE
{
    /** @class GameManager
        Manages the flow of the game states, providing a link between the window
        system and the game.  The manager will handle loading the states, and
        providing interactivity with the user.
    */
    class GameManager
    {
    private:
        typedef SharedPtr< BaseGameEngine >     GameEnginePtr;

        GameEnginePtr       mCurGameEngine;

        TileEngine  mTileEngine;

    public:
        GameManager();
        virtual ~GameManager();

        /** Initialize the manager.  This will load any configuration and get
            the game started.
        */
        void Init();

        /** Prepare the current frame for rendering */
        void PrepareFrame();

        /** Render the current scene, using the currently active state. */
        void RenderFrame();

    protected:

    }; // class GameManager

} // namespace PGE

#endif // PGEGAMEMANAGER_H
