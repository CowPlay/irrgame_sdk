/*
 * CXMLReader.h
 *
 *  Created on: Aug 7, 2012
 *      Author: gregorytkach
 */

#ifndef CXMLREADER_H_
#define CXMLREADER_H_

#include "io/xml/IXMLReader.h"
#include "io/xml/ETextFormat.h"
#include "core/collections/array.h"
#include "core/collections/stringc.h"
#include "SAttribute.h"

namespace irrgame
{
	namespace io
	{
		//! Implementation of IXMLReader
		class CXMLReader: public IXMLReader
		{
			public:

				//! Default constructor
				CXMLReader(IReadFile* file);

				//! Destructor
				virtual ~CXMLReader();

				//! Reads forward to the next xml node.
				//! \return Returns false, if there was no further node.
				virtual bool read();

				//! Returns the type of the current XML node.
				virtual EXML_NODE_TYPE getNodeType() const;

				//! Returns attribute count of the current XML node.
				virtual u32 getAttributeCount() const;

				//! Returns name of an attribute.
				virtual const c8* getAttributeName(int idx) const;

				//! Returns the value of an attribute.
				virtual const c8* getAttributeValue(int idx) const;

				//! Returns the value of an attribute.
				virtual const c8* getAttributeValue(const c8* name) const;

				//! Returns the value of an attribute
				virtual const c8* getAttributeValueSafe(const c8* name) const;

				//! Returns the value of an attribute as integer.
				s32 getAttributeValueAsInt(const c8* name) const;

				//! Returns the value of an attribute as integer.
				s32 getAttributeValueAsInt(int idx) const;

				//! Returns the value of an attribute as float.
				f32 getAttributeValueAsFloat(const c8* name) const;

				//! Returns the value of an attribute as float.
				f32 getAttributeValueAsFloat(int idx) const;

				//! Returns the name of the current node.
				virtual const c8* getNodeName() const;

				//! Returns data of the current node.
				virtual const c8* getNodeData() const;

				//! Returns if an element is an empty element, like <foo />
				virtual bool isEmptyElement() const;

			private:

				//! reads the xml file and converts it into the wanted character format.
				bool readFile(IReadFile* file);

				// Reads the current xml node
				// return false if no further node is found
				bool parseCurrentNode();

				//! sets the state that text was found. Returns true if set should be set
				bool setText(c8* start, c8* end);

				//! ignores an xml definition like <?xml something />
				void ignoreDefinition();

				//! parses a comment
				void parseComment();

				//! parses an opening xml element and reads attributes
				void parseOpeningXMLElement();

				//! parses an closing xml tag
				void parseClosingXMLElement();

				//! parses a possible CDATA section, returns false if begin was not a CDATA section
				bool parseCDATA();

				// finds a current attribute by name, returns 0 if not found
				const SAttribute* getAttributeByName(const c8* name) const;

				// replaces xml special characters in a string and creates a new one
				core::stringc replaceSpecialCharacters(core::stringc& origstr);

				//! converts the text file into the desired format.
				//! \param source: begin of the text (without byte order mark)
				//! \param pointerToStore: pointer to text data block which can be
				//! stored or deleted based on the nesessary conversion.
				//! \param sizeWithoutHeader: Text size in characters without header
				template<class src_char_type>
				void convertTextData(ETextFormat srcFormat,
						src_char_type* source, c8* pointerToStore,
						int sizeWithoutHeader);

				//! Returns True if format is little endian. Otherwise - return False.
				bool isLittleEndian(ETextFormat f);

				//! converts whole text buffer to little endian
				template<class src_char_type>
				void convertToLittleEndian(src_char_type* t);

				//! generates a list with xml special characters
				void createSpecialCharacterList();

			private:

				c8* TextData;         	// data block of the text file
				c8* P;                // current point in text to parse
				c8* TextBegin;        	// start of text to parse
				u32 TextSize; // size of text to parse in characters, not bytes

				EXML_NODE_TYPE CurrentNodeType; // type of the currently parsed node
				// source format of the xml file

				core::stringc NodeName; // name of the node currently in
				core::stringc EmptyString; // empty string to be returned by getSafe() methods

				bool IsEmptyElement; // is the currently parsed node empty?

				arraystr SpecialCharacters; // see createSpecialCharacterList()

				core::array<SAttribute> Attributes; // attributes of current element
		};
	}
}

#endif /* CXMLREADER_H_ */
