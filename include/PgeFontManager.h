
/*! $Id$
 *  @file   PgeFontManager.h
 *  @author Chad M. Draper
 *  @date   December 5, 2008
 *  @brief  Stores font definitions for the engine.
 *
 */

#ifndef PGEFONTMANAGER_H
#define PGEFONTMANAGER_H

#include "PgeTypes.h"
#include "PgeSharedPtr.h"
//#include "PgeTileMap.h"
#include "PgeSingleton.h"

//#include <map>

namespace PGE
{
    /** @class Font
        Stores information for a specific bitmap font.

        @remarks
            It is not possible to change attributes such as bold, italic, or
            underline after a font is created.  Since the font is rendered as a
            tile map, it could be scaled, but it is still ideal to create the
            font as close to the desired size as possible.

        @remarks
            It is recommeded that the font's descriptive name include all
            attributes defining the font, though this is not required.  It just
            makes it more meaningful to users.  For example:

                <pre>
                    Arial 12pt bold underline italic
                </pre>
    */
    class _PgeExport Font
    {
    public:
        String      mDescription;
        //typedef SharedPtr< TileMap > TileMapPtr;
        //TileMapPtr  mTileMap;

        /** Constructor */
        Font();

        /** Load the font from a data file */

        /** Print a string using the font */
    };

    /** @class FontManager
        Bitmap fonts are handled similarly to tile maps, but require some extra
        handling to print strings.  The FontManager class is sublclassed from
        TileManager, and has additional functionality, primarily a PrintString
        method.

        @remarks
            The input data file should be a simple xml file containing any of
            the folloring tags

            <UL>
                <LI>name            - Name of the font. required.</LI>
                <LI>dataFile        - Name of the data file, which descibes the
                                      layout of the font in the texture.  This
                                      may have a "type" attribute with one of
                                      the following values:
                    <UL>
                        <LI>cbfgBinFile (Binary Font Data File exported from Codeheads' Bitmap Font Generator)</LI>
                        <LI>cbfgBffFile (Proprietary file format used by CBFG.  Only the font data is read, and the texture must be a separate image file.)</LI>
                    </UL>
                    If no type or data file is given, then it is assumed that the image
                    contains all 256 ASCII characters, which is used by LMNOpc.com's
                    Bitmap Font Builder.
                <LI>imageFile       - Name of the image file containing the font glyphs.</LI>
            </UL>

            so a sample font definition file would look something like:
            <CODE>
            <?xml version="1.0" encoding="ISO-8859-1" ?>
            <font>
                <name>Arial</name>
                <dataFile type="cbfgBinFile">Arial.dat</cbfgBinFile>
                <imageFile>Arial.tga</dataFile>
            </font>
            </CODE>

        @remarks
            If no data file is listed to describe the font, but an image is
            given, then the image is assumed to have all 256 ASCII characters,
            in a 16x16 grid.  This is equivalent to the LMNOpc.com's format.
    */
    class _PgeExport FontManager : public Singleton< FontManager >
    {
    public:
        /** Constructor */
        FontManager();

        /** Override singleton retrieval to avoid link errors */
        static FontManager& GetSingleton();
        /** Override singleton pointer retrieval to avoid link errors */
        static FontManager* GetSingletonPtr();

        /** Load a font into the manager */
        bool LoadFont( const String& fontDataFile );

        /** Print a string to the current display using a specified font.  If
            the font is not available, it will fail and return false.
        */
        bool PrintString( const String& fontName, const Real& posX, const Real& posY, const String& msg );
    };

//    /** The font class is what actually holds the data for each font.  It is
//        responsible for loading the font, and for rendering strings using the
//        font.
//
//        @remarks
//            The input data file should be a simple xml file containing any of
//            the folloring tags
//
//            <UL>
//                <LI>name            - Name of the font. required.</LI>
//                <LI>dataFile        - Name of the data file, which descibes the
//                                      layout of the font in the texture.  This
//                                      may have a "type" attribute with one of
//                                      the following values:
//                    <UL>
//                        <LI>cbfgBinFile (Binary Font Data File exported from Codeheads' Bitmap Font Generator)</LI>
//                        <LI>cbfgBffFile (Proprietary file format used by CBFG.  Only the font data is read, and the texture must be a separate image file.)</LI>
//                    </UL>
//                    If no type is given, then it is assumed that the image
//                    contains all 256 ASCII characters, which is used by LMNOpc.com's
//                    Bitmap Font Builder.
//                <LI>imageFile       - Name of the image file containing the font glyphs.</LI>
//            </UL>
//
//            so a sample font definition file would look something like:
//            <CODE>
//            <?xml version="1.0" encoding="ISO-8859-1" ?>
//            <font>
//                <name>Arial</name>
//                <dataFile type="cbfgBinFile">Arial.dat</cbfgBinFile>
//                <imageFile>Arial.tga</dataFile>
//            </font>
//            </CODE>
//
//        @remarks
//            If no data file is listed to describe the font, but an image is
//            given, then the image is assumed to have all 256 ASCII characters,
//            in a 16x16 grid.  This is equivalent to the LMNOpc.com's format.
//    */
//    class Font
//    {
//    private:
//        friend class FontManager;
//        String  mFontName;          ///< Identifier for the font
//
//    public:
//        /** Constructor */
//        Font();
//        /** Constructor */
//        Font( const String& fontDataFile );
//        /** Destructor */
//        ~Font();
//
//        /** Open a data file and load the font information */
//        void GenerateFont( const String& fontDataFile );
//
//        /** Render a string to the display using the font */
//        void RenderString( Int posX, Int posY, const String& msg ) const;
//
//    }; // class Font
//
//    /** @class FontManager
//        A collection of fonts.
//
//        The font manager stores and maintains all loaded fonts.
//
//        @remarks
//            There is no limitation on the number of font managers.  Typically,
//            the font manager will exist in a game state, and be destroyed when
//            the state ends.
//    */
//    class FontManager
//    {
//    private:
//        typedef SharedPtr< Font > FontPtr;
//        typedef std::map< String, FontPtr > FontMap
//        FontMap mFontMap;       ///< Map containing loaded fonts
//
//    public:
//        /** Constructor */
//        FontManager();
//        /** Destructor */
//        virtual ~FontManager();
//
//        /** Add a font to the manager */
//        void AddFont( Font* newFont );
//
//        /** Load a font and add it to the manager */
//        void AddFont( const String& fontDataFile );
//
//        /** Return a raw pointer to a named font, or null if the font does not exist */
//        Font* GetFont( const String& fontName );
//
//        /** Remove a font from the manager */
//        void RemoveFont( const String& fontName );
//
//        /** Remove all fonts */
//        void RemoveAllFonts();
//
//        /** Render a string with a named font */
//        void RenderString( const String& fontName, Int posX, Int posY, const String& msg ) const;
//
//    }; // class FontManager

} // namespace PGE

#endif // PGEFONTMANAGER_H
