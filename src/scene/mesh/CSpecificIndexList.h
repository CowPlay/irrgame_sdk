///*
// * CSpecificIndexList.h
// *
// *  Created on: Nov 12, 2012
// *      Author: gregorytkach
// */
//
//#ifndef CSPECIFICINDEXLIST_H_
//#define CSPECIFICINDEXLIST_H_
//
//#include "IIndexList.h"
//
//namespace irrgame
//{
//	namespace scene
//	{
//		//TODO: write comments
//
//		template<class T>
//		class CSpecificIndexList: public IIndexList<T>
//		{
//			public:
//
//				//! Default constructor
//				CSpecificIndexList();
//
//				//! Destructor
//				virtual ~CSpecificIndexList();
//
//				virtual u32 stride() const;
//
//				virtual u32 size() const;
//
//				virtual void pushBack(const T &value);
//
//				virtual T& operator[](u32 index);
//
//				virtual T getLast();
//
//				virtual void setUsed(u32 usedNow);
//
//				virtual void reallocate(u32 newSize);
//
//				virtual u32 allocatedSize() const;
//
//				virtual void* pointer();
//
//				virtual video::EIndexType getType() const;
//
//			public:
//				core::array<T> Indices;
//		};
//
//		template<class T>
//		CSpecificIndexList<T>::CSpecificIndexList()
//		{
//		}
//
//		template<class T>
//		CSpecificIndexList<T>::~CSpecificIndexList()
//		{
//		}
//
//		template<class T>
//		virtual u32 CSpecificIndexList<T>::stride() const
//		{
//			return sizeof(T);
//		}
//
//		template<class T>
//		virtual u32 CSpecificIndexList<T>::size() const
//		{
//			return Indices.size();
//		}
//
//		template<class T>
//		virtual void CSpecificIndexList<T>::pushBack(const T &value)
//		{
//			Indices.pushBack(value);
//		}
//
//		template<class T>
//		virtual T& CSpecificIndexList<T>::operator[](u32 index)
//		{
//			return Indices[index];
//		}
//
//		template<class T>
//		virtual T CSpecificIndexList<T>::getLast()
//		{
//			return Indices.getLast();
//		}
//
//		template<class T>
//		virtual void CSpecificIndexList<T>::setUsed(u32 usedNow)
//		{
//			Indices.setUsed(usedNow);
//		}
//
//		template<class T>
//		virtual void CSpecificIndexList<T>::reallocate(u32 newSize)
//		{
//			Indices.reallocate(newSize);
//		}
//
//		template<class T>
//		virtual u32 CSpecificIndexList<T>::allocatedSize() const
//		{
//			return Indices.allocatedSize();
//		}
//
//		template<class T>
//		virtual void* CSpecificIndexList<T>::pointer()
//		{
//			return Indices.pointer();
//		}
//
//		template<class T>
//		virtual video::EIndexType getType() const
//		{
//			video::EIndexType result;
//
//			if (sizeof(T) == sizeof(u16))
//			{
//				result = video::EIT_16BIT;
//			}
//			else
//			{
//				result = video::EIT_32BIT;
//			}
//
//			return result;
//		}
//
//	} /* namespace scene */
//} /* namespace irrgame */
//#endif /* CSPECIFICINDEXLIST_H_ */
