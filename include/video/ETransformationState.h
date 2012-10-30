/*
 * ETransformationState.h
 *
 *  Created on: Oct 25, 2012
 *      Author: gregorytkach
 */

#ifndef ETRANSFORMATIONSTATE_H_
#define ETRANSFORMATIONSTATE_H_

namespace irrgame
{
	namespace video
	{
		//! enumeration for geometry transformation states
		enum ETransformationState
		{
			//! View transformation
			ETS_VIEW = 0,
			//! World transformation
			ETS_WORLD,
			//! Projection transformation
			ETS_PROJECTION,
			//! Texture transformation
			ETS_TEXTURE_0,
			//! Texture transformation
			ETS_TEXTURE_1,
			//! Texture transformation
			ETS_TEXTURE_2,
			//! Texture transformation
			ETS_TEXTURE_3,
			//! Texture transformation
			ETS_TEXTURE_4,
			//! Texture transformation
			ETS_TEXTURE_5,
			//! Texture transformation
			ETS_TEXTURE_6,
			//! Texture transformation
			ETS_TEXTURE_7,

			//! Not used
			ETS_COUNT
		};

	}  // namespace video

}  // namespace irrgame

#endif /* ETRANSFORMATIONSTATE_H_ */
