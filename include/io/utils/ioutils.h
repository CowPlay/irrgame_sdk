// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_CORE_UTIL_H_INCLUDED__
#define __IRR_CORE_UTIL_H_INCLUDED__

#include "io/SPath.h"

namespace irrgame
{
	namespace io
	{
		class ioutils
		{
			public:

				// ----------- some basic quite often used string functions -----------------
				//! search if a filename has a proper extension
				static s32 isFileExtension(const core::stringc& filename,
						const core::stringc& ext0, const core::stringc& ext1,
						const core::stringc& ext2);

				//! search if a filename has a proper extension
				static bool hasFileExtension(const core::stringc& filename,
						const core::stringc& ext0, const core::stringc& ext1 =
								"", const core::stringc& ext2 = "");

				//! cut the filename extension from a source file path and store it in a dest file path
				static core::stringc& cutFilenameExtension(core::stringc &dest,
						const core::stringc &source);

				//! Returns new string which contains the filename extension from a file path
				/* After used result you must delete it */
				static core::stringc* getFileNameExtension(
						const core::stringc& path);

				//! delete path from filename
				static core::stringc& deletePathFromFilename(
						core::stringc& filename);

				//! trim paths
				static core::stringc& deletePathFromPath(
						core::stringc& filename, s32 pathCount);

				//! looks if file is in the same directory of path. returns offset of directory.
				//! 0 means in same directory. 1 means file is direct child of path
				static s32 isInSameDirectory(const core::stringc& path,
						const core::stringc& file);

				//! returns the directory part of a filename, i.e. all until the first
				//! slash or backslash, excluding it. If no directory path is prefixed, a '.'
				//! is returned.
				static core::stringc getFileDir(const core::stringc& filename);

				//! some standard function ( to remove dependencies )
				static s32 isdigit(s32 c);

				static s32 isspace(s32 c);

				static s32 isupper(s32 c);

				//! returns true if a character is whitespace
				static bool isWhiteSpace(c8 c);

				static s32 getByteFromHex(c8 h);

				static void getHexStrFromByte(c8 byte, c8* out);
		};

	} // end namespace core
} // end namespace irr

#endif

