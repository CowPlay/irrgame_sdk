/*
 * SColor.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "video/color/SColor.h"
#include "video/color/SharedColorConverter.h"
#include "video/utils/SharedVideoUtils.h"
#include "core/math/SharedFastMath.h"

namespace irrgame
{

	namespace video
	{
		//! Constructor of the Color. Does nothing.opaque
		SColor::SColor() :
				color(0)
		{
		}

		//! Constructs the color from 4 values representing the alpha, red, green and blue component.
		SColor::SColor(u32 a, u32 r, u32 g, u32 b) :
				color(
						((a & 0xff) << 24) | ((r & 0xff) << 16)
								| ((g & 0xff) << 8) | (b & 0xff))
		{
		}

		//! Constructs the color from a 32 bit value. Could be another color.
		SColor::SColor(u32 clr) :
				color(clr)
		{
		}

		//! Returns the alpha component of the color.
		u32 SColor::getAlpha() const
		{
			return color >> 24;
		}

		//! Returns the red component of the color.
		u32 SColor::getRed() const
		{
			return (color >> 16) & 0xff;
		}

		//! Returns the green component of the color.
		u32 SColor::getGreen() const
		{
			return (color >> 8) & 0xff;
		}

		//! Returns the blue component of the color.
		u32 SColor::getBlue() const
		{
			return color & 0xff;
		}

		//! Get lightness of the color in the range [0,255]
		f32 SColor::getLightness() const
		{
			return 0.5f
					* (core::SharedMath::getInstance().max(
							core::SharedMath::getInstance().max(getRed(),
									getGreen()), getBlue())
							+ core::SharedMath::getInstance().min(
									core::SharedMath::getInstance().min(
											getRed(), getGreen()), getBlue()));
		}

		//! Get luminance of the color in the range [0,255].
		f32 SColor::getLuminance() const
		{
			return 0.3f * getRed() + 0.59f * getGreen() + 0.11f * getBlue();
		}

		//! Get average intensity of the color in the range [0,255].
		u32 SColor::getAverage() const
		{
			return (getRed() + getGreen() + getBlue()) / 3;
		}

		//! Sets the alpha component of the Color.
		void SColor::setAlpha(u32 a)
		{
			color = ((a & 0xff) << 24) | (color & 0x00ffffff);
		}

		//! Sets the red component of the Color.
		void SColor::setRed(u32 r)
		{
			color = ((r & 0xff) << 16) | (color & 0xff00ffff);
		}

		//! Sets the green component of the Color.
		void SColor::setGreen(u32 g)
		{
			color = ((g & 0xff) << 8) | (color & 0xffff00ff);
		}

		//! Sets the blue component of the Color.
		void SColor::setBlue(u32 b)
		{
			color = (b & 0xff) | (color & 0xffffff00);
		}

		//! Calculates a 16 bit A1R5G5B5 value of this color.
		u16 SColor::toA1R5G5B5() const
		{
			return SharedColorConverter::getInstance().A8R8G8B8toA1R5G5B5(color);
		}

		//! Converts color to OpenGL color format
		void SColor::toOpenGLColor(u8* dest) const
		{
			*dest = (u8) getRed();
			*++dest = (u8) getGreen();
			*++dest = (u8) getBlue();
			*++dest = (u8) getAlpha();
		}

		//! Sets all four components of the color at once.
		void SColor::set(u32 a, u32 r, u32 g, u32 b)
		{
			color = (((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8)
					| (b & 0xff));
		}
		void SColor::set(u32 col)
		{
			color = col;
		}

		//! Compares the color to another color.
		bool SColor::operator==(const SColor& other) const
		{
			return other.color == color;
		}

		//! Compares the color to another color.
		bool SColor::operator!=(const SColor& other) const
		{
			return other.color != color;
		}

		//! comparison operator
		bool SColor::operator<(const SColor& other) const
		{
			return (color < other.color);
		}

		//! Adds two colors, result is clamped to 0..255 values
		SColor SColor::operator+(const SColor& other) const
		{
			return SColor(
					core::SharedMath::getInstance().min(
							getAlpha() + other.getAlpha(), 255u),
					core::SharedMath::getInstance().min(
							getRed() + other.getRed(), 255u),
					core::SharedMath::getInstance().min(
							getGreen() + other.getGreen(), 255u),
					core::SharedMath::getInstance().min(
							getBlue() + other.getBlue(), 255u));
		}

		//! Interpolates the color with a f32 value to another color
		SColor SColor::getInterpolated(const SColor &other, f32 d) const
		{
			d = core::SharedMath::getInstance().clamp(d, 0.f, 1.f);
			const f32 inv = 1.0f - d;
			return SColor((u32) (other.getAlpha() * inv + getAlpha() * d),
					(u32) (other.getRed() * inv + getRed() * d),
					(u32) (other.getGreen() * inv + getGreen() * d),
					(u32) (other.getBlue() * inv + getBlue() * d));
		}

		//! Returns interpolated color. ( quadratic )
		SColor SColor::getInterpolated_quadratic(const SColor& c1,
				const SColor& c2, f32 d) const
		{
			// this*(1-d)*(1-d) + 2 * c1 * (1-d) + c2 * d * d;
			d = core::SharedMath::getInstance().clamp(d, 0.f, 1.f);
			const f32 inv = 1.f - d;
			const f32 mul0 = inv * inv;
			const f32 mul1 = 2.f * d * inv;
			const f32 mul2 = d * d;

			return SColor(
					core::SharedMath::getInstance().clamp(
							core::SharedFastMath::getInstance().floor32(
									getAlpha() * mul0 + c1.getAlpha() * mul1
											+ c2.getAlpha() * mul2), 0, 255),
					core::SharedMath::getInstance().clamp(
							core::SharedFastMath::getInstance().floor32(
									getRed() * mul0 + c1.getRed() * mul1
											+ c2.getRed() * mul2), 0, 255),
					core::SharedMath::getInstance().clamp(
							core::SharedFastMath::getInstance().floor32(
									getGreen() * mul0 + c1.getGreen() * mul1
											+ c2.getGreen() * mul2), 0, 255),
					core::SharedMath::getInstance().clamp(
							core::SharedFastMath::getInstance().floor32(
									getBlue() * mul0 + c1.getBlue() * mul1
											+ c2.getBlue() * mul2), 0, 255));
		}
	}  // namespace video

}  // namespace irrgame
