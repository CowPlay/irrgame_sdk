///*
// * SMesh.cpp
// *
// *  Created on: Nov 12, 2012
// *      Author: gregorytkach
// */
//
//#include "scene/mesh/SMesh.h"
//
//namespace irrgame
//{
//	namespace scene
//	{
//		//! Default constructor
//		SMesh::SMesh()
//		{
//#ifdef DEBUG
//			setDebugName("SMesh");
//#endif
//		}
//
//		//! Destructor
//		SMesh::~SMesh()
//		{
//			// drop buffers
//			for (u32 i = 0; i < MeshBuffers.size(); ++i)
//			{
//				MeshBuffers[i]->drop();
//			}
//		}
//
//		//! returns amount of mesh buffers.
//		u32 SMesh::getMeshBufferCount() const
//		{
//			return MeshBuffers.size();
//		}
//
//		//! returns pointer to a mesh buffer
//		IMeshBuffer* SMesh::getMeshBuffer(u32 nr) const
//		{
//			return MeshBuffers[nr];
//		}
//
//		//! returns a meshbuffer which fits a material
//		IMeshBuffer* SMesh::getMeshBuffer(
//				const video::SMaterial & material) const
//		{
//			IMeshBuffer* result = 0;
//
//			for (s32 i = (s32) MeshBuffers.size() - 1; i >= 0; --i)
//			{
//				if (material == MeshBuffers[i]->getMaterial())
//				{
//					result = MeshBuffers[i];
//					break;
//				}
//			}
//
//			return result;
//		}
//
//		//! returns an axis aligned bounding box
//		const aabbox3df& SMesh::getBoundingBox() const
//		{
//			return BoundingBox;
//		}
//
//		//! set user axis aligned bounding box
//		void SMesh::setBoundingBox(const aabbox3df& box)
//		{
//			BoundingBox = box;
//		}
//
//		//! recalculates the bounding box
//		void SMesh::recalculateBoundingBox()
//		{
//			if (MeshBuffers.size())
//			{
//				BoundingBox = MeshBuffers[0]->getBoundingBox();
//				for (u32 i = 1; i < MeshBuffers.size(); ++i)
//				{
//					BoundingBox.addInternalBox(
//							MeshBuffers[i]->getBoundingBox());
//				}
//			}
//			else
//			{
//				BoundingBox.reset(0.0f, 0.0f, 0.0f);
//			}
//		}
//
//		//! adds a MeshBuffer
//		void SMesh::addMeshBuffer(IMeshBuffer* value)
//		{
//			IRR_ASSERT(value);
//
//			value->grab();
//			MeshBuffers.pushBack(value);
//		}
//
//		//! sets a flag of all contained materials to a new value
//		void SMesh::setMaterialFlag(video::E_MATERIAL_FLAG flag, bool newvalue)
//		{
//			for (u32 i = 0; i < MeshBuffers.size(); ++i)
//			{
//				MeshBuffers[i]->getMaterial().setFlag(flag, newvalue);
//			}
//		}
//
//		//! set the hardware mapping hint, for driver
//		void SMesh::setHardwareMappingHint(E_HARDWARE_MAPPING newMappingHint,
//				E_BUFFER_TYPE buffer)
//		{
//			for (u32 i = 0; i < MeshBuffers.size(); ++i)
//			{
//				MeshBuffers[i]->setHardwareMappingHint(newMappingHint, buffer);
//			}
//		}
//
//		//! flags the meshbuffer as changed, reloads hardware buffers
//		void SMesh::setDirty(E_BUFFER_TYPE buffer)
//		{
//			for (u32 i = 0; i < MeshBuffers.size(); ++i)
//			{
//				MeshBuffers[i]->setDirty(buffer);
//			}
//		}
//
//	}  // namespace scene
//}  // namespace irrgame
//
