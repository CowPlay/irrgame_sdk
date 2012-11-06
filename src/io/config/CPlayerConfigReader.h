/*
 * CConfigReader.h
 *
 *  Created on: Aug 7, 2012
 *      Author: gregorytkach
 */

#ifndef CCONFIGREADER_H_
#define CCONFIGREADER_H_

#include "io/config/IPlayerConfigReader.h"
#include "io/SPath.h"

namespace irrgame
{
	namespace io
	{
		class CPlayerConfigReader: public IPlayerConfigReader
		{
			public:

				//! Default constructor
				CPlayerConfigReader();

				//! Destructor
				~CPlayerConfigReader();

				virtual void read(const c8* file);

				//! Gets enty which contains data from config
				virtual SPlayerConfigEntry* getEntry();

			protected:
				//! Parse <application/>
				virtual void parseApplication(IXMLReader* xml);

			private:
				IXMLReader* XMLReader;
				SPlayerConfigEntry* Entry;
		};
	}
}

#endif /* CCONFIGREADER_H_ */
