/*
 * blitterTable.h
 *
 *  Created on: Nov 1, 2012
 *      Author: gregorytkach
 */

#ifndef BLITTERTABLE_H_
#define BLITTERTABLE_H_

namespace irrgame
{
	namespace video
	{
		struct blitterTable
		{
				eBlitter operation;
				s32 destFormat;
				s32 sourceFormat;
				tExecuteBlit func;
		};

		static const blitterTable blitTable[] =
		{
		{ BLITTER_TEXTURE, -2, -2, executeBlit_TextureCopy_x_to_x },
		{ BLITTER_TEXTURE, video::ECF_A1R5G5B5, video::ECF_A8R8G8B8,
				executeBlit_TextureCopy_32_to_16 },
		{ BLITTER_TEXTURE, video::ECF_A1R5G5B5, video::ECF_R8G8B8,
				executeBlit_TextureCopy_24_to_16 },
		{ BLITTER_TEXTURE, video::ECF_A8R8G8B8, video::ECF_A1R5G5B5,
				executeBlit_TextureCopy_16_to_32 },
		{ BLITTER_TEXTURE, video::ECF_A8R8G8B8, video::ECF_R8G8B8,
				executeBlit_TextureCopy_24_to_32 },
		{ BLITTER_TEXTURE, video::ECF_R8G8B8, video::ECF_A1R5G5B5,
				executeBlit_TextureCopy_16_to_24 },
		{ BLITTER_TEXTURE, video::ECF_R8G8B8, video::ECF_A8R8G8B8,
				executeBlit_TextureCopy_32_to_24 },
		{ BLITTER_TEXTURE_ALPHA_BLEND, video::ECF_A1R5G5B5, video::ECF_A1R5G5B5,
				executeBlit_TextureBlend_16_to_16 },
		{ BLITTER_TEXTURE_ALPHA_BLEND, video::ECF_A8R8G8B8, video::ECF_A8R8G8B8,
				executeBlit_TextureBlend_32_to_32 },
		{ BLITTER_TEXTURE_ALPHA_COLOR_BLEND, video::ECF_A1R5G5B5,
				video::ECF_A1R5G5B5, executeBlit_TextureBlendColor_16_to_16 },
		{ BLITTER_TEXTURE_ALPHA_COLOR_BLEND, video::ECF_A8R8G8B8,
				video::ECF_A8R8G8B8, executeBlit_TextureBlendColor_32_to_32 },
		{ BLITTER_COLOR, video::ECF_A1R5G5B5, -1, executeBlit_Color_16_to_16 },
		{ BLITTER_COLOR, video::ECF_A8R8G8B8, -1, executeBlit_Color_32_to_32 },
		{ BLITTER_COLOR_ALPHA, video::ECF_A1R5G5B5, -1,
				executeBlit_ColorAlpha_16_to_16 },
		{ BLITTER_COLOR_ALPHA, video::ECF_A8R8G8B8, -1,
				executeBlit_ColorAlpha_32_to_32 },
		{ BLITTER_INVALID, -1, -1, 0 } };

	} // namespace video
} // namespace irrgame

#endif /* BLITTERTABLE_H_ */
