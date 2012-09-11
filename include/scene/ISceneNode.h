/*
 * ISceneNode.h
 *
 *  Created on: Sep 11, 2012
 *      Author: gregorytkach
 */

#ifndef ISCENENODE_H_
#define ISCENENODE_H_

namespace irrgame
{
	namespace scene
	{
		//! Scene node interface.
		/** A scene node is a node in the hierarchical scene graph. Every scene
		 node may have children, which are also scene nodes. Children move
		 relative to their parent's position. If the parent of a node is not
		 visible, its children won't be visible either. In this way, it is for
		 example easily possible to attach a light to a moving car, or to place
		 a walking character on a moving platform on a moving ship.
		 */
		class ISceneNode
		{
			public:

			protected:

		};

	}

}

#endif /* ISCENENODE_H_ */
