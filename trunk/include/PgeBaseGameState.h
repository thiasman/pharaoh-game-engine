
/*! $Id$
 *  @file   PgeBaseGameState.h
 *  @author Chad M. Draper
 *  @date   May 30, 2008
 *  @brief  Base class for the game states
 *
 */

#ifndef PGEBASEGAMESTATE_H
#define PGEBASEGAMESTATE_H

#include "PgePlatform.h"
#include "PgeTypes.h"

namespace PGE
{
    /** @class BaseGameState
        Every state in the game will derive from BaseGameState.  This is used
        for rendering the currently active portion of the game.
    */
    class BaseGameState
    {
    public:
        BaseGameState();
        virtual ~BaseGameState();

        /** Initialize the game state.  This is where any loading of config
            files or creation of objects should occur.
        */
        virtual void Init() = 0;

        /** Destroy the state, releasing any allocated memory. */
        virtual void Destroy() = 0;

        /** Pause the game state */
        virtual void Pause()        { }

        /** Resume (unpause) */
        virtual void Resume()       { }

        /** Prepare the frame for rendering after an elapsed period of time.
            This should not actually perform the rendering (that needs to be
            called later.)  Instead, this move objects to their necessary
            positions, updates any AI, etc.
        */
        virtual void Update( Real32 elapsedMS ) = 0;

        /** Render the current frame. */
        virtual void Render() = 0;

    protected:
    private:

    }; // class BaseGameState

    /** @class GameStateFactory
        @remarks
            Game states will be application-dependent, and therefore, unknown
            until run-time.  The game state factory will take care of creating
            a state for the game state manager, by allowing the state to be
            created from a name string.  A game configuration file could define
            the state with a type, such as PAUSE, which will be passed through
            to this factory to create a new pause state.
    */
    class GameStateFactory
    {
    public:
        /** Constructory */
        GameStateFactory()              { }
        /** Destructor */
        virtual ~GameStateFactory()     { }

        /** Create a new game state given the state's type */
        virtual BaseGameState* CreateState( const String& type ) = 0;

    }; // class GameStateFactory
} // namespace PGE

#endif // PGEBASEGAMESTATE_H
