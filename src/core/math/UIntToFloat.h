/*
 * UIntToFloat.h
 *
 *  Created on: Nov 5, 2012
 *      Author: gregorytkach
 */

#ifndef UINTTOFLOAT_H_
#define UINTTOFLOAT_H_

#include "compileConfig.h"

namespace irrgame
{
	namespace core
	{

		typedef union
		{
			public:
				u32 u;
				s32 s;
				f32 f;
		} UIntToFloat;

	}  // namespace math
}  // namespace irrgame

#endif /* UINTTOFLOAT_H_ */
