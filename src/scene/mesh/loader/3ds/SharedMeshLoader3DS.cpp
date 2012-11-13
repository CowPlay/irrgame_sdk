/*
 * SharedMeshLoader3DS.cpp
 *
 *  Created on: Nov 12, 2012
 *      Author: gregorytkach
 */

#include "SharedMeshLoader3DS.h"

namespace irrgame
{
	namespace scene
	{
		//! Singleton realization
		SharedMeshLoader3DS& SharedMeshLoader3DS::getInstance()
		{
			static SharedMeshLoader3DS instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		SharedMeshLoader3DS::SharedMeshLoader3DS()
		{
		}

		//! Destructor. Should use only one time.
		SharedMeshLoader3DS::~SharedMeshLoader3DS()
		{
		}

	/*
	 * Methods
	 */

	} /* namespace scene */
} /* namespace irrgame */
