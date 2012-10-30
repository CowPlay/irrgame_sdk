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

		//! Default constructor
		CRectAttribute::CRectAttribute(const c8* name, recti value) :
				CNumbersAttribute(name, value)
		{
		}

		EAttributeType CRectAttribute::getType() const
		{
			return EAT_RECT;
		}

		const c8* CRectAttribute::getTypeString() const
		{
			return "rect";
		}

	}
}

