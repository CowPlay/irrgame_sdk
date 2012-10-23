/*
 * CSceneManager.cpp
 *
 *  Created on: Oct 11, 2012
 *      Author: gregorytkach
 */

#include "CSceneManager.h"

namespace irrgame
{
	namespace scene
	{

		//! Default constructor
		CSceneManager::CSceneManager() :
				ISceneNode(0)
		{
			// TODO Auto-generated constructor stub

		}

		//! Destructor
		CSceneManager::~CSceneManager()
		{
			// TODO Auto-generated destructor stub
		}

		//! Returns root node on the scene
		ISceneNode* CSceneManager::getRoot()
		{
			return this;
		}

		/*
		 * ISceneNode stubs
		 */

		//! Renders the node.
		void CSceneManager::render()
		{
		}

		//! Update absolute transformation by data from game object(logic).
		void CSceneManager::updateAbsoluteTransformation()
		{
		}

		//! SceneManager creator
		ISceneManager* createSceneManager()
		{
			return new CSceneManager;
		}

	} /* namespace scene */
} /* namespace irrgame */
