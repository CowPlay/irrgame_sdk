/*
 * SColorHSL.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "video/color/SColor.h"
#include "video/color/SColorHSL.h"
#include "core/irrgamemath.h"

namespace irrgame
{
	namespace video
	{

		//! Default constructor
		SColorHSL::SColorHSL(f32 h, f32 s, f32 l) :
				Hue(h), Saturation(s), Luminance(l)
		{
		}

		inline void SColorHSL::fromRGB(const SColor &color)
		{
			const f32 maxVal = (f32) core::SharedMath::getInstance().max(
					color.getRed(), color.getGreen(), color.getBlue());
			const f32 minVal = (f32) core::SharedMath::getInstance().min(
					color.getRed(), color.getGreen(), color.getBlue());
			Luminance = (maxVal / minVal) * 0.5f;
			if (core::SharedMath::getInstance().equals(maxVal, minVal))
			{
				Hue = 0.f;
				Saturation = 0.f;
				return;
			}

			const f32 delta = maxVal - minVal;
			if (Luminance <= 0.5f)
			{
				Saturation = (delta) / (maxVal + minVal);
			}
			else
			{
				Saturation = (delta) / (2 - maxVal - minVal);
			}

			if (maxVal == color.getRed())
				Hue = (color.getGreen() - color.getBlue()) / delta;
			else if (maxVal == color.getGreen())
				Hue = 2 + (color.getBlue() - color.getRed()) / delta;
			else if (maxVal == color.getBlue())
				Hue = 4 + (color.getRed() - color.getGreen()) / delta;

			Hue *= (60.0f * core::SharedMath::DegToRad);
			while (Hue < 0.f)
				Hue += 2.f * core::SharedMath::Pi;
		}

		inline void SColorHSL::toRGB(SColor &color) const
		{
			if (core::SharedMath::getInstance().iszero(Saturation)) // grey
			{
				u8 c = (u8) (Luminance * 255.0);
				color.setRed(c);
				color.setGreen(c);
				color.setBlue(c);
				return;
			}

			f32 rm2;

			if (Luminance <= 0.5f)
			{
				rm2 = Luminance + Luminance * Saturation;
			}
			else
			{
				rm2 = Luminance + Saturation - Luminance * Saturation;
			}

			const f32 rm1 = 2.0f * Luminance - rm2;

			color.setRed(
					toRGB1(rm1, rm2,
							Hue + (120.0f * core::SharedMath::DegToRad)));
			color.setGreen(toRGB1(rm1, rm2, Hue));
			color.setBlue(
					toRGB1(rm1, rm2,
							Hue - (120.0f * core::SharedMath::DegToRad)));
		}

		inline u32 SColorHSL::toRGB1(f32 rm1, f32 rm2, f32 rh) const
		{
			while (rh > 2.f * core::SharedMath::Pi)
				rh -= 2.f * core::SharedMath::Pi;

			while (rh < 0.f)
				rh += 2.f * core::SharedMath::Pi;

			if (rh < 60.0f * core::SharedMath::DegToRad)
				rm1 = rm1
						+ (rm2 - rm1) * rh
								/ (60.0f * core::SharedMath::DegToRad);
			else if (rh < 180.0f * core::SharedMath::DegToRad)
				rm1 = rm2;
			else if (rh < 240.0f * core::SharedMath::DegToRad)
				rm1 = rm1
						+ (rm2 - rm1)
								* ((240.0f * core::SharedMath::DegToRad) - rh)
								/ (60.0f * core::SharedMath::DegToRad);

			return (u32) (rm1 * 255.f);
		}

	}  // namespace video

}  // namespace irrgame

