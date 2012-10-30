/*
 * EVertexType.h
 *
 *  Created on: Oct 29, 2012
 *      Author: gregorytkach
 */

#ifndef EVERTEXTYPE_H_
#define EVERTEXTYPE_H_

namespace irrgame
{
	namespace video
	{
		//! Enumeration for all vertex types there are.
		enum E_VERTEX_TYPE
		{
			//! Standard vertex type used by the Irrlicht engine, video::S3DVertex.
			EVT_STANDARD = 0,

			//! Vertex with two texture coordinates, video::S3DVertex2TCoords.
			/** Usually used for geometry with lightmaps or other special materials. */
			EVT_2TCOORDS,

			//! Vertex with a tangent and binormal vector, video::S3DVertexTangents.
			/** Usually used for tangent space normal mapping. */
			EVT_TANGENTS,

			//! Not used
			EVT_COUNT
		};

		//! Array holding the built in vertex type names
		const char* const sBuiltInVertexTypeNames[] =
		{ "standard", "2tcoords", "tangents", 0 };

	}  // namespace video
}  // namespace irrgame

#endif /* EVERTEXTYPE_H_ */
