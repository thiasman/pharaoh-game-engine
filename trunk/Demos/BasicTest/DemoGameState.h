
/*! $
 *  @file
 *  @author
 *  @date
 *  @brief
 *
 */

#ifndef DEMOGAMESTATE_H
#define DEMOGAMESTATE_H

#include "PgePlatform.h"
#include "PgeTypes.h"
#include "PgeBaseGameState.h"

#include "cmd/LogFileManager.h"

class DemoGameState : public PGE::BaseGameState
{
public:
    DemoGameState();
    virtual ~DemoGameState();

    /** Initialize the game state.  This is where any loading of config
        files or creation of objects should occur.
    */
    virtual void Init();

    /** Destroy the state, releasing any allocated memory. */
    virtual void Destroy();

    /** Pause the game state */
    virtual void Pause();

    /** Resume (unpause) */
    virtual void Resume();

    /** Prepare the frame for rendering after an elapsed period of time.
        This should not actually perform the rendering (that needs to be
        called later.)  Instead, this move objects to their necessary
        positions, updates any AI, etc.
    */
    virtual void Update( PGE::Real32 elapsedMS );

    /** Render the current frame. */
    virtual void Render();

    //keyPressed----------------------------------------------------------------
    bool KeyPressed( const OIS::KeyEvent& e )
    {
        return true;
    }

    //keyReleased---------------------------------------------------------------
    bool KeyReleased( const OIS::KeyEvent& e )
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
        lfm << "Key: " << e.key << ", " << ((OIS::Keyboard*)(e.device))->getAsString(e.key) << ", Character = " << (char)e.text << std::endl;

        return true;
    }

protected:

private:
};

#endif // DEMOGAMESTATE_H
