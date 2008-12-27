
/*! $Id$
 *  @file   PgePoint2D.h
 *  @author Chad M. Draper
 *  @date   May 7, 2007
 *  @brief  Contains classes for 3D points and vectors.
 *
 */

#ifndef PGEPOINT3D_H
#define PGEPOINT3D_H

#include <ostream>
#include "PgeTypes.h"
#include "PgeMath.h"

namespace PGE
{
    // Some forward declarations
    class Point2D;
    class Point2Df;
    class Point3D;
    class Point3Df;

    /** @class Point3DTempl
        Template for a point/vector in 3D space.
    */
    template < typename T >
    class _PgeExport Point3DTempl
    {
    public:
        T           x, y, z;   /**< Coordinates of the point */
        static const Point3DTempl<T> ZERO;
        static const Point3DTempl<T> UNIT_X;
        static const Point3DTempl<T> UNIT_Y;
        static const Point3DTempl<T> UNIT_Z;

        /** Default constructor */
        Point3DTempl<T>() : x( 0 ), y( 0 ), z( 0 )        { }
        /** Initialization constructor */
        Point3DTempl<T>( T ix, T iy, T iz ) : x( ix ), y( iy ), z( iz )  { }
        /** Initialization constructor */
        Point3DTempl<T>( const Point3DTempl<T>& pt ) : x( pt.x ), y( pt.y ), z ( pt.z )  { }

        /** Test for equality with another point */
        virtual bool IsEqual( const Point3DTempl<T>& p )
        {
            return ( x == p.x && y == p.y && z == p.z );
        }

        /** Equality operator */
        bool operator==( const Point3DTempl<T>& p ) const   { return IsEqual( p ); }
        /** Inequality operator */
        bool operator!=( const Point3DTempl<T>& p ) const   { return !IsEqual( p ); }

        /** Assignment operator */
        Point3DTempl<T>& operator=( const Point3DTempl<T>& p )
        {
            x = p.x;
            y = p.y;
            return *this;
        }

        /** Negate the point */
        Point3DTempl<T> operator-() const
        {
            Point3DTempl<T> pt( -x, -y, -z );
            return pt;
        }

        /** Add another point to this point and return the sum */
        Point3DTempl<T> operator+( const Point3DTempl<T>& p ) const
        {
            Point3DTempl<T> pt( x + p.x, y + p.y, z + p.z );
            return pt;
        }

        /** Subtract another point from this point and return the difference */
        Point3DTempl<T> operator-( const Point3DTempl<T>& p ) const
        {
            Point3DTempl<T> pt( x - p.x, y - p.y, z - p.z );
            return pt;
        }

        /** Multiply another point by this point and return the product */
        Point3DTempl<T> operator*( const Point3DTempl<T>& p ) const
        {
            Point3DTempl<T> pt( x * p.x, y * p.y, z * p.z );
            return pt;
        }

        /** Divide this point by another point and return the result */
        Point3DTempl<T> operator/( const Point3DTempl<T>& p ) const
        {
            Point3DTempl<T> pt;
            pt.x = ( p.x == 0 ) ? x : x / pt.x;
            pt.y = ( p.y == 0 ) ? y : y / pt.y;
            pt.z = ( p.z == 0 ) ? z : z / pt.z;
            return pt;
        }

        /** Add a scalar to this point and return the result */
        Point3DTempl<T> operator+( T scalar ) const
        {
            Point3DTempl<T> pt( x + scalar, y + scalar, z + scalar );
            return pt;
        }

        /** Subtract a scalar from this point and return the result */
        Point3DTempl<T> operator-( T scalar ) const
        {
            Point3DTempl<T> pt( x - scalar, y - scalar, z - scalar );
            return pt;
        }

        /** Multiply a scalar by this point and return the result */
        Point3DTempl<T> operator*( T scalar ) const
        {
            Point3DTempl<T> pt( x * scalar, y * scalar, z * scalar );
            return pt;
        }

        /** Divide this point by a scalar and return the result */
        Point3DTempl<T> operator/( T scalar ) const
        {
            Point3DTempl<T> pt;
            pt.x = ( scalar == 0 ) ? x : x / scalar;
            pt.y = ( scalar == 0 ) ? y : y / scalar;
            pt.z = ( scalar == 0 ) ? z : z / scalar;
            return pt;
        }

        /** Add another point to this point */
        Point3DTempl<T>& operator+=( const Point3DTempl<T>& p )
        {
            x += p.x;
            y += p.y;
            z += p.z;
            return *this;
        }

        /** Subtract another point from this point */
        Point3DTempl<T>& operator-=( const Point3DTempl<T>& p )
        {
            x -= p.x;
            y -= p.y;
            z -= p.z;
            return *this;
        }

        /** Multiply another point by this point */
        Point3DTempl<T>& operator*=( const Point3DTempl<T>& p )
        {
            x *= p.x;
            y *= p.y;
            z *= p.z;
            return *this;
        }

        /** Divide this point by another point */
        Point3DTempl<T>& operator/=( const Point3DTempl<T>& p )
        {
            x /= ( p.x == 0 ) ? T( 1.0 ) : p.x;
            y /= ( p.y == 0 ) ? T( 1.0 ) : p.y;
            z /= ( p.z == 0 ) ? T( 1.0 ) : p.z;
            return *this;
        }

        /** Add a scalar to this point */
        Point3DTempl<T>& operator+( T scalar )
        {
            x += scalar;
            y += scalar;
            z += scalar;
            return *this;
        }

        /** Subtract a scalar from this point */
        Point3DTempl<T>& operator-( T scalar )
        {
            x -= scalar;
            y -= scalar;
            z -= scalar;
            return *this;
        }

        /** Multiply a scalar by this point */
        Point3DTempl<T>& operator*( T scalar )
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        /** Divide this point by a scalar */
        Point3DTempl<T>& operator/( T scalar )
        {
            if ( scalar != 0 )
            {
                x /= scalar;
                y /= scalar;
                z /= scalar;
            }
            return *this;
        }

        /** Determine if this point is less than another point */
        bool operator<( const Point3DTempl<T>& p ) const
        {
            return ( x < p.x && y < p.y && z < p.z );
        }

        /** Determine if this point is less than or equal to another point */
        bool operator<=( const Point3DTempl<T>& p ) const
        {
            return ( x <= p.x && y <= p.y && z <= p.z );
        }

        /** Determine if this point is greater than another point */
        bool operator>( const Point3DTempl<T>& p ) const
        {
            return ( x > p.x && y > p.y && z > p.z );
        }

        /** Determine if this point is greater than or equal to another point */
        bool operator>=( const Point3DTempl<T>& p ) const
        {
            return ( x >= p.x && y >= p.y && z >= p.z );
        }

        /** Linearly interpolate between two points */
        static Point3DTempl<T> Lerp( const Point3DTempl<T>& p1, const Point3DTempl<T>& p2, Real ratio )
        {
            return Point3DTempl<T>(
                        static_cast<T>( ( p2.x - p1.x ) * ratio + p1.x ),
                        static_cast<T>( ( p2.y - p1.y ) * ratio + p1.y ),
                        static_cast<T>( ( p2.z - p1.z ) * ratio + p1.z ) );
        }

        /** Linearly interpolate between this and another point */
        Point3DTempl<T> Lerp( const Point3DTempl<T>& p ) const
        {
            return Lerp( *this, p );
        }

        /** Quadratic interpolation between two points */
        static Point3DTempl<T> QuadraticInterp( const Point3DTempl<T>& p1, const Point3DTempl<T>& p2, const Point3DTempl<T>& p3, Real ratio )
        {
            Real invRatio = 1.0 - ratio;
            return ( p1 * Math::Sqr( invRatio ) + 2.0 * p2 * ratio * invRatio + p3 * Math::Sqr( ratio ) );
        }

        /** Quadratic interpolation between this point and another */
        Point3DTempl<T> QuadraticInterp( const Point3DTempl<T>& p2, const Point3DTempl<T>& p3, Real ratio ) const
        {
            return QuadraticInterp( *this, p2, p3, ratio );
        }

        /** Find the midpoint between two points */
        static Point3DTempl<T> MidPoint( const Point3DTempl<T>& p1, const Point3DTempl<T>& p2 )
        {
            return Lerp( p1, p2, 0.5 );
        }

        /** Find the midpoint between this and another point */
        Point3DTempl<T> MidPoint( const Point3DTempl<T>& p ) const
        {
            return MidPoint( *this, p );
        }

        /** Calculate the distance between two points */
        static Real Distance( const Point3DTempl<T>& p1, const Point3DTempl<T>& p2 )
        {
            return Math::Sqrt( Math::Sqr( p2.x - p1.x ) + Math::Sqr( p2.y - p1.y ) + Math::Sqr( p2.z - p1.z ) );
        }

        /** Calculate the distance between this and another point */
        Real Distance( const Point3DTempl<T>& p ) const
        {
            return Distance( *this, p );
        }

        /** Calculate the length of a point/vector */
        static Real Length( const Point3DTempl<T>& p )
        {
            return Math::Sqrt( Math::Sqr( p.x ) + Math::Sqr( p.y ) + Math::Sqr( p.z ) );
        }

        /** Calculate the length of this point/vector */
        Real Length() const
        {
            return Length( *this );
        }

        /** Normalize a point/vector */
        static Point3DTempl<T> Normalize( Point3DTempl<T>& p )
        {
            Real length = Distance( p, ZERO );
            if ( length )
                return Point3DTempl<T>( p.x / length, p.y / length, p.z / length );
            return p;
        }

        /** Normalize this point/vector */
        Point3DTempl<T>& Normalize()
        {
            Normalize( *this );
            return *this;
        }

        /** Create a vector of a specified length */
        Point3DTempl<T> SetLength( const Point3DTempl<T>& p, Real length )
        {
            return Point3DTempl<T>( p * length / Length( p ) );
        }

        /** Set the length of this vector to a given value */
        Point3DTempl<T>& SetLength( Real length )
        {
            *this = SetLength( *this, length );
            return *this;
        }

        /** Get a vector perpendicular to a given vector */
        Point3DTempl<T> Perpendicular( const Point3DTempl<T>& p )
        {
            return Point3DTempl<T>( -p.y, p.x );
        }

        /** Get a vector perpendicular to this vector */
        Point3DTempl<T> Perpendicular() const
        {
            return Pependicular( *this );
        }

        /** Calculate the dot product of two vectors */
        static Real Dot( const Point3DTempl<T>& p1, const Point3DTempl<T>& p2 )
        {
            return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
        }

        /** Calculate the dot product of this vector with another vector */
        Real Dot( const Point3DTempl<T>& p ) const
        {
            return Dot( *this, p );
        }

        /** Calculate the cross product of two vectors */
        static Point3DTempl<T> Cross( const Point3DTempl<T>& p1, const Point3DTempl<T>& p2 )
        {
            Point3DTempl<T> crossVec;
            crossVec.x = p1.y * p2.z - p1.z * p2.y;
            crossVec.y = p1.z * p2.x - p1.x * p2.z;
            crossVec.z = p1.x * p2.y - p1.y * p2.x;
            return crossVec;
        }

        /** Calculate the cross product of this vector with another vector */
        Point3DTempl<T> Cross( const Point3DTempl<T>& p ) const
        {
            return Cross( *this, p );
        }

        /** Calculate the angle between two vectors */
        static Real Angle( const Point3DTempl<T>& p1, const Point3DTempl<T>& p2 )
        {
            // If both vectors are unit vectors, we know that the dot product returns the
            // cosine of the angle between the vectors.  Since we may not have normalized
            // vectors, we need to divide the dot product by the product of the magnitudes
            // of the vectors.  ie. V1.V2 / ||V1|| * ||V2||.
            Real  dotProd    = Dot( p1, p2 );
            Real  magnitude  = p1.Length() * p2.Length();

            // Get angle by calculating the arc cosine of fDotProduct / fMagnitude.  This value
            // will be in radians.  Use AngleD if you want to get the angle in degrees.
            return Math::ACos( (Real)( dotProd / magnitude ) );
        }

        /** Calculate the angle between this vector and another vector */
        Real Angle( const Point3DTempl<T>& p ) const
        {
            return Angle( *this, p );
        }

        /** Find the closes point on a line between two points to a given point. */
        static Real ClosestPointOnLine( const Point3DTempl<T>& p1, const Point3DTempl<T>& p2, const Point3DTempl<T>& p )
        {
            // First, we need a vector from the first point to 'this' point:
            Point3DTempl<T> vec1( p - p1 );

            // We want the normalized vector from the second end-point to the first:
            Point3DTempl<T> vec2( p2 - p1 );
            vec2.Normalize();

            // Find the distance between the end-points (ie. find the length of the line segment):
            Real      dist = p1.Distance( p2 );

            // Take the dot product of vec1 and vec2.  If the value is 0, then the
            // lines were perpendicular at ptLinePt1.  If the value is less than 0,
            // then the closest point is still ptLinePt1, since the actual closest
            // point would be outside the segment.  Also, the value of the dot product
            // will give us the distance along the segment to the closest point.
            // If this is greater than the length of the segment, then the closest
            // point is ptLinePt2, since we are again out-of-range.
            Real      t   = vec2.Dot( vec1 );

            if ( t <= 0 )
            {
                // linePt1 is closest.  Either 'this' point is directly perpendicular, or
                // we are out of range here:
                return p1;
            }

            if ( t >= dist )
            {
                // We intersect either right on, or past the second point:
                return p2;
            }

            // The point is somewhere between the two end-points.  To find it, create
            // a vector in the direction of the line segment, with a length of t (which
            // is the distance from the first point to the 'closest' point:
            Point3DTempl<T> vec3( vec2 * t );

            // The closest point will be vec3 + ptLinePt1:
            return vec3 + p1;
        }

        /** Find the closest point to this point on a line defined by two other points */
        Point3DTempl<T> ClosestPointOnLine( const Point3DTempl<T>& p1, const Point3DTempl<T>& p2 ) const
        {
            return ClosestPointOnLine( p1, p2, *this );
        }

        /** Write the point to a stream */
        inline friend std::ostream& operator<<( std::ostream& stream, const Point3DTempl<T>& src )
        {
            std::ostream::sentry opfx(stream);
            if ( !opfx )
                return stream;
            return ( stream << "Point3D( " << src.x << ", " << src.y << ", " << src.z << " )" );
        }


    }; // class Point3DTempl;
    template <typename T> const Point3DTempl<T> Point3DTempl<T>::ZERO( static_cast<T>( 0 ), static_cast<T>( 0 ), static_cast<T>( 0 ) );
    template <typename T> const Point3DTempl<T> Point3DTempl<T>::UNIT_X( static_cast<T>( 1 ), static_cast<T>( 0 ), static_cast<T>( 0 ) );
    template <typename T> const Point3DTempl<T> Point3DTempl<T>::UNIT_Y( static_cast<T>( 0 ), static_cast<T>( 1 ), static_cast<T>( 0 ) );
    template <typename T> const Point3DTempl<T> Point3DTempl<T>::UNIT_Z( static_cast<T>( 0 ), static_cast<T>( 0 ), static_cast<T>( 1 ) );

    /** Point/Vector in 3D space, using integer values for the coordinates */
    class _PgeExport Point3D : public Point3DTempl< Int >
    {
    public:
        /** Constructor */
        Point3D() : Point3DTempl< Int >()       { }
        /** Constructor */
        Point3D( Int ix, Int iy, Int iz ) : Point3DTempl< Int >( ix, iy, iz )   { }
        /** Constructor */
        Point3D( const Point3D& pt ) : Point3DTempl< Int >( pt )    { }
        /** Constructor */
        template < typename U >
        Point3D( const Point3DTempl<U>& pt ) : Point3DTempl< Int >( pt.x, pt.y, pt.z )    { }

        /** Constructor that implicitly converts from a floating-point point. */
        Point3D( const Point3Df& pt );

        /** Constructor that implicitly converts from a 2D point. */
        Point3D( const Point2D& pt );
    };

    /** Point/Vector in 3D space, using floating-point values for the coordinates */
    class _PgeExport Point3Df : public Point3DTempl< Real >
    {
    public:
        /** Constructor */
        Point3Df() : Point3DTempl< Real >()       { }
        /** Constructor */
        Point3Df( Real ix, Real iy, Real iz ) : Point3DTempl< Real >( ix, iy, iz )   { }
        /** Constructor */
        Point3Df( const Point3Df& pt ) : Point3DTempl< Real >( pt )    { }
        /** Constructor */
        template < typename U >
        Point3Df( const Point3DTempl<U>& pt ) : Point3DTempl< Real >( pt.x, pt.y, pt.z )    { }

        /** Constructor that implicitly converts from a integer point. */
        Point3Df( const Point3D& pt );

        /** Constructor that implicitly converts from a 2D point. */
        Point3Df( const Point2Df& pt );

        /** Override the equal test for floating-point values */
        bool IsEqual( const Point3Df& p );
    };

} // namespace PGE

#endif // PGEPOINT3D_H
