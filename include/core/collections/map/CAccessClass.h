/*
 * CAccessClass.h
 *
 *  Created on: Nov 13, 2012
 *      Author: gregorytkach
 */

#ifndef CACCESSCLASS_H_
#define CACCESSCLASS_H_

#include "compileConfig.h"
#include "core/collections/map/RBTree.h"

namespace irrgame
{
	namespace core
	{

		template<class KType, class VType>
		class map;

		// AccessClass is a temporary class used with the [] operator.
		// It makes it possible to have different behavior in situations like:
		// myTree["Foo"] = 32;
		// If "Foo" already exists update its value else insert a new element.
		// int i = myTree["Foo"]
		// If "Foo" exists return its value.
		template<class KType, class VType>
		class CAccessClass
		{
				typedef RBTree<KType, VType> Node;

			public:

				//! Default constructor
				CAccessClass(map<KType, VType>& tree, const KType& key);

				// Assignment operator. Handles the myTree["Foo"] = 32; situation
				void operator=(const VType& value);

				// Value operator
				operator VType();

			private:

				//! Do not implement
				CAccessClass();

			private:

				map<KType, VType>& Tree;
				const KType& Key;
		};

		//! Default constructor
		template<class KType, class VType>
		inline CAccessClass<KType, VType>::CAccessClass(map<KType, VType>& tree,
				const KType& key) :
				Tree(tree), Key(key)
		{
		}

		// Assignment operator. Handles the myTree["Foo"] = 32; situation
		template<class KType, class VType>
		inline void CAccessClass<KType, VType>::operator=(const VType& value)
		{
			Node* node = Tree.find(Key);

			IRR_ASSERT(node);

			node->setValue(value);
		}

		// Value operator
		template<class KType, class VType>
		inline CAccessClass<KType, VType>::operator VType()
		{
			RBTree<KType, VType>* node = Tree.find(Key);

			// Not found
			// access violation
			IRR_ASSERT(node);

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return node->getValue();
		}

	}  // namespace core
}  // namespace irrgame

#endif /* CACCESSCLASS_H_ */
