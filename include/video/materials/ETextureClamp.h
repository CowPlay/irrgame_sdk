/*
 * ETextureClamp.h
 *
 *  Created on: Oct 26, 2012
 *      Author: gregorytkach
 */

#ifndef ETEXTURECLAMP_H_
#define ETEXTURECLAMP_H_

namespace irrgame
{
	namespace video
	{

		//! Texture coord clamp mode outside [0.0, 1.0]
		enum E_TEXTURE_CLAMP
		{
			//! Texture repeats
			ETC_REPEAT = 0,
			//! Texture is clamped to the last pixel
			ETC_CLAMP,
			//! Texture is clamped to the edge pixel
			ETC_CLAMP_TO_EDGE,
			//! Texture is clamped to the border pixel (if exists)
			ETC_CLAMP_TO_BORDER,
			//! Texture is alternatingly mirrored (0..1..0..1..0..)
			ETC_MIRROR,
			//! Texture is mirrored once and then clamped (0..1..0)
			ETC_MIRROR_CLAMP,
			//! Texture is mirrored once and then clamped to edge
			ETC_MIRROR_CLAMP_TO_EDGE,
			//! Texture is mirrored once and then clamped to border
			ETC_MIRROR_CLAMP_TO_BORDER
		};

		static const char* const aTextureClampNames[] =
		{ "texture_clamp_repeat", "texture_clamp_clamp",
				"texture_clamp_clamp_to_edge", "texture_clamp_clamp_to_border",
				"texture_clamp_mirror", "texture_clamp_mirror_clamp",
				"texture_clamp_mirror_clamp_to_edge",
				"texture_clamp_mirror_clamp_to_border", 0 };

	}  // namespace video

}  // namespace irrgame

#endif /* ETEXTURECLAMP_H_ */
