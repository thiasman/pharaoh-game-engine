
/*! $Id$
 *  @file   PgeTextureManager.h
 *  @author Chad M. Draper
 *  @date   May 8, 2007
 *
 */

#include "PgeTextureManager.h"

namespace PGE
{
    ////////////////////////////////////////////////////////////////////////////
    // TextureItem
    ////////////////////////////////////////////////////////////////////////////

    TextureItem::TextureItem( const String& imageFileName )
        : mIsLoaded( false ),
          mImageFileName( imageFileName )
    {
    }

    //Load----------------------------------------------------------------------
    bool TextureItem::Load()
    {
        mIsLoaded = true;

        return true;
    }

    //Unload--------------------------------------------------------------------
    bool TextureItem::Unload()
    {
        mIsLoaded = false;

        return false;
    }

    ////////////////////////////////////////////////////////////////////////////
    // TextureManager
    ////////////////////////////////////////////////////////////////////////////

    // Instantiate the singleton instance
    template<> TextureManager* Singleton< TextureManager >::mInstance = 0;
    TextureManager& TextureManager::GetSingleton()
    {
        assert( mInstance );
        return *mInstance;
    }
    TextureManager* TextureManager::GetSingletonPtr()
    {
        return mInstance;
    }

    TextureManager::TextureManager()
    {
    }

    TextureManager::~TextureManager()
    {
        mTextureMap.clear();
    }

    //AddImage------------------------------------------------------------------
    bool TextureManager::AddImage( const String& imageFileName )
    {
        // Attempt to find the image in the map:
        TextureIter iter = mTextureMap.find( imageFileName );

        // Add the new item only if it is not found
        if ( iter == mTextureMap.end() )
            mTextureMap[ imageFileName ] = TextureItemPtr( new TextureItem( imageFileName ) );

        // Check if the item is in the map now:
        iter = mTextureMap.find( imageFileName );
        if ( iter != mTextureMap.end() )
            return true;
        return false;
    }

    //LoadImage-----------------------------------------------------------------
    bool TextureManager::LoadImage( const String& imageFileName )
    {
        // Make sure the image is in the map:
        AddImage( imageFileName );

        // Load the image:
        TextureIter iter = mTextureMap.find( imageFileName );
        if ( iter != mTextureMap.end() )
            return iter->second->Load();
        return false;
    }

    //GetTextureItemPtr---------------------------------------------------------
    TextureItem* TextureManager::GetTextureItemPtr( const String& textureName )
    {
        // Find the texture in the map:
        TextureIter iter = mTextureMap.find( textureName );
        if ( iter != mTextureMap.end() )
            return iter->second.Get();

        // The texture wasn't found, so attempt to add and load the image:
        LoadImage( textureName );

        // Now see if the texture data can be returned:
        iter = mTextureMap.find( textureName );
        if ( iter != mTextureMap.end() )
            return iter->second.Get();
        return 0;
    }

} // namespace PGE
