/*
 * SColorf.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "video/color/SColorf.h"
#include "video/color/SColor.h"
#include "core/irrgamemath.h"

namespace irrgame
{
	namespace video
	{

		//! Default constructor for SColorf.
		SColorf::SColorf() :
				Red(0.0f), Green(0.0f), Blue(0.0f), Alpha(1.0f)
		{
		}

		//! Constructs a color from up to four color values: red, green, blue, and alpha.
		SColorf::SColorf(f32 r, f32 g, f32 b, f32 a) :
				Red(r), Green(g), Blue(b), Alpha(a)
		{
		}

		//! Constructs a color from 32 bit Color.
		SColorf::SColorf(SColor c)
		{
			const f32 inv = 1.0f / 255.0f;
			Red = c.getRed() * inv;
			Green = c.getGreen() * inv;
			Blue = c.getBlue() * inv;
			Alpha = c.getAlpha() * inv;
		}

		//! Converts this color to a SColor without floats.
		SColor SColorf::toSColor() const
		{
			return SColor((u32) (Alpha * 255.0f), (u32) (Red * 255.0f),
					(u32) (Green * 255.0f), (u32) (Blue * 255.0f));
		}

		//! Sets three color components to new values at once.
		void SColorf::set(f32 rr, f32 gg, f32 bb)
		{
			Red = rr;
			Green = gg;
			Blue = bb;
		}

		//! Sets all four color components to new values at once.
		void SColorf::set(f32 aa, f32 rr, f32 gg, f32 bb)
		{
			Alpha = aa;
			Red = rr;
			Green = gg;
			Blue = bb;
		}

		//! Interpolates the color with a f32 value to another color
		SColorf SColorf::getInterpolated(const SColorf &other, f32 d) const
		{
			d = core::SharedMath::getInstance().clamp(d, 0.f, 1.f);
			const f32 inv = 1.0f - d;
			return SColorf(other.Red * inv + Red * d,
					other.Green * inv + Green * d, other.Blue * inv + Blue * d,
					other.Alpha * inv + Alpha * d);
		}

		//! Returns interpolated color. ( quadratic )
		inline SColorf SColorf::getInterpolated_quadratic(const SColorf& c1,
				const SColorf& c2, f32 d) const
		{
			d = core::SharedMath::getInstance().clamp(d, 0.f, 1.f);
			// this*(1-d)*(1-d) + 2 * c1 * (1-d) + c2 * d * d;
			const f32 inv = 1.f - d;
			const f32 mul0 = inv * inv;
			const f32 mul1 = 2.f * d * inv;
			const f32 mul2 = d * d;

			return SColorf(Red * mul0 + c1.Red * mul1 + c2.Red * mul2,
					Green * mul0 + c1.Green * mul1 + c2.Green * mul2,
					Green * mul0 + c1.Blue * mul1 + c2.Blue * mul2,
					Alpha * mul0 + c1.Alpha * mul1 + c2.Alpha * mul2);
		}

		//! Sets a color component by index. R=0, G=1, B=2, A=3
		void SColorf::setColorComponentValue(s32 index, f32 value)
		{
			switch (index)
			{
				case 0:
					Red = value;
					break;
				case 1:
					Green = value;
					break;
				case 2:
					Blue = value;
					break;
				case 3:
					Alpha = value;
					break;
			}
		}

		//! Returns the alpha component of the color in the range 0.0 (transparent) to 1.0 (opaque)
		f32 SColorf::getAlpha() const
		{
			return Alpha;
		}

		//! Returns the red component of the color in the range 0.0 to 1.0
		f32 SColorf::getRed() const
		{
			return Red;
		}

		//! Returns the green component of the color in the range 0.0 to 1.0
		f32 SColorf::getGreen() const
		{
			return Green;
		}

		//! Returns the blue component of the color in the range 0.0 to 1.0
		f32 SColorf::getBlue() const
		{
			return Blue;
		}

	}  // namespace video

}  // namespace irrgame
