
/*! $Id$
 *  @file   PgeTextureManager.h
 *  @author Chad M. Draper
 *  @date   May 8, 2008
 *
 */

#include "PgeTextureManager.h"
#include "PgeMath.h"

#include <gl/gl.h>
#include <gl/glu.h>
#include <il/il.h>
#include <il/ilu.h>

namespace PGE
{
    ////////////////////////////////////////////////////////////////////////////
    // TextureItem
    ////////////////////////////////////////////////////////////////////////////

    TextureItem::TextureItem( const String& imageFileName )
        : mIsLoaded( false ),
          mImageFileName( imageFileName ),
          mWidth( 0 ), mHeight( 0 ),
          mTextureID( 0 )
    {
    }

    //Load----------------------------------------------------------------------
    bool TextureItem::Load( GLuint minFilter, GLuint maxFilter, bool forceMipmap )
    {
        ILuint imageID;
        ilGenImages( 1, &imageID );
        ilBindImage( imageID );
        if ( ilLoadImage( const_cast< char* >( mImageFileName.c_str() ) ) )
        {
            // Generate the GL texture
            glGenTextures( 1, &mTextureID );
            glBindTexture( GL_TEXTURE_2D, mTextureID );
            mWidth  = ilGetInteger( IL_IMAGE_WIDTH );
            mHeight = ilGetInteger( IL_IMAGE_HEIGHT );

            // If forcing mipmap generation, or if the size is not a power of 2,
            // generate as mipmaps
            if ( forceMipmap || !Math::IsPowerOf2( mWidth ) || !Math::IsPowerOf2( mHeight ) )
            {
                gluBuild2DMipmaps( GL_TEXTURE_2D,
                                ilGetInteger( IL_IMAGE_BPP ),
                                mWidth,
                                mHeight,
                                ilGetInteger( IL_IMAGE_FORMAT ),
                                GL_UNSIGNED_BYTE,
                                ilGetData() );
            }
            else
            {
                glTexImage2D(   GL_TEXTURE_2D,
                                0,
                                ilGetInteger( IL_IMAGE_BPP ),
                                mWidth,
                                mHeight,
                                0,
                                ilGetInteger( IL_IMAGE_FORMAT ),
                                GL_UNSIGNED_BYTE,
                                ilGetData() );
            }

            // Set the minification and magnification filters
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter );

            mIsLoaded = true;
        }

        //ilDeleteImages( 1, &imageID );

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
        // Initialize the image loading library
        // NOTE: The version checking seems to be broken with DevIL 1.6.8.  The
        // value returned as current is 166, and IL_VERSION is 168.  I'm just
        // guessing that something didn't get compiled correctly...
        //assert( !( ilGetInteger( IL_VERSION_NUM ) < IL_VERSION ) );
        ilInit();
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
    bool TextureManager::LoadImage( const String& imageFileName, GLuint minFilter, GLuint maxFilter, bool forceMipmap )
    {
        // Make sure the image is in the map:
        AddImage( imageFileName );

        // Load the image:
        TextureIter iter = mTextureMap.find( imageFileName );
        if ( iter != mTextureMap.end() )
            return iter->second->Load( minFilter, maxFilter, forceMipmap );
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
