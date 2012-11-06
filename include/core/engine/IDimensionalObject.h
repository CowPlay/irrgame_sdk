/*
 * IDimensionalObject.h
 *
 *  Created on: Sep 13, 2012
 *      Author: gregorytkach
 */

#ifndef IDIMENSIONALOBJECT_H_
#define IDIMENSIONALOBJECT_H_

#include "core/shapes/vector3d.h"
#include "core/math/matrix4.h"
#include "core/collections/ILeafNode.h"

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
				virtual ~IDimensionalObject();

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

		//! Default destructor
		template<class T>
		inline IDimensionalObject<T>::~IDimensionalObject()
		{

		}

		//! Updates the absolute position based on the relative and the parents position
		template<class T>
		inline void IDimensionalObject<T>::updateAbsoluteTransformation()
		{
			if (this->Parent)
			{
				AbsoluteTransformation = this->Parent->AbsoluteTransformation
						* RelativeTransformation;
			}
			else
			{
				AbsoluteTransformation = RelativeTransformation;
			}
		}

		//! Returns object absolute position
		template<class T>
		inline vector3df IDimensionalObject<T>::getAbsolutePosition()
		{
			return AbsoluteTransformation.getTranslation();
		}

		//! Returns object absolute scale
		template<class T>
		inline vector3df IDimensionalObject<T>::getAbsoluteScale()
		{
			return AbsoluteTransformation.getScale();
		}

		//! Returns object absolute rotation
		template<class T>
		inline vector3df IDimensionalObject<T>::getAbsoluteRotation()
		{
			return AbsoluteTransformation.getRotationDegrees();
		}

		//! Returns relative position to its parent.
		template<class T>
		inline vector3df IDimensionalObject<T>::getRelativePosition()
		{
			return RelativeTransformation.getTranslation();
		}

		//! Returns relative scale to its parent.
		template<class T>
		inline vector3df IDimensionalObject<T>::getRelativeScale()
		{
			return RelativeTransformation.getScale();
		}

		//! Returns relative rotation to its parent.
		template<class T>
		inline vector3df IDimensionalObject<T>::getRelativeRotation()
		{
			return RelativeTransformation.getRotationDegrees();
		}

		//! Sets relative position to its parent.
		template<class T>
		inline void IDimensionalObject<T>::setRelativePosition(vector3df value)
		{
			RelativeTransformation.setTranslation(value);
		}

		//! Sets relative scale to its parent.
		template<class T>
		inline void IDimensionalObject<T>::setRelativeScale(vector3df value)
		{
			RelativeTransformation.setScale(value);
		}

		//! Sets relative rotation to its parent.
		template<class T>
		inline void IDimensionalObject<T>::setRelativeRotation(vector3df value)
		{
			RelativeTransformation.setRotationDegrees(value);
		}

	}  // namespace core
}  // namespace irrgame

#endif /* IDIMENSIONALOBJECT_H_ */
