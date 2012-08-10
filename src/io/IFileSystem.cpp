/*
 * IFileSystem.cpp
 *
 *	Implementation of IFileSystem static methods
 *
 *  Created on: Aug 7, 2012
 *      Author: gregorytkach
 */
#include "irrgamesdkCompileConfig.h"
#ifdef _IRRGAME_MACOSX_

#include "io/IFileSystem.h"
#include "io/serialize/IAttributes.h"
namespace irrgame
{
	namespace io
	{
		//! Currently used FileSystemType
		EFileSystemType IFileSystem::FileSystemType;

		//! WorkingDirectory for Native and Virtual filesystems
		core::stringc IFileSystem::WorkingDirectory[2];

		//! currently attached Archives
		core::array<IFileArchive*> IFileSystem::FileArchives;

		//! Creates a XML Reader from a file which returns all parsed strings as ASCII/UTF-8 characters (char*).
		/** See IXMLReader for more information on how to use the parser.
		 \return 0, if file could not be opened, otherwise a pointer to the created
		 IXMLReader is returned. After use, the reader
		 has to be deleted using its IXMLReader::drop() method.
		 See IReferenceCounted::drop() for more information. */
		IXMLReader* IFileSystem::createXMLReader(const core::stringc& filename)
		{
			// Create the file using an absolute path so that it matches
			// the scheme used by CNullDriver::getTexture().
			IReadFile * file = createReadFile(
					IFileSystem::getAbsolutePath(filename));

			IXMLReader* reader = irrgame::io::createXMLReader(file);

			if (file)
				file->drop();

			return reader;
		}

		//! Creates a XML Reader from a file which returns all parsed strings as ASCII/UTF-8 characters (char*).
		/** Use createXMLReader() if you prefer wchar_t* instead of char*. See IIrrXMLReader for
		 more information on how to use the parser.
		 \return 0, if file could not be opened, otherwise a pointer to the created
		 IXMLReader is returned. After use, the reader
		 has to be deleted using its IXMLReader::drop() method.
		 See IReferenceCounted::drop() for more information. */
		IXMLReader* IFileSystem::createXMLReader(IReadFile* file)
		{
			return irrgame::io::createXMLReader(file);
		}

		//! Creates a XML Writer from a file.
		IXMLWriter* IFileSystem::createXMLWriter(const core::stringc& filename)
		{
			IWriteFile* file = createAndWriteFile(filename);

			IXMLWriter* writer = irrgame::io::createXMLWriter(file);

			if (file)
				file->drop();

			return writer;
		}

		//! Creates a XML Writer from a file.
		IXMLWriter* IFileSystem::createXMLWriter(IWriteFile* file)
		{
			return irrgame::io::createXMLWriter(file);
		}

		//! flatten a path and file name for example: "/you/me/../." becomes "/you"
		core::stringc& IFileSystem::flattenFilename(core::stringc& directory,
				const core::stringc& root)
		{
			directory.replace('\\', '/');
			if (directory.lastChar() != '/')
				directory.append('/');

			core::stringc dir;
			core::stringc subdir;

			s32 lastpos = 0;
			s32 pos = 0;
			bool lastWasRealDir = false;

			while ((pos = directory.findNext('/', lastpos)) >= 0)
			{
				subdir = directory.subString(lastpos, pos - lastpos + 1);

				if (subdir == "../")
				{
					if (lastWasRealDir)
					{
						deletePathFromPath(dir, 2);
						lastWasRealDir = (dir.size() != 0);
					}
					else
					{
						dir.append(subdir);
						lastWasRealDir = false;
					}
				}
				else if (subdir == "/")
				{
					dir = root;
				}
				else if (subdir != "./")
				{
					dir.append(subdir);
					lastWasRealDir = true;
				}

				lastpos = pos + 1;
			}
			directory = dir;
			return directory;
		}

		//! opens a file for read access
		IReadFile* IFileSystem::createAndOpenFile(const core::stringc& filename)
		{
			return io::createReadFile(filename);
		}

		//! Creates an IReadFile interface for treating memory like a file.
		IReadFile* IFileSystem::createMemoryReadFile(void* memory, s32 len,
				const core::stringc& fileName, bool deleteMemoryWhenDropped)
		{
			return irrgame::io::createMemoryReadFile(memory, len, fileName,
					deleteMemoryWhenDropped);
		}

		//! Creates an IReadFile interface for reading files inside files
		IReadFile* IFileSystem::createLimitReadFile(
				const core::stringc& fileName, IReadFile* alreadyOpenedFile,
				long pos, long areaSize)
		{
			return irrgame::io::createLimitReadFile(fileName, alreadyOpenedFile,
					pos, areaSize);
		}

		//! Creates an IReadFile interface for treating memory like a file.
		IWriteFile* IFileSystem::createMemoryWriteFile(void* memory, s32 len,
				const core::stringc& fileName, bool deleteMemoryWhenDropped)
		{
			return irrgame::io::createMemoryWriteFile(memory, len, fileName,
					deleteMemoryWhenDropped);
		}

		//! Opens a file for write access.
		IWriteFile* IFileSystem::createAndWriteFile(
				const core::stringc& filename, bool append)
		{
			return createWriteFile(filename, append);
		}

		//! Creates a new empty collection of attributes, usable for serialization and more.
		IAttributes* IFileSystem::createEmptyAttributes()
		{
			return createAttributes();
		}

	}
}
#endif

