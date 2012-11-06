/*
 * SColorHSL.h
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#ifndef SCOLORHSL_H_
#define SCOLORHSL_H_

#include "compileConfig.h"

namespace irrgame
{
	namespace video
	{

		struct SColor;

		//! Class representing a color in HSV format
		/** The color values for hue, saturation, value
		 are stored in a 32 bit floating point variable.
		 */
		class SColorHSL
		{
			public:
				//! Default constructor
				SColorHSL(f32 h = 0.f, f32 s = 0.f, f32 l = 0.f);

				void fromRGB(const SColor &color);
				void toRGB(SColor &color) const;

			private:
				inline u32 toRGB1(f32 rm1, f32 rm2, f32 rh) const;

			public:

				f32 Hue;
				f32 Saturation;
				f32 Luminance;

		};

	}  // namespace video
}  // namespace irrgame

#endif /* SCOLORHSL_H_ */
