/*
 * CQuaternionAttribute.h
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#ifndef CQUATERNIONATTRIBUTE_H_
#define CQUATERNIONATTRIBUTE_H_

#include "CNumbersAttribute.h"

namespace irrgame
{
	namespace io
	{
		// Attribute implemented for quaternions
		class CQuaternionAttribute: public CNumbersAttribute
		{
			public:

				CQuaternionAttribute(const c8* name, core::quaternion value);

				virtual EAttributeType getType() const;

				virtual matrix4f getMatrix();

				virtual const c8* getTypeString() const;

		};
	}
}

#endif /* CQUATERNIONATTRIBUTE_H_ */
