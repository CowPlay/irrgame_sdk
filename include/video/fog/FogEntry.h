/*
 * SFog.h
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#ifndef SFOG_H_
#define SFOG_H_

#include "EFogType.h"
#include "video/color/SColor.h"
#include "core/engine/IReferenceCounted.h"

namespace irrgame
{
	namespace video
	{

		class FogEntry: public IReferenceCounted
		{
			public:

				//! Default constructor
				FogEntry() :
						Color(SColor(0, 255, 255, 255)), Type(EFT_FOG_LINEAR), Start(
								50.0f), End(100.0f), Density(0.01f), PixelFog(
								false), RangeFog(false)
				{
				}

				//! Destructor
				virtual ~FogEntry()
				{
				}

			public:
				// Color of the fog
				SColor Color;
				// Type of fog used
				EFogType Type;
				// Only used in linear fog mode (linearFog=true). Specifies where fog starts.
				f32 Start;
				// Only used in linear fog mode (linearFog=true). Specifies where fog ends.
				f32 End;
				// density Only used in exponential fog mode (linearFog=false). Must be a value between 0 and 1.
				f32 Density;
				// Set this to false for vertex fog, and true if you want per-pixel fog.
				bool PixelFog;
				// Set this to true to enable range-based vertex fog. The distance from the viewer is used to compute the fog,
				// not the z-coordinate. This is better, but slower. This might not be available with all drivers and fog settings.
				bool RangeFog;
		};

	}
// namespace video

}// namespace irrgame

#endif /* SFOG_H_ */
