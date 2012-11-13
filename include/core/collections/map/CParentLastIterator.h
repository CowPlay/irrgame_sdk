/*
 * CParentLastIterator.h
 *
 *  Created on: Sep 4, 2012
 *      Author: gregorytkach
 */

#ifndef CPARENTLASTITERATOR_H_
#define CPARENTLASTITERATOR_H_

#include "core/collections/map/RBTree.h"

namespace irrgame
{
	namespace core
	{
		//! Parent Last Iterator
		/** Traverse the tree from bottom to top.
		 Typical usage is when deleting all elements in the tree
		 because you must delete the children before you delete
		 their parent. */
		template<class Key, class Value>
		class CParentLastIterator
		{
			public:

				typedef RBTree<Key, Value> Node;

			public:
				/*
				 * Constructors
				 */

				//! Default constructor
				CParentLastIterator();

				//! Explicit Node* constructor
				explicit CParentLastIterator(Node* root);

				/*
				 * Methods
				 */

				void reset();

				bool atEnd() const;

				Node* getNode();

				/*
				 * Operators
				 */

				CParentLastIterator<Key, Value>& operator=(
						const CParentLastIterator<Key, Value>& src);

				void operator++(s32);

				Node* operator ->();
				Node& operator*();

			private:

				Node* getMin(Node* n);

				void inc();

			private:

				Node* Root;
				Node* Cur;
		};

		//-------- Public funcs

		template<class Key, class Value>
		inline CParentLastIterator<Key, Value>::CParentLastIterator() :
				Root(0), Cur(0)
		{
		}

		template<class Key, class Value>
		inline CParentLastIterator<Key, Value>::CParentLastIterator(
				RBTree<Key, Value>* root) :
				Root(root), Cur(0)
		{
			reset();
		}

		template<class Key, class Value>
		inline void CParentLastIterator<Key, Value>::reset()
		{
			Cur = getMin(Root);
		}

		template<class Key, class Value>
		inline bool CParentLastIterator<Key, Value>::atEnd() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return Cur == 0;
		}

		template<class Key, class Value>
		inline RBTree<Key, Value>* CParentLastIterator<Key, Value>::getNode()
		{
			return Cur;
		}

		template<class Key, class Value>
		inline CParentLastIterator<Key, Value>& CParentLastIterator<Key, Value>::operator=(
				const CParentLastIterator<Key, Value>& src)
		{
			Root = src.Root;
			Cur = src.Cur;
			return (*this);
		}

		template<class Key, class Value>
		inline void CParentLastIterator<Key, Value>::operator++(int)
		{
			inc();
		}

		template<class Key, class Value>
		inline RBTree<Key, Value>* CParentLastIterator<Key, Value>::operator ->()
		{
			return getNode();
		}

		template<class Key, class Value>
		inline RBTree<Key, Value>& CParentLastIterator<Key, Value>::operator*()
		{
			// access violation
			IRR_ASSERT (atEnd())

			return *getNode();
		}

		//-------- Private funcs
		template<class Key, class Value>
		inline RBTree<Key, Value>* CParentLastIterator<Key, Value>::getMin(
				RBTree<Key, Value>* n)
		{
			while (n != 0 && (n->getLeftChild() != 0 || n->getRightChild() != 0))
			{
				if (n->getLeftChild())
					n = n->getLeftChild();
				else
					n = n->getRightChild();
			}
			return n;
		}

		template<class Key, class Value>
		inline void CParentLastIterator<Key, Value>::inc()
		{
			// Already at end?
			if (Cur == 0)
				return;

			// Note: Starting point is the node as far down to the left as possible.

			// If current node has an uncle to the right, go to the
			// node as far down to the left from the uncle as possible
			// else just go up a level to the parent.
			if (Cur->isLeftChild() && Cur->getParent()->getRightChild())
			{
				Cur = getMin(Cur->getParent()->getRightChild());
			}
			else
				Cur = Cur->getParent();
		}
	// ParentLastIterator
	}
}

#endif /* CPARENTLASTITERATOR_H_ */
