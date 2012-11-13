/*
 * EHardwareMapping.h
 *
 *  Created on: Nov 12, 2012
 *      Author: gregorytkach
 */

#ifndef EHARDWAREMAPPING_H_
#define EHARDWAREMAPPING_H_

namespace irrgame
{
	namespace scene
	{
		enum E_HARDWARE_MAPPING
		{
			//! Don't store on the hardware
			EHM_NEVER = 0,

			//! Rarely changed, usually stored completely on the hardware
			EHM_STATIC,

			//! Sometimes changed, driver optimized placement
			EHM_DYNAMIC,

			//! Always changed, cache optimizing on the GPU
			EHM_STREAM,

			EHM_COUNT
		};
	}  // namespace scene
}  // namespace irrgame

#endif /* EHARDWAREMAPPING_H_ */
