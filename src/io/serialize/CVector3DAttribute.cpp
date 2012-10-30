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
		CVector3DAttribute::CVector3DAttribute(const c8* name, vector3df value) :
				CNumbersAttribute(name, value)
		{
		}

		EAttributeType CVector3DAttribute::getType() const
		{
			return EAT_VECTOR3D;
		}

		matrix4f CVector3DAttribute::getMatrix()
		{
			matrix4f ret;
			ret.makeIdentity();
			ret.setTranslation(vector3df(ValueF[0], ValueF[1], ValueF[2]));
			return ret;
		}

		const c8* CVector3DAttribute::getTypeString() const
		{
			return "vector3d";
		}

	}
}
