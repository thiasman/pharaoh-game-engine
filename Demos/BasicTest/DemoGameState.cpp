
/*! $
 *  @file
 *  @author
 *  @date
 *
 */

#include "DemoGameState.h"
#include "PgeAudioManager.h"
#include "PgeTextureManager.h"

#include <gl/gl.h>
#include <gl/glu.h>
#include <il/il.h>
#include <il/ilu.h>

DemoGameState::DemoGameState()
    : PGE::BaseGameState(),
      mTextureName( "media/puppies.jpg" )
{
    //ctor
}

DemoGameState::~DemoGameState()
{
    //dtor
}

void DemoGameState::Init()
{
    glEnable( GL_TEXTURE_2D );

    // Set the background color:
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    // Set the size of the viewport:
    //glViewport( 0, 0, 1, 1 );

    // Clear the display:
    glClear( GL_COLOR_BUFFER_BIT );

    // Reset the projection matrix, and set it for orthographic display:
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glOrtho( 0.0f, static_cast<float>( mWidth ), static_cast<float>( mHeight ), 0.0f, -1.0f, 1.0f );
    glOrtho( -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f );

    // Reset the modelview matrix:
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    PGE::TextureManager::GetSingleton().LoadImage( mTextureName );
}

void DemoGameState::Destroy()
{
}

void DemoGameState::Pause()
{
}

void DemoGameState::Resume()
{
}

void DemoGameState::Update( PGE::Real32 elapsedMS )
{
    glClear( GL_COLOR_BUFFER_BIT );
    glRotatef( elapsedMS * 360.0f / 2000.0f, 0.0f, 0.0f, 1.0f );
}

void DemoGameState::Render()
{
    PGE::TextureItem* texItem = PGE::TextureManager::GetSingleton().GetTextureItemPtr( mTextureName );
    PGE::UInt32 texID = texItem->GetID();
    glBindTexture( GL_TEXTURE_2D, texID );
    glBegin( GL_QUADS );

        glTexCoord2i( 0, 0 );
        glColor3f( 1.0f, 0.0f, 0.0f );
        glVertex2f( -0.5f, -0.5f );

        glTexCoord2i( 1, 0 );
        glColor3f( 0.0f, 1.0f, 0.0f );
        glVertex2f( 0.5f, -0.5f );

        glTexCoord2i( 1, 1 );
        glColor3f( 0.0f, 0.0f, 1.0f );
        glVertex2f( 0.5f, 0.5f );

        glTexCoord2i( 0, 1 );
        glColor3f( 1.0f, 1.0f, 1.0f );
        glVertex2f( -0.5f, 0.5f );

    glEnd();
}

/** Keyboard key pressed */
bool DemoGameState::KeyPressed( const OIS::KeyEvent& e )
{
    return true;
}

/** Keyboard key released */
bool DemoGameState::KeyReleased( const OIS::KeyEvent& e )
{
    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    lfm << "Key: " << e.key << ", " << ((OIS::Keyboard*)(e.device))->getAsString(e.key) << ", Character = " << (char)e.text << std::endl;

    return true;
}

/** Mouse moved */
bool DemoGameState::MouseMoved( const OIS::MouseEvent& e )
{
    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    const OIS::MouseState state = e.state;
    lfm << "Mouse Moved: Abs( " << state.X.abs << ", " << state.Y.abs << ", " << state.Z.abs << " ), Rel( " << state.X.rel << ", " << state.Y.rel << ", " << state.Z.rel << " )\n";
    return true;
}
/** Mouse button pressed */
bool DemoGameState::MousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID id )
{
    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    const OIS::MouseState state = e.state;
    lfm << "Mouse button " << id << " pressed. Abs( " << state.X.abs << ", " << state.Y.abs << ", " << state.Z.abs << " ), Rel( " << state.X.rel << ", " << state.Y.rel << ", " << state.Z.rel << " )\n";
    return true;
}
/** Mouse button released */
bool DemoGameState::MouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID id )
{
    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    const OIS::MouseState state = e.state;
    lfm << "Mouse button " << id << " released. Abs( " << state.X.abs << ", " << state.Y.abs << ", " << state.Z.abs << " ), Rel( " << state.X.rel << ", " << state.Y.rel << ", " << state.Z.rel << " )\n";
    return true;
}

/** Joystick axis moved */
bool DemoGameState::AxisMoved( const OIS::JoyStickEvent& e, int axis )
{
    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    lfm << e.device->vendor() << ". Axis # " << axis << " Value: " << e.state.mAxes[axis].abs << std::endl;
    return true;
}
/** Joystick pov moved */
bool DemoGameState::PovMoved( const OIS::JoyStickEvent& e, int index )
{
    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    lfm << e.device->vendor() << ". POV ";
    if ( e.state.mPOV[ index ].direction == OIS::Pov::Centered )
        lfm << "Centered.";
    else
    {
        if ( e.state.mPOV[ index ].direction & OIS::Pov::North )
            lfm << "North.";
        else if ( e.state.mPOV[ index ].direction & OIS::Pov::South )
            lfm << "South.";

        if ( e.state.mPOV[ index ].direction & OIS::Pov::East )
            lfm << "East.";
        else if ( e.state.mPOV[ index ].direction & OIS::Pov::West )
            lfm << "West.";
        lfm << "\n";
    }

    return true;
}
/** Joystick 3D vector moved */
bool DemoGameState::Vector3Moved( const OIS::JoyStickEvent& e, int index )
{
    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    lfm << e.device->vendor() << ". Vector3 Orientation " << index << " ( " << e.state.mVectors[ index ].x << ", " << e.state.mVectors[ index ].y << ", " << e.state.mVectors[ index ].z << " )" << std::endl;
    return true;
}
/** Joystick slider moved */
bool DemoGameState::SliderMoved( const OIS::JoyStickEvent& e, int index )
{
    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    lfm << e.device->vendor() << ". Slider " << index << " ( " << e.state.mSliders[ index ].abX << ", " << e.state.mSliders[ index ].abY << " )" << std::endl;
    return true;
}
/** Joystick button pressed */
bool DemoGameState::ButtonPressed( const OIS::JoyStickEvent& e, int button )
{
    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    lfm << e.device->vendor() << ". Button Pressed # = " << button << std::endl;

    PGE::AudioManager* audioMgr = PGE::AudioManager::getSingletonPtr();
    int soundIndex = audioMgr->CreateSound2D( "media/boom.mp3", false );
    int channelIndex = 2;
    audioMgr->Play( soundIndex, channelIndex );

    return true;
}
/** Joystick button released */
bool DemoGameState::ButtonReleased( const OIS::JoyStickEvent& e, int button )
{
    cmd::LogFileManager& lfm = cmd::LogFileManager::getInstance();
    cmd::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    lfm << e.device->vendor() << ". Button Released # = " << button << std::endl;
    return true;
}
