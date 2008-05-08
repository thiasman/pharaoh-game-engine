
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
    void TextureItem::Load()
    {
        mIsLoaded = true;
    }

    //Unload--------------------------------------------------------------------
    void TextureItem::Unload()
    {
        mIsLoaded = false;
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
    void TextureManager::AddImage( const String& imageFileName )
    {
        // Attempt to find the image in the map:
        TextureIter iter = mTextureMap.find( imageFileName );

        // Add the new item only if it is not found
        if ( iter == mTextureMap.end() )
        {
            mTextureMap[ imageFileName ] = TextureItemPtr( new TextureItem( imageFileName ) );
        }
    }

    //LoadImage-----------------------------------------------------------------
    void TextureManager::LoadImage( const String& imageFileName )
    {
        // Make sure the image is in the map:
        AddImage( imageFileName );

        // Load the image:
        TextureIter iter = mTextureMap.find( imageFileName );
        if ( iter != mTextureMap.end() )
            iter->second->Load();
    }

    //GetTextureItemPtr---------------------------------------------------------
    TextureItem* TextureManager::GetTextureItemPtr() const
    {
    }

} // namespace PGE
