/*
 * IFileSystem.cpp
 *
 *	Implementation of IFileSystem static methods
 *
 *  Created on: Aug 7, 2012
 *      Author: gregorytkach
 */
#include "irrgamesdkCompileConfig.h"	//TODO: replace to riigame player config
#ifdef _IRRGAME_MACOSX_

#include "io/IFileSystem.h"
#include "io/IReadFile.h"

namespace irrgame
{
	namespace io
	{
		//! Creates a XML Reader from a file which returns all parsed strings as wide characters (wchar_t*).
		/** Use createXMLReaderUTF8() if you prefer char* instead of wchar_t*. See IIrrXMLReader for
		 more information on how to use the parser.
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
			if (!file)
				return 0;

			IXMLReader* reader = irrgame::io::createXMLReader(file);
			file->drop();
			return reader;
		}

		//! Creates a XML Reader from a file which returns all parsed strings as wide characters (wchar_t*).
		/** Use createXMLReaderUTF8() if you prefer char* instead of wchar_t*. See IIrrXMLReader for
		 more information on how to use the parser.
		 \return 0, if file could not be opened, otherwise a pointer to the created
		 IXMLReader is returned. After use, the reader
		 has to be deleted using its IXMLReader::drop() method.
		 See IReferenceCounted::drop() for more information. */
		IXMLReader* IFileSystem::createXMLReader(IReadFile* file)
		{
			if (!file)
				return 0;

			return irrgame::io::createXMLReader(file);
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

	}
}
#endif

