// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_MATH_H_INCLUDED__
#define __IRR_MATH_H_INCLUDED__

#include "compileConfig.h"

#include <math.h>
#include <float.h>
#include <stdlib.h> // for abs() etc.
#include <limits.h> // For INT_MAX / UINT_MAX
namespace irrgame
{
	namespace core
	{

		class SharedMath
		{
				/*
				 * Static constants
				 */
			public:
				static const f32 MaxFloat;

				//! Rounding error constant often used when comparing f32 values.
				static const s32 RoundErrS32;
				static const f32 RoundErrF32;

				//! Constant for PI.
				static const f32 Pi;

				//! Constant for iverted of PI.
				static const f32 PiInverted;

				//! Constant for half of PI.
				static const f32 PiHalf;

				//! 32bit Constant for converting from degrees to radians
				static const f32 DegToRad;

				//! 32bit constant for converting from radians to degrees (formally known as GRAD_PI)
				static const f32 RadToDeg;

			public:
				//! Singleton realization
				static SharedMath& getInstance();

			private:
				//! Default constructor. Should use only one time.
				SharedMath();

				//! Destructor. Should use only one time.
				virtual ~SharedMath();

				//! Copy constructor. Do not implement.
				SharedMath(const SharedMath& root);

				//! Override equal operator. Do not implement.
				const SharedMath& operator=(SharedMath&);

				/*
				 * Methods
				 */
			public:

				//! Utility function to convert a radian value to degrees
				/** Provided as it can be clearer to write radToDeg(X) than RADTODEG * X
				 \param radians	The radians value to convert to degrees.
				 */
				f32 radToDeg(f32 radians) const;

				//! Utility function to convert a degrees value to radians
				/** Provided as it can be clearer to write degToRad(X) than DEGTORAD * X
				 \param degrees	The degrees value to convert to radians.
				 */
				f32 degToRad(f32 degrees) const;

				//! returns if a equals b, taking possible rounding errors into account
				bool equals(const f32 a, const f32 b, const f32 tolerance =
						RoundErrF32) const;

				//! returns if a equals b, taking an explicit rounding tolerance into account
				bool equals(const s32 a, const s32 b, const s32 tolerance =
						RoundErrS32) const;

				//! returns if a equals b, taking an explicit rounding tolerance into account
				bool equals(const u32 a, const u32 b, const s32 tolerance =
						RoundErrS32) const;

				//! returns if a equals zero, taking rounding errors into account
				bool iszero(const f32 a,
						const f32 tolerance = RoundErrF32) const;

				//! returns if a equals not zero, taking rounding errors into account
				inline bool isnotzero(const f32 a, const f32 tolerance =
						RoundErrF32) const;

				//! returns if a equals zero, taking rounding errors into account
				bool iszero(const s32 a, const s32 tolerance = 0) const;

				//! returns if a equals zero, taking rounding errors into account
				bool iszero(const u32 a, const u32 tolerance = 0) const;

				s32 s32Min(s32 a, s32 b) const;

				s32 s32Max(s32 a, s32 b) const;

				s32 s32Clamp(s32 value, s32 low, s32 high) const;

				//! conditional set based on mask and arithmetic shift
				u32 ifCONDThanAelseB(const s32 condition, const u32 a,
						const u32 b) const;

				//! conditional set based on mask and arithmetic shift
				u16 ifCONDThanAelseB(const s16 condition, const u16 a,
						const u16 b) const;

				//! conditional set based on mask and arithmetic shift
				u32 ifCONDThanAelseZERO(const s32 condition, const u32 a) const;

				//! if (condition) state |= m; else state &= ~m;
				void setbitCond(u32 &state, s32 condition, u32 mask) const;

				f32 round(f32 x) const;

				// calculate: sqrt ( x )
				f32 squareroot(const f32 f) const;

				// calculate: sqrt ( x )
				s32 squareroot(const s32 f) const;

				f32 f32Max(const f32 a, const f32 b, const f32 c) const;

				f32 f32Min(const f32 a, const f32 b, const f32 c) const;

				f32 fract(f32 x) const;

				/*
				 * Template methods
				 */

				//! returns minimum of two values. Own implementation to get rid of the STL (VS6 problems)
				template<class T>
				const T& min(const T& a, const T& b) const;

				//! returns minimum of three values. Own implementation to get rid of the STL (VS6 problems)
				template<class T>
				const T& min(const T& a, const T& b, const T& c) const;

				//! returns maximum of two values. Own implementation to get rid of the STL (VS6 problems)
				template<class T>
				const T& max(const T& a, const T& b) const;

				//! returns maximum of three values. Own implementation to get rid of the STL (VS6 problems)
				template<class T>
				const T& max(const T& a, const T& b, const T& c) const;

				//! returns abs of two values. Own implementation to get rid of STL (VS6 problems)
				template<class T>
				T abs(const T& a) const;

				//! returns linear interpolation of a and b with ratio t
				//! \return: a if t==0, b if t==1, and the linear interpolation else
				template<class T>
				T lerp(const T& a, const T& b, const f32 t) const;

				//! clamps a value between low and high
				template<class T>
				const T clamp(const T& value, const T& low,
						const T& high) const;

				//! swaps the content of the passed parameters
				template<class T>
				void swap(T& a, T& b) const;

		};

		//! returns minimum of two values. Own implementation to get rid of the STL (VS6 problems)
		template<class T>
		inline const T& SharedMath::min(const T& a, const T& b) const
		{
			return a < b ? a : b;
		}

		//! returns minimum of three values. Own implementation to get rid of the STL (VS6 problems)
		template<class T>
		inline const T& SharedMath::min(const T& a, const T& b,
				const T& c) const
		{
			return a < b ? min(a, c) : min(b, c);
		}

		//! returns maximum of two values. Own implementation to get rid of the STL (VS6 problems)
		template<class T>
		inline const T& SharedMath::max(const T& a, const T& b) const
		{
			return a < b ? b : a;
		}

		//! returns maximum of three values. Own implementation to get rid of the STL (VS6 problems)
		template<class T>
		inline const T& SharedMath::max(const T& a, const T& b,
				const T& c) const
		{
			return a < b ? max(b, c) : max(a, c);
		}

		//! returns abs of two values. Own implementation to get rid of STL (VS6 problems)
		template<class T>
		inline T SharedMath::abs(const T& a) const
		{
			return a < (T) 0 ? -a : a;
		}

		//! returns linear interpolation of a and b with ratio t
		//! \return: a if t==0, b if t==1, and the linear interpolation else
		template<class T>
		inline T SharedMath::lerp(const T& a, const T& b, const f32 t) const
		{
			return (T) (a * (1.f - t)) + (b * t);
		}

		//! clamps a value between low and high
		template<class T>
		inline const T SharedMath::clamp(const T& value, const T& low,
				const T& high) const
		{
			return min(max(value, low), high);
		}

		//! swaps the content of the passed parameters
		template<class T>
		inline void SharedMath::swap(T& a, T& b) const
		{
			T c(a);
			a = b;
			b = c;
		}
	} // end namespace core
} // end namespace irrgame

#endif

