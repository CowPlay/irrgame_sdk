/*
 * CBoolAttribute.cpp
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#include "CBoolAttribute.h"

namespace irrgame
{
	namespace io
	{
		//! Default constructor
		CBoolAttribute::CBoolAttribute(const c8* name, bool value)
		{
			Name = name;
			setBool(value);
		}

		s32 CBoolAttribute::getInt()
		{
			return BoolValue ? 1 : 0;
		}

		f32 CBoolAttribute::getFloat()
		{
			return BoolValue ? 1.0f : 0.0f;
		}

		bool CBoolAttribute::getBool()
		{
			return BoolValue;
		}

		core::stringc CBoolAttribute::getString()
		{
			return core::stringc(BoolValue ? "true" : "false");
		}

		void CBoolAttribute::setInt(s32 intValue)
		{
			BoolValue = (intValue != 0);
		}

		void CBoolAttribute::setFloat(f32 floatValue)
		{
			BoolValue = (floatValue != 0);
		}

		void CBoolAttribute::setBool(bool boolValue)
		{
			BoolValue = boolValue;
		}

		void CBoolAttribute::setString(const c8* string)
		{
			BoolValue = strcmp(string, "true") == 0;
		}

		EAttributeType CBoolAttribute::getType() const
		{
			return EAT_BOOL;
		}

		const c8* CBoolAttribute::getTypeString() const
		{
			return "bool";
		}

	}
}

