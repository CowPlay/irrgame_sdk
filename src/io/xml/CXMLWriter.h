// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef CXMLWRITER_H
#define CXMLWRITER_H

#include "io/xml/IXMLWriter.h"
#include "io/IWriteFile.h"

namespace irrgame
{
	namespace io
	{

		//! Interface providing methods for making it easier to write XML files.
		class CXMLWriter: public IXMLWriter
		{
			public:

				//! Constructor
				CXMLWriter(IWriteFile* file);

				//! Destructor
				virtual ~CXMLWriter();

				//! Writes a xml 1.0 header like <?xml version="1.0"?>
				virtual void writeXMLHeader();

				//! Writes an xml element with maximal 5 attributes
				virtual void writeElement(const c8* name, bool empty = false,
						const c8* attr1Name = 0, const c8* attr1Value = 0,
						const c8* attr2Name = 0, const c8* attr2Value = 0,
						const c8* attr3Name = 0, const c8* attr3Value = 0,
						const c8* attr4Name = 0, const c8* attr4Value = 0,
						const c8* attr5Name = 0, const c8* attr5Value = 0);

				//! Writes an xml element with any number of attributes
				virtual void writeElement(const c8* name, bool empty,
						arraystr &names,
						arraystr &values);

				//! Writes a comment into the xml file
				virtual void writeComment(const c8* comment);

				//! Writes the closing tag for an element. Like </foo>
				virtual void writeClosingTag(const c8* name);

				//! Writes a text into the file. All occurrences of special characters like
				//! & (&amp;), < (&lt;), > (&gt;), and " (&quot;) are automaticly replaced.
				virtual void writeText(const c8* text);

				//! Writes a line break
				virtual void writeLineBreak();

				struct XMLSpecialCharacters
				{
						c8 Character;
						const c8* Symbol;
				};

			private:

				void writeAttribute(const c8* att, const c8* name);

			private:

				IWriteFile* File;
				s32 Tabs;

				bool TextWrittenLast;
		};

	} // end namespace irr
} // end namespace io

#endif

