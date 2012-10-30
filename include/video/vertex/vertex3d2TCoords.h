/*
 * S3DVertex2TCoords.h
 *
 *  Created on: Oct 29, 2012
 *      Author: gregorytkach
 */

#ifndef VERTEX3D2TCOORDS_H_
#define VERTEX3D2TCOORDS_H_

#include "vertex3d.h"

namespace irrgame
{
	namespace video
	{

		//! Vertex with two texture coordinates.
		/** Usually used for geometry with lightmaps
		 or other special materials.
		 */
		class vertex3d2TCoords: public vertex3d
		{
			public:
				//! default constructor
				vertex3d2TCoords();

				//! constructor with two different texture coords, but no normal
				vertex3d2TCoords(f32 x, f32 y, f32 z, SColor c, f32 tu, f32 tv,
						f32 tu2, f32 tv2);

				//! constructor with two different texture coords, but no normal
				vertex3d2TCoords(const vector3df& pos, SColor color,
						const vector2df& tcoords, const vector2df& tcoords2);

				//! constructor with all values
				vertex3d2TCoords(const vector3df& pos, const vector3df& normal,
						const SColor& color, const vector2df& tcoords,
						const vector2df& tcoords2);

				//! constructor with all values
				vertex3d2TCoords(f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz,
						SColor c, f32 tu, f32 tv, f32 tu2, f32 tv2);

				//! constructor with the same texture coords and normal
				vertex3d2TCoords(f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz,
						SColor c, f32 tu, f32 tv);

				//! constructor with the same texture coords and normal
				vertex3d2TCoords(const vector3df& pos, const vector3df& normal,
						SColor color, const vector2df& tcoords);

				//! constructor from S3DVertex
				vertex3d2TCoords(vertex3d& o);

				E_VERTEX_TYPE getType() const;

				/*
				 * Operators
				 */

				//! Equality operator
				bool operator==(const vertex3d2TCoords& other) const;

				//! Inequality operator
				bool operator!=(const vertex3d2TCoords& other) const;

				bool operator<(const vertex3d2TCoords& other) const;

			public:

				//! Second set of texture coordinates
				core::vector2d<f32> TCoords2;
		};

	}  // namespace video
}  // namespace irrgame

#endif /* VERTEX3D2TCOORDS_H_ */
