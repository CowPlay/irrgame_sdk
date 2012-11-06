// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine" and the "irrXML" project.
// For conditions of distribution and use, see copyright notice in irrlicht.h and/or irrXML.h

#ifndef IRRXMLREADER_H_
#define IRRXMLREADER_H_
#include "EXmlNodeTypes.h"
#include "core/engine/IReferenceCounted.h"

namespace irrgame
{
	namespace io
	{
		class IReadFile;

		/** Not using wchar_t for this because
		 wchar_t has 16 bit on windows and 32 bit on other operating systems. */

		//! defines the utf-16 type.
		typedef unsigned short char16;
		//! defines the utf-32 type.
		typedef unsigned long char32;


		//! Interface providing easy read access to a XML file.
		// Output format can UTF8 or ASCII
		class IXMLReader: public IReferenceCounted
		{
			public:

				//! Destructor
				virtual ~IXMLReader()
				{
				}

				//! Reads forward to the next xml node.
				/** \return Returns false, if there was no further node. */
				virtual bool read() = 0;

				//! Returns the type of the current XML node.
				virtual EXML_NODE_TYPE getNodeType() const = 0;

				//! Returns attribute count of the current XML node.
				/** This is usually
				 non null if the current node is EXN_ELEMENT, and the element has attributes.
				 \return Returns amount of attributes of this xml node. */
				virtual unsigned int getAttributeCount() const = 0;

				//! Returns name of an attribute.
				/** \param idx: Zero based index, should be something between 0 and getAttributeCount()-1.
				 \return Name of the attribute, 0 if an attribute with this index does not exist. */
				virtual const c8* getAttributeName(int idx) const = 0;

				//! Returns the value of an attribute. Attribute must be exists.
				/** \param idx: Zero based index, should be something between 0 and getAttributeCount()-1.
				 \return Value of the attribute. */
				virtual const c8* getAttributeValue(int idx) const = 0;

				//! Returns the value of an attribute.
				/** \param name: Name of the attribute.
				 \return Value of the attribute, 0 if an attribute with this name does not exist. */
				virtual const c8* getAttributeValue(const c8* name) const = 0;

				//! Returns the value of an attribute in a safe way.
				/** Like getAttributeValue(), but does not
				 return 0 if the attribute does not exist. An empty string ("") is returned then.
				 \param name: Name of the attribute.
				 \return Value of the attribute, and "" if an attribute with this name does not exist */
				virtual const c8* getAttributeValueSafe(
						const c8* name) const = 0;

				//! Returns the value of an attribute as integer.
				/** \param name Name of the attribute.
				 \return Value of the attribute as integer, and 0 if an attribute with this name does not exist or
				 the value could not be interpreted as integer. */
				virtual int getAttributeValueAsInt(const c8* name) const = 0;

				//! Returns the value of an attribute as integer.
				/** \param idx: Zero based index, should be something between 0 and getAttributeCount()-1.
				 \return Value of the attribute as integer, and 0 if an attribute with this index does not exist or
				 the value could not be interpreted as integer. */
				virtual int getAttributeValueAsInt(int idx) const = 0;

				//! Returns the value of an attribute as float.
				/** \param name: Name of the attribute.
				 \return Value of the attribute as float, and 0 if an attribute with this name does not exist or
				 the value could not be interpreted as float. */
				virtual float getAttributeValueAsFloat(
						const c8* name) const = 0;

				//! Returns the value of an attribute as float.
				/** \param idx: Zero based index, should be something between 0 and getAttributeCount()-1.
				 \return Value of the attribute as float, and 0 if an attribute with this index does not exist or
				 the value could not be interpreted as float. */
				virtual float getAttributeValueAsFloat(int idx) const = 0;

				//! Returns the name of the current node.
				/** Only non null, if the node type is EXN_ELEMENT.
				 \return Name of the current node or 0 if the node has no name. */
				virtual const c8* getNodeName() const = 0;

				//! Returns data of the current node.
				/** Only non null if the node has some
				 data and it is of type EXN_TEXT or EXN_UNKNOWN. */
				virtual const c8* getNodeData() const = 0;

				//! Returns if an element is an empty element, like <foo />
				virtual bool isEmptyElement() const = 0;
		};

		//! Creates an instance of an UFT-8 or ASCII character xml parser. Internal function. Please do not use.
		IXMLReader* createXMLReader(IReadFile* file);

	}
// end namespace io
}// end namespace irrgame

#endif // IRRXMLREADER_H_
