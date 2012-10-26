/*
 * EBlendFactor.h
 *
 *  Created on: Oct 26, 2012
 *      Author: gregorytkach
 */

#ifndef EBLENDFACTOR_H_
#define EBLENDFACTOR_H_

namespace irrgame
{

	namespace video
	{

		//! Flag for EMT_ONETEXTURE_BLEND, ( BlendFactor ) BlendFunc = source * sourceFactor + dest * destFactor
		enum E_BLEND_FACTOR
		{
			EBF_ZERO = 0,		//!< src & dest	(0, 0, 0, 0)
			EBF_ONE,			//!< src & dest	(1, 1, 1, 1)
			EBF_DST_COLOR, 			//!< src	(destR, destG, destB, destA)
			EBF_ONE_MINUS_DST_COLOR, //!< src	(1-destR, 1-destG, 1-destB, 1-destA)
			EBF_SRC_COLOR,			//!< dest	(srcR, srcG, srcB, srcA)
			EBF_ONE_MINUS_SRC_COLOR, //!< dest	(1-srcR, 1-srcG, 1-srcB, 1-srcA)
			EBF_SRC_ALPHA,			//!< src & dest	(srcA, srcA, srcA, srcA)
			EBF_ONE_MINUS_SRC_ALPHA,//!< src & dest	(1-srcA, 1-srcA, 1-srcA, 1-srcA)
			EBF_DST_ALPHA,			//!< src & dest	(destA, destA, destA, destA)
			EBF_ONE_MINUS_DST_ALPHA,//!< src & dest	(1-destA, 1-destA, 1-destA, 1-destA)
			EBF_SRC_ALPHA_SATURATE	//!< src	(min(srcA, 1-destA), idem, ...)
		};

	}  // namespace video

}  // namespace irrgame

#endif /* EBLENDFACTOR_H_ */
