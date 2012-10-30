/*
 * CLine3dAttribute.h
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#ifndef CLINE3DATTRIBUTE_H_
#define CLINE3DATTRIBUTE_H_

#include "CNumbersAttribute.h"

namespace irrgame
{
	namespace io
	{
		// Attribute implemented for 3d lines
		class CLine3dAttribute: public CNumbersAttribute
		{
			public:

				//! Default constructor
				CLine3dAttribute(const c8* name, line3df value);

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

		};
	}
}
#endif /* CLINE3DATTRIBUTE_H_ */
