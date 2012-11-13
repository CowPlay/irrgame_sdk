/*
 * ICollection.h
 *
 *  Created on: Sep 5, 2012
 *      Author: gregorytkach
 */

#ifndef ICOLLECTION_H_
#define ICOLLECTION_H_

#include "compileConfig.h"

namespace irrgame
{
	namespace core
	{
		template<class T>
		class ICollection
		{
			public:
				//! Destructor
				virtual ~ICollection()
				{
				}

				//! Adds an element at back of array.
				/** If the array is too small to add this new element it is made bigger.
				 \param element: Element to add at the back of the array. */
				virtual void pushBack(const T& element) = 0;

				//! Adds an element at the front of the array.
				/** If the array is to small to add this new element, the array is
				 made bigger. Please note that this is slow, because the whole array
				 needs to be copied for this.
				 \param element Element to add at the back of the array. */
				virtual void pushFront(const T& element) = 0;

				//! Get number of occupied elements of the array.
				/** \return Size of elements in the array which are actually occupied. */
				virtual u32 size() const = 0;

				//! Returns last element of collection
				virtual T& getLast() = 0;

				//! Returns last element of collection
				virtual const T& getLast() const = 0;

				//! Direct access operator
				/* \param index Index of element. Must be lower than collection size
				 * \return Element by index for getting or setting value. */
				virtual T& operator[](u32 index) = 0;

				//! Direct const access operator
				/* \param index Index of element. Must be lower than collection size
				 * \return Element by index for getting or setting value. */
				virtual const T& operator[](u32 index) const = 0;
		};
	}
}

#endif /* ICOLLECTION_H_ */
