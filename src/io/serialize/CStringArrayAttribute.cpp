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
				const core::array<core::stringc>& value)
		{
			Name = name;
			setArray(value);
		}

		core::array<core::stringc> CStringArrayAttribute::getArray()
		{
			return Value;
		}

		void CStringArrayAttribute::setArray(
				const core::array<core::stringc>& value)
		{
			Value = value;
		}

		E_ATTRIBUTE_TYPE CStringArrayAttribute::getType() const
		{
			return EAT_STRINGARRAY;
		}

		const c8* CStringArrayAttribute::getTypeString() const
		{
			return "stringarray";
		}

	}
}

