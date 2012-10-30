/*
 * CTriangleAttribute.h
 *
 *  Created on: Aug 10, 2012
 *      Author: gregorytkach
 */

#ifndef CTRIANGLEATTRIBUTE_H_
#define CTRIANGLEATTRIBUTE_H_

#include "CNumbersAttribute.h"

namespace irrgame
{
	namespace io
	{
		// Attribute implemented for triangles
		class CTriangleAttribute: public CNumbersAttribute
		{
			public:

				//! Default constructor
				CTriangleAttribute(const c8* name, triangle3df value);

				virtual EAttributeType getType() const;

				virtual plane3df getPlane();

				virtual const c8* getTypeString() const;
		};
	}
}

#endif /* CTRIANGLEATTRIBUTE_H_ */
