
/*! $Id$
 *  @file   FileParseStringUtil.cpp
 *  @author Chad M. Draper
 *  @date   August 15, 2008
 *
 */

#include "PgeStringUtil.h"
#include <algorithm>
#include <sstream>
#include <tchar.h>
#include <direct.h>

namespace PGE
{
    //const String StringUtil::WHITE_SPACE = _T( " \t\n\r" );
    //const String StringUtil::BLANK       = _T( "" );

    //Trim--------------------------------------------------------------------------
    void StringUtil::Trim( String& str, bool removeLeft, bool removeRight )
    {
        // Method (for trim start.  end is similar)
        // 1.) find the location of the first character that is not whitespace.
        // 2.) erase all characters up to that index.
        /*
        if ( removeLeft )
            str.erase( 0, str.find_first_not_of( StringUtil::WHITE_SPACE ) );
        if ( removeRight )
            str.erase( str.find_last_not_of( StringUtil::WHITE_SPACE ) + 1 );
        */
    }

    //Split---------------------------------------------------------------------
    UInt32 StringUtil::Split( const String& src, const String& delim, StringUtil::StringVector& results, UInt32 maxSplits, bool addBlank )
    {
        // Make sure the source and delimiter are specified
        if ( src.size() == 0 || delim.size() == 0 )
        {
            return 0;
        }

        UInt32 delimFound = 0, curPos, startPos = 0;
        //String curString = StringUtil::BLANK;
        String curString = "";
        do
        {
            // Find the first delimiter
            curPos = src.find_first_of( delim, startPos );
            if ( curPos == startPos )
            {
                // There is a delimiter at the start of the string.  Increment
                // the delimiter count, and if adding empty strings, add one.
                delimFound++;
                if ( addBlank )
                {
                    results.push_back( curString );
                }

                startPos = curPos + 1;
            }

            // Check for the last match
            else if ( curPos == String::npos )
            {
                // Add the remainder of the source to the results, checking
                // for an empty string.
                curString = src.substr( startPos );
                if ( curString.length() || addBlank )
                    results.push_back( curString );
                break;
            }

            // Store the current substring
            else
            {
                delimFound++;
                results.push_back( src.substr( startPos, curPos - startPos ) );

                // Set the start position just past the delimiter
                startPos = curPos + 1;
            }
        } while ( curPos != String::npos );

        return delimFound;
    }

    //ToUpper-------------------------------------------------------------------
    void StringUtil::ToUpper( String& str )
    {
        // Iterate over the string, converting each character's case:
        std::transform( str.begin(), str.end(), str.begin(), toupper );
    }

    //ToLower-------------------------------------------------------------------
    void StringUtil::ToLower( String& str )
    {
        // Iterate over the string, converting each character's case:
        std::transform( str.begin(), str.end(), str.begin(), tolower );
    }

    //ToReal--------------------------------------------------------------------
    Real StringUtil::ToReal( const String& str )
    {
        Real val;
        std::istringstream( str ) >> val;
        return val;
    }

    //ToInt---------------------------------------------------------------------
    Int StringUtil::ToInt( const String& str )
    {
        Int val;
        std::istringstream( str ) >> val;
        return val;
    }

    //IsNumber------------------------------------------------------------------
    bool StringUtil::IsNumber( const String& str )
    {
        Real val;
        String leftover;
        std::istringstream iss( str );
        if ( ( iss >> val ).fail() )
            return false;
        if ( ( iss >> leftover ).fail() )
            return true;
        return false;
    }

    //StartsWith----------------------------------------------------------------
    bool StringUtil::StartsWith( const String& str, const String& pattern, bool lowerCase )
    {
        // First examine the length of the string and the pattern.  The
        // string should be at least the length of the pattern.
        UInt32 strLen = str.length();
        UInt32 patLen = pattern.length();
        if ( strLen < patLen || patLen == 0 )
            return false;

        // Examine the first part of the string to see if it matches the pattern:
        String strStart = str.substr( 0, patLen );
        if ( lowerCase )
            StringUtil::ToLower( strStart );

        return ( strStart == pattern );
    }

    //EndsWith------------------------------------------------------------------
    bool StringUtil::EndsWith( const String& str, const String& pattern, bool lowerCase )
    {
        // First examine the length of the string and the pattern.  The
        // string should be at least the length of the pattern.
        UInt32 strLen = str.length();
        UInt32 patLen = pattern.length();
        if ( strLen < patLen || patLen == 0 )
            return false;

        // Examine the first part of the string to see if it matches the pattern:
        String strEnd = str.substr( strLen - patLen, patLen );
        if ( lowerCase )
            StringUtil::ToLower( strEnd );

        return ( strEnd == pattern );
    }

    //FindReplace---------------------------------------------------------------
    String StringUtil::FindReplace( const String& str, const String& findStr, const String& newStr )
    {
        // As long as the substring exists, replace it in the string:
        int index = 0;
        String result = str;
        while ( ( index = result.find( findStr, index ) ) != String::npos )
        {
            result.replace( index, findStr.length(), newStr );

            // It might be the case that the replacement string contains the
            // original string as a substring.  Therefore, we need to begin the
            // next look after the new change.
            index += newStr.length();
        }

        return result;
    }

    //StandardizePath-----------------------------------------------------------
    String StringUtil::StandardizePath( const String& path, bool addTrailingSlash )
    {
        // Clean the path.  This will replace back slashes with forward slashes
        // and resolve an "." or ".." occurrances.
        String fixedPath = path;
        CleanPath( fixedPath, fixedPath );

        // Make sure the last character is a slash:
        if ( addTrailingSlash && ( fixedPath[ fixedPath.length() - 1 ] != _T('/') ) )
            fixedPath += _T('/');

        return fixedPath;
    }

    //SplitFilename-------------------------------------------------------------
    void StringUtil::SplitFilename( const String& str, String& outPath, String& outFilename )
    {
        // Fix the path, as in standardizePath, but don't add the trailing slash:
        String fixedPath = str;
        std::replace( fixedPath.begin(), fixedPath.end(), _T('\\'), _T('/') );

        // Find the last occurrance of the slash:
        UInt32 i = fixedPath.find_last_of( _T('/') );

        // If no occurrances were found, the path was empty, but the base name
        // is the given string:
        if ( i == String::npos )
        {
            outPath = _T("");
            outFilename = fixedPath;
        }
        else
        {
            outPath = fixedPath.substr( 0, i + 1 );
            outFilename = fixedPath.substr( i + 1, ( fixedPath.length() - i ) - 1 );
        }
    }

    //SplitFileExtension--------------------------------------------------------
    void StringUtil::SplitFileExtension( const String& str, String& outFilename, String& outExt )
    {
        // Fix the path, as in standardizePath, but don't add the trailing slash:
        String fixedPath = str;
        std::replace( fixedPath.begin(), fixedPath.end(), _T('\\'), _T('/') );

        // Find the last occurrance of the slash:
        UInt32 i = fixedPath.find_last_of( _T('.') );

        // If no occurrances were found, the path was empty, but the base name
        // is the given string:
        if ( i == String::npos )
        {
            outExt = _T("");
            outFilename = fixedPath;
        }
        else
        {
            outFilename = fixedPath.substr( 0, i );
            outExt = fixedPath.substr( i + 1, ( fixedPath.length() - i ) - 1 );
        }
    }

    //SplitNumberedFilename
    void StringUtil::SplitNumberedFilename( const String& full, String& base, int& number, String& ext )
    {
        // Separate the extension from the filename:
        SplitFileExtension( full, base, ext );

        // Start at the end of the filename, and move toward the front as long
        // as the character is a number:
        String numStr = "";
        String::reverse_iterator numIter = base.rbegin();
        while ( numIter != base.rend() && *numIter >= '0' && *numIter <= '9' )
        {
            numStr = *numIter + numStr;
            numIter++;
        }
        base.resize( base.size() - numStr.size() );
        number = ToInt( numStr );
    }

    //BuildPath-----------------------------------------------------------------
    void StringUtil::BuildPath( const String& basePath, const String& dir, String& outPath )
    {
        CleanPath( basePath + dir, outPath );
    }

    //CleanPath-----------------------------------------------------------------
    void StringUtil::CleanPath( const String& inPath, String& outPath )
    {
        // Replace all occurrances of '\\' with '/':
        String fixedPath = inPath;
        std::replace( fixedPath.begin(), fixedPath.end(), _T('\\'), _T('/') );

        // Make sure there are no double slashes:
        fixedPath = FindReplace( fixedPath, _T("//"), _T("/") );

        // Similarly, the '/./' pattern can be replaced with '/' since the
        // '.' just means the current directory.
        fixedPath = FindReplace( fixedPath, _T("/./"), _T("/") );

        // Now for some magic.  Any occurrances of the '/../' pattern require
        // the string be split, and the rightmost directory before the pattern
        // be removed.
        int index;
        while ( ( index = fixedPath.find( _T("/../") ) ) != String::npos )
        {
            String left = fixedPath.substr( 0, index );
            String right = fixedPath.substr( index );

            // The way the string was split, the left side does not end with a
            // slash, which means the path just has to be reverse searched for a
            // slash to remove the last directory.  Also, the right string starts
            // with the '/../' pattern, which needs to be replaced by '/'.
            int dirIndex = left.find_last_of( _T('/') );
            left = left.substr( 0, dirIndex );
            right.replace( 0, 4, _T("/") );
            fixedPath = left + right;
        }

        outPath = fixedPath;
    }

    //Match---------------------------------------------------------------------
    bool StringUtil::Match( const String& str, const String& pattern, bool caseSensitive )
    {
        // Make temporary copies of the string and pattern.  If case-sensitivity
        // is off, then make the temp strings lowercase.
        String tempStr = str;
        String tempPattern = pattern;
        if ( !caseSensitive )
        {
            ToLower( tempStr );
            ToLower( tempPattern );
        }

        // Iterators for the string and pattern:
        String::const_iterator patternIter  = tempPattern.begin();
        String::const_iterator strIter      = tempStr.begin();

        // Temporary pointers.  When a wildcard is found, store the
        // wildcard, and the next character of the source string.  Then
        // when a character match is not found, use the previous wildcard
        // and the next source character.
        String::const_iterator lastWildcard = tempPattern.end();
        String::const_iterator nextSource   = tempStr.end();

        // Compare initial characters until the search character is
        // a multi-character wildcard:
        while ( ( strIter != tempStr.end() ) && ( patternIter != tempPattern.end() ) && ( *patternIter != _T('*') ) )
        {
            // If the characters do not match and the current search
            // character is not a single character wildcard, the
            // strings do not match:
            if ( ( *strIter != *patternIter ) && ( *patternIter != _T('?') ) )
                return false;

            // Increment the pointers:
            ++patternIter;
            ++strIter;
        }

        // There has been a multi-character wildcard...
        while ( ( strIter != tempStr.end() ) && ( patternIter != tempPattern.end() ) )
        {
            if ( *patternIter == _T('*') )
            {
                // If the current wildcard is at the end of the pattern string,
                // then the strings definitely match:
                ++patternIter;
                if ( patternIter == tempPattern.end() )
                    return true;

                // Otherwise, store the pattern character right after the wildcard
                // and the next source character.  At this point, the source string
                // will be searched until this next pattern character is found.
                // If there is a point where the pattern and source do not match,
                // come back to these values:
                lastWildcard = patternIter;
                nextSource   = strIter;
            }

            // If the pattern and source strings match, simply advance the pointers:
            else if ( ( *patternIter == *strIter ) || ( *patternIter == _T('?') ) )
            {
                ++patternIter;
                ++strIter;
            }

            else
            {
                // The pattern and source characters do not match here.  Set the
                // pattern back to the character just after the previous wildcard,
                // and set the source character to the next one to compare:
                patternIter = lastWildcard;
                strIter     = nextSource;

                // Advance the source character.  The wildcard will apply to as
                // many source characters as necessary until either the source string
                // ends, or there is a positive match.  The character just after the
                // wildcard needs to match a character in the string.
                nextSource++;
            }
        }

        // Eat trailing '*'s in the pattern:
        while ( ( patternIter != tempPattern.end() ) && ( *patternIter == _T('*') ) )
            ++patternIter;

        // If the pattern is at the end, then the strings match:
        return ( patternIter == tempPattern.end() );
    }

    //AsciiToUnicode------------------------------------------------------------
    void StringUtil::AsciiToUnicode( const char* src, wchar_t* dest )
    {
        int length = strlen( src );
        //assert( length == wcslen( dest ) );
        if ( length == wcslen( dest ) )
            mbstowcs( dest, src, length );
    }
    //AsciiToUnicode------------------------------------------------------------
    std::wstring StringUtil::AsciiToUnicode( const std::string& src )
    {
        return std::wstring( src.begin(), src.end() );
    }

    //UnicodeToAscii------------------------------------------------------------
    void StringUtil::UnicodeToAscii( const wchar_t* src, char* dest )
    {
        int length = wcslen( src );
        //assert( length == strlen( dest ) );
        if ( length == strlen( dest ) )
            wcstombs( dest, src, length );
    }

    //UnicodeToAscii------------------------------------------------------------
    std::string StringUtil::UnicodeToAscii( const std::wstring& src )
    {
        int length = src.length();
        char* asciiStr = new char [ length + 1 ];
        wcstombs( asciiStr, src.c_str(), length );
        asciiStr[ length ] = '\0';
        std::string convStr( asciiStr );
        delete [] asciiStr;
        return convStr;
    }

    void StringUtil::CreatePath( const std::string& path )
    {
        std::string fixedPath = StandardizePath( path );

        // Split the path into each directory
        std::vector< std::string > dirs;
        Split( fixedPath, "/", dirs );

        // Go over the components, making sure each directory exists
        std::vector< std::string >::iterator iter;
        std::string curPath = "";
        for ( iter = dirs.begin(); iter != dirs.end(); iter++ )
        {
            const char* curDir = iter->c_str();
            if ( *( curDir + 1 ) != ':' )
            {
                curPath += curDir;
                std::string dirStr;
                dirStr += curPath;
                try
                {
                    //namespace fs = boost::filesystem;
                    //fs::path p( dirStr.c_str(), fs::native );
                    //fs::create_directory( p );
                    mkdir( dirStr.c_str() );
                }
                catch ( std::exception& e )
                {
                    std::string msg( "Error creating directory:" );
                    msg += e.what();
                }

                curPath += "/";
            }
            else
                curPath = std::string( curDir ) + "/";
        }
    }

} // namespace PGE
