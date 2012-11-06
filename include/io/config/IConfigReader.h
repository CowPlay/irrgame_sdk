/*
 * IConfigReader.h
 *
 *  Created on: Aug 20, 2012
 *      Author: gregorytkach
 */

#ifndef ICONFIGREADER_H_
#define ICONFIGREADER_H_

#include "compileConfig.h"
#include "core/engine/IReferenceCounted.h"

namespace irrgame
{
	namespace io
	{
		//! Provide interface for read config from xml file
		class IConfigReader: public IReferenceCounted
		{
			public:
				//! Destructor
				virtual ~IConfigReader()
				{
				}

				virtual void read(const c8* file) = 0;
		};
	}
}

#endif /* ICONFIGREADER_H_ */
