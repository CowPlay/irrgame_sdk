/*
 * CVector3DAttribute.cpp
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#include "CVector3DAttribute.h"

namespace irrgame
{
	namespace io
	{

		//! Default constructor
		CVector3DAttribute::CVector3DAttribute(const c8* name,
				core::vector3df value) :
				CNumbersAttribute(name, value)
		{
		}

		E_ATTRIBUTE_TYPE CVector3DAttribute::getType() const
		{
			return EAT_VECTOR3D;
		}

		core::matrix4 CVector3DAttribute::getMatrix()
		{
			core::matrix4 ret;
			ret.makeIdentity();
			ret.setTranslation(
					core::vector3df(ValueF[0], ValueF[1], ValueF[2]));
			return ret;
		}

		const c8* CVector3DAttribute::getTypeString() const
		{
			return "vector3d";
		}

	}
}
