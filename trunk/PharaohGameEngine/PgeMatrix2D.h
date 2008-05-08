
/*! $Id$
 *  @file   PgePoint2D.h
 *  @author Chad M. Draper
 *  @date   May 7, 2007
 *  @brief  Contains class for a 2-dimensional matrix
 *
 */

#ifndef PGEMATRIX2D_H
#define PGEMATRIX2D_H

#include "PgeTypes.h"
//#include "PgePoint2D.h"
#include "PgeEnums.h"
#include <ostream>

namespace PGE
{
    class Point2Df;

    /** @class Matrix2D
        A matrix class for working with 2D points.
    */
    class Matrix2D
    {
    protected:
        Real m[ 3 ][ 3 ];

    public:
        static const Matrix2D   ZERO;       /**< Matrix filled with zeroes */
        static const Matrix2D   IDENTITY;   /**< Identity matrix */

        /** Constructor */
        Matrix2D();
        /** Constructor */
        explicit Matrix2D( Real mat[ 3 ][ 3 ] );
        /** Constructor */
        Matrix2D( const Matrix2D& mat );
        /** Constructor */
        Matrix2D( Real mat[ 9 ] );
        /** Constructor */
        Matrix2D( const Real* mat );
        /** Constructor */
        Matrix2D( Real m11, Real m12, Real m13,
                  Real m21, Real m22, Real m23,
                  Real m31, Real m32, Real m33 );

        /** Fill the matrix from an array of values */
        void FillMatrix( const Real* mat );
        /** Fill the matrix with given values */
        void FillMatrix( Real m11, Real m12, Real m13,
                  Real m21, Real m22, Real m23,
                  Real m31, Real m32, Real m33 );

        /** Access to the elements of the matrix */
        Real* operator[]( Int i );
        /** Get the elements of the matrix */
        void GetMatrix( Real mat[ 9 ] ) const;
        void GetMatrix( Real mat[ 3 ][ 3 ] ) const;

        /** Set the matrix to identity */
        void Identity();

        /** Assignment operator */
        Matrix2D& operator=( const Matrix2D& mat );

        /** Equality operator */
        bool operator==( const Matrix2D& mat ) const;
        /** Inequality operator */
        bool operator!=( const Matrix2D& mat ) const;

        /** Merge this matrix with another matrix */
        void MergeMatrix( const Matrix2D& mat, MatrixOrder order = MatrixOrderPrepend );
        void MergeMatrix( const Real mat[ 9 ], MatrixOrder order = MatrixOrderPrepend );

        /** Rotate the matrix by a given angle */
        void Rotate( Real angle, MatrixOrder order = MatrixOrderPrepend );

        /** Scale the matrix */
        void Scale( Real sx, Real sy, MatrixOrder order = MatrixOrderPrepend );

        /** Translate the matrix */
        void Translate( Real tx, Real ty, MatrixOrder order = MatrixOrderPrepend );

        /** Transform a point by the matrix */
        Point2Df Transform( const Point2Df& pt );



        /** Write to a stream */
        inline friend std::ostream& operator<<( std::ostream& stream, const Matrix2D& src )
        {
            std::ostream::sentry opfx(stream);
            if ( !opfx )
                return stream;
            stream << "Matrix2D {\n";
            stream << "        | " << src.m[ 0 ][ 0 ] << "  " << src.m[ 0 ][ 1 ] << "  " << src.m[ 0 ][ 2 ] << " |\n";
            stream << "        | " << src.m[ 1 ][ 0 ] << "  " << src.m[ 1 ][ 1 ] << "  " << src.m[ 1 ][ 2 ] << " |\n";
            stream << "        | " << src.m[ 2 ][ 0 ] << "  " << src.m[ 2 ][ 1 ] << "  " << src.m[ 2 ][ 2 ] << " |\n";
            stream << "    }\n";
            return stream;
        }

    }; // class Matrix2D

} // namespace PGE

#endif // PGEMATRIX2D_H
