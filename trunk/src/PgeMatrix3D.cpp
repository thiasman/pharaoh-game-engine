
/*! $Id$
 *  @file   PgePoint3D.h
 *  @author Chad M. Draper
 *  @date   May 7, 2007
 *
 */

#include "PgeMatrix3D.h"
#include "PgePoint3D.h"
#include "PgeMath.h"

namespace PGE
{
    const Matrix3D   Matrix3D::ZERO;
    const Matrix3D   Matrix3D::IDENTITY( 1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1 );

    Matrix3D::Matrix3D()
    {
        memset( m, 0, sizeof( Real ) * 16 );
    }

    Matrix3D::Matrix3D( Real mat[ 4 ][ 4 ] )
    {
        memcpy( m, mat, sizeof( Real ) * 16 );
    }

    Matrix3D::Matrix3D( const Matrix3D& mat )
    {
        memcpy( m, mat.m, sizeof( Real ) * 16 );
    }

    Matrix3D::Matrix3D( Real mat[ 16 ] )
    {
        memcpy( m, mat, sizeof( Real ) * 16 );
    }

    Matrix3D::Matrix3D( const Real* mat )
    {
        memcpy( m, mat, sizeof( Real ) * 16 );
    }

    Matrix3D::Matrix3D( Real m11, Real m12, Real m13, Real m14,
                  Real m21, Real m22, Real m23, Real m24,
                  Real m31, Real m32, Real m33, Real m34,
                  Real m41, Real m42, Real m43, Real m44 )
    {
        FillMatrix( m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44 );
    }

    //FillMatrix----------------------------------------------------------------
    void Matrix3D::FillMatrix( const Real* mat )
    {
        memcpy( m, mat, sizeof( Real ) * 16 );
    }

    //FillMatrix----------------------------------------------------------------
    void Matrix3D::FillMatrix( Real m11, Real m12, Real m13, Real m14,
                  Real m21, Real m22, Real m23, Real m24,
                  Real m31, Real m32, Real m33, Real m34,
                  Real m41, Real m42, Real m43, Real m44 )
    {
        m[ 0 ][ 0 ] = m11; m[ 0 ][ 1 ] = m12; m[ 0 ][ 2 ] = m13; m[ 0 ][ 3 ] = m14;
        m[ 1 ][ 0 ] = m21; m[ 1 ][ 1 ] = m22; m[ 1 ][ 2 ] = m23; m[ 1 ][ 3 ] = m24;
        m[ 2 ][ 0 ] = m31; m[ 2 ][ 1 ] = m32; m[ 2 ][ 2 ] = m33; m[ 2 ][ 4 ] = m34;
        m[ 3 ][ 0 ] = m41; m[ 3 ][ 1 ] = m42; m[ 3 ][ 2 ] = m43; m[ 3 ][ 4 ] = m44;
    }

    //operator[]----------------------------------------------------------------
    Real* Matrix3D::operator[]( Int i )
    {
        assert( i >= 0 && i < 4 );
        return (Real*)m[ i ];
    }

    //GetMatrix-----------------------------------------------------------------
    void Matrix3D::GetMatrix( Real mat[ 16 ] ) const
    {
        memcpy( mat, m, sizeof( Real ) * 16 );
    }

    //GetMatrix-----------------------------------------------------------------
    void Matrix3D::GetMatrix( Real mat[ 4 ][ 4 ] ) const
    {
        memcpy( mat, m, sizeof( Real ) * 16 );
    }

    //Identity------------------------------------------------------------------
    void Matrix3D::Identity()
    {
        *this = IDENTITY;
    }

    //operator= ----------------------------------------------------------------
    Matrix3D& Matrix3D::operator=( const Matrix3D& mat )
    {
        memcpy( m, mat.m, sizeof( Real ) * 16 );
        return *this;
    }

    //operator== ---------------------------------------------------------------
    bool Matrix3D::operator==( const Matrix3D& mat ) const
    {
        for ( Int r = 0; r < 4; r++ )
        {
            for ( Int c = 0; c < 4; c++ )
            {
                if ( !Math::RealEqual( m[ r ][ c ], mat.m[ r ][ c ] ) )
                    return false;
            }
        }
        return true;
    }

    //operator!= ---------------------------------------------------------------
    bool Matrix3D::operator!=( const Matrix3D& mat ) const
    {
        return !( *this == mat );
    }

    // MergeMatrix--------------------------------------------------------------
    void Matrix3D::MergeMatrix( const Matrix3D& mat, MatrixOrder order )
    {
        Matrix3D mat1, mat2;
        if ( order == MatrixOrderPrepend )
        {
            mat1 = *this;
            mat2 = mat;
        }
        else
        {
            mat1 = mat;
            mat2 = *this;
        }

        for ( Int r = 0; r < 4; r++ )
        {
            for ( Int c = 0; c < 4; c++ )
            {
                m[ r ][ c ] =
                    mat1.m[ r ][ 0 ] * mat2.m[ 0 ][ c ] +
                    mat1.m[ r ][ 1 ] * mat2.m[ 1 ][ c ] +
                    mat1.m[ r ][ 2 ] * mat2.m[ 2 ][ c ] +
                    mat1.m[ r ][ 3 ] * mat2.m[ 3 ][ c ];
            }
        }
    }

    // MergeMatrix--------------------------------------------------------------
    void Matrix3D::MergeMatrix( const Real mat[ 9 ], MatrixOrder order )
    {
        MergeMatrix( Matrix3D( mat ), order );
    }

    //RotateX-------------------------------------------------------------------
    void Matrix3D::RotateX( Real angle, MatrixOrder order )
    {
        Real mat[ 4 ][ 4 ];
        mat[ 0 ][ 0 ] = 1;                    mat[ 0 ][ 1 ] = 0;                     mat[ 0 ][ 2 ] = 0;                     mat[ 0 ][ 3 ] = 0;
        mat[ 1 ][ 0 ] = 0;                    mat[ 1 ][ 1 ] = Math::Cos( angle );    mat[ 1 ][ 2 ] = -Math::Sin( angle );   mat[ 1 ][ 3 ] = 0;
        mat[ 2 ][ 0 ] = 0;                    mat[ 2 ][ 1 ] = Math::Sin( angle );    mat[ 2 ][ 2 ] = Math::Cos( angle );    mat[ 2 ][ 3 ] = 0;
        mat[ 3 ][ 0 ] = 0;                    mat[ 3 ][ 1 ] = 0;                     mat[ 3 ][ 2 ] = 0;                     mat[ 3 ][ 3 ] = 1;

        MergeMatrix( &mat[ 0 ][ 0 ], order );
    }

    //RotateY-------------------------------------------------------------------
    void Matrix3D::RotateY( Real angle, MatrixOrder order )
    {
        Real mat[ 4 ][ 4 ];
        mat[ 0 ][ 0 ] = Math::Cos( angle );   mat[ 0 ][ 1 ] = 0;                     mat[ 0 ][ 2 ] = Math::Sin( angle );    mat[ 0 ][ 3 ] = 0;
        mat[ 1 ][ 0 ] = 0;                    mat[ 1 ][ 1 ] = 1;                     mat[ 1 ][ 2 ] = 0;                     mat[ 1 ][ 3 ] = 0;
        mat[ 2 ][ 0 ] = -Math::Sin( angle );  mat[ 2 ][ 1 ] = 0;                     mat[ 2 ][ 2 ] = Math::Cos( angle );    mat[ 2 ][ 3 ] = 0;
        mat[ 3 ][ 0 ] = 0;                    mat[ 3 ][ 1 ] = 0;                     mat[ 3 ][ 2 ] = 0;                     mat[ 3 ][ 3 ] = 1;

        MergeMatrix( &mat[ 0 ][ 0 ], order );
    }

    //RotateZ-------------------------------------------------------------------
    void Matrix3D::RotateZ( Real angle, MatrixOrder order )
    {
        Real mat[ 4 ][ 4 ];
        mat[ 0 ][ 0 ] = Math::Cos( angle );   mat[ 0 ][ 1 ] = -Math::Sin( angle );   mat[ 0 ][ 2 ] = 0;                     mat[ 0 ][ 3 ] = 0;
        mat[ 1 ][ 0 ] = Math::Sin( angle );   mat[ 1 ][ 1 ] = Math::Cos( angle );    mat[ 1 ][ 2 ] = 0;                     mat[ 1 ][ 3 ] = 0;
        mat[ 2 ][ 0 ] = 0;                    mat[ 2 ][ 1 ] = 0;                     mat[ 2 ][ 2 ] = 1;                     mat[ 2 ][ 3 ] = 0;
        mat[ 3 ][ 0 ] = 0;                    mat[ 3 ][ 1 ] = 0;                     mat[ 3 ][ 2 ] = 0;                     mat[ 3 ][ 3 ] = 1;

        MergeMatrix( &mat[ 0 ][ 0 ], order );
    }

    //Scale---------------------------------------------------------------------
    void Matrix3D::Scale( Real sx, Real sy, Real sz, MatrixOrder order )
    {
        Real mat[ 3 ][ 3 ];
        mat[ 0 ][ 0 ] = sx;   mat[ 0 ][ 1 ] = 0;   mat[ 0 ][ 2 ] = 0;   mat[ 0 ][ 3 ] = 0;
        mat[ 1 ][ 0 ] = 0;    mat[ 1 ][ 1 ] = sy;  mat[ 1 ][ 2 ] = 0;   mat[ 1 ][ 3 ] = 0;
        mat[ 2 ][ 0 ] = 0;    mat[ 2 ][ 1 ] = 0;   mat[ 2 ][ 2 ] = sz;  mat[ 2 ][ 3 ] = 0;
        mat[ 3 ][ 0 ] = 0;    mat[ 3 ][ 1 ] = 0;   mat[ 3 ][ 2 ] = 0;   mat[ 3 ][ 3 ] = 1;

        MergeMatrix( &mat[ 0 ][ 0 ], order );
    }

    //Translate-----------------------------------------------------------------
    void Matrix3D::Translate( Real tx, Real ty, Real tz, MatrixOrder order )
    {
        Real mat[ 3 ][ 3 ];
        mat[ 0 ][ 0 ] = 1;   mat[ 0 ][ 1 ] = 0;   mat[ 0 ][ 2 ] = 0;   mat[ 0 ][ 3 ] = tx;
        mat[ 1 ][ 0 ] = 0;   mat[ 1 ][ 1 ] = 1;   mat[ 1 ][ 2 ] = 0;   mat[ 1 ][ 3 ] = ty;
        mat[ 2 ][ 0 ] = 0;   mat[ 2 ][ 1 ] = 0;   mat[ 2 ][ 2 ] = 1;   mat[ 2 ][ 3 ] = tz;
        mat[ 3 ][ 0 ] = 0;   mat[ 3 ][ 1 ] = 0;   mat[ 3 ][ 2 ] = 0;   mat[ 3 ][ 3 ] = 1;

        MergeMatrix( &mat[ 0 ][ 0 ], order );
    }

    Point3Df Matrix3D::Transform( const Point3Df& pt )
    {
        Point3Df ret;
        ret.x = pt.x * m[ 0 ][ 0 ] + pt.y * m[ 0 ][ 1 ] + m[ 0 ][ 2 ];
        ret.x = pt.x * m[ 1 ][ 0 ] + pt.y * m[ 1 ][ 1 ] + m[ 1 ][ 2 ];
        return ret;
    }


} // namespace PGE
