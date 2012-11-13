/*
 * ISceneNode.cpp
 *
 *  Created on: Oct 11, 2012
 *      Author: gregorytkach
 */

#include "scene/node/ISceneNode.h"

namespace irrgame
{
	namespace scene
	{
		//! Default constructor
		ISceneNode::ISceneNode(ISceneNode* parent) :
				core::ILeafNode<ISceneNode>(parent)
		{
		}

		//! Destructor
		ISceneNode::~ISceneNode()
		{
		}

	}  // namespace scene

}  // namespace irrgame

