/*
 * CMatrixAttribute.h
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#ifndef CMATRIXATTRIBUTE_H_
#define CMATRIXATTRIBUTE_H_
#include "io/serialize/CNumbersAttribute.h"
namespace irrgame
{
	namespace io
	{
		// Attribute implemented for matrices
		class CMatrixAttribute: public CNumbersAttribute
		{
			public:

				CMatrixAttribute(const c8* name, core::matrix4 value);

				virtual E_ATTRIBUTE_TYPE getType() const;

				virtual core::quaternion getQuaternion();

				virtual const c8* getTypeString() const;

		};
	}
}

#endif /* CMATRIXATTRIBUTE_H_ */
