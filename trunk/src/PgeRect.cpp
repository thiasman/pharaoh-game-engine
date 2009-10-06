
/*! $Id$
 *  @file   PgeRect.cpp
 *  @author Chad M. Draper
 *  @date   April 27, 2009
 *
 */

#include "PgeRect.h"

namespace PGE
{
    // Rect
    Rect::Rect( const RectF& r )
    {
        x       = r.x;
        y       = r.y;
        width   = r.width;
        height  = r.height;
    }

    // RectF
    RectF::RectF( const Rect& r )
    {
        x       = r.x;
        y       = r.y;
        width   = r.width;
        height  = r.height;
    }

    bool RectF::IsEqual( const RectF& r )
    {
        return ( Math::RealEqual( x, r.x ) && Math::RealEqual( y, r.y ) && Math::RealEqual( width, r.width ) && Math::RealEqual( height, r.height ) );
    }

} // namespace PGE
