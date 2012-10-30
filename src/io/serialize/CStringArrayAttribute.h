/*
 * CStringArrayAttribute.h
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#ifndef CSTRINGARRAYATTRIBUTE_H_
#define CSTRINGARRAYATTRIBUTE_H_

#include "io/serialize/IAttribute.h"

namespace irrgame
{
	namespace io
	{
		// Attribute implemented for array of stringw
		class CStringArrayAttribute: public IAttribute
		{
			public:

				//! Default constructor
				CStringArrayAttribute(const c8* name, const arraystr& value);

				virtual arraystr getArray();

				virtual void setArray(const arraystr& value);

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

			public:

				arraystr Value;
		};
	}
}

#endif /* CSTRINGARRAYATTRIBUTE_H_ */
