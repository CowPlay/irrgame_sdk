/*
 * CIntAttribute.cpp
 *
 *  Created on: Aug 8, 2012
 *      Author: gregorytkach
 */

#include "CIntAttribute.h"
#include "core/collections/stringc.h"

namespace irrgame
{
	namespace io
	{

		//! Default constructor
		CIntAttribute::CIntAttribute(const c8* name, s32 value)
		{
			Name = name;
			setInt(value);
		}

		s32 CIntAttribute::getInt()
		{
			return Value;
		}

		f32 CIntAttribute::getFloat()
		{
			return (f32) Value;
		}

		bool CIntAttribute::getBool()
		{
			return (Value != 0);
		}

		core::stringc CIntAttribute::getString()
		{
			return core::stringc(Value);
		}

		void CIntAttribute::setInt(s32 intValue)
		{
			Value = intValue;
		}

		void CIntAttribute::setFloat(f32 floatValue)
		{
			Value = (s32) floatValue;
		}

		void CIntAttribute::setString(const c8* text)
		{
			Value = atoi(text);
		}

		EAttributeType CIntAttribute::getType() const
		{
			return EAT_INT;
		}

		const c8* CIntAttribute::getTypeString() const
		{
			return "int";
		}

	}
}

