///*
// * IIndexList.h
// *
// *  Created on: Nov 12, 2012
// *      Author: gregorytkach
// */
//
//#ifndef IINDEXLIST_H_
//#define IINDEXLIST_H_
//
//#include "core/collections/ICollection.h"
//
//namespace irrgame
//{
//	namespace scene
//	{
//		template<class T>
//		class IIndexList: public core::ICollection<T>
//		{
//			public:
//				//! Destructor
//				virtual ~IIndexList()
//				{
//				}
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
//				virtual video::EIndexType getType() const = 0;
//		};
//	}  // namespace scene
//}  // namespace irrgame
//
//#endif /* IINDEXLIST_H_ */
