/*
 * SharedMath.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#include "core/math/SharedMath.h"
#include "core/math/SharedFastMath.h"

namespace irrgame
{
	namespace core
	{

		/*
		 * Constants
		 */
		const f32 SharedMath::MaxFloat = 3.402823466E+38F;

		//! Rounding error constant often used when comparing f32 values.
		const s32 SharedMath::RoundErrS32 = 0;
		const f32 SharedMath::RoundErrF32 = 0.000001f;

		//! Constant for PI.
		const f32 SharedMath::Pi = 3.14159265359f;

		//! Constant for reciprocal of PI.
		const f32 SharedMath::PiInverted = 1.0f / SharedMath::Pi;

		//! Constant for half of PI.
		const f32 SharedMath::PiHalf = SharedMath::Pi / 2.0f;

		//! 32bit Constant for converting from degrees to radians
		const f32 SharedMath::DegToRad = SharedMath::Pi / 180.0f;

		//! 32bit constant for converting from radians to degrees (formally known as GRAD_PI)
		const f32 SharedMath::RadToDeg = 180.0f / SharedMath::Pi;

		//! Singleton realization
		SharedMath& SharedMath::getInstance()
		{
			static SharedMath instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		SharedMath::SharedMath()
		{
		}

		//! Destructor. Should use only one time.
		SharedMath::~SharedMath()
		{
		}

		/*
		 * Methods
		 */

		//! Utility function to convert a radian value to degrees
		f32 SharedMath::radToDeg(f32 radians) const
		{
			return RadToDeg * radians;
		}

		//! Utility function to convert a degrees value to radians
		f32 SharedMath::degToRad(f32 degrees) const
		{
			return DegToRad * degrees;
		}

		//! returns if a equals b, taking possible rounding errors into account
		bool SharedMath::equals(const f32 a, const f32 b,
				const f32 tolerance) const
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}

		//! returns if a equals b, taking an explicit rounding tolerance into account
		bool SharedMath::equals(const s32 a, const s32 b,
				const s32 tolerance) const
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}

		//! returns if a equals b, taking an explicit rounding tolerance into account
		bool SharedMath::equals(const u32 a, const u32 b,
				const s32 tolerance) const
		{
			return (a + tolerance >= b) && (a - tolerance <= b);
		}

		//! returns if a equals zero, taking rounding errors into account
		bool SharedMath::iszero(const f32 a, const f32 tolerance) const
		{
			return fabsf(a) <= tolerance;
		}

		//! returns if a equals not zero, taking rounding errors into account
		bool SharedMath::isnotzero(const f32 a, const f32 tolerance) const
		{
			return fabsf(a) > tolerance;
		}

		//! returns if a equals zero, taking rounding errors into account
		bool SharedMath::iszero(const s32 a, const s32 tolerance) const
		{
			return (a & 0x7ffffff) <= tolerance;
		}

		//! returns if a equals zero, taking rounding errors into account
		bool SharedMath::iszero(const u32 a, const u32 tolerance) const
		{
			return a <= tolerance;
		}

		s32 SharedMath::s32Min(s32 a, s32 b) const
		{
			const s32 mask = (a - b) >> 31;
			return (a & mask) | (b & ~mask);
		}

		s32 SharedMath::s32Max(s32 a, s32 b) const
		{
			const s32 mask = (a - b) >> 31;
			return (b & mask) | (a & ~mask);
		}

		s32 SharedMath::s32Clamp(s32 value, s32 low, s32 high) const
		{
			return s32Min(s32Max(value, low), high);
		}

		//! conditional set based on mask and arithmetic shift
		u32 SharedMath::ifCONDThanAelseB(const s32 condition, const u32 a,
				const u32 b) const
		{
			return ((-condition >> 31) & (a ^ b)) ^ b;
		}

		//! conditional set based on mask and arithmetic shift
		u16 SharedMath::ifCONDThanAelseB(const s16 condition, const u16 a,
				const u16 b) const
		{
			return ((-condition >> 15) & (a ^ b)) ^ b;
		}

		//! conditional set based on mask and arithmetic shift
		u32 SharedMath::ifCONDThanAelseZERO(const s32 condition,
				const u32 a) const
		{
			return (-condition >> 31) & a;
		}

		//! if (condition) state |= m; else state &= ~m;
		void SharedMath::setbitCond(u32 &state, s32 condition, u32 mask) const
		{
			// 0, or any postive to mask
			//s32 conmask = -condition >> 31;
			state ^= ((-condition >> 31) ^ state) & mask;
		}

		f32 SharedMath::round(f32 x) const
		{
			return floorf(x + 0.5f);
		}

		// calculate: sqrt ( x )
		f32 SharedMath::squareroot(const f32 f) const
		{
			return sqrtf(f);
		}

		// calculate: sqrt ( x )
		s32 SharedMath::squareroot(const s32 f) const
		{
			return static_cast<s32>(squareroot(static_cast<f32>(f)));
		}

		f32 SharedMath::f32Max(const f32 a, const f32 b, const f32 c) const
		{
			return a > b ? (a > c ? a : c) : (b > c ? b : c);
		}

		f32 SharedMath::f32Min(const f32 a, const f32 b, const f32 c) const
		{
			return a < b ? (a < c ? a : c) : (b < c ? b : c);
		}

		f32 SharedMath::fract(f32 x) const
		{
			return x - floorf(x);
		}

	}  // namespace core
}  // namespace irrgame
