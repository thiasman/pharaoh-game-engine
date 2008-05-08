
/*! $Id$
 *  @file   PgePoint2D.h
 *  @author Chad M. Draper
 *  @date   May 7, 2007
 *
 */

#include "PgeMatrix2D.h"
#include "PgePoint2D.h"
#include "PgeMath.h"

namespace PGE
{
    const Matrix2D   Matrix2D::ZERO;
    const Matrix2D   Matrix2D::IDENTITY( 1, 0, 0, 0, 1, 0, 0, 0, 1 );

    Matrix2D::Matrix2D()
    {
        memset( m, 0, sizeof( Real ) * 9 );
    }

    Matrix2D::Matrix2D( Real mat[ 3 ][ 3 ] )
    {
        memcpy( m, mat, sizeof( Real ) * 9 );
    }

    Matrix2D::Matrix2D( const Matrix2D& mat )
    {
        memcpy( m, mat.m, sizeof( Real ) * 9 );
    }

    Matrix2D::Matrix2D( Real mat[ 9 ] )
    {
        memcpy( m, mat, sizeof( Real ) * 9 );
    }

    Matrix2D::Matrix2D( const Real* mat )
    {
        memcpy( m, mat, sizeof( Real ) * 9 );
    }

    Matrix2D::Matrix2D( Real m11, Real m12, Real m13,
              Real m21, Real m22, Real m23,
              Real m31, Real m32, Real m33 )
    {
        FillMatrix( m11, m12, m13, m21, m22, m23, m31, m32, m33 );
    }

    //FillMatrix----------------------------------------------------------------
    void Matrix2D::FillMatrix( const Real* mat )
    {
        memcpy( m, mat, sizeof( Real ) * 9 );
    }

    //FillMatrix----------------------------------------------------------------
    void Matrix2D::FillMatrix( Real m11, Real m12, Real m13,
              Real m21, Real m22, Real m23,
              Real m31, Real m32, Real m33 )
    {
        m[ 0 ][ 0 ] = m11; m[ 0 ][ 1 ] = m12; m[ 0 ][ 2 ] = m13;
        m[ 1 ][ 0 ] = m21; m[ 1 ][ 1 ] = m22; m[ 1 ][ 2 ] = m23;
        m[ 2 ][ 0 ] = m31; m[ 2 ][ 1 ] = m32; m[ 2 ][ 2 ] = m33;
    }

    //operator[]----------------------------------------------------------------
    Real* Matrix2D::operator[]( Int i )
    {
        assert( i >= 0 && i < 3 );
        return (Real*)m[ i ];
    }

    //GetMatrix-----------------------------------------------------------------
    void Matrix2D::GetMatrix( Real mat[ 9 ] ) const
    {
        memcpy( mat, m, sizeof( Real ) * 9 );
    }

    //GetMatrix-----------------------------------------------------------------
    void Matrix2D::GetMatrix( Real mat[ 3 ][ 3 ] ) const
    {
        memcpy( mat, m, sizeof( Real ) * 9 );
    }

    //Identity------------------------------------------------------------------
    void Matrix2D::Identity()
    {
        *this = IDENTITY;
    }

    //operator= ----------------------------------------------------------------
    Matrix2D& Matrix2D::operator=( const Matrix2D& mat )
    {
        memcpy( m, mat.m, sizeof( Real ) * 9 );
        return *this;
    }

    //operator== ---------------------------------------------------------------
    bool Matrix2D::operator==( const Matrix2D& mat ) const
    {
        for ( Int r = 0; r < 3; r++ )
        {
            for ( Int c = 0; c < 3; c++ )
            {
                if ( !Math::RealEqual( m[ r ][ c ], mat.m[ r ][ c ] ) )
                    return false;
            }
        }
        return true;
    }

    //operator!= ---------------------------------------------------------------
    bool Matrix2D::operator!=( const Matrix2D& mat ) const
    {
        return !( *this == mat );
    }

    // MergeMatrix--------------------------------------------------------------
    void Matrix2D::MergeMatrix( const Matrix2D& mat, MatrixOrder order )
    {
        Matrix2D mat1, mat2;
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

        for ( Int r = 0; r < 3; r++ )
        {
            for ( Int c = 0; c < 3; c++ )
            {
                m[ r ][ c ] =
                    mat1.m[ r ][ 0 ] * mat2.m[ 0 ][ c ] +
                    mat1.m[ r ][ 1 ] * mat2.m[ 1 ][ c ] +
                    mat1.m[ r ][ 2 ] * mat2.m[ 2 ][ c ];
            }
        }
    }

    // MergeMatrix--------------------------------------------------------------
    void Matrix2D::MergeMatrix( const Real mat[ 9 ], MatrixOrder order )
    {
        MergeMatrix( Matrix2D( mat ), order );
    }

    //Rotate--------------------------------------------------------------------
    void Matrix2D::Rotate( Real angle, MatrixOrder order )
    {
        Real mat[ 3 ][ 3 ];
        mat[ 0 ][ 0 ] = Math::Cos( angle );   mat[ 0 ][ 1 ] = -Math::Sin( angle );   mat[ 0 ][ 2 ] = 0;
        mat[ 1 ][ 0 ] = Math::Sin( angle );   mat[ 1 ][ 1 ] = Math::Cos( angle );    mat[ 1 ][ 2 ] = 0;
        mat[ 2 ][ 0 ] = 0;                    mat[ 2 ][ 1 ] = 0;                     mat[ 2 ][ 2 ] = 1;

        MergeMatrix( &mat[ 0 ][ 0 ], order );
    }

    //Scale---------------------------------------------------------------------
    void Matrix2D::Scale( Real sx, Real sy, MatrixOrder order )
    {
        Real mat[ 3 ][ 3 ];
        mat[ 0 ][ 0 ] = sx;   mat[ 0 ][ 1 ] = 0;   mat[ 0 ][ 2 ] = 0;
        mat[ 1 ][ 0 ] = 0;    mat[ 1 ][ 1 ] = sy;  mat[ 1 ][ 2 ] = 0;
        mat[ 2 ][ 0 ] = 0;    mat[ 2 ][ 1 ] = 0;   mat[ 2 ][ 2 ] = 1;

        MergeMatrix( &mat[ 0 ][ 0 ], order );
    }

    //Translate-----------------------------------------------------------------
    void Matrix2D::Translate( Real tx, Real ty, MatrixOrder order )
    {
        Real mat[ 3 ][ 3 ];
        mat[ 0 ][ 0 ] = 1;   mat[ 0 ][ 1 ] = 0;   mat[ 0 ][ 2 ] = tx;
        mat[ 1 ][ 0 ] = 0;   mat[ 1 ][ 1 ] = 1;   mat[ 1 ][ 2 ] = ty;
        mat[ 2 ][ 0 ] = 0;   mat[ 2 ][ 1 ] = 0;   mat[ 2 ][ 2 ] = 1;

        MergeMatrix( &mat[ 0 ][ 0 ], order );
    }

    Point2Df Matrix2D::Transform( const Point2Df& pt )
    {
        Point2Df ret;
        ret.x = pt.x * m[ 0 ][ 0 ] + pt.y * m[ 0 ][ 1 ] + m[ 0 ][ 2 ];
        ret.x = pt.x * m[ 1 ][ 0 ] + pt.y * m[ 1 ][ 1 ] + m[ 1 ][ 2 ];
        return ret;
    }


} // namespace PGE
