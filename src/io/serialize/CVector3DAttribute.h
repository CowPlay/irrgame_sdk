/*
 * CVector3DAttribute.h
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#ifndef CVECTOR3DATTRIBUTE_H_
#define CVECTOR3DATTRIBUTE_H_
#include "io/serialize/CNumbersAttribute.h"
#include "io/serialize/EAttributeTypes.h"

namespace irrgame
{
	namespace io
	{
		// Attribute implemented for 3d vectors
		class CVector3DAttribute: public CNumbersAttribute
		{
			public:

				//! Default constructor
				CVector3DAttribute(const c8* name, core::vector3df value);

				virtual E_ATTRIBUTE_TYPE getType() const;

				virtual core::matrix4 getMatrix();

				virtual const c8* getTypeString() const;

		};

	}
}
#endif /* CVECTOR3DATTRIBUTE_H_ */
