/*
 * CStringArrayAttribute.cpp
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#include "CStringArrayAttribute.h"
namespace irrgame
{
	namespace io
	{
		//! Default constructor
		CStringArrayAttribute::CStringArrayAttribute(const c8* name,
				const arraystr& value)
		{
			Name = name;
			setArray(value);
		}

		arraystr CStringArrayAttribute::getArray()
		{
			return Value;
		}

		void CStringArrayAttribute::setArray(const arraystr& value)
		{
			Value = value;
		}

		EAttributeType CStringArrayAttribute::getType() const
		{
			return EAT_STRINGARRAY;
		}

		const c8* CStringArrayAttribute::getTypeString() const
		{
			return "stringarray";
		}

	}
}

