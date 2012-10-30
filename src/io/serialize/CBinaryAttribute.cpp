/*
 * CBinaryAttribute.cpp
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */
#include "CBinaryAttribute.h"

namespace irrgame
{
	namespace io
	{
		//! Default constructor
		CBinaryAttribute::CBinaryAttribute(const c8* name, void* binaryData,
				s32 lenghtInBytes) :
				CStringAttribute(name, binaryData, lenghtInBytes)
		{

		}

		EAttributeType CBinaryAttribute::getType() const
		{
			return EAT_BINARY;
		}

		const c8* CBinaryAttribute::getTypeString() const
		{
			return "binary";
		}

	}

}

