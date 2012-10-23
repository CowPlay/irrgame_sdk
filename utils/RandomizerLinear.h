/*
 * RandomizerLinear.h
 *
 *  Created on: Aug 1, 2012
 *      Author: gregorytkach
 */

#ifndef RANDOMIZERLINEAR_H_
#define RANDOMIZERLINEAR_H_

#include "core/base/irrgameTypes.h"

namespace irrgame
{
	namespace utils
	{
		// our Randomizer is not really os specific, so we
		// code one for all, which should work on every platform the same,
		// which is desireable.
		class RandomizerLinear
		{
			public:
				//! generates a pseudo random number
				static s32 rand();

				//! resets the randomizer
				static void reset();

			protected:
				static s32 seed;
		};
	}
}

#endif /* RANDOMIZERLINEAR_H_ */
