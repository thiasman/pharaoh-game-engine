
/*! $Id$
 *  @file   PgePoint3D.h
 *  @author Chad M. Draper
 *  @date   May 7, 2007
 *  @brief  Contains class for a 2-dimensional matrix.
 *
 */

#ifndef PGEMATRIX3D_H
#define PGEMATRIX3D_H


#include "PgeTypes.h"
//#include "PgePoint3D.h"
#include "PgeEnums.h"
#include <ostream>

namespace PGE
{
    class Point3Df;

    /** @class Matrix3D
        A matrix class for working with 3D points.
    */
    class _PgeExport Matrix3D
    {
    protected:
        Real m[ 4 ][ 4 ];

    public:
        static const Matrix3D   ZERO;       /**< Matrix filled with zeroes */
        static const Matrix3D   IDENTITY;   /**< Identity matrix */

        /** Constructor */
        Matrix3D();
        /** Constructor */
        explicit Matrix3D( Real mat[ 4 ][ 4 ] );
        /** Constructor */
        Matrix3D( const Matrix3D& mat );
        /** Constructor */
        Matrix3D( Real mat[ 16 ] );
        /** Constructor */
        Matrix3D( const Real* mat );
        /** Constructor */
        Matrix3D( Real m11, Real m12, Real m13, Real m14,
                  Real m21, Real m22, Real m23, Real m24,
                  Real m31, Real m32, Real m33, Real m34,
                  Real m41, Real m42, Real m43, Real m44 );

        /** Fill the matrix from an array of values */
        void FillMatrix( const Real* mat );
        /** Fill the matrix with given values */
        void FillMatrix( Real m11, Real m12, Real m13, Real m14,
                  Real m21, Real m22, Real m23, Real m24,
                  Real m31, Real m32, Real m33, Real m34,
                  Real m41, Real m42, Real m43, Real m44 );

        /** Access to the elements of the matrix */
        Real* operator[]( Int i );
        /** Get the elements of the matrix */
        void GetMatrix( Real mat[ 16 ] ) const;
        void GetMatrix( Real mat[ 4 ][ 4 ] ) const;

        /** Set the matrix to identity */
        void Identity();

        /** Assignment operator */
        Matrix3D& operator=( const Matrix3D& mat );

        /** Equality operator */
        bool operator==( const Matrix3D& mat ) const;
        /** Inequality operator */
        bool operator!=( const Matrix3D& mat ) const;

        /** Merge this matrix with another matrix */
        void MergeMatrix( const Matrix3D& mat, MatrixOrder order = MatrixOrderPrepend );
        void MergeMatrix( const Real mat[ 16 ], MatrixOrder order = MatrixOrderPrepend );

        /** Rotate the matrix by a given angle about the x-axis */
        void RotateX( Real angle, MatrixOrder order = MatrixOrderPrepend );

        /** Rotate the matrix by a given angle about the y-axis */
        void RotateY( Real angle, MatrixOrder order = MatrixOrderPrepend );

        /** Rotate the matrix by a given angle about the z-axis */
        void RotateZ( Real angle, MatrixOrder order = MatrixOrderPrepend );

        /** Scale the matrix */
        void Scale( Real sx, Real sy, Real sz, MatrixOrder order = MatrixOrderPrepend );

        /** Translate the matrix */
        void Translate( Real tx, Real ty, Real tz, MatrixOrder order = MatrixOrderPrepend );

        /** Transform a point by the matrix */
        Point3Df Transform( const Point3Df& pt );



        /** Write to a stream */
        inline friend std::ostream& operator<<( std::ostream& stream, const Matrix3D& src )
        {
            std::ostream::sentry opfx(stream);
            if ( !opfx )
                return stream;
            stream << "Matrix3D {\n";
            stream << "        | " << src.m[ 0 ][ 0 ] << "  " << src.m[ 0 ][ 1 ] << "  " << src.m[ 0 ][ 2 ] << "  " << src.m[ 0 ][ 3 ] << " |\n";
            stream << "        | " << src.m[ 1 ][ 0 ] << "  " << src.m[ 1 ][ 1 ] << "  " << src.m[ 1 ][ 2 ] << "  " << src.m[ 1 ][ 3 ] << " |\n";
            stream << "        | " << src.m[ 2 ][ 0 ] << "  " << src.m[ 2 ][ 1 ] << "  " << src.m[ 2 ][ 2 ] << "  " << src.m[ 2 ][ 3 ] << " |\n";
            stream << "        | " << src.m[ 3 ][ 0 ] << "  " << src.m[ 3 ][ 1 ] << "  " << src.m[ 3 ][ 2 ] << "  " << src.m[ 3 ][ 3 ] << " |\n";
            stream << "    }\n";
            return stream;
        }

    }; // class Matrix3D

} // namespace PGE

#endif // PGEMATRIX3D_H
