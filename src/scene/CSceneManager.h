/*
 * CSceneManager.h
 *
 *  Created on: Oct 11, 2012
 *      Author: gregorytkach
 */

#ifndef CSCENEMANAGER_H_
#define CSCENEMANAGER_H_

#include "scene/ISceneManager.h"
#include "scene/node/ISceneNode.h"

namespace irrgame
{
	namespace scene
	{

		class CSceneManager: public ISceneManager, ISceneNode
		{
			public:
				//! Default constructor
				CSceneManager();

				//! Destructor
				virtual ~CSceneManager();

				//! Returns root node on the scene
				virtual ISceneNode* getRoot();

				/*
				 * ISceneNode stubs
				 */

				//! Renders the node.
				virtual void render();

				//! Update absolute transformation by data from game object(logic).
				virtual void updateAbsoluteTransformation();
		};

	} /* namespace scene */
} /* namespace irrgame */
#endif /* CSCENEMANAGER_H_ */
