
/*! $Id$
 *  @file   PgeViewport.h
 *  @author Chad M. Draper
 *  @date   October 6, 2008
 *  @brief  Representation of a viewport.
 *
 */

#ifndef PGEVIEWPORT_H
#define PGEVIEWPORT_H

#include "PgeTypes.h"
#include "PgePoint2D.h"
#include <ostream>

namespace PGE
{
    /** @class Viewport
        The viewport class is just a simple representation of the viewport.
        Essentially, the class defines the size and position of the viewport.
        Additionally, there are some debugging options which are contained here,
        such as being able to zoom out and see the tiles which will normally be
        clipped.
    */
    class _PgeExport Viewport
    {
    private:
        Point2D     mPosition;      ///< Top-left corner of the viewport
        Point2D     mSize;          ///< Size of the viewport

    public:
        /** Constructor */
        Viewport();
        /** Constructor */
        Viewport( const Point2D& size );
        virtual ~Viewport();

        /** Set the viewport size */
        void SetSize( Int w, Int h );
        /** Get the viewport size */
        const Point2D& GetSize() const;

        /** Set the position */
        void SetPosition( Int x, Int y );
        /** Get the position */
        const Point2D& GetPosition() const;

        /** Write the viewport to a stream */
        inline friend std::ostream& operator<<( std::ostream& stream, const Viewport& src )
        {
            std::ostream::sentry opfx(stream);
            if ( !opfx )
                return stream;
            return stream << "Viewport: position = " << src.mPosition << ", size = " << src.mSize << std::endl;
        }

    }; // class Viewport
} // namespace PGE

#endif // PGEVIEWPORT_H
