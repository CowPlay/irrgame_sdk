/*
 * videoutils.h
 *
 *  Created on: Jul 30, 2012
 *      Author: gregorytkach
 */

#ifndef VIDEOUTILS_H_
#define VIDEOUTILS_H_

#include "./core/irrMath.h"

namespace irrgame
{
	namespace video
	{
		// some 2D Defines
		struct AbsRectangle
		{
				s32 x0;
				s32 y0;
				s32 x1;
				s32 y1;
		};

		//! a more useful memset for pixel
		inline void memset32(void * dest, const u32 value, u32 bytesize)
		{
			u32 * d = (u32*) dest;

			u32 i;

			i = bytesize >> (2 + 3);
			while (i)
			{
				d[0] = value;
				d[1] = value;
				d[2] = value;
				d[3] = value;

				d[4] = value;
				d[5] = value;
				d[6] = value;
				d[7] = value;

				d += 8;
				i -= 1;
			}

			i = (bytesize >> 2) & 7;
			while (i)
			{
				d[0] = value;
				d += 1;
				i -= 1;
			}

		}

		/*!
		 Pixel = dest * ( 1 - alpha ) + source * alpha
		 alpha [0;256]
		 */REALINLINE u32 PixelBlend32(const u32 c2, const u32 c1, u32 alpha)
		{
			u32 srcRB = c1 & 0x00FF00FF;
			u32 srcXG = c1 & 0x0000FF00;

			u32 dstRB = c2 & 0x00FF00FF;
			u32 dstXG = c2 & 0x0000FF00;

			u32 rb = srcRB - dstRB;
			u32 xg = srcXG - dstXG;

			rb *= alpha;
			xg *= alpha;
			rb >>= 8;
			xg >>= 8;

			rb += dstRB;
			xg += dstXG;

			rb &= 0x00FF00FF;
			xg &= 0x0000FF00;

			return rb | xg;
		}

		/*!
		 Pixel = dest * ( 1 - alpha ) + source * alpha
		 alpha [0;32]
		 */
		inline u16 PixelBlend16(const u16 c2, const u32 c1, const u16 alpha)
		{
			const u16 srcRB = c1 & 0x7C1F;
			const u16 srcXG = c1 & 0x03E0;

			const u16 dstRB = c2 & 0x7C1F;
			const u16 dstXG = c2 & 0x03E0;

			u32 rb = srcRB - dstRB;
			u32 xg = srcXG - dstXG;

			rb *= alpha;
			xg *= alpha;
			rb >>= 5;
			xg >>= 5;

			rb += dstRB;
			xg += dstXG;

			rb &= 0x7C1F;
			xg &= 0x03E0;

			return (u16) (rb | xg);
		}

		// 1 - Bit Alpha Blending
		inline u16 PixelBlend16(const u16 c2, const u16 c1)
		{
			u16 mask = ((c1 & 0x8000) >> 15) + 0x7fff;
			return (c2 & mask) | (c1 & ~mask);
		}

		// 1 - Bit Alpha Blending 16Bit SIMD
		inline u32 PixelBlend16_simd(const u32 c2, const u32 c1)
		{
			u32 mask = ((c1 & 0x80008000) >> 15) + 0x7fff7fff;
			return (c2 & mask) | (c1 & ~mask);
		}

		/*!
		 Pixel = dest * ( 1 - SourceAlpha ) + source * SourceAlpha
		 */
		inline u32 PixelBlend32(const u32 c2, const u32 c1)
		{
			// alpha test
			u32 alpha = c1 & 0xFF000000;

			if (0 == alpha)
				return c2;

			if (0xFF000000 == alpha)
			{
				return c1;
			}

			alpha >>= 24;

			// add highbit alpha, if ( alpha > 127 ) alpha += 1;
			alpha += (alpha >> 7);

			u32 srcRB = c1 & 0x00FF00FF;
			u32 srcXG = c1 & 0x0000FF00;

			u32 dstRB = c2 & 0x00FF00FF;
			u32 dstXG = c2 & 0x0000FF00;

			u32 rb = srcRB - dstRB;
			u32 xg = srcXG - dstXG;

			rb *= alpha;
			xg *= alpha;
			rb >>= 8;
			xg >>= 8;

			rb += dstRB;
			xg += dstXG;

			rb &= 0x00FF00FF;
			xg &= 0x0000FF00;

			return (c1 & 0xFF000000) | rb | xg;
		}

		/*
		 Pixel = c0 * (c1/31).
		 */
		inline u16 PixelMul16_2(u16 c0, u16 c1)
		{
			return (u16) ((((c0 & 0x7C00) * (c1 & 0x7C00)) & 0x3E000000) >> 15
					| (((c0 & 0x03E0) * (c1 & 0x03E0)) & 0x000F8000) >> 10
					| (((c0 & 0x001F) * (c1 & 0x001F)) & 0x000003E0) >> 5
					| (c0 & c1 & 0x8000));
		}

		/*
		 Pixel = c0 * (c1/255). c0 Alpha Retain
		 */REALINLINE u32 PixelMul32(const u32 c0, const u32 c1)
		{
			return (c0 & 0xFF000000)
					| ((((c0 & 0x00FF0000) >> 12) * ((c1 & 0x00FF0000) >> 12))
							& 0x00FF0000)
					| ((((c0 & 0x0000FF00) * (c1 & 0x0000FF00)) >> 16)
							& 0x0000FF00)
					| ((((c0 & 0x000000FF) * (c1 & 0x000000FF)) >> 8)
							& 0x000000FF);
		}

		/*
		 Pixel = c0 * (c1/255).
		 */REALINLINE u32 PixelMul32_2(const u32 c0, const u32 c1)
		{
			return ((((c0 & 0xFF000000) >> 16) * ((c1 & 0xFF000000) >> 16))
					& 0xFF000000)
					| ((((c0 & 0x00FF0000) >> 12) * ((c1 & 0x00FF0000) >> 12))
							& 0x00FF0000)
					| ((((c0 & 0x0000FF00) * (c1 & 0x0000FF00)) >> 16)
							& 0x0000FF00)
					| ((((c0 & 0x000000FF) * (c1 & 0x000000FF)) >> 8)
							& 0x000000FF);
		}

		// integer log2 of a float ieee 754. TODO: non ieee floating point
		static inline s32 s32_log2_f32(f32 f)
		{
			u32 x = core::IR(f);
			return ((x & 0x7F800000) >> 23) - 127;
		}

		static inline s32 s32_log2_s32(u32 x)
		{
			return s32_log2_f32((f32) x);
		}

		//! 2D Intersection test
		inline bool intersect(AbsRectangle &dest, const AbsRectangle& a,
				const AbsRectangle& b)
		{
			dest.x0 = core::s32_max(a.x0, b.x0);
			dest.y0 = core::s32_max(a.y0, b.y0);
			dest.x1 = core::s32_min(a.x1, b.x1);
			dest.y1 = core::s32_min(a.y1, b.y1);
			return dest.x0 < dest.x1 && dest.y0 < dest.y1;
		}

		//! Creates a 16 bit A1R5G5B5 color
		inline u16 RGBA16(u32 r, u32 g, u32 b, u32 a = 0xFF)
		{
			return (u16) ((a & 0x80) << 8 | (r & 0xF8) << 7 | (g & 0xF8) << 2
					| (b & 0xF8) >> 3);
		}

		//! Creates a 16 bit A1R5G5B5 color
		inline u16 RGB16(u32 r, u32 g, u32 b)
		{
			return RGBA16(r, g, b);
		}

		//! Creates a 16bit A1R5G5B5 color, based on 16bit input values
		inline u16 RGB16from16(u16 r, u16 g, u16 b)
		{
			return (0x8000 | (r & 0x1F) << 10 | (g & 0x1F) << 5 | (b & 0x1F));
		}

		//! Converts a 32bit (X8R8G8B8) color to a 16bit A1R5G5B5 color
		inline u16 X8R8G8B8toA1R5G5B5(u32 color)
		{
			return (u16) (0x8000 | (color & 0x00F80000) >> 9
					| (color & 0x0000F800) >> 6 | (color & 0x000000F8) >> 3);
		}

		//! Converts a 32bit (A8R8G8B8) color to a 16bit A1R5G5B5 color
		inline u16 A8R8G8B8toA1R5G5B5(u32 color)
		{
			return (u16) ((color & 0x80000000) >> 16 | (color & 0x00F80000) >> 9
					| (color & 0x0000F800) >> 6 | (color & 0x000000F8) >> 3);
		}

		//! Converts a 32bit (A8R8G8B8) color to a 16bit R5G6B5 color
		inline u16 A8R8G8B8toR5G6B5(u32 color)
		{
			return (u16) ((color & 0x00F80000) >> 8 | (color & 0x0000FC00) >> 5
					| (color & 0x000000F8) >> 3);
		}

		//! Convert A8R8G8B8 Color from A1R5G5B5 color
		/** build a nicer 32bit Color by extending dest lower bits with source high bits. */
		inline u32 A1R5G5B5toA8R8G8B8(u16 color)
		{
			return (((-((s32) color & 0x00008000) >> (s32) 31) & 0xFF000000)
					| ((color & 0x00007C00) << 9) | ((color & 0x00007000) << 4)
					| ((color & 0x000003E0) << 6) | ((color & 0x00000380) << 1)
					| ((color & 0x0000001F) << 3) | ((color & 0x0000001C) >> 2));
		}

		//! Returns A8R8G8B8 Color from R5G6B5 color
		inline u32 R5G6B5toA8R8G8B8(u16 color)
		{
			return 0xFF000000 | ((color & 0xF800) << 8)
					| ((color & 0x07E0) << 5) | ((color & 0x001F) << 3);
		}

		//! Returns A1R5G5B5 Color from R5G6B5 color
		inline u16 R5G6B5toA1R5G5B5(u16 color)
		{
			return 0x8000 | (((color & 0xFFC0) >> 1) | (color & 0x1F));
		}

		//! Returns R5G6B5 Color from A1R5G5B5 color
		inline u16 A1R5G5B5toR5G6B5(u16 color)
		{
			return (((color & 0x7FE0) << 1) | (color & 0x1F));
		}

		//! Returns the alpha component from A1R5G5B5 color
		/** In Irrlicht, alpha refers to opacity.
		 \return The alpha value of the color. 0 is transparent, 1 is opaque. */
		inline u32 getAlpha(u16 color)
		{
			return ((color >> 15) & 0x1);
		}

		//! Returns the red component from A1R5G5B5 color.
		/** Shift left by 3 to get 8 bit value. */
		inline u32 getRed(u16 color)
		{
			return ((color >> 10) & 0x1F);
		}

		//! Returns the green component from A1R5G5B5 color
		/** Shift left by 3 to get 8 bit value. */
		inline u32 getGreen(u16 color)
		{
			return ((color >> 5) & 0x1F);
		}

		//! Returns the blue component from A1R5G5B5 color
		/** Shift left by 3 to get 8 bit value. */
		inline u32 getBlue(u16 color)
		{
			return (color & 0x1F);
		}

		//! Returns the average from a 16 bit A1R5G5B5 color
		inline s32 getAverage(s16 color)
		{
			return ((getRed(color) << 3) + (getGreen(color) << 3)
					+ (getBlue(color) << 3)) / 3;
		}

	}
}

#endif /* VIDEOUTILS_H_ */
