// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "io/CFileList.h"
#include "io/utils/ioutils.h"

namespace irrgame
{
	namespace io
	{

		static const core::stringc emptyFileListEntry;

		CFileList::CFileList(const core::stringc& path, bool ignoreCase,
				bool ignorePaths) :
				IgnorePaths(ignorePaths), IgnoreCase(ignoreCase), Path(path)
		{
#ifdef DEBUG
			setDebugName("CFileList");
#endif

			Path.replace('\\', '/');
		}

		CFileList::~CFileList()
		{
			Files.clear();
		}

		u32 CFileList::getFileCount() const
		{
			return Files.size();
		}

		void CFileList::sort()
		{
			Files.sort();
		}

		const core::stringc& CFileList::getFileName(u32 index) const
		{
			if (index >= Files.size())
			{
				return core::stringc::getEmpty();
			}

			return Files[index].Name;
		}

		//! Gets the full name of a file in the list, path included, based on an index.
		const core::stringc& CFileList::getFullFileName(u32 index) const
		{
			if (index >= Files.size())
			{
				return core::stringc::getEmpty();
			}

			return Files[index].FullName;
		}

		//! adds a file or folder
		u32 CFileList::addItem(const core::stringc& fullPath, u32 size,
				bool isDirectory, u32 id)
		{
			SFileListEntry entry;
			entry.Size = size;
			entry.ID = id;
			entry.Name = fullPath;
			entry.Name.replace('\\', '/');
			entry.IsDirectory = isDirectory;

			// remove trailing slash
			if (entry.Name.lastChar() == '/')
			{
				entry.IsDirectory = true;
				entry.Name[entry.Name.size() - 1] = 0;
//				entry.Name.validate();
			}

			if (IgnoreCase)
				entry.Name.makeLower();

			entry.FullName = entry.Name;

			io::ioutils::deletePathFromFilename(entry.Name);

			if (IgnorePaths)
			{
				entry.FullName = entry.Name;
			}

			Files.pushBack(entry);

			return Files.size() - 1;
		}

		//! Returns the ID of a file in the file list, based on an index.
		u32 CFileList::getID(u32 index) const
		{
			return index < Files.size() ? Files[index].ID : 0;
		}

		bool CFileList::isDirectory(u32 index) const
		{
			bool ret = false;
			if (index < Files.size())
				ret = Files[index].IsDirectory;

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return ret;
		}

		//! Returns the size of a file
		u32 CFileList::getFileSize(u32 index) const
		{
			return index < Files.size() ? Files[index].Size : 0;
		}

		//! Searches for a file or folder within the list, returns the index
		s32 CFileList::findFile(const core::stringc& filename,
				bool isDirectory = false) const
		{
			SFileListEntry entry;
			entry.FullName = filename;
			entry.IsDirectory = isDirectory;

			// swap
			entry.FullName.replace('\\', '/');

			// remove trailing slash
			if (entry.Name.lastChar() == '/')
			{
				entry.IsDirectory = true;
				entry.Name[entry.Name.size() - 1] = 0;
//				entry.Name.validate();
			}

			if (IgnoreCase)
				entry.FullName.makeLower();

			if (IgnorePaths)
			{
				io::ioutils::deletePathFromFilename(entry.FullName);
			}

			return Files.linearReverseSearch(entry);
		}

		//! Returns the base path of the file list
		const core::stringc& CFileList::getPath() const
		{
			return Path;
		}

		//! IFileList creator
		IFileList* createFileList(const core::stringc& path, bool ignoreCase,
				bool ignorePaths)
		{
			return new CFileList(path, ignoreCase, ignorePaths);
		}

	} // end namespace irr
} // end namespace io

