/*
 * EAlphaSource.h
 *
 *  Created on: Oct 26, 2012
 *      Author: gregorytkach
 */

#ifndef EALPHASOURCE_H_
#define EALPHASOURCE_H_

namespace irrgame
{
	namespace video
	{

		//! Source of the alpha value to take
		/** This is currently only supported in EMT_ONETEXTURE_BLEND. You can use an
		 or'ed combination of values. Alpha values are modulated (multiplicated). */
		enum E_ALPHA_SOURCE
		{
			//! Use no alpha, somewhat redundant with other settings
			EAS_NONE = 0,
			//! Use vertex color alpha
			EAS_VERTEX_COLOR,
			//! Use texture alpha channel
			EAS_TEXTURE,

			//! Not used
			EAS_COUNT
		};
	}  // namespace video
}  // namespace irrgame

#endif /* EALPHASOURCE_H_ */
