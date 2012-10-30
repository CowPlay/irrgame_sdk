// Copyright (C) 2002-2009 Nikolaus Gebhardt/ Thomas Alten
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_FILE_ARCHIVE_H_INCLUDED__
#define __I_FILE_ARCHIVE_H_INCLUDED__

#include "IReadFile.h"
#include "IFileList.h"
#include "EFileArchiveType.h"

namespace irrgame
{

	namespace io
	{

		//! The FileArchive manages archives and provides access to files inside them.
		class IFileArchive: public virtual IReferenceCounted
		{
			public:

				//! Opens a file based on its name
				/** Creates and returns a new IReadFile for a file in the archive.
				 \param filename The file to open
				 \return Returns A pointer to the created file on success,
				 or 0 on failure. */
				virtual IReadFile* createAndOpenFile(
						const core::stringc& filename) = 0;

				//! Opens a file based on its position in the file list.
				/** Creates and returns
				 \param index The zero based index of the file.
				 \return Returns a pointer to the created file on success, or 0 on failure. */
				virtual IReadFile* createAndOpenFile(u32 index) = 0;

				//! Returns the complete file tree
				/** \return Returns the complete directory tree for the archive,
				 including all files and folders */
				virtual const IFileList* getFileList() const = 0;

				//! get the archive type
				virtual E_FILE_ARCHIVE_TYPE getType() const
				{
					return EFAT_UNKNOWN;
				}

			public:
				//! An optionally used password string
				/** This variable is publicly accessible from the interface in order to
				 avoid single access patterns to this place, and hence allow some more
				 obscurity.
				 */
				core::stringc Password;
		};
	} // end namespace io
} // end namespace irr

#endif

