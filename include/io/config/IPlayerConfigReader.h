/*
 * IPlayerConfigReader.h
 *
 *  Created on: Aug 20, 2012
 *      Author: gregorytkach
 */

#ifndef IPLAYERCONFIGREADER_H_
#define IPLAYERCONFIGREADER_H_

#include "io/config/IConfigReader.h"
#include "core/collections/stringc.h"
#include "core/shapes/dimension2d.h"

namespace irrgame
{
	class irrgamePlayer;

	namespace io
	{
		class IXMLReader;

		struct SPlayerConfigEntry
		{
			public:
				//! Block <application>
				core::stringc AppFile;
				core::stringc AppCreator;

				//! Block <video>
				dimension2du ScreenSize;
		};

		class IPlayerConfigReader: public IConfigReader
		{
			public:
				//! Destructor
				virtual ~IPlayerConfigReader()
				{
				}

				//! Gets enty which contains data from config
				virtual SPlayerConfigEntry* getEntry() = 0;

			protected:
				//! Parse <application/>
				virtual void parseApplication(IXMLReader* xml) = 0;
		};

		//! Internal funtcion. Please do not use.
		IPlayerConfigReader* createPlayerConfigReader();
	}
}

#endif /* IPLAYERCONFIGREADER_H_ */
