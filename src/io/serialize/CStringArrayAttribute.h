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
				CStringArrayAttribute(const c8* name,
						const core::array<core::stringc>& value);

				virtual core::array<core::stringc> getArray();

				virtual void setArray(const core::array<core::stringc>& value);

				virtual E_ATTRIBUTE_TYPE getType() const;

				virtual const c8* getTypeString() const;

			public:

				core::array<core::stringc> Value;
		};
	}
}

#endif /* CSTRINGARRAYATTRIBUTE_H_ */
