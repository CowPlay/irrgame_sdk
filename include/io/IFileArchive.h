// Copyright (C) 2002-2009 Nikolaus Gebhardt/ Thomas Alten
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_FILE_ARCHIVE_H_INCLUDED__
#define __I_FILE_ARCHIVE_H_INCLUDED__

#include "IReadFile.h"
#include "IFileList.h"

namespace irrgame
{

	namespace io
	{

		//! FileSystemType: which Filesystem should be used for e.g. browsing
		enum EFileSystemType
		{
			FILESYSTEM_NATIVE = 0,	// Native OS FileSystem
			FILESYSTEM_VIRTUAL	// Virtual FileSystem
		};

		//! Contains the different types of archives
		enum E_FILE_ARCHIVE_TYPE
		{
			//! A PKZIP archive
			EFAT_ZIP = MAKE_IRR_ID('Z','I','P', 0),

			//! A gzip archive
			EFAT_GZIP = MAKE_IRR_ID('g','z','i','p'),

			//! A virtual directory
			EFAT_FOLDER = MAKE_IRR_ID('f','l','d','r'),

			//! An ID Software PAK archive
			EFAT_PAK = MAKE_IRR_ID('P','A','K', 0),

			//! A Nebula Device archive
			EFAT_NPK = MAKE_IRR_ID('N','P','K', 0),

			//! A Tape ARchive
			EFAT_TAR = MAKE_IRR_ID('T','A','R', 0),

			//! The type of this archive is unknown
			EFAT_UNKNOWN = MAKE_IRR_ID('u','n','k','n')
		};

		//! The FileArchive manages archives and provides access to files inside them.
		class IFileArchive: public virtual IReferenceCounted
		{
			public:

				//! Opens a file based on its name
				/** Creates and returns a new IReadFile for a file in the archive.
				 \param filename The file to open
				 \return Returns A pointer to the created file on success,
				 or 0 on failure. */
				virtual IReadFile* createAndOpenFile(const path& filename) =0;

				//! Opens a file based on its position in the file list.
				/** Creates and returns
				 \param index The zero based index of the file.
				 \return Returns a pointer to the created file on success, or 0 on failure. */
				virtual IReadFile* createAndOpenFile(u32 index) =0;

				//! Returns the complete file tree
				/** \return Returns the complete directory tree for the archive,
				 including all files and folders */
				virtual const IFileList* getFileList() const =0;

				//! get the archive type
				virtual E_FILE_ARCHIVE_TYPE getType() const
				{
					return EFAT_UNKNOWN;
				}

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

