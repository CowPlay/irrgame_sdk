/*
 * CFloatAttribute.h
 *
 *  Created on: Aug 8, 2012
 *      Author: gregorytkach
 */

#ifndef CFLOATATTRIBUTE_H_
#define CFLOATATTRIBUTE_H_

#include "io/serialize/IAttribute.h"

namespace irrgame
{
	namespace io
	{

		// Attribute implemented for floats
		class CFloatAttribute: public IAttribute
		{
			public:

				//! Default constructor
				CFloatAttribute(const c8* name, f32 value);

				virtual s32 getInt();

				virtual f32 getFloat();

				virtual bool getBool();

				virtual core::stringc getString();

				virtual void setInt(s32 intValue);

				virtual void setFloat(f32 floatValue);

				virtual void setString(const c8* text);

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

			public:
				f32 Value;
		};
	}
}

#endif /* CFLOATATTRIBUTE_H_ */
