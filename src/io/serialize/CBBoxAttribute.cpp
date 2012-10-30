/*
 * CBBoxAttribute.cpp
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#include "CBBoxAttribute.h"
namespace irrgame
{
	namespace io
	{

		//! Default constructor
		CBBoxAttribute::CBBoxAttribute(const c8* name, aabbox3df value) :
				CNumbersAttribute(name, value)
		{
		}

		EAttributeType CBBoxAttribute::getType() const
		{
			return EAT_BBOX;
		}

		const c8* CBBoxAttribute::getTypeString() const
		{
			return "box3d";
		}

	}
}

