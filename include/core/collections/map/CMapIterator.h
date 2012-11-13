/*
 * Iterator.h
 *
 *  Created on: Sep 4, 2012
 *      Author: gregorytkach
 */

#ifndef CMAPITERATOR_H_
#define CMAPITERATOR_H_

#include "core/collections/map/RBTree.h"

namespace irrgame
{
	namespace core
	{
		//! Normal Iterator
		template<class KType, class VType>
		class CMapIterator
		{
			public:

				typedef RBTree<KType, VType> Node;

			public:

				/*
				 * Constructors
				 */

				//! Default constructor
				CMapIterator();

				// Constructor(Node*)
				CMapIterator(Node* root);

				// Copy constructor
				CMapIterator(const CMapIterator& src);

				/*
				 * Methods
				 */

				void reset(bool atLowest = true);

				bool atEnd() const;

				Node* getNode();

				/*
				 * Operators
				 */

				CMapIterator& operator=(const CMapIterator& src);

				void operator++(s32);
				void operator--(s32);

				Node* operator ->();
				Node& operator*();

			private:

				Node* getMin(Node* n);
				Node* getMax(Node* n);

				void inc();
				void dec();

			private:

				Node* Root;
				Node* Cur;
		};

		//!--------- Public funcs

		//! Default constructor
		template<class KType, class VType>
		inline CMapIterator<KType, VType>::CMapIterator() :
				Root(0), Cur(0)
		{
		}

		// Constructor(Node*)
		template<class KType, class VType>
		inline CMapIterator<KType, VType>::CMapIterator(Node* root) :
				Root(root)
		{
			reset();
		}

		// Copy constructor
		template<class KType, class VType>
		inline CMapIterator<KType, VType>::CMapIterator(const CMapIterator& src) :
				Root(src.Root), Cur(src.Cur)
		{
		}

		template<class KType, class VType>
		inline void CMapIterator<KType, VType>::reset(bool atLowest)
		{
			if (atLowest)
			{
				Cur = getMin(Root);
			}
			else
			{
				Cur = getMax(Root);
			}
		}

		template<class KType, class VType>
		inline bool CMapIterator<KType, VType>::atEnd() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return Cur == 0;
		}

		template<class KType, class VType>
		inline RBTree<KType, VType>* CMapIterator<KType, VType>::getNode()
		{
			return Cur;
		}

		template<class KType, class VType>
		inline CMapIterator<KType, VType>& CMapIterator<KType, VType>::operator=(
				const CMapIterator& src)
		{
			Root = src.Root;
			Cur = src.Cur;

			return (*this);
		}

		template<class KType, class VType>
		inline void CMapIterator<KType, VType>::operator++(s32)
		{
			inc();
		}

		template<class KType, class VType>
		inline void CMapIterator<KType, VType>::operator--(s32)
		{
			dec();
		}

		template<class KType, class VType>
		inline RBTree<KType, VType>* CMapIterator<KType, VType>::operator ->()
		{
			return getNode();
		}

		template<class KType, class VType>
		inline RBTree<KType, VType>& CMapIterator<KType, VType>::operator*()
		{
			// access violation
			IRR_ASSERT(!atEnd())

			return *Cur;
		}

		//!--------- Private funcs
		template<class KType, class VType>
		inline RBTree<KType, VType>* CMapIterator<KType, VType>::getMin(Node* n)
		{
			while (n && n->getLeftChild())
			{
				n = n->getLeftChild();
			}

			return n;
		}

		template<class KType, class VType>
		inline RBTree<KType, VType>* CMapIterator<KType, VType>::getMax(Node* n)
		{
			while (n && n->getRightChild())
				n = n->getRightChild();
			return n;
		}

		template<class KType, class VType>
		inline void CMapIterator<KType, VType>::inc()
		{
			// Already at end?
			if (Cur == 0)
				return;

			if (Cur->getRightChild())
			{
				// If current node has a right child, the next higher node is the
				// node with lowest key beneath the right child.
				Cur = getMin(Cur->getRightChild());
			}
			else if (Cur->isLeftChild())
			{
				// No right child? Well if current node is a left child then
				// the next higher node is the parent
				Cur = Cur->getParent();
			}
			else
			{
				// Current node neither is left child nor has a right child.
				// Ie it is either right child or root
				// The next higher node is the parent of the first non-right
				// child (ie either a left child or the root) up in the
				// hierarchy. Root's parent is 0.
				while (Cur->isRightChild())
				{
					Cur = Cur->getParent();
				}
				Cur = Cur->getParent();
			}
		}

		template<class KType, class VType>
		inline void CMapIterator<KType, VType>::dec()
		{
			// Already at end?
			if (Cur == 0)
			{
				return;
			}

			if (Cur->getLeftChild())
			{
				// If current node has a left child, the next lower node is the
				// node with highest key beneath the left child.
				Cur = getMax(Cur->getLeftChild());
			}
			else if (Cur->isRightChild())
			{
				// No left child? Well if current node is a right child then
				// the next lower node is the parent
				Cur = Cur->getParent();
			}
			else
			{
				// Current node neither is right child nor has a left child.
				// Ie it is either left child or root
				// The next higher node is the parent of the first non-left
				// child (ie either a right child or the root) up in the
				// hierarchy. Root's parent is 0.

				while (Cur->isLeftChild())
				{
					Cur = Cur->getParent();
				}
				Cur = Cur->getParent();
			}
		}

	} // end namespace core
} // end namespace irrgame

#endif /* CMAPITERATOR_H_ */
