// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "io/serialize/CAttributes.h"
//#include "CAttributeImpl.h"

#include "io/xml/IXMLWriter.h"

#include "io/serialize/CBBoxAttribute.h"
#include "io/serialize/CBinaryAttribute.h"
#include "io/serialize/CBoolAttribute.h"
#include "io/serialize/CColorAttribute.h"
#include "io/serialize/CColorfAttribute.h"
#include "io/serialize/CEnumAttribute.h"
#include "io/serialize/CIntAttribute.h"
#include "io/serialize/CMatrixAttribute.h"
#include "io/serialize/CFloatAttribute.h"
#include "io/serialize/CRectAttribute.h"
#include "io/serialize/CStringAttribute.h"
#include "io/serialize/CStringArrayAttribute.h"
#include "io/serialize/CVector2DAttribute.h"
#include "io/serialize/CVector3DAttribute.h"
#include "io/serialize/CQuaternionAttribute.h"

namespace irrgame
{
	namespace io
	{
		//! Default constructor
		CAttributes::CAttributes()
		{
#ifdef DEBUG
			setDebugName("CAttributes");
#endif
		}

		//! Destructor
		CAttributes::~CAttributes()
		{
			clear();
		}

		//! Removes all attributes
		void CAttributes::clear()
		{
			for (u32 i = 0; i < Attributes.size(); ++i)
				Attributes[i]->drop();

			Attributes.clear();
		}

		//! Returns amount of string attributes set in this scene manager.
		u32 CAttributes::getAttributeCount() const
		{
			return Attributes.size();
		}

		//! Returns string attribute name by index.
		//! \param index: Index value, must be between 0 and getStringAttributeCount()-1.
		const c8* CAttributes::getAttributeName(s32 index)
		{
			return Attributes[index]->Name.c_str();
		}

		IAttribute* CAttributes::getAttributeByName(const c8* name)
		{
			for (u32 i = 0; i < Attributes.size(); ++i)
				if (Attributes[i]->Name == name)
					return Attributes[i];

			return 0;
		}

		//! Returns the type of an attribute
		E_ATTRIBUTE_TYPE CAttributes::getAttributeType(const c8* attributeName)
		{
			E_ATTRIBUTE_TYPE ret = EAT_UNKNOWN;

			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				ret = att->getType();

			return ret;
		}

		//! Returns attribute type by index.
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		E_ATTRIBUTE_TYPE CAttributes::getAttributeType(s32 index)
		{
			return Attributes[index]->getType();
		}

		//! Returns the type of an attribute
		const c8* CAttributes::getAttributeTypeString(const c8* attributeName)
		{
			IAttribute* att = getAttributeByName(attributeName);

			return att ? att->getTypeString() : "unknown";
		}

		//! Returns attribute type string by index.
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		const c8* CAttributes::getAttributeTypeString(s32 index)
		{
			return Attributes[index]->getTypeString();
		}

		//! Returns if an attribute with a name exists
		bool CAttributes::existsAttribute(const c8* attributeName)
		{
			return getAttributeByName(attributeName) != 0;
		}

		//! Returns attribute index from name, -1 if not found
		s32 CAttributes::findAttribute(const c8* attributeName)
		{
			for (u32 i = 0; i < Attributes.size(); ++i)
				if (Attributes[i]->Name == attributeName)
					return i;

			return -1;
		}

		//! Reads attributes from a xml file.
		//! \param readCurrentElementOnly: If set to true, reading only works if current element has the name 'attributes'.
		//! IF set to false, the first appearing list attributes are read.
		//! TODO: add contract
		bool CAttributes::read(io::IXMLReader* reader,
				bool readCurrentElementOnly, const c8* nonDefaultElementName)
		{
			if (!reader)
				return false;

			clear();

			core::stringc elementName = "attributes";
			if (nonDefaultElementName)
				elementName = nonDefaultElementName;

			if (readCurrentElementOnly)
			{
				if (elementName != reader->getNodeName())
					return false;
			}

			while (reader->read())
			{
				switch (reader->getNodeType())
				{
					case io::EXNT_ELEMENT:
						readAttributeFromXML(reader);
						break;
					case io::EXNT_ELEMENT_END:
						if (elementName == reader->getNodeName())
							return true;
						break;
					default:
						break;
				}
			}

			return true;
		}

		void CAttributes::readAttributeFromXML(io::IXMLReader* reader)
		{
			core::stringc element = reader->getNodeName();
			core::stringc name = reader->getAttributeValue("name");

			if (element == "int")
			{
				addInt(name.c_str(), 0);
				Attributes.getLast()->setString(
						reader->getAttributeValue("value"));
			}
			else if (element == "float")
			{
				addFloat(name.c_str(), 0);
				Attributes.getLast()->setString(
						reader->getAttributeValue("value"));
			}
			else if (element == "string")
			{
				addString(name.c_str(), "");
				Attributes.getLast()->setString(
						reader->getAttributeValue("value"));
			}
			else if (element == "binary")
			{
				addBinary(name.c_str(), 0, 0);
				Attributes.getLast()->setString(
						reader->getAttributeValue("value"));
			}
			else if (element == "stringarray")
			{
				core::array<core::stringc> tmpArray;

				s32 count = reader->getAttributeValueAsInt("count");
				s32 n = 0;
				const core::stringc tmpName("value");
				for (; n < count; ++n)
				{
					tmpArray.push_back(
							reader->getAttributeValue(
									(tmpName + core::stringc(n)).c_str()));
				}
				addArray(name.c_str(), tmpArray);
			}
			else if (element == "enum")
			{
				addEnum(name.c_str(), 0, 0);
				Attributes.getLast()->setString(
						reader->getAttributeValue("value"));
			}
			else if (element == "bool")
			{
				addBool(name.c_str(), 0);
				Attributes.getLast()->setString(
						reader->getAttributeValue("value"));
			}
			else if (element == "color")
			{
				addColor(name.c_str(), video::SColor());
				Attributes.getLast()->setString(
						reader->getAttributeValue("value"));
			}
			else if (element == "colorf")
			{
				addColorf(name.c_str(), video::SColorf());
				Attributes.getLast()->setString(
						reader->getAttributeValue("value"));
			}
			else if (element == "vector2d")
			{
				addVector2d(name.c_str(), core::vector2df());
				Attributes.getLast()->setString(
						reader->getAttributeValue("value"));
			}
			else if (element == "vector3d")
			{
				addVector3d(name.c_str(), core::vector3df());
				Attributes.getLast()->setString(
						reader->getAttributeValue("value"));
			}
//
//
//
//
//			else if (element == "rect")
//			{
//				addRect(name.c_str(), core::recti());
//				Attributes.getLast()->setString(
//						reader->getAttributeValue("value"));
//			}
//			else if (element == "matrix")
//			{
//				addMatrix(name.c_str(), core::matrix4());
//				Attributes.getLast()->setString(
//						reader->getAttributeValue("value"));
//			}
//			else if (element == "quaternion")
//			{
//				addQuaternion(name.c_str(), core::quaternion());
//				Attributes.getLast()->setString(
//						reader->getAttributeValue("value"));
//			}
//			else if (element == "box3d")
//			{
//				addBox3d(name.c_str(), core::aabbox3df());
//				Attributes.getLast()->setString(
//						reader->getAttributeValue("value"));
//			}
//			else if (element == "plane")
//			{
//				addPlane3d(name.c_str(), core::plane3df());
//				Attributes.getLast()->setString(
//						reader->getAttributeValue("value"));
//			}
//			else if (element == "triangle")
//			{
//				addTriangle3d(name.c_str(), core::triangle3df());
//				Attributes.getLast()->setString(
//						reader->getAttributeValue("value"));
//			}
//			else if (element == "line2d")
//			{
//				addLine2d(name.c_str(), core::line2df());
//				Attributes.getLast()->setString(
//						reader->getAttributeValue("value"));
//			}
//			else if (element == "line3d")
//			{
//				addLine3d(name.c_str(), core::line3df());
//				Attributes.getLast()->setString(
//						reader->getAttributeValue("value"));
//			}
//
//			else if (element == "userPointer")
//			{
//				// It's debatable if a pointer should be set or not, but it's more likely that adding it now would wreck user-applications.
//				// Also it probably doesn't makes sense setting this to a value when it comes from file.
//			}
		}

		/*

		 Integer Attribute

		 */

		//! Adds an attribute as integer
		void CAttributes::addInt(const c8* attributeName, s32 value)
		{
			Attributes.push_back(new CIntAttribute(attributeName, value));
		}

		//! Sets a attribute as integer value
		void CAttributes::setAttribute(const c8* attributeName, s32 value)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				att->setInt(value);
			else
				Attributes.push_back(new CIntAttribute(attributeName, value));
		}

		//! Gets a attribute as integer value
		//! \param attributeName: Name of the attribute to get.
		//! \return Returns value of the attribute previously set by setAttribute() as integer
		//! or 0 if attribute is not set.
		s32 CAttributes::getAttributeAsInt(const c8* attributeName)
		{
			IAttribute* att = getAttributeByName(attributeName);

			return att ? att->getInt() : 0;
		}

		//! Gets an attribute as integer value
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		s32 CAttributes::getAttributeAsInt(s32 index)
		{
			return Attributes[index]->getInt();
		}

		//! Sets an attribute as integer value
		void CAttributes::setAttribute(s32 index, s32 value)
		{
			Attributes[index]->setInt(value);
		}

		/*

		 Float Attribute

		 */

		//! Adds an attribute as float
		void CAttributes::addFloat(const c8* attributeName, f32 value)
		{
			Attributes.push_back(new CFloatAttribute(attributeName, value));
		}

		//! Sets a attribute as float value
		void CAttributes::setAttribute(const c8* attributeName, f32 value)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				att->setFloat(value);
			else
				Attributes.push_back(new CFloatAttribute(attributeName, value));
		}

		//! Gets a attribute as integer value
		//! \param attributeName: Name of the attribute to get.
		//! \return Returns value of the attribute previously set by setAttribute() as float value
		//! or 0 if attribute is not set.
		f32 CAttributes::getAttributeAsFloat(const c8* attributeName)
		{
			IAttribute* att = getAttributeByName(attributeName);

			return att ? att->getFloat() : 0.f;
		}

		//! Gets an attribute as float value
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		f32 CAttributes::getAttributeAsFloat(s32 index)
		{
			return Attributes[index]->getFloat();
		}

		//! Sets a attribute as float value
		void CAttributes::setAttribute(s32 index, f32 value)
		{
			Attributes[index]->setFloat(value);
		}

		/*

		 String Attribute

		 */

		//! Adds an attribute as string
		void CAttributes::addString(const c8* attributeName, const c8* value)
		{
			Attributes.push_back(new CStringAttribute(attributeName, value));
		}

		//! Sets a string attribute.
		//! \param attributeName: Name for the attribute
		//! \param value: Value for the attribute. Set this to 0 to delete the attribute
		void CAttributes::setAttribute(const c8* attributeName, const c8* value)
		{
			for (u32 i = 0; i < Attributes.size(); ++i)
				if (Attributes[i]->Name == attributeName)
				{
					if (!value)
					{
						Attributes[i]->drop();
						Attributes.erase(i);
					}
					else
						Attributes[i]->setString(value);

					return;
				}

			if (value)
				Attributes.push_back(
						new CStringAttribute(attributeName, value));

		}

		//! Sets an attribute value as string.
		//! \param attributeName: Name for the attribute
		void CAttributes::setAttribute(s32 index, const c8* value)
		{
			Attributes[index]->setString(value);
		}

		//! Gets a string attribute.
		//! \param attributeName: Name of the attribute to get.
		//! \return Returns value of the attribute previously set by setStringAttribute()
		//! or 0 if attribute is not set.
		core::stringc CAttributes::getAttributeAsString(const c8* attributeName)
		{
			IAttribute* att = getAttributeByName(attributeName);

			return att ? att->getString() : "";
		}

		//! Gets a string attribute.
		//! \param attributeName: Name of the attribute to get.
		//! \param out: Buffer where the string is copied to.
		void CAttributes::getAttributeAsString(const c8* attributeName, c8* out)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
			{
				core::stringc str = att->getString();
				strcpy(out, str.c_str());
			}
			else
				out[0] = 0;
		}

		//! Returns string attribute value by index.
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		core::stringc CAttributes::getAttributeAsString(s32 index)
		{
			return Attributes[index]->getString();
		}

		/*

		 Binary Data Attribute

		 */

		//! Adds an attribute as binary data
		void CAttributes::addBinary(const c8* attributeName, void* data,
				s32 dataSizeInBytes)
		{
			Attributes.push_back(
					new CBinaryAttribute(attributeName, data, dataSizeInBytes));
		}

		//! Sets an attribute as binary data
		void CAttributes::setAttribute(const c8* attributeName, void* data,
				s32 dataSizeInBytes)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				att->setBinary(data, dataSizeInBytes);
			else
				Attributes.push_back(
						new CBinaryAttribute(attributeName, data,
								dataSizeInBytes));
		}

		//! Sets an attribute as binary data
		void CAttributes::setAttribute(s32 index, void* data,
				s32 dataSizeInBytes)
		{
			Attributes[index]->setBinary(data, dataSizeInBytes);
		}

		//! Gets an attribute as binary data
		/** \param attributeName: Name of the attribute to get.
		 \param out Pointer to buffer where data shall be stored.
		 \param maxSizeInBytes Maximum number of bytes to write into out.
		 */
		void CAttributes::getAttributeAsBinaryData(const c8* attributeName,
				void* out, s32 maxSizeInBytes)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				att->getBinary(out, maxSizeInBytes);
		}

		//! Gets an attribute as binary data
		/** \param index: Index value, must be between 0 and getAttributeCount()-1.
		 \param out Pointer to buffer where data shall be stored.
		 \param maxSizeInBytes Maximum number of bytes to write into out.
		 */
		void CAttributes::getAttributeAsBinaryData(s32 index, void* out,
				s32 maxSizeInBytes)
		{
			Attributes[index]->getBinary(out, maxSizeInBytes);
		}

		/*

		 Array Attribute

		 */

		//! Adds an attribute as an array of wide strings
		void CAttributes::addArray(const c8* attributeName,
				const core::array<core::stringc>& value)
		{
			Attributes.push_back(
					new CStringArrayAttribute(attributeName, value));
		}

		//! Sets an attribute value as an array of strings.
		void CAttributes::setAttribute(const c8* attributeName,
				const core::array<core::stringc>& value)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				att->setArray(value);
			else
				Attributes.push_back(
						new CStringArrayAttribute(attributeName, value));
		}

		//! Sets an attribute as an array of wide strings
		void CAttributes::setAttribute(s32 index,
				const core::array<core::stringc>& value)
		{
			Attributes[index]->setArray(value);
		}

		//! Gets an attribute as an array of  strings.
		core::array<core::stringc> CAttributes::getAttributeAsArray(
				const c8* attributeName)
		{
			IAttribute* att = getAttributeByName(attributeName);

			return att ? att->getArray() : core::array<core::stringc>();
		}

		//! Returns attribute value as an array of wide strings by index.
		core::array<core::stringc> CAttributes::getAttributeAsArray(s32 index)
		{
			return Attributes[index]->getArray();
		}

		/*

		 Bool Attribute

		 */

		//! Adds an attribute as bool
		void CAttributes::addBool(const c8* attributeName, bool value)
		{
			Attributes.push_back(new CBoolAttribute(attributeName, value));
		}

		//! Sets a attribute as boolean value
		void CAttributes::setAttribute(const c8* attributeName, bool value)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				att->setBool(value);
			else
				Attributes.push_back(new CBoolAttribute(attributeName, value));
		}

		//! Sets an attribute as boolean value
		void CAttributes::setAttribute(s32 index, bool value)
		{
			Attributes[index]->setBool(value);
		}

		//! Gets a attribute as boolean value
		//! \param attributeName: Name of the attribute to get.
		//! \return Returns value of the attribute previously set by setAttribute() as bool
		//! or 0 if attribute is not set.
		bool CAttributes::getAttributeAsBool(const c8* attributeName)
		{

			IAttribute* att = getAttributeByName(attributeName);

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;

			return att ? att->getBool() : false;
		}

		//! Gets an attribute as boolean value
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		bool CAttributes::getAttributeAsBool(s32 index)
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;

			return Attributes[index]->getBool();
		}

		/*

		 Enumeration Attribute

		 */

		//! Adds an attribute as enum
		void CAttributes::addEnum(const c8* attributeName, const c8* enumValue,
				const c8* const * enumerationLiterals)
		{
			Attributes.push_back(
					new CEnumAttribute(attributeName, enumValue,
							enumerationLiterals));
		}

		//! Adds an attribute as enum
		void CAttributes::addEnum(const c8* attributeName, s32 enumValue,
				const c8* const * enumerationLiterals)
		{
			addEnum(attributeName, "", enumerationLiterals);
			Attributes.getLast()->setInt(enumValue);
		}

		//! Sets an attribute as enumeration
		void CAttributes::setAttribute(const c8* attributeName,
				const c8* enumValue, const c8* const * enumerationLiterals)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				att->setEnum(enumValue, enumerationLiterals);
			else
				Attributes.push_back(
						new CEnumAttribute(attributeName, enumValue,
								enumerationLiterals));
		}

		//! Sets an attribute as enumeration
		void CAttributes::setAttribute(s32 index, const c8* enumValue,
				const c8* const * enumerationLiterals)
		{
			Attributes[index]->setEnum(enumValue, enumerationLiterals);
		}

		//! Gets an attribute as enumeration
		//! \param attributeName: Name of the attribute to get.
		//! \return Returns value of the attribute previously set by setAttribute()
		const c8* CAttributes::getAttributeAsEnumeration(
				const c8* attributeName)
		{
			IAttribute* att = getAttributeByName(attributeName);

			return att ? att->getEnum() : 0;
		}

		//! Gets an attribute as enumeration
		s32 CAttributes::getAttributeAsEnumeration(const c8* attributeName,
				const c8* const * enumerationLiteralsToUse)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (enumerationLiteralsToUse && att)
			{
				const c8* value = att->getEnum();
				if (value)
				{
					for (s32 i = 0; enumerationLiteralsToUse[i]; ++i)
						if (!strcmp(value, enumerationLiteralsToUse[i]))
							return i;
				}
			}

			return -1;
		}

		//! Gets an attribute as enumeration
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		const c8* CAttributes::getAttributeAsEnumeration(s32 index)
		{
			return Attributes[index]->getEnum();
		}

		//! Gets an attribute as enumeration
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		s32 CAttributes::getAttributeAsEnumeration(s32 index,
				const c8* const * enumerationLiteralsToUse)
		{
			if ((u32) index < Attributes.size())
			{
				IAttribute* att = Attributes[index];

				if (enumerationLiteralsToUse && att)
				{
					const c8* value = att->getEnum();
					if (value)
					{
						for (s32 i = 0; enumerationLiteralsToUse[i]; ++i)
							if (!strcmp(value, enumerationLiteralsToUse[i]))
								return i;
					}
				}
			}

			return -1;
		}

		//! Gets the list of enumeration literals of an enumeration attribute
		//! \param attributeName: Name of the attribute to get.
		void CAttributes::getAttributeEnumerationLiteralsOfEnumeration(
				const c8* attributeName,
				core::array<core::stringc>& outLiterals)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
			{
				IRR_ASSERT(att->getType() != EAT_ENUM);

				outLiterals = ((CEnumAttribute*) att)->EnumLiterals;
			}
		}

		//! Gets the list of enumeration literals of an enumeration attribute
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		void CAttributes::getAttributeEnumerationLiteralsOfEnumeration(
				s32 index, core::array<core::stringc>& outLiterals)
		{
			IRR_ASSERT(Attributes[index]->getType() != EAT_ENUM);

			outLiterals = ((CEnumAttribute*) Attributes[index])->EnumLiterals;
		}

		/*

		 SColor Attribute

		 */

		//! Adds an attribute as color
		void CAttributes::addColor(const c8* attributeName, video::SColor value)
		{
			Attributes.push_back(new CColorAttribute(attributeName, value));
		}

		//! Sets a attribute as color
		void CAttributes::setAttribute(const c8* attributeName,
				video::SColor value)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				att->setColor(value);
			else
				Attributes.push_back(new CColorAttribute(attributeName, value));
		}

		//! Sets a attribute as color
		void CAttributes::setAttribute(s32 index, video::SColor color)
		{
			Attributes[index]->setColor(color);
		}

		//! Gets an attribute as color
		//! \param attributeName: Name of the attribute to get.
		//! \return Returns value of the attribute previously set by setAttribute()
		video::SColor CAttributes::getAttributeAsColor(const c8* attributeName)
		{
			video::SColor ret(0);

			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				ret = att->getColor();

			return ret;
		}

		//! Gets an attribute as color
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		video::SColor CAttributes::getAttributeAsColor(s32 index)
		{
			return Attributes[index]->getColor();
		}

		/*

		 SColorf Attribute

		 */

		//! Adds an attribute as floating point color
		void CAttributes::addColorf(const c8* attributeName,
				video::SColorf value)
		{
			Attributes.push_back(new CColorfAttribute(attributeName, value));
		}

		//! Sets a attribute as floating point color
		void CAttributes::setAttribute(const c8* attributeName,
				video::SColorf value)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				att->setColor(value);
			else
				Attributes.push_back(
						new CColorfAttribute(attributeName, value));
		}

		//! Sets a attribute as floating point color
		void CAttributes::setAttribute(s32 index, video::SColorf color)
		{
			Attributes[index]->setColor(color);
		}

		//! Gets an attribute as floating point color
		//! \param attributeName: Name of the attribute to get.
		//! \return Returns value of the attribute previously set by setAttribute()
		video::SColorf CAttributes::getAttributeAsColorf(
				const c8* attributeName)
		{
			IAttribute* att = getAttributeByName(attributeName);

			return att ? att->getColorf() : video::SColorf();
		}

		//! Gets an attribute as floating point color
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		video::SColorf CAttributes::getAttributeAsColorf(s32 index)
		{
			return Attributes[index]->getColorf();
		}

		/*

		 Vector2d Attribute

		 */

		//! Adds an attribute as 3d vector
		void CAttributes::addVector2d(const c8* attributeName,
				core::vector2df value)
		{
			Attributes.push_back(new CVector2DAttribute(attributeName, value));
		}

		//! Sets a attribute as vector
		void CAttributes::setAttribute(s32 index, core::vector2df v)
		{
			Attributes[index]->setVector2d(v);
		}

		//! Sets a attribute as 2d vector
		void CAttributes::setAttribute(const c8* attributeName,
				core::vector2df value)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				att->setVector2d(value);
			else
				Attributes.push_back(
						new CVector2DAttribute(attributeName, value));
		}

		//! Gets an attribute as vector
		//! \param attributeName: Name of the attribute to get.
		//! \return Returns value of the attribute previously set by setAttribute()
		core::vector2df CAttributes::getAttributeAsVector2d(
				const c8* attributeName)
		{
			IAttribute* att = getAttributeByName(attributeName);

			return att ? att->getVector2d() : core::vector2df();
		}

		//! Gets an attribute as 3d vector
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		core::vector2df CAttributes::getAttributeAsVector2d(s32 index)
		{
			return Attributes[index]->getVector2d();
		}

		/*

		 Vector3d Attribute

		 */

		//! Adds an attribute as 3d vector
		void CAttributes::addVector3d(const c8* attributeName,
				core::vector3df value)
		{
			Attributes.push_back(new CVector3DAttribute(attributeName, value));
		}

		//! Sets a attribute as vector
		void CAttributes::setAttribute(s32 index, core::vector3df v)
		{
			Attributes[index]->setVector3d(v);
		}

		//! Sets a attribute as 3d vector
		void CAttributes::setAttribute(const c8* attributeName,
				core::vector3df value)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				att->setVector3d(value);
			else
				Attributes.push_back(
						new CVector3DAttribute(attributeName, value));
		}

		//! Gets an attribute as vector
		//! \param attributeName: Name of the attribute to get.
		//! \return Returns value of the attribute previously set by setAttribute()
		core::vector3df CAttributes::getAttributeAsVector3d(
				const c8* attributeName)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				return att->getVector3d();
			else
				return core::vector3df();
		}

		//! Gets an attribute as 3d vector
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		core::vector3df CAttributes::getAttributeAsVector3d(s32 index)
		{
			return Attributes[index]->getVector3d();
		}

		/*

		 Rectangle Attribute

		 */

		//! Adds an attribute as rectangle
		void CAttributes::addRect(const c8* attributeName, core::recti value)
		{
			Attributes.push_back(new CRectAttribute(attributeName, value));
		}

		//! Sets a attribute as rectangle
		void CAttributes::setAttribute(const c8* attributeName,
				core::recti value)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				att->setRect(value);
			else
				Attributes.push_back(new CRectAttribute(attributeName, value));
		}

		//! Sets a attribute as rectangle
		void CAttributes::setAttribute(s32 index, core::recti v)
		{
			Attributes[index]->setRect(v);
		}

		//! Gets an attribute as rectangle
		//! \param index: Index value, must be between 0 and getAttributeCount()-1.
		core::recti CAttributes::getAttributeAsRect(s32 index)
		{
			return Attributes[index]->getRect();
		}

		//! Gets an attribute as rectangle
		//! \param attributeName: Name of the attribute to get.
		//! \return Returns value of the attribute previously set by setAttribute()
		core::recti CAttributes::getAttributeAsRect(const c8* attributeName)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				return att->getRect();
			else
				return core::recti();
		}

		/*

		 matrix attribute

		 */

		//! Adds an attribute as matrix
		void CAttributes::addMatrix(const c8* attributeName,
				const core::matrix4& v)
		{
			Attributes.push_back(new CMatrixAttribute(attributeName, v));
		}

		//! Sets an attribute as matrix
		void CAttributes::setAttribute(const c8* attributeName,
				const core::matrix4& v)
		{
			IAttribute* att = getAttributeByName(attributeName);
			if (att)
				att->setMatrix(v);
			else
				Attributes.push_back(new CMatrixAttribute(attributeName, v));
		}

		//! Sets an attribute as matrix
		void CAttributes::setAttribute(s32 index, const core::matrix4& v)
		{
			Attributes[index]->setMatrix(v);
		}

		//! Gets an attribute as a matrix4
		core::matrix4 CAttributes::getAttributeAsMatrix(const c8* attributeName)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				return att->getMatrix();
			else
				return core::matrix4();

		}

		//! Gets an attribute as matrix
		core::matrix4 CAttributes::getAttributeAsMatrix(s32 index)
		{
			return Attributes[index]->getMatrix();
		}

		/*

		 quaternion attribute

		 */

		//! Adds an attribute as quaternion
		void CAttributes::addQuaternion(const c8* attributeName,
				core::quaternion v)
		{
			Attributes.push_back(new CQuaternionAttribute(attributeName, v));
		}

		//! Sets an attribute as quaternion
		void CAttributes::setAttribute(const c8* attributeName,
				core::quaternion v)
		{
			IAttribute* att = getAttributeByName(attributeName);
			if (att)
				att->setQuaternion(v);
			else

				Attributes.push_back(
						new CQuaternionAttribute(attributeName, v));
		}

		//! Sets an attribute as quaternion
		void CAttributes::setAttribute(s32 index, core::quaternion v)
		{
			Attributes[index]->setQuaternion(v);
		}

		//! Gets an attribute as a quaternion
		core::quaternion CAttributes::getAttributeAsQuaternion(
				const c8* attributeName)
		{
			core::quaternion ret(0, 1, 0, 0);

			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				ret = att->getQuaternion();

			return ret;
		}

		//! Gets an attribute as quaternion
		core::quaternion CAttributes::getAttributeAsQuaternion(s32 index)
		{
			return Attributes[index]->getQuaternion();
		}

		/*

		 3d bounding box

		 */

		//! Adds an attribute as axis aligned bounding box
		void CAttributes::addBox3d(const c8* attributeName, core::aabbox3df v)
		{
			Attributes.push_back(new CBBoxAttribute(attributeName, v));
		}

		//! Sets an attribute as axis aligned bounding box
		void CAttributes::setAttribute(const c8* attributeName,
				core::aabbox3df v)
		{
			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				att->setBBox(v);
			else
				Attributes.push_back(new CBBoxAttribute(attributeName, v));
		}

		//! Sets an attribute as axis aligned bounding box
		void CAttributes::setAttribute(s32 index, core::aabbox3df v)
		{
			Attributes[index]->setBBox(v);
		}

		//! Gets an attribute as a axis aligned bounding box
		core::aabbox3df CAttributes::getAttributeAsBox3d(
				const c8* attributeName)
		{
			core::aabbox3df ret(0, 0, 0, 0, 0, 0);

			IAttribute* att = getAttributeByName(attributeName);

			if (att)
				ret = att->getBBox();

			return ret;
		}

		//! Gets an attribute as axis aligned bounding box
		core::aabbox3df CAttributes::getAttributeAsBox3d(s32 index)
		{
			return Attributes[index]->getBBox();
		}
//

//
////! Adds an attribute as 3d plane
//void CAttributes::addPlane3d(const c8* attributeName, core::plane3df v)
//{
//	Attributes.push_back(new CPlaneAttribute(attributeName, v));
//}
//
////! Sets an attribute as 3d plane
//void CAttributes::setAttribute(const c8* attributeName, core::plane3df v)
//{
//	IAttribute* att = getAttributeByName(attributeName);
//	if (att)
//		att->setPlane(v);
//	else
//	{
//		Attributes.push_back(new CPlaneAttribute(attributeName, v));
//	}
//}
//
////! Gets an attribute as a 3d plane
//core::plane3df CAttributes::getAttributeAsPlane3d(const c8* attributeName)
//{
//	core::plane3df ret(0,0,0, 0,1,0);
//
//	IAttribute* att = getAttributeByName(attributeName);
//	if (att)
//		ret = att->getPlane();
//
//	return ret;
//}
//
////! Gets an attribute as 3d plane
//core::plane3df CAttributes::getAttributeAsPlane3d(s32 index)
//{
//	core::plane3df ret(0,0,0, 0,1,0);
//
//	if (index >= 0 && index < (s32)Attributes.size())
//		ret = Attributes[index]->getPlane();
//
//	return ret;
//}
//
////! Sets an attribute as 3d plane
//void CAttributes::setAttribute(s32 index, core::plane3df v)
//{
//	if (index >= 0 && index < (s32)Attributes.size() )
//		Attributes[index]->setPlane(v);
//}
//
////! Adds an attribute as 3d triangle
//void CAttributes::addTriangle3d(const c8* attributeName, core::triangle3df v)
//{
//	Attributes.push_back(new CTriangleAttribute(attributeName, v));
//}
//
////! Sets an attribute as 3d triangle
//void CAttributes::setAttribute(const c8* attributeName, core::triangle3df v)
//{
//	IAttribute* att = getAttributeByName(attributeName);
//	if (att)
//		att->setTriangle(v);
//	else
//	{
//		Attributes.push_back(new CTriangleAttribute(attributeName, v));
//	}
//}
//
////! Gets an attribute as a 3d triangle
//core::triangle3df CAttributes::getAttributeAsTriangle3d(const c8* attributeName)
//{
//	core::triangle3df ret;
//	ret.pointA = ret.pointB = ret.pointC = core::vector3df(0,0,0);
//
//	IAttribute* att = getAttributeByName(attributeName);
//	if (att)
//		ret = att->getTriangle();
//
//	return ret;
//}
//
////! Gets an attribute as 3d triangle
//core::triangle3df CAttributes::getAttributeAsTriangle3d(s32 index)
//{
//	core::triangle3df ret;
//	ret.pointA = ret.pointB = ret.pointC = core::vector3df(0,0,0);
//
//	if (index >= 0 && index < (s32)Attributes.size())
//		ret = Attributes[index]->getTriangle();
//
//	return ret;
//}
//
////! Sets an attribute as 3d triangle
//void CAttributes::setAttribute(s32 index, core::triangle3df v)
//{
//	if (index >= 0 && index < (s32)Attributes.size() )
//		Attributes[index]->setTriangle(v);
//}
//
////! Adds an attribute as a 2d line
//void CAttributes::addLine2d(const c8* attributeName, core::line2df v)
//{
//	Attributes.push_back(new CLine2dAttribute(attributeName, v));
//}
//
////! Sets an attribute as a 2d line
//void CAttributes::setAttribute(const c8* attributeName, core::line2df v)
//{
//	IAttribute* att = getAttributeByName(attributeName);
//	if (att)
//		att->setLine2d(v);
//	else
//	{
//		Attributes.push_back(new CLine2dAttribute(attributeName, v));
//	}
//}
//
////! Gets an attribute as a 2d line
//core::line2df CAttributes::getAttributeAsLine2d(const c8* attributeName)
//{
//	core::line2df ret(0,0, 0,0);
//
//	IAttribute* att = getAttributeByName(attributeName);
//	if (att)
//		ret = att->getLine2d();
//
//	return ret;
//}
//
////! Gets an attribute as a 2d line
//core::line2df CAttributes::getAttributeAsLine2d(s32 index)
//{
//	core::line2df ret(0,0, 0,0);
//
//	if (index >= 0 && index < (s32)Attributes.size())
//		ret = Attributes[index]->getLine2d();
//
//	return ret;
//}
//
////! Sets an attribute as a 2d line
//void CAttributes::setAttribute(s32 index, core::line2df v)
//{
//	if (index >= 0 && index < (s32)Attributes.size() )
//		Attributes[index]->setLine2d(v);
//}
//
////! Adds an attribute as a 3d line
//void CAttributes::addLine3d(const c8* attributeName, core::line3df v)
//{
//	Attributes.push_back(new CLine3dAttribute(attributeName, v));
//}
//
////! Sets an attribute as a 3d line
//void CAttributes::setAttribute(const c8* attributeName, core::line3df v)
//{
//	IAttribute* att = getAttributeByName(attributeName);
//	if (att)
//		att->setLine3d(v);
//	else
//	{
//		Attributes.push_back(new CLine3dAttribute(attributeName, v));
//	}
//}
//
////! Gets an attribute as a 3d line
//core::line3df CAttributes::getAttributeAsLine3d(const c8* attributeName)
//{
//	core::line3df ret(0,0,0, 0,0,0);
//
//	IAttribute* att = getAttributeByName(attributeName);
//	if (att)
//		ret = att->getLine3d();
//
//	return ret;
//}
//
////! Gets an attribute as a 3d line
//core::line3df CAttributes::getAttributeAsLine3d(s32 index)
//{
//	core::line3df ret(0,0,0, 0,0,0);
//
//	if (index >= 0 && index < (s32)Attributes.size())
//		ret = Attributes[index]->getLine3d();
//
//	return ret;
//}
//
////! Sets an attribute as a 3d line
//void CAttributes::setAttribute(s32 index, core::line3df v)
//{
//	if (index >= 0 && index < (s32)Attributes.size() )
//		Attributes[index]->setLine3d(v);
//
//}
//
//
////! Adds an attribute as user pointner
//void CAttributes::addUserPointer(const c8* attributeName, void* userPointer)
//{
//	Attributes.push_back(new CUserPointerAttribute(attributeName, userPointer));
//}
//
////! Sets an attribute as user pointer
//void CAttributes::setAttribute(const c8* attributeName, void* userPointer)
//{
//	IAttribute* att = getAttributeByName(attributeName);
//	if (att)
//		att->setUserPointer(userPointer);
//	else
//	{
//		Attributes.push_back(new CUserPointerAttribute(attributeName, userPointer));
//	}
//}
//
////! Gets an attribute as user pointer
////! \param attributeName: Name of the attribute to get.
//void* CAttributes::getAttributeAsUserPointer(const c8* attributeName)
//{
//	void* value = 0;
//
//	IAttribute* att = getAttributeByName(attributeName);
//	if (att)
//		value = att->getUserPointer();
//
//	return value;
//}
//
////! Gets an attribute as user pointer
////! \param index: Index value, must be between 0 and getAttributeCount()-1.
//void* CAttributes::getAttributeAsUserPointer(s32 index)
//{
//	void* value = 0;
//
//	if (index >= 0 && index < (s32)Attributes.size())
//        value = Attributes[index]->getUserPointer();
//
//	return value;
//}
//
////! Sets an attribute as user pointer
//void CAttributes::setAttribute(s32 index, void* userPointer)
//{
//	if (index >= 0 && index < (s32)Attributes.size() )
//		Attributes[index]->setUserPointer(userPointer);
//}
//
//
//
//
//
////! Write these attributes into a xml file
//bool CAttributes::write(io::IXMLWriter* writer, bool writeXMLHeader,
//						const wchar_t* nonDefaultElementName)
//{
//	if (!writer)
//		return false;
//
//	if (writeXMLHeader)
//		writer->writeXMLHeader();
//
//	core::stringw elementName = "attributes";
//	if (nonDefaultElementName)
//		elementName = nonDefaultElementName;
//
//	writer->writeElement(elementName.c_str(), false);
//	writer->writeLineBreak();
//
//	s32 i=0;
//	for (; i<(s32)Attributes.size(); ++i)
//	{
//		if ( Attributes[i]->getType() == EAT_STRINGWARRAY )
//		{
//			core::array<core::stringw> arraynames, arrayvalues;
//			core::array<core::stringw> arrayinput = Attributes[i]->getArray();
//
//			// build arrays
//
//			// name
//			arraynames.push_back(core::stringw("name"));
//			arrayvalues.push_back(core::stringw(Attributes[i]->Name.c_str()) );
//
//			// count
//			arraynames.push_back(core::stringw("count"));
//			arrayvalues.push_back(core::stringw((s32)arrayinput.size()));
//
//			// array...
//			u32 n=0;
//			const core::stringw tmpName(L"value");
//			for (; n < arrayinput.size(); ++n)
//			{
//				arraynames.push_back((tmpName+core::stringw(n)).c_str());
//				arrayvalues.push_back(arrayinput[n]);
//			}
//
//			// write them
//			writer->writeElement( Attributes[i]->getTypeString(), true, arraynames, arrayvalues);
//		}
//		else
//		{
//			writer->writeElement(
//				Attributes[i]->getTypeString(), true,
//				L"name", core::stringw(Attributes[i]->Name.c_str()).c_str(),
//				"value", Attributes[i]->getStringW().c_str() );
//		}
//
//		writer->writeLineBreak();
//	}
//
//	writer->writeClosingTag(elementName.c_str());
//	writer->writeLineBreak();
//
//	return true;
//}
		//! IAttributes creator. Internal function. Please do not use.
		IAttributes* createAttributes()
		{
			return new CAttributes();
		}
	}		// end namespace io
} // end namespace irrgame

