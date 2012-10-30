/*
 * CStringAttribute.h
 *
 *  Created on: Aug 8, 2012
 *      Author: gregorytkach
 */

#ifndef CSTRINGATTRIBUTE_H_
#define CSTRINGATTRIBUTE_H_

#include "io/serialize/IAttribute.h"

namespace irrgame
{
	namespace io
	{
		// Attribute implemented for strings
		class CStringAttribute: public IAttribute
		{
			public:

				//! Default constructor
				CStringAttribute(const c8* name, const c8* value);

				//! Extended constructor for work with binary data
				CStringAttribute(const c8* name, void* binaryData,
						s32 lenghtInBytes);

				virtual s32 getInt();

				virtual f32 getFloat();

				virtual bool getBool();

				virtual core::stringc getString();

				virtual void setInt(s32 intValue);

				virtual void setFloat(f32 floatValue);

				virtual void setString(const c8* text);

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

				virtual void getBinary(void* outdata, s32 maxLength);

				virtual void setBinary(void* data, s32 maxLength);

			public:
				core::stringc Value;
		};

	}
}
#endif /* CSTRINGATTRIBUTE_H_ */
