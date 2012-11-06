/*
 * eBlitter.h
 *
 *  Created on: Nov 1, 2012
 *      Author: gregorytkach
 */

#ifndef EBLITTER_H_
#define EBLITTER_H_

namespace irrgame
{
	namespace video
	{
		// Blitter Operation
		enum eBlitter
		{
			BLITTER_INVALID = 0,
			BLITTER_COLOR,
			BLITTER_COLOR_ALPHA,
			BLITTER_TEXTURE,
			BLITTER_TEXTURE_ALPHA_BLEND,
			BLITTER_TEXTURE_ALPHA_COLOR_BLEND,

			//Not used
			BLITTER_COUNT
		};
	}  // namespace video
}  // namespace irrgame

#endif /* EBLITTER_H_ */
