/*
 * CParentIterator.h
 *
 *  Created on: Sep 4, 2012
 *      Author: gregorytkach
 */

#ifndef CPARENTFIRSTITERATOR_H_
#define CPARENTFIRSTITERATOR_H_

#include "RBTree.h"

namespace irrgame
{
	namespace core
	{
		//! Parent First Iterator.
		/** Traverses the tree from top to bottom. Typical usage is
		 when storing the tree structure, because when reading it
		 later (and inserting elements) the tree structure will
		 be the same. */
		template<class Key, class Value>
		class CParentFirstIterator
		{
			public:

				typedef RBTree<Key, Value> Node;

			public:

				//! Default constructor
				CParentFirstIterator();

				//! Excplicit Node* constructor
				explicit CParentFirstIterator(Node* root);

				void reset();

				bool atEnd() const;

				Node* getNode();

				CParentFirstIterator<Key, Value>& operator=(
						const CParentFirstIterator<Key, Value>& src);

				void operator++(s32);

				Node* operator ->();
				Node& operator*();

			private:

				void inc()
				{
					// Already at end?
					if (Cur == 0)
						return;

					// First we try down to the left
					if (Cur->getLeftChild())
					{
						Cur = Cur->getLeftChild();
					}
					else if (Cur->getRightChild())
					{
						// No left child? The we go down to the right.
						Cur = Cur->getRightChild();
					}
					else
					{
						// No children? Move up in the hierarcy until
						// we either reach 0 (and are finished) or
						// find a right uncle.
						while (Cur != 0)
						{
							// But if parent is left child and has a right "uncle" the parent
							// has already been processed but the uncle hasn't. Move to
							// the uncle.
							if (Cur->isLeftChild()
									&& Cur->getParent()->getRightChild())
							{
								Cur = Cur->getParent()->getRightChild();
								return;
							}
							Cur = Cur->getParent();
						}
					}
				}

			private:

				Node* Root;
				Node* Cur;

		};

		//------- Public funcs
		//! Default constructor
		template<class Key, class Value>
		inline CParentFirstIterator<Key, Value>::CParentFirstIterator() :
				Root(0), Cur(0)
		{
		}

		//! Excplicit Node* constructor
		template<class Key, class Value>
		inline CParentFirstIterator<Key, Value>::CParentFirstIterator(
				RBTree<Key, Value>* root) :
				Root(root), Cur(0)
		{
			reset();
		}

		template<class Key, class Value>
		inline void CParentFirstIterator<Key, Value>::reset()
		{
			Cur = Root;
		}

		template<class Key, class Value>
		inline bool CParentFirstIterator<Key, Value>::atEnd() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return Cur == 0;
		}

		template<class Key, class Value>
		inline RBTree<Key, Value>* CParentFirstIterator<Key, Value>::getNode()
		{
			return Cur;
		}

		template<class Key, class Value>
		inline CParentFirstIterator<Key, Value>& CParentFirstIterator<Key, Value>::operator=(
				const CParentFirstIterator<Key, Value>& src)
		{
			Root = src.Root;
			Cur = src.Cur;
			return (*this);
		}

		template<class Key, class Value>
		inline void CParentFirstIterator<Key, Value>::operator++(int)
		{
			inc();
		}

		template<class Key, class Value>
		inline RBTree<Key, Value>* CParentFirstIterator<Key, Value>::operator ->()
		{
			return getNode();
		}

		template<class Key, class Value>
		inline RBTree<Key, Value>& CParentFirstIterator<Key, Value>::operator*()
		{
			// access violation
			IRR_ASSERT(!atEnd())

			return *getNode();
		}
	}		// end namespace core
} // end namespace irrgame

#endif /* CPARENTFIRSTITERATOR_H_ */
