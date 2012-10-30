/*
 * EColorPlane.h
 *
 *  Created on: Oct 26, 2012
 *      Author: gregorytkach
 */

#ifndef ECOLORPLANE_H_
#define ECOLORPLANE_H_

namespace irrgame
{

	namespace video
	{
		//! Enum values for enabling/disabling color planes for rendering
		enum E_COLOR_PLANE
		{
			//! No color enabled
			ECP_NONE = 0,
			//! Alpha enabled
			ECP_ALPHA = 1,
			//! Red enabled
			ECP_RED = 2,
			//! Green enabled
			ECP_GREEN = 4,
			//! Blue enabled
			ECP_BLUE = 8,
			//! All colors, no alpha
			ECP_RGB = 14,
			//! All planes enabled
			ECP_ALL = 15
		};

	}  // namespace video

}  // namespace irrgame

#endif /* ECOLORPLANE_H_ */
