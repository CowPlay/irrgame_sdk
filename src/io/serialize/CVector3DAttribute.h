/*
 * CVector3DAttribute.h
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#ifndef CVECTOR3DATTRIBUTE_H_
#define CVECTOR3DATTRIBUTE_H_

#include "io/serialize/CNumbersAttribute.h"

namespace irrgame
{
	namespace io
	{
		// Attribute implemented for 3d vectors
		class CVector3DAttribute: public CNumbersAttribute
		{
			public:

				//! Default constructor
				CVector3DAttribute(const c8* name, vector3df value);

				virtual EAttributeType getType() const;

				virtual matrix4f getMatrix();

				virtual const c8* getTypeString() const;

		};

	}
}
#endif /* CVECTOR3DATTRIBUTE_H_ */
