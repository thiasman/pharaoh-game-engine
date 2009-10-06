
/*! $
 *  @file
 *  @author
 *  @date
 *
 */

#include "DemoGameState.h"
#include "PgeAudioManager.h"
#include "PgeTextureManager.h"
#include "PgeFontManager.h"
#include "PgeMath.h"
#include "PgeColor.h"
#include "PgePoint2D.h"
#include "PgeTypes.h"
#include "PgeArchiveManager.h"
//#include "PgeLogFileManager.h"


#if PGE_PLATFORM == PGE_PLATFORM_WIN32
#   include <windows.h>
#endif

#include <gl/gl.h>
#include <gl/glu.h>
#include <il/il.h>
#include <il/ilu.h>


DemoGameState::DemoGameState()
    : PGE::TileGameState()
{
    //ctor
    //mTextureName    = "puppies2.jpg";
    mTextureName = "gfx\\Level_Tiles.png";
}

DemoGameState::~DemoGameState()
{
    //dtor
}

void DemoGameState::Init()
{
//    PGE::LogFileManager& lfm = PGE::LogFileManager::GetSingleton();
//    PGE::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::Init()" );

    TileGameState::Init();

    //LoadTileStudioXML( "test01/test01.xml" );
    LoadTileStudioXML( "scroll/ScrollDemo.xml" );
    //mTileSet.GenerateDefaultTileset( mTextureName, PGE::Point2Df( 32, 32 ), PGE::Point2D( 20, 20 ) );

    PGE::FontManager::GetSingleton().LoadFont( "fonts/VectorSigmaNormal.fontdef" );

/*
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
//glCullFace( GL_FRONT );

    // Set the background color:
    PGE::Colorf col = PGE::Colorf::RandomRGB();
    glClearColor( col.r, col.g, col.b, col.a );
    //glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    // Set the size of the viewport:
    glViewport( 0, 0, mWidth, mHeight );

    // Clear the display:
    glClear( GL_COLOR_BUFFER_BIT );

    // Reset the projection matrix, and set it for orthographic display:
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0f, static_cast<float>( mWidth ), static_cast<float>( mHeight ), 0.0f, -1.0f, 1.0f );
    //glOrtho( -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f );

    // Reset the modelview matrix:
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    PGE::TextureManager::GetSingleton().LoadImage( mTextureName );

    //mTileMap.GenerateMap( PGE::Point2Df( 32, 32 ), PGE::Point2D( 200, 200 ) );
    mTileMap.GenerateMap( PGE::Point2Df( 32, 32 ), PGE::Point2D( 20, 20 ) );
    mTileMap.LoadMap( "test01/test01.xml" );
    mTileMap.SetDepth( 0 );
    mTileSet.AddTileMap( mTileMap );
*/
}

/*
//SetWindowPosition
void DemoGameState::SetWindowSize( PGE::UInt32 w, PGE::UInt32 h )
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    mWidth = w;
    mHeight = h;
    mViewport.SetSize( w, h );
    glViewport( 0, 0, mWidth, mHeight );
    glOrtho( 0.0f, static_cast<float>( mWidth ), static_cast<float>( mHeight ), 0.0f, -1.0f, 1.0f );
//    float aspectRatio = w / double( h );
//    if ( aspectRatio < 1.0 )
//        glOrtho( -aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f );
//    else
//        glOrtho( -1.0f, 1.0f, 1.0f / aspectRatio, -1.0f / aspectRatio, -1.0f, 1.0f );


    glMatrixMode( GL_MODELVIEW );
}
*/

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
    TileGameState::Update( elapsedMS );

    PGE::InputManager& inputMgr = PGE::InputManager::getSingleton();
    if ( inputMgr.GetJoystickCount() > 0 )
    {
        PGE::AudioManager& audioMgr = PGE::AudioManager::getSingleton();
        const OIS::JoyStickState& state = inputMgr.GetJoystick( 0 )->getJoyStickState();
        if ( state.mButtons[ 4 ] )
            audioMgr.SetPan( 0, -1 );
        else if ( state.mButtons[ 5 ] )
            audioMgr.SetPan( 0, 1 );
        else
            audioMgr.SetPan( 0, 0 );
    }
}

void DemoGameState::Render()
{
    TileGameState::Render();
/*
    PGE::TextureItem* texItem = PGE::TextureManager::GetSingleton().GetTextureItemPtr( mTextureName );
    PGE::UInt32 texID = texItem->GetID();
    glBindTexture( GL_TEXTURE_2D, texID );

    float aspectRatio = texItem->GetWidth() / float( texItem->GetHeight() );
    float w = 1.0f, h = 1.0f;
    if ( aspectRatio < 1.0 )
    {
        w = aspectRatio;
        h = 1.0;
    }
    else
    {
        w = 1.0;
        h = 1.0f / aspectRatio;
    }

    //mTileMap.Render();
    mTileSet.Render( mPosition, mViewport );
*/
}

/** Keyboard key pressed */
bool DemoGameState::KeyPressed( const OIS::KeyEvent& e )
{
//    PGE::LogFileManager& lfm = PGE::LogFileManager::GetSingleton();
//    PGE::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyPressed(...)" );
//    lfm << "velocity (before) = " << mVelocity << std::endl;

    switch ( e.key )
    {
    case OIS::KC_LEFT:
        mVelocity += PGE::Point2Df::UNIT_X;
        break;

    case OIS::KC_RIGHT:
        mVelocity -= PGE::Point2Df::UNIT_X;
        break;

    case OIS::KC_UP:
        mVelocity += PGE::Point2Df::UNIT_Y;
        break;

    case OIS::KC_DOWN:
        mVelocity -= PGE::Point2Df::UNIT_Y;
        break;
    }
//    lfm << "velocity (after) = " << mVelocity << std::endl;

    return true;
}

/** Keyboard key released */
bool DemoGameState::KeyReleased( const OIS::KeyEvent& e )
{
//    PGE::LogFileManager& lfm = PGE::LogFileManager::GetSingleton();
//    PGE::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
//    lfm << "Key: " << e.key << ", " << ((OIS::Keyboard*)(e.device))->getAsString(e.key) << ", Character = " << (char)e.text << std::endl;

    switch ( e.key )
    {
    case OIS::KC_LEFT:
        mVelocity -= PGE::Point2Df::UNIT_X;
        break;

    case OIS::KC_RIGHT:
        mVelocity += PGE::Point2Df::UNIT_X;
        break;

    case OIS::KC_UP:
        mVelocity -= PGE::Point2Df::UNIT_Y;
        break;

    case OIS::KC_DOWN:
        mVelocity += PGE::Point2Df::UNIT_Y;
        break;
    }

    return true;
}

/** Mouse moved */
bool DemoGameState::MouseMoved( const OIS::MouseEvent& e )
{
//    PGE::LogFileManager& lfm = PGE::LogFileManager::GetSingleton();
//    PGE::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::MouseMoved(...)" );
    const OIS::MouseState& state = e.state;
//    lfm << "Mouse Moved: Abs( " << state.X.abs << ", " << state.Y.abs << ", " << state.Z.abs << " ), Rel( " << state.X.rel << ", " << state.Y.rel << ", " << state.Z.rel << " )\n";
    return true;
}
/** Mouse button pressed */
bool DemoGameState::MousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID id )
{
//    PGE::LogFileManager& lfm = PGE::LogFileManager::GetSingleton();
//    PGE::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    const OIS::MouseState& state = e.state;
//    lfm << "Mouse button " << id << " pressed. Abs( " << state.X.abs << ", " << state.Y.abs << ", " << state.Z.abs << " ), Rel( " << state.X.rel << ", " << state.Y.rel << ", " << state.Z.rel << " )\n";

    PGE::AudioManager* audioMgr = PGE::AudioManager::getSingletonPtr();
    int soundIndex = audioMgr->CreateSound2D( "boom.mp3", false );
    int channelIndex = 2;
    audioMgr->Play( "boom.mp3", channelIndex );

    return true;
}
/** Mouse button released */
bool DemoGameState::MouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID id )
{
//    PGE::LogFileManager& lfm = PGE::LogFileManager::GetSingleton();
//    PGE::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    const OIS::MouseState& state = e.state;
//    lfm << "Mouse button " << id << " released. Abs( " << state.X.abs << ", " << state.Y.abs << ", " << state.Z.abs << " ), Rel( " << state.X.rel << ", " << state.Y.rel << ", " << state.Z.rel << " )\n";
    return true;
}

/** Joystick axis moved */
bool DemoGameState::AxisMoved( const OIS::JoyStickEvent& e, int axis )
{
//    PGE::LogFileManager& lfm = PGE::LogFileManager::GetSingleton();
//    PGE::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
//    lfm << e.device->vendor() << ". Axis # " << axis << " Value: " << e.state.mAxes[axis].abs << std::endl;
    if ( axis == 1 )
    {
        float ratio = PGE::Math::Clamp( e.state.mAxes[ axis ].abs, -10000, 10000 ) / 10000.0f;
        mAngle = ratio * 360.0f;
    }
    return true;
}
/** Joystick pov moved */
bool DemoGameState::PovMoved( const OIS::JoyStickEvent& e, int index )
{
//    PGE::LogFileManager& lfm = PGE::LogFileManager::GetSingleton();
//    PGE::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
//    lfm << e.device->vendor() << ". POV ";
/*
    if ( e.state.mPOV[ index ].direction == OIS::Pov::Centered )
    {
        lfm << "Centered.";
    }
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
*/

    return true;
}
/** Joystick 3D vector moved */
bool DemoGameState::Vector3Moved( const OIS::JoyStickEvent& e, int index )
{
/*
    PGE::LogFileManager& lfm = PGE::LogFileManager::GetSingleton();
    PGE::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    lfm << e.device->vendor() << ". Vector3 Orientation " << index << " ( " << e.state.mVectors[ index ].x << ", " << e.state.mVectors[ index ].y << ", " << e.state.mVectors[ index ].z << " )" << std::endl;
*/
    return true;
}
/** Joystick slider moved */
bool DemoGameState::SliderMoved( const OIS::JoyStickEvent& e, int index )
{
/*
    PGE::LogFileManager& lfm = PGE::LogFileManager::GetSingleton();
    PGE::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    lfm << e.device->vendor() << ". Slider " << index << " ( " << e.state.mSliders[ index ].abX << ", " << e.state.mSliders[ index ].abY << " )" << std::endl;
*/
    return true;
}
/** Joystick button pressed */
bool DemoGameState::ButtonPressed( const OIS::JoyStickEvent& e, int button )
{
/*
    PGE::LogFileManager& lfm = PGE::LogFileManager::GetSingleton();
    PGE::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    lfm << e.device->vendor() << ". Button Pressed # = " << button << std::endl;
*/

/*
    PGE::AudioManager* audioMgr = PGE::AudioManager::getSingletonPtr();
    int soundIndex = audioMgr->CreateSound2D( "boom.mp3", false );
    int channelIndex = 2;
    audioMgr->Play( soundIndex, channelIndex );
*/

    return true;
}
/** Joystick button released */
bool DemoGameState::ButtonReleased( const OIS::JoyStickEvent& e, int button )
{
/*
    PGE::LogFileManager& lfm = PGE::LogFileManager::GetSingleton();
    PGE::LogFileSection sect( lfm.GetDefaultLog(), "DemoGameState::KeyReleased(...)" );
    lfm << e.device->vendor() << ". Button Released # = " << button << std::endl;
*/

    return true;
}
