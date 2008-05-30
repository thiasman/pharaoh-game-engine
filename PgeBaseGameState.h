
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
    };

} // namespace PGE

#endif // PGEBASEGAMESTATE_H
