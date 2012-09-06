// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine" and the "irrXML" project.
// For conditions of distribution and use, see copyright notice in irrlicht.h and irrXML.h

#ifndef __IRR_ARRAY_H_INCLUDED__
#define __IRR_ARRAY_H_INCLUDED__

#include "core/collections/ICollection.h"
#include "core/base/irrAllocator.h"
#include "core/math/irrMath.h"
#include "core/math/heapsort.h"
#include "stdio.h"
namespace irrgame
{
	namespace core
	{
		//! Self reallocating template array (like stl vector) with additional features.
		/** Some features are: Heap sorting, binary search methods, easier debugging.
		 */
		template<class T>
		class array: public ICollection<T>
		{
			public:

				//! Default constructor for empty array.
				array();

				//! Constructs an array and allocates an initial chunk of memory.
				/** \param start_count Amount of elements to pre-allocate. */
				array(u32 start_count);

				//! Copy constructor
				array(const array<T>& other);

				//! Destructor.
				/** Frees allocated memory, if set_free_when_destroyed was not set to
				 false by the user before. */
				virtual ~array();

				//! Reallocates the array, make it bigger or smaller.
				/** \param new_size New size of array. */
				virtual void reallocate(u32 new_size);

				//! set a new allocation strategy
				/** if the maximum size of the array is unknown, you can define how big the
				 allocation should happen.
				 \param newStrategy New strategy to apply to this array. */
				virtual void setAllocStrategy(eAllocStrategy newStrategy =
						ALLOC_STRATEGY_DOUBLE);

				//! Adds an element at back of array.
				/** If the array is too small to add this new element it is made bigger.
				 \param element: Element to add at the back of the array. */
				void push_back(const T& element);

				//! Adds an element at the front of the array.
				/** If the array is to small to add this new element, the array is
				 made bigger. Please note that this is slow, because the whole array
				 needs to be copied for this.
				 \param element Element to add at the back of the array. */
				void push_front(const T& element);

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
				virtual void set_free_when_destroyed(bool f = true);

				//! Sets the size of the array and allocates new elements if necessary.
				/** Please note: This is only secure when using it with simple types,
				 because no default constructor will be called for the added elements.
				 \param usedNow Amount of elements now used. */
				void set_used(u32 usedNow);

				//! Assignment operator
				virtual array<T>& operator=(const array<T>& other);

				//! Equality operator. Typename T must implement operator!=
				virtual bool operator ==(const array<T>& other) const;

				//! Inequality operator
				virtual bool operator !=(const array<T>& other) const;

				//! Direct access operator
				virtual T& operator [](u32 index);

				//! Direct const access operator
				virtual const T& operator [](u32 index) const;

				//! Gets last element.
				//! Can be get or set value.
				//! Size must be greater than zero.
				virtual T& getLast();

				//! Gets last element.
				//! Can be get or set value.
				//! Size must be greater than zero.
				virtual const T& getLast() const;

				//! Gets a pointer to the array.
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
				bool empty() const;

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
				virtual void swap(array<T>& other);

			protected:
				T* data;
				u32 allocated;
				u32 used;
				irrAllocator<T> allocator;
				eAllocStrategy strategy :4;
				bool free_when_destroyed :1;
				bool is_sorted :1;
		};

		//! Default constructor for empty array.
		template<class T>
		inline array<T>::array() :
				data(0), allocated(0), used(0), strategy(ALLOC_STRATEGY_DOUBLE), free_when_destroyed(
						true), is_sorted(true)
		{
		}

		//! Constructs an array and allocates an initial chunk of memory.
		template<class T>
		inline array<T>::array(u32 start_count) :
				data(0), allocated(0), used(0), strategy(ALLOC_STRATEGY_DOUBLE), free_when_destroyed(
						true), is_sorted(true)
		{
			array<T>::reallocate(start_count);
		}

		//! Copy constructor
		template<class T>
		inline array<T>::array(const array<T>& other) :
				data(0)
		{
			*this = other;
		}

		//! Destructor.
		template<class T>
		inline array<T>::~array()
		{
			array<T>::clear();
		}

		//! Reallocates the array, make it bigger or smaller.
		/** \param new_size New size of array. */
		template<class T>
		inline void array<T>::reallocate(u32 new_size)
		{
			T* old_data = data;

			data = allocator.allocate(new_size); //new T[new_size];
			allocated = new_size;

			// copy old data
			s32 end = used < new_size ? used : new_size;

			for (s32 i = 0; i < end; ++i)
			{
				// data[i] = old_data[i];
				allocator.construct(&data[i], old_data[i]);
			}

			// destruct old data
			for (u32 j = 0; j < used; ++j)
				allocator.destruct(&old_data[j]);

			if (allocated < used)
				used = allocated;

			allocator.deallocate(old_data); //delete [] old_data;
		}

		//! set a new allocation strategy
		template<class T>
		inline void array<T>::setAllocStrategy(eAllocStrategy newStrategy)
		{
			strategy = newStrategy;
		}

		//! Adds an element at back of array.
		template<class T>
		inline void array<T>::push_back(const T& element)
		{
			insert(element, used);
		}

		//! Adds an element at the front of the array.
		template<class T>
		inline void array<T>::push_front(const T& element)
		{
			insert(element);
		}

		//! Insert item into array at specified position.
		template<class T>
		inline void array<T>::insert(const T& element, u32 index)
		{
			// access violation
			IRR_ASSERT(index >= 0 && index <= used)

			if (used + 1 > allocated)
			{
				// this doesn't work if the element is in the same
				// array. So we'll copy the element first to be sure
				// we'll get no data corruption
				const T e(element);

				// increase data block
				u32 newAlloc;
				switch (strategy)
				{
					case ALLOC_STRATEGY_DOUBLE:
						newAlloc = used + 1
								+ (allocated < 500 ?
										(allocated < 5 ? 5 : used) : used >> 2);
						break;
					default:
					case ALLOC_STRATEGY_SAFE:
						newAlloc = used + 1;
						break;
				}
				array<T>::reallocate(newAlloc);

				// move array content and construct new element
				// first move end one up
				for (u32 i = used; i > index; --i)
				{
					if (i < used)
						allocator.destruct(&data[i]);
					allocator.construct(&data[i], data[i - 1]); // data[i] = data[i-1];
				}
				// then add new element
				if (used > index)
					allocator.destruct(&data[index]);
				allocator.construct(&data[index], e); // data[index] = e;
			}
			else
			{
				// element inserted not at end
				if (used > index)
				{
					// create one new element at the end
					allocator.construct(&data[used], data[used - 1]);

					// move the rest of the array content
					for (u32 i = used - 1; i > index; --i)
					{
						data[i] = data[i - 1];
					}
					// insert the new element
					data[index] = element;
				}
				else
				{
					// insert the new element to the end
					allocator.construct(&data[index], element);
				}
			}
			// set to false as we don't know if we have the comparison operators
			is_sorted = false;
			++used;
		}

		//! Clears the array and deletes all allocated memory.
		template<class T>
		inline void array<T>::clear()
		{
			if (free_when_destroyed)
			{
				for (u32 i = 0; i < used; ++i)
					allocator.destruct(&data[i]);

				allocator.deallocate(data); // delete [] data;
			}
			data = 0;
			used = 0;
			allocated = 0;
			is_sorted = true;
		}

		//! Sets pointer to new array, using this as new workspace.
		template<class T>
		inline void array<T>::set_pointer(T* newPointer, u32 size,
				bool _is_sorted, bool _free_when_destroyed)
		{
			array<T>::clear();
			data = newPointer;
			allocated = size;
			used = size;
			is_sorted = _is_sorted;
			free_when_destroyed = _free_when_destroyed;
		}

		//! Sets if the array should delete the memory it uses upon destruction.
		template<class T>
		inline void array<T>::set_free_when_destroyed(bool f)
		{
			free_when_destroyed = f;
		}

		//! Sets the size of the array and allocates new elements if necessary.
		template<class T>
		inline void array<T>::set_used(u32 usedNow)
		{
			if (allocated < usedNow)
				array<T>::reallocate(usedNow);

			used = usedNow;
		}

		//! Assignment operator
		template<class T>
		inline array<T>& array<T>::operator=(const array<T>& other)
		{
			//handle self-assignment
			if (this == &other)
				return *this;

			strategy = other.strategy;

			if (data)
				array<T>::clear();

			//if (allocated < other.allocated)
			if (other.allocated == 0)
				data = 0;
			else
				data = allocator.allocate(other.allocated); // new T[other.allocated];

			used = other.used;
			free_when_destroyed = true;
			is_sorted = other.is_sorted;
			allocated = other.allocated;

			for (u32 i = 0; i < other.used; ++i)
				allocator.construct(&data[i], other.data[i]); // data[i] = other.data[i];

			return *this;
		}

		template<class T>
		inline bool array<T>::operator ==(const array<T>& other) const
		{
			if (used != other.used)
				return false;

			for (u32 i = 0; i < other.used; ++i)
				if (data[i] != other.data[i])
					return false;

			return true;
		}

		template<class T>
		inline bool array<T>::operator !=(const array<T>& other) const
		{
			return !(*this == other);
		}

		template<class T>
		inline T& array<T>::operator [](u32 index)
		{
			// access violation
			IRR_ASSERT(index >= 0 && index <= used)

			return data[index];
		}

		template<class T>
		inline const T& array<T>::operator [](u32 index) const
		{
			// access violation
			IRR_ASSERT(index >= 0 && index <= used);

			return data[index];
		}

		template<class T>
		inline T& array<T>::getLast()
		{
			// access violation
			IRR_ASSERT(used > 0)

			return data[used - 1];
		}

		template<class T>
		inline const T& array<T>::getLast() const
		{
			// access violation
			IRR_ASSERT(used > 0)

			return data[used - 1];
		}

		template<class T>
		inline T* array<T>::pointer()
		{
			return data;
		}

		template<class T>
		inline const T* array<T>::const_pointer() const
		{
			return data;
		}

		template<class T>
		inline u32 array<T>::size() const
		{
			return used;
		}

		template<class T>
		inline u32 array<T>::allocated_size() const
		{
			return allocated;
		}

		template<class T>
		inline bool array<T>::empty() const
		{
			return used == 0;
		}

		//! Sorts the array using heapsort.
		template<class T>
		inline void array<T>::sort()
		{
			if (!is_sorted && used > 1)
				heapsort(data, used);
			is_sorted = true;
		}

		//! Performs a binary search for an element, returns -1 if not found.
		template<class T>
		inline s32 array<T>::binary_search(const T& element)
		{
			array<T>::sort();
			return array<T>::binary_search(element, 0, used - 1);
		}

		//! Performs a binary search for an element if possible, returns -1 if not found.
		template<class T>
		inline s32 array<T>::binary_search(const T& element) const
		{
			if (is_sorted)
				return array<T>::binary_search(element, 0, used - 1);
			else
				return array<T>::linear_search(element);
		}

		//! Performs a binary search for an element, returns -1 if not found.
		template<class T>
		inline s32 array<T>::binary_search(const T& element, s32 left,
				s32 right) const
		{
			if (!used)
				return -1;

			s32 m;

			do
			{
				m = (left + right) >> 1;

				if (element < data[m])
					right = m - 1;
				else
					left = m + 1;

			} while ((element < data[m] || data[m] < element) && left <= right);
			// this last line equals to:
			// " while((element != array[m]) && left<=right);"
			// but we only want to use the '<' operator.
			// the same in next line, it is "(element == array[m])"

			if (!(element < data[m]) && !(data[m] < element))
				return m;

			return -1;
		}

		template<class T>
		inline s32 array<T>::binary_search_multi(const T& element, s32 &last)
		{
			array<T>::sort();
			s32 index = array<T>::binary_search(element, 0, used - 1);
			if (index < 0)
				return index;

			// The search can be somewhere in the middle of the set
			// look linear previous and past the index
			last = index;

			while (index > 0 && !(element < data[index - 1])
					&& !(data[index - 1] < element))
			{
				index -= 1;
			}
			// look linear up
			while (last < (s32) used - 1 && !(element < data[last + 1])
					&& !(data[last + 1] < element))
			{
				last += 1;
			}

			return index;
		}

		//! Finds an element in linear time, which is very slow.
		/** Use binary_search for faster finding. Only works if ==operator is
		 implemented.
		 \param element Element to search for.
		 \return Position of the searched element if it was found, otherwise -1
		 is returned. */
		template<class T>
		inline s32 array<T>::linear_search(const T& element) const
		{
			for (u32 i = 0; i < used; ++i)
				if (element == data[i])
					return (s32) i;

			return -1;
		}

		//! Finds an element in linear time, which is very slow.
		/** Use binary_search for faster finding. Only works if ==operator is
		 implemented.
		 \param element: Element to search for.
		 \return Position of the searched element if it was found, otherwise -1
		 is returned. */
		template<class T>
		inline s32 array<T>::linear_reverse_search(const T& element) const
		{
			for (s32 i = used - 1; i >= 0; --i)
				if (data[i] == element)
					return i;

			return -1;
		}

		//! Erases an element from the array.
		/** May be slow, because all elements following after the erased
		 element have to be copied.
		 \param index: Index of element to be erased. */
		template<class T>
		inline void array<T>::erase(u32 index)
		{
			// access violation
			IRR_ASSERT(index >= 0 && index <= used)

			for (u32 i = index + 1; i < used; ++i)
			{
				allocator.destruct(&data[i - 1]);
				allocator.construct(&data[i - 1], data[i]); // data[i-1] = data[i];
			}

			allocator.destruct(&data[used - 1]);

			--used;
		}

		//! Erases some elements from the array.
		/** May be slow, because all elements following after the erased
		 element have to be copied.
		 \param index: Index of the first element to be erased.
		 \param count: Amount of elements to be erased. */
		template<class T>
		inline void array<T>::erase(u32 index, s32 count)
		{
			IRR_ASSERT(index >= used || count < 1);

			if (index + count > used)
				count = used - index;

			u32 i;
			for (i = index; i < index + count; ++i)
				allocator.destruct(&data[i]);

			for (i = index + count; i < used; ++i)
			{
				if (i > index + count)
					allocator.destruct(&data[i - count]);

				allocator.construct(&data[i - count], data[i]); // data[i-count] = data[i];

				if (i >= used - count)
					allocator.destruct(&data[i]);
			}

			used -= count;
		}

		//! Sets if the array is sorted
		template<class T>
		inline void array<T>::set_sorted(bool _is_sorted)
		{
			is_sorted = _is_sorted;
		}

		//! Swap the content of this array container with the content of another array
		/** Afterwards this object will contain the content of the other object and the other
		 object will contain the content of this object.
		 \param other Swap content with this object	*/
		template<class T>
		inline void array<T>::swap(array<T>& other)
		{
			if (this == &other)
				return;

			core::swap(data, other.data);
			core::swap(allocated, other.allocated);
			core::swap(used, other.used);
			core::swap(allocator, other.allocator);	// memory is still released by the same allocator used for allocation
			eAllocStrategy helper_strategy(strategy);// can't use core::swap with bitfields
			strategy = other.strategy;
			other.strategy = helper_strategy;
			bool helper_free_when_destroyed(free_when_destroyed);
			free_when_destroyed = other.free_when_destroyed;
			other.free_when_destroyed = helper_free_when_destroyed;
			bool helper_is_sorted(is_sorted);
			is_sorted = other.is_sorted;
			other.is_sorted = helper_is_sorted;
		}

	} // end namespace core
} // end namespace irr

#endif

