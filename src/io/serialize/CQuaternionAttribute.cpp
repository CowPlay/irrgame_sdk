/*
 * CQuaternionAttribute.cpp
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#include "CQuaternionAttribute.h"

namespace irrgame
{
	namespace io
	{

		CQuaternionAttribute::CQuaternionAttribute(const c8* name,
				core::quaternion value) :
				CNumbersAttribute(name, value)
		{
		}

		EAttributeType CQuaternionAttribute::getType() const
		{
			return EAT_QUATERNION;
		}

		matrix4f CQuaternionAttribute::getMatrix()
		{
			return getQuaternion().getMatrix();
		}

		const c8* CQuaternionAttribute::getTypeString() const
		{
			return "quaternion";
		}

	}
}

