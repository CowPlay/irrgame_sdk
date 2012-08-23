/*
 * CRectAttribute.h
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#ifndef CRECTATTRIBUTE_H_
#define CRECTATTRIBUTE_H_
#include "io/serialize/CNumbersAttribute.h"
namespace irrgame
{
	namespace io
	{
		// Attribute implemented for rectangles
		class CRectAttribute: public CNumbersAttribute
		{
			public:

				//! Default constructor
				CRectAttribute(const c8* name, recti value);

				virtual E_ATTRIBUTE_TYPE getType() const;

				virtual const c8* getTypeString() const;

		};

	}
}

#endif /* CRECTATTRIBUTE_H_ */
