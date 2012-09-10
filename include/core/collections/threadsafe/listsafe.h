///*
// * irrlistsafe.h
// *
// *  Created on: Aug 24, 2012
// *      Author: gregorytkach
// */
//
//#ifndef IRRLISTSAFE_H_
//#define IRRLISTSAFE_H_
//
//#include "core/collections/list/list.h"
//#include "threads/irrgameMonitor.h"
//
//namespace irrgame
//{
//	namespace core
//	{
//		//! Doubly linked threadsafe list template.
//		template<class T>
//		class listsafe: public list<T>
//		{
//			public:
//				typedef CIterator<T> Iterator;
//				typedef CConstIterator<T> ConstIterator;
//
//			public:
//
//				//! Default constructor for empty list.
//				listsafe();
//
//				//! Copy constructor.
//				listsafe(const listsafe<T>& other);
//
//				//! Destructor
//				virtual ~listsafe();
//
//				//! Assignment operator
//				virtual void operator=(const listsafe<T>& other);
//
//				//! Returns amount of elements in list.
//				/** \return Amount of elements in the list. */
//				virtual u32 size() const;
//
//				//! Clears the list, deletes all elements in the list.
//				/** All existing iterators of this list will be invalid. */
//				virtual void clear();
//
//				//! Checks for empty list.
//				/** \return True if the list is empty and false if not. */
//				virtual bool empty() const;
//
//				//! Adds an element at the end of the list.
//				/** \param element Element to add to the list. */
//				virtual void push_back(const T& element);
//
//				//! Adds an element at the begin of the list.
//				/** \param element: Element to add to the list. */
//				virtual void push_front(const T& element);
//
//				//! Inserts an element after an element.
//				/** \param it Iterator pointing to element after which the new element
//				 should be inserted.
//				 \param element The new element to be inserted into the list.
//				 */
//				virtual void insert_after(const Iterator& it, const T& element);
//
//				//! Inserts an element before an element.
//				/** \param it Iterator pointing to element before which the new element
//				 should be inserted.
//				 \param element The new element to be inserted into the list.
//				 */
//				virtual void insert_before(const Iterator& it,
//						const T& element);
//
//				//! Erases an element.
//				/** \param it Iterator pointing to the element which shall be erased.
//				 \return Iterator pointing to next element. */
//				virtual Iterator erase(Iterator& it);
//
//				//! Swap the content of this list container with the content of another list
//				/** Afterwards this object will contain the content of the other object and the other
//				 object will contain the content of this object. Iterators will afterwards be valid for
//				 the swapped object.
//				 \param other Swap content with this object	*/
//				virtual void swap(listsafe<T>& other);
//
//				//! Gets first node.
//				/** \return A list iterator pointing to the beginning of the list. */
//				virtual Iterator begin();
//
//				//! Gets end node.
//				/** \return List iterator pointing to null. */
//				virtual Iterator end();
//
//				//! Gets last element.
//				/** \return List iterator pointing to the last element of the list. */
//				virtual Iterator getLast();
//
//				//! Gets first node.
//				/** \return A const list iterator pointing to the beginning of the list. */
//				virtual ConstIterator begin() const;
//
//				//! Gets end node.
//				/** \return Const list iterator pointing to null. */
//				virtual ConstIterator end() const;
//
//				//! Gets last element.
//				/** \return Const list iterator pointing to the last element of the list. */
//				virtual ConstIterator getLast() const;
//
//			protected:
//				threads::irrgameMonitor* Monitor;
//		};
//
//		//! Default constructor for empty list.
//		template<class T>
//		inline listsafe<T>::listsafe() :
//				list<T>::list(), Monitor(0)
//		{
//			Monitor = irrgame::threads::createIrrgameMonitor();
//		}
//
//		//! Copy constructor.
//		template<class T>
//		inline listsafe<T>::listsafe(const listsafe<T>& other) :
//				Monitor(0)
//		{
//			*this = other;
//		}
//
//		//! Destructor
//		template<class T>
//		inline listsafe<T>::~listsafe()
//		{
//			if (Monitor)
//				Monitor->drop();
//		}
//
//		//! Assignment operator
//		template<class T>
//		inline void listsafe<T>::operator=(const listsafe<T>& other)
//		{
//			if (Monitor)
//				Monitor->drop();
//
//			other.Monitor->enter();
//			list<T>::operator =(other);
//			Monitor = irrgame::threads::createIrrgameMonitor();
//			other.Monitor->exit();
//		}
//
//		//! Returns amount of elements in list.
//		/** \return Amount of elements in the list. */
//		template<class T>
//		inline u32 listsafe<T>::size() const
//		{
//			Monitor->enter();
//			u32 result = list<T>::size();
//			Monitor->exit();
//
//			return result;
//		}
//
//		//! Clears the list, deletes all elements in the list.
//		/** All existing iterators of this list will be invalid. */
//		template<class T>
//		inline void listsafe<T>::clear()
//		{
//			Monitor->enter();
//			list<T>::clear();
//			Monitor->exit();
//		}
//
//		//! Checks for empty list.
//		/** \return True if the list is empty and false if not. */
//		template<class T>
//		inline bool listsafe<T>::empty() const
//		{
//			Monitor->enter();
//			bool result = list<T>::empty();
//			Monitor->exit();
//
//			return result;
//		}
//
//		//! Adds an element at the end of the list.
//		/** \param element Element to add to the list. */
//		template<class T>
//		inline void listsafe<T>::push_back(const T& element)
//		{
//			Monitor->enter();
//			list<T>::push_back(element);
//			Monitor->exit();
//		}
//
//		//! Adds an element at the begin of the list.
//		/** \param element: Element to add to the list. */
//		template<class T>
//		inline void listsafe<T>::push_front(const T& element)
//		{
//			Monitor->enter();
//			list<T>::push_front(element);
//			Monitor->exit();
//		}
//
//		//! Inserts an element after an element.
//		/** \param it Iterator pointing to element after which the new element
//		 should be inserted.
//		 \param element The new element to be inserted into the list.
//		 */
//		template<class T>
//		inline void listsafe<T>::insert_after(const CIterator<T>& it,
//				const T& element)
//		{
//			Monitor->enter();
//			list<T>::insert_after(it, element);
//			Monitor->exit();
//		}
//
//		//! Inserts an element before an element.
//		/** \param it Iterator pointing to element before which the new element
//		 should be inserted.
//		 \param element The new element to be inserted into the list.
//		 */
//		template<class T>
//		inline void listsafe<T>::insert_before(const CIterator<T>& it,
//				const T& element)
//		{
//			Monitor->enter();
//			list<T>::insert_before(it, element);
//			Monitor->exit();
//		}
//
//		//! Erases an element.
//		/** \param it Iterator pointing to the element which shall be erased.
//		 \return Iterator pointing to next element. */
//		template<class T>
//		inline CIterator<T> listsafe<T>::erase(CIterator<T>& it)
//		{
//			Monitor->enter();
//			CIterator<T> result = list<T>::erase(it);
//			Monitor->exit();
//
//			return result;
//		}
//
//		//! Swap the content of this list container with the content of another list
//		/** Afterwards this object will contain the content of the other object and the other
//		 object will contain the content of this object. Iterators will afterwards be valid for
//		 the swapped object.
//		 \param other Swap content with this object	*/
//		template<class T>
//		inline void listsafe<T>::swap(listsafe<T>& other)
//		{
//			if (this == &other)
//				return;
//
//			Monitor->enter();
//			other.Monitor->enter();
//
//			list<T>::swap(other);
//			irrgame::threads::irrgameMonitor* helper_monitor(Monitor);
//			Monitor = other.Monitor;
//			other.Monitor = helper_monitor;
//
//			Monitor->exit();
//			other.Monitor->exit();
//		}
//
//		//! Gets first node.
//		/** \return A list iterator pointing to the beginning of the list. */
//		template<class T>
//		inline CIterator<T> listsafe<T>::begin()
//		{
//			Monitor->enter();
//			CIterator<T> result = list<T>::begin();
//			Monitor->exit();
//
//			return result;
//		}
//
//		//! Gets end node.
//		/** \return List iterator pointing to null. */
//		template<class T>
//		inline CIterator<T> listsafe<T>::end()
//		{
//			Monitor->enter();
//			CIterator<T> result = list<T>::end();
//			Monitor->exit();
//
//			return result;
//		}
//		//! Gets last element.
//		/** \return List iterator pointing to the last element of the list. */
//		template<class T>
//		inline CIterator<T> listsafe<T>::getLast()
//		{
//			Monitor->enter();
//			CIterator<T> result = list<T>::getLast();
//			Monitor->exit();
//
//			return result;
//		}
//
//		//! Gets first node.
//		/** \return A const list iterator pointing to the beginning of the list. */
//		template<class T>
//		inline CConstIterator<T> listsafe<T>::begin() const
//		{
//			Monitor->enter();
//			CConstIterator<T> result = list<T>::begin();
//			Monitor->exit();
//
//			return result;
//		}
//
//		//! Gets end node.
//		/** \return Const list iterator pointing to null. */
//		template<class T>
//		inline CConstIterator<T> listsafe<T>::end() const
//		{
//			Monitor->enter();
//			CConstIterator<T> result = list<T>::end();
//			Monitor->exit();
//
//			return result;
//		}
//
//		//! Gets last element.
//		/** \return Const list iterator pointing to the last element of the list. */
//		template<class T>
//		inline CConstIterator<T> listsafe<T>::getLast() const
//		{
//			Monitor->enter();
//			CConstIterator<T> result = list<T>::getLast();
//			Monitor->exit();
//
//			return result;
//		}
//
//	} // end namespace core
//} // end namespace irrgame
//
//#endif /* IRRLISTSAFE_H_ */
