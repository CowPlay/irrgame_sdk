// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_CORE_UTIL_H_INCLUDED__
#define __IRR_CORE_UTIL_H_INCLUDED__

#include "core/irrgamecollections.h"
#include "io/SPath.h"

namespace irrgame
{
	namespace io
	{

		// ----------- some basic quite often used string functions -----------------
		//! search if a filename has a proper extension
		inline s32 isFileExtension(const stringc& filename,
				const stringc& ext0, const stringc& ext1,
				const stringc& ext2)
		{
			s32 extPos = filename.findLast('.');
			if (extPos < 0)
				return 0;

			extPos += 1;
			if (filename.equalsSubstringIgnoreCase(ext0, extPos))
				return 1;
			if (filename.equalsSubstringIgnoreCase(ext1, extPos))
				return 2;
			if (filename.equalsSubstringIgnoreCase(ext2, extPos))
				return 3;
			return 0;
		}

		//! search if a filename has a proper extension
		inline bool hasFileExtension(const stringc& filename,
				const stringc& ext0, const stringc& ext1 = "",
				const stringc& ext2 = "")
		{
			return isFileExtension(filename, ext0, ext1, ext2) > 0;
		}

		//! cut the filename extension from a source file path and store it in a dest file path
		inline stringc& cutFilenameExtension(stringc &dest,
				const stringc &source)
		{
			s32 endPos = source.findLast('.');
			dest = source.subString(0, endPos < 0 ? source.size() : endPos);
			return dest;
		}

		//! get the filename extension from a file path
		inline stringc& getFileNameExtension(stringc &dest,
				const stringc &source)
		{
			s32 endPos = source.findLast('.');
			if (endPos < 0)
				dest = "";
			else
				dest = source.subString(endPos, source.size());
			return dest;
		}

		//! delete path from filename
		inline stringc& deletePathFromFilename(stringc& filename)
		{
			// delete path from filename
			const c8* s = filename.cStr();
			const c8* p = s + filename.size();

			// search for path separator or beginning
			while (*p != '/' && *p != '\\' && p != s)
				p--;

			if (p != s)
			{
				++p;
				filename = p;
			}
			return filename;
		}

		//! trim paths
		inline stringc& deletePathFromPath(stringc& filename,
				s32 pathCount)
		{
			// delete path from filename
			s32 i = filename.size();

			// search for path separator or beginning
			while (i >= 0)
			{
				if (filename[i] == '/' || filename[i] == '\\')
				{
					if (--pathCount <= 0)
						break;
				}
				--i;
			}

			if (i > 0)
			{
				filename[i + 1] = 0;
				filename.validate();
			}
			else
				filename = "";
			return filename;
		}

		//! looks if file is in the same directory of path. returns offset of directory.
		//! 0 means in same directory. 1 means file is direct child of path
		inline s32 isInSameDirectory(const stringc& path,
				const stringc& file)
		{
			s32 subA = 0;
			s32 subB = 0;
			s32 pos;

			if (path.size() && !path.equalsn(file, path.size()))
				return -1;

			pos = 0;
			while ((pos = path.findNext('/', pos)) >= 0)
			{
				subA += 1;
				pos += 1;
			}

			pos = 0;
			while ((pos = file.findNext('/', pos)) >= 0)
			{
				subB += 1;
				pos += 1;
			}

			return subB - subA;
		}

		//! returns the directory part of a filename, i.e. all until the first
		//! slash or backslash, excluding it. If no directory path is prefixed, a '.'
		//! is returned.
		inline stringc getFileDir(const stringc& filename)
		{
			// find last forward or backslash
			s32 lastSlash = filename.findLast('/');
			const s32 lastBackSlash = filename.findLast('\\');
			lastSlash = lastSlash > lastBackSlash ? lastSlash : lastBackSlash;

			if ((u32) lastSlash < filename.size())
				return filename.subString(0, lastSlash);
			else
				return ".";
		}

		//! some standard function ( to remove dependencies )
#undef isdigit
#undef isspace
#undef isupper
		inline s32 isdigit(s32 c)
		{
			return c >= '0' && c <= '9';
		}
		inline s32 isspace(s32 c)
		{
			return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
					|| c == '\v';
		}
		inline s32 isupper(s32 c)
		{
			return c >= 'A' && c <= 'Z';
		}

		//! returns true if a character is whitespace
		inline bool isWhiteSpace(c8 c)
		{
			return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
		}

		inline s32 getByteFromHex(c8 h)
		{
			if (h >= '0' && h <= '9')
				return h - '0';

			if (h >= 'a' && h <= 'f')
				return h - 'a' + 10;

			return 0;
		}

		inline void getHexStrFromByte(c8 byte, c8* out)
		{
			s32 b = (byte & 0xf0) >> 4;

			for (s32 i = 0; i < 2; ++i)
			{
				if (b >= 0 && b <= 9)
					out[i] = b + '0';
				if (b >= 10 && b <= 15)
					out[i] = (b - 10) + 'a';

				b = byte & 0x0f;
			}
		}

	} // end namespace core
} // end namespace irr

#endif

