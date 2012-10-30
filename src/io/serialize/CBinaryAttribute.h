/*
 * CBinaryAttribute.h
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#ifndef CBINARYATTRIBUTE_H_
#define CBINARYATTRIBUTE_H_

#include "io/serialize/CStringAttribute.h"

namespace irrgame
{
	namespace io
	{
		// Attribute implemented for binary data
		class CBinaryAttribute: public CStringAttribute
		{
			public:

				//! Default constructor
				CBinaryAttribute(const c8* name, void* binaryData,
						s32 lenghtInBytes);

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

		};
	}
}

#endif /* CBINARYATTRIBUTE_H_ */
