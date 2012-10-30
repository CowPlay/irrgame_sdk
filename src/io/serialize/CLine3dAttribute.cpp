/*
 * CLine3dAttribute.cpp
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */
#include "CLine3dAttribute.h"

namespace irrgame
{
	namespace io
	{
		//! Default constructor
		CLine3dAttribute::CLine3dAttribute(const c8* name, line3df value) :
				CNumbersAttribute(name, value)
		{
		}

		EAttributeType CLine3dAttribute::getType() const
		{
			return EAT_LINE3D;
		}

		const c8* CLine3dAttribute::getTypeString() const
		{
			return "line3d";
		}

	}
}

