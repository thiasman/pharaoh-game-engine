
/*! $
 *  @file
 *  @author
 *  @date
 *
 */

#include "DemoGameState.h"

#include <gl/gl.h>
#include <gl/glu.h>

DemoGameState::DemoGameState()
    : PGE::BaseGameState()
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
    glBegin( GL_QUADS );

        glColor3f( 1.0f, 0.0f, 0.0f );
        glVertex2f( -0.5f, -0.5f );

        glColor3f( 0.0f, 1.0f, 0.0f );
        glVertex2f( 0.5f, -0.5f );

        glColor3f( 0.0f, 0.0f, 1.0f );
        glVertex2f( 0.5f, 0.5f );

        glColor3f( 1.0f, 1.0f, 1.0f );
        glVertex2f( -0.5f, 0.5f );

    glEnd();
}
