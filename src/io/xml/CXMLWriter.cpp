// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CXMLWriter.h"
#include "core/irrString.h"
#include "irrgamesdkCompileConfig.h"

namespace irrgame
{
	namespace io
	{

		//! Constructor
		CXMLWriter::CXMLWriter(IWriteFile* file) :
				File(file), Tabs(0), TextWrittenLast(false)
		{
#ifdef DEBUG
			setDebugName("CXMLWriter");
#endif

			if (File)
				File->grab();
		}

		//! Destructor
		CXMLWriter::~CXMLWriter()
		{
			if (File)
				File->drop();
		}

		//! Writes a xml 1.0 header like <?xml version="1.0"?>
		void CXMLWriter::writeXMLHeader()
		{
			if (!File)
				return;

			const u8 bom[] =
			{ 0xEF, 0xBB, 0xBF }; // 0xEFBBBF;

			File->write(&bom, sizeof(bom));

			const c8* const p = "<?xml version=\"1.0\"?>";
			File->write(p, strlen(p) * sizeof(c8));

			writeLineBreak();
			TextWrittenLast = false;
		}

		//! Writes an xml element with maximal 5 attributes
		void CXMLWriter::writeElement(const c8* name, bool empty,
				const c8* attr1Name, const c8* attr1Value, const c8* attr2Name,
				const c8* attr2Value, const c8* attr3Name, const c8* attr3Value,
				const c8* attr4Name, const c8* attr4Value, const c8* attr5Name,
				const c8* attr5Value)
		{
			if (!File || !name)
				return;

			if (Tabs > 0)
			{
				for (int i = 0; i < Tabs; ++i)
					File->write("\t", sizeof(c8));
			}

			// write name

			File->write("<", sizeof(c8));
			File->write(name, strlen(name) * sizeof(c8));

			// write attributes

			writeAttribute(attr1Name, attr1Value);
			writeAttribute(attr2Name, attr2Value);
			writeAttribute(attr3Name, attr3Value);
			writeAttribute(attr4Name, attr4Value);
			writeAttribute(attr5Name, attr5Value);

			// write closing tag
			if (empty)
				File->write(" />", 3 * sizeof(c8));
			else
			{
				File->write(">", sizeof(c8));
				++Tabs;
			}

			TextWrittenLast = false;
		}

		//! Writes an xml element with any number of attributes
		void CXMLWriter::writeElement(const c8* name, bool empty,
				core::array<core::stringc> &names,
				core::array<core::stringc> &values)
		{
			if (!File || !name)
				return;

			if (Tabs > 0)
			{
				for (int i = 0; i < Tabs; ++i)
					File->write("\t", sizeof(c8));
			}

			// write name

			File->write("<", sizeof(c8));
			File->write(name, strlen(name) * sizeof(c8));

			// write attributes
			u32 i = 0;
			for (; i < names.size() && i < values.size(); ++i)
				writeAttribute(names[i].c_str(), values[i].c_str());

			// write closing tag
			if (empty)
				File->write(" />", 3 * sizeof(c8));
			else
			{
				File->write(">", sizeof(c8));
				++Tabs;
			}

			TextWrittenLast = false;
		}

		void CXMLWriter::writeAttribute(const c8* name,
				const c8* value)
		{
			if (!name || !value)
				return;

			File->write(" ", sizeof(wchar_t));
			File->write(name, strlen(name) * sizeof(c8));
			File->write("=\"", 2 * sizeof(c8));
			writeText(value);
			File->write("\"", sizeof(c8));
		}

		//! Writes a comment into the xml file
		void CXMLWriter::writeComment(const c8* comment)
		{
			if (!File || !comment)
				return;

			File->write("<!--", 4 * sizeof(c8));
			writeText(comment);
			File->write("-->", 3 * sizeof(c8));
		}

		//! Writes the closing tag for an element. Like </foo>
		void CXMLWriter::writeClosingTag(const c8* name)
		{
			if (!File || !name)
				return;

			--Tabs;

			if (Tabs > 0 && !TextWrittenLast)
			{
				for (int i = 0; i < Tabs; ++i)
					File->write("\t", sizeof(c8));
			}

			File->write(L"</", 2 * sizeof(c8));
			File->write(name, strlen(name) * sizeof(c8));
			File->write(L">", sizeof(c8));
			TextWrittenLast = false;
		}

		const CXMLWriter::XMLSpecialCharacters XMLWSChar[] =
		{
		{ '&', "&amp;" },
		{ '<', "&lt;" },
		{ '>', "&gt;" },
		{ '"', "&quot;" },
		{ '\0', 0 } };

		//! Writes a text into the file. All occurrences of special characters like
		//! & (&amp;), < (&lt;), > (&gt;), and " (&quot;) are automaticly replaced.
		void CXMLWriter::writeText(const c8* text)
		{
			if (!File || !text)
				return;

			core::stringc s;
			const c8* p = text;

			while (*p)
			{
				// check if it is matching
				bool found = false;
				for (s32 i = 0; XMLWSChar[i].Character != '\0'; ++i)
					if (*p == XMLWSChar[i].Character)
					{
						s.append(XMLWSChar[i].Symbol);
						found = true;
						break;
					}

				if (!found)
					s.append(*p);
				++p;
			}

			// write new string
			File->write(s.c_str(), s.size() * sizeof(wchar_t));
			TextWrittenLast = true;
		}

		//! Writes a line break
		void CXMLWriter::writeLineBreak()
		{
			if (!File)
				return;

			File->write(LINEBREAK, sizeof(LINEBREAK));
		}

		//! Creates an instance of a wide character xml writer.
		IXMLWriter* createXMLWriter(IWriteFile* file)
		{
			if (!file)
				return 0;

			return new CXMLWriter(file);
		}

	}// end namespace irr
} // end namespace io

