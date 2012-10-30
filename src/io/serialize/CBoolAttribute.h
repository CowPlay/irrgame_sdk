/*
 * CBoolAttribute.h
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#ifndef CBOOLATTRIBUTE_H_
#define CBOOLATTRIBUTE_H_
#include "io/serialize/IAttribute.h"

namespace irrgame
{
	namespace io
	{
		// Attribute implemented for boolean values
		class CBoolAttribute: public IAttribute
		{
			public:

				//! Default constructor
				CBoolAttribute(const c8* name, bool value);

				virtual s32 getInt();

				virtual f32 getFloat();

				virtual bool getBool();

				virtual core::stringc getString();

				virtual void setInt(s32 intValue);

				virtual void setFloat(f32 floatValue);

				virtual void setBool(bool boolValue);

				virtual void setString(const c8* string);

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

			public:

				bool BoolValue;
		};

	}
}

#endif /* CBOOLATTRIBUTE_H_ */
