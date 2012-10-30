/*
 * SFog.h
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#ifndef SFOG_H_
#define SFOG_H_

#include "EFogType.h"
#include "video/color/SColor.h"

namespace irrgame
{

	namespace video
	{

		struct SFog
		{
			public:
				SColor Color;
				EFogType Type;
				f32 Start;
				f32 End;
				f32 Density;
				bool PixelFog;
				bool RangeFog;
		};

	}
// namespace video

}// namespace irrgame

#endif /* SFOG_H_ */
