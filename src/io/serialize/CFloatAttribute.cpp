/*
 * CFloatAttribute.cpp
 *
 *  Created on: Aug 8, 2012
 *      Author: gregorytkach
 */
#include "CFloatAttribute.h"
#include "core/fast_atof.h"
namespace irrgame
{
	namespace io
	{

		//! Default constructor
		CFloatAttribute::CFloatAttribute(const c8* name, f32 value)
		{
			Name = name;
			setFloat(value);
		}

		s32 CFloatAttribute::getInt()
		{
			return (s32) Value;
		}

		f32 CFloatAttribute::getFloat()
		{
			return Value;
		}

		bool CFloatAttribute::getBool()
		{
			return (Value != 0);
		}

		core::stringc CFloatAttribute::getString()
		{
			return core::stringc(Value);
		}

		void CFloatAttribute::setInt(s32 intValue)
		{
			Value = (f32) intValue;
		}

		void CFloatAttribute::setFloat(f32 floatValue)
		{
			Value = floatValue;
		}

		void CFloatAttribute::setString(const c8* text)
		{
			Value = core::fast_atof(text);
		}

		E_ATTRIBUTE_TYPE CFloatAttribute::getType() const
		{
			return EAT_FLOAT;
		}

		const c8* CFloatAttribute::getTypeString() const
		{
			return "float";
		}

	}
}

