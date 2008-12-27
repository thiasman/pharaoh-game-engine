
/*! $Id$
 *  @file   PgeXmlArchiveFile.h
 *  @author Chad M. Draper
 *  @date   November 16, 2008
 *  @brief  In order to read an xml document from an archive, we need to provide
 *          some special handling to the xml document class.
 *
 */

#ifndef PGEXMLARCHIVEFILE_H
#define PGEXMLARCHIVEFILE_H

#include "PgeSharedPtr.h"
#include "tinyxml.h"

namespace PGE
{
    class ArchiveFile;

    class _PgeExport XmlArchiveFile : public TiXmlDocument
    {
    protected:
        typedef SharedPtr< ArchiveFile > FilePtr;
        FilePtr     mFile;

    public:
        /** Constructor */
        XmlArchiveFile();
        /** Constructor */
        XmlArchiveFile( ArchiveFile* file );

        /** Destructor */
        virtual ~XmlArchiveFile();

        /** Load a file using the current document value.
            Returns true if successful. Will delete any existing
            document data before loading.
        */
        bool LoadFile( TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING );

        /** Load a file from a given archive file.  The entire file data is
            parsed, and true is returned if successful.
        */
        bool LoadFile( ArchiveFile* file, TiXmlEncoding encoding = TIXML_DEFAULT_ENCODING );

        /** Most of the attributes in the tile map file will be listed as
            <pre>
                <item>itemVal</item>
            </pre>

            This requires some extra steps in TinyXML to get the value (value in
            TinyXML is the name of node, and the attributes are listed within
            the node's brackets.  In order to read itemVal, we would get the
            first node of the <item> node, then take it's value, as it would be
            a text node.)

            This function allows us to get the item's value directly, without
            having to step the tree manually each time.
        */
        static String GetItemValue( TiXmlNode* node );

    };

} // namespace PGE

#endif // PGEXMLARCHIVEFILE_H
