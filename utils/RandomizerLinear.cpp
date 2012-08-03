///*
// * IRandomizerLinear.cpp
// *
// *  Created on: Aug 1, 2012
// *      Author: gregorytkach
// */
//
//#include "./utils/RandomizerLinear.h"
//
//namespace irrgame
//{
//	namespace utils
//	{
//		s32 RandomizerLinear::seed = 0x0f0f0f0f;
//
//		//! generates a pseudo random number
//		s32 RandomizerLinear::rand()
//		{
//			const s32 m = 2147483399;	// a non-Mersenne prime
//			const s32 a = 40692;		// another spectral success story
//			const s32 q = m / a;
//			const s32 r = m % a;		// again less than q
//
//			seed = a * (seed % q) - r * (seed / q);
//			if (seed < 0)
//				seed += m;
//
//			return seed;
//		}
//
//		//! resets the randomizer
//		void RandomizerLinear::reset()
//		{
//			seed = 0x0f0f0f0f;
//		}
//
//	}
//}
//
