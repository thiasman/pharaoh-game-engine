
/*! $Id$
 *  @file   PgePoint2D.h
 *  @author Chad M. Draper
 *  @date   May 7, 2007
 *
 */

#include "PgePoint2D.h"
#include "PgePoint3D.h"

namespace PGE
{
    ////////////////////////////////////////////////////////////////////////////
    // Point2D
    ////////////////////////////////////////////////////////////////////////////
    Point2D::Point2D( const Point2Df& pt )
        : Point2DTempl<Int>( static_cast<Int>( pt.x ), static_cast<Int>( pt.y ) )
    {
    }

    Point2D::Point2D( const Point3D& pt )
        : Point2DTempl<Int>( pt.x, pt.y )
    {
    }

    ////////////////////////////////////////////////////////////////////////////
    // Point2Df
    ////////////////////////////////////////////////////////////////////////////
    Point2Df::Point2Df( const Point2D& pt )
        : Point2DTempl<Real>( static_cast<Real>( pt.x ), static_cast<Real>( pt.y ) )
    {
    }

    Point2Df::Point2Df( const Point3Df& pt )
        : Point2DTempl<Real>( pt.x, pt.y )
    {
    }

    //IsEqual-------------------------------------------------------------------
    bool Point2Df::IsEqual( const Point2Df& p )
    {
        return ( Math::RealEqual( x, p.x ) && Math::RealEqual( y, p.y ) );
    }

} // namespace PGE
