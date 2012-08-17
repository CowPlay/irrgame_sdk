/*
 * CXMLReader.cpp
 *
 *  Created on: Aug 7, 2012
 *      Author: gregorytkach
 */
#include "CXMLReader.h"
#include "io/IReadFile.h"
#include "io/ioutil.h"
#include "core/fast_atof.h"
namespace irrgame
{
	namespace io
	{
		//! Default constructor
		CXMLReader::CXMLReader(IReadFile* file) :
				TextData(0), P(0), TextBegin(0), TextSize(0), CurrentNodeType(
						EXNT_NONE), IsEmptyElement(true)
		{
			IRR_ASSERT(file != 0);

			// read whole xml file

			readFile(file);

			// create list with special characters

			createSpecialCharacterList();

			// set pointer to text begin
			P = TextBegin;
		}

		//! Destructor
		CXMLReader::~CXMLReader()
		{
			delete[] TextData;
		}

		//! reads the xml file and converts it into the wanted character format.
		bool CXMLReader::readFile(IReadFile* file)
		{
			long size = file->getSize();

			if (size < 0)
				return false;

			size += 4; // We need four terminating 0's at the end.
					   // For ASCII we need 1 0's, for UTF-16 2, for UTF-32 4.

			c8* data8 = new c8[size];

			if (!file->read(data8, size - 4))
			{
				delete[] data8;
				return false;
			}

			// add zeros at end

			memset(data8 + size - 4, 0, 4);

			char16* data16 = reinterpret_cast<char16*>(data8);
			char32* data32 = reinterpret_cast<char32*>(data8);

			// now we need to convert the data to the desired target format
			// based on the byte order mark.

			const unsigned char UTF8[] =
			{ 0xEF, 0xBB, 0xBF }; // 0xEFBBBF;
			const int UTF16_BE = 0xFFFE;
			const int UTF16_LE = 0xFEFF;
			const int UTF32_BE = 0xFFFE0000;
			const int UTF32_LE = 0x0000FEFF;

			// check source for all utf versions and convert to utf8 format

			if (size >= 4 && data32[0] == (char32) UTF32_BE)
			{
				// UTF-32, big endian
				convertTextData(ETF_UTF32_BE, data32 + 1, data8,
						(size / 4) - 1); // data32+1 because we need to skip the header
			}
			else if (size >= 4 && data32[0] == (char32) UTF32_LE)
			{
				// UTF-32, little endian
				convertTextData(ETF_UTF32_LE, data32 + 1, data8,
						(size / 4) - 1); // data32+1 because we need to skip the header
			}
			else if (size >= 2 && data16[0] == UTF16_BE)
			{
				// UTF-16, big endian
				convertTextData(ETF_UTF16_BE, data16 + 1, data8,
						(size / 2) - 1); // data16+1 because we need to skip the header
			}
			else if (size >= 2 && data16[0] == UTF16_LE)
			{
				// UTF-16, little endian
				convertTextData(ETF_UTF16_LE, data16 + 1, data8,
						(size / 2) - 1); // data16+1 because we need to skip the header
			}
			else if (size >= 3 && memcmp(data8, UTF8, 3) == 0)
			{
				// UTF-8
				convertTextData(ETF_UTF8, data8 + 3, data8, size - 3); // data8+3 because we need to skip the header
			}
			else
			{
				// ASCII
				convertTextData(ETF_ASCII, data8, data8, size);
			}

			return true;
		}

		//! converts the text file into the desired format.
		//! \param source: begin of the text (without byte order mark)
		//! \param pointerToStore: pointer to text data block which can be
		//! stored or deleted based on the nesessary conversion.
		//! \param sizeWithoutHeader: Text size in characters without header
		template<class src_c8>
		void CXMLReader::convertTextData(ETEXT_FORMAT srcFormat, src_c8* source,
				c8* pointerToStore, int sizeWithoutHeader)
		{
			// convert little to big endian if necessary
			if (sizeof(src_c8) > 1 && !isLittleEndian(srcFormat))
				convertToLittleEndian(source);

			// check if conversion is necessary:
			if (sizeof(src_c8) == sizeof(c8))
			{
				// no need to convert
				TextBegin = (c8*) source;
				TextData = (c8*) pointerToStore;
				TextSize = sizeWithoutHeader;
			}
			else
			{
				// convert source into target data format.
				// TODO: implement a real conversion. This one just
				// copies bytes. This is a problem when there are
				// unicode symbols using more than one character.

				TextData = new c8[sizeWithoutHeader];

				for (int i = 0; i < sizeWithoutHeader; ++i)
					TextData[i] = (c8) source[i];

				TextBegin = TextData;
				TextSize = sizeWithoutHeader;

				// delete original data because no longer needed
				delete[] pointerToStore;
			}
		}

		//! returns if a format is little endian
		inline bool CXMLReader::isLittleEndian(ETEXT_FORMAT f)
		{
			return f == ETF_ASCII || f == ETF_UTF8 || f == ETF_UTF16_LE
					|| f == ETF_UTF32_LE;
		}

		//! converts whole text buffer to little endian
		template<class src_c8>
		void CXMLReader::convertToLittleEndian(src_c8* t)
		{
			if (sizeof(src_c8) == 4)
			{
				// 32 bit

				while (*t)
				{
					*t = ((*t & 0xff000000) >> 24) | ((*t & 0x00ff0000) >> 8)
							| ((*t & 0x0000ff00) << 8)
							| ((*t & 0x000000ff) << 24);
					++t;
				}
			}
			else
			{
				// 16 bit

				while (*t)
				{
					*t = (*t >> 8) | (*t << 8);
					++t;
				}
			}
		}

		//! generates a list with xml special characters
		void CXMLReader::createSpecialCharacterList()
		{
			// list of strings containing special symbols,
			// the first character is the special character,
			// the following is the symbol string without trailing &.

			SpecialCharacters.push_back("&amp;");
			SpecialCharacters.push_back("<lt;");
			SpecialCharacters.push_back(">gt;");
			SpecialCharacters.push_back("\"quot;");
			SpecialCharacters.push_back("'apos;");

		}

		//! Reads forward to the next xml node.
		//! \return Returns false, if there was no further node.
		bool CXMLReader::read()
		{
			// if not end reached, parse the node
			if (P && (u32) (P - TextBegin) < TextSize - 1 && *P != 0)
			{
				return parseCurrentNode();
			}

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return false;
		}

		//! Returns the type of the current XML node.
		EXML_NODE_TYPE CXMLReader::getNodeType() const
		{
			return CurrentNodeType;
		}

		//! Returns attribute count of the current XML node.
		u32 CXMLReader::getAttributeCount() const
		{
			return Attributes.size();
		}

		//! Returns name of an attribute.
		const c8* CXMLReader::getAttributeName(int idx) const
		{
			return Attributes[idx].Name.c_str();
		}

		//! Returns the value of an attribute.
		const c8* CXMLReader::getAttributeValue(int idx) const
		{
			return Attributes[idx].Value.c_str();
		}

		//! Returns the value of an attribute.
		const c8* CXMLReader::getAttributeValue(const c8* name) const
		{
			const SAttribute* attr = getAttributeByName(name);

			IRR_ASSERT(attr != 0);

			return attr->Value.c_str();
		}

		//! Returns the value of an attribute
		const c8* CXMLReader::getAttributeValueSafe(const c8* name) const
		{
			const SAttribute* attr = getAttributeByName(name);

			if (!attr)
				return EmptyString.c_str();

			return attr->Value.c_str();
		}

		//! Returns the value of an attribute as integer.
		s32 CXMLReader::getAttributeValueAsInt(const c8* name) const
		{
			return (s32) getAttributeValueAsFloat(name);
		}

		//! Returns the value of an attribute as integer.
		s32 CXMLReader::getAttributeValueAsInt(int idx) const
		{
			return (s32) getAttributeValueAsFloat(idx);
		}

		//! Returns the value of an attribute as float.
		f32 CXMLReader::getAttributeValueAsFloat(const c8* name) const
		{
			const SAttribute* attr = getAttributeByName(name);

			IRR_ASSERT(attr != 0);

			core::stringc c = attr->Value.c_str();
			return core::fast_atof(c.c_str());
		}

		//! Returns the value of an attribute as float.
		f32 CXMLReader::getAttributeValueAsFloat(int idx) const
		{
			const c8* attrvalue = getAttributeValue(idx);

			IRR_ASSERT(sizeof(attrvalue) > 0);

			core::stringc c = attrvalue;
			return core::fast_atof(c.c_str());
		}

		//! Returns the name of the current node.
		const c8* CXMLReader::getNodeName() const
		{
			return NodeName.c_str();
		}

		//! Returns data of the current node.
		const c8* CXMLReader::getNodeData() const
		{
			return NodeName.c_str();
		}

		//! Returns if an element is an empty element, like <foo />
		bool CXMLReader::isEmptyElement() const
		{
			return IsEmptyElement;
		}

		// Reads the current xml node
		// return false if no further node is found
		bool CXMLReader::parseCurrentNode()
		{
			c8* start = P;

			// more forward until '<' found
			while (*P != '<' && *P)
				++P;

			// not a node, so return false
			if (!*P)
				return false;

			if (P - start > 0)
			{
				// we found some text, store it
				if (setText(start, P))
					return true;
			}

			++P;

			// based on current token, parse and report next element
			switch (*P)
			{
				case '/':
					parseClosingXMLElement();
					break;
				case '?':
					ignoreDefinition();
					break;
				case '!':
					if (!parseCDATA())
						parseComment();
					break;
				default:
					parseOpeningXMLElement();
					break;
			}
			return true;
		}

		//! sets the state that text was found. Returns true if set should be set
		bool CXMLReader::setText(c8* start, c8* end)
		{
			// check if text is more than 2 characters, and if not, check if there is
			// only white space, so that this text won't be reported
			if (end - start < 3)
			{
				c8* p = start;
				for (; p != end; ++p)
					if (!io::isWhiteSpace(*p))
						break;

				if (p == end)
					return false;
			}

			// set current text to the parsed text, and replace xml special characters
			core::stringc s(start, (int) (end - start));
			NodeName = replaceSpecialCharacters(s);

			// current XML node type is text
			CurrentNodeType = EXNT_TEXT;

			return true;
		}

		//! ignores an xml definition like <?xml something />
		void CXMLReader::ignoreDefinition()
		{
			CurrentNodeType = EXNT_UNKNOWN;

			// move until end marked with '>' reached
			while (*P != '>')
				++P;

			++P;
		}

		//! parses a comment
		void CXMLReader::parseComment()
		{
			CurrentNodeType = EXNT_COMMENT;
			P += 1;

			c8 *pCommentBegin = P;

			int count = 1;

			// move until end of comment reached
			while (count)
			{
				if (*P == '>')
					--count;
				else if (*P == '<')
					++count;

				++P;
			}

			P -= 3;
			NodeName = core::stringc(pCommentBegin + 2,
					(int) (P - pCommentBegin - 2));
			P += 3;
		}

		//! parses an opening xml element and reads attributes
		void CXMLReader::parseOpeningXMLElement()
		{
			CurrentNodeType = EXNT_ELEMENT;
			IsEmptyElement = false;
			Attributes.clear();

			// find name
			const c8* startName = P;

			// find end of element
			while (*P != '>' && !io::isWhiteSpace(*P))
				++P;

			const c8* endName = P;

			// find Attributes
			while (*P != '>')
			{
				if (io::isWhiteSpace(*P))
					++P;
				else
				{
					if (*P != '/')
					{
						// we've got an attribute

						// read the attribute names
						const c8* attributeNameBegin = P;

						while (!isWhiteSpace(*P) && *P != '=')
							++P;

						const c8* attributeNameEnd = P;
						++P;

						// read the attribute value
						// check for quotes and single quotes, thx to murphy
						while ((*P != '\"') && (*P != '\'') && *P)
							++P;

						if (!*P) // malformatted xml file
							return;

						const c8 attributeQuoteChar = *P;

						++P;
						const c8* attributeValueBegin = P;

						while (*P != attributeQuoteChar && *P)
							++P;

						if (!*P) // malformatted xml file
							return;

						const c8* attributeValueEnd = P;
						++P;

						SAttribute attr;
						attr.Name = core::stringc(attributeNameBegin,
								(int) (attributeNameEnd - attributeNameBegin));

						core::stringc s(attributeValueBegin,
								(int) (attributeValueEnd - attributeValueBegin));

						attr.Value = replaceSpecialCharacters(s);
						Attributes.push_back(attr);
					}
					else
					{
						// tag is closed directly
						++P;
						IsEmptyElement = true;
						break;
					}
				}
			}

			// check if this tag is closing directly
			if (endName > startName && *(endName - 1) == '/')
			{
				// directly closing tag
				IsEmptyElement = true;
				endName--;
			}

			NodeName = core::stringc(startName, (int) (endName - startName));

			++P;
		}

		//! parses an closing xml tag
		void CXMLReader::parseClosingXMLElement()
		{
			CurrentNodeType = EXNT_ELEMENT_END;
			IsEmptyElement = false;
			Attributes.clear();

			++P;
			const c8* pBeginClose = P;

			while (*P != '>')
				++P;

			NodeName = core::stringc(pBeginClose, (int) (P - pBeginClose));
			++P;
		}

		//! parses a possible CDATA section, returns false if begin was not a CDATA section
		bool CXMLReader::parseCDATA()
		{
			if (*(P + 1) != '[')
				return false;

			CurrentNodeType = EXNT_CDATA;

			// skip '<![CDATA['
			int count = 0;
			while (*P && count < 8)
			{
				++P;
				++count;
			}

			if (!*P)
				return true;

			c8 *cDataBegin = P;
			c8 *cDataEnd = 0;

			// find end of CDATA
			while (*P && !cDataEnd)
			{
				if (*P == '>' && (*(P - 1) == ']') && (*(P - 2) == ']'))
				{
					cDataEnd = P - 2;
				}

				++P;
			}

			if (cDataEnd)
				NodeName = core::stringc(cDataBegin,
						(int) (cDataEnd - cDataBegin));
			else
				NodeName = "";

			return true;
		}

		// finds a current attribute by name, returns 0 if not found
		const CXMLReader::SAttribute* CXMLReader::getAttributeByName(
				const c8* name) const
		{
			IRR_ASSERT(sizeof(name) > 0);

			core::stringc n = name;

			for (int i = 0; i < (int) Attributes.size(); ++i)
				if (Attributes[i].Name == n)
					return &Attributes[i];

			return 0;
		}

		// replaces xml special characters in a string and creates a new one
		core::stringc CXMLReader::replaceSpecialCharacters(
				core::stringc& origstr)
		{
			int pos = origstr.findFirst('&');
			int oldPos = 0;

			if (pos == -1)
				return origstr;

			core::stringc newstr;

			while (pos != -1 && pos < (int) origstr.size() - 2)
			{
				// check if it is one of the special characters

				int specialChar = -1;
				for (int i = 0; i < (int) SpecialCharacters.size(); ++i)
				{
					const c8* p = &origstr.c_str()[pos] + 1;

					if (SpecialCharacters[i].equalsn(p,
							SpecialCharacters[i].size() - 1))
					{
						specialChar = i;
						break;
					}
				}

				if (specialChar != -1)
				{
					newstr.append(origstr.subString(oldPos, pos - oldPos));
					newstr.append(SpecialCharacters[specialChar][0]);
					pos += SpecialCharacters[specialChar].size();
				}
				else
				{
					newstr.append(origstr.subString(oldPos, pos - oldPos + 1));
					pos += 1;
				}

				// find next &
				oldPos = pos;
				pos = origstr.findNext('&', pos);
			}

			if (oldPos < (int) origstr.size() - 1)
				newstr.append(
						origstr.subString(oldPos, origstr.size() - oldPos));

			return newstr;
		}

		//! Creates an instance of an UFT-8 or ASCII character xml parser. Internal function. Please do not use.
		IXMLReader* createXMLReader(IReadFile* file)
		{
			return new CXMLReader(file);
		}
	}
}

