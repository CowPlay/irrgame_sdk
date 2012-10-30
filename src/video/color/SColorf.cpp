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
				r(0.0f), g(0.0f), b(0.0f), a(1.0f)
		{
		}

		//! Constructs a color from up to four color values: red, green, blue, and alpha.
		SColorf::SColorf(f32 r, f32 g, f32 b, f32 a) :
				r(r), g(g), b(b), a(a)
		{
		}

		//! Constructs a color from 32 bit Color.
		SColorf::SColorf(SColor c)
		{
			const f32 inv = 1.0f / 255.0f;
			r = c.getRed() * inv;
			g = c.getGreen() * inv;
			b = c.getBlue() * inv;
			a = c.getAlpha() * inv;
		}

		//! Converts this color to a SColor without floats.
		SColor SColorf::toSColor() const
		{
			return SColor((u32) (a * 255.0f), (u32) (r * 255.0f),
					(u32) (g * 255.0f), (u32) (b * 255.0f));
		}

		//! Sets three color components to new values at once.
		void SColorf::set(f32 rr, f32 gg, f32 bb)
		{
			r = rr;
			g = gg;
			b = bb;
		}

		//! Sets all four color components to new values at once.
		void SColorf::set(f32 aa, f32 rr, f32 gg, f32 bb)
		{
			a = aa;
			r = rr;
			g = gg;
			b = bb;
		}

		//! Interpolates the color with a f32 value to another color
		SColorf SColorf::getInterpolated(const SColorf &other, f32 d) const
		{
			d = core::clamp(d, 0.f, 1.f);
			const f32 inv = 1.0f - d;
			return SColorf(other.r * inv + r * d, other.g * inv + g * d,
					other.b * inv + b * d, other.a * inv + a * d);
		}

		//! Returns interpolated color. ( quadratic )
		inline SColorf SColorf::getInterpolated_quadratic(const SColorf& c1,
				const SColorf& c2, f32 d) const
		{
			d = core::clamp(d, 0.f, 1.f);
			// this*(1-d)*(1-d) + 2 * c1 * (1-d) + c2 * d * d;
			const f32 inv = 1.f - d;
			const f32 mul0 = inv * inv;
			const f32 mul1 = 2.f * d * inv;
			const f32 mul2 = d * d;

			return SColorf(r * mul0 + c1.r * mul1 + c2.r * mul2,
					g * mul0 + c1.g * mul1 + c2.g * mul2,
					g * mul0 + c1.b * mul1 + c2.b * mul2,
					a * mul0 + c1.a * mul1 + c2.a * mul2);
		}

		//! Sets a color component by index. R=0, G=1, B=2, A=3
		void SColorf::setColorComponentValue(s32 index, f32 value)
		{
			switch (index)
			{
				case 0:
					r = value;
					break;
				case 1:
					g = value;
					break;
				case 2:
					b = value;
					break;
				case 3:
					a = value;
					break;
			}
		}

		//! Returns the alpha component of the color in the range 0.0 (transparent) to 1.0 (opaque)
		f32 SColorf::getAlpha() const
		{
			return a;
		}

		//! Returns the red component of the color in the range 0.0 to 1.0
		f32 SColorf::getRed() const
		{
			return r;
		}

		//! Returns the green component of the color in the range 0.0 to 1.0
		f32 SColorf::getGreen() const
		{
			return g;
		}

		//! Returns the blue component of the color in the range 0.0 to 1.0
		f32 SColorf::getBlue() const
		{
			return b;
		}

	}  // namespace video

}  // namespace irrgame
