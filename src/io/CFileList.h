// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_FILE_LIST_H_INCLUDED__
#define __C_FILE_LIST_H_INCLUDED__

#include "io/IFileList.h"
#include "io/SFileListEntry.h"
#include "core/collections/array.h"


namespace irrgame
{
	namespace io
	{

		//! Implementation of a file list
		class CFileList: public IFileList
		{
			public:

				//! Constructor
				/** \param path The path of this file archive */
				CFileList(const core::stringc& path, bool ignoreCase,
						bool ignorePaths);

				//! Destructor
				virtual ~CFileList();

				//! Add as a file or folder to the list
				/** \param fullPath The file name including path, up to the root of the file list.
				 \param isDirectory True if this is a directory rather than a file.
				 \param size The size of the file in bytes.
				 \param id The ID of the file in the archive which owns it */
				virtual u32 addItem(const core::stringc& fullPath, u32 size,
						bool isDirectory, u32 id = 0);

				//! Sorts the file list. You should call this after adding any items to the file list
				virtual void sort();

				//! Returns the amount of files in the filelist.
				virtual u32 getFileCount() const;

				//! Gets the name of a file in the list, based on an index.
				virtual const core::stringc& getFileName(u32 index) const;

				//! Gets the full name of a file in the list, path included, based on an index.
				virtual const core::stringc& getFullFileName(u32 index) const;

				//! Returns the ID of a file in the file list, based on an index.
				virtual u32 getID(u32 index) const;

				//! Returns true if the file is a directory
				virtual bool isDirectory(u32 index) const;

				//! Returns the size of a file
				virtual u32 getFileSize(u32 index) const;

				//! Searches for a file or folder within the list, returns the index
				virtual s32 findFile(const core::stringc& filename,
						bool isFolder) const;

				//! Returns the base path of the file list
				virtual const core::stringc& getPath() const;

			protected:

				//! Ignore paths when adding or searching for files
				bool IgnorePaths;

				//! Ignore case when adding or searching for files
				bool IgnoreCase;

				//! Path to the file list
				core::stringc Path;

				//! List of files
				core::array<SFileListEntry> Files;
		};

	} // end namespace irr
} // end namespace io

#endif

