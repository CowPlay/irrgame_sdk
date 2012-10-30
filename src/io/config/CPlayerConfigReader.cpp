/*
 * CConfigReader.cpp
 *
 *  Created on: Aug 7, 2012
 *      Author: gregorytkach
 */

#include "CPlayerConfigReader.h"
#include "io/serialize/IAttributes.h"

namespace irrgame
{
	namespace io
	{

		//! Default constructor
		CPlayerConfigReader::CPlayerConfigReader() :
				XMLReader(0), Entry(0)
		{

		}

		//! Destructor
		CPlayerConfigReader::~CPlayerConfigReader()
		{
		}

		void CPlayerConfigReader::read(const c8* file)
		{
			XMLReader = IFileSystem::getInstance().createXMLReader(file);

			Entry = new SPlayerConfigEntry();

			bool configRead = false;

			do
			{
				switch (XMLReader->getNodeType())
				{
					case EXNT_ELEMENT:
					{
						core::stringc nodeName = XMLReader->getNodeName();

						if (nodeName == XML_TAG_APPLICATION)
							parseApplication(XMLReader);

						break;
					}
					case EXNT_ELEMENT_END:
					{
						core::stringc nodeName = XMLReader->getNodeName();

						if (nodeName == XML_TAG_CONFIG)
						{
							configRead = true;
							XMLReader->read();
						}

						break;
					}
					case EXNT_NONE:
					case EXNT_TEXT:
					case EXNT_COMMENT:
					case EXNT_CDATA:
					case EXNT_UNKNOWN:
					default:
						break;
				}
			} while (!configRead && XMLReader->read());

			if (XMLReader)
				XMLReader->drop();
		}

		//! Parse <application/>
		void CPlayerConfigReader::parseApplication(IXMLReader* xml)
		{
			bool appRead = false;

			do
			{
				switch (xml->getNodeType())
				{
					case EXNT_ELEMENT:
					{
						core::stringc nodeName = xml->getNodeName();

						if (nodeName == XML_TAG_ATTRIBUTES)
						{
							io::IAttributes* attr =
									IFileSystem::getInstance().createEmptyAttributes();

							attr->read(xml, true);

							if (attr->existsAttribute(XML_ATTR_APP_FILE))
								Entry->AppFile = attr->getAttributeAsString(
										XML_ATTR_APP_FILE);

							if (attr->existsAttribute(XML_ATTR_APP_CREATOR))
								Entry->AppCreator = attr->getAttributeAsString(
										XML_ATTR_APP_CREATOR);

							attr->drop();
						}

						break;
					}
					case EXNT_ELEMENT_END:
					{
						core::stringc nodeName = xml->getNodeName();

						if (nodeName == XML_TAG_APPLICATION)
						{
							appRead = true;
							xml->read();
						}

						break;
					}
					case EXNT_NONE:
					case EXNT_TEXT:
					case EXNT_COMMENT:
					case EXNT_CDATA:
					case EXNT_UNKNOWN:
					default:
						break;
				}
			} while (!appRead && xml->read());

		}

		//! Gets enty which contains data from config
		SPlayerConfigEntry* CPlayerConfigReader::getEntry()
		{
			return Entry;
		}

		//! Internal funtcion. Please do not use.
		IPlayerConfigReader* createPlayerConfigReader()
		{
			return new CPlayerConfigReader();
		}

	}
}
