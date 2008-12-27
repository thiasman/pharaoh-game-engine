
/*! $Id$
 *  @file   PgeTypes.h
 *  @author Chad M. Draper
 *  @date   May 7, 2008
 *  @brief  Defines types used by the Pharaoh Game Engine.  Some of these are
 *          aliases for
 *
 */

#ifndef PGETYPES_H_INCLUDED
#define PGETYPES_H_INCLUDED

#include "PgePlatform.h"
#include <string>
#include <vector>

namespace PGE
{
    typedef unsigned char   UInt8;
    typedef char            SInt8;
    typedef unsigned short  UInt16;
    typedef short           SInt16;
    typedef unsigned long   UInt32;
    typedef long            SInt32;
    typedef long            Int;

    #if ( PGE_PLATFORM == PGE_PLATFORM_LINUX ) || ( PGE_PLATFORM == PGE_PLATFORM_APPLE ) || ( PGE_COMPILER == PGE_COMPILER_GNUC )
        typedef unsigned long long  UInt64;
        typedef long long           SInt64;

    #else   // Win32
        typedef unsigned __int64    UInt64;
        typedef __int64             SInt64;
    #endif

    typedef float           Real16;
    typedef double          Real32;
    typedef float           Real;

    typedef std::string     String;
    typedef std::vector< String >   StringVector;

} // namespace PGE

#endif // PGETYPES_H_INCLUDED
