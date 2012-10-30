/*
 * S3DVertexTangents.h
 *
 *  Created on: Oct 29, 2012
 *      Author: gregorytkach
 */

#ifndef S3DVERTEXTANGENTS_H_
#define S3DVERTEXTANGENTS_H_

#include "vertex3d.h"

namespace irrgame
{
	namespace video
	{
		//! Vertex with a tangent and binormal vector.
		/** Usually used for tangent space normal mapping. */
		class vertex3dTangents: public vertex3d
		{
				//! Default constructor
				vertex3dTangents();

				//! Constructor
				vertex3dTangents(f32 x, f32 y, f32 z, f32 nx = 0.0f, f32 ny =
						0.0f, f32 nz = 0.0f, SColor c = 0xFFFFFFFF, f32 tu =
						0.0f, f32 tv = 0.0f, f32 tanx = 0.0f, f32 tany = 0.0f,
						f32 tanz = 0.0f, f32 bx = 0.0f, f32 by = 0.0f, f32 bz =
								0.0f);
				//! constructor
				vertex3dTangents(const vector3df& pos, SColor c,
						const vector2df& tcoords);

				//! constructor
				vertex3dTangents(const vector3df& pos, const vector3df& normal,
						SColor c, const vector2df& tcoords,
						const vector3df& tangent = vector3df(),
						const vector3df& binormal = vector3df());

				E_VERTEX_TYPE getType() const;

				/*
				 * Operators
				 */

				bool operator==(const vertex3dTangents& other) const;

				bool operator!=(const vertex3dTangents& other) const;

				bool operator<(const vertex3dTangents& other) const;

			public:
				//! Tangent vector along the x-axis of the texture
				vector3df Tangent;

				//! Binormal vector (tangent x normal)
				vector3df Binormal;
		};
	}  // namespace video

}  // namespace irrgame

#endif /* S3DVERTEXTANGENTS_H_ */
