/*
 * SChunkData.h
 *
 *  Created on: Nov 12, 2012
 *      Author: gregorytkach
 */

#ifndef SCHUNKDATA_H_
#define SCHUNKDATA_H_

#include "SChunkHeader.h"

namespace irrgame
{

	namespace scene
	{
		struct SChunkData
		{
			public:
				SChunkData();

			public:
				SChunkHeader header;
				s32 read;
		};

		inline SChunkData::SChunkData() :
				read(0)
		{
		}

	} // namespace scene

}  // namespace irrgame

#endif /* SCHUNKDATA_H_ */
