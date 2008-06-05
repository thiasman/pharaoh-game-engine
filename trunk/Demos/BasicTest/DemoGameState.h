
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

    /** Joystick axis moved */
    bool AxisMoved( const OIS::JoyStickEvent& e, int axis )
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
		lfm << e.device->vendor() << ". Axis # " << axis << " Value: " << e.state.mAxes[axis].abs << std::endl;
        return true;
    }
    /** Joystick pov moved */
    bool PovMoved( const OIS::JoyStickEvent& e, int index )
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
		lfm << e.device->vendor() << ". POV " << std::endl;
        return true;
    }
    /** Joystick 3D vector moved */
    bool Vector3Moved( const OIS::JoyStickEvent& e, int index )
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
		lfm << e.device->vendor() << ". Vector3 " << std::endl;
        return true;
    }
    /** Joystick slider moved */
    bool SliderMoved( const OIS::JoyStickEvent& e, int index )
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
		lfm << e.device->vendor() << ". Slider " << std::endl;
        return true;
    }
    /** Joystick button pressed */
    bool ButtonPressed( const OIS::JoyStickEvent& e, int button )
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
		lfm << e.device->vendor() << ". Button Pressed # = " << button << std::endl;
        return true;
    }
    /** Joystick button released */
    bool ButtonReleased( const OIS::JoyStickEvent& e, int button )
    {
        cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
        cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
		lfm << e.device->vendor() << ". Button Released # = " << button << std::endl;
        return true;
    }

protected:

private:
};

#endif // DEMOGAMESTATE_H
