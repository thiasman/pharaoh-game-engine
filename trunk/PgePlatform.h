
/*! $Id$
 *  @file   PgePlatform.h
 *  @author Chad M. Draper
 *  @date   May 14, 2008
 *  @brief  Defines some constants for indicating the current platform.
 *
 */

#ifndef PGEPLATFORM_H_INCLUDED
#define PGEPLATFORM_H_INCLUDED

#include <stddef.h>
#include <memory.h>
#include <stdlib.h>
#include <stdarg.h>

namespace PGE
{
    #define PGE_PLATFORM_WIN32  1
    #define PGE_PLATFORM_APPLE  2
    #define PGE_PLATFORM_LINUX  3

    #define PGE_COMPILER_MSVC   1
    #define PGE_COMPILER_GNUC   2
    #define PGE_COMPILER_BORL   3

    #define PGE_ENDIAN_LITTLE   1
    #define PGE_ENDIAN_BIG      2

    #define PGE_ARCHETECTURE_32 1
    #define PGE_ARCHETECTURE_64 2

    // Set the compiler flags
    #if defined( _MSC_VER )
        #define PGE_COMPILER    PGE_COMPILER_MSVC

    #elif defined( __GNUC__ )
        #define PGE_COMPILER    PGE_COMPILER_GNUC

    #elif defined( __BORLANDC__ )
        #define PGE_COMPILER    PGE_COMPILER_BORL

    #else
        #pragma error "ERROR: Compiler unknown.  Abort."
    #endif

    // Set the platform flags
    #if defined( __WIN32__ ) || defined( _WIN32 )
        #define PGE_PLATFORM    PGE_PLATFORM_WIN32

//    #elif defined( __APPLE_CC__ )
//        #define PGE_PLATFORM    PGE_PLATFORM_APPLE

    #else
        #define PGE_PLATFORM    PGE_PLATFORM_LINUX
    #endif

    #if (_WIN32_WCE < 0x500) && ( defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP) )
        #pragma comment(lib, "ccrtrtti.lib")
        #ifdef _X86_
            #if defined(_DEBUG)
                #pragma comment(lib, "libcmtx86d.lib")
            #else
                #pragma comment(lib, "libcmtx86.lib")
            #endif
        #endif
    #endif

    // Architecture type (32 or 64 bit, currently.)
    #if defined(__x86_64__)
    #   define PGE_ARCHITECTURE AGGOO_ARCHITECTURE_64
    #else
    #   define PGE_ARCHITECTURE AGGOO_ARCHITECTURE_32
    #endif

    // Set the endian flag
    #if defined(__hppa__) || \
        defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || \
        (defined(__MIPS__) && defined(__MISPEB__)) || \
        defined(__ppc__) || defined(__POWERPC__) || defined(_M_PPC) || \
        defined(__sparc__)

        #define PGE_ENDIAN  PGE_ENDIAN_BIG

    #else
        #define PGE_ENDIAN  PGE_ENDIAN_LITTLE
    #endif

    //----------------------------------------------------------------------------
    // Settings for Windows systems
    #if PGE_PLATFORM == PGE_PLATFORM_WIN32

        #include <windows.h>

        // If we're not including this from a client build, specify that the stuff
        // should get exported. Otherwise, import it.
        #if defined( __MINGW32__ )
             // Linux compilers don't have symbol import/export directives.
            #define _PgeExport
            #define _PgePrivate
        #else
            #if PGE_DYNAMIC_LINKAGE == 1
                #if defined( PGE_NONCLIENT_BUILD )
                    #define _PgeExport __declspec( dllexport )
                #else
                    #define _PgeExport __declspec( dllimport )
                #endif
            #else
                #define _PgeExport
            #endif
            #define _PgePrivate
        #endif
        // Win32 compilers use _DEBUG for specifying debug builds.
        #ifdef _DEBUG
            #define PGE_DEBUG_MODE 1
        #else
            #define PGE_DEBUG_MODE 0
        #endif

        #if defined( __MINGW32__ )
            #define EXT_HASH
        #else
            #define snprintf _snprintf
            #define vsnprintf _vsnprintf
        #endif
    #endif
    //----------------------------------------------------------------------------

    //----------------------------------------------------------------------------
    // Linux/Apple Settings
    #if PGE_PLATFORM == PGE_PLATFORM_LINUX || PGE_PLATFORM == PGE_PLATFORM_APPLE

        // Enable GCC 4.0 symbol visibility
        #   if PGE_COMP_VER >= 400
        #       define _PgeExport  __attribute__ ((visibility("default")))
        #       define _PgePrivate __attribute__ ((visibility("hidden")))
        #   else
        #       define _PgeExport
        #       define _PgePrivate
        #   endif

        // A quick define to overcome different names for the same function
        #   define stricmp strcasecmp

        // Unlike the Win32 compilers, Linux compilers seem to use DEBUG for when
        // specifying a debug build.
        #   ifdef DEBUG
        #       define PGE_DEBUG_MODE 1
        #   else
        #       define PGE_DEBUG_MODE 0
        #   endif

        #if PGE_PLATFORM == PGE_PLATFORM_APPLE
            #define PGE_PLATFORM_LIB "PgePlatform.bundle"
        #else
            //AGGOO_PLATFORM_LINUX
            #define PGE_PLATFORM_LIB "libPgePlatform.so"
        #endif

    #endif

    //For apple, we always have a custom config.h file
    #if ( PGE_PLATFORM == PGE_PLATFORM_APPLE )
    #    include "config.h"
    #endif


} // namespace PGE


#endif // PGEPLATFORM_H_INCLUDED
