
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

#include <string>

namespace PGE
{
    typedef unsigned char   UInt8;
    typedef char            SInt8;
    typedef unsigned short  UInt16;
    typedef short           SInt16;
    typedef unsigned long   UInt32;
    typedef long            SInt32;
    typedef long            Int;

    typedef float           Real16;
    typedef double          Real32;
    typedef float           Real;

    typedef std::string     String;

} // namespace PGE

#endif // PGETYPES_H_INCLUDED
