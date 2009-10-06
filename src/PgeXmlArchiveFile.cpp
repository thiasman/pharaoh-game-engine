
/*! $Id$
 *  @file   PgeXmlArchiveFile.h
 *  @author Chad M. Draper
 *  @date   November 16, 2008
 *
 */

#include "PgeArchiveFile.h"
#include "PgeXmlArchiveFile.h"

namespace PGE
{
    //Constructor
    XmlArchiveFile::XmlArchiveFile()
        : TiXmlDocument()
    {
    }

    //Constructor
    XmlArchiveFile::XmlArchiveFile( ArchiveFile* file )
        : TiXmlDocument(), mFile( file )
    {
    }

    //Destructor
    XmlArchiveFile::~XmlArchiveFile()
    {
        //dtor
    }

    //LoadFile
    bool XmlArchiveFile::LoadFile( TiXmlEncoding encoding )
    {
        if ( !mFile.IsNull() && LoadFile( mFile.Get(), encoding ) )
            return true;

        return false;
    }

    //LoadFile
    bool XmlArchiveFile::LoadFile( ArchiveFile* file, TiXmlEncoding encoding )
    {
        if ( !file )
        {
            SetError( TIXML_ERROR_OPENING_FILE, 0, 0, TIXML_ENCODING_UNKNOWN );
            return false;
        }

        // Delete the existing data:
        Clear();
        location.Clear();

        // Get the file size, so we can pre-allocate the string. HUGE speed impact.
        long length = 0;
        length = file->Length();
        file->Seek( 0, ArchiveFile::Begin );

        // Strange case, but good to handle up front.
        if ( length == 0 )
        {
            SetError( TIXML_ERROR_DOCUMENT_EMPTY, 0, 0, TIXML_ENCODING_UNKNOWN );
            return false;
        }

        // If we have a file, assume it is all one big XML file, and read it in.
        // The document parser may decide the document ends sooner than the entire file, however.
        TIXML_STRING data;
        data.reserve( length );

        // Subtle bug here. TinyXml did use fgets. But from the XML spec:
        // 2.11 End-of-Line Handling
        // <snip>
        // <quote>
        // ...the XML processor MUST behave as if it normalized all line breaks in external
        // parsed entities (including the document entity) on input, before parsing, by translating
        // both the two-character sequence #xD #xA and any #xD that is not followed by #xA to
        // a single #xA character.
        // </quote>
        //
        // It is not clear fgets does that, and certainly isn't clear it works cross platform.
        // Generally, you expect fgets to translate from the convention of the OS to the c/unix
        // convention, and not work generally.

        /*
        while( fgets( buf, sizeof(buf), file ) )
        {
            data += buf;
        }
        */

        char* buf = new char[ length+1 ];
        buf[0] = 0;

        if ( file->Read( buf, length ) != length )
        {
            SetError( TIXML_ERROR_OPENING_FILE, 0, 0, TIXML_ENCODING_UNKNOWN );
            return false;
        }

        const char* lastPos = buf;
        const char* p = buf;

        buf[length] = 0;
        while( *p ) {
            assert( p < (buf+length) );
            if ( *p == 0xa ) {
                // Newline character. No special rules for this. Append all the characters
                // since the last string, and include the newline.
                data.append( lastPos, (p-lastPos+1) );	// append, include the newline
                ++p;									// move past the newline
                lastPos = p;							// and point to the new buffer (may be 0)
                assert( p <= (buf+length) );
            }
            else if ( *p == 0xd ) {
                // Carriage return. Append what we have so far, then
                // handle moving forward in the buffer.
                if ( (p-lastPos) > 0 ) {
                    data.append( lastPos, p-lastPos );	// do not add the CR
                }
                data += (char)0xa;						// a proper newline

                if ( *(p+1) == 0xa ) {
                    // Carriage return - new line sequence
                    p += 2;
                    lastPos = p;
                    assert( p <= (buf+length) );
                }
                else {
                    // it was followed by something else...that is presumably characters again.
                    ++p;
                    lastPos = p;
                    assert( p <= (buf+length) );
                }
            }
            else {
                ++p;
            }
        }
        // Handle any left over characters.
        if ( p-lastPos ) {
            data.append( lastPos, p-lastPos );
        }
        delete [] buf;
        buf = 0;

        Parse( data.c_str(), 0, encoding );

        if (  Error() )
            return false;
        else
            return true;
    }

    //GetItemValue
    String XmlArchiveFile::GetItemValue( TiXmlNode* node )
    {
        String value = "";
        if ( node )
        {
            TiXmlNode* valNode = node->FirstChild();
            if ( valNode && valNode->Type() == TiXmlNode::TEXT )
                value = valNode->Value();
        }
        return value;
    }

}
