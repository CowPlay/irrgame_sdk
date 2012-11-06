/*
 * blit.h
 *
 *  Created on: Nov 1, 2012
 *      Author: gregorytkach
 */

#ifndef BLIT_H_
#define BLIT_H_

#include "SBlitJob.h"
#include "eBlitter.h"
#include "EClipCode.h"
#include "core/shapes/vector2d.h"
#include "core/shapes/rect.h"

namespace irrgame
{
	namespace video
	{
		struct AbsRectangle;
		class IImage;

		typedef void (*tExecuteBlit)(const SBlitJob * job);

		u32 GetClipCode(const AbsRectangle &r, const vector2di &p);

		/*!
		 Cohen Sutherland clipping
		 @return: 1 if valid
		 */
		s32 ClipLine(const AbsRectangle &clipping, vector2di &p0, vector2di &p1,
				const vector2di& p0_in, const vector2di& p1_in);

		void GetClip(AbsRectangle &clipping, IImage * t);

		/*
		 return alpha in [0;256] Granularity from 32-Bit ARGB
		 add highbit alpha ( alpha > 127 ? + 1 )
		 */
		u32 extractAlpha(const u32 c);

		/*
		 return alpha in [0;255] Granularity and 32-Bit ARGB
		 add highbit alpha ( alpha > 127 ? + 1 )
		 */
		u32 packAlpha(const u32 c);

		/*!
		 Scale Color by (1/value)
		 value 0 - 256 ( alpha )
		 */
		u32 PixelLerp32(const u32 source, const u32 value);

		void RenderLine32_Decal(video::IImage *t, const vector2di &p0,
				const vector2di &p1, u32 argb);

		void RenderLine32_Blend(IImage *t, const vector2di &p0,
				const vector2di &p1, u32 argb, u32 alpha);

		void RenderLine16_Decal(IImage *t, const vector2di &p0,
				const vector2di &p1, u32 argb);

		void RenderLine16_Blend(IImage *t, const vector2di &p0,
				const vector2di &p1, u16 argb, u16 alpha);

		void executeBlit_TextureCopy_x_to_x(const SBlitJob * job);

		void executeBlit_TextureCopy_32_to_16(const SBlitJob * job);

		void executeBlit_TextureCopy_24_to_16(const SBlitJob * job);

		void executeBlit_TextureCopy_16_to_32(const SBlitJob * job);

		void executeBlit_TextureCopy_16_to_24(const SBlitJob * job);

		void executeBlit_TextureCopy_24_to_32(const SBlitJob * job);

		void executeBlit_TextureCopy_32_to_24(const SBlitJob * job);

		void executeBlit_TextureBlend_16_to_16(const SBlitJob * job);

		void executeBlit_TextureBlend_32_to_32(const SBlitJob * job);

		void executeBlit_TextureBlendColor_16_to_16(const SBlitJob * job);

		void executeBlit_TextureBlendColor_32_to_32(const SBlitJob * job);

		void executeBlit_Color_16_to_16(const SBlitJob * job);

		void executeBlit_Color_32_to_32(const SBlitJob * job);

		void executeBlit_ColorAlpha_16_to_16(const SBlitJob * job);

		void executeBlit_ColorAlpha_32_to_32(const SBlitJob * job);

		tExecuteBlit getBlitter2(eBlitter operation, const video::IImage * dest,
				const video::IImage * source);

		// bounce clipping to texture
		void setClip(AbsRectangle &out, const recti *clip, const IImage * tex,
				s32 passnative);

		/*!
		 a generic 2D Blitter
		 */
		s32 Blit(eBlitter operation, IImage * dest, const recti *destClipping,
				const vector2di *destPos, IImage * const source,
				const recti *sourceClipping, u32 argb);

	}  // namespace video
}  // namespace irrgame

#endif /* BLIT_H_ */
