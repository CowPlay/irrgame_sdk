/*
 * EAntiAliasingMode.h
 *
 *  Created on: Oct 26, 2012
 *      Author: gregorytkach
 */

#ifndef EANTIALIASINGMODE_H_
#define EANTIALIASINGMODE_H_

namespace irrgame
{

	namespace video
	{

		//! These flags are used to specify the anti-aliasing and smoothing modes
		/** Techniques supported are multisampling, geometry smoothing, and alpha
		 to coverage.
		 Some drivers don't support a per-material setting of the anti-aliasing
		 modes. In those cases, FSAA/multisampling is defined by the device mode
		 chosen upon creation via irr::SIrrCreationParameters.
		 */
		enum E_ANTI_ALIASING_MODE
		{
			//! Use to turn off anti-aliasing for this material
			EAAM_OFF = 0,
			//! Default anti-aliasing mode
			EAAM_SIMPLE = 1,
			//! High-quality anti-aliasing, not always supported, automatically enables SIMPLE mode
			EAAM_QUALITY = 3,
			//! Line smoothing
			EAAM_LINE_SMOOTH = 4,
			//! point smoothing, often in software and slow, only with OpenGL
			EAAM_POINT_SMOOTH = 8,
			//! All typical anti-alias and smooth modes
			EAAM_FULL_BASIC = 15,
			//! Enhanced anti-aliasing for transparent materials
			/** Usually used with EMT_TRANSPARENT_ALPHA_REF and multisampling. */
			EAAM_ALPHA_TO_COVERAGE = 16
		};

	}  // namespace video

}  // namespace irrgame

#endif /* EANTIALIASINGMODE_H_ */
