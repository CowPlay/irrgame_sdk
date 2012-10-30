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
		CVector2DAttribute::CVector2DAttribute(const c8* name, vector2df value) :
				CNumbersAttribute(name, value)
		{
		}

		EAttributeType CVector2DAttribute::getType() const
		{
			return EAT_VECTOR2D;
		}

		const c8* CVector2DAttribute::getTypeString() const
		{
			return "vector2d";
		}

	}
}
