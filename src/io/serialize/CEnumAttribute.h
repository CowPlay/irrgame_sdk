/*
 * CEnumAttribute.h
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#ifndef CENUMATTRIBUTE_H_
#define CENUMATTRIBUTE_H_

#include "io/serialize/IAttribute.h"
#include "core/collections/stringc.h"

namespace irrgame
{
	namespace io
	{
		// Attribute implemented for enumeration literals
		class CEnumAttribute: public IAttribute
		{
			public:

				//! Default constructor
				CEnumAttribute(const c8* name, const c8* value,
						const c8* const * literals);

				virtual void setEnum(const c8* enumValue,
						const c8* const * enumerationLiterals);

				virtual s32 getInt();

				virtual f32 getFloat();

				virtual bool getBool();

				virtual core::stringc getString();

				virtual void setInt(s32 intValue);

				virtual void setFloat(f32 floatValue);

				virtual void setString(const c8* text);

				virtual const c8* getEnum();

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

			public:
				core::stringc Value;
				arraystr EnumLiterals;
		};
	}
}

#endif /* CENUMATTRIBUTE_H_ */
