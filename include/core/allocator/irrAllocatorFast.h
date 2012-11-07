// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine" and the "irrXML" project.
// For conditions of distribution and use, see copyright notice in irrlicht.h and irrXML.h

#ifndef __IRR_ALLOCATOR_H_INCLUDED__
#define __IRR_ALLOCATOR_H_INCLUDED__

#include "compileConfig.h"
#include <new>
// necessary for older compilers
#include <memory.h>

namespace irrgame
{
	namespace core
	{

		//! Fast allocator, only to be used in containers inside the same memory heap.
		/** Containers using it are NOT able to be used it across dll boundaries. Use this
		 when using in an internal class or function or when compiled into a static lib */
		template<class T>
		class irrAllocatorFast
		{
			public:

				//! Allocate memory for an array of objects
				T* allocate(size_t cnt);

				//! Deallocate memory for an array of objects
				void deallocate(T* ptr);

				//! Construct an element
				void construct(T* ptr, const T&e);

				//! Destruct an element
				void destruct(T* ptr);
		};

		//! Allocate memory for an array of objects
		template<typename T>
		inline T* irrAllocatorFast<T>::allocate(size_t cnt)
		{
			return (T*) operator new(cnt * sizeof(T));
		}

		//! Deallocate memory for an array of objects
		template<typename T>
		inline void irrAllocatorFast<T>::deallocate(T* ptr)
		{
			operator delete(ptr);
		}

		//! Construct an element
		template<typename T>
		inline void irrAllocatorFast<T>::construct(T* ptr, const T&e)
		{
			new ((void*) ptr) T(e);
		}

		//! Destruct an element
		template<typename T>
		inline void irrAllocatorFast<T>::destruct(T* ptr)
		{
			ptr->~T();
		}

	} // end namespace core
} // end namespace irr

#endif

