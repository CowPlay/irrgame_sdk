/*
 * CColorAttribute.h
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#ifndef CCOLORATTRIBUTE_H_
#define CCOLORATTRIBUTE_H_

#include "io/serialize/CNumbersAttribute.h"
#include "core/collections/stringc.h"

namespace irrgame
{
	namespace io
	{
		//! Attribute implemented for colors
		class CColorAttribute: public CNumbersAttribute
		{
			public:

				//! Default constructor for colorf
				CColorAttribute(const c8* name, const video::SColorf& value);

				//! Default constructor for color
				CColorAttribute(const c8* name, const video::SColor& value);

				virtual s32 getInt();

				virtual f32 getFloat();

				virtual void setInt(s32 intValue);

				virtual void setFloat(f32 floatValue);

				virtual core::stringc getString();

				virtual void setString(const c8* text);

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

		};
	}
}

#endif /* CCOLORATTRIBUTE_H_ */
