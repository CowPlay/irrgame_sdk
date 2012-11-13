/*
 * IByteSwap.h
 *
 *  Created on: Jul 31, 2012
 *      Author: gregorytkach
 */

#ifndef IBYTESWAP_H_
#define IBYTESWAP_H_

#include "compileConfig.h"

namespace irrgame
{
	namespace utils
	{
		//! Platform dependent
		class StaticByteSwap
		{
			public:
				static u16 byteswap(u16 num);

				static s16 byteswap(s16 num);

				static u32 byteswap(u32 num);

				static s32 byteswap(s32 num);

				static f32 byteswap(f32 num);

				// prevent accidental swapping of chars
				static u8 byteswap(u8 num);

				static c8 byteswap(c8 num);
		};

	}
}

#endif /* IBYTESWAP_H_ */
