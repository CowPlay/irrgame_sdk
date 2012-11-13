/*
 * CConstIterator.h
 *
 *  Created on: Sep 3, 2012
 *      Author: gregorytkach
 */

#ifndef ITERATORS_H_
#define ITERATORS_H_

#include "core/collections/list/SKListNode.h"

namespace irrgame
{
	namespace core
	{
		template<class T>
		class list;

		template<class T>
		class CConstIterator;

		template<class T>
		class CIterator;

		//! List iterator.
		template<class T>
		class CIterator
		{
			public:
				//! Default constructor
				CIterator();

				//! Explicit constructor
				explicit CIterator(SKListNode<T>* begin);

				/*
				 * Operators
				 */

				CIterator<T>& operator ++();
				CIterator& operator --();
				CIterator& operator -=(s32 num) const;
				CIterator& operator +=(s32 num);

				CIterator operator ++(s32);
				CIterator operator --(s32);
				CIterator operator +(s32 num) const;
				CIterator operator -(s32 num) const;

				bool operator ==(const CIterator& other) const;
				bool operator !=(const CIterator& other) const;
				bool operator ==(const CConstIterator<T>& other) const;
				bool operator !=(const CConstIterator<T>& other) const;

				T& operator *();
				T* operator ->();

			public:
				//! For internal use. Please do not use
				SKListNode<T>* Current;
		};

		//! List iterator for const access.
		template<class T>
		class CConstIterator
		{
			public:

				//! Default constructor
				CConstIterator();

				//! Constructor from another iterator
				CConstIterator(const CIterator<T>& iter);

				//! Explicit constructor
				explicit CConstIterator(SKListNode<T>* begin);

				/*
				 * Operators
				 */

				CConstIterator<T>& operator +=(s32 num);
				CConstIterator<T>& operator -=(s32 num) const;
				CConstIterator<T>& operator ++();
				CConstIterator<T>& operator --();
				CConstIterator<T>& operator =(const CIterator<T> & iterator);

				CConstIterator operator ++(s32);
				CConstIterator operator --(s32);
				CConstIterator operator +(s32 num) const;
				CConstIterator operator -(s32 num) const;

				bool operator ==(const CConstIterator& other) const;
				bool operator !=(const CConstIterator& other) const;
				bool operator ==(const CIterator<T>& other) const;
				bool operator !=(const CIterator<T>& other) const;

				const T& operator *();
				const T* operator ->();

			public:
				//! For internal use. Please do not use
				SKListNode<T>* Current;
		};

		//!-------- Iterator realization

		//! Default constructor
		template<class T>
		inline CIterator<T>::CIterator() :
				Current(0)
		{
		}

		//! Explicit constructor
		template<class T>
		inline CIterator<T>::CIterator(SKListNode<T>* begin) :
				Current(begin)
		{
		}

		template<class T>
		inline CIterator<T>& CIterator<T>::operator ++()
		{
			Current = Current->Next;
			return *this;
		}

		template<class T>
		inline CIterator<T>& CIterator<T>::operator --()
		{
			Current = Current->Prev;
			return *this;
		}

		template<class T>
		inline CIterator<T>& CIterator<T>::operator -=(s32 num) const
		{
			return (*this) += (-num);
		}

		template<class T>
		inline CIterator<T>& CIterator<T>::operator +=(s32 num)
		{
			if (num > 0)
			{
				while (num-- && this->Current != 0)
					++(*this);
			}
			else
			{
				while (num++ && this->Current != 0)
					--(*this);
			}
			return *this;
		}

		template<class T>
		inline CIterator<T> CIterator<T>::operator ++(s32)
		{
			CIterator<T> tmp = *this;
			Current = Current->Next;
			return tmp;
		}

		template<class T>
		inline CIterator<T> CIterator<T>::operator --(s32)
		{
			CIterator<T> tmp = *this;
			Current = Current->Prev;
			return tmp;
		}

		template<class T>
		inline CIterator<T> CIterator<T>::operator +(s32 num) const
		{
			CIterator<T> tmp = *this;
			return tmp += num;
		}

		template<class T>
		inline CIterator<T> CIterator<T>::operator -(s32 num) const
		{
			return (*this) + (-num);
		}

		template<class T>
		inline bool CIterator<T>::operator ==(const CIterator<T>& other) const
		{
			return Current == other.Current;
		}

		template<class T>
		inline bool CIterator<T>::operator !=(const CIterator<T>& other) const
		{
			return Current != other.Current;
		}

		template<class T>
		inline bool CIterator<T>::operator ==(
				const CConstIterator<T>& other) const
		{
			return Current == other.Current;
		}

		template<class T>
		inline bool CIterator<T>::operator !=(
				const CConstIterator<T>& other) const
		{
			return Current != other.Current;
		}

		template<class T>
		inline T& CIterator<T>::operator *()
		{
			return Current->Element;
		}

		template<class T>
		inline T* CIterator<T>::operator ->()
		{
			return &Current->Element;
		}

		//!--------- CConstIterator realization

		//! Default constructor
		template<class T>
		inline CConstIterator<T>::CConstIterator() :
				Current(0)
		{
		}

		//! Constructor from another iterator
		template<class T>
		inline CConstIterator<T>::CConstIterator(const CIterator<T>& iter) :
				Current(iter.Current)
		{
		}

		//! Explicit constructor
		template<class T>
		inline CConstIterator<T>::CConstIterator(SKListNode<T>* begin) :
				Current(begin)
		{
		}

		template<class T>
		inline CConstIterator<T>& CConstIterator<T>::operator +=(s32 num)
		{
			if (num > 0)
			{
				while (num-- && this->Current != 0)
					++(*this);
			}
			else
			{
				while (num++ && this->Current != 0)
					--(*this);
			}
			return *this;
		}

		template<class T>
		inline CConstIterator<T>& CConstIterator<T>::operator -=(s32 num) const
		{
			return (*this) += (-num);
		}

		template<class T>
		inline CConstIterator<T>& CConstIterator<T>::operator ++()
		{
			Current = Current->Next;
			return *this;
		}

		template<class T>
		inline CConstIterator<T>& CConstIterator<T>::operator --()
		{
			Current = Current->Prev;
			return *this;
		}

		template<class T>
		inline CConstIterator<T>& CConstIterator<T>::operator =(
				const CIterator<T>& iterator)
		{
			Current = iterator.Current;
			return *this;
		}

		template<class T>
		inline CConstIterator<T> CConstIterator<T>::operator ++(s32)
		{
			CConstIterator<T> tmp = *this;
			Current = Current->Next;
			return tmp;
		}

		template<class T>
		inline CConstIterator<T> CConstIterator<T>::operator --(s32)
		{
			CConstIterator<T> tmp = *this;
			Current = Current->Prev;
			return tmp;
		}

		template<class T>
		inline CConstIterator<T> CConstIterator<T>::operator +(s32 num) const
		{
			CConstIterator<T> tmp = *this;
			return tmp += num;
		}

		template<class T>
		inline CConstIterator<T> CConstIterator<T>::operator -(s32 num) const
		{
			return (*this) + (-num);
		}

		template<class T>
		inline bool CConstIterator<T>::operator ==(
				const CConstIterator<T>& other) const
		{
			return Current == other.Current;
		}

		template<class T>
		inline bool CConstIterator<T>::operator !=(
				const CConstIterator<T>& other) const
		{
			return Current != other.Current;
		}

		template<class T>
		inline bool CConstIterator<T>::operator ==(
				const CIterator<T>& other) const
		{
			return Current == other.Current;
		}

		template<class T>
		inline bool CConstIterator<T>::operator !=(
				const CIterator<T>& other) const
		{
			return Current != other.Current;
		}

		template<class T>
		inline const T& CConstIterator<T>::operator *()
		{
			return Current->Element;
		}

		template<class T>
		inline const T* CConstIterator<T>::operator ->()
		{
			return &Current->Element;
		}

	} // end namespace core
} // end namespace irrgame

#endif /* ITERATORS_H_ */
