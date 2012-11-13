// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef IMESH_H_INCLUDED__
#define IMESH_H_INCLUDED__

#include "core/engine/IReferenceCounted.h"
//#include "SMaterial.h"
//#include "EHardwareBufferFlags.h"
//
namespace irrgame
{

	namespace io
	{
		class IReadFile;
	}  // namespace io

	namespace scene
	{
		//! Class which holds the geometry of an object.
		/** An IMesh is nothing more than a collection of some mesh buffers
		 (IMeshBuffer). SMesh is a simple implementation of an IMesh.
		 A mesh is usually added to an IMeshSceneNode in order to be rendered.
		 */
		class IMesh: public IReferenceCounted
		{
			public:

				//! Mesh creator
				static IMesh* createMesh(io::IReadFile* file);

			public:

				//! Destructor
				virtual ~IMesh()
				{
				}

				//! Get the amount of mesh buffers.
				/** \return Amount of mesh buffers (IMeshBuffer) in this mesh. */
				virtual u32 getMeshBufferCount() const = 0;
		};
	} // end namespace scene
} // end namespace irrgame

#endif
//		class IMeshBuffer;
//

//			public:
//

//
//				//! Get pointer to a mesh buffer.
//				/** \param nr: Zero based index of the mesh buffer. The maximum value is
//				 getMeshBufferCount() - 1;
//				 \return Pointer to the mesh buffer or 0 if there is no such
//				 mesh buffer. */
//				virtual IMeshBuffer* getMeshBuffer(u32 nr) const = 0;
//
//				//! Get pointer to a mesh buffer which fits a material
//				/** \param material: material to search for
//				 \return Pointer to the mesh buffer or 0 if there is no such
//				 mesh buffer. */
//				virtual IMeshBuffer* getMeshBuffer(
//						const video::SMaterial &material) const = 0;
//
//				//! Get an axis aligned bounding box of the mesh.
//				/** \return Bounding box of this mesh. */
//				virtual const aabbox3df& getBoundingBox() const = 0;
//
//				//! Set user-defined axis aligned bounding box
//				/** \param box New bounding box to use for the mesh. */
//				virtual void setBoundingBox(const core::aabbox3df& value) = 0;
//
//				//! Sets a flag of all contained materials to a new value.
//				/** \param flag: Flag to set in all materials.
//				 \param newvalue: New value to set in all materials. */
//				virtual void setMaterialFlag(video::E_MATERIAL_FLAG flag,
//						bool newvalue) = 0;
//
//				//! Set the hardware mapping hint
//				/** This methods allows to define optimization hints for the
//				 hardware. This enables, e.g., the use of hardware buffers on
//				 pltforms that support this feature. This can lead to noticeable
//				 performance gains. */
//				virtual void setHardwareMappingHint(
//						E_HARDWARE_MAPPING newMappingHint,
//						E_BUFFER_TYPE buffer = EBT_VERTEX_AND_INDEX) = 0;
//
//				//! Flag the meshbuffer as changed, reloads hardware buffers
//				/** This method has to be called every time the vertices or
//				 indices have changed. Otherwise, changes won't be updated
//				 on the GPU in the next render cycle. */
//				virtual void setDirty(E_BUFFER_TYPE buffer =
//						EBT_VERTEX_AND_INDEX) = 0;
//		};
//

//
