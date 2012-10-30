/*
 * IDimensionalObject.h
 *
 *  Created on: Sep 13, 2012
 *      Author: gregorytkach
 */

#ifndef IDIMENSIONALOBJECT_H_
#define IDIMENSIONALOBJECT_H_

#include "core/irrgameshapes.h"
#include "core/irrgamemath.h"
#include "core/irrgamecollections.h"

namespace irrgame
{
	namespace core
	{
		//! Base object of dimensional objects. T must be derived by IDimensionalObject.
		template<class T>
		class IDimensionalObject: public ILeafNode<T>
		{
			public:
				//! Default destructor
				virtual ~ IDimensionalObject();

				//! Updates the absolute position, scale and rotation based on the relative and the parents position
				/** Note: This does not recursively update the parents absolute positions, so if you have a deeper
				 hierarchy you might want to update the parents first.*/
				virtual void updateAbsoluteTransformation();

				//! Returns object absolute position
				virtual vector3df getAbsolutePosition();
				//! Returns object absolute scale
				virtual vector3df getAbsoluteScale();
				//! Returns object absolute rotation
				virtual vector3df getAbsoluteRotation();

				//! Returns relative position to its parent.
				virtual vector3df getRelativePosition();
				//! Returns relative scale to its parent.
				virtual vector3df getRelativeScale();
				//! Returns relative rotation to its parent.
				virtual vector3df getRelativeRotation();

				//! Sets relative position to its parent.
				virtual void setRelativePosition(vector3df value);
				//! Sets relative scale to its parent.
				virtual void setRelativeScale(vector3df value);
				//! Sets relative rotation to its parent.
				virtual void setRelativeRotation(vector3df value);

			protected:

				//! Absolute position, rotation of the game object.
				matrix4f AbsoluteTransformation;

				//! Relative position, rotation of the game object.
				matrix4f RelativeTransformation;
		};
	}  // namespace core

}  // namespace irrgame

#endif /* IDIMENSIONALOBJECT_H_ */
