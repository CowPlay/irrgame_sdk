/*
 * CColorfAttribute.h
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#ifndef CCOLORFATTRIBUTE_H_
#define CCOLORFATTRIBUTE_H_

#include "io/serialize/CNumbersAttribute.h"
namespace irrgame
{
	namespace io
	{

		// Attribute implemented for floating point colors
		class CColorfAttribute: public CNumbersAttribute
		{
			public:

				//! Default constructor
				CColorfAttribute(const c8* name, video::SColorf value);

				virtual s32 getInt();

				virtual f32 getFloat();

				virtual void setInt(s32 intValue);

				virtual void setFloat(f32 floatValue);

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

		};
	}
}

#endif /* CCOLORFATTRIBUTE_H_ */
