// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_LIST_H_INCLUDED__
#define __IRR_LIST_H_INCLUDED__

#include "core/base/irrAllocator.h"
#include "SKListNode.h"
#include "iterators.h"

namespace irrgame
{
	namespace core
	{
		//! Doubly linked list template.
		template<class T>
		class list
		{
			public:
				typedef CIterator<T> Iterator;
				typedef CConstIterator<T> ConstIterator;

			public:

				//! Default constructor for empty list.
				list();

				//! Copy constructor.
				list(const list<T>& other);

				//! Destructor
				virtual ~list();

				//! Assignment operator
				virtual void operator=(const list<T>& other);

				//! Returns amount of elements in list.
				/** \return Amount of elements in the list. */
				virtual u32 size() const;

				//! Clears the list, deletes all elements in the list.
				/** All existing iterators of this list will be invalid. */
				virtual void clear();

				//! Checks for empty list.
				/** \return True if the list is empty and false if not. */
				virtual bool empty() const;

				//! Adds an element at the end of the list.
				/** \param element Element to add to the list. */
				virtual void push_back(const T& element);

				//! Adds an element at the begin of the list.
				/** \param element: Element to add to the list. */
				virtual void push_front(const T& element);

				//! Inserts an element after an element.
				/** \param it Iterator pointing to element after which the new element
				 should be inserted.
				 \param element The new element to be inserted into the list.
				 */
				virtual void insert_after(const Iterator& it, const T& element);

				//! Inserts an element before an element.
				/** \param it Iterator pointing to element before which the new element
				 should be inserted.
				 \param element The new element to be inserted into the list.
				 */
				virtual void insert_before(const Iterator& it,
						const T& element);

				//! Erases an element.
				/** \param it Iterator pointing to the element which shall be erased.
				 \return Iterator pointing to next element. */
				virtual Iterator erase(Iterator& it);

				//! Swap the content of this list container with the content of another list
				/** Afterwards this object will contain the content of the other object and the other
				 object will contain the content of this object. Iterators will afterwards be valid for
				 the swapped object.
				 \param other Swap content with this object	*/
				virtual void swap(list<T>& other);

				//! Gets first node.
				/** \return A list iterator pointing to the beginning of the list. */
				virtual Iterator begin();

				//! Gets end node.
				/** \return List iterator pointing to null. */
				virtual Iterator end();

				//! Gets last element.
				/** \return List iterator pointing to the last element of the list. */
				virtual Iterator getLast();

				//! Gets first node.
				/** \return A const list iterator pointing to the beginning of the list. */
				virtual ConstIterator begin() const;

				//! Gets end node.
				/** \return Const list iterator pointing to null. */
				virtual ConstIterator end() const;

				//! Gets last element.
				/** \return Const list iterator pointing to the last element of the list. */
				virtual ConstIterator getLast() const;

			protected:

				SKListNode<T>* First;
				SKListNode<T>* Last;
				u32 Size;
				irrAllocator<SKListNode<T> > allocator;
		};

		//!--------- List realization

		//! Default constructor for empty list.
		template<class T>
		inline list<T>::list() :
				First(0), Last(0), Size(0)
		{
		}

		//! Copy constructor.
		template<class T>
		inline list<T>::list(const list<T>& other) :
				First(0), Last(0), Size(0)
		{
			*this = other;
		}

		//! Destructor
		template<class T>
		inline list<T>::~list()
		{
			list<T>::clear();
		}

		//! Assignment operator
		template<class T>
		inline void list<T>::operator=(const list<T>& other)
		{
			if (&other == this)
				return;

			list<T>::clear();

			SKListNode<T>* node = other.First;
			while (node)
			{
				list<T>::push_back(node->Element);
				node = node->Next;
			}
		}

		//! Returns amount of elements in list.
		/** \return Amount of elements in the list. */
		template<class T>
		inline u32 list<T>::size() const
		{
			return Size;
		}

		//! Clears the list, deletes all elements in the list.
		/** All existing iterators of this list will be invalid. */
		template<class T>
		inline void list<T>::clear()
		{
			while (First)
			{
				SKListNode<T>* next = First->Next;
				allocator.destruct(First);
				allocator.deallocate(First);
				First = next;
			}

			//First = 0; handled by loop
			Last = 0;
			Size = 0;
		}

		//! Checks for empty list.
		/** \return True if the list is empty and false if not. */
		template<class T>
		inline bool list<T>::empty() const
		{
			return (First == 0);
		}

		//! Adds an element at the end of the list.
		/** \param element Element to add to the list. */
		template<class T>
		inline void list<T>::push_back(const T& element)
		{
			SKListNode<T>* node = allocator.allocate(1);
			allocator.construct(node, element);

			++Size;

			if (First == 0)
				First = node;

			node->Prev = Last;

			if (Last != 0)
				Last->Next = node;

			Last = node;
		}

		//! Adds an element at the begin of the list.
		/** \param element: Element to add to the list. */
		template<class T>
		inline void list<T>::push_front(const T& element)
		{
			SKListNode<T>* node = allocator.allocate(1);
			allocator.construct(node, element);

			++Size;

			if (First == 0)
			{
				Last = node;
				First = node;
			}
			else
			{
				node->Next = First;
				First->Prev = node;
				First = node;
			}
		}

		//! Inserts an element after an element.
		/** \param it Iterator pointing to element after which the new element
		 should be inserted.
		 \param element The new element to be inserted into the list.
		 */
		template<class T>
		inline void list<T>::insert_after(const CIterator<T>& it,
				const T& element)
		{
			SKListNode<T>* node = allocator.allocate(1);
			allocator.construct(node, element);

			node->Next = it.Current->Next;

			if (it.Current->Next)
				it.Current->Next->Prev = node;

			node->Prev = it.Current;
			it.Current->Next = node;
			++Size;

			if (it.Current == Last)
				Last = node;
		}

		//! Inserts an element before an element.
		/** \param it Iterator pointing to element before which the new element
		 should be inserted.
		 \param element The new element to be inserted into the list.
		 */
		template<class T>
		inline void list<T>::insert_before(const CIterator<T>& it,
				const T& element)
		{
			SKListNode<T>* node = allocator.allocate(1);
			allocator.construct(node, element);

			node->Prev = it.Current->Prev;

			if (it.Current->Prev)
				it.Current->Prev->Next = node;

			node->Next = it.Current;
			it.Current->Prev = node;
			++Size;

			if (it.Current == First)
				First = node;
		}

		//! Erases an element.
		/** \param it Iterator pointing to the element which shall be erased.
		 \return Iterator pointing to next element. */
		template<class T>
		inline CIterator<T> list<T>::erase(CIterator<T>& it)
		{
			// suggest changing this to a const Iterator& and
			// working around line: it.Current = 0 (possibly with a mutable, or just let it be garbage?)

			CIterator<T> returnIterator(it);
			++returnIterator;

			if (it.Current == First)
				First = it.Current->Next;
			else
				it.Current->Prev->Next = it.Current->Next;

			if (it.Current == Last)
				Last = it.Current->Prev;
			else
				it.Current->Next->Prev = it.Current->Prev;

			allocator.destruct(it.Current);
			allocator.deallocate(it.Current);
			it.Current = 0;
			--Size;

			return returnIterator;
		}

		//! Swap the content of this list container with the content of another list
		/** Afterwards this object will contain the content of the other object and the other
		 object will contain the content of this object. Iterators will afterwards be valid for
		 the swapped object.
		 \param other Swap content with this object	*/
		template<class T>
		inline void list<T>::swap(list<T>& other)
		{
			core::swap(First, other.First);
			core::swap(Last, other.Last);
			core::swap(Size, other.Size);
			core::swap(allocator, other.allocator);	// memory is still released by the same allocator used for allocation
		}

		//! Gets first node.
		/** \return A list iterator pointing to the beginning of the list. */
		template<class T>
		inline CIterator<T> list<T>::begin()
		{
			return CIterator<T>(First);
		}

		/** \return List iterator pointing to null. */
		template<class T>
		inline CIterator<T> list<T>::end()
		{
			return CIterator<T>(0);
		}

		/** \return List iterator pointing to the last element of the list. */
		template<class T>
		inline CIterator<T> list<T>::getLast()
		{
			return CIterator<T>(Last);
		}

		//! Gets first node.
		/** \return A const list iterator pointing to the beginning of the list. */
		template<class T>
		inline CConstIterator<T> list<T>::begin() const
		{
			return CConstIterator<T>(First);
		}

		//! Gets end node.
		/** \return Const list iterator pointing to null. */
		template<class T>
		inline CConstIterator<T> list<T>::end() const
		{
			return CConstIterator<T>(0);
		}

		//! Gets last element.
		/** \return Const list iterator pointing to the last element of the list. */
		template<class T>
		inline CConstIterator<T> list<T>::getLast() const
		{
			return CConstIterator<T>(Last);
		}

	}	// end namespace core
}	// end namespace irr

#endif

