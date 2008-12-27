
/*! $Id$
 *  @file   PgeViewport.h
 *  @author Chad M. Draper
 *  @date   October 6, 2008
 *
 */

#include "PgeViewport.h"

namespace PGE
{
    Viewport::Viewport()
    {
    }

    Viewport::Viewport( const Point2D& size )
        : mPosition( Point2D( 0, 0 ) ),
          mSize( size )
    {
        //ctor
    }

    Viewport::~Viewport()
    {
        //dtor
    }

    //SetSize-------------------------------------------------------------------
    void Viewport::SetSize( Int w, Int h )
    {
        mSize = Point2D( w, h );
    }

    //GetSize-------------------------------------------------------------------
    const Point2D& Viewport::GetSize() const
    {
        return mSize;
    }

    //SetPosition---------------------------------------------------------------
    void Viewport::SetPosition( Int x, Int y )
    {
        mPosition = Point2D( x, y );
    }

    //GetPosition---------------------------------------------------------------
    const Point2D& Viewport::GetPosition() const
    {
        return mPosition;
    }

} // namespace PGE
