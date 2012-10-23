/*
 * ISceneManager.h
 *
 *  Created on: Sep 12, 2012
 *      Author: gregorytkach
 */

#ifndef ISCENEMANAGER_H_
#define ISCENEMANAGER_H_

#include "core/engine/IReferenceCounted.h"

namespace irrgame
{
	namespace scene
	{

		class ISceneNode;

		//! Scene manager interface.
		/*
		 */
		class ISceneManager : public IReferenceCounted
		{
			public:

				//! Destructor
				virtual ~ISceneManager()
				{
				}

				//! Returns root node on the scene
				virtual ISceneNode* getRoot() = 0;
		};

		//! SceneManager creator
		ISceneManager* createSceneManager();

	}  // namespace scene

}  // namespace irrgame

#endif /* ISCENEMANAGER_H_ */
