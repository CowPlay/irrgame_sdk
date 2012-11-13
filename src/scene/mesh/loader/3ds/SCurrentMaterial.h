/*
 * SCurrentMaterial.h
 *
 *  Created on: Nov 12, 2012
 *      Author: gregorytkach
 */

#ifndef SCURRENTMATERIAL_H_
#define SCURRENTMATERIAL_H_

#include "compileConfig.h"
#include "video/material/SMaterial.h"

namespace irrgame
{
	namespace scene
	{
		struct SCurrentMaterial
		{
			public:
				void clear();

			public:

				video::SMaterial Material;
				core::stringc Name;
				core::stringc Filename[5];
				f32 Strength[5];
		};

		inline void SCurrentMaterial::clear()
		{
			Material = video::SMaterial();
			Name = "";
			Filename[0] = "";
			Filename[1] = "";
			Filename[2] = "";
			Filename[3] = "";
			Filename[4] = "";
			Strength[0] = 0.f;
			Strength[1] = 0.f;
			Strength[2] = 0.f;
			Strength[3] = 0.f;
			Strength[4] = 0.f;
		}

	}  // namespace scene
}  // namespace irrgame

#endif /* SCURRENTMATERIAL_H_ */
