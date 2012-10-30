// Copyright (C) 2002-2010 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef	VERTEX3D_H_INCLUDED_
#define VERTEX3D_H_INCLUDED_

#include "EVertexType.h"
#include "video/color/SColor.h"
#include "core/shapes/vector2d.h"
#include "core/shapes/vector3d.h"

namespace irrgame
{
	namespace video
	{
		//! Standard vertex used by the Irrlicht engine.
		class vertex3d
		{
				/*
				 * Static methods
				 */
			public:

				static u32 getVertexPitchByType(E_VERTEX_TYPE vertexType);

				/*
				 * Instance methods
				 */

			public:
				//! Default constructor
				vertex3d();

				//! Constructor
				vertex3d(f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz, SColor c,
						f32 tu, f32 tv);

				//! Constructor
				vertex3d(const vector3df& pos, const vector3df& normal,
						SColor color, const vector2df& tcoords);

				E_VERTEX_TYPE getType() const;

				/*
				 * Operators
				 */

				bool operator==(const vertex3d& other) const;

				bool operator!=(const vertex3d& other) const;

				bool operator<(const vertex3d& other) const;

			public:
				//! Position
				vector3df Pos;

				//! Normal vector
				vector3df Normal;

				//! Color
				SColor Color;

				//! Texture coordinates
				vector2df TCoords;
		};

	} // end namespace video
} // end namespace irrgame

#endif //VERTEX3D_H_INCLUDED_
