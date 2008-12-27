
/*! $Id$
 *  @file   PgeFontManager.h
 *  @author Chad M. Draper
 *  @date   December 5, 2008
 *
 */

#include "PgeFontManager.h"
#include "PgeArchiveFile.h"
#include "PgeArchiveManager.h"
#include "PgeXmlArchiveFile.h"
#include "PgeTextureManager.h"
//#include "PgeStringUtil.h"

#if PGE_PLATFORM == PGE_PLATFORM_WIN32
#   include <windows.h>
#endif

#include <gl/gl.h>

#include "cmd/StringUtil.h"
using cmd::StringUtil;

namespace PGE
{
    //Constructor
    FontManager::FontManager()
//        : TileManager()
    {
    }

    // Instantiate the singleton instance
    //template<> FontManager* Singleton< FontManager >::mInstance = 0;
    FontManager* FontManager::mInstance = 0;

    //GetSingleton
    FontManager& FontManager::GetSingleton()
    {
        assert( mInstance );
        return *( static_cast< FontManager* >( mInstance ) );
    }

    //GetSingletonPtr
    FontManager* FontManager::GetSingletonPtr()
    {
        return static_cast< FontManager* >( mInstance );
    }

    //LoadFont
    bool FontManager::LoadFont( const String& fontDataFile )
    {
        // Get the archive file:
        String baseDir, fileTitle;
//        StringUtil::SplitFilename( fontDataFile, baseDir, fileTitle );
        StringUtil::SplitFilename( fontDataFile, &baseDir, &fileTitle );
        XmlArchiveFile doc( ArchiveManager::GetSingleton().CreateArchiveFile( fontDataFile ) );
        if ( doc.LoadFile() )
        {
            TiXmlNode* fontNode = doc.FirstChild( "font" );
            if ( fontNode )
            {
                // Get the font name
                String fontName = XmlArchiveFile::GetItemValue( fontNode->FirstChild( "name" ) );

                // Arrays used to store the positions and widths of the characters
                std::vector< Point2D > glyphPositions;
                std::vector< Point2D > glyphSizes;

                // Get the data file
                String dataFile = "", dataFileType = "bfb";
                TiXmlNode* dataNode = fontNode->FirstChild( "dataFile" );
                if ( dataNode && dataNode->Type() == TiXmlNode::ELEMENT )
                {
                    TiXmlElement* element = dataNode->ToElement();

                    // Get the type of data file:
                    dataFileType = element->Attribute( "type" );
//                    StringUtil::ToLower( dataFileType );
                    StringUtil::toLower( dataFileType );

                    // Get the name of the data file:
                    dataFile = baseDir + "/" + XmlArchiveFile::GetItemValue( dataNode );
                }

                // Get the image file name
                String imageFile = baseDir + "/" + XmlArchiveFile::GetItemValue( fontNode->FirstChild( "imageFile" ) );

                // Read the data file:
                if ( dataFileType == "cbfgbinfile" && ArchiveManager::GetSingleton().Exists( dataFile ) )
                {
                    // Open the file for reading:
                    ArchiveFile* file = ArchiveManager::GetSingleton().CreateArchiveFile( dataFile );
                    if ( file )
                    {
                        Int mapWidth, mapHeight, cellWidth, cellHeight, startOffset;
                        file->Read( &mapWidth, 4 );
                        file->Read( &mapHeight, 4 );
                        file->Read( &cellWidth, 4 );
                        file->Read( &cellHeight, 4 );
                        file->Read( &startOffset, 1 );
                        Int filePos = file->Tell();
                        Int hCells = mapWidth / cellWidth;
                        Int vCells = mapHeight / cellHeight;
                        Int numCells = hCells * vCells;

                        glyphPositions.resize( numCells );
                        glyphSizes.resize( numCells );

                        for ( Int curChar = 0; curChar < numCells; curChar++ )
                        {
                            glyphPositions[ curChar ] = Point2D( curChar % hCells * cellWidth, curChar / hCells * cellHeight );

                            UInt8 charWidth;
                            file->Read( &charWidth, 1 );
                            glyphSizes[ curChar ] = Point2D( cellHeight, charWidth );
                        }

                        delete file;
                    }
                }
                else if ( dataFileType == "cbfgbfffile" && ArchiveManager::GetSingleton().Exists( dataFile ) )
                {
                    // Codehead's Bitmap Font Generator has a native file format
                    // which stores the image data along with the layout data.
                    // Currently, the image data is not read from this file, but
                    // we can use the layout information along with an exported
                    // image file.

                    // Open the file for reading:
                    ArchiveFile* file = ArchiveManager::GetSingleton().CreateArchiveFile( dataFile );
                    if ( file )
                    {
                        Int mapWidth, mapHeight, cellWidth, cellHeight, startOffset;
                        file->Seek( 2, ArchiveFile::Begin );
                        file->Read( &mapWidth, 4 );
                        file->Read( &mapHeight, 4 );
                        file->Read( &cellWidth, 4 );
                        file->Read( &cellHeight, 4 );
                        file->Seek( 20, ArchiveFile::Begin );
                        file->Read( &startOffset, 1 );
                        Int hCells = mapWidth / cellWidth;
                        Int vCells = mapHeight / cellHeight;
                        Int numCells = hCells * vCells;

                        glyphPositions.resize( numCells );
                        glyphSizes.resize( numCells );

                        for ( Int curChar = 0; curChar < numCells; curChar++ )
                        {
                            glyphPositions[ curChar ] = Point2D( curChar % hCells * cellWidth, curChar / hCells * cellHeight );

                            Int charWidth;
                            file->Read( &charWidth, 1 );
                            glyphSizes[ curChar ] = Point2D( cellHeight, charWidth );
                        }

                        delete file;
                    }
                }
                else
                {
                    // Assuming 16x16 grid of character glyphs
                    TextureManager::GetSingleton().LoadImage( imageFile, GL_NEAREST, GL_NEAREST, false, true );
                    TextureItem* textureItem = TextureManager::GetSingleton().GetTextureItemPtr( imageFile );
                    if ( !textureItem )
                        return 0;

                    Point2D glyphSize( textureItem->GetOriginalWidth() / 16, textureItem->GetOriginalHeight() / 16 );
//                    return GenerateTiles( imageFile, fontName, glyphSize, Point2D( 16, 16 ), 256 );
return true;
                }
            }
        }

        return false;
    }

    //PrintString
    bool FontManager::PrintString( const String& fontName, const Real& posX, const Real& posY, const String& msg )
    {
        return true;
    }

    ////////////////////////////////////////////////////////////////////////////
    // class Font
    ////////////////////////////////////////////////////////////////////////////

/*
    //Font
    Font::Font()
    {
    }
    //Font
    Font::Font( const String& fontDataFile )
    {
    }
    //~Font
    Font::~Font()
    {
    }

    //GenerateFont
    void Font::GenerateFont( const String& fontDataFile )
    {
        // Get a pointer to the archive file so we can start reading
        XmlArchiveFile doc( ArchiveManager::GetSingleton().CreateArchiveFile( fontDataFile ) );
        if ( doc.LoadFile() )
        {
            TiXmlNode* fontNode = doc.FirstChild( "font" );

            // There can only be one data file describing the image layout.  In
            // the event that there are more than one in the file, then only one
            // is used...
            TiXmlNode* node = fontNode->FirstChild( "dataFile" );
            if ( node && node->Type() == TiXmlNode::ELEMENT )
            {
                TiXmlElement* element = node->ToElement();

                // Get the type of data file:
                String dataFileType = element->Attribute( "type" );
                StringUtil::toLower( dataFileType );

                // Get the name of the data file:
                String dataFileName = XmlArchiveFile::GetItemValue( node );

                // Read the data file:
                bool validDataFile = false;
                if ( ArchiveManager::Exists( dataFileName ) )
                {
                    if ( dataFileType == "cbfgbinfile" )
                    {
                        validDataFile = true;
                    }
                    else if ( dataFileType == "cbfgbfffile" )
                    {
                        validDataFile = true;
                    }
                }
                if ( !validDataFile )
                {
                    // Assuming 16x16 grid of character glyphs
                }
            }
            while ( node )
            {
                ReadProject( node );
                node = node->NextSibling( "project" );
            }
        }
    }

    //RenderString
    void Font::RenderString( Int posX, Int posY, const String& msg ) const
    {
    }


    ////////////////////////////////////////////////////////////////////////////
    // class FontManager
    ////////////////////////////////////////////////////////////////////////////

    //FontManager
    FontManager::FontManager()
    {
        //ctor
    }

    //~FontManager
    FontManager::~FontManager()
    {
        RemoveAllFonts();
    }

    //AddFont
    void FontManager::AddFont( Font* newFont )
    {
        // Make sure the font does not already exist:
        FontMap::iterator iter = mFontMap.find( newFont->mFontName );
        if ( iter != mFontMap.end() )
        {
            mFontMap[ newFont->mFontName ] = FontPtr( newFont );
        }
    }

    //AddFont
    void FontManager::AddFont( const String& fontDataFile )
    {
        // Make sure the font does not already exist:
        FontPtr newFont = FontPtr( new Font( fontDataFile ) );
        FontMap::iterator iter = mFontMap.find( newFont->mFontName );
        if ( iter != mFontMap.end() )
        {
            mFontMap[ newFont->mFontName ] = newFont;
        }
    }

    //GetFont
    Font* FontManager::GetFont( const String& fontName )
    {
        // Attempt to locate the font
        FontMap::iterator iter = mFontMap.find( fontName );
        if ( iter == mFontMap.end() )
            return 0;
        return iter->second.Get();
    }

    //RemoveFont
    void FontManager::RemoveFont( const String& fontName )
    {
        // Attempt to locate the font
        FontMap::iterator iter = mFontMap.find( fontName );
        if ( iter != mFontMap.end() )
        {
            mFontMap.erase( iter );
        }
    }

    //RemoveAllFonts
    void FontManager::RemoveAllFonts()
    {
        mFontMap.clear();
    }

    //RenderString
    void FontManager::RenderString( const String& fontName, Int posX, Int posY, const String& msg ) const
    {
        // Attempt to locate the font
        FontMap::iterator iter = mFontMap.find( fontName );
        if ( iter != mFontMap.end() )
        {
            iter->second->RenderString( posX, posY, msg );
        }
    }
*/

} // namespace PGE
