/*
 * CTriangleAttribute.cpp
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#include "CTriangleAttribute.h"

namespace irrgame
{
	namespace io
	{

		CTriangleAttribute::CTriangleAttribute(const c8* name,
				core::triangle3df value) :
				CNumbersAttribute(name, value)
		{
		}

		E_ATTRIBUTE_TYPE CTriangleAttribute::getType() const
		{
			return EAT_TRIANGLE3D;
		}

		core::plane3df CTriangleAttribute::getPlane()
		{
			return getTriangle().getPlane();
		}

		const c8* CTriangleAttribute::getTypeString() const
		{
			return "triangle";
		}

	}
}
