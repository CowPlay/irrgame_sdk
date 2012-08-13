/*
 * CPlaneAttribute.h
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#ifndef CPLANEATTRIBUTE_H_
#define CPLANEATTRIBUTE_H_

#include "CNumbersAttribute.h"

namespace irrgame
{
	namespace io
	{
		// Attribute implemented for planes
		class CPlaneAttribute: public CNumbersAttribute
		{
			public:
				//! Default constructor
				CPlaneAttribute(const c8* name, core::plane3df value);

				virtual E_ATTRIBUTE_TYPE getType() const;

				virtual const c8* getTypeString() const;

		};

	}
}

#endif /* CPLANEATTRIBUTE_H_ */
