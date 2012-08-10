/*
 * CRectAttribute.cpp
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */
#include "CRectAttribute.h"
namespace irrgame
{
	namespace io
	{

		CRectAttribute::CRectAttribute(const c8* name, core::recti value) :
				CNumbersAttribute(name, value)
		{
		}

		E_ATTRIBUTE_TYPE CRectAttribute::getType() const
		{
			return EAT_RECT;
		}

		const c8* CRectAttribute::getTypeString() const
		{
			return "rect";
		}

	}
}
