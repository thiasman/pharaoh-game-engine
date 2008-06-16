
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

#include <gl/gl.h>

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

    /** Keyboard key pressed */
    bool KeyPressed( const OIS::KeyEvent& e );

    /** Keyboard key released */
    bool KeyReleased( const OIS::KeyEvent& e );

    /** Mouse moved */
    virtual bool MouseMoved( const OIS::MouseEvent& e );
    /** Mouse button pressed */
    virtual bool MousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID id );
    /** Mouse button released */
    virtual bool MouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID id );

    /** Joystick axis moved */
    bool AxisMoved( const OIS::JoyStickEvent& e, int axis );
    /** Joystick pov moved */
    bool PovMoved( const OIS::JoyStickEvent& e, int index );
    /** Joystick 3D vector moved */
    bool Vector3Moved( const OIS::JoyStickEvent& e, int index );
    /** Joystick slider moved */
    bool SliderMoved( const OIS::JoyStickEvent& e, int index );
    /** Joystick button pressed */
    bool ButtonPressed( const OIS::JoyStickEvent& e, int button );
    /** Joystick button released */
    bool ButtonReleased( const OIS::JoyStickEvent& e, int button );

    /** Set the position and size of the display */
    void SetWindowSize( PGE::UInt32 w, PGE::UInt32 h );

protected:

private:
    PGE::String  mTextureName;
    GLuint mTexID;

    float   mAngle;
};

#endif // DEMOGAMESTATE_H
