// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_ATTRIBUTE_EXCHANGING_OBJECT_H_INCLUDED__
#define __I_ATTRIBUTE_EXCHANGING_OBJECT_H_INCLUDED__

#include "core/base/baseTypes.h"
#include "SAttributeReadWriteOptions.h"

namespace irrgame
{
	namespace io
	{
		class IAttributes;

		//! An object which is able to serialize and deserialize its attributes into an attributes object
		class IAttributeExchangingObject: virtual public IReferenceCounted
		{
			public:

				//! Writes attributes of the object.
				/** Implement this to expose the attributes of your scene node animator for
				 scripting languages, editors, debuggers or xml serialization purposes. */
				virtual void serializeAttributes(IAttributes* out,
						SAttributeReadWriteOptions* options = 0) const
				{
					//dummy because object can have only deserialize
				}

				//! Reads attributes of the object.
				/** Implement this to set the attributes of your scene node animator for
				 scripting languages, editors, debuggers or xml deserialization purposes. */
				virtual void deserializeAttributes(IAttributes* in,
						SAttributeReadWriteOptions* options = 0) = 0;

		};

	} // end namespace io
} // end namespace irrgame

#endif /* __I_ATTRIBUTE_EXCHANGING_OBJECT_H_INCLUDED__ */

