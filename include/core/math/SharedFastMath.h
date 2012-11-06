/*
 * SharedFastMath.h
 *
 *  Created on: Nov 5, 2012
 *      Author: gregorytkach
 */

#ifndef SHAREDFASTMATH_H_
#define SHAREDFASTMATH_H_

#include "core/math/SharedMath.h"

namespace irrgame
{
	namespace core
	{

//#define F32_AS_S32(f)		(*((s32 *) &(f)))
//#define F32_AS_U32(f)		(*((u32 *) &(f)))
//#define F32_AS_U32_POINTER(f)	( ((u32 *) &(f)))
//
//#define F32_VALUE_0		0x00000000
//#define F32_VALUE_1		0x3f800000
//#define F32_SIGN_BIT		0x80000000U
//#define F32_EXPON_MANTISSA	0x7FFFFFFFU

//! Absolute integer representation of a floating-point value
//#define AIR(x)				(IR(x)&0x7fffffff)

//! integer representation of 1.0
//#define IEEE_1_0			0x3f800000
		//! integer representation of 255.0
//#define IEEE_255_0			0x437f0000

		class SharedFastMath
		{

			public:
				/*
				 float IEEE-754 bit represenation

				 0      0x00000000
				 1.0    0x3f800000
				 0.5    0x3f000000
				 3      0x40400000
				 +inf   0x7f800000
				 -inf   0xff800000
				 +NaN   0x7fc00000 or 0x7ff00000
				 in general: number = (sign ? -1:1) * 2^(exponent) * 1.(mantissa bits)
				 */
				static const f32 F32Value0;
				static const f32 F32Value1;

			public:
				//! Singleton realization
				static SharedFastMath& getInstance();

			private:
				//! Default constructor. Should use only one time.
				SharedFastMath();

				//! Destructor. Should use only one time.
				virtual ~SharedFastMath();

				//! Copy constructor. Do not implement.
				SharedFastMath(const SharedFastMath& root);

				//! Override equal operator. Do not implement.
				const SharedFastMath& operator=(SharedFastMath&);

				/*
				 * Methods
				 */

			public:

				bool F32_LOWER_0(f32 n) const;
				bool F32_LOWER_EQUAL_0(f32 n) const;
				bool F32_GREATER_0(f32 n) const;
				bool F32_GREATER_EQUAL_0(f32 n) const;
				bool F32_EQUAL_1(f32 n) const;
				bool F32_EQUAL_0(f32 n) const;
				bool F32_A_GREATER_B(f32 a, f32 b) const;

				// calculate: 1 / x
				f32 invert(const f32 f) const;

				// calculate: 1 / sqrtf ( x )
				f32 invertSqrt(const f32 f) const;

				// calculate: 1 / sqrtf( x )
				s32 invertSqrt(const s32 x) const;

				// calculate: 1 / x, low precision allowed
				f32 invertApproximate(const f32 f) const;

				s32 floor32(f32 x) const;

				s32 ceil32(f32 x) const;

				s32 round32(f32 x) const;
		};

	}  // namespace math
}  // namespace irrgame

#endif /* SHAREDFASTMATH_H_ */
