//// Copyright (C) 2008-2009 Nikolaus Gebhardt
//// This file is part of the "Irrlicht Engine".
//// For conditions of distribution and use, see copyright notice in irrlicht.h
//
//#ifndef IINDEX_BUFFER_H_INCLUDED_
//#define IINDEX_BUFFER_H_INCLUDED_
//
//#include "core/engine/IReferenceCounted.h"
//#include "core/collections/ICollection.h"
//#include "video/vertex/EIndexType.h"
//
//namespace irrgame
//{
//	namespace scene
//	{
//
//		//TODO: refactor and make comments
////		template<class T>
//		class IIndexBuffer: public core::ICollection<u32>
//		{
//			public:
//
//				//! Destructor
//				virtual ~IIndexBuffer()
//				{
//				}
//
//				virtual void* getData() = 0;
//
//				virtual video::EIndexType getType() const = 0;
//
//				virtual void setType(video::EIndexType value) = 0;
//
//				virtual u32 stride() const = 0;
//
//				virtual void setUsed(u32 usedNow) = 0;
//
//				virtual void reallocate(u32 new_size) = 0;
//
//				virtual u32 allocatedSize() const = 0;
//
//				virtual void* pointer() = 0;
//
//				//! get the current hardware mapping hint
//				virtual E_HARDWARE_MAPPING getHardwareMappingHint() const = 0;
//
//				//! set the hardware mapping hint, for driver
//				virtual void setHardwareMappingHint(
//						E_HARDWARE_MAPPING NewMappingHint) = 0;
//
//				//! flags the meshbuffer as changed, reloads hardware buffers
//				virtual void setDirty() = 0;
//
//				//! Get the currently used ID for identification of changes.
//				/** This shouldn't be used for anything outside the VideoDriver. */
//				virtual u32 getChangedID() const = 0;
//		};
//
//	} // end namespace scene
//} // end namespace irrgame
//
//#endif /* IINDEX_BUFFER_H_INCLUDED_ */
//
