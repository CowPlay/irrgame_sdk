/*
 * SHaredFastMath.cpp
 *
 *  Created on: Nov 5, 2012
 *      Author: gregorytkach
 */

#include "compileConfig.h"

#include "core/math/SharedFastMath.h"

namespace irrgame
{
	namespace core
	{

		//! Singleton realization
		SharedFastMath& SharedFastMath::getInstance()
		{
			static SharedFastMath instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		SharedFastMath::SharedFastMath()
		{
		}

		//! Destructor. Should use only one time.
		SharedFastMath::~SharedFastMath()
		{
		}

		/*
		 * Methods
		 */

#ifdef IRR_FAST_MATH

		const f32 SharedFastMath::F32Value0 = 0x00000000;
		const f32 SharedFastMath::F32Value1 = 0x3f800000;

		bool SharedFastMath::F32_LOWER_0(f32 f)
		{
			return ((*((u32 *) &(f))) > 0x80000000U);
		}

		bool SharedFastMath::F32_LOWER_EQUAL_0(f32 f)
		{
			return ((*((s32 *) &(f))) <= 0x00000000);
		}

		bool SharedFastMath::F32_GREATER_0(f32 f)
		{
			return ((*((s32 *) &(f))) > 0x00000000);
		}

		bool SharedFastMath::F32_GREATER_EQUAL_0(f32 f)
		{
			return ((*((u32 *) &(f))) <= 0x80000000U);
		}

		bool SharedFastMath::F32_EQUAL_1(f32 f)
		{
			return ((*((u32 *) &(f))) == 0x3f800000);
		}

		bool SharedFastMath::F32_EQUAL_0(f32 f)
		{
			return (((*((u32 *) &(f))) & 0x7FFFFFFFU) == 0x00000000);
		}

		// only same sign
		bool F32_A_GREATER_B(f32 a, f32 b)
		{
			return ((*((s32 *) &(a))) > (*((s32 *) &(b))));
		}

		// calculate: 1 / sqrtf ( x )
		f32 SharedFastMath::invertSqrt(const f32 f)
		{
#ifdef _MSC_VER
// SSE reciprocal square root estimate, accurate to 12 significant
// bits of the mantissa
			f32 recsqrt;
			__asm rsqrtss xmm0, f// xmm0 = rsqrtss(f)
			__asm movss recsqrt, xmm0// return xmm0
			return recsqrt;

			/*
			 // comes from Nvidia
			 u32 tmp = (u32(IEEE_1_0 << 1) + IEEE_1_0 - *(u32*)&x) >> 1;
			 f32 y = *(f32*)&tmp;
			 return y * (1.47f - 0.47f * x * y * y);
			 */
#else
			return 1.f / sqrtf(f);
#endif
		}

		// calculate: 1 / x
		f32 SharedFastMath::invert(const f32 f)
		{
#ifdef _MSC_VER

// SSE Newton-Raphson reciprocal estimate, accurate to 23 significant
// bi ts of the mantissa
// One Newtown-Raphson Iteration:
// f(i+1) = 2 * rcpss(f) - f * rcpss(f) * rcpss(f)
			f32 rec;
			__asm rcpss xmm0, f// xmm0 = rcpss(f)
			__asm movss xmm1, f// xmm1 = f
			__asm mulss xmm1, xmm0// xmm1 = f * rcpss(f)
			__asm mulss xmm1, xmm0// xmm2 = f * rcpss(f) * rcpss(f)
			__asm addss xmm0, xmm0// xmm0 = 2 * rcpss(f)
			__asm subss xmm0, xmm1// xmm0 = 2 * rcpss(f)
//        - f * rcpss(f) * rcpss(f)
			__asm movss rec, xmm0// return xmm0
			return rec;

//! i do not divide through 0.. (fpu expection)
// instead set f to a high value to get a return value near zero..
// -1000000000000.f.. is use minus to stay negative..
// must test's here (plane.normal dot anything ) checks on <= 0.f
//u32 x = (-(AIR(f) != 0 ) >> 31 ) & ( IR(f) ^ 0xd368d4a5 ) ^ 0xd368d4a5;
//return 1.f / FR ( x );

#else // no fast math
			return 1.f / f;
#endif
		}

		// calculate: 1 / x, low precision allowed
		f32 SharedFastMath::invertApproximate(const f32 f)
		{
#ifdef _MSC_VER

// SSE Newton-Raphson reciprocal estimate, accurate to 23 significant
// bi ts of the mantissa
// One Newtown-Raphson Iteration:
// f(i+1) = 2 * rcpss(f) - f * rcpss(f) * rcpss(f)
			f32 rec;
			__asm rcpss xmm0, f// xmm0 = rcpss(f)
			__asm movss xmm1, f// xmm1 = f
			__asm mulss xmm1, xmm0// xmm1 = f * rcpss(f)
			__asm mulss xmm1, xmm0// xmm2 = f * rcpss(f) * rcpss(f)
			__asm addss xmm0, xmm0// xmm0 = 2 * rcpss(f)
			__asm subss xmm0, xmm1// xmm0 = 2 * rcpss(f)
//        - f * rcpss(f) * rcpss(f)
			__asm movss rec, xmm0// return xmm0
			return rec;

			/*
			 // SSE reciprocal estimate, accurate to 12 significant bits of
			 f32 rec;
			 __asm rcpss xmm0, f             // xmm0 = rcpss(f)
			 __asm movss rec , xmm0          // return xmm0
			 return rec;
			 */
			/*
			 register u32 x = 0x7F000000 - IR ( p );
			 const f32 r = FR ( x );
			 return r * (2.0f - p * r);
			 */
#else // no fast math
			return 1.f / f;
#endif
		}

		s32 SharedFastMath::floor32(f32 x)
		{
			const f32 h = 0.5f;

			s32 t;

#ifdef _MSC_VER
			__asm
			{
				fld x
				fsub h
				fistp t
			}
#elif defined(__GNUC__)
			__asm__ __volatile__ (
					"fsub %2 \n\t"
					"fistpl %0"
					: "=m" (t)
					: "t" (x), "f" (h)
					: "st"
			);
#else
#  warn IRRLICHT_FAST_MATH not supported.
			return (s32) floorf ( x );
#endif
			return t;
		}

		s32 SharedFastMath::ceil32(f32 x)
		{
			const f32 h = 0.5f;

			s32 t;

#if defined(_MSC_VER)
			__asm
			{
				fld x
				fadd h
				fistp t
			}
#elif defined(__GNUC__)
			__asm__ __volatile__ (
					"fadd %2 \n\t"
					"fistpl %0 \n\t"
					: "=m"(t)
					: "t"(x), "f"(h)
					: "st"
			);
#else
#  warn IRRLICHT_FAST_MATH not supported.
			return (s32) ceilf ( x );
#endif
			return t;
		}

		s32 SharedFastMath::round32(f32 x)
		{
			s32 t;

#if defined(_MSC_VER)
			__asm
			{
				fld x
				fistp t
			}
#elif defined(__GNUC__)
			__asm__ __volatile__ (
					"fistpl %0 \n\t"
					: "=m"(t)
					: "t"(x)
					: "st"
			);
#else
#  warn IRRLICHT_FAST_MATH not supported.
			return (s32) round(x);
#endif
			return t;
		}

#else //not IRR_FAST_MATH
		const f32 SharedFastMath::F32Value0 = 0.0f;
		const f32 SharedFastMath::F32Value1 = 1.0f;

		bool SharedFastMath::F32_LOWER_0(f32 n) const
		{
			return n < 0.0f;
		}

		bool SharedFastMath::F32_LOWER_EQUAL_0(f32 n) const
		{
			return n <= 0.0f;
		}

		bool SharedFastMath::F32_GREATER_0(f32 n) const
		{
			return n > 0.0f;
		}

		bool SharedFastMath::F32_GREATER_EQUAL_0(f32 n) const
		{
			return n >= 0.0f;
		}

		bool SharedFastMath::F32_EQUAL_1(f32 n) const
		{
			return n == 1.0f;
		}

		bool SharedFastMath::F32_EQUAL_0(f32 n) const
		{
			return n == 0.0f;
		}

		bool SharedFastMath::F32_A_GREATER_B(f32 a, f32 b) const
		{
			return a > b;
		}

		// calculate: 1 / x
		f32 SharedFastMath::invert(const f32 f) const
		{
			return 1.f / f;
		}

		// calculate: 1 / sqrtf ( x )
		f32 SharedFastMath::invertSqrt(const f32 f) const
		{
			return 1.f / sqrtf(f);
		}

		// calculate: 1 / sqrtf( x )
		s32 SharedFastMath::invertSqrt(const s32 x) const
		{
			return static_cast<s32>(SharedFastMath::getInstance().invertSqrt(
					static_cast<f32>(x)));
		}

		// calculate: 1 / x, low precision allowed
		f32 SharedFastMath::invertApproximate(const f32 f) const
		{
			return 1.f / f;
		}

		s32 SharedFastMath::floor32(f32 x) const
		{
			return (s32) floorf(x);
		}

		s32 SharedFastMath::ceil32(f32 x) const
		{
			return (s32) ceilf(x);
		}

		s32 SharedFastMath::round32(f32 x) const
		{
			return (s32) SharedMath::getInstance().round(x);
		}
#endif

	} // namespace core
} // namespace irrgame

