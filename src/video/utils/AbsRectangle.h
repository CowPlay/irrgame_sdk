/*
 * AbsRectangle.h
 *
 *  Created on: Nov 1, 2012
 *      Author: gregorytkach
 */

#ifndef ABSRECTANGLE_H_
#define ABSRECTANGLE_H_

#include "compileConfig.h"

namespace irrgame
{
	namespace video
	{
		// some 2D Defines
		struct AbsRectangle
		{
			public:
				s32 x0;
				s32 y0;
				s32 x1;
				s32 y1;
		};
	}  // namespace video
}  // namespace irrgame

#endif /* ABSRECTANGLE_H_ */
