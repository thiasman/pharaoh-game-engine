
/*! $Id$
 *  @file   PgeStringUtil.h
 *  @author Chad M. Draper
 *  @date   August 15, 2008
 *  @brief  Class for manipulating strings.
 *
 */

#ifndef PgeStringUtil_H_
#define PgeStringUtil_H_

#include "PgeTypes.h"
#include <vector>
#include <sstream>

namespace PGE
{
    /** @class StringUtil
        A collection of static methods for working with strings.
    */
    class _PgeExport StringUtil
    {
    public:
        //static const String WHITE_SPACE;    /** Defines the whitespace characters */
        //static const String BLANK;          /** Empty string */

        typedef std::vector< String > StringVector; /**< A vector of strings */

        /** Trim whitespace from either end of a string */
        static void Trim( String& str, bool removeLeft = true, bool removeRight = true );
        static void TrimLeft( String& str )     { Trim( str, true, false ); }
        static void TrimRight( String& str )    { Trim( str, false, true ); }

        /** Split the string into sub-strings using a user-defined delimiter.
            @param  src         String to be split
            @param  delim       User-defined delimiter
            @param  results     Vector of resultant substrings
            @param  maxSplits   Maximum number of splits (0 = ignore)
            @param  addBlank    Indicates if empty strings should be added to the array
            @return             Number of delimiters found (NOT the number of sub-strings.)
        */
        static UInt32 Split( const String& src, const String& delim, StringVector& results, UInt32 maxSplits = 0, bool addBlank = false );

        /** Convert a value to a string */
        template< typename T >
        static String ToString( const T& val )
        {
            std::stringstream stream;
            stream << val;
            return stream.str();
        }

        /** Convert a string to upper case */
        static void ToUpper( String& str );

        /** Convert a string to lower case */
        static void ToLower( String& str );

        /** Convert a string to a REAL.  If the string is not a valid REAL, 0.0
            is returned.
        */
        static Real ToReal( const String& str );

        /** Test if a string represents a number.  This is rigid, and if the
            entire string is not a number, will fail.
        */
        static bool IsNumber( const String& str );

        /** Convert a string to an INT.  If the string is not a valid INT, 0
            is returned.
        */
        static Int ToInt( const String& str );

        /** Test whether the string starts with a supplied substring.
            @param  str         String to search
            @param  pattern     Pattern to look for
            @param  lowerCase   If true, the string is converted to lower-case
                                before testing.  The pattern is assumed to
                                already be lower-case.
        */
        static bool StartsWith( const String& str, const String& pattern, bool lowerCase = false );

        /** Test whether the string ends with a supplied substring.
            @param  str         String to search
            @param  pattern     Pattern to look for
            @param  lowerCase   If true, the string is converted to lower-case
                                before testing.  The pattern is assumed to
                                already be lower-case.
        */
        static bool EndsWith( const String& str, const String& pattern, bool lowerCase = false );

        /** Search for a substring and replace it with a different string.
            @param  str         String to modify
            @param  findStr     String to search for
            @param  newStr      String to use for the replacement
        */
        static String FindReplace( const String& str, const String& findStr, const String& newStr );

        /** Method for creating standardized paths.  This replaces back-slash
            pairs ('\\') with forward slashes ('/').
        */
        static String StandardizePath( const String& path, bool addTrailingSlash = true );

        /** Method to split a full filename and return the path and base name. */
        static void SplitFilename( const String& str, String& outPath, String& outFilename );

        /** Method to split a filename into the extension, and everything else... */
        static void SplitFileExtension( const String& str, String& outFilename, String& outExt );

        /** Method that will split all elements of a file path (path, title,
            and extension) given its path + extension.  This is the same as
            calling splitFilename followed by splitFileExtension.
        */
        inline static void SplitFile( const String& str, String& outPath, String& outTitle, String& outExt )
        {
            String filename;
            SplitFilename( str, outPath, filename );
            SplitFileExtension( filename, outTitle, outExt );
        }

        /** Split a numbered filename (i.e. file0000.txt) into the basename (file),
            number (0), and extension (txt).
        */
        static void SplitNumberedFilename( const String& full, String& base, int& number, String& ext );

        /** Build a path string, allowing for directory modifiers ('.' and '..')
            @param  basePath    Initial path
            @param  dir         Directory to append to the path
            @param  outPath     Resultant path
            @remarks
                'dir' is first appended to 'basePath.'  The result is then searched
                for modifiers.  If any are found, the path is split at the modifier
                and the necessary directory changes are made.
        */
        static void BuildPath( const String& basePath, const String& dir, String& outPath );
        static void CleanPath( const String& inPath, String& outPath );

        /** Method to search a String for a user-defined pattern.  The
            pattern may use the '*' wildcard.
            @param  str         String to test
            @param  pattern     Pattern to look for
            @param  caseSensitive   Indicates if the search should be case sensitive
        */
        static bool Match( const String& str, const String& pattern, bool caseSensitive = true );

        /** Convert an ANSI string to UNICODE
            @remarks    Requires the destination string to be big enough to
                        hold the conversion
        */
        static void AsciiToUnicode( const char* src, wchar_t* dest );
        static std::wstring AsciiToUnicode( const std::string& src );

        /** Convert an UNICODE string to ANSI
            @remarks    Uses ATL to perform the conversion
        */
        static void UnicodeToAscii( const wchar_t* src, char* dest );
        static std::string UnicodeToAscii( const std::wstring& src );

        /** Create full path
            @remarks
                Starting at the given root, this will work its way up the path,
                creating any sub-directory that does not yet exist.

            @param  path        Path to be created
            @return true if the path was created, false otherwise
        */
        static void CreatePath( const std::string& path );

    };
} // namespace PGE

#endif  // PgeStringUtil_H_
