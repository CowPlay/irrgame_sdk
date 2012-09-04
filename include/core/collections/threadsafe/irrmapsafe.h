/*
 * irrmapsafe.h
 *
 *  Created on: Sep 4, 2012
 *      Author: gregorytkach
 */

#ifndef IRRMAPSAFE_H_
#define IRRMAPSAFE_H_

#include "core/collections/map/map.h"
#include "threads/irrgameMonitor.h"

namespace irrgame
{
	namespace core
	{
		template<class Key, class Value>
		class mapsafe: public map<Key, Value>
		{
			public:

				typedef RBTree<Key, Value> Node;
				typedef CMapIterator<Key, Value> Iterator;
				typedef CParentFirstIterator<Key, Value> ParentFirstIterator;
				typedef CParentLastIterator<Key, Value> ParentLastIterator;
				typedef CAccessClass<Key, Value> AccessClass;

			public:
				//! Default constructor.
				mapsafe();

				//! Destructor
				virtual ~mapsafe();

				//------------------------------
				// Public Commands
				//------------------------------

				//! Inserts a new node into the tree
				/** \param keyNew: the index for this value
				 \param v: the value to insert
				 \return True if successful, false if it fails (already exists) */
				virtual bool insert(const Key& keyNew, const Value& v);

				//! Replaces the value if the key already exists, otherwise inserts a new element.
				/** \param k The index for this value
				 \param v The new value of */
				virtual void set(const Key& k, const Value& v);

				//! Removes a node from the tree and returns it.
				/** The returned node must be deleted by the user
				 \param k the key to remove
				 \return A pointer to the node, or 0 if not found */
				virtual Node* delink(const Key& k);

				//! Removes a node from the tree and deletes it.
				/** \return True if the node was found and deleted */
				virtual bool remove(const Key& k);

				//! Clear the entire tree
				virtual void clear();

				//! Is the tree empty?
				//! \return Returns true if empty, false if not
				virtual bool empty() const;

				//! Search for a node with the specified key.
				//! \param keyToFind: The key to find
				//! \return Returns 0 if node couldn't be found.
				virtual Node* find(const Key& keyToFind) const;

				//! Gets the root element.
				//! \return Returns a pointer to the root node, or
				//! 0 if the tree is empty.
				virtual Node* getRoot() const;

				//! Returns the number of nodes in the tree.
				virtual u32 size() const;

				//! Swap the content of this map container with the content of another map
				/** Afterwards this object will contain the content of the other object and the other
				 object will contain the content of this object. Iterators will afterwards be valid for
				 the swapped object.
				 \param other Swap content with this object	*/
				virtual void swap(mapsafe<Key, Value>& other);

				//------------------------------
				// Public Iterators
				//------------------------------

				//! Returns an iterator
				virtual Iterator getIterator();
				//! Returns a ParentFirstIterator.
				//! Traverses the tree from top to bottom. Typical usage is
				//! when storing the tree structure, because when reading it
				//! later (and inserting elements) the tree structure will
				//! be the same.
				virtual ParentFirstIterator getParentFirstIterator();
				//! Returns a ParentLastIterator to traverse the tree from
				//! bottom to top.
				//! Typical usage is when deleting all elements in the tree
				//! because you must delete the children before you delete
				//! their parent.
				virtual ParentLastIterator getParentLastIterator();

				//------------------------------
				// Public Operators
				//------------------------------

				//! operator [] for access to elements
				/** for example myMap["key"] */
				virtual AccessClass operator[](const Key& k);
			protected:

				//------------------------------
				// Disabled methods
				//------------------------------
				// Copy constructor and assignment operator deliberately
				// defined but not implemented. The tree should never be
				// copied, pass along references to it instead.
				explicit mapsafe(const mapsafe& src);
				mapsafe& operator =(const mapsafe& src);

			protected:
				threads::irrgameMonitor* Monitor;
		};

		//------------------------------
		// map realization
		//------------------------------

		//! Default constructor.
		template<class Key, class Value>
		inline mapsafe<Key, Value>::mapsafe() :
				map<Key, Value>::map(), Monitor(0)
		{
		}

		//! Destructor
		template<class Key, class Value>
		inline mapsafe<Key, Value>::~mapsafe()
		{
			if (Monitor)
				Monitor->drop();
		}

		//! Inserts a new node into the tree
		/** \param keyNew: the index for this value
		 \param v: the value to insert
		 \return True if successful, false if it fails (already exists) */
		template<class Key, class Value>
		inline bool mapsafe<Key, Value>::insert(const Key& keyNew,
				const Value& v)
		{
			bool result = 0;

			Monitor->enter();
			result = map<Key, Value>::insert(keyNew, v);
			Monitor->exit();

			return result;
		}

		//! Replaces the value if the key already exists, otherwise inserts a new element.
		/** \param k The index for this value
		 \param v The new value of */
		template<class Key, class Value>
		inline void mapsafe<Key, Value>::set(const Key& k, const Value& v)
		{
			Monitor->enter();
			map<Key, Value>::set(k, v);
			Monitor->exit();
		}

		//! Removes a node from the tree and returns it.
		/** The returned node must be deleted by the user
		 \param k the key to remove
		 \return A pointer to the node, or 0 if not found */
		template<class Key, class Value>
		inline RBTree<Key, Value>* mapsafe<Key, Value>::delink(const Key& k)
		{
			Node* result = 0;

			Monitor->enter();
			result = map<Key, Value>::delink(k);
			Monitor->exit();

			return result;
		}

		//! Removes a node from the tree and deletes it.
		/** \return True if the node was found and deleted */
		template<class Key, class Value>
		inline bool mapsafe<Key, Value>::remove(const Key& k)
		{
			bool result = false;

			Monitor->enter();
			result = map<Key, Value>::remove(k);
			Monitor->exit();

			return result;
		}

		//! Clear the entire tree
		template<class Key, class Value>
		inline void mapsafe<Key, Value>::clear()
		{
			Monitor->enter();
			map<Key, Value>::clear();
			Monitor->exit();
		}

		//! Is the tree empty?
		//! \return Returns true if empty, false if not
		template<class Key, class Value>
		inline bool mapsafe<Key, Value>::empty() const
		{
			bool result = false;

			Monitor->enter();
			result = map<Key, Value>::empty();
			Monitor->exit();

			return result;
		}

		//! Search for a node with the specified key.
		//! \param keyToFind: The key to find
		//! \return Returns 0 if node couldn't be found.
		template<class Key, class Value>
		inline RBTree<Key, Value>* mapsafe<Key, Value>::find(
				const Key& keyToFind) const
		{
			Node* result = 0;

			Monitor->enter();
			result = map<Key, Value>::find(keyToFind);
			Monitor->exit();

			return result;
		}

		//! Gets the root element.
		//! \return Returns a pointer to the root node, or
		//! 0 if the tree is empty.
		template<class Key, class Value>
		inline RBTree<Key, Value>* mapsafe<Key, Value>::getRoot() const
		{
			Node* result = 0;

			Monitor->enter();
			result = map<Key, Value>::getRoot();
			Monitor->exit();

			return result;
		}

		//! Returns the number of nodes in the tree.
		template<class Key, class Value>
		inline u32 mapsafe<Key, Value>::size() const
		{
			u32 result = 0;

			Monitor->enter();
			result = map<Key, Value>::size();
			Monitor->exit();

			return result;
		}

		//! Swap the content of this map container with the content of another map
		/** Afterwards this object will contain the content of the other object and the other
		 object will contain the content of this object. Iterators will afterwards be valid for
		 the swapped object.
		 \param other Swap content with this object	*/
		template<class Key, class Value>
		inline void mapsafe<Key, Value>::swap(mapsafe<Key, Value>& other)
		{
			Monitor->enter();
			map<Key, Value>::swap(other);
			Monitor->exit();
		}

		//------------------------------
		// Public Iterators
		//------------------------------

		//! Returns an iterator
		template<class Key, class Value>
		inline CMapIterator<Key, Value> mapsafe<Key, Value>::getIterator()
		{
			Iterator result;

			Monitor->enter();
			result = map<Key, Value>::getIterator();
			Monitor->exit();

			return result;
		}

		//! Returns a ParentFirstIterator.
		//! Traverses the tree from top to bottom. Typical usage is
		//! when storing the tree structure, because when reading it
		//! later (and inserting elements) the tree structure will
		//! be the same.
		template<class Key, class Value>
		inline CParentFirstIterator<Key, Value> mapsafe<Key, Value>::getParentFirstIterator()
		{
			ParentFirstIterator result;

			Monitor->enter();
			result = map<Key, Value>::getParentFirstIterator();
			Monitor->exit();

			return result;
		}

		//! Returns a ParentLastIterator to traverse the tree from
		//! bottom to top.
		//! Typical usage is when deleting all elements in the tree
		//! because you must delete the children before you delete
		//! their parent.
		template<class Key, class Value>
		inline CParentLastIterator<Key, Value> mapsafe<Key, Value>::getParentLastIterator()
		{
			ParentLastIterator result;

			Monitor->enter();
			result = map<Key, Value>::getParentFirstIterator();
			Monitor->exit();

			return result;
		}

		//------------------------------
		// Public Operators
		//------------------------------

		//! operator [] for access to elements
		/** for example myMap["key"] */
		template<class Key, class Value>
		inline CAccessClass<Key, Value> mapsafe<Key, Value>::operator[](
				const Key& k)
		{

			AccessClass result;

			Monitor->enter();
			result = map<Key, Value>::operator[](k);
			Monitor->exit();

			return result;
		}
//
//				//------------------------------
//				// Protected funcs
//				//------------------------------
//
//				//! Set node as new root.
//				/** The node will be set to black, otherwise core dumps may arise
//				 (patch provided by rogerborg).
//				 \param newRoot Node which will be the new root
//				 */
//				template<class Key, class Value>
//				inline void map<Key, Value>::setRoot(Node* newRoot)
//				{
//					Root = newRoot;
//					if (Root != 0)
//					{
//						Root->setParent(0);
//						Root->setBlack();
//					}
//				}
//
//				//! Insert a node into the tree without using any fancy balancing logic.
//				/** \return false if that key already exist in the tree. */
//				template<class Key, class Value>
//				inline bool map<Key, Value>::insert(Node* newNode)
//				{
//					bool result = true; // Assume success
//
//					if (Root == 0)
//					{
//						setRoot(newNode);
//						Size = 1;
//					}
//					else
//					{
//						Node* pNode = Root;
//						Key keyNew = newNode->getKey();
//						while (pNode)
//						{
//							Key key(pNode->getKey());
//
//							if (keyNew == key)
//							{
//								result = false;
//								pNode = 0;
//							}
//							else if (keyNew < key)
//							{
//								if (pNode->getLeftChild() == 0)
//								{
//									pNode->setLeftChild(newNode);
//									pNode = 0;
//								}
//								else
//									pNode = pNode->getLeftChild();
//							}
//							else // keyNew > key
//							{
//								if (pNode->getRightChild() == 0)
//								{
//									pNode->setRightChild(newNode);
//									pNode = 0;
//								}
//								else
//								{
//									pNode = pNode->getRightChild();
//								}
//							}
//						}
//
//						if (result)
//							++Size;
//					}
//
//					_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
//					return result;
//				}
//
//				//! Rotate left.
//				//! Pull up node's right child and let it knock node down to the left
//				template<class Key, class Value>
//				inline void map<Key, Value>::rotateLeft(Node* p)
//				{
//					Node* right = p->getRightChild();
//
//					p->setRightChild(right->getLeftChild());
//
//					if (p->isLeftChild())
//						p->getParent()->setLeftChild(right);
//					else if (p->isRightChild())
//						p->getParent()->setRightChild(right);
//					else
//						setRoot(right);
//
//					right->setLeftChild(p);
//				}
//
//				//! Rotate right.
//				//! Pull up node's left child and let it knock node down to the right
//				template<class Key, class Value>
//				inline void map<Key, Value>::rotateRight(Node* p)
//				{
//					Node* left = p->getLeftChild();
//
//					p->setLeftChild(left->getRightChild());
//
//					if (p->isLeftChild())
//						p->getParent()->setLeftChild(left);
//					else if (p->isRightChild())
//						p->getParent()->setRightChild(left);
//					else
//						setRoot(left);
//
//					left->setRightChild(p);
//				}
	}
// end namespace core
}// end namespace irrgame

#endif /* IRRMAPSAFE_H_ */
