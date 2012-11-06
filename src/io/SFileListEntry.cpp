/*
 * SFileListEntry.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#include "io/SFileListEntry.h"

namespace irrgame
{
	namespace io
	{

		//! The == operator is provided so that CFileList can slowly search the list!
		bool SFileListEntry::operator==(
				const struct SFileListEntry& other) const
		{
			bool result = false;

			if ((IsDirectory == other.IsDirectory))
			{
				FullName.equalsIgnoreCase(other.FullName);
			}

			return result;
		}

		//! Inequality operator
		bool SFileListEntry::operator!=(
				const struct SFileListEntry& other) const
		{
			return !(*this == other);
		}

		//! The < operator is provided so that CFileList can sort and quickly search the list.
		bool SFileListEntry::operator<(const struct SFileListEntry& other) const
		{
			bool result = false;

			if (IsDirectory != other.IsDirectory)
			{
				result = IsDirectory;
			}
			else
			{
				result = FullName.lowerIgnoreCase(other.FullName);
			}

			return result;
		}

	}  // namespace io
}  // namespace irrgame
