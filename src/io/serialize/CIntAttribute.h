/*
 * CIntAttribute.h
 *
 *  Created on: Aug 8, 2012
 *      Author: gregorytkach
 */

#ifndef CINTATTRIBUTE_H_
#define CINTATTRIBUTE_H_
#include "io/serialize/IAttribute.h"
namespace irrgame
{
	namespace io
	{
		// Attribute implemented for integers
		class CIntAttribute: public IAttribute
		{
			public:

				//! Default constructor
				CIntAttribute(const c8* name, s32 value);

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
				s32 Value;
		};
	}
}

#endif /* CINTATTRIBUTE_H_ */
