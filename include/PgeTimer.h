
/*! $Id$
 *  @file   PgeTimer.h
 *  @author Chad M. Draper
 *  @date   May 14, 2008
 *  @brief  A cross platform timer.
 *
 */

#ifndef PGETIMER_H
#define PGETIMER_H

#include "PgeTypes.h"

#if ( PGE_PLATFORM == PGE_PLATFORM_WIN32 )
#   include <windows.h>
#   include <mmsystem.h>
    // Link with winmm.lib...
#else
    #include <sys/time.h>
#endif

namespace PGE
{
    class _PgeExport Timer
    {
    private:
        Real32  mPreviousTime;      /**< Time when the timer was last updated */
        Real32  mStartTime;         /**< Time the timer was started or reset */
        bool    mPaused;            /**< Indicates if the timer is paused */

    public:
        /** Constructor */
        Timer();
        /** Destructor */
        virtual ~Timer();

        /** Restart the timer.  The timer is initialized by the constructor, but
            it may be necessary at times to start it manually, or to restart it.
        */
        void Restart();

        /** Return the current number of milliseconds since the timer was started */
        static Real32 GetTicks();

        /** Get the number of milliseconds since the previous call to this timer */
        Real32 GetElapsedTime();

        /** Get the number of milliseconds since the timer was started or reset */
        Real32 GetTotalTime();

        /** Check if the timer is currently paused. */
        bool IsPaused() const               { return mPaused; }

        /** Basically pauses the timer.  As long as the timer is paused, the
            returned time will be what it was when the timer was paused.
        */
        void Pause();

        /** Unpause the timer. */
        void Unpause();
    };

} // namespace PGE

#endif // PGETIMER_H
