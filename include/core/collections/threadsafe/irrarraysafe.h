/*
 * irrarraysafe.h
 *
 *  Created on: Aug 23, 2012
 *      Author: gregorytkach
 */

#ifndef IRRARRAYSAFE_H_
#define IRRARRAYSAFE_H_

#include "core/collections/irrArray.h"
#include "threads/irrgameMonitor.h"

namespace irrgame
{
	namespace core
	{
		//! Self reallocating threadsafe template array (like stl vector) with additional features.
		/** Some features are: Heap sorting, binary search methods, easier debugging.
		 */
		template<class T>
		class arraysafe: public array<T>
		{
			public:

				//! Default constructor for empty array.
				arraysafe();

				//! Constructs an array and allocates an initial chunk of memory.
				/** \param start_count Amount of elements to pre-allocate. */
				arraysafe(u32 start_count);

				//! Copy constructor
				arraysafe(const arraysafe<T>& other);

				//! Destructor.
				/** Frees allocated memory, if set_free_when_destroyed was not set to
				 false by the user before. */
				virtual ~arraysafe();

				//! Reallocates the array, make it bigger or smaller.
				/** \param new_size New size of array. */
				virtual void reallocate(u32 new_size);

				//! set a new allocation strategy
				/** if the maximum size of the array is unknown, you can define how big the
				 allocation should happen.
				 \param newStrategy New strategy to apply to this array. */
				virtual void setAllocStrategy(eAllocStrategy newStrategy =
						ALLOC_STRATEGY_DOUBLE);

				//! Insert item into array at specified position.
				/** Please use this only if you know what you are doing (possible
				 performance loss). The preferred method of adding elements should be
				 push_back().
				 \param element: Element to be inserted
				 \param index: Where position to insert the new element. */
				virtual void insert(const T& element, u32 index = 0);

				//! Clears the array and deletes all allocated memory.
				virtual void clear();

				//! Sets pointer to new array, using this as new workspace.
				/** Make sure that set_free_when_destroyed is used properly.
				 \param newPointer: Pointer to new array of elements.
				 \param size: Size of the new array.
				 \param _is_sorted Flag which tells whether the new array is already
				 sorted.
				 \param _free_when_destroyed Sets whether the new memory area shall be
				 freed by the array upon destruction, or if this will be up to the user
				 application. */
				virtual void set_pointer(T* newPointer, u32 size,
						bool _is_sorted = false, bool _free_when_destroyed =
								true);

				//! Sets if the array should delete the memory it uses upon destruction.
				/** Also clear and set_pointer will only delete the (original) memory
				 area if this flag is set to true, which is also the default. The
				 methods reallocate, set_used, push_back, push_front, insert, and erase
				 will still try to deallocate the original memory, which might cause
				 troubles depending on the intended use of the memory area.
				 \param f If true, the array frees the allocated memory in its
				 destructor, otherwise not. The default is true. */
				virtual void set_free_when_destroyed(bool f);

				//! Sets the size of the array and allocates new elements if necessary.
				/** Please note: This is only secure when using it with simple types,
				 because no default constructor will be called for the added elements.
				 \param usedNow Amount of elements now used. */
				virtual void set_used(u32 usedNow);

				//! Assignment operator
				virtual arraysafe<T>& operator=(const arraysafe<T>& other);

				//! Equality operator
				virtual bool operator ==(const arraysafe<T>& other) const;

				//! Inequality operator
				virtual bool operator !=(const arraysafe<T>& other) const;

				//! Direct access operator. Can be get or set value.
				virtual T& operator [](u32 index);

				//! Direct const access operator. Can be get or set value.
				virtual const T& operator [](u32 index) const;

				//! Gets last element. Can be get or set value.
				virtual T& getLast();

				//! Gets last element. Can be get or set value.
				virtual const T& getLast() const;

				//! Gets a pointer to the array. Can be get or set value.
				/** \return Pointer to the array. */
				virtual T* pointer();

				//! Gets a const pointer to the array.
				/** \return Pointer to the array. */
				virtual const T* const_pointer() const;

				//! Get number of occupied elements of the array.
				/** \return Size of elements in the array which are actually occupied. */
				virtual u32 size() const;

				//! Get amount of memory allocated.
				/** \return Amount of memory allocated. The amount of bytes
				 allocated would be allocated_size() * sizeof(ElementTypeUsed); */
				virtual u32 allocated_size() const;

				//! Check if array is empty.
				/** \return True if the array is empty false if not. */
				virtual bool empty() const;

				//! Sorts the array using heapsort.
				/** There is no additional memory waste and the algorithm performs
				 O(n*log n) in worst case. */
				virtual void sort();

				//! Performs a binary search for an element, returns -1 if not found.
				/** The array will be sorted before the binary search if it is not
				 already sorted. Caution is advised! Be careful not to call this on
				 unsorted const arrays, or the slower method will be used.
				 \param element Element to search for.
				 \return Position of the searched element if it was found,
				 otherwise -1 is returned. */
				virtual s32 binary_search(const T& element);

				//! Performs a binary search for an element if possible, returns -1 if not found.
				/** This method is for const arrays and so cannot call sort(), if the array is
				 not sorted then linear_search will be used instead. Potentially very slow!
				 \param element Element to search for.
				 \return Position of the searched element if it was found,
				 otherwise -1 is returned. */
				virtual s32 binary_search(const T& element) const;

				//! Performs a binary search for an element, returns -1 if not found.
				/** \param element: Element to search for.
				 \param left First left index
				 \param right Last right index.
				 \return Position of the searched element if it was found, otherwise -1
				 is returned. */
				virtual s32 binary_search(const T& element, s32 left,
						s32 right) const;

				//! Performs a binary search for an element, returns -1 if not found.
				//! it is used for searching a multiset
				/** The array will be sorted before the binary search if it is not
				 already sorted.
				 \param element	Element to search for.
				 \param &last	return lastIndex of equal elements
				 \return Position of the first searched element if it was found,
				 otherwise -1 is returned. */
				virtual s32 binary_search_multi(const T& element, s32 &last);

				//! Finds an element in linear time, which is very slow.
				/** Use binary_search for faster finding. Only works if ==operator is
				 implemented.
				 \param element Element to search for.
				 \return Position of the searched element if it was found, otherwise -1
				 is returned. */
				virtual s32 linear_search(const T& element) const;

				//! Finds an element in linear time, which is very slow.
				/** Use binary_search for faster finding. Only works if ==operator is
				 implemented.
				 \param element: Element to search for.
				 \return Position of the searched element if it was found, otherwise -1
				 is returned. */
				virtual s32 linear_reverse_search(const T& element) const;

				//! Erases an element from the array.
				/** May be slow, because all elements following after the erased
				 element have to be copied.
				 \param index: Index of element to be erased. */
				virtual void erase(u32 index);

				//! Erases some elements from the array.
				/** May be slow, because all elements following after the erased
				 element have to be copied.
				 \param index: Index of the first element to be erased.
				 \param count: Amount of elements to be erased. */
				virtual void erase(u32 index, s32 count);

				//! Sets if the array is sorted
				virtual void set_sorted(bool _is_sorted);

				//! Swap the content of this array container with the content of another array
				/** Afterwards this object will contain the content of the other object and the other
				 object will contain the content of this object.
				 \param other Swap content with this object	*/
				virtual void swap(arraysafe<T>& other);

			protected:
				threads::irrgameMonitor* Monitor;
		};

		//! Default constructor for empty array.
		template<class T>
		inline arraysafe<T>::arraysafe() :
				array<T>::array(), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
		}

		//! Constructs an array and allocates an initial chunk of memory.
		/** \param start_count Amount of elements to pre-allocate. */
		template<class T>
		inline arraysafe<T>::arraysafe(u32 start_count) :
				array<T>::array(start_count), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
		}

		//! Copy constructor
		template<class T>
		inline arraysafe<T>::arraysafe(const arraysafe<T>& other) :
				Monitor(0)
		{
			*this = other;
		}

		//! Destructor.
		/** Frees allocated memory, if set_free_when_destroyed was not set to
		 false by the user before. */
		template<class T>
		inline arraysafe<T>::~arraysafe()
		{
			if (Monitor)
				Monitor->drop();
		}

		//! Reallocates the array, make it bigger or smaller.
		/** \param new_size New size of array. */
		template<class T>
		inline void arraysafe<T>::reallocate(u32 new_size)
		{
			Monitor->enter();
			array<T>::reallocate(new_size);
			Monitor->exit();
		}

		//! set a new allocation strategy
		/** if the maximum size of the array is unknown, you can define how big the
		 allocation should happen.
		 \param newStrategy New strategy to apply to this array. */
		template<class T>
		inline void arraysafe<T>::setAllocStrategy(eAllocStrategy newStrategy)
		{
			Monitor->enter();
			array<T>::setAllocStrategy(newStrategy);
			Monitor->exit();
		}

		//! Insert item into array at specified position.
		/** Please use this only if you know what you are doing (possible
		 performance loss). The preferred method of adding elements should be
		 push_back().
		 \param element: Element to be inserted
		 \param index: Where position to insert the new element. */
		template<class T>
		inline void arraysafe<T>::insert(const T& element, u32 index)
		{
			Monitor->enter();
			array<T>::insert(element, index);
			Monitor->exit();
		}

		//! Clears the array and deletes all allocated memory.
		template<class T>
		inline void arraysafe<T>::clear()
		{
			Monitor->enter();
			array<T>::clear();
			Monitor->exit();
		}

		//! Sets pointer to new array, using this as new workspace.
		/** Make sure that set_free_when_destroyed is used properly.
		 \param newPointer: Pointer to new array of elements.
		 \param size: Size of the new array.
		 \param _is_sorted Flag which tells whether the new array is already
		 sorted.
		 \param _free_when_destroyed Sets whether the new memory area shall be
		 freed by the array upon destruction, or if this will be up to the user
		 application. */
		template<class T>
		inline void arraysafe<T>::set_pointer(T* newPointer, u32 size,
				bool _is_sorted, bool _free_when_destroyed)
		{
			Monitor->enter();
			array<T>::set_pointer(newPointer, size, _is_sorted,
					_free_when_destroyed);
			Monitor->exit();
		}

		//! Sets if the array should delete the memory it uses upon destruction.
		/** Also clear and set_pointer will only delete the (original) memory
		 area if this flag is set to true, which is also the default. The
		 methods reallocate, set_used, push_back, push_front, insert, and erase
		 will still try to deallocate the original memory, which might cause
		 troubles depending on the intended use of the memory area.
		 \param f If true, the array frees the allocated memory in its
		 destructor, otherwise not. The default is true. */
		template<class T>
		inline void arraysafe<T>::set_free_when_destroyed(bool f)
		{
			Monitor->enter();
			array<T>::set_free_when_destroyed(f);
			Monitor->exit();
		}

		//! Sets the size of the array and allocates new elements if necessary.
		/** Please note: This is only secure when using it with simple types,
		 because no default constructor will be called for the added elements.
		 \param usedNow Amount of elements now used. */
		template<class T>
		inline void arraysafe<T>::set_used(u32 usedNow)
		{
			Monitor->enter();
			set_used(usedNow);
			Monitor->exit();
		}

		//! Assignment operator
		template<class T>
		inline arraysafe<T>& arraysafe<T>::operator=(const arraysafe<T>& other)
		{
			arraysafe<T> result;

			//handle self-assignment
			if (this == &other)
				return *this;

			if (Monitor)
				Monitor->drop();

			other.Monitor->enter();

			(*result) = static_cast<arraysafe<T>&>(array<T>::operator=(other));
			&result.Monitor = other.Monitor;

			other.Monitor->exit();

			return (*result);
		}

		//! Equality operator
		template<class T>
		inline bool arraysafe<T>::operator ==(const arraysafe<T>& other) const
		{
			bool result = false;

			if (this == &other)
				return true;

			other.Monitor->enter();
			Monitor->enter();

			result = array<T>::operator==(other);

			other.Monitor->exit();
			Monitor->exit();

			return result;
		}

		//! Inequality operator
		template<class T>
		inline bool arraysafe<T>::operator !=(const arraysafe<T>& other) const
		{
			bool result = false;

			if (this == &other)
				return false;

			other.Monitor->enter();
			Monitor->enter();

			result = array<T>::operator!=(other);

			other.Monitor->exit();
			Monitor->exit();

			return result;
		}

		//! Direct access operator. Can be get or set value.
		template<class T>
		inline T& arraysafe<T>::operator [](u32 index)
		{
			T result;

			Monitor->enter();
			(*result) = array<T>::operator[](index);
			Monitor->exit();

			return (*result);
		}

		//! Direct const access operator. Can be get or set value.
		template<class T>
		inline const T& arraysafe<T>::operator [](u32 index) const
		{
			T result;

			Monitor->enter();
			(*result) = array<T>::operator[](index);
			Monitor->exit();

			return (*result);
		}

		//! Gets last element. Can be get or set value.
		template<class T>
		inline T& arraysafe<T>::getLast()
		{
			T result;

			Monitor->enter();
			(*result) = array<T>::getLast();
			Monitor->exit();

			return (*result);
		}

		//! Gets last element. Can be get or set value.
		template<class T>
		inline const T& arraysafe<T>::getLast() const
		{
			T result;

			Monitor->enter();
			(*result) = array<T>::getLast();
			Monitor->exit();

			return (*result);
		}

		//! Gets a pointer to the array. Can be get or set value.
		/** \return Pointer to the array. */
		template<class T>
		inline T* arraysafe<T>::pointer()
		{
			T* result = 0;

			Monitor->enter();
			result = array<T>::pointer();
			Monitor->exit();

			return result;
		}

		//! Gets a const pointer to the array.
		/** \return Pointer to the array. */
		template<class T>
		inline const T* arraysafe<T>::const_pointer() const
		{
			const T* result;

			Monitor->enter();
			result = array<T>::const_pointer();
			Monitor->exit();

			return result;
		}

		//! Get number of occupied elements of the array.
		/** \return Size of elements in the array which are actually occupied. */
		template<class T>
		inline u32 arraysafe<T>::size() const
		{
			u32 result = 0;

			Monitor->enter();
			result = array<T>::size();
			Monitor->exit();

			return result;
		}

		//! Get amount of memory allocated.
		/** \return Amount of memory allocated. The amount of bytes
		 allocated would be allocated_size() * sizeof(ElementTypeUsed); */
		template<class T>
		inline u32 arraysafe<T>::allocated_size() const
		{
			u32 result = false;

			Monitor->enter();
			result = array<T>::allocated_size();
			Monitor->exit();

			return result;
		}

		//! Check if array is empty.
		/** \return True if the array is empty false if not. */
		template<class T>
		inline bool arraysafe<T>::empty() const
		{
			bool result = false;

			Monitor->enter();
			result = array<T>::empty();
			Monitor->exit();

			return result;
		}

		//! Sorts the array using heapsort.
		/** There is no additional memory waste and the algorithm performs
		 O(n*log n) in worst case. */
		template<class T>
		inline void arraysafe<T>::sort()
		{
			Monitor->enter();
			array<T>::sort();
			Monitor->exit();
		}

		//! Performs a binary search for an element, returns -1 if not found.
		/** The array will be sorted before the binary search if it is not
		 already sorted. Caution is advised! Be careful not to call this on
		 unsorted const arrays, or the slower method will be used.
		 \param element Element to search for.
		 \return Position of the searched element if it was found,
		 otherwise -1 is returned. */
		template<class T>
		inline s32 arraysafe<T>::binary_search(const T& element)
		{
			s32 result = -1;

			Monitor->enter();
			result = array<T>::binary_search(element);
			Monitor->exit();

			return result;
		}

		//! Performs a binary search for an element if possible, returns -1 if not found.
		/** This method is for const arrays and so cannot call sort(), if the array is
		 not sorted then linear_search will be used instead. Potentially very slow!
		 \param element Element to search for.
		 \return Position of the searched element if it was found,
		 otherwise -1 is returned. */
		template<class T>
		inline s32 arraysafe<T>::binary_search(const T& element) const
		{
			s32 result = -1;

			Monitor->enter();
			result = array<T>::binary_search(element);
			Monitor->exit();

			return result;
		}

		//! Performs a binary search for an element, returns -1 if not found.
		/** \param element: Element to search for.
		 \param left First left index
		 \param right Last right index.
		 \return Position of the searched element if it was found, otherwise -1
		 is returned. */
		template<class T>
		inline s32 arraysafe<T>::binary_search(const T& element, s32 left,
				s32 right) const
		{
			s32 result = -1;

			Monitor->enter();
			result = array<T>::binary_search(element, left, right);
			Monitor->exit();

			return result;
		}

		//! Performs a binary search for an element, returns -1 if not found.
		//! it is used for searching a multiset
		/** The array will be sorted before the binary search if it is not
		 already sorted.
		 \param element	Element to search for.
		 \param &last	return lastIndex of equal elements
		 \return Position of the first searched element if it was found,
		 otherwise -1 is returned. */
		template<class T>
		inline s32 arraysafe<T>::binary_search_multi(const T& element,
				s32 &last)
		{
			s32 result = -1;

			Monitor->enter();
			result = array<T>::binary_search_multi(element, last);
			Monitor->exit();

			return result;
		}

		//! Finds an element in linear time, which is very slow.
		/** Use binary_search for faster finding. Only works if ==operator is
		 implemented.
		 \param element Element to search for.
		 \return Position of the searched element if it was found, otherwise -1
		 is returned. */
		template<class T>
		inline s32 arraysafe<T>::linear_search(const T& element) const
		{
			s32 result = -1;

			Monitor->enter();
			result = array<T>::linear_search(element);
			Monitor->exit();

			return result;
		}

		//! Finds an element in linear time, which is very slow.
		/** Use binary_search for faster finding. Only works if ==operator is
		 implemented.
		 \param element: Element to search for.
		 \return Position of the searched element if it was found, otherwise -1
		 is returned. */
		template<class T>
		inline s32 arraysafe<T>::linear_reverse_search(const T& element) const
		{
			s32 result = -1;

			Monitor->enter();
			result = array<T>::linear_reverse_search(element);
			Monitor->exit();

			return result;
		}

		//! Erases an element from the array.
		/** May be slow, because all elements following after the erased
		 element have to be copied.
		 \param index: Index of element to be erased. */
		template<class T>
		inline void arraysafe<T>::erase(u32 index)
		{
			Monitor->enter();
			array<T>::erase(index);
			Monitor->exit();
		}

		//! Erases some elements from the array.
		/** May be slow, because all elements following after the erased
		 element have to be copied.
		 \param index: Index of the first element to be erased.
		 \param count: Amount of elements to be erased. */
		template<class T>
		inline void arraysafe<T>::erase(u32 index, s32 count)
		{
			Monitor->enter();
			array<T>::erase(index, count);
			Monitor->exit();
		}

		//! Sets if the array is sorted
		template<class T>
		inline void arraysafe<T>::set_sorted(bool _is_sorted)
		{
			Monitor->enter();
			array<T>::set_sorted(_is_sorted);
			Monitor->exit();
		}

		//! Swap the content of this array container with the content of another array
		/** Afterwards this object will contain the content of the other object and the other
		 object will contain the content of this object.
		 \param other Swap content with this object	*/
		//TODO: add locker for other
		template<class T>
		inline void arraysafe<T>::swap(arraysafe<T>& other)
		{
			if (this == &other)
				return;

			Monitor->enter();

			array<T>::swap(other);
			irrgame::threads::irrgameMonitor* helper_monitor(Monitor);
			Monitor = other.Monitor;
			other.Monitor = helper_monitor;

			Monitor->exit();
		}
	}
}

#endif /* IRRARRAYSAFE_H_ */
