/*
 * IDimensionalObject.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: gregorytkach
 */

#include "core/engine/IDimensionalObject.h"

namespace irrgame
{
	namespace core
	{
		//! Default destructor
		template<class T>
		IDimensionalObject<T>::~IDimensionalObject()
		{

		}

		//! Updates the absolute position based on the relative and the parents position
		template<class T>
		void IDimensionalObject<T>::updateAbsoluteTransformation()
		{
			if (this->Parent)
				AbsoluteTransformation = this->Parent->AbsoluteTransformation
						* RelativeTransformation;
			else
				AbsoluteTransformation = RelativeTransformation;
		}

		//! Returns object absolute position
		template<class T>
		vector3df IDimensionalObject<T>::getAbsolutePosition()
		{
			return AbsoluteTransformation.getTranslation();
		}

		//! Returns object absolute scale
		template<class T>
		vector3df IDimensionalObject<T>::getAbsoluteScale()
		{
			return AbsoluteTransformation.getScale();
		}

		//! Returns object absolute rotation
		template<class T>
		vector3df IDimensionalObject<T>::getAbsoluteRotation()
		{
			return AbsoluteTransformation.getRotationDegrees();
		}

		//! Returns relative position to its parent.
		template<class T>
		vector3df IDimensionalObject<T>::getRelativePosition()
		{
			return RelativeTransformation.getTranslation();
		}

		//! Returns relative scale to its parent.
		template<class T>
		vector3df IDimensionalObject<T>::getRelativeScale()
		{
			return RelativeTransformation.getScale();
		}

		//! Returns relative rotation to its parent.
		template<class T>
		vector3df IDimensionalObject<T>::getRelativeRotation()
		{
			return RelativeTransformation.getRotationDegrees();
		}

		//! Sets relative position to its parent.
		template<class T>
		void IDimensionalObject<T>::setRelativePosition(vector3df value)
		{
			RelativeTransformation.setTranslation(value);
		}

		//! Sets relative scale to its parent.
		template<class T>
		void IDimensionalObject<T>::setRelativeScale(vector3df value)
		{
			RelativeTransformation.setScale(value);
		}

		//! Sets relative rotation to its parent.
		template<class T>
		void IDimensionalObject<T>::setRelativeRotation(vector3df value)
		{
			RelativeTransformation.setRotationDegrees(value);
		}

	}  // namespace core

}  // namespace irrgame

