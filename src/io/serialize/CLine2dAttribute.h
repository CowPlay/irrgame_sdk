/*
 * CLine2dAttribute.h
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#ifndef CLINE2DATTRIBUTE_H_
#define CLINE2DATTRIBUTE_H_
#include "CNumbersAttribute.h"
namespace irrgame
{
	namespace io
	{
		// Attribute implemented for 2d lines
		class CLine2dAttribute: public CNumbersAttribute
		{
			public:

				//! Default constructor
				CLine2dAttribute(const c8* name, line2df value);

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

		};
	}
}
#endif /* CLINE2DATTRIBUTE_H_ */
