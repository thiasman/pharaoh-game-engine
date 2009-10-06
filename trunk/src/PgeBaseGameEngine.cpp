
/*! $Id$
 *  @file   PgeBaseGameEngine.cpp
 *  @author Chad M. Draper
 *  @date   May 14, 2008
 *
 */

#include "PgeBaseGameEngine.h"

namespace PGE
{
    BaseGameEngine::BaseGameEngine()
        : mLastTick( 0 ),
          mTickCounter( 0 ),
          mFrameCounter( 0 ),
          mCurrentFPS( 0 ),
          mDisplaySize( Point2D::ZERO )
    {
        //ctor
    }

    BaseGameEngine::~BaseGameEngine()
    {
        //dtor
    }

    //GetFPS--------------------------------------------------------------------
    unsigned long BaseGameEngine::GetFPS() const
    {
        return mCurrentFPS;
    }

    //Init----------------------------------------------------------------------
    void BaseGameEngine::Init()
    {
        AdditionalInit();
    }

    //Pause---------------------------------------------------------------------
    void BaseGameEngine::Pause()
    {
    }

    //Unpause-------------------------------------------------------------------
    void BaseGameEngine::Unpause()
    {
    }

    //PrepareFrame--------------------------------------------------------------
    void BaseGameEngine::PrepareFrame()
    {
        // Get the elapsed time:
        unsigned long curTick = Timer::GetTicks();
        unsigned long elapsedTicks = curTick - mLastTick;
        mLastTick = curTick;

        DoPrepareFrame( mTimer.GetElapsedTime() );

        // Update the tick counter:
        mTickCounter += elapsedTicks;
    }

    //RenderFrame---------------------------------------------------------------
    void BaseGameEngine::RenderFrame()
    {
        // Update the frame counter:
        ++mFrameCounter;

        if ( mTickCounter > 1000 )
        {
            mCurrentFPS = mFrameCounter;
            mFrameCounter = 0;
            mTickCounter = 0;
        }

        // Render the scene:
        DoRenderFrame();
    }

} // namespace PGE
