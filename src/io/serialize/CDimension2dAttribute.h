/*
 * CDimension2dAttribute.h
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#ifndef CDIMENSION2DATTRIBUTE_H_
#define CDIMENSION2DATTRIBUTE_H_

#include "io/serialize/CNumbersAttribute.h"
namespace irrgame
{
	namespace io
	{
		// Attribute implemented for dimension2d
		class CDimension2dAttribute: public CNumbersAttribute
		{
			public:

				//! Default constructor
				CDimension2dAttribute(const c8* name, dimension2df value);

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

		};

	}
}

#endif /* CDIMENSION2DATTRIBUTE_H_ */
