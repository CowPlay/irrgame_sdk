/*
 * CPlaneAttribute.cpp
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#include "CPlaneAttribute.h"
namespace irrgame
{
	namespace io
	{
		//! Default constructor
		CPlaneAttribute::CPlaneAttribute(const c8* name, core::plane3df value) :
				CNumbersAttribute(name, value)
		{
		}

		E_ATTRIBUTE_TYPE CPlaneAttribute::getType() const
		{
			return EAT_PLANE;
		}

		const c8* CPlaneAttribute::getTypeString() const
		{
			return "plane";
		}

	}
}

