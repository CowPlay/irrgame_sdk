/*
 * CVector2DAttribute.h
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#ifndef CVECTOR2DATTRIBUTE_H_
#define CVECTOR2DATTRIBUTE_H_
#include "io/serialize/CNumbersAttribute.h"
namespace irrgame
{
	namespace io
	{
		// Attribute implemented for 3d vectors
		class CVector2DAttribute: public CNumbersAttribute
		{
			public:

				//! Default constructor
				CVector2DAttribute(const c8* name, vector2df value);

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

		};

	}
}

#endif /* CVECTOR2DATTRIBUTE_H_ */
