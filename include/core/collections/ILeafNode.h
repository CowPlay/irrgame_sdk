/*
 * IHierarchicalCollection.h
 *
 *  Created on: Sep 11, 2012
 *      Author: gregorytkach
 */

#ifndef ILEAFNODE_H_
#define ILEAFNODE_H_

#include "core/base/IReferenceCounted.h"
#include "core/collections/list/list.h"

namespace irrgame
{
	namespace core
	{
		template<class T>
		class ILeafNode;

		//! LeafNode interface
		/** A leaf node is a node in the some hierarchical graph. Every leaf
		 node may have children, which are also leaf nodes. */
		template<class T>
		class ILeafNode: public IReferenceCounted
		{
			public:
				typedef ILeafNode<T> LeafNode;

			public:
				//! Destructor
				virtual ~ILeafNode();

				//! Adds a child to this scene node.
				/** If the leaf node already has a parent it is first removed
				 from the other parent.
				 \param child A pointer to the new child. */
				virtual void addChild(LeafNode* child);

				//! Removes a child from this leaf node.
				/** If found in the children list, the child pointer is also
				 dropped and might be deleted if no other grab exists.
				 \param child A pointer to the child which shall be removed. */
				virtual void removeChild(LeafNode* child);

				//! Removes all children of this scene node
				/** The scene nodes found in the children list are also dropped
				 and might be deleted if no other grab exists on them.*/
				virtual void removeAll();

				//! Removes this scene node from the scene
				/** If no other grab exists for this node, it will be deleted. */
				virtual void remove();

				//! Returns a const reference to the list of all children.
				/** \return The list of all children of this node. */
				const list<LeafNode*>& getChildren() const;

				//! Changes the parent of the scene node.
				/** \param newParent The new parent to be used. */
				virtual void setParent(LeafNode* value);

			protected:

				//! Pointer to the parent
				LeafNode* Parent;

				//! List of all children of this node
				list<LeafNode*> Children;
		};

		//! Destructor
		template<class T>
		inline ILeafNode<T>::~ILeafNode()
		{
			// delete all children
			removeAll();
		}

		//! Adds a child to this scene node.
		template<class T>
		inline void ILeafNode<T>::addChild(LeafNode* child)
		{
			if (child && (child != this))
			{
				child->grab();
				child->remove(); // remove from old parent
				Children.push_back(child);
				child->Parent = this;
			}
		}

		//! Removes a child from this scene node.
		template<class T>
		inline void ILeafNode<T>::removeChild(LeafNode* child)
		{
			CIterator<LeafNode*> it = Children.begin();

			for (; it != Children.end(); ++it)
				if ((*it) == child)
				{
					(*it)->Parent = 0;
					(*it)->drop();
					Children.erase(it);
				}
		}

		//! Removes all children of this scene node
		template<class T>
		inline void ILeafNode<T>::removeAll()
		{
			CIterator<LeafNode*> it = Children.begin();

			for (; it != Children.end(); ++it)
			{
				(*it)->Parent = 0;
				(*it)->drop();
			}

			Children.clear();
		}

		//! Removes this scene node from the scene
		template<class T>
		inline void ILeafNode<T>::remove()
		{
			if (Parent)
				Parent->removeChild(this);
		}

		//! Returns a const reference to the list of all children.
		template<class T>
		inline const list<ILeafNode<T>*>& ILeafNode<T>::getChildren() const
		{
			return Children;
		}

		//! Changes the parent of the scene node.
		template<class T>
		inline void ILeafNode<T>::setParent(LeafNode* value)
		{
			grab();
			remove();

			Parent = value;

			if (Parent)
				Parent->addChild(this);

			drop();
		}

	}
// namespace core
}// namespace irrgame

#endif /* ILEAFNODE_H_ */
