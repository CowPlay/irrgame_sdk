/*
 * SAttributeReadWriteOptions.h
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#ifndef SATTRIBUTEREADWRITEOPTIONS_H_
#define SATTRIBUTEREADWRITEOPTIONS_H_

#include "core/base/baseTypes.h"

namespace irrgame
{
	namespace io
	{
		//! struct holding data describing options
		struct SAttributeReadWriteOptions
		{
			public:
				//! Default constructor
				SAttributeReadWriteOptions() :
						Flags(0), Filename(0)
				{
				}

			public:
				//! Combination of E_ATTRIBUTE_READ_WRITE_FLAGS or other, custom ones
				s32 Flags;

				//! Optional filename
				const c8* Filename;
		};
	}  // namespace io
}  // namespace irrgame

#endif /* SATTRIBUTEREADWRITEOPTIONS_H_ */
