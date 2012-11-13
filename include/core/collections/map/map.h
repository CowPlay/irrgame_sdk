// Copyright (C) 2006-2009 by Kat'Oun
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_MAP_H_INCLUDED__
#define __IRR_MAP_H_INCLUDED__

#include "core/collections/map/CAccessClass.h"
#include "core/collections/map/CMapIterator.h"
#include "core/collections/map/CParentFirstIterator.h"
#include "core/collections/map/CParentLastIterator.h"

#include "core/math/SharedMath.h"
#include "threads/irrgameMonitor.h"

namespace irrgame
{
	namespace core
	{

		//! map template for associative arrays using a red-black tree
		template<class KType, class VType>
		class map
		{
			public:

				typedef RBTree<KType, VType> Node;
				typedef CMapIterator<KType, VType> Iterator;
				typedef CParentFirstIterator<KType, VType> ParentFirstIterator;
				typedef CParentLastIterator<KType, VType> ParentLastIterator;
				typedef CAccessClass<KType, VType> AccessClass;

			public:

				//! Default constructor.
				map();

				//! Destructor
				virtual ~map();

				/*
				 * Methods
				 */

				//! Inserts a new node into the tree
				/** \param keyNew: the index for this value
				 \param v: the value to insert */
				void insert(const KType& keyNew, const VType& v);

				//! Removes a node from the tree and returns it.
				/** The returned node must be deleted by the user
				 \param k the key to remove
				 \return A pointer to the node*/
				Node* delink(const KType& k);

				//! Removes a node from the tree and deletes it.
				void remove(const KType& k);

				//! Clear the entire tree
				void clear();

				//! Is the tree empty?
				//! \return Returns true if empty, false if not
				bool empty() const;

				//! Search for a node with the specified key.
				//! \param keyToFind: The key to find
				//! \return Returns 0 if node couldn't be found.
				Node* find(const KType& keyToFind) const;

				//! Gets the root element.
				//! \return Returns a pointer to the root node, or
				//! 0 if the tree is empty.
				Node* getRoot() const;

				//! Returns the number of nodes in the tree.
				u32 size() const;

				//! Swap the content of this map container with the content of another map
				/** Afterwards this object will contain the content of the other object and the other
				 object will contain the content of this object. Iterators will afterwards be valid for
				 the swapped object.
				 \param other Swap content with this object	*/
				void swap(map<KType, VType>& other);

				/*
				 * Iterators
				 */

				//! Returns an iterator
				Iterator getIterator();
				//! Returns a ParentFirstIterator.
				//! Traverses the tree from top to bottom. Typical usage is
				//! when storing the tree structure, because when reading it
				//! later (and inserting elements) the tree structure will
				//! be the same.
				ParentFirstIterator getParentFirstIterator();

				//! Returns a ParentLastIterator to traverse the tree from
				//! bottom to top.
				//! Typical usage is when deleting all elements in the tree
				//! because you must delete the children before you delete
				//! their parent.
				ParentLastIterator getParentLastIterator();

				/*
				 * Operators
				 */

				//! operator [] for access to elements
				/** for example myMap["key"] */
				AccessClass operator[](const KType& k);

			private:

				/*
				 * Disabled methods
				 */

				// Copy constructor and assignment operator deliberately
				// defined but not implemented. The tree should never be
				// copied, pass along references to it instead.
				explicit map(const map& src);
				map& operator=(const map& src);

			private:

				//! Search for a node with the specified key.
				//! \param keyToFind: The key to find
				//! \return Returns 0 if node couldn't be found.
				Node* findInternal(const KType& keyToFind) const;

				//! Set node as new root.
				/** The node will be set to black, otherwise core dumps may arise
				 (patch provided by rogerborg).
				 \param newRoot Node which will be the new root
				 */
				void setRoot(Node* newRoot);

				//! Insert a node into the tree without using any fancy balancing logic.
				void insert(Node* newNode);

				//! Rotate left.
				//! Pull up node's right child and let it knock node down to the left
				void rotateLeft(Node* p);

				//! Rotate right.
				//! Pull up node's left child and let it knock node down to the right
				void rotateRight(Node* p);

			private:

				//! The top node. 0 if empty.
				Node* Root;
				//! Number of nodes in the tree
				u32 Size;
				threads::irrgameMonitor* Monitor;
		};

		//! Default constructor.
		template<class KType, class VType>
		inline map<KType, VType>::map() :
				Root(0), Size(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
		}

		//! Destructor
		template<class KType, class VType>
		inline map<KType, VType>::~map()
		{
			clear();

			if (Monitor)
				Monitor->drop();
		}

		//! Inserts a new node into the tree
		/** \param keyNew: the index for this value
		 \param v: the value to insert
		 \return True if successful, false if it fails (already exists) */
		template<class KType, class VType>
		inline void map<KType, VType>::insert(const KType& keyNew,
				const VType& v)
		{
			// First insert node the "usual" way (no fancy balance logic yet)
			Node* newNode = new Node(keyNew, v);

			insert(newNode);

			// Then attend a balancing party
			while (!newNode->isRoot() && (newNode->getParent()->isRed()))
			{
				if (newNode->getParent()->isLeftChild())
				{
					// If newNode is a left child, get its right 'uncle'
					Node* newNodesUncle =
							newNode->getParent()->getParent()->getRightChild();

					if (newNodesUncle != 0 && newNodesUncle->isRed())
					{
						// case 1 - change the colours
						newNode->getParent()->setBlack();
						newNodesUncle->setBlack();
						newNode->getParent()->getParent()->setRed();
						// Move newNode up the tree
						newNode = newNode->getParent()->getParent();
					}
					else
					{
						// newNodesUncle is a black node
						if (newNode->isRightChild())
						{
							// and newNode is to the right
							// case 2 - move newNode up and rotate
							newNode = newNode->getParent();
							rotateLeft(newNode);
						}
						// case 3
						newNode->getParent()->setBlack();
						newNode->getParent()->getParent()->setRed();
						rotateRight(newNode->getParent()->getParent());
					}
				}
				else
				{
					// If newNode is a right child, get its left 'uncle'
					Node* newNodesUncle =
							newNode->getParent()->getParent()->getLeftChild();
					if (newNodesUncle != 0 && newNodesUncle->isRed())
					{
						// case 1 - change the colours
						newNode->getParent()->setBlack();
						newNodesUncle->setBlack();
						newNode->getParent()->getParent()->setRed();
						// Move newNode up the tree
						newNode = newNode->getParent()->getParent();
					}
					else
					{
						// newNodesUncle is a black node
						if (newNode->isLeftChild())
						{
							// and newNode is to the left
							// case 2 - move newNode up and rotate
							newNode = newNode->getParent();
							rotateRight(newNode);
						}
						// case 3
						newNode->getParent()->setBlack();
						newNode->getParent()->getParent()->setRed();
						rotateLeft(newNode->getParent()->getParent());
					}

				}
			}
			// Color the root black
			Root->setBlack();
		}

		//! Removes a node from the tree and returns it.
		template<class KType, class VType>
		inline RBTree<KType, VType>* map<KType, VType>::delink(const KType& k)
		{
			Monitor->enter();

			Node* p = findInternal(k);

			IRR_ASSERT(p != 0);

			// Rotate p down to the left until it has no right child, will get there
			// sooner or later.
			while (p->getRightChild())
			{
				// "Pull up my right child and let it knock me down to the left"
				rotateLeft(p);
			}
			// p now has no right child but might have a left child
			Node* left = p->getLeftChild();

			// Let p's parent point to p's child instead of point to p
			if (p->isLeftChild())
			{
				p->getParent()->setLeftChild(left);
			}
			else if (p->isRightChild())
			{
				p->getParent()->setRightChild(left);
			}
			else
			{
				// p has no parent => p is the root.
				// Let the left child be the new root.
				setRoot(left);
			}

			// p is now gone from the tree in the sense that
			// no one is pointing at it, so return it.

			--Size;

			Monitor->exit();

			return p;
		}

		//! Removes a node from the tree and deletes it.
		template<class KType, class VType>
		inline void map<KType, VType>::remove(const KType& k)
		{
			Monitor->enter();

			Node* p = findInternal(k);

			IRR_ASSERT(p != 0);

			// Rotate p down to the left until it has no right child, will get there
			// sooner or later.
			while (p->getRightChild())
			{
				// "Pull up my right child and let it knock me down to the left"
				rotateLeft(p);
			}
			// p now has no right child but might have a left child
			Node* left = p->getLeftChild();

			// Let p's parent point to p's child instead of point to p
			if (p->isLeftChild())
			{
				p->getParent()->setLeftChild(left);
			}
			else if (p->isRightChild())
			{
				p->getParent()->setRightChild(left);
			}
			else
			{
				// p has no parent => p is the root.
				// Let the left child be the new root.
				setRoot(left);
			}

			// p is now gone from the tree in the sense that
			// no one is pointing at it. Let's get rid of it.
			delete p;

			--Size;

			Monitor->exit();
		}

		//! Clear the entire tree
		template<class KType, class VType>
		inline void map<KType, VType>::clear()
		{
			Monitor->enter();

			ParentLastIterator i(Root);

			while (!i.atEnd())
			{
				Node* p = i.getNode();
				i++; // Increment it before it is deleted
					 // else iterator will get quite confused.
				delete p;
			}

			Root = 0;
			Size = 0;

			Monitor->exit();
		}

		//! Is the tree empty?
		//! \return Returns true if empty, false if not
		template<class KType, class VType>
		inline bool map<KType, VType>::empty() const
		{
			Monitor->enter();
			bool result = Root == 0;
			Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! Search for a node with the specified key.
		//! \param keyToFind: The key to find
		//! \return Returns 0 if node couldn't be found.
		template<class KType, class VType>
		inline RBTree<KType, VType>* map<KType, VType>::find(
				const KType& keyToFind) const
		{
			Monitor->enter();
			Node* result = findInternal(keyToFind);
			Monitor->exit();

			return result;
		}

		//! Search for a node with the specified key.
		//! \param keyToFind: The key to find
		//! \return Returns 0 if node couldn't be found.
		template<class KType, class VType>
		inline RBTree<KType, VType>* map<KType, VType>::findInternal(
				const KType& keyToFind) const
		{
			Node* result = Root;

			while (result)
			{
				KType key(result->getKey());

				if (keyToFind == key)
				{
					break;
				}
				else if (keyToFind < key)
				{
					result = result->getLeftChild();
				}
				else //keyToFind > key
				{
					result = result->getRightChild();
				}
			}

			return result;
		}

		//! Gets the root element.
		//! \return Returns a pointer to the root node, or
		//! 0 if the tree is empty.
		template<class KType, class VType>
		inline RBTree<KType, VType>* map<KType, VType>::getRoot() const
		{
			Monitor->enter();
			Node* result = Root;
			Monitor->exit();

			return result;
		}

		//! Returns the number of nodes in the tree.
		template<class KType, class VType>
		inline u32 map<KType, VType>::size() const
		{
			Monitor->enter();
			u32 result = Size;
			Monitor->exit();

			return result;
		}

		//! Swap the content of this map container with the content of another map
		/** Afterwards this object will contain the content of the other object and the other
		 object will contain the content of this object. Iterators will afterwards be valid for
		 the swapped object.
		 \param other Swap content with this object	*/
		template<class KType, class VType>
		inline void map<KType, VType>::swap(map<KType, VType>& other)
		{
			// handle self swap
			if (this == &other)
				return;

			other.Monitor->enter();
			Monitor->enter();

			SharedMath::getInstance().swap(Monitor, other.Monitor);
			SharedMath::getInstance().swap(Root, other.Root);
			SharedMath::getInstance().swap(Size, other.Size);

			Monitor->exit();
			other.Monitor->exit();
		}

		//------------------------------
		// Public Iterators
		//------------------------------

		//! Returns an iterator
		template<class KType, class VType>
		inline CMapIterator<KType, VType> map<KType, VType>::getIterator()
		{
			Monitor->enter();
			Iterator result(Root);
			Monitor->exit();

			return result;
		}

		//! Returns a ParentFirstIterator.
		//! Traverses the tree from top to bottom. Typical usage is
		//! when storing the tree structure, because when reading it
		//! later (and inserting elements) the tree structure will
		//! be the same.
		template<class KType, class VType>
		inline CParentFirstIterator<KType, VType> map<KType, VType>::getParentFirstIterator()
		{
			Monitor->enter();
			ParentFirstIterator result(Root);
			Monitor->exit();

			return result;
		}

		//! Returns a ParentLastIterator to traverse the tree from
		//! bottom to top.
		//! Typical usage is when deleting all elements in the tree
		//! because you must delete the children before you delete
		//! their parent.
		template<class KType, class VType>
		inline CParentLastIterator<KType, VType> map<KType, VType>::getParentLastIterator()
		{
			Monitor->enter();
			ParentLastIterator it(Root);
			Monitor->exit();

			return it;
		}

		//------------------------------
		// Public Operators
		//------------------------------

		//! operator [] for access to elements
		template<class KType, class VType>
		inline CAccessClass<KType, VType> map<KType, VType>::operator[](
				const KType& k)
		{
			Monitor->enter();
			AccessClass result(*this, k);
			Monitor->exit();

			return result;
		}

		//------------------------------
		// Protected funcs
		//------------------------------

		//! Set node as new root.
		template<class KType, class VType>
		inline void map<KType, VType>::setRoot(Node* newRoot)
		{
			Root = newRoot;
			if (Root != 0)
			{
				Root->setParent(0);
				Root->setBlack();
			}
		}

		//! Insert a node into the tree without using any fancy balancing logic.
		template<class KType, class VType>
		inline void map<KType, VType>::insert(Node* newNode)
		{
			if (Root == 0)
			{
				setRoot(newNode);
				Size = 1;
			}
			else
			{
				Node* pNode = Root;
				KType keyNew = newNode->getKey();
				while (pNode)
				{
					KType key(pNode->getKey());

					IRR_ASSERT(keyNew != key);

					if (keyNew < key)
					{
						if (pNode->getLeftChild() == 0)
						{
							pNode->setLeftChild(newNode);
							pNode = 0;
						}
						else
							pNode = pNode->getLeftChild();
					}
					else // keyNew > key
					{
						if (pNode->getRightChild() == 0)
						{
							pNode->setRightChild(newNode);
							pNode = 0;
						}
						else
							pNode = pNode->getRightChild();
					}
				}

				++Size;
			}
		}

		//! Rotate left.
		//! Pull up node's right child and let it knock node down to the left
		template<class KType, class VType>
		inline void map<KType, VType>::rotateLeft(Node* p)
		{
			Node* right = p->getRightChild();

			p->setRightChild(right->getLeftChild());

			if (p->isLeftChild())
			{
				p->getParent()->setLeftChild(right);
			}
			else if (p->isRightChild())
			{
				p->getParent()->setRightChild(right);
			}
			else
			{
				setRoot(right);
			}

			right->setLeftChild(p);
		}

		//! Rotate right.
		//! Pull up node's left child and let it knock node down to the right
		template<class KType, class VType>
		inline void map<KType, VType>::rotateRight(Node* p)
		{
			Node* left = p->getLeftChild();

			p->setLeftChild(left->getRightChild());

			if (p->isLeftChild())
			{
				p->getParent()->setLeftChild(left);
			}
			else if (p->isRightChild())
			{
				p->getParent()->setRightChild(left);
			}
			else
			{
				setRoot(left);
			}

			left->setRightChild(p);
		}

	} // end namespace core
} // end namespace irrgame

//! map typedefs
typedef irrgame::core::map<s32, s32> DictIntInt;

#endif // __IRR_MAP_H_INCLUDED__
