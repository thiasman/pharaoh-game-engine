
/*! $Id$
 *  @file   PgeMath.cpp
 *  @author Chad M. Draper
 *  @date   May 7, 2008
 *
 */

#include "PgeMath.h"
#include <math.h>
#include <stdlib.h>
#include "cmd/StringUtil.h"

namespace PGE
{
    const Real Math::pi         = 3.14159;
    const Real Math::half_pi    = static_cast<Real>( Math::pi / 2.0 );
    const Real Math::two_pi     = static_cast<Real>( 2.0 * Math::pi );
    const Real Math::rad_2_deg  = static_cast<Real>( 180.0 / Math::pi );
    const Real Math::deg_2_rad  = static_cast<Real>( Math::pi / 180.0 );
    const Real Math::epsilon    = std::numeric_limits< Real >::epsilon();


    //Lerp----------------------------------------------------------------------
    Real Math::Lerp( Real n1, Real n2, Real ratio )
    {
        return ( n2 - n1 ) * ratio + n1;
    }

    //InterpCosine--------------------------------------------------------------
    Real Math::InterpCosine( Real ratio, Real low, Real high, Real easeInOut )
    {
        Real th = ratio * Math::pi;
        Real f  = ( 1.0 - Math::Cos( th ) ) * 0.5;

        // The interpolation will now be done linearly.  Do linear
        // interpolation between the 'ratio' and 'f' using the easeInOut
        // parameter to find the new ratio:
        f = Lerp( easeInOut, ratio, f );
        return low + ( high - low ) * f;
    }

    //InterpCosine--------------------------------------------------------------
    Real Math::InterpStep( Real ratio, Real low, Real high )
    {
        return ( ratio < 1.0 ) ? low : high;
    }

    //InterpCubic---------------------------------------------------------------
    Real InterpCubic( Real ratio, Real v0, Real v1, Real v2, Real v3 )
    {
        Real p   = ( v3 - v2 ) - ( v0 - v1 );
        Real q   = ( v0 - v1 ) - p;
        Real r   = ( v2 - v0 );
        Real s   = v1;

        return p * ( ratio * ratio * ratio ) + q * ( ratio * ratio ) + r * ratio + s;
    }

    //InterpQuadratic-----------------------------------------------------------
    Real Math::InterpQuadratic( Real v1, Real v2, Real v3, Real ratio )
    {
        return ( v1 * ( 1.0 - ratio ) * ( 1.0 - ratio ) + 2 * v2 * ratio * ( 1.0 - ratio ) + v3 * ratio * ratio );
    }

    //Sqrt----------------------------------------------------------------------
    Real Math::Sqrt( Real n )
    {
        return static_cast< Real >( sqrt( n ) );
    }

    //Sqr-----------------------------------------------------------------------
    Real Math::Sqr( Real n )
    {
        return n * n;
    }

    //Cube----------------------------------------------------------------------
    Real Math::Cube( Real n )
    {
        return n * n * n;
    }

    //Cosine--------------------------------------------------------------------
    Real Math::Cos( Real n )
    {
        return cos( n );
    }
    //ArcCosine-----------------------------------------------------------------
    Real Math::ACos( Real n )
    {
        return acos( n );
    }
    //Sine----------------------------------------------------------------------
    Real Math::Sin( Real n )
    {
        return sin( n );
    }
    //ArcSine-------------------------------------------------------------------
    Real Math::ASin( Real n )
    {
        return asin( n );
    }
    //Tangent-------------------------------------------------------------------
    Real Math::Tan( Real n )
    {
        return tan( n );
    }
    //ArcTangent----------------------------------------------------------------
    Real Math::ATan( Real n )
    {
        return atan( n );
    }
    //ArcTangent2----------------------------------------------------------------
    Real Math::ATan2( Real n, Real y )
    {
        return atan2( n, y );
    }

    //Logarithm-----------------------------------------------------------------
    Real Math::Log( Real n )
    {
        return static_cast< Real >( log( n ) );
    }

    //Exponential---------------------------------------------------------------
    Real Math::Exp( Real n )
    {
        return static_cast<Real>( exp( n ) );
    }

    //Power---------------------------------------------------------------------
    Real Math::Pow( Real n, Real y )
    {
        return static_cast<Real>( pow( n, y ) );
    }

    //Min-----------------------------------------------------------------------
    Real Math::Min( Real n1, Real n2 )
    {
        if ( n1 < n2 )
            return n1;
        return n2;
    }

    //Max-----------------------------------------------------------------------
    Real Math::Max( Real n1, Real n2 )
    {
        if ( n1 < n2 )
            return n2;
        return n1;
    }

    //IMin----------------------------------------------------------------------
    Int Math::IMin( Int n1, Int n2 )
    {
        if ( n1 < n2 )
            return n1;
        return n2;
    }

    //IMax----------------------------------------------------------------------
    Int Math::IMax( Int n1, Int n2 )
    {
        if ( n1 < n2 )
            return n2;
        return n1;
    }

    //RangeRandom---------------------------------------------------------------
    Real Math::RangeRandom( Real low, Real high )
    {
        Real ratio = UnitRandom();
        return Lerp( low, high, ratio );
    }

    //IRangeRandom---------------------------------------------------------------
    Int Math::IRangeRandom( Int low, Int high )
    {
        return IClamp( static_cast<Int>( Round( RangeRandom( low, high ) ) ), low, high );
    }

    //SymmetricRandom-----------------------------------------------------------
    Real Math::SymmetricRandom( Real n )
    {
        return RangeRandom( -n, n );
    }

    //ISymmetricRandom-----------------------------------------------------------
    Int Math::ISymmetricRandom( Int n )
    {
        return IRangeRandom( -n, n );
    }

    //UnitRandom----------------------------------------------------------------
    Real Math::UnitRandom()
    {
        return static_cast<Real>( rand() ) / static_cast<Real>( RAND_MAX );
    }

    //Abs-----------------------------------------------------------------------
    Real Math::Abs( Real n )
    {
        if ( n < 0 )
            return -n;
        return n;
    }

    //IAbs----------------------------------------------------------------------
    Int Math::IAbs( Int n )
    {
        if ( n < 0 )
            return -n;
        return n;
    }

    //Sign----------------------------------------------------------------------
    Real Math::Sign( Real n )
    {
        if ( n < 0 )
            return -1;
        if ( n > 0 )
            return 1;
        return 0;
    }

    //ISign---------------------------------------------------------------------
    Int Math::ISign( Int n )
    {
        if ( n < 0 )
            return -1;
        if ( n > 0 )
            return 1;
        return 0;
    }

    //Floor---------------------------------------------------------------------
    Real Math::Floor( Real n )
    {
        return static_cast< Real >( floor( n ) );
    }

    //IFloor--------------------------------------------------------------------
    Int Math::IFloor( Int n )
    {
        return static_cast< Int >( floor( n ) );
    }

    //Ceil----------------------------------------------------------------------
    Real Math::Ceil( Real n )
    {
        return static_cast< Real >( ceil( n ) );
    }

    //ICeil---------------------------------------------------------------------
    Int Math::ICeil( Int n )
    {
        return static_cast< Int >( ceil( n ) );
    }

    //Round---------------------------------------------------------------------
    Real Math::Round( Real n )
    {
        return Floor( n + 0.5 );
    }

    //RoundTo-------------------------------------------------------------------
    Real Math::RoundTo( Real n, Int numDigits )
    {
        Real multiplier = Pow( 10.0, numDigits );
        return Round( n * multiplier ) / multiplier;
    }

    //Clamp---------------------------------------------------------------------
    Real Math::Clamp( Real val, Real low, Real high )
    {
        if ( high < low )
            return ( val < high ) ? high : ( val > low ) ? low : val;
        return ( val < low ) ? low : ( val > high ) ? high : val;
    }

    //IClamp--------------------------------------------------------------------
    Int Math::IClamp( Int val, Int low, Int high )
    {
        if ( high < low )
            return ( val < high ) ? high : ( val > low ) ? low : val;
        return ( val < low ) ? low : ( val > high ) ? high : val;
    }

    //Mod-----------------------------------------------------------------------
    Real Math::Mod( Real n1, Real n2 )
    {
        return static_cast<Real>( fmod( n1, n2 ) );
    }

    //ModRange------------------------------------------------------------------
    Real Math::ModRange( Real n, Real low, Real high )
    {
        if ( low == high )
            return low;

        if ( high < low )
            Swap( low, high );

        Real range = high - low;
        n -= low;
        if ( n < 0.0 )
        {
            n  = fmod( n, range );
            n  = fmod( n + range, range );
//            val += range;
        }
        else
            n = fmod( n, range );
        n += low;

        return n;
    }

    //ModRangeInclusive---------------------------------------------------------
    Real Math::ModRangeInclusive( Real n, Real low, Real high )
    {
        if ( low == high )
            return low;

        if ( high < low )
            Math::Swap( low, high );

        Real range = high - low;
        while ( n < low )    n += range;
        while ( n > high )n -= range;

        return n;
    }

    //IMod----------------------------------------------------------------------
    Int Math::IMod( Int n1, Int n2 )
    {
        return static_cast<Int>( n1 % n2 );
    }

    //IModRange-----------------------------------------------------------------
    Int Math::IModRange( Int n, Int low, Int high )
    {
        if ( low == high )
            return low;

        if ( high < low )
            Math::Swap( low, high );

        Real range = high - low;
        n -= low;
        if ( n < 0.0 )
        {
            n  = static_cast<Int>( fmod( n, range ) );
            n  = static_cast<Int>( fmod( n + range, range ) );
//            val += range;
        }
        else
            n = static_cast<Int>( fmod( n, range ) );
        n += low;

        return n;
    }

    //IModRangeInclusive--------------------------------------------------------
    Int Math::IModRangeInclusive( Int n, Int low, Int high )
    {
        if ( low == high )
            return low;

        if ( high < low )
            Math::Swap( low, high );

        int range = ( high - low ) + 1;
        n -= low;
        if ( n < 0 )
        {
            n %= range;
            n += range;
        }
        else
            n %= range;
        n += low;

        return n;
    }

    //RadiansToDegrees----------------------------------------------------------
    Real Math::RadiansToDegrees( Real angle )
    {
        return angle * rad_2_deg;
    }

    //DegreesToRadians----------------------------------------------------------
    Real Math::DegreesToRadians( Real angle )
    {
        return angle * deg_2_rad;
    }

    //IReflect------------------------------------------------------------------
    Int Math::IReflect( int val, int pivot )
    {
        return pivot + ( pivot - val );
    }
    //Reflect-------------------------------------------------------------------
    Real Math::Reflect( Real val, Real pivot )
    {
        return pivot + ( pivot - val );
    }

    //IReflectRange-------------------------------------------------------------
    Int Math::IReflectRange( Int val, Int minVal, Int maxVal )
    {
        if ( maxVal < minVal )
            Swap( minVal, maxVal );
        int diff = ( maxVal - minVal );
        val = Math::IAbs( ( val - minVal ) % ( diff * 2 ) );
        if ( val > diff )
            val = IReflect( val, diff );
        val += minVal;

        return val;
    }
    //ReflectRange--------------------------------------------------------------
    Real Math::ReflectRange( Real val, Real minVal, Real maxVal )
    {
        if ( maxVal < minVal )
            Swap( minVal, maxVal );
        Real diff = ( maxVal - minVal );
        val = Math::Abs( Math::Mod( val - minVal, diff * 2.0 ) );
        if ( val > diff )
            val = Reflect( val, diff );
        val += minVal;

        return val;
    }

    //ReflectSine---------------------------------------------------------------
    Real Math::ReflectSine( Real val, Real minVal, Real maxVal )
    {
        if ( minVal == maxVal )
            return minVal;

        // Calculate the ratio:
        Real diff = maxVal - minVal;
        Real ratio = ( val - minVal ) / ( 2.0 * diff );

        // Interpolate using a sine curve:
        return ( Sin( ratio * two_pi - half_pi ) * 0.5 + 0.5 ) * diff + minVal;
    }


    //Int2Hex-------------------------------------------------------------------
    String Math::Int2Hex( UInt32 intVal )
    {
        // Create a string containing the hex characters in order:
        String hexChars = "0123456789ABCDEF";

        // Convert the integer to the corresponding hex code:
        String hexString = "";
        do
        {
            hexString = hexChars[ intVal % 16 ] + hexString;
        } while ( ( intVal = intVal >> 4 ) > 0 );

        return hexString;
    }

    //Hex2Int-------------------------------------------------------------------
    UInt32 Math::Hex2Int( String hexVal )
    {
        // Create a string containing the hex characters in order:
        String hexChars = "0123456789ABCDEF";

        // Convert the hex string to the corresponding integer:
        Int intVal = 0;
        cmd::StringUtil::toUpper( hexVal );
        String::const_iterator hexIter;
        for ( hexIter = hexVal.begin(); hexIter != hexVal.end(); hexIter++ )
        {
            Int charVal = String::npos;
            switch ( *hexIter )
            {
            case '0':
                charVal = 0;
                break;

            case '1':
                charVal = 1;
                break;

            case '2':
                charVal = 2;
                break;

            case '3':
                charVal = 3;
                break;

            case '4':
                charVal = 4;
                break;

            case '5':
                charVal = 5;
                break;

            case '6':
                charVal = 6;
                break;

            case '7':
                charVal = 7;
                break;

            case '8':
                charVal = 8;
                break;

            case '9':
                charVal = 9;
                break;

            case 'A':
                charVal = 10;
                break;

            case 'B':
                charVal = 11;
                break;

            case 'C':
                charVal = 12;
                break;

            case 'D':
                charVal = 13;
                break;

            case 'E':
                charVal = 14;
                break;

            case 'F':
                charVal = 15;
                break;
            }

            if ( charVal != String::npos )
                intVal = ( intVal << 4 ) + charVal;
        }

        return intVal;
    }

    //SawtoothSin---------------------------------------------------------------
    Real Math::SawtoothSin( Real angle )
    {
        // Depending on which quadrant the angle is in, return a diagonal value:
        Real ang1 = ModRange( angle, 0.0, two_pi );
        Real ang2 = Mod( ang1, half_pi );
        Real ang3;

        if ( ang1 >= ( pi + half_pi ) )
            ang3 = -half_pi + ang2;
        else if ( ang1 >= pi )
            ang3 = -ang2;
        else if ( ang1 >= half_pi )
            ang3 = half_pi - ang2;
        else
            ang3 = ang2;

        return ang3 / half_pi;
    }

    //StepSin-------------------------------------------------------------------
    Real Math::StepSin( Real angle )
    {
        Real ang = ModRange( angle, 0.0, two_pi );
        return ( ang < pi ) ? 1.0 : -1.0;
    }

    //RectToPolar---------------------------------------------------------------
    void Math::RectToPolar( Real* ang, Real* dist, Int x, Int y, Int centerX, Int centerY, Real scaleX, Real scaleY )
    {
        // Calculate the offsets:
        Real dx = Real( x - centerX ) * scaleX;
        Real dy = Real( y - centerY ) * scaleY;

        // The angle is calculated as the inverse tangent of dy/dx.  If
        // dx == 0, then the angle is either +/- 90 degrees, based on the
        // sign of dy.
        if ( dx == 0.0 )
        {
            *ang = Math::half_pi * Math::Sign( dy );
        }
        else
            *ang = Math::ATan2( dy, dx );
        *dist = Math::Sqrt( dx * dx + dy * dy );
    }

    //RectToPolar---------------------------------------------------------------
    void Math::RectToPolar( Real* ang, Real* dist, Real x, Real y, Real centerX, Real centerY, Real scaleX, Real scaleY )
    {
        // Calculate the offsets:
        Real dx = ( x - centerX ) * scaleX;
        Real dy = ( y - centerY ) * scaleY;

        // The angle is calculated as the inverse tangent of dy/dx.  If
        // dx == 0, then the angle is either +/- 90 degrees, based on the
        // sign of dy.
        if ( dx == 0.0 )
        {
            *ang = Math::half_pi * Math::Sign( dy );
        }
        else
            *ang = Math::ATan2( dy, dx );
        *dist = Math::Sqrt( dx * dx + dy * dy );
    }

    void Math::PolarToRect( Real ang, Real dist, Int* x, Int* y, Int centerX, Int centerY )
    {
        *x = static_cast<Int>( Math::Round( centerX + dist * Math::Cos( ang ) ) );
        *y = static_cast<Int>( Math::Round( centerY + dist * Math::Sin( ang ) ) );
    }
    void Math::PolarToRect( Real ang, Real dist, Real* x, Real* y, Real centerX, Real centerY )
    {
        *x = centerX + dist * Math::Cos( ang );
        *y = centerY + dist * Math::Sin( ang );
    }

    //FindMSB-------------------------------------------------------------------
    UInt32 Math::FindMSB( UInt32 val )
    {
        int pos = 0;
        while ( val >>= 1 )
            ++pos;
        return pos;
    }

    //IsPowerOf2----------------------------------------------------------------
    bool Math::IsPowerOf2( UInt32 val )
    {
        if ( val )
        {
            return ( ( val & ( val - 1 ) ) == 0 );
        }
        return false;
    }

    //FindNextPowerOf2----------------------------------------------------------
    UInt32 Math::FindNextPowerOf2( UInt32 start )
    {
        UInt32 msb = FindMSB( start );

        // Shifting 1 to the left msb + 1 times will give the next power of 2
        return ( 1 << ( msb + 1 ) );
    }

    ////////////////////////////////////////////////////////////////////////////
    // RandomString
    ////////////////////////////////////////////////////////////////////////////

    const String RandomString::DefaultChars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //RandomString--------------------------------------------------------------
    RandomString::RandomString()
        : CustomChars( DefaultChars )
    {
    }
    //RandomString--------------------------------------------------------------
    RandomString::RandomString( const String& legalChars )
        : CustomChars( legalChars )
    {
    }

    //SetLegalChars-------------------------------------------------------------
    void RandomString::SetLegalChars( const String& legalChars )
    {
        CustomChars = legalChars;
    }

    //GetCustomString-----------------------------------------------------------
    String RandomString::GetCustomString( size_t length ) const
    {
        String result = "";
        if ( CustomChars.length() < 1 )
            return RandomString::GetRandomString( length );
        for ( size_t i = 0; i < length; i++ )
        {
            result += CustomChars[ Math::IRangeRandom( 0, CustomChars.length() ) ];
        }
        return result;
    }

    //GetRandomString-----------------------------------------------------------
    String RandomString::GetRandomString( size_t length )
    {
        String result = "";
        for ( size_t i = 0; i < length; i++ )
        {
            result += DefaultChars[ Math::IRangeRandom( 0, DefaultChars.length() ) ];
        }
        return result;
    }

}
