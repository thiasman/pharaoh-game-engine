
/*! $Id$
 *  @file   PgeTextureManager.h
 *  @author Chad M. Draper
 *  @date   May 8, 2008
 *
 */

#include "PgeTextureManager.h"
#include "PgeMath.h"
#include "PgeArchiveFile.h"
#include "PgeArchiveManager.h"

#include "PgeStringUtil.h"
//using cmd::StringUtil;

#if PGE_PLATFORM == PGE_PLATFORM_WIN32
#   include <windows.h>
#endif

#include <gl/gl.h>
#include <gl/glu.h>
#include <il/il.h>
#include <il/ilu.h>

/** @remarks
        In order to handle image loading, Pharaoh Game Engine depends on DevIL
        (<a href="http://openil.sourceforge.net">http://openil.sourceforge.net</a>).
        The thing to do for MinGW compilers is to download the Windows libraries,
        then reimp the *.lib files to generate *.a files.
*/

//#include <unzip.h>

//#include "PgeLogFileManager.h"

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
    bool TextureItem::Load( GLuint minFilter, GLuint maxFilter, bool forceMipmap, bool resizeIfNeeded )
    {
        /** NOTE: This is a test of using an archive file.  This will need to
            be modified to allow direct file access, or archived file access.
        */
        ArchiveFile* file = ArchiveManager::GetSingleton().CreateArchiveFile( mImageFileName );
        if ( file )
        {
            UInt32 fileSize = file->Length();
            unsigned char* buf = new unsigned char [ fileSize ];
            if ( !buf )
            {
                delete file;
                return false;
            }
            file->Read( buf, fileSize );

            // Load the texture:

            //****
            ilInit();
            iluInit();

            // Make sure the DevIL version is valid:
            if ( ilGetInteger( IL_VERSION_NUM ) < IL_VERSION || iluGetInteger( ILU_VERSION_NUM ) < ILU_VERSION )
            {
                // Invalid version...
                delete file;
                delete buf;
                return false;
            }


            // Get the decompressed data
            ILuint imageID;
            ilGenImages( 1, &imageID );
            ilBindImage( imageID );
            //if ( ilLoadImage( const_cast< char* >( mImageFileName.c_str() ) ) )
            if ( ilLoadL( IL_TYPE_UNKNOWN, buf, fileSize ) )
            {
                // Convert the image to unsigned bytes:
                ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );

                // Generate the GL texture
                glGenTextures( 1, &mTextureID );
                glBindTexture( GL_TEXTURE_2D, mTextureID );
                mWidth  = ilGetInteger( IL_IMAGE_WIDTH );
                mHeight = ilGetInteger( IL_IMAGE_HEIGHT );
                mOriginalWidth  = mWidth;
                mOriginalHeight = mHeight;

                // OpenGL will work better with textures that have dimensions
                // that are a power of 2.  If doing a scrolling tile map, then
                // this is pretty much a necessity.  However, there are times
                // when using a mipmap instead is perfectly fine (ie, when NOT
                // doing tiles, or in cases where we might be running out of
                // video memory...
                if ( resizeIfNeeded && !forceMipmap )
                {
                    UInt32 newWidth = mWidth, newHeight = mHeight;
                    if ( !Math::IsPowerOf2( mWidth ) )
                    {
                        // Find the next power of 2:
                        newWidth = Math::FindNextPowerOf2( mWidth );
                    }

                    if ( !Math::IsPowerOf2( mHeight ) )
                    {
                        // Find the next power of 2:
                        newHeight = Math::FindNextPowerOf2( mHeight );
                    }

                    if ( newWidth != mWidth || newHeight != mHeight )
                    {
                        // Resize the canvas:
                        ilClearColor( 0, 0, 0, 0 );
                        iluImageParameter( ILU_PLACEMENT, ILU_UPPER_LEFT );
                        iluEnlargeCanvas( newWidth, newHeight, ilGetInteger( IL_IMAGE_DEPTH ) );
                        mWidth  = ilGetInteger( IL_IMAGE_WIDTH );
                        mHeight = ilGetInteger( IL_IMAGE_HEIGHT );
                    }
                }

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
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

                mIsLoaded = true;
            }
            else
            {
                ILenum error;
                error = ilGetError();
                //std::string errString = iluErrorString( error );
            }

            ilDeleteImages( 1, &imageID );

            //***

            // Free memory:
            delete buf;
            delete file;
        }
        else
            return false;

        return true;
    }

    //Unload--------------------------------------------------------------------
    bool TextureItem::Unload()
    {
        glDeleteTextures( 1, &mTextureID );
        mTextureID = 0;
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
        String imageName = StringUtil::FixPath( imageFileName );
        TextureIter iter = mTextureMap.find( imageName );

        // Add the new item only if it is not found
        if ( iter == mTextureMap.end() )
            mTextureMap[ imageName ] = TextureItemPtr( new TextureItem( imageName ) );

        // Check if the item is in the map now:
        iter = mTextureMap.find( imageName );
        if ( iter != mTextureMap.end() )
            return true;
        return false;
    }

    //RemoveImage---------------------------------------------------------------
    bool TextureManager::RemoveImage( const String& imageFileName )
    {
        // Attempt to find the image in the map:
        TextureIter iter = mTextureMap.find( imageFileName );

        // Add the new item only if it is not found
        if ( iter != mTextureMap.end() )
        {
            // Unload the image
            if ( !iter->second->Unload() )
                return false;

            // Remove the image from the map
            mTextureMap.erase( iter );
        }

        return true;
    }

    //LoadImage-----------------------------------------------------------------
    bool TextureManager::LoadImage( const String& imageFileName, GLuint minFilter, GLuint maxFilter, bool forceMipmap, bool resizeIfNeeded )
    {
        // Make sure the image is in the map:
        AddImage( imageFileName );

        // Load the image:
        TextureIter iter = mTextureMap.find( imageFileName );
        if ( iter != mTextureMap.end() )
            return iter->second->Load( minFilter, maxFilter, forceMipmap, resizeIfNeeded );
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
