/*
 * CEnumAttribute.cpp
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#include "CEnumAttribute.h"

namespace irrgame
{
	namespace io
	{
		//! Default constructor
		CEnumAttribute::CEnumAttribute(const c8* name, const c8* value,
				const c8* const * literals)
		{
			Name = name;
			setEnum(value, literals);
		}

		void CEnumAttribute::setEnum(const c8* enumValue,
				const c8* const * enumerationLiterals)
		{
			int literalCount = 0;

			if (enumerationLiterals)
			{
				s32 i;
				for (i = 0; enumerationLiterals[i]; ++i)
					++literalCount;

				EnumLiterals.reallocate(literalCount);
				for (i = 0; enumerationLiterals[i]; ++i)
					EnumLiterals.pushBack(enumerationLiterals[i]);
			}

			setString(enumValue);
		}

		s32 CEnumAttribute::getInt()
		{
			for (s32 i = 0; EnumLiterals.size(); ++i)
				if (Value.equalsIgnoreCase(EnumLiterals[i]))
				{
					return i;
				}

			return -1;
		}

		f32 CEnumAttribute::getFloat()
		{
			return (f32) getInt();
		}

		bool CEnumAttribute::getBool()
		{
			return (getInt() != 0); // does not make a lot of sense, I know
		}

		core::stringc CEnumAttribute::getString()
		{
			return Value;
		}

		void CEnumAttribute::setInt(s32 intValue)
		{
			if (intValue >= 0 && intValue < (s32) EnumLiterals.size())
				Value = EnumLiterals[intValue];
			else
				Value = "";
		}

		void CEnumAttribute::setFloat(f32 floatValue)
		{
			setInt((s32) floatValue);
		}

		void CEnumAttribute::setString(const c8* text)
		{
			Value = text;
		}

		const c8* CEnumAttribute::getEnum()
		{
			return Value.cStr();
		}

		EAttributeType CEnumAttribute::getType() const
		{
			return EAT_ENUM;
		}

		const c8* CEnumAttribute::getTypeString() const
		{
			return "enum";
		}

	}
}
