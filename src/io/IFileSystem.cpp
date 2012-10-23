/*
 * IFileSystem.cpp
 *
 *	Implementation of IFileSystem static methods
 *
 *  Created on: Aug 7, 2012
 *      Author: gregorytkach
 */

#include "io/IFileSystem.h"
#include "io/serialize/IAttributes.h"
namespace irrgame
{
	namespace io
	{

		//! Singleton realization
		IFileSystem& IFileSystem::getInstance()
		{
			static IFileSystem instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		IFileSystem::IFileSystem() :
				FileSystemType(FILESYSTEM_NATIVE)
		{
		}

		//! Creates a XML Reader from a file which returns all parsed strings as ASCII/UTF-8 characters (char*).
		/** See IXMLReader for more information on how to use the parser.
		 \return 0, if file could not be opened, otherwise a pointer to the created
		 IXMLReader is returned. After use, the reader
		 has to be deleted using its IXMLReader::drop() method.
		 See IReferenceCounted::drop() for more information. */
		IXMLReader* IFileSystem::createXMLReader(const stringc& filename)
		{
			// Create the file using an absolute path so that it matches
			// the scheme used by CNullDriver::getTexture().
			IReadFile * file = createReadFile(this->getAbsolutePath(filename));

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
		IXMLWriter* IFileSystem::createXMLWriter(const stringc& filename)
		{
			IWriteFile* file = createWriteFile(filename);

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
		stringc& IFileSystem::flattenFilename(stringc& directory,
				const stringc& root)
		{
			directory.replace('\\', '/');
			if (directory.lastChar() != '/')
				directory.append('/');

			stringc dir;
			stringc subdir;

			s32 lastpos = 0;
			s32 pos = 0;
			bool lastWasRealDir = false;

			while ((pos = directory.findFirst('/', lastpos)) >= 0)
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
		IReadFile* IFileSystem::createReadFile(const stringc& filename)
		{
			return io::createReadFile(filename);
		}

		//! Creates an IReadFile interface for treating memory like a file.
		IReadFile* IFileSystem::createMemoryReadFile(void* memory, s32 len,
				const stringc& fileName, bool deleteMemoryWhenDropped)
		{
			return io::createMemoryReadFile(memory, len, fileName,
					deleteMemoryWhenDropped);
		}

		//! Creates an IReadFile interface for reading files inside files
		IReadFile* IFileSystem::createLimitReadFile(const stringc& fileName,
				IReadFile* alreadyOpenedFile, long pos, long areaSize)
		{
			return io::createLimitReadFile(fileName, alreadyOpenedFile, pos,
					areaSize);
		}

		//! Creates an IReadFile interface for treating memory like a file.
		IWriteFile* IFileSystem::createMemoryWriteFile(void* memory, s32 len,
				const stringc& fileName, bool deleteMemoryWhenDropped)
		{
			return io::createMemoryWriteFile(memory, len, fileName,
					deleteMemoryWhenDropped);
		}

		//! Opens a file for write access.
		IWriteFile* IFileSystem::createWriteFile(const stringc& filename,
				bool append)
		{
			return io::createWriteFile(filename, append);
		}

		//! Creates a new empty collection of attributes, usable for serialization and more.
		IAttributes* IFileSystem::createEmptyAttributes()
		{
			return createAttributes();
		}

	}
}

