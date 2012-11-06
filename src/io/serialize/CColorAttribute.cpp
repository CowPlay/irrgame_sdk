/*
 * CColorAttribute.cpp
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#include "CColorAttribute.h"
namespace irrgame
{
	namespace io
	{
		//! Default constructor for colorf
		CColorAttribute::CColorAttribute(const c8* name,
				const video::SColorf& value) :
				CNumbersAttribute(name, value)
		{
		}

		//! Default constructor for color
		CColorAttribute::CColorAttribute(const c8* name,
				const video::SColor& value) :
				CNumbersAttribute(name, value)
		{
		}

		s32 CColorAttribute::getInt()
		{
			return getColor().color;
		}

		f32 CColorAttribute::getFloat()
		{
			return (f32) getColor().color;
		}

		void CColorAttribute::setInt(s32 intValue)
		{
			video::SColorf c = video::SColor(intValue);
			ValueF[0] = c.Red;
			ValueF[1] = c.Green;
			ValueF[2] = c.Blue;
			ValueF[3] = c.Alpha;
		}

		void CColorAttribute::setFloat(f32 floatValue)
		{
			setInt((s32) floatValue);
		}

		core::stringc CColorAttribute::getString()
		{
			c8 tmp[10];
			const video::SColor c = getColor();
			sprintf(tmp, "%02x%02x%02x%02x", c.getAlpha(), c.getRed(),
					c.getGreen(), c.getBlue());
			return core::stringc(tmp);
		}

		void CColorAttribute::setString(const c8* text)
		{
			u32 c;
			if (sscanf(text, "%08x", &c) != 1)
			{
				CNumbersAttribute::setString(text);
			}
			else
				setColor(c);
		}

		EAttributeType CColorAttribute::getType() const
		{
			return EAT_COLOR;
		}

		const c8* CColorAttribute::getTypeString() const
		{
			return "color";
		}
	}
}

