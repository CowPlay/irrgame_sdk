/*
 * irrAllocator.h
 *
 *  Created on: Nov 1, 2012
 *      Author: gregorytkach
 */

#ifndef IRRALLOCATOR_H_
#define IRRALLOCATOR_H_

#include "compileConfig.h"

#include <new>
// necessary for older compilers
#include <memory.h>
namespace irrgame
{
	namespace core
	{
		//! Very simple allocator implementation, containers using it can be used across dll boundaries
		template<typename T>
		class irrAllocator
		{
			public:

				//! Destructor
				virtual ~irrAllocator();

				//! Allocate memory for an array of objects
				T* allocate(size_t cnt);

				//! Deallocate memory for an array of objects
				void deallocate(T* ptr);

				//! Construct an element
				void construct(T* ptr, const T&e);

				//! Destruct an element
				void destruct(T* ptr);

			protected:

				virtual void* internalNew(size_t cnt);

				virtual void internalDelete(void* ptr);

		};

		//! Destructor
		template<typename T>
		inline irrAllocator<T>::~irrAllocator()
		{
		}

		//! Allocate memory for an array of objects
		template<typename T>
		inline T* irrAllocator<T>::allocate(size_t cnt)
		{
			return (T*) internalNew(cnt * sizeof(T));
		}

		//! Deallocate memory for an array of objects
		template<typename T>
		inline void irrAllocator<T>::deallocate(T* ptr)
		{
			internalDelete(ptr);
		}

		//! Construct an element
		template<typename T>
		inline void irrAllocator<T>::construct(T* ptr, const T&e)
		{
			new ((void*) ptr) T(e);
		}

		//! Destruct an element
		template<typename T>
		inline void irrAllocator<T>::destruct(T* ptr)
		{
			ptr->~T();
		}

		template<typename T>
		inline void* irrAllocator<T>::internalNew(size_t cnt)
		{
			return operator new(cnt);
		}

		template<typename T>
		inline void irrAllocator<T>::internalDelete(void* ptr)
		{
			operator delete(ptr);
		}

	}  // namespace core

}  // namespace irrgame

#endif /* IRRALLOCATOR_H_ */
