/*
 * EFileSystemTypes.h
 *
 *  Created on: Aug 8, 2012
 *      Author: gregorytkach
 */

#ifndef EFILESYSTEMTYPES_H_
#define EFILESYSTEMTYPES_H_

namespace irrgame
{
	namespace io
	{
		//! FileSystemType: which Filesystem should be used for e.g. browsing
		enum EFileSystemType
		{
			FILESYSTEM_NATIVE = 0,	// Native OS FileSystem
			FILESYSTEM_VIRTUAL		// Virtual FileSystem. Example: current working directory is archive
		};

	}
}

#endif /* EFILESYSTEMTYPES_H_ */
