/*
 * EFogType.h
 *
 *  Created on: Oct 26, 2012
 *      Author: gregorytkach
 */

#ifndef EFOGTYPE_H_
#define EFOGTYPE_H_

namespace irrgame
{
	namespace video
	{
		//! Enum for the types of fog distributions to choose from
		enum EFogType
		{
			EFT_FOG_EXP = 0, EFT_FOG_LINEAR, EFT_FOG_EXP2
		};

		const c8* const FogTypeNames[] =
		{ "FogExp", "FogLinear", "FogExp2", 0 };

	}  // namespace video

}  // namespace irrgame

#endif /* EFOGTYPE_H_ */
