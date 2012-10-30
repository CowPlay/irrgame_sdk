/*
 * S3DVertexTangents.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: gregorytkach
 */

#include "video/vertex/vertex3dTangents.h"

namespace irrgame
{
	namespace video
	{

		//! Default constructor
		vertex3dTangents::vertex3dTangents() :
				vertex3d()
		{
		}

		//! Constructor
		vertex3dTangents::vertex3dTangents(f32 x, f32 y, f32 z, f32 nx, f32 ny,
				f32 nz, SColor c, f32 tu, f32 tv, f32 tanx, f32 tany, f32 tanz,
				f32 bx, f32 by, f32 bz) :
				vertex3d(x, y, z, nx, ny, nz, c, tu, tv), Tangent(tanx, tany,
						tanz), Binormal(bx, by, bz)
		{
		}

		//! constructor
		vertex3dTangents::vertex3dTangents(const vector3df& pos, SColor c,
				const vector2df& tcoords) :
				vertex3d(pos, vector3df(), c, tcoords)
		{
		}

		//! constructor
		vertex3dTangents::vertex3dTangents(const vector3df& pos,
				const vector3df& normal, SColor c, const vector2df& tcoords,
				const vector3df& tangent, const vector3df& binormal) :
				vertex3d(pos, normal, c, tcoords), Tangent(tangent), Binormal(
						binormal)
		{
		}

		E_VERTEX_TYPE vertex3dTangents::getType() const
		{
			return EVT_TANGENTS;
		}

		/*
		 * Operators
		 */

		bool vertex3dTangents::operator==(const vertex3dTangents& other) const
		{
			return ((static_cast<vertex3d>(*this) == other)
					&& (Tangent == other.Tangent)
					&& (Binormal == other.Binormal));
		}

		bool vertex3dTangents::operator!=(const vertex3dTangents& other) const
		{
			return ((static_cast<vertex3d>(*this) != other)
					|| (Tangent != other.Tangent)
					|| (Binormal != other.Binormal));
		}

		bool vertex3dTangents::operator<(const vertex3dTangents& other) const
		{
			return ((static_cast<vertex3d>(*this) < other)
					|| ((static_cast<vertex3d>(*this) == other)
							&& (Tangent < other.Tangent))
					|| ((static_cast<vertex3d>(*this) == other)
							&& (Tangent == other.Tangent)
							&& (Binormal < other.Binormal)));
		}

	}  // namespace video

}  // namespace irrgame

