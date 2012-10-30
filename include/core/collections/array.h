// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine" and the "irrXML" project.
// For conditions of distribution and use, see copyright notice in irrlicht.h and irrXML.h

#ifndef _IRR_ARRAY_HINCLUDED__
#define _IRR_ARRAY_HINCLUDED__

#include "core/collections/ICollection.h"
#include "core/base/irrAllocator.h"
#include "threads/irrgameMonitor.h"
#include "core/math/irrMath.h"
#include "core/math/heapsort.h"
#include "stdio.h"
namespace irrgame
{
	namespace core
	{
		class stringc;

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
				/** \param startCount Amount of elements to pre-allocate. */
				array(u32 startCount);

				//! Copy constructor
				array(const array<T>& other);

				//! Destructor.
				/** Frees allocated memory, if setFreeWhenDestroyed was not set to
				 false by the user before. */
				virtual ~array();

				//! Reallocates the array, make it bigger or smaller.
				/** \param newSize New size of array. */
				void reallocate(u32 newSize);

				//! set a new allocation strategy
				/** if the maximum size of the array is unknown, you can define how big the
				 allocation should happen.
				 \param value New strategy to apply to this array. */
				void setAllocStrategy(eAllocStrategy value =
						ALLOC_STRATEGY_DOUBLE);

				//! Adds an element at back of array.
				/** If the array is too small to add this new element it is made bigger.
				 \param value: Element to add at the back of the array. */
				void pushBack(const T& value);

				//! Adds an element at the front of the array.
				/** If the array is to small to add this new element, the array is
				 made bigger. Please note that this is slow, because the whole array
				 needs to be copied for this.
				 \param value Element to add at the back of the array. */
				void pushFront(const T& value);

				//! Insert item into array at specified position.
				/** Please use this only if you know what you are doing (possible
				 performance loss). The preferred method of adding elements should be
				 pushBack().
				 \param value: Element to be inserted
				 \param index: Where position to insert the new element. */
				void insert(const T& value, u32 index = 0);

				//! Clears the array and deletes all allocated memory.
				void clear();

				//! Sets pointer to new array, using this as new workspace.
				/** Make sure that setFreeWhenDestroyed is used properly.
				 \param newPointer: Pointer to new array of elements.
				 \param size: Size of the new array.
				 \param isSorted Flag which tells whether the new array is already
				 sorted.
				 \param freeWhenDestroyed Sets whether the new memory area shall be
				 freed by the array upon destruction, or if this will be up to the user
				 application. */
				void setPointer(T* value, u32 size, bool isSorted = false,
						bool freeWhenDestroyed = true);

				//! Sets if the array should delete the memory it uses upon destruction.
				/** Also clear and setPointer will only delete the (original) memory
				 area if this flag is set to true, which is also the default. The
				 methods reallocate, setUsed, pushBack, pushFront, insert, and erase
				 will still try to deallocate the original memory, which might cause
				 troubles depending on the intended use of the memory area.
				 \param freeWhenDestroyed If true, the array frees the allocated memory in its
				 destructor, otherwise not. The default is true. */
				void setFreeWhenDestroyed(bool freeWhenDestroyed = true);

				//! Sets the size of the array and allocates new elements if necessary.
				/** Please note: This is only secure when using it with simple types,
				 because no default constructor will be called for the added elements.
				 \param value Amount of elements now used. */
				void setUsed(u32 value);

				//! Assignment operator
				array<T>& operator=(const array<T>& other);

				//! Equality operator. Typename T must implement operator!=
				bool operator ==(const array<T>& other) const;

				//! Inequality operator
				bool operator !=(const array<T>& other) const;

				//! Direct access operator
				T& operator [](u32 index);

				//! Direct const access operator
				const T& operator [](u32 index) const;

				//! Gets last element.
				//! Can be get or set value.
				//! Size must be greater than zero.
				T& getLast();

				//! Gets last element.
				//! Can be get or set value.
				//! Size must be greater than zero.
				const T& getLast() const;

				//! Gets a pointer to the array.
				/** \return Pointer to the array. */
				T* pointer();

				//! Gets a const pointer to the array.
				/** \return Pointer to the array. */
				const T* constPointer() const;

				//! Get number of occupied elements of the array.
				/** \return Size of elements in the array which are actually occupied. */
				u32 size() const;

				//! Get amount of memory allocated.
				/** \return Amount of memory allocated. The amount of bytes
				 allocated would be allocatedSize() * sizeof(ElementTypeUsed); */
				u32 allocatedSize() const;

				//! Check if array is empty.
				/** \return True if the array is empty false if not. */
				bool empty() const;

				//! Sorts the array using heapsort.
				/** There is no additional memory waste and the algorithm performs
				 O(n*log n) in worst case. */
				void sort();

				//! Performs a binary search for an element.
				//! Use only for non const arrays. For const arrays use linearSearch
				/** \param value: Element to search for.
				 \return Position of the searched element if it was found, otherwise irrNotFound
				 is returned. */
				s32 binarySearchFirst(const T& value);

				//! Performs a binary search for an element.
				//! Use only for non const arrays. For const arrays use linearSearch
				/** The array will be sorted before the binary search if it is not
				 already sorted.
				 \param value	Element to search for.
				 \return lastIndex of equal elements of the searched element if it was found,
				 otherwise irrNotFound is returned. */
				s32 binarySearchLast(const T& value);

				//! Finds an element in linear time, which is very slow.
				/** Use binarySearch for faster finding. Only works if ==operator is
				 implemented.
				 \param value Element to search for.
				 \return Position of the searched element if it was found, otherwise irrNotFound
				 is returned. */
				s32 linearSearch(const T& value) const;

				//! Finds an element in linear time, which is very slow.
				/** Use binarySearch for faster finding. Only works if ==operator is
				 implemented.
				 \param value: Element to search for.
				 \return Position of the searched element if it was found, otherwise irrNotFound
				 is returned. */
				s32 linearReverseSearch(const T& value) const;

				//! Erases an element from the array.
				/** May be slow, because all elements following after the erased
				 element have to be copied.
				 \param index: Index of element to be erased. */
				void erase(u32 index);

				//! Erases some elements from the array.
				/** May be slow, because all elements following after the erased
				 element have to be copied.
				 \param index: Index of the first element to be erased.
				 \param count: Amount of elements to be erased. */
				void erase(u32 index, s32 count);

				//! Sets if the array is sorted
				void setSorted(bool isSorted);

				//! Swap the content of this array container with the content of another array
				/** Afterwards this object will contain the content of the other object and the other
				 object will contain the content of this object.
				 \param other Swap content with this object	*/
				void swap(array<T>& other);

			private:

				//! Sorts the array using heapsort.
				//! Uses internal without lockers
				/** There is no additional memory waste and the algorithm performs
				 O(n*log n) in worst case. */
				void sortInternal();

				//! Reallocates the array, make it bigger or smaller.
				//! Uses internal without lockers
				/** \param newSize New size of array. */
				void reallocateInternal(u32 newSize);

				//! Clears the array and deletes all allocated memory.
				//! Uses internal without lockers
				void clearInternal();
			private:
				T* Data;
				u32 Allocated;
				u32 Used;
				irrAllocator<T> Allocator;
				threads::irrgameMonitor* Monitor;
				eAllocStrategy Strategy :4;
				bool FreeWhenDestroyed :1;
				bool IsSorted :1;
		};

		//! Default constructor for empty array.
		template<class T>
		inline array<T>::array() :
				Data(0), Allocated(0), Used(0), Monitor(0), Strategy(
						ALLOC_STRATEGY_DOUBLE), FreeWhenDestroyed(true), IsSorted(
						true)
		{
			Monitor = threads::createIrrgameMonitor();
		}

		//! Constructs an array and allocates an initial chunk of memory.
		template<class T>
		inline array<T>::array(u32 startCount) :
				Data(0), Allocated(0), Used(0), Monitor(0), Strategy(
						ALLOC_STRATEGY_DOUBLE), FreeWhenDestroyed(true), IsSorted(
						true)
		{
			Monitor = threads::createIrrgameMonitor();
			reallocate(startCount);
		}

		//! Copy constructor
		template<class T>
		inline array<T>::array(const array<T>& other) :
				Data(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
			*this = other;
		}

		//! Destructor.
		template<class T>
		inline array<T>::~array()
		{
			clear();

			if (Monitor)
				Monitor->drop();
		}

		//! Reallocates the array, make it bigger or smaller.
		template<class T>
		inline void array<T>::reallocate(u32 newSize)
		{
			Monitor->enter();
			reallocateInternal(newSize);
			Monitor->exit();
		}

		//! Reallocates the array, make it bigger or smaller.
		//! Uses internal without lockers
		template<class T>
		inline void array<T>::reallocateInternal(u32 newSize)
		{
			T* oldData = Data;

			Data = Allocator.allocate(newSize); //new T[newSize];
			Allocated = newSize;

			// copy old data
			s32 end = Used < newSize ? Used : newSize;

			for (s32 i = 0; i < end; ++i)
			{
				// data[i] = oldData[i];
				Allocator.construct(&Data[i], oldData[i]);
			}

			// destruct old data
			for (u32 j = 0; j < Used; ++j)
				Allocator.destruct(&oldData[j]);

			if (Allocated < Used)
				Used = Allocated;

			Allocator.deallocate(oldData); //delete [] oldData;
		}

		//! set a new allocation strategy
		template<class T>
		inline void array<T>::setAllocStrategy(eAllocStrategy value)
		{
			Monitor->enter();
			Strategy = value;
			Monitor->exit();
		}

		//! Adds an element at back of array.
		template<class T>
		inline void array<T>::pushBack(const T& value)
		{
			insert(value, Used);
		}

		//! Adds an element at the front of the array.
		template<class T>
		inline void array<T>::pushFront(const T& value)
		{
			insert(value);
		}

		//! Insert item into array at specified position.
		template<class T>
		inline void array<T>::insert(const T& value, u32 index)
		{
			Monitor->enter();

			// access violation
			IRR_ASSERT(index >= 0 && index <= Used)

			if (Used + 1 > Allocated)
			{
				// this doesn't work if the element is in the same
				// array. So we'll copy the element first to be sure
				// we'll get no data corruption
				const T e(value);

				// increase data block
				u32 newAlloc;
				switch (Strategy)
				{
					case ALLOC_STRATEGY_DOUBLE:
						newAlloc = Used + 1
								+ (Allocated < 500 ?
										(Allocated < 5 ? 5 : Used) : Used >> 2);
						break;
					default:
					case ALLOC_STRATEGY_SAFE:
						newAlloc = Used + 1;
						break;
				}

				reallocateInternal(newAlloc);

				// move array content and construct new element
				// first move end one up
				for (u32 i = Used; i > index; --i)
				{
					if (i < Used)
						Allocator.destruct(&Data[i]);
					Allocator.construct(&Data[i], Data[i - 1]); // data[i] = data[i-1];
				}
				// then add new element
				if (Used > index)
					Allocator.destruct(&Data[index]);
				Allocator.construct(&Data[index], e); // data[index] = e;
			}
			else
			{
				// element inserted not at end
				if (Used > index)
				{
					// create one new element at the end
					Allocator.construct(&Data[Used], Data[Used - 1]);

					// move the rest of the array content
					for (u32 i = Used - 1; i > index; --i)
					{
						Data[i] = Data[i - 1];
					}
					// insert the new element
					Data[index] = value;
				}
				else
				{
					// insert the new element to the end
					Allocator.construct(&Data[index], value);
				}
			}
			// set to false as we don't know if we have the comparison operators
			IsSorted = false;
			++Used;

			Monitor->exit();
		}

		//! Clears the array and deletes all allocated memory.
		template<class T>
		inline void array<T>::clear()
		{
			Monitor->enter();
			clearInternal();
			Monitor->exit();
		}

		//! Clears the array and deletes all allocated memory.
		//! Uses internal without lockers
		template<class T>
		inline void array<T>::clearInternal()
		{
			if (FreeWhenDestroyed)
			{
				for (u32 i = 0; i < Used; ++i)
					Allocator.destruct(&Data[i]);

				Allocator.deallocate(Data); // delete [] data;
			}

			Data = 0;
			Used = 0;
			Allocated = 0;
			IsSorted = true;
		}

		//! Sets pointer to new array, using this as new workspace.
		template<class T>
		inline void array<T>::setPointer(T* value, u32 size, bool isSorted,
				bool freeWhenDestroyed)
		{
			Monitor->enter();

			clearInternal();

			Data = value;
			Allocated = size;
			Used = size;
			IsSorted = isSorted;
			FreeWhenDestroyed = freeWhenDestroyed;

			Monitor->exit();
		}

		//! Sets if the array should delete the memory it uses upon destruction.
		template<class T>
		inline void array<T>::setFreeWhenDestroyed(bool value)
		{
			Monitor->enter();
			FreeWhenDestroyed = value;
			Monitor->exit();
		}

		//! Sets the size of the array and allocates new elements if necessary.
		template<class T>
		inline void array<T>::setUsed(u32 value)
		{
			Monitor->enter();
			if (Allocated < value)
				reallocateInternal(value);

			Used = value;
			Monitor->exit();
		}

		//! Assignment operator
		template<class T>
		inline array<T>& array<T>::operator=(const array<T>& other)
		{
			//handle self-assignment
			if (this == &other)
				return *this;

			Monitor->enter();
			other.Monitor->enter();

			Strategy = other.Strategy;

			if (Data)
				clearInternal();

			//if (allocated < other.allocated)
			if (other.Allocated == 0)
				Data = 0;
			else
				Data = Allocator.allocate(other.Allocated); // new T[other.allocated];

			Used = other.Used;
			FreeWhenDestroyed = true;
			IsSorted = other.IsSorted;
			Allocated = other.Allocated;

			for (u32 i = 0; i < other.Used; ++i)
				Allocator.construct(&Data[i], other.Data[i]); // data[i] = other.data[i];

			Monitor->exit();
			other.Monitor->exit();

			return *this;
		}

		template<class T>
		inline bool array<T>::operator ==(const array<T>& other) const
		{
			bool result = true;

			//handle self-check equality
			if (this == &other)
				return result;

			Monitor->enter();
			other.Monitor->enter();

			if (Used != other.Used)
			{
				result = false;
			}
			else
			{
				for (u32 i = 0; i < other.Used; ++i)
					if (Data[i] != other.Data[i])
					{
						result = false;
						break;
					}
			}

			Monitor->exit();
			other.Monitor->exit();

			return result;
		}

		template<class T>
		inline bool array<T>::operator !=(const array<T>& other) const
		{
			return !(*this == other);
		}

		template<class T>
		inline T& array<T>::operator [](u32 index)
		{
			Monitor->enter();

			// access violation
			IRR_ASSERT(index >= 0 && index <= Used)

			T& result = Data[index];

			Monitor->exit();

			return result;
		}

		template<class T>
		inline const T& array<T>::operator [](u32 index) const
		{
			Monitor->enter();

			// access violation
			IRR_ASSERT(index >= 0 && index <= Used)

			const T& result = Data[index];

			Monitor->exit();

			return result;
		}

		template<class T>
		inline T& array<T>::getLast()
		{
			Monitor->enter();

			// access violation
			IRR_ASSERT(Used > 0)

			T& result = Data[Used - 1];

			Monitor->exit();

			return result;
		}

		template<class T>
		inline const T& array<T>::getLast() const
		{
			Monitor->enter();

			// access violation
			IRR_ASSERT(Used > 0)

			const T& result = Data[Used - 1];

			Monitor->exit();

			return result;
		}

		template<class T>
		inline T* array<T>::pointer()
		{
			Monitor->enter();
			T* result = Data;
			Monitor->exit();

			return result;
		}

		template<class T>
		inline const T* array<T>::constPointer() const
		{
			Monitor->enter();
			const T* result = Data;
			Monitor->exit();

			return result;
		}

		template<class T>
		inline u32 array<T>::size() const
		{
			Monitor->enter();
			u32 result = Used;
			Monitor->exit();

			return result;
		}

		template<class T>
		inline u32 array<T>::allocatedSize() const
		{
			Monitor->enter();
			u32 result = Allocated;
			Monitor->exit();

			return result;
		}

		template<class T>
		inline bool array<T>::empty() const
		{
			Monitor->enter();
			bool result = Used == 0;
			Monitor->exit();

			return result;
		}

		//! Sorts the array using heapsort.
		template<class T>
		inline void array<T>::sort()
		{
			Monitor->enter();
			sortInternal();
			Monitor->exit();
		}

		//! Sorts the array using heapsort.
		template<class T>
		inline void array<T>::sortInternal()
		{
			if (!IsSorted && Used > 1)
				heapsort(Data, Used);

			IsSorted = true;
		}

		//! Performs a binary search for an element.
		//! Use only for non const arrays. For const arrays use linearSearch
		template<class T>
		inline s32 array<T>::binarySearchFirst(const T& value)
		{
			s32 result = IrrNotFound;

			Monitor->enter();

			if (!Used)
			{
				Monitor->exit();
				return result;
			}

			sortInternal();

			s32 left = 0;
			s32 right = Used - 1;

			s32 m;

			do
			{
				m = (left + right) >> 1;

				if (value < Data[m])
					right = m - 1;
				else
					left = m + 1;

			} while ((value < Data[m] || Data[m] < value) && left <= right);
			// this last line equals to:
			// " while((value != array[m]) && left<=right);"
			// but we only want to use the '<' operator.
			// the same in next line, it is "(value == array[m])"

			if (!(value < Data[m]) && !(Data[m] < value))
				result = m;

			Monitor->exit();

			return result;
		}

		//! Performs a binary search for an element.
		//! Use only for non const arrays. For const arrays use linearSearch
		template<class T>
		inline s32 array<T>::binarySearchLast(const T& value)
		{
			s32 result = IrrNotFound;

			Monitor->enter();

			sortInternal();

			s32 index = binarySearchFirst(value);

			if (index == result)
			{
				Monitor->exit();
				return result;
			}

			// The search can be somewhere in the middle of the set
			// look linear previous and past the index
			result = index;

			while (index > 0 && !(value < Data[index - 1])
					&& !(Data[index - 1] < value))
			{
				index -= 1;
			}

			// look linear up
			while (result < (s32) Used - 1 && !(value < Data[result + 1])
					&& !(Data[result + 1] < value))
			{
				result += 1;
			}

			Monitor->exit();

			return result;
		}

		//! Finds an element in linear time, which is very slow.
		template<class T>
		inline s32 array<T>::linearSearch(const T& value) const
		{
			s32 result = IrrNotFound;

			Monitor->enter();

			for (u32 i = 0; i < Used; ++i)
				if (value == Data[i])
				{
					result = (s32) i;
					break;
				}

			Monitor->exit();

			return result;
		}

		//! Finds an element in linear time, which is very slow.
		template<class T>
		inline s32 array<T>::linearReverseSearch(const T& value) const
		{
			s32 result = IrrNotFound;

			Monitor->enter();

			for (s32 i = Used - 1; i >= 0; --i)
				if (Data[i] == value)
				{
					result = i;
					break;
				}

			Monitor->exit();

			return result;
		}

		//! Erases an element from the array.
		template<class T>
		inline void array<T>::erase(u32 index)
		{
			Monitor->enter();

			// access violation
			IRR_ASSERT(index >= 0 && index <= Used)

			for (u32 i = index + 1; i < Used; ++i)
			{
				Allocator.destruct(&Data[i - 1]);
				Allocator.construct(&Data[i - 1], Data[i]); // data[i-1] = data[i];
			}

			Allocator.destruct(&Data[Used - 1]);

			--Used;

			Monitor->exit();
		}

		//! Erases some elements from the array.
		template<class T>
		inline void array<T>::erase(u32 index, s32 count)
		{
			Monitor->enter();

			IRR_ASSERT(index >= Used || count < 1);

			if (index + count > Used)
				count = Used - index;

			u32 i;
			for (i = index; i < index + count; ++i)
				Allocator.destruct(&Data[i]);

			for (i = index + count; i < Used; ++i)
			{
				if (i > index + count)
					Allocator.destruct(&Data[i - count]);

				Allocator.construct(&Data[i - count], Data[i]); // data[i-count] = data[i];

				if (i >= Used - count)
					Allocator.destruct(&Data[i]);
			}

			Used -= count;

			Monitor->exit();
		}

		//! Sets if the array is sorted
		template<class T>
		inline void array<T>::setSorted(bool isSorted)
		{
			Monitor->enter();
			IsSorted = isSorted;
			Monitor->exit();
		}

		//! Swap the content of this array container with the content of another array
		template<class T>
		inline void array<T>::swap(array<T>& other)
		{
			// handle self swap
			if (this == &other)
				return;

			other.Monitor->enter();
			Monitor->enter();

			core::swap(Monitor, other.Monitor);
			core::swap(Data, other.Data);
			core::swap(Allocated, other.Allocated);
			core::swap(Used, other.Used);
			core::swap(Allocator, other.Allocator);	// memory is still released by the same allocator used for allocation
			eAllocStrategy helperStrategy(Strategy);// can't use core::swap with bitfields
			Strategy = other.Strategy;
			other.Strategy = helperStrategy;

			bool helperFreeWhenDestroyed(FreeWhenDestroyed);
			FreeWhenDestroyed = other.FreeWhenDestroyed;
			other.FreeWhenDestroyed = helperFreeWhenDestroyed;

			bool helperIsSorted(IsSorted);
			IsSorted = other.IsSorted;
			other.IsSorted = helperIsSorted;

			Monitor->exit();
			other.Monitor->exit();
		}
	} // end namespace core
} // end namespace irrgame

//! array typedefs
typedef irrgame::core::array<s32> arrayi;
typedef irrgame::core::array<u32> arrayu;
typedef irrgame::core::array<f32> arrayf;
typedef irrgame::core::array<irrgame::core::stringc> arraystr;

#endif

