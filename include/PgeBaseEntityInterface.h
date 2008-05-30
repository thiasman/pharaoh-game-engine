
/*! $Id$
 *  @file   PgeBaseEntity.h
 *  @author Chad M. Draper
 *  @date   May 7, 2008
 *  @brief  Defines the BaseEntityInterface class, which is used by all entities
 *          in the game.  An entity is anything that moves or interacts with the
 *          player.  This includes: the player, enemies, villagers, treasure
 *          chests, power-ups, etc.
 *
 */

#ifndef PGEBASEENTITYINTERFACE_H_INCLUDED
#define PGEBASEENTITYINTERFACE_H_INCLUDED

#include "PgeTypes.h"
#include "tinyxml.h"

namespace PGE
{
    /** @class BaseEntityInterface
        All characters and items in the game will be derived from BaseEntity.
        BaseEntityInterface basically just defines the interface for loading and
        manipulating the tiles.
    */
    class _PgeExport BaseEntityInterface
    {
    public:
        /** Perform any logic for the entity.  This could be advanced AI, in the
            case of an AI character, or it could be simple routines, such as
            constant rotating.  If a tile does nothing at all, this isn't going
            to be very exciting.
        */
        virtual void    DoLogic( unsigned long elapsedTime ) = 0;

        /** Render the entity to the display
            @param  surface     Surface onto which the entity will be rendered
        */
        virtual void    Render( SDL_Surface* surface ) = 0;

        /** Load the entity from an XML file
            @param  xmlData     XML data stream containing the entity information
            @return true if loaded successfully, false otherwise.
        */
        virtual bool    Load( TiXmlElement* xmlData ) = 0;

        /** Get the XML data for saving this entity
            @return TiXmlElement pointer to the data for this entity.
        */
        virtual TiXmlElement* GetSaveData() const = 0;

    }; // class BaseEntityInterface

} // namespace PGE

#endif // PGEBASEENTITYINTERFACE_H_INCLUDED
