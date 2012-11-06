/*
 * SBlitJob.h
 *
 *  Created on: Nov 1, 2012
 *      Author: gregorytkach
 */

#ifndef SBLITJOB_H_
#define SBLITJOB_H_

#include "video/utils/AbsRectangle.h"

namespace irrgame
{
	namespace video
	{
		struct SBlitJob
		{
			public:
				AbsRectangle Dest;
				AbsRectangle Source;

				u32 argb;

				void * src;
				void * dst;

				s32 width;
				s32 height;

				u32 srcPitch;
				u32 dstPitch;

				u32 srcPixelMul;
				u32 dstPixelMul;
		};
	}  // namespace video
}  // namespace irrgame

#endif /* SBLITJOB_H_ */
