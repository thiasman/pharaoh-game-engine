
/*! $Id$
 *  @file   PgeColor.h
 *  @author Chad M. Draper
 *  @date   September 5, 2007
 *  @brief  Contains definition of color class.
 *
 */

#ifndef PGECOLOR_H_INCLUDED
#define PGECOLOR_H_INCLUDED

#include <ostream>
#include "PgeTypes.h"
#include "PgeMath.h"

namespace PGE
{
    /** @class ColorTempl
        Template color definition.

        @param  T           Type used for the color components
        @param  maxValue    Maximum value of any color component
    */
    template < typename T, UInt32 maxValue >
    class _PgeExport ColorTempl
    {
    public:
        T       r, g, b, a;         ///< Color components

        /** Default constructor */
        ColorTempl<T, maxValue>() : r( 0 ), g( 0 ), b( 0 ), a( 0 )
        {
        }
        /** Initialization constructor */
        ColorTempl<T, maxValue>( T ir, T ig, T ib, T ia )
            : r( ir ), g( ig ), b( ib ), a( ia )
        {
        }
        /** Copy constructor */
        template < typename U, UInt32 maxValue2 >
        ColorTempl<T, maxValue>( const ColorTempl<U, maxValue2>& col )
            : r( col.r ), g( col.g ), b( col.b ), a( col.a )
        {
        }

        /** Copy operator */
        template< typename U, UInt32 maxValue2 >
        ColorTempl<T, maxValue>& operator=( const ColorTempl<U, maxValue2>& col )
        {
            r   = Math::Clamp( col.r, 0, maxValue );
            g   = Math::Clamp( col.g, 0, maxValue );
            b   = Math::Clamp( col.b, 0, maxValue );
            a   = Math::Clamp( col.a, 0, maxValue );
            return *this;
        }

        /** Test for equality with another color */
        template < typename U, UInt32 maxValue2 >
        bool IsEqual( const ColorTempl<U, maxValue2>& col )
        {
            return ( r == col.r &&
                     g == col.g &&
                     b == col.b &&
                     a == col.a );
        }

        /** Equality operator */
        template < typename U, UInt32 maxValue2 >
        bool operator==( const ColorTempl<U, maxValue2>& pt )  { return IsEqual( pt ); }

        /** Inequality operator */
        template < typename U, UInt32 maxValue2 >
        bool operator!=( const ColorTempl<U, maxValue2>& pt )  { return !IsEqual( pt ); }

        /** Scale the color components by multipling them by a scalar.  The
            result is stored in this color, and a reference is returned.
        */
        ColorTempl<T, maxValue>& Scale( Real scalar )
        {
            r = Math::Clamp( r * scalar, 0, maxValue );
            g = Math::Clamp( g * scalar, 0, maxValue );
            b = Math::Clamp( b * scalar, 0, maxValue );
            a = Math::Clamp( a * scalar, 0, maxValue );
            return *this;
        }

        /** Multiply this color by a scalar, returning the new color */
        ColorTempl<T, maxValue> operator*( Real scalar )
        {
            ColorTempl<T, maxValue> color = *this;
            return color.Scale( scalar );
        }

        /** Divide the color by a scalar, returning the new color */
        ColorTempl<T, maxValue> operator/( Real scalar )
        {
            ColorTempl<T, maxValue> color = *this;
            if ( scalar == Real( 0 ) )
                return color;
            return color.Scale( 1.0 / scalar );
        }

        /** Offset the color values by a constant */
        ColorTempl<T, maxValue>& Translate( T offset )
        {
            r = Math::Clamp( r + offset, 0, maxValue );
            g = Math::Clamp( g + offset, 0, maxValue );
            b = Math::Clamp( b + offset, 0, maxValue );
            a = Math::Clamp( a + offset, 0, maxValue );
            return *this;
        }

        /** Add a constant to the color components and return the clamped
            result.
        */
        ColorTempl<T, maxValue>& operator+( T offset )
        {
            ColorTempl<T, maxValue> color( *this );
            return color.Translate( offset );
        }

        /** Subtract a constant from the color components and return the clamped
            result.
        */
        ColorTempl<T, maxValue>& operator-( T offset )
        {
            ColorTempl<T, maxValue> color( *this );
            return color.Translate( -offset );
        }

        /** Normalize the color by setting the maximum component to maxValue
            and scale the other components using the following algorithm:

                ratio = maxValue / max_component_value
                for each component
                    component *= ratio;
        */
        ColorTempl<T, maxValue>& Normalize()
        {
            // Find the value of the maximum component:
            Real maxComp = Math::Max( Math::Max( r, g ), Math::Max( b, a ) );

            // Calculate the ratio:
            Real ratio = maxValue / maxComp;

            r *= ratio;
            g *= ratio;
            g *= ratio;
            a *= ratio;
            return *this;
        }

        /** Linear interpolation between two colors */
        ColorTempl<T, maxValue> Lerp( const ColorTempl<T, maxValue>& color2, Real ratio )
        {
            ColorTempl<T, maxValue> retColor( Math::Lerp( r, color2.r, ratio ),
                                              Math::Lerp( g, color2.g, ratio ),
                                              Math::Lerp( b, color2.b, ratio ),
                                              Math::Lerp( a, color2.a, ratio ) );
            return retColor;
        }

        /** Generate a random color, with components between 0 and maxValue */
        static ColorTempl<T, maxValue> Random()
        {
            T maxVal = reinterpret_cast< T >( maxValue );
            T r = Math::RangeRandom( 0, maxVal );
            T g = Math::RangeRandom( 0, maxVal );
            T b = Math::RangeRandom( 0, maxVal );
            T a = Math::RangeRandom( 0, maxVal );

            return ColorTempl<T, maxValue>( r, g, b, a );
        }

        /** Generate a random RGB color, with components between 0 and maxValue
            and the alpha at maxValue.
        */
        static ColorTempl<T, maxValue> RandomRGB()
        {
            T maxVal = static_cast< T >( maxValue );
            T r = Math::RangeRandom( 0, maxVal );
            T g = Math::RangeRandom( 0, maxVal );
            T b = Math::RangeRandom( 0, maxVal );
            T a = maxValue;

            return ColorTempl<T, maxValue>( r, g, b, a );
        }

        /** Write the point to a stream */
        inline friend std::ostream& operator<<( std::ostream& stream, const ColorTempl<T, maxValue>& src )
        {
            std::ostream::sentry opfx(stream);
            if ( !opfx )
                return stream;
            return ( stream << "Color( " << src.r << ", " << src.g << ", " << src.b << ", " << src.a << " )" );
        }

    }; // class ColorTempl

    /** @typedef Color
        A color definition using unsigned char as the data type, with a maximum
        component value of 255.
    */
    typedef ColorTempl< UInt8, 255 > Color;

    /** @typedef Colorf
        A color definition using Real as the data type, with a maximum
        component value of 1.0.
    */
    typedef ColorTempl< Real, 1 > Colorf;

} // namespace PGE

#endif // PGECOLOR_H_INCLUDED
