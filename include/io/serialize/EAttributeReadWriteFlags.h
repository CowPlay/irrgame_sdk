/*
 * EAttributeReadWriteFlags.h
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#ifndef EATTRIBUTEREADWRITEFLAGS_H_
#define EATTRIBUTEREADWRITEFLAGS_H_

namespace irrgame
{

	namespace io
	{

		//! Enumeration flags passed through SAttributeReadWriteOptions to the IAttributeExchangingObject object
		enum E_ATTRIBUTE_READ_WRITE_FLAGS
		{
			//! Serialization/Deserializion is done for an xml file
			EARWF_FOR_FILE = 0x00000001,

			//! Serialization/Deserializion is done for an editor property box
			EARWF_FOR_EDITOR = 0x00000002,

			//! When writing filenames, relative paths should be used
			EARWF_USE_RELATIVE_PATHS = 0x00000004,

			//! Not used
			EARWF_COUNT
		};

	}  // namespace io
}  // namespace irrgame

#endif /* EATTRIBUTEREADWRITEFLAGS_H_ */
