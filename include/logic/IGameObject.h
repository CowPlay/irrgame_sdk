/*
 * IGameObject.h
 *
 *  Created on: Jul 23, 2012
 *      Author: gregorytkach
 */

#ifndef IGAMEOBJECT_H_
#define IGAMEOBJECT_H_

#include "core/irrgamecollections.h"
#include "events/IEventReceiver.h"
#include "core/irrgameshapes.h"
#include "core/engine/IDimensionalObject.h"

namespace irrgame
{
	namespace scene
	{
		class ISceneNode;
	}

	class IGameObjectAnimator;

	namespace logic
	{
		class IGameObject: public events::IEventReceiver,
				public core::IDimensionalObject<IGameObject>
		{
			public:

			protected:

		};

	}  // namespace logic

}  // namespace irrgame

#endif /* IGAMEOBJECT_H_ */
