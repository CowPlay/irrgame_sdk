//// Copyright (C) 2008-2009 Nikolaus Gebhardt
//// This file is part of the "Irrlicht Engine".
//// For conditions of distribution and use, see copyright notice in irrlicht.h
//
//#ifndef __C_INDEX_BUFFER_H_INCLUDED__
//#define __C_INDEX_BUFFER_H_INCLUDED__
//
//#include "IIndexBuffer.h"
//
//namespace irr
//{
//	namespace scene
//	{
//
//		class CIndexBuffer: public IIndexBuffer
//		{
//			public:
//				IIndexList *Indices;
//
//				//! Default constructor
//				CIndexBuffer(video::E_INDEX_TYPE IndexType) :
//						Indices(0), MappingHint(EHM_NEVER), ChangedID(1)
//				{
//					setType(IndexType);
//				}
//
//				//! Copy constructor
//				CIndexBuffer(const IIndexBuffer& IndexBufferCopy) :
//						Indices(0), MappingHint(EHM_NEVER), ChangedID(1)
//				{
//					setType(IndexBufferCopy.getType());
//					reallocate(IndexBufferCopy.size());
//
//					for (u32 n = 0; n < IndexBufferCopy.size(); ++n)
//					{
//						pushBack(IndexBufferCopy[n]);
//					}
//				}
//
//				//! Destructor
//				virtual ~CIndexBuffer()
//				{
//					delete Indices;
//				}
//
//				virtual void setType(video::EIndexType IndexType)
//				{
//					IIndexList *NewIndices = 0;
//
//					switch (IndexType)
//					{
//						case video::EIT_16BIT:
//						{
//							NewIndices = new CSpecificIndexList<u16>;
//							break;
//						}
//						case video::EIT_32BIT:
//						{
//							NewIndices = new CSpecificIndexList<u32>;
//							break;
//						}
//						default:
//						{
//							//Not implemented
//							IRR_ASSERT(false);
//							break;
//						}
//					}
//
//					if (Indices)
//					{
//						NewIndices->reallocate(Indices->size());
//
//						for (u32 n = 0; n < Indices->size(); ++n)
//						{
//							NewIndices->pushBack((*Indices)[n]);
//						}
//
//						delete Indices;
//					}
//
//					Indices = NewIndices;
//				}
//
//				virtual void* getData()
//				{
//					return Indices->pointer();
//				}
//
//				virtual video::EIndexType getType() const
//				{
//					return Indices->getType();
//				}
//
//				virtual u32 stride() const
//				{
//					return Indices->stride();
//				}
//
//				virtual u32 size() const
//				{
//					return Indices->size();
//				}
//
//				virtual void pushBack(const u32 &element)
//				{
//					Indices->pushBack(element);
//				}
//
//				virtual u32 operator[](u32 index) const
//				{
//					return (*Indices)[index];
//				}
//
//				virtual u32 getLast()
//				{
//					return Indices->getLast();
//				}
//
//				virtual void setValue(u32 index, u32 value)
//				{
//					Indices->setValue(index, value);
//				}
//
//				virtual void setUsed(u32 usedNow)
//				{
//					Indices->setUsed(usedNow);
//				}
//
//				virtual void reallocate(u32 new_size)
//				{
//					Indices->reallocate(new_size);
//				}
//
//				virtual u32 allocatedSize() const
//				{
//					return Indices->allocatedSize();
//				}
//
//				virtual void* pointer()
//				{
//					return Indices->pointer();
//				}
//
//				//! get the current hardware mapping hint
//				virtual E_HARDWARE_MAPPING getHardwareMappingHint() const
//				{
//					return MappingHint;
//				}
//
//				//! set the hardware mapping hint, for driver
//				virtual void setHardwareMappingHint(
//						E_HARDWARE_MAPPING NewMappingHint)
//				{
//					MappingHint = NewMappingHint;
//				}
//
//				//! flags the mesh as changed, reloads hardware buffers
//				virtual void setDirty()
//				{
//					++ChangedID;
//				}
//
//				//! Get the currently used ID for identification of changes.
//				/** This shouldn't be used for anything outside the VideoDriver. */
//				virtual u32 getChangedID() const
//				{
//					return ChangedID;
//				}
//
//			private:
//
//				E_HARDWARE_MAPPING MappingHint;
//				u32 ChangedID;
//		};
//
//	} // end namespace scene
//} // end namespace irr
//
//#endif
//
