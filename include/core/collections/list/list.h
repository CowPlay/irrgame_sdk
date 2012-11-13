// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_LIST_H_INCLUDED__
#define __IRR_LIST_H_INCLUDED__

#include "core/collections/list/SKListNode.h"
#include "core/collections/list/iterators.h"

#include "core/collections/ICollection.h"

#include "core/allocator/irrAllocator.h"
#include "core/math/SharedMath.h"
#include "threads/irrgameMonitor.h"

namespace irrgame
{
	namespace core
	{

		class stringc;

		//! Doubly linked list template.
		template<class T>
		class list: public ICollection<T>
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

				/*
				 * Operators
				 */

				//! Assignment operator
				void operator=(const list<T>& other);

				/*
				 * ICollection realization
				 */

				//! Adds an element at the end of the list.
				/** \param element Element to add to the list. */
				virtual void pushBack(const T& element);

				//! Adds an element at the begin of the list.
				/** \param element: Element to add to the list. */
				virtual void pushFront(const T& element);

				//! Returns amount of elements in list.
				/** \return Amount of elements in the list. */
				virtual u32 size() const;

				//! Gets last element
				virtual T& getLast();

				//! Returns last element of collection
				virtual const T& getLast() const;

				//! Direct access operator
				//! Reverse search
				/* \param index Index of element. Must be lower than collection size
				 * \return Element by index for getting or setting value. */
				virtual T& operator[](u32 index);

				//! Direct const access operator
				//! Reverse search
				/* \param index Index of element. Must be lower than collection size
				 * \return Element by index for getting or setting value. */
				virtual const T& operator[](u32 index) const;

				/*
				 * Methods
				 */

				//! Clears the list, deletes all elements in the list.
				/** All existing iterators of this list will be invalid. */
				void clear();

				//! Checks for empty list.
				/** \return True if the list is empty and false if not. */
				bool empty() const;

				//! Inserts an element after an element.
				/* \param it Iterator pointing to element after which the new element
				 * should be inserted.
				 * \param element The new element to be inserted into the list.
				 */
				void insertAfter(const Iterator& it, const T& element);

				//! Inserts an element before an element.
				/** \param it Iterator pointing to element before which the new element
				 should be inserted.
				 \param element The new element to be inserted into the list.
				 */
				void insertBefore(const Iterator& it, const T& element);

				//! Remove an element from list.
				/** \param element: Element to remove from the list. */
				void remove(const T& element);

				//! Erases an element.
				/** \param it Iterator pointing to the element which shall be erased.
				 \return Iterator pointing to next element. */
				Iterator erase(Iterator& it);

				//! Swap the content of this list container with the content of another list
				/** Afterwards this object will contain the content of the other object and the other
				 object will contain the content of this object. Iterators will afterwards be valid for
				 the swapped object.
				 \param other Swap content with this object	*/
				void swap(list<T>& other);

				//! Gets iterator of first node.
				/** \return A list iterator pointing to the beginning of the list. */
				Iterator begin();

				//! Gets end node.
				/** \return List iterator pointing to null. */
				Iterator end();

				//! Gets iterator of last element.
				/** \return List iterator pointing to the last element of the list. */
				Iterator getLastIterator();

				//! Gets const iterator of first node.
				/** \return A const list iterator pointing to the beginning of the list. */
				ConstIterator begin() const;

				//! Gets end node.
				/** \return Const list iterator pointing to null. */
				ConstIterator end() const;

				//! Gets const iterator of  last element.
				/** \return Const list iterator pointing to the last element of the list. */
				virtual ConstIterator getLastIterator() const;

			private:
				//! Clears the list, deletes all elements in the list.
				//! Uses internal without lockers
				/** All existing iterators of this list will be invalid. */
				void clearInternal();

			private:

				SKListNode<T>* First;
				SKListNode<T>* Last;
				u32 Size;
				irrAllocator<SKListNode<T> > Allocator;
				threads::irrgameMonitor* Monitor;
		};

		//! Default constructor for empty list.
		template<class T>
		inline list<T>::list() :
				First(0), Last(0), Size(0), Monitor(0)
		{
			Monitor = irrgame::threads::createIrrgameMonitor();
		}

		//! Copy constructor.
		template<class T>
		inline list<T>::list(const list<T>& other) :
				First(0), Last(0), Size(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
			*this = other;
		}

		//! Destructor
		template<class T>
		inline list<T>::~list()
		{
			clear();

			if (Monitor)
				Monitor->drop();
		}

		//! Assignment operator
		template<class T>
		inline void list<T>::operator=(const list<T>& other)
		{
			if (&other == this)
				return;

			Monitor->enter();

			clearInternal();

			SKListNode<T>* node = other.First;
			while (node)
			{
				pushBack(node->Element);
				node = node->Next;
			}

			Monitor->exit();
		}

		//! Adds an element at the end of the list.
		template<class T>
		inline void list<T>::pushBack(const T& element)
		{
			Monitor->enter();

			SKListNode<T>* node = Allocator.allocate(1);
			Allocator.construct(node, element);

			++Size;

			if (First == 0)
				First = node;

			node->Prev = Last;

			if (Last != 0)
				Last->Next = node;

			Last = node;

			Monitor->exit();
		}

		//! Adds an element at the begin of the list.
		template<class T>
		inline void list<T>::pushFront(const T& element)
		{
			Monitor->enter();

			SKListNode<T>* node = Allocator.allocate(1);
			Allocator.construct(node, element);

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

			Monitor->exit();
		}

		//! Returns amount of elements in list.
		template<class T>
		inline u32 list<T>::size() const
		{
			Monitor->enter();
			u32 result = Size;
			Monitor->exit();

			return result;
		}

		//! Gets last element
		template<class T>
		inline T& list<T>::getLast()
		{
			Monitor->enter();
			T& result = Last->Element;
			Monitor->exit();

			return result;
		}

		//! Returns last element of collection
		template<class T>
		inline const T& list<T>::getLast() const
		{
			Monitor->enter();
			const T& result = Last->Element;
			Monitor->exit();

			return result;

		}

		//! Direct access operator
		template<class T>
		inline T& list<T>::operator[](u32 index)
		{
			IRR_ASSERT(index < Size);

			Monitor->enter();

			SKListNode<T>* resultNode = Last;
			for (u32 i = Size; i != index; --i)
			{
				resultNode = Last->Prev;
			}

			T& result = resultNode->Element;

			Monitor->exit();

			return result;
		}

		//! Direct const access operator
		template<class T>
		inline const T& list<T>::operator[](u32 index) const
		{
			IRR_ASSERT(index < Size);

			Monitor->enter();

			SKListNode<T>* resultNode = Last;
			for (u32 i = Size; i != index; --i)
			{
				resultNode = Last->Prev;
			}

			const T& result = resultNode->Element;

			Monitor->exit();

			return result;
		}

		//! Clears the list, deletes all elements in the list.
		template<class T>
		inline void list<T>::clear()
		{
			Monitor->enter();
			clearInternal();
			Monitor->exit();
		}

		//! Clears the list, deletes all elements in the list.
		//! Uses internal without lockers
		template<class T>
		inline void list<T>::clearInternal()
		{
			while (First)
			{
				SKListNode<T>* next = First->Next;
				Allocator.destruct(First);
				Allocator.deallocate(First);
				First = next;
			}

			//First = 0; handled by loop
			Last = 0;
			Size = 0;
		}

		//! Checks for empty list.
		template<class T>
		inline bool list<T>::empty() const
		{
			Monitor->enter();
			bool result = First == 0;
			Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! Inserts an element after an element.
		template<class T>
		inline void list<T>::insertAfter(const CIterator<T>& it,
				const T& element)
		{
			IRR_ASSERT(it != Iterator(0));

			Monitor->enter();

			SKListNode<T>* node = Allocator.allocate(1);
			Allocator.construct(node, element);

			node->Next = it.Current->Next;

			if (it.Current->Next)
			{
				it.Current->Next->Prev = node;
			}

			node->Prev = it.Current;
			it.Current->Next = node;
			++Size;

			if (it.Current == Last)
			{
				Last = node;
			}

			Monitor->exit();
		}

		//! Inserts an element before an element.
		template<class T>
		inline void list<T>::insertBefore(const CIterator<T>& it,
				const T& element)
		{
			IRR_ASSERT(it != Iterator(0));

			Monitor->enter();

			SKListNode<T>* node = Allocator.allocate(1);
			Allocator.construct(node, element);

			node->Prev = it.Current->Prev;

			if (it.Current->Prev)
			{
				it.Current->Prev->Next = node;
			}

			node->Next = it.Current;
			it.Current->Prev = node;
			++Size;

			if (it.Current == First)
			{
				First = node;
			}

			Monitor->exit();
		}

		//! Remove an element from list.
		template<class T>
		inline void list<T>::remove(const T& element)
		{
			Monitor->enter();

			SKListNode<T>* node = First;
			while (node)
			{
				if (node->Element == element)
				{
					node->Prev->Next = node->Next;
					--Size;

					Allocator.destruct(node);
					Allocator.deallocate(node);

					break;
				}

				node = node->Next;
			}

			Monitor->exit();
		}

		//! Erases an element.
		template<class T>
		inline CIterator<T> list<T>::erase(CIterator<T>& it)
		{
			IRR_ASSERT(it != Iterator(0));

			// suggest changing this to a const Iterator& and
			// working around line: it.Current = 0 (possibly with a mutable, or just let it be garbage?)

			Iterator result(it);

			Monitor->enter();

			++result;

			if (it.Current == First)
				First = it.Current->Next;
			else
				it.Current->Prev->Next = it.Current->Next;

			if (it.Current == Last)
				Last = it.Current->Prev;
			else
				it.Current->Next->Prev = it.Current->Prev;

			Allocator.destruct(it.Current);
			Allocator.deallocate(it.Current);
			it.Current = 0;
			--Size;

			Monitor->exit();

			return result;
		}

		//! Swap the content of this list container with the content of another list
		template<class T>
		inline void list<T>::swap(list<T>& other)
		{
			// handle self swap
			if (this == &other)
				return;

			other.Monitor->enter();
			Monitor->enter();

			SharedMath::getInstance().swap(First, other.First);
			SharedMath::getInstance().swap(Last, other.Last);
			SharedMath::getInstance().swap(Size, other.Size);
			SharedMath::getInstance().swap(Allocator, other.Allocator);	// memory is still released by the same Allocator used for allocation

			Monitor->exit();
			other.Monitor->exit();
		}

		//! Gets first node.
		template<class T>
		inline CIterator<T> list<T>::begin()
		{
			Monitor->enter();
			Iterator result(First);
			Monitor->exit();

			return result;
		}

		//! Gets end node.
		template<class T>
		inline CIterator<T> list<T>::end()
		{
			return Iterator(0);
		}

		//! Gets last element.
		template<class T>
		inline CIterator<T> list<T>::getLastIterator()
		{
			Monitor->enter();
			Iterator result(Last);
			Monitor->exit();

			return result;
		}

		//! Gets first node.
		template<class T>
		inline CConstIterator<T> list<T>::begin() const
		{
			Monitor->enter();
			ConstIterator result(First);
			Monitor->exit();

			return result;
		}

		//! Gets end node.
		template<class T>
		inline CConstIterator<T> list<T>::end() const
		{
			return ConstIterator(0);
		}

		//! Gets last element.
		template<class T>
		inline CConstIterator<T> list<T>::getLastIterator() const
		{
			Monitor->enter();
			ConstIterator result(Last);
			Monitor->exit();

			return result;
		}

	}	// end namespace core
}	// end namespace irr

//! list typedefs
typedef irrgame::core::list<s32> listi;
typedef irrgame::core::list<u32> listu;
typedef irrgame::core::list<f32> listf;
typedef irrgame::core::list<irrgame::core::stringc> liststr;

#endif

