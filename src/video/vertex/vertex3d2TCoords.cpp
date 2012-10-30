/*
 * S3DVertex2TCoords.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: gregorytkach
 */

#include "video/vertex/vertex3d2TCoords.h"

namespace irrgame
{

	namespace video
	{

		//! default constructor
		vertex3d2TCoords::vertex3d2TCoords() :
				vertex3d()
		{
		}

		//! constructor with two different texture coords, but no normal
		vertex3d2TCoords::vertex3d2TCoords(f32 x, f32 y, f32 z, SColor c,
				f32 tu, f32 tv, f32 tu2, f32 tv2) :
				vertex3d(x, y, z, 0.0f, 0.0f, 0.0f, c, tu, tv), TCoords2(tu2,
						tv2)
		{
		}

		//! constructor with two different texture coords, but no normal
		vertex3d2TCoords::vertex3d2TCoords(const vector3df& pos, SColor color,
				const vector2df& tcoords, const vector2df& tcoords2) :
				vertex3d(pos, vector3df(), color, tcoords), TCoords2(tcoords2)
		{
		}

		//! constructor with all values
		vertex3d2TCoords::vertex3d2TCoords(const vector3df& pos,
				const vector3df& normal, const SColor& color,
				const vector2df& tcoords, const vector2df& tcoords2) :
				vertex3d(pos, normal, color, tcoords), TCoords2(tcoords2)
		{
		}

		//! constructor with all values
		vertex3d2TCoords::vertex3d2TCoords(f32 x, f32 y, f32 z, f32 nx, f32 ny,
				f32 nz, SColor c, f32 tu, f32 tv, f32 tu2, f32 tv2) :
				vertex3d(x, y, z, nx, ny, nz, c, tu, tv), TCoords2(tu2, tv2)
		{
		}

		//! constructor with the same texture coords and normal
		vertex3d2TCoords::vertex3d2TCoords(f32 x, f32 y, f32 z, f32 nx, f32 ny,
				f32 nz, SColor c, f32 tu, f32 tv) :
				vertex3d(x, y, z, nx, ny, nz, c, tu, tv), TCoords2(tu, tv)
		{
		}

		//! constructor with the same texture coords and normal
		vertex3d2TCoords::vertex3d2TCoords(const vector3df& pos,
				const vector3df& normal, SColor color, const vector2df& tcoords) :
				vertex3d(pos, normal, color, tcoords), TCoords2(tcoords)
		{
		}

		//! constructor from S3DVertex
		vertex3d2TCoords::vertex3d2TCoords(vertex3d& o) :
				vertex3d(o)
		{
		}

		E_VERTEX_TYPE vertex3d2TCoords::getType() const
		{
			return EVT_2TCOORDS;
		}

		/*
		 * Operators
		 */

		//! Equality operator
		bool vertex3d2TCoords::operator==(const vertex3d2TCoords& other) const
		{
			return ((static_cast<vertex3d>(*this) == other)
					&& (TCoords2 == other.TCoords2));
		}

		//! Inequality operator
		bool vertex3d2TCoords::operator!=(const vertex3d2TCoords& other) const
		{
			return ((static_cast<vertex3d>(*this) != other)
					|| (TCoords2 != other.TCoords2));
		}

		bool vertex3d2TCoords::operator<(const vertex3d2TCoords& other) const
		{
			return ((static_cast<vertex3d>(*this) < other)
					|| ((static_cast<vertex3d>(*this) == other)
							&& (TCoords2 < other.TCoords2)));
		}

	}  // namespace video

}  // namespace irrgame

