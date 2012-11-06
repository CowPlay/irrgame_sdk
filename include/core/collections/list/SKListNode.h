/*
 * SKListNode.h
 *
 *  Created on: Sep 3, 2012
 *      Author: gregorytkach
 */

#ifndef SKLISTNODE_H_
#define SKLISTNODE_H_

namespace irrgame
{
	namespace core
	{
		//! List element node with pointer to previous and next element in the list.
		template<class T>
		struct SKListNode
		{
			public:
				//! Default constructor
				SKListNode(const T& e);

			public:

				SKListNode* Next;
				SKListNode* Prev;
				T Element;
		};

		//!-------- SKListNode realization

		//! Default constructor
		template<class T>
		inline SKListNode<T>::SKListNode(const T& e) :
				Next(0), Prev(0), Element(e)
		{
		}

	}	// end namespace core
}	// end namespace irrgame

#endif /* SKLISTNODE_H_ */
