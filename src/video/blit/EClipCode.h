/*
 * EClipCode.h
 *
 *  Created on: Nov 1, 2012
 *      Author: gregorytkach
 */

#ifndef ECLIPCODE_H_
#define ECLIPCODE_H_

namespace irrgame
{
	namespace video
	{
		// Bitfields Cohen Sutherland
		enum eClipCode
		{
			CLIPCODE_EMPTY = 0,
			CLIPCODE_BOTTOM = 1,
			CLIPCODE_TOP = 2,
			CLIPCODE_LEFT = 4,
			CLIPCODE_RIGHT = 8,

			//Not used
			CLIPCODE_COUNT
		};
	} // namespace video
} // namespace irrgame

#endif /* ECLIPCODE_H_ */
