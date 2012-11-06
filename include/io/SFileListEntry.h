/*
 * SFileListEntry.h
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#ifndef SFILELISTENTRY_H_
#define SFILELISTENTRY_H_

#include "core/collections/stringc.h"

namespace irrgame
{
	namespace io
	{

		//! An entry in a list of files, can be a folder or a file.
		struct SFileListEntry
		{

			public:

				/*
				 * Operators
				 */

				//! The == operator is provided so that CFileList can slowly search the list!
				bool operator ==(const struct SFileListEntry& other) const;

				//! Inequality operator
				bool operator !=(const struct SFileListEntry& other) const;

				//! The < operator is provided so that CFileList can sort and quickly search the list.
				bool operator <(const struct SFileListEntry& other) const;

			public:
				//! The name of the file
				/** If this is a file or folder in the virtual filesystem and the archive
				 was created with the ignoreCase flag then the file name will be lower case. */
				core::stringc Name;

				//! The name of the file including the path
				/** If this is a file or folder in the virtual filesystem and the archive was
				 created with the ignoreDirs flag then it will be the same as Name. */
				core::stringc FullName;

				//! The size of the file in bytes
				u32 Size;

				//! The ID of the file in an archive
				/** This is used to link the FileList entry to extra info held about this
				 file in an archive, which can hold things like data offset and CRC. */
				u32 ID;

				//! True if this is a folder, false if not.
				bool IsDirectory;
		};

	}  // namespace io
}  // namespace irrgame

#endif /* SFILELISTENTRY_H_ */
