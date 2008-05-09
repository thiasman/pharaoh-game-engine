
/*! $Id$
 *  @file   PgeTextureManager.h
 *  @author Chad M. Draper
 *  @date   May 8, 2007
 *  @brief  Maintains a map of loaded image files.  This allows images to only
 *          need to be loaded once.
 *
 */

#ifndef PGETEXTUREMANAGER_H
#define PGETEXTUREMANAGER_H

#include <map>
#include "PgeTypes.h"
#include "PgeSingleton.h"
#include "PgeSharedPtr.h"

namespace PGE
{
    /** @class TextureItem
        The TextureItem class contains the actual image data (size, bpp, pixel
        information, etc.)  The class will take care of loading and unloading
        the image.
    */
    class TextureItem
    {
    private:
        bool    mIsLoaded;              /**< Indicates if the image exists in memory */
        String  mImageFileName;         /**< Name of the image file */

    public:
        /** Constructor */
        TextureItem( const String& imageFileName );

        /** Get the name of the image */
        const String& GetImageName() const        { return mImageFileName; }

        /** Get the load state */
        bool IsLoaded() const               { return mIsLoaded; }

        /** Load the image into memory.  If the image is already loaded, it does
            nothing.
        */
        bool Load();

        /** Unload the image from memory */
        bool Unload();

    }; // class TextureItem

    /** @class TextureManager
        A singleton class which maintains the image files.  By using this class,
        images are only loaded if needed, and are loaded just once.  When an
        image file is unloaded, it is closed, and the data is released, but its
        reference still exists in the manager.  If it is later requested, it
        will be automatically reloaded until it is again released.  Care should
        be taken so that images are not constantly loaded and unloaded, but at
        the same time, they shouldn't unnecessarily occupy memory.
    */
    class TextureManager : public Singleton< TextureManager >
    {
    public:
        typedef SharedPtr< TextureItem >            TextureItemPtr;
        //typedef std::pair< String, TextureItemPtr > Texture;

    private:
        typedef std::map< String, TextureItemPtr >  TextureMap;
        TextureMap                                  mTextureMap;
        typedef TextureMap::iterator                TextureIter;
        typedef TextureMap::const_iterator          TextureIterConst;

    public:
        /** Constructor */
        TextureManager();

        /** Destructor */
        virtual ~TextureManager();

        /** Override singleton retrieval to avoid link errors */
        static TextureManager& GetSingleton();
        /** Override singleton pointer retrieval to avoid link errors */
        static TextureManager* GetSingletonPtr();

        /** Add an image to the manager.  Optionally, load it into memory. */
        bool AddImage( const String& imageFileName );

        /** Load an image.  If the image is not already in the manager, it is
            first added.  If the image exists and is already loaded, it is not
            loaded again.
        */
        bool LoadImage( const String& imageFileName );

        /** Get a pointer to the texture item */
        TextureItem* GetTextureItemPtr( const String& textureName );
    };

} // namespace PGE;

#endif // PGETEXTUREMANAGER_H
