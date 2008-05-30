
/*! $Id$
 *  @file   PgeBaseEntity.h
 *  @author Chad M. Draper
 *  @date   May 7, 2008
 *  @brief  Defines the BaseEntity class
 *
 */

#ifndef PGEBASEENTITY_H_INCLUDED
#define PGEBASEENTITY_H_INCLUDED

#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif

#include "PgeBaseEntityInterface.h"
#include "PgeTypes.h"
#include "PgePoint2D.h"

namespace PGE
{
    /** @class BaseEntity
        All characters and tiles in the game will be derived from BaseEntity.
    */
    class _PgeExport BaseEntity : public BaseEntityInterface
    {
    private:
        Point2D         mPosition;          /**< Position of the entity */
        SDL_Surface*    mSurface;           /**< Surface for rendering the entity */
        bool            mIsVisible;         /**< Indicates if the entity should be rendered */
        Real            mAlpha;             /**< Alpha transparency value */
        String          mImageFileName;     /**< Name of the image file, used as a key for the texture manager */
        Point2D         mTilePosition;      /**< Index of the entity tile within the source image */

        /** Set the x-coordinate of the entity */
        void    SetPosX( Int pos )          { mPosition.x = pos; }
        /** Set the y-coordinate of the entity */
        void    SetPosY( Int pos )          { mPosition.y = pos; }
        /** Set the position of the entity */
        void    SetPosition( const Point2D& pos )   { mPosition = pos; }

    protected:
        /** Load the image from a file */
        virtual void LoadImageFile( const String& imageFileName );

        /** Get the x-coordinate of the entity */
        Int     GetPosX() const             { return mPosition.x; }
        /** Get the y-coordinate of the entity */
        Int     GetPosY() const             { return mPosition.y; }

        /** Set the alpha transparency */
        void    SetAlpha( Real alpha )      { mAlpha = alpha; }

        /** Set the visibility */
        void    SetVisibility( bool visible )   { mIsVisible = visible; }

    public:
        /** Constructor */
        BaseEntity();

        /** Destructor */
        virtual ~BaseEntity();

        /** Perform any logic for the tile.  This could be advanced AI, in the
            case of an AI character, or it could be simple routines, such as
            constant rotating.  If a tile does nothing at all, this isn't going
            to be very exciting.
        */
        virtual void    DoLogic( unsigned long elapsedTime );

        /** Render the entity to the display
            @param  surface     Surface onto which the entity will be rendered
        */
        virtual void    Render( SDL_Surface* surface );

        /** Load the entity from an XML file
            @param  xmlData     XML data stream containing the entity information
            @return true if loaded successfully, false otherwise.
        */
        virtual bool    Load( TiXmlElement* xmlData );

        /** Get the XML data for saving this entity
            @return TiXmlElement pointer to the data for this entity.
        */
        virtual TiXmlElement* GetSaveData() const;

    }; // class BaseEntity

} // namespace PGE

#endif // PGEBASEENTITY_H_INCLUDED
