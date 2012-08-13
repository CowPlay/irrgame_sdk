/*
 * CLine2dAttribute.cpp
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#include "CLine2dAttribute.h"
namespace irrgame
{
	namespace io
	{

		//! Default constructor
		CLine2dAttribute::CLine2dAttribute(const char* name,
				core::line2df value) :
				CNumbersAttribute(name, value)
		{
		}

		E_ATTRIBUTE_TYPE CLine2dAttribute::getType() const
		{
			return EAT_LINE2D;
		}

		const c8* CLine2dAttribute::getTypeString() const
		{
			return "line2d";
		}

	}
}

