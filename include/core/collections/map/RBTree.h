/*
 * RBTree.h
 *
 *  Created on: Sep 4, 2012
 *      Author: gregorytkach
 */

#ifndef RBTREE_H_
#define RBTREE_H_

namespace irrgame
{
	namespace core
	{

		//! red/black tree for map
		template<class Key, class Value>
		class RBTree
		{
			public:

				RBTree(const Key& k, const Value& v);

				void setLeftChild(RBTree<Key, Value>* p);
				void setRightChild(RBTree<Key, Value>* p);

				void setParent(RBTree<Key, Value>* p);
				void setValue(const Value& v);

				void setRed();
				void setBlack();

				RBTree<Key, Value>* getLeftChild() const;
				RBTree<Key, Value>* getRightChild() const;
				RBTree<Key, Value>* getParent() const;
				Value getValue() const;

				Key getKey() const;

				bool isRoot() const;
				bool isLeaf() const;

				bool isLeftChild() const;
				bool isRightChild() const;

				u32 getLevel() const;

				bool isRed() const;
				bool isBlack() const;

			private:
				RBTree();

			private:

				RBTree<Key, Value>* LeftChild;
				RBTree<Key, Value>* RightChild;

				RBTree<Key, Value>* Parent;

				Key _Key;
				Value _Value;

				bool IsRed;
		};

		template<class Key, class Value>
		inline RBTree<Key, Value>::RBTree(const Key& k, const Value& v) :
				LeftChild(0), RightChild(0), Parent(0), _Key(k), _Value(v), IsRed(
						true)
		{
		}

		template<class Key, class Value>
		inline void RBTree<Key, Value>::setLeftChild(RBTree<Key, Value>* p)
		{
			LeftChild = p;
			if (p)
			{
				p->setParent(this);
			}
		}

		template<class Key, class Value>
		inline void RBTree<Key, Value>::setRightChild(RBTree<Key, Value>* p)
		{
			RightChild = p;
			if (p)
				p->setParent(this);
		}

		template<class Key, class Value>
		inline void RBTree<Key, Value>::setParent(RBTree<Key, Value>* p)
		{
			Parent = p;
		}

		template<class Key, class Value>
		inline void RBTree<Key, Value>::setValue(const Value& v)
		{
			_Value = v;
		}

		template<class Key, class Value>
		inline void RBTree<Key, Value>::setRed()
		{
			IsRed = true;
		}

		template<class Key, class Value>
		inline void RBTree<Key, Value>::setBlack()
		{
			IsRed = false;
		}

		template<class Key, class Value>
		inline RBTree<Key, Value>* RBTree<Key, Value>::getLeftChild() const
		{
			return LeftChild;
		}

		template<class Key, class Value>
		inline RBTree<Key, Value>* RBTree<Key, Value>::getRightChild() const
		{
			return RightChild;
		}

		template<class Key, class Value>
		inline RBTree<Key, Value>* RBTree<Key, Value>::getParent() const
		{
			return Parent;
		}

		template<class Key, class Value>
		inline Value RBTree<Key, Value>::getValue() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return _Value;
		}

		template<class Key, class Value>
		inline Key RBTree<Key, Value>::getKey() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return _Key;
		}

		template<class Key, class Value>
		inline bool RBTree<Key, Value>::isRoot() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return Parent == 0;
		}

		template<class Key, class Value>
		inline bool RBTree<Key, Value>::isLeftChild() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return (Parent != 0) && (Parent->getLeftChild() == this);
		}

		template<class Key, class Value>
		inline bool RBTree<Key, Value>::isRightChild() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return (Parent != 0) && (Parent->getRightChild() == this);
		}

		template<class Key, class Value>
		inline bool RBTree<Key, Value>::isLeaf() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return (LeftChild == 0) && (RightChild == 0);
		}

		template<class Key, class Value>
		inline u32 RBTree<Key, Value>::getLevel() const
		{
			if (isRoot())
				return 1;
			else
				return getParent()->getLevel() + 1;
		}

		template<class Key, class Value>
		inline bool RBTree<Key, Value>::isRed() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return IsRed;
		}

		template<class Key, class Value>
		inline bool RBTree<Key, Value>::isBlack() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return !IsRed;
		}
	} // end namespace core
} // end namespace irrgame

#endif /* RBTREE_H_ */
