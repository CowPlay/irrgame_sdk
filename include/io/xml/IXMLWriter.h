// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_XML_WRITER_H_INCLUDED__
#define __I_XML_WRITER_H_INCLUDED__

#include "core/engine/IReferenceCounted.h"
#include "core/collections/array.h"

namespace irrgame
{
	namespace io
	{
		class IWriteFile;

		//! Interface providing methods for making it easier to write XML files.
		/** This XML Writer writes xml files using in the platform dependent
		 wchar_t format and sets the xml-encoding correspondingly. */
		class IXMLWriter: public virtual IReferenceCounted
		{
			public:

				//! Destructor
				virtual ~IXMLWriter()
				{
				}

				//! Writes an xml 1.0 header.
				/** Looks like &lt;?xml version="1.0"?&gt;. This should always
				 be called before writing anything other, because also the text
				 file header for unicode texts is written out with this method. */
				virtual void writeXMLHeader() = 0;

				//! Writes an xml element with maximal 5 attributes like "<foo />" or
				//! &lt;foo optAttr="value" /&gt;.
				/** The element can be empty or not.
				 \param name: Name of the element
				 \param empty: Specifies if the element should be empty. Like
				 "<foo />". If You set this to false, something like this is
				 written instead: "<foo>".
				 \param attr1Name: 1st attributes name
				 \param attr1Value: 1st attributes value
				 \param attr2Name: 2nd attributes name
				 \param attr2Value: 2nd attributes value
				 \param attr3Name: 3rd attributes name
				 \param attr3Value: 3rd attributes value
				 \param attr4Name: 4th attributes name
				 \param attr4Value: 4th attributes value
				 \param attr5Name: 5th attributes name
				 \param attr5Value: 5th attributes value */
				virtual void writeElement(const c8* name, bool empty = false,
						const c8* attr1Name = 0, const c8* attr1Value = 0,
						const c8* attr2Name = 0, const c8* attr2Value = 0,
						const c8* attr3Name = 0, const c8* attr3Value = 0,
						const c8* attr4Name = 0, const c8* attr4Value = 0,
						const c8* attr5Name = 0, const c8* attr5Value = 0) = 0;

				//! Writes an xml element with any number of attributes
				virtual void writeElement(const c8* name, bool empty,
						arraystr &names,
						arraystr &values) = 0;

				//! Writes a comment into the xml file
				virtual void writeComment(const c8* comment) = 0;

				//! Writes the closing tag for an element. Like "</foo>"
				virtual void writeClosingTag(const c8* name) = 0;

				//! Writes a text into the file.
				/** All occurrences of special characters such as
				 & (&amp;), < (&lt;), > (&gt;), and " (&quot;) are automaticly
				 replaced. */
				virtual void writeText(const c8* text) = 0;

				//! Writes a line break
				virtual void writeLineBreak() = 0;
		};

		//! Creates an instance of a character xml writer.
		IXMLWriter* createXMLWriter(IWriteFile* file);

	} // end namespace io
} // end namespace irr

#endif

