/*
 * CColorfAttribute.cpp
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */
#include "CColorfAttribute.h"
namespace irrgame
{
	namespace io
	{

		//! Default constructor
		CColorfAttribute::CColorfAttribute(const c8* name, video::SColorf value) :
				CNumbersAttribute(name, value)
		{
		}

		s32 CColorfAttribute::getInt()
		{
			return getColor().color;
		}

		f32 CColorfAttribute::getFloat()
		{
			return (f32) getColor().color;
		}

		void CColorfAttribute::setInt(s32 intValue)
		{
			video::SColorf c = video::SColor(intValue);
			ValueF[0] = c.Red;
			ValueF[1] = c.Green;
			ValueF[2] = c.Blue;
			ValueF[3] = c.Alpha;
		}

		void CColorfAttribute::setFloat(f32 floatValue)
		{
			setInt((s32) floatValue);
		}

		EAttributeType CColorfAttribute::getType() const
		{
			return EAT_COLORF;
		}

		const c8* CColorfAttribute::getTypeString() const
		{
			return "colorf";
		}

	}
}

