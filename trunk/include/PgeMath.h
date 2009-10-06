
/*! $Id$
 *  @file   PgeMath.h
 *  @author Chad M. Draper
 *  @date   May 7, 2008
 *  @brief  Some useful mathematical routines and constants.
 *
 */
#ifndef PGEMATH_H
#define PGEMATH_H

#include "PgeTypes.h"
#include <limits>
#include <math.h>

namespace PGE
{
    class _PgeExport Math
    {
    public:
        static const Real       pi;
        static const Real       half_pi;
        static const Real       two_pi;
        static const Real       rad_2_deg;
        static const Real       deg_2_rad;
        static const Real       epsilon;


        /** Compare Real values for equality */
        static inline bool RealEqual( Real r1, Real r2 )
        {
            return ( static_cast< Real >( fabs( r1 - r2 ) ) <= epsilon );
        }

        /** Get the absolute value of a number */
        static Real Abs( Real n );
        /** Get the absolute value of a number */
        static Int IAbs( Int n );
        /** Get the sign of a number */
        static Real Sign( Real n );
        /** Get the sign of a number */
        static Int ISign( Int n );
        /** Get the floor of a number */
        static Real Floor( Real n );
        /** Get the floor of a number */
        static Int IFloor( Int n );
        /** Get the ceiling of a number */
        static Real Ceil( Real n );
        /** Get the ceiling of a number */
        static Int ICeil( Int n );
        /** Round a number */
        static Real Round( Real n );
        /** Round a number to a given decimal position */
        static Real RoundTo( Real n, Int numDigits );

        /** Linear interpolation between two numbers */
        static Real Lerp( Real n1, Real n2, Real ratio );

        /** Cosine interpolation using an ease in/out ratio
            @param  ratio   Interpolation ratio
            @param  low     Lower bounds of the range
            @param  high    Upper bounds of the range
            @param  easeInOut   Amount to ease in and out
        */
        static Real InterpCosine( Real ratio, Real low, Real high, Real easeInOut );

        /** Perform step interpolation, where the minimum value is
            returned for ratios less than 1, and the  maximum value is
            returned for ratios >= 1.
            @param  ratio       Interpolation ratio
            @param  low         Lower bounds of the range
            @param  high        Upper bounds of the range
        */
        static Real InterpStep( Real ratio, Real low, Real high );

        /** Perform cubic interpolation.  Cubic interpolation requires
            4 parameters: the value before the minimum, the minimum, the
            maximum, and the value after the maximum.
        */
        static Real InterpCubic( Real ratio, Real v0, Real v1, Real v2, Real v3 );

        /** Perform quadratic interpolation */
        static Real InterpQuadratic( Real v1, Real v2, Real v3, Real ratio );

        /** Calculate the square root of a number */
        static Real Sqrt( Real n );

        /** Calculate the square of a number */
        static Real Sqr( Real n );

        /** Cube a number */
        static Real Cube( Real n );

        /** Swap two numbers */
        template< typename T >
        static void Swap( T& n1, T& n2 )
        {
            T temp = n1;
            n1 = n2;
            n2 = temp;
        }

        /** Cosine */
        static Real Cos( Real n );
        /** ArcCosine */
        static Real ACos( Real n );
        /** Sine */
        static Real Sin( Real n );
        /** ArcSine */
        static Real ASin( Real n );
        /** Tangent */
        static Real Tan( Real n );
        /** ArcTangent */
        static Real ATan( Real n );
        /** ArcTangent2 */
        static Real ATan2( Real n, Real y );
        /** Logarithm */
        static Real Log( Real n );
        /** Exponential */
        static Real Exp( Real n );
        /** Calculate n^y */
        static Real Pow( Real n, Real y );

        /** Take the minimum of two numbers */
        static Real Min( Real n1, Real n2 );
        /** Take the maximum of two numbers */
        static Real Max( Real n1, Real n2 );
        /** Take the minimum of two numbers */
        static Int IMin( Int n1, Int n2 );
        /** Take the maximum of two numbers */
        static Int IMax( Int n1, Int n2 );

        /** Select a random number within a range */
        static Real RangeRandom( Real low, Real high );
        /** Select a random number within a range */
        static Int  IRangeRandom( Int low, Int high );
        /** Select a random number within +/- a value */
        static Real SymmetricRandom( Real n );
        /** Select a random number within +/- a value */
        static Int  ISymmetricRandom( Int n );
        /** Select a random number between 0 and 1 (inclusive) */
        static Real UnitRandom();

        /** Clamp a value to a range */
        static Real Clamp( Real val, Real low, Real high );
        /** Clamp a value to a range */
        static Int IClamp( Int val, Int low, Int high );

        /** Calculate the modulus of two numbers */
        static Real Mod( Real n1, Real n2 );
        /** Calculate the modulus of a number within a range */
        static Real ModRange( Real n, Real low, Real high );
        /** Calculate the modulus of a number within a range (inclusive) */
        static Real ModRangeInclusive( Real n, Real low, Real high );
        /** Calculate the modulus of two numbers */
        static Int IMod( Int n1, Int n2 );
        /** Calculate the modulus of a number within a range */
        static Int IModRange( Int n, Int low, Int high );
        /** Calculate the modulus of a number within a range (inclusive) */
        static Int IModRangeInclusive( Int n, Int low, Int high );

        /** Convert a value from radians to degrees */
        static Real RadiansToDegrees( Real angle );
        /** Convert a value from degrees to radian */
        static Real DegreesToRadians( Real angle );

        /**
            Reflect a value about a specfied pivot.
            @remarks
            The value is mirrored about the pivot so that the new value equals
            the pivot plus the pivot minus the original value.  There is no
            additional bounds checking.  For example, reflect( 3, 4 ) = 5,
            reflect( 10, 3 ) = -4.
        */
        static Int IReflect( int val, int pivot );
        static Real Reflect( Real val, Real pivot );

        /**
            Keep a value within a range, by reflecting it about the boundaries.
            @remarks
            If the value is less than the minimum of the range, reflect about
            the minimum.  If the value is greater than the range maximum,
            reflect about the maximum.  If the value is within the range, do
            nothing.
        */
        static Int IReflectRange( Int val, Int minVal, Int maxVal );
        static Real ReflectRange( Real val, Real minVal, Real maxVal );

        /** Reflect a value the boundaries of a range, using a sine curve.  This
            will result in a smoother reflection than ReflectRange.
        */
        static Real ReflectSine( Real val, Real minVal, Real maxVal );

        /** Convert a base 10 integer value to a hexadecimal string */
        static String Int2Hex( UInt32 intVal );

        /** Convert an hexadecimal string to base 10 integer */
        static UInt32 Hex2Int( String hexVal );

        /** Calculate the sawtooth sine of an angle:
            @param  angle       Angle in radians
        */
        static Real SawtoothSin( Real angle );

        /** Calculate the step sine of an angle:
            @param  angle       Angle in radians
        */
        static Real StepSin( Real angle );

        /** Convert rectancular coordinates to polar coordinates */
        static void RectToPolar( Real* ang, Real* dist, Int x, Int y, Int centerX, Int centerY, Real scaleX = 1.0, Real scaleY = 1.0 );
        static void RectToPolar( Real* ang, Real* dist, Real x, Real y, Real centerX, Real centerY, Real scaleX = 1.0, Real scaleY = 1.0 );

        /** Convert polar coordinates to rectangular coordinates */
        static void PolarToRect( Real ang, Real dist, Int* x, Int* y, Int centerX, Int centerY );
        static void PolarToRect( Real ang, Real dist, Real* x, Real* y, Real centerX, Real centerY );

        /** Find the most significant bit of a number */
        static UInt32 FindMSB( UInt32 val );

        /** Test whether a number is a power of 2 */
        static bool IsPowerOf2( UInt32 val );

        /** Get the next value, after a given number, that is a power of 2 */
        static UInt32 FindNextPowerOf2( UInt32 start );

    }; // class Math

    /** @class RandomString
        Generates a random string of characters.

        @remarks
            By default, legal characters in the random string are alphanumeric,
            upper and lowercase.  If a custom set of characters are desired,
            use the <code>SetLegalChars</code> method to set the string of
            characters to select from.  Then, use the <code>GetCustomString</code>
            to get a random string using the custom characters.

        @note
            Only the default characters will be returned when using the static
            method <code>GetRandomString</code>.  To get a string using custom
            characters, the class must be instantiated.
    */
    class _PgeExport RandomString
    {
    private:
        static const String DefaultChars;
        String CustomChars;

    public:
        /** Constructor
            @remarks
                The class is instantiated, and the custom characters is set to
                the default characters.  Use <code>SetLegalChars</code> to set
                a custom set of characters.
        */
        RandomString();
        /** Initialization constructor
            @param  legalChars          String of characters to use for a custom random string
        */
        RandomString( const String& legalChars );

        /** Set the custom set of characters */
        void SetLegalChars( const String& legalChars );

        /** Get a random string of characters using the custom characters
            @param  length              Length of the returned string
        */
        String GetCustomString( size_t length ) const;

        /** Get a random string of characters using the default characters
            @param  length              Length of the returned string
        */
        static String GetRandomString( size_t length );
    };

} // namespace PGE

#endif // PGEMATH_H
