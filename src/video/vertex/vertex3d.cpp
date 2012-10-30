/*
 * vertex.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: gregorytkach
 */

#include "video/vertex/vertex3d.h"
#include "video/vertex/vertex3d2TCoords.h"
#include "video/vertex/vertex3dTangents.h"

namespace irrgame
{
	namespace video
	{
		u32 vertex3d::getVertexPitchByType(E_VERTEX_TYPE vertexType)
		{
			u32 result = 0;

			switch (vertexType)
			{
				case EVT_2TCOORDS:
				{
					result = sizeof(vertex3d2TCoords);
					break;
				}
				case EVT_TANGENTS:
				{
					result = sizeof(vertex3dTangents);
					break;
				}
				case EVT_STANDARD:
				{
					result = sizeof(vertex3d);
					break;
				}
				default:
				{
					//not implement
					IRR_ASSERT(false);
					break;
				}
			}

			return result;
		}

		//! Default constructor
		vertex3d::vertex3d()
		{
		}

		//! Constructor
		vertex3d::vertex3d(f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz,
				SColor c, f32 tu, f32 tv) :
				Pos(x, y, z), Normal(nx, ny, nz), Color(c), TCoords(tu, tv)
		{
		}

		//! Constructor
		vertex3d::vertex3d(const vector3df& pos, const vector3df& normal,
				SColor color, const vector2df& tcoords) :
				Pos(pos), Normal(normal), Color(color), TCoords(tcoords)
		{
		}

		E_VERTEX_TYPE vertex3d::getType() const
		{
			return EVT_STANDARD;
		}

		/*
		 * Operators
		 */

		bool vertex3d::operator==(const vertex3d& other) const
		{
			return ((Pos == other.Pos) && (Normal == other.Normal)
					&& (Color == other.Color) && (TCoords == other.TCoords));
		}

		bool vertex3d::operator!=(const vertex3d& other) const
		{
			return ((Pos != other.Pos) || (Normal != other.Normal)
					|| (Color != other.Color) || (TCoords != other.TCoords));
		}

		bool vertex3d::operator<(const vertex3d& other) const
		{
			return ((Pos < other.Pos)
					|| ((Pos == other.Pos) && (Normal < other.Normal))
					|| ((Pos == other.Pos) && (Normal == other.Normal)
							&& (Color < other.Color))
					|| ((Pos == other.Pos) && (Normal == other.Normal)
							&& (Color == other.Color)
							&& (TCoords < other.TCoords)));
		}

	}  // namespace video
}  // namespace irrgame

