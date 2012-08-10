/*
 * CVector2DAttribute.cpp
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#include "CVector2DAttribute.h"

namespace irrgame
{
	namespace io
	{

		//! Default constructor
		CVector2DAttribute::CVector2DAttribute(const c8* name,
				core::vector2df value) :
				CNumbersAttribute(name, value)
		{
		}

		E_ATTRIBUTE_TYPE CVector2DAttribute::getType() const
		{
			return EAT_VECTOR2D;
		}

		const c8* CVector2DAttribute::getTypeString() const
		{
			return "vector2d";
		}

	}
}