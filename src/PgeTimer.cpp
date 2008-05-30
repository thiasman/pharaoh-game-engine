
/*! $Id$
 *  @file   PgeTimer.cpp
 *  @author Chad M. Draper
 *  @date   May 14, 2008
 *
 */

#include "PgeTimer.h"

namespace PGE
{
    Timer::Timer()
        : mPaused( false )
    {
        //ctor
#if ( PGE_PLATFORM == PGE_PLATFORM_WIN32 )
        timeBeginPeriod( 1 );
#endif

        Restart();
    }

    Timer::~Timer()
    {
        //dtor
#if ( PGE_PLATFORM == PGE_PLATFORM_WIN32 )
        timeEndPeriod( 1 );
#endif
    }

    //Restart-------------------------------------------------------------------
    void Timer::Restart()
    {
        mPaused = false;
        mPreviousTime = Timer::GetTicks();
        mStartTime = mPreviousTime;
    }

    //GetTicks------------------------------------------------------------------
    Real32 Timer::GetTicks()
    {
#if ( PGE_PLATFORM == PGE_PLATFORM_WIN32 )
        return timeGetTime();
#else
        struct timeval tv;
        gettimeofday( &tv, NULL );

        // Calculate the milliseconds:
        return static_cast< Real32 >( tv.tv_sec ) * 1000.0 + static_cast< Real32 >( tv.tv_usec ) * .001;
#endif
    }

    //GetElapsedTime------------------------------------------------------------
    Real32 Timer::GetElapsedTime()
    {
        Real32 elapsed = 0;
        if ( !mPaused )
        {
            Real32 curTime = Timer::GetTicks();
            elapsed = curTime - mPreviousTime;
            mPreviousTime = curTime;
        }

        return elapsed;
    }

    //GetTotalTime--------------------------------------------------------------
    Real32 Timer::GetTotalTime()
    {
        Real32 elapsed = mPreviousTime - mStartTime;
        if ( !mPaused )
        {
            Real32 curTime = Timer::GetTicks();
            elapsed = curTime - mStartTime;
            mPreviousTime = curTime;
        }
        return elapsed;
    }

    //Pause---------------------------------------------------------------------
    void Timer::Pause()
    {
        mPaused = true;
    }

    //Unpause-------------------------------------------------------------------
    void Timer::Unpause()
    {
        if ( mPaused )
        {
            mPaused = false;

            // Need to update the start time and the previous time.  The previous
            // time is simply set to the current time.  The start time will need to
            // account for the difference that the timer was paused.  Simply put,
            // add the pause time onto the start time.
            Real32 curTime = Timer::GetTicks();
            Real32 elapsed = curTime - mPreviousTime;
            mPreviousTime  = curTime;
            mStartTime    += elapsed;
        }
    }


} // namespace PGE
