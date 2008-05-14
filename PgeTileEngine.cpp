
/*! $Id$
 *  @file   PgeTileEngine.h
 *  @author Chad M. Draper
 *  @date   May 9, 2008
 *
 */

#include "PgeTileEngine.h"

#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#else
#include <SDL.h>
#include <SDL_opengl.h>
#endif

namespace PGE
{
    TileEngine::TileEngine()
        : BaseGameEngine()
    {
        //ctor
    }

    TileEngine::~TileEngine()
    {
        //dtor
    }

/*
    // CreateSurface------------------------------------------------------------
    void TileEngine::CreateSurface()
    {
        // OpenGL double buffering:
        SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

        // Note that calling SDL_SetVideoMode will destroy the OpenGL state, and
        // all OpenGL items will need to be reloaded (including textures!)
        mSurface = SDL_SetVideoMode( mWidth, mHeight, 0, SDL_OPENGL | SDL_SWSURFACE );
    }

    //AditionalInit-------------------------------------------------------------
    void TileEngine::AdditionalInit()
    {
        glEnable( GL_TEXTURE_2D );

        // Set the background color:
        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

        // Set the size of the viewport:
        glViewport( 0, 0, mWidth, mHeight );

        // Clear the display:
        glClear( GL_COLOR_BUFFER_BIT );

        // Reset the projection matrix, and set it for orthographic display:
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( 0.0f, static_cast<float>( mWidth ), static_cast<float>( mHeight ), 0.0f, -1.0f, 1.0f );

        // Reset the modelview matrix:
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
    }

    //Render--------------------------------------------------------------------
    void TileEngine::Render(  )
    {
        glBegin( GL_QUADS );

            glColor3f( 1.0f, 0.0f, 0.0f );
            glVertex2f( 100.0f, 100.0f );

            glColor3f( 0.0f, 1.0f, 0.0f );
            glVertex2f( 300.0f, 100.0f );

            glColor3f( 0.0f, 0.0f, 1.0f );
            glVertex2f( 300.0f, 250.0f );

            glColor3f( 1.0f, 1.0f, 1.0f );
            glVertex2f( 100.0f, 250.0f );

        glEnd();

        SDL_GL_SwapBuffers();
    }
*/

} // namespace PGE
