/*
 * CMatrixAttribute.cpp
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#include "CMatrixAttribute.h"

namespace irrgame
{
	namespace io
	{

		CMatrixAttribute::CMatrixAttribute(const c8* name, core::matrix4 value) :
				CNumbersAttribute(name, value)
		{
		}

		E_ATTRIBUTE_TYPE CMatrixAttribute::getType() const
		{
			return EAT_MATRIX;
		}

		core::quaternion CMatrixAttribute::getQuaternion()
		{
			return core::quaternion(getMatrix());
		}

		const c8* CMatrixAttribute::getTypeString() const
		{
			return "matrix";
		}

	}
}

