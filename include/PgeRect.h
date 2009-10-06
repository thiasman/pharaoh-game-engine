
/*! $Id$
 *  @file   PgeRect.h
 *  @author Chad M. Draper
 *  @date   April 27, 2009
 *  @brief  Class for a 2D rectangle.
 *
 */

#ifndef PGERECT_H_
#define PGERECT_H_

#include <ostream>
#include "PgeTypes.h"
#include "PgeMath.h"
#include "PgePoint2D.h"

namespace PGE
{
    class Rect;
    class RectF;

    /** @class RectTempl
        Template class for rectangles.
    */
    template < typename T >
    class _PgeExport RectTempl
    {
    public:
        T       x, y, width, height;

        /** Constructor */
        RectTempl<T>() : x( 0 ), y( 0 ), width( 0 ), height( 0 )    { }
        /** Constructor */
        RectTempl<T>( T ix, T iy, T iw, T ih ) : x( ix ), y( iy ), width( iw ), height( ih )    { }
        /** Constructor */
        RectTempl<T>( const RectTempl<T>& r ) : x( r.x ), y( r.y ), width( r.width ), height( r.height )    { }
        /** Constructor */
        template < typename U >
        RectTempl<T>( const Point2DTempl<U>& tl, const Point2DTempl<U>& br )
        {
            x       = tl.x;
            y       = tl.y;
            width   = br.x - tl.x;
            height  = br.y - tl.y;
        }

        /** Test for equality with another point */
        virtual bool IsEqual( const RectTempl<T>& p )
        {
            return ( x == p.x && y == p.y && width == p.width && height == p.height );
        }

        /** Equality operator */
        bool operator==( const RectTempl<T>& p ) const   { return IsEqual( p ); }
        /** Inequality operator */
        bool operator!=( const RectTempl<T>& p ) const   { return !IsEqual( p ); }

        /** Assignment operator */
        template < typename U >
        const RectTempl<T>& operator=( const RectTempl<U>& r )
        {
            x       = r.x;
            y       = r.y;
            width   = r.width;
            height  = r.height;
            return *this;
        }

        /** Get the left edge of the rect */
        T GetLeft() const       { return x; }
        /** Get the top edge of the rect */
        T GetTop() const        { return y; }
        /** Get the right edge of the rect */
        T GetRight() const      { return x + width; }
        /** Get the bottom edge of the rect */
        T GetBottom() const     { return y + height; }

        /** Get the top-left corner as a 2D point */
        Point2DTempl<T> GetTopLeft() const
        {
            Point2DTempl<T> tl( x, y );
            return tl;
        }

        /** Get the bottom-right corner as a 2D point */
        Point2DTempl<T> GetBottomRight() const
        {
            Point2DTempl<T> br( x + width, y + height );
            return br;
        }

        /** Get the center of the rect as a 2D point */
        Point2DTempl<T> GetCenter() const
        {
            Point2DTempl<T> center( x + width * 0.5, y + height * 0.5 );
            return center;
        }
        
        /** Offset this rect by a given amount */
        template < typename U >
        void Offset( U sx, U sy )
        {
            x += sx;
            y += sy;
        }

        /** Inflate the rect by a given amount */
        template < typename U >
        void Inflate( U infl )
        {
            x       -= infl;
            y       -= infl;
            width   += infl * 2;
            height  += infl * 2;
        }
        /** Inflate the rect by a given amount */
        template < typename U >
        void Inflate( U inflX, U inflY )
        {
            x       -= inflX;
            y       -= inflY;
            width   += inflX * 2;
            height  += inflY * 2;
        }

        /** Combine this rect with another, returning the result (this rect is not modified) */
        template < typename U >
        RectTempl<T>& Union( const RectTempl<U>& r )
        {
            RectTempl<T> result;
            result.x        = Math::Min( x, r.x );
            result.y        = Math::Min( y, r.y );
            result.width    = Math::Max( GetRight(), r.GetRight() ) - result.x;
            result.height   = Math::Max( GetBottom(), r.GetBottom() ) - result.y;
            return *this;
        }

        /** Normalize the rect.  This will make sure that the position is at the
            top-left, and that the bottom-right is the position + width/height.
        */
        void Normalize()
        {
            if ( width < 0 )
            {
                x += width;
                width = -width;
            }
            if ( height < 0 )
            {
                y += height;
                height = -height;
            }
        }

        /** Test whether a point lies within the rect */
        template < typename U >
        bool HitTest( const Point2DTempl<U>& pt )
        {
            return ( pt.x >= x && pt.x < pt.x + width && pt.y >= y && pt.y < y + height );
        }

        /** Write the point to a stream */
        inline friend std::ostream& operator<<( std::ostream& stream, const RectTempl<T>& src )
        {
            std::ostream::sentry opfx(stream);
            if ( !opfx )
                return stream;
            return ( stream << "Rect( " << src.x << ", " << src.y << ", " << src.width << ", " << src.height << " )" );
        }

    }; // class RectTempl

    /** Point/Vector in 2D space, using integer values for the coordinates */
    class _PgeExport Rect : public RectTempl< Int >
    {
    public:
        /** Constructor */
        Rect() : RectTempl< Int >()       { }
        /** Constructor */
        Rect( Int ix, Int iy, Int iw, Int ih ) : RectTempl< Int >( ix, iy, iw, ih )   { }
        /** Constructor */
        Rect( const Rect& r ) : RectTempl< Int >( r )    { }
        /** Constructor */
        template < typename U >
        Rect( const Point2DTempl<U>& tl, const Point2DTempl<U>& br ) : RectTempl< Int >( tl, br ) { }

        /** Constructor that implicitly converts from a floating-point rect. */
        Rect( const RectF& r );
    };

    /** Point/Vector in 2D space, using floating-point values for the coordinates */
    class _PgeExport RectF : public RectTempl< Real >
    {
    public:
        /** Constructor */
        RectF() : RectTempl< Real >()       { }
        /** Constructor */
        RectF( Real ix, Real iy, Real iw, Real ih ) : RectTempl< Real >( ix, iy, iw, ih )   { }
        /** Constructor */
        RectF( const RectF& r ) : RectTempl< Real >( r )    { }
        /** Constructor */
        template < typename U >
        RectF( const Point2DTempl<U>& tl, const Point2DTempl<U>& br ) : RectTempl< Real >( tl, br ) { }

        /** Constructor that implicitly converts from a floating-point rect. */
        RectF( const Rect& r );

        /** Override the equal test for floating-point values */
        bool IsEqual( const RectF& r );
    };

} // namespace PGE

#endif  // PGERECT_H_
