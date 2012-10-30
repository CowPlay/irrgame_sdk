/*
 * CDimension2dAttribute.cpp
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */
#include "CDimension2dAttribute.h"
namespace irrgame
{
	namespace io
	{

		//! Default constructor
		CDimension2dAttribute::CDimension2dAttribute(const c8* name,
				dimension2df value) :
				CNumbersAttribute(name, value)
		{
		}

		EAttributeType CDimension2dAttribute::getType() const
		{
			return EAT_DIMENSION2D;
		}

		const c8* CDimension2dAttribute::getTypeString() const
		{
			return "dimension2d";
		}

	}
}

