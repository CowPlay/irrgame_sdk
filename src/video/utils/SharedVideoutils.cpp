/*
 * utils.cpp
 *
 *  Created on: Nov 1, 2012
 *      Author: gregorytkach
 */

#include "video/utils/SharedVideoUtils.h"
#include "core/math/SharedFastMath.h"
#include "core/math/SharedConverter.h"
#include "AbsRectangle.h"

namespace irrgame
{
	namespace video
	{

		//! Singleton realization
		SharedVideoUtils& SharedVideoUtils::getInstance()
		{
			static SharedVideoUtils instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		SharedVideoUtils::SharedVideoUtils()
		{
		}

		//! Destructor. Should use only one time.
		SharedVideoUtils::~SharedVideoUtils()
		{
		}

		/*
		 * Methods
		 */

		//! a more useful memset for pixel
		void SharedVideoUtils::memset32(void * dest, const u32 value,
				u32 bytesize)
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
		 */
		u32 SharedVideoUtils::PixelBlend32(const u32 c2, const u32 c1,
				u32 alpha)
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
		u16 SharedVideoUtils::PixelBlend16(const u16 c2, const u32 c1,
				const u16 alpha)
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
		u16 SharedVideoUtils::PixelBlend16(const u16 c2, const u16 c1)
		{
			u16 mask = ((c1 & 0x8000) >> 15) + 0x7fff;
			return (c2 & mask) | (c1 & ~mask);
		}

		// 1 - Bit Alpha Blending 16Bit SIMD
		u32 SharedVideoUtils::PixelBlend16_simd(const u32 c2, const u32 c1)
		{
			u32 mask = ((c1 & 0x80008000) >> 15) + 0x7fff7fff;
			return (c2 & mask) | (c1 & ~mask);
		}

		/*!
		 Pixel = dest * ( 1 - SourceAlpha ) + source * SourceAlpha
		 */
		u32 SharedVideoUtils::PixelBlend32(const u32 c2, const u32 c1)
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
		u16 SharedVideoUtils::PixelMul16_2(u16 c0, u16 c1)
		{
			return (u16) ((((c0 & 0x7C00) * (c1 & 0x7C00)) & 0x3E000000) >> 15
					| (((c0 & 0x03E0) * (c1 & 0x03E0)) & 0x000F8000) >> 10
					| (((c0 & 0x001F) * (c1 & 0x001F)) & 0x000003E0) >> 5
					| (c0 & c1 & 0x8000));
		}

		/*
		 Pixel = c0 * (c1/255). c0 Alpha Retain
		 */
		u32 SharedVideoUtils::PixelMul32(const u32 c0, const u32 c1)
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
		 */
		u32 SharedVideoUtils::PixelMul32_2(const u32 c0, const u32 c1)
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
		s32 SharedVideoUtils::s32_log2_f32(f32 f)
		{
			u32 x = core::SharedConverter::getInstance().convertToUInt(f);
			return ((x & 0x7F800000) >> 23) - 127;
		}

		s32 SharedVideoUtils::s32_log2_s32(u32 x)
		{
			return s32_log2_f32((f32) x);
		}

		//! 2D Intersection test
		bool SharedVideoUtils::intersect(AbsRectangle &dest,
				const AbsRectangle& a, const AbsRectangle& b)
		{
			dest.x0 = core::SharedMath::getInstance().s32Max(a.x0, b.x0);
			dest.y0 = core::SharedMath::getInstance().s32Max(a.y0, b.y0);
			dest.x1 = core::SharedMath::getInstance().s32Min(a.x1, b.x1);
			dest.y1 = core::SharedMath::getInstance().s32Min(a.y1, b.y1);

			return dest.x0 < dest.x1 && dest.y0 < dest.y1;
		}

		//! Returns the alpha component from A1R5G5B5 color
		u32 SharedVideoUtils::getAlpha(u16 color)
		{
			return ((color >> 15) & 0x1);
		}

		//! Returns the red component from A1R5G5B5 color.
		u32 SharedVideoUtils::getRed(u16 color)
		{
			return ((color >> 10) & 0x1F);
		}

		//! Returns the green component from A1R5G5B5 color
		u32 SharedVideoUtils::getGreen(u16 color)
		{
			return ((color >> 5) & 0x1F);
		}

		//! Returns the blue component from A1R5G5B5 color
		/** Shift left by 3 to get 8 bit value. */
		u32 SharedVideoUtils::getBlue(u16 color)
		{
			return (color & 0x1F);
		}

		//! Returns the average from a 16 bit A1R5G5B5 color
		s32 SharedVideoUtils::getAverage(s16 color)
		{
			return ((getRed(color) << 3) + (getGreen(color) << 3)
					+ (getBlue(color) << 3)) / 3;
		}

		//! get the amount of Bits per Pixel of the given color format
		u32 SharedVideoUtils::getBitsPerPixelFromFormat(
				const EColorFormat format)
		{
			switch (format)
			{
				case ECF_A1R5G5B5:
					return 16;
				case ECF_R5G6B5:
					return 16;
				case ECF_R8G8B8:
					return 24;
				case ECF_A8R8G8B8:
					return 32;
				case ECF_R16F:
					return 16;
				case ECF_G16R16F:
					return 32;
				case ECF_A16B16G16R16F:
					return 64;
				case ECF_R32F:
					return 32;
				case ECF_G32R32F:
					return 64;
				case ECF_A32B32G32R32F:
					return 128;
				default:
					return 0;
			}
		}

		//! test if the color format is only viable for RenderTarget textures
		bool SharedVideoUtils::isRenderTargetOnlyFormat(
				const EColorFormat format)
		{
			switch (format)
			{
				case ECF_A1R5G5B5:
				case ECF_R5G6B5:
				case ECF_R8G8B8:
				case ECF_A8R8G8B8:
					return false;
				default:
					return true;
			}
		}

		//! EMT_ONETEXTURE_BLEND: pack srcFact, dstFact, Modulate and alpha source to MaterialTypeParam
		f32 SharedVideoUtils::pack_texureBlendFunc(const E_BLEND_FACTOR srcFact,
				const E_BLEND_FACTOR dstFact, const E_MODULATE_FUNC modulate,
				const u32 alphaSource)
		{
			const u32 tmp = (alphaSource << 12) | (modulate << 8)
					| (srcFact << 4) | dstFact;

			return core::SharedConverter::getInstance().convertToFloat(tmp);
		}

		//! EMT_ONETEXTURE_BLEND: unpack srcFact & dstFact and Modulo to MaterialTypeParam
		void SharedVideoUtils::unpack_texureBlendFunc(E_BLEND_FACTOR &srcFact,
				E_BLEND_FACTOR &dstFact, E_MODULATE_FUNC &modulo,
				u32& alphaSource, const f32 param)
		{
			const u32 state =
					core::SharedConverter::getInstance().convertToUInt(param);
			alphaSource = (state & 0x0000F000) >> 12;
			modulo = E_MODULATE_FUNC((state & 0x00000F00) >> 8);
			srcFact = E_BLEND_FACTOR((state & 0x000000F0) >> 4);
			dstFact = E_BLEND_FACTOR((state & 0x0000000F));
		}

		//! EMT_ONETEXTURE_BLEND: has BlendFactor Alphablending
		bool SharedVideoUtils::textureBlendFunc_hasAlpha(
				const E_BLEND_FACTOR factor)
		{
			switch (factor)
			{
				case EBF_SRC_ALPHA:
				case EBF_ONE_MINUS_SRC_ALPHA:
				case EBF_DST_ALPHA:
				case EBF_ONE_MINUS_DST_ALPHA:
				case EBF_SRC_ALPHA_SATURATE:
					return true;
				default:
					return false;
			}
		}

	}  // namespace video
}  // namespace irrgame

