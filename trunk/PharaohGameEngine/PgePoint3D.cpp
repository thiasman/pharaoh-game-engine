
/*! $Id$
 *  @file   PgePoint2D.h
 *  @author Chad M. Draper
 *  @date   May 7, 2007
 *
 */

#include "PgePoint3D.h"
#include "PgePoint2D.h"

namespace PGE
{
    ////////////////////////////////////////////////////////////////////////////
    // Point3D
    ////////////////////////////////////////////////////////////////////////////
    Point3D::Point3D( const Point3Df& pt )
        : Point3DTempl<Int>( static_cast<Int>( pt.x ), static_cast<Int>( pt.y ), static_cast<Int>( pt.z ) )
    {
    }

    Point3D::Point3D( const Point2D& pt )
        : Point3DTempl<Int>( pt.x, pt.y, 0 )
    {
    }

    ////////////////////////////////////////////////////////////////////////////
    // Point3Df
    ////////////////////////////////////////////////////////////////////////////
    Point3Df::Point3Df( const Point3D& pt )
        : Point3DTempl<Real>( static_cast<Real>( pt.x ), static_cast<Real>( pt.y ), static_cast<Real>( pt.z ) )
    {
    }

    Point3Df::Point3Df( const Point2Df& pt )
        : Point3DTempl<Real>( pt.x, pt.y, 0.0 )
    {
    }

    //IsEqual-------------------------------------------------------------------
    bool Point3Df::IsEqual( const Point3Df& p )
    {
        return ( Math::RealEqual( x, p.x ) && Math::RealEqual( y, p.y ) && Math::RealEqual( z, p.z ) );
    }

} // namespace PGE
