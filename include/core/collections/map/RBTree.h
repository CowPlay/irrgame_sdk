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
		template<class KType, class VType>
		class RBTree
		{
			public:

				RBTree(const KType& k, const VType& v);

				void setLeftChild(RBTree<KType, VType>* p);
				void setRightChild(RBTree<KType, VType>* p);

				void setParent(RBTree<KType, VType>* p);
				void setValue(const VType& v);

				void setRed();
				void setBlack();

				RBTree<KType, VType>* getLeftChild() const;
				RBTree<KType, VType>* getRightChild() const;
				RBTree<KType, VType>* getParent() const;
				VType getValue() const;

				KType getKey() const;

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

				RBTree<KType, VType>* LeftChild;
				RBTree<KType, VType>* RightChild;

				RBTree<KType, VType>* Parent;

				KType Key;
				VType Value;

				bool IsRed;
		};

		template<class KType, class VType>
		inline RBTree<KType, VType>::RBTree(const KType& k, const VType& v) :
				LeftChild(0), RightChild(0), Parent(0), Key(k), Value(v), IsRed(
						true)
		{
		}

		template<class KType, class VType>
		inline void RBTree<KType, VType>::setLeftChild(RBTree<KType, VType>* p)
		{
			LeftChild = p;
			if (p)
			{
				p->setParent(this);
			}
		}

		template<class KType, class VType>
		inline void RBTree<KType, VType>::setRightChild(RBTree<KType, VType>* p)
		{
			RightChild = p;
			if (p)
				p->setParent(this);
		}

		template<class KType, class VType>
		inline void RBTree<KType, VType>::setParent(RBTree<KType, VType>* p)
		{
			Parent = p;
		}

		template<class KType, class VType>
		inline void RBTree<KType, VType>::setValue(const VType& v)
		{
			Value = v;
		}

		template<class KType, class VType>
		inline void RBTree<KType, VType>::setRed()
		{
			IsRed = true;
		}

		template<class KType, class VType>
		inline void RBTree<KType, VType>::setBlack()
		{
			IsRed = false;
		}

		template<class KType, class VType>
		inline RBTree<KType, VType>* RBTree<KType, VType>::getLeftChild() const
		{
			return LeftChild;
		}

		template<class KType, class VType>
		inline RBTree<KType, VType>* RBTree<KType, VType>::getRightChild() const
		{
			return RightChild;
		}

		template<class KType, class VType>
		inline RBTree<KType, VType>* RBTree<KType, VType>::getParent() const
		{
			return Parent;
		}

		template<class KType, class VType>
		inline VType RBTree<KType, VType>::getValue() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return Value;
		}

		template<class KType, class VType>
		inline KType RBTree<KType, VType>::getKey() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return Key;
		}

		template<class KType, class VType>
		inline bool RBTree<KType, VType>::isRoot() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return Parent == 0;
		}

		template<class KType, class VType>
		inline bool RBTree<KType, VType>::isLeftChild() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return (Parent != 0) && (Parent->getLeftChild() == this);
		}

		template<class KType, class VType>
		inline bool RBTree<KType, VType>::isRightChild() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return (Parent != 0) && (Parent->getRightChild() == this);
		}

		template<class KType, class VType>
		inline bool RBTree<KType, VType>::isLeaf() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return (LeftChild == 0) && (RightChild == 0);
		}

		template<class KType, class VType>
		inline u32 RBTree<KType, VType>::getLevel() const
		{
			if (isRoot())
				return 1;
			else
				return getParent()->getLevel() + 1;
		}

		template<class KType, class VType>
		inline bool RBTree<KType, VType>::isRed() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return IsRed;
		}

		template<class KType, class VType>
		inline bool RBTree<KType, VType>::isBlack() const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return !IsRed;
		}
	} // end namespace core
} // end namespace irrgame

#endif /* RBTREE_H_ */
