/*
 * CBBoxAttribute.h
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#ifndef CBBOXATTRIBUTE_H_
#define CBBOXATTRIBUTE_H_

#include "CNumbersAttribute.h"

namespace irrgame
{
	namespace io
	{
		// Attribute implemented for bounding boxes
		class CBBoxAttribute: public CNumbersAttribute
		{
			public:

				//! Default constructor
				CBBoxAttribute(const c8* name, aabbox3df value);

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

		};
	}
}

#endif /* CBBOXATTRIBUTE_H_ */
