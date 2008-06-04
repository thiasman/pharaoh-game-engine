
/*! $Id$
 *  @file   PgeGameStateManager.h
 *  @author Chad M. Draper
 *  @date   May 30, 2008
 *  @brief  Manages the game states.
 *
 */

#ifndef PGEGAMESTATEMANAGER_H
#define PGEGAMESTATEMANAGER_H

#include <vector>

#include "PgeTypes.h"
#include "PgeSharedPtr.h"
#include "PgeException.h"
#include "PgeBaseGameState.h"
#include "PgeBaseWindowListener.h"
#include "PgeBaseInputListener.h"
#include "PgeInputManager.h"

#include "cmd/LogFileManager.h"

namespace PGE
{

    /** @class GameStateManager
        A game is made up of one or more states.  For instance, the introduction
        or title sequence is a state, the menu is a state, the game level is a
        state, and the pause screen is a state (to name a few.)  The state
        manager keeps track of what state is active, and passes information
        between the app and the states.

        @remarks
            The game state manager is window listener, and can be added to the
            render window so that it will shut down when the window is closed.

        @remarks
            The game state manager is also derived from BaseInputListener, but
            none of the input event methods are implemented.  This is mostly to
            help with passing input along to the states, but attaching the
            states (also derived from BaseInputListener) as listeners.  However,
            if the state manager is desired to have input handling, simply
            subclass the manager, and implement the methods.
    */
    class _PgeExport GameStateManager : public BaseWindowListener, public BaseInputListener
    {
    public:
        /** Constructor */
        GameStateManager( GameStateFactory* stateFactory );
        /** Destructor */
        virtual ~GameStateManager();

        /** Adds the first state to the manager and activates it, effectively
            starting the game.
        */
        void StartGame( const String& stateType );
        void StartGame( BaseGameState* state );

        /** Remove the currently active state and adds a new state, making it active */
        void ChangeState( const String& stateType );
        /** Remove the currently active state and adds a new state, making it active */
        void ChangeState( BaseGameState* state );

        /** Add a new game state to the list and make it active */
        void PushState( const String& stateType );
        /** Add a new game state to the list and make it active */
        void PushState( BaseGameState* state );

        /** Remove the currently active state */
        void PopState();

        /** Check whether the game is shutting down */
        bool IsClosing()            { return mIsClosed; }

        /** Prepare the frame for rendering after an elapsed period of time.
            This should not actually perform the rendering (that needs to be
            called later.)  Instead, this move objects to their necessary
            positions, updates any AI, etc.
        */
        virtual void Update( Real32 elapsedMS );

        /** Render the current frame. */
        virtual void Render();

        /** === From BaseWindowListener === */

        /** Window has changed size */
        virtual void WindowSizeChanged( BaseWindowSystem* win );

        /** Window has been closed */
        virtual void WindowClosed( BaseWindowSystem* win );

        /** Window has gained or lost focus
            @remarks
                Minimizing the window should also cause a loss of focus.  It is
                up to the client how to deal with this.  That is, if a game
                should be paused whenever the window loses focus, only when
                minimized, or never (as far as window events are concerned.)
                Likewise, restoring a minimized window should cause it to regain
                focus.
        */
        virtual void WindowFocusChanged( BaseWindowSystem* win );

        /** === From BaseInputListener === */

        /** Keyboard key was pressed */
        virtual bool KeyPressed( const OIS::KeyEvent& e );

        /** Keyboard key was released */
        virtual bool KeyReleased( const OIS::KeyEvent& e );

    protected:
        typedef SharedPtr< BaseGameState >    StatePtr;
        typedef SharedPtr< GameStateFactory > StateFactoryPtr;
        StateFactoryPtr mStateFactory;      /**< Factory which generates the application-specific states. */

        bool    mIsClosed;                  /**< Indicates if the game (more specifically, the window) is closed. */

    private:
        std::vector< StatePtr > mStates;
    };

} // namespace PGE

#endif // PGEGAMESTATEMANAGER_H
