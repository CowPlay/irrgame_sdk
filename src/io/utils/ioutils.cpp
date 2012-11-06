/*
 * ioutils.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#include "io/utils/ioutils.h"

namespace irrgame
{
	namespace io
	{
		// ----------- some basic quite often used string functions -----------------
		//! search if a filename has a proper extension
		s32 ioutils::isFileExtension(const core::stringc& filename,
				const core::stringc& ext0, const core::stringc& ext1,
				const core::stringc& ext2)
		{
			s32 result = 0;

			s32 extPos = filename.findLast('.');

			if (extPos != IrrNotFound)
			{
				extPos += 1;
				if (filename.equalsIgnoreCase(ext0, extPos))
				{
					result = 1;
				}
				if (filename.equalsIgnoreCase(ext1, extPos))
				{
					result = 2;
				}
				if (filename.equalsIgnoreCase(ext2, extPos))
				{
					result = 3;
				}
			}

			return result;
		}

		//! search if a filename has a proper extension
		bool ioutils::hasFileExtension(const core::stringc& filename,
				const core::stringc& ext0, const core::stringc& ext1,
				const core::stringc& ext2)
		{
			return isFileExtension(filename, ext0, ext1, ext2) > 0;
		}

		//! cut the filename extension from a source file path and store it in a dest file path
		core::stringc& ioutils::cutFilenameExtension(core::stringc &dest,
				const core::stringc &source)
		{
			s32 endPos = source.findLast('.');
			dest = source.subString(0, endPos < 0 ? source.size() : endPos);
			return dest;
		}

		//! Returns new string which contains the filename extension from a file path
		core::stringc* ioutils::getFileNameExtension(const core::stringc& path)
		{
			core::stringc* result = 0;

			s32 endPos = path.findLast('.');

			if (endPos == IrrNotFound)
			{
				result = new core::stringc("");
			}
			else
			{
				// We add to endPost + 1 to prevent "." in extention
				result = new core::stringc(path.subString(endPos + 1, path.size()));
			}

			return result;
		}

//! delete path from filename
		core::stringc& ioutils::deletePathFromFilename(core::stringc& filename)
		{
			// delete path from filename
			const c8* s = filename.cStr();
			const c8* p = s + filename.size();

			// search for path separator or beginning
			while (*p != '/' && *p != '\\' && p != s)
			{
				p--;
			}

			if (p != s)
			{
				++p;
				filename = p;
			}

			return filename;
		}

//! trim paths
		core::stringc& ioutils::deletePathFromPath(core::stringc& filename,
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
				//				filename.validate();
			}
			else
			{
				filename = "";
			}

			return filename;
		}

//! looks if file is in the same directory of path. returns offset of directory.
//! 0 means in same directory. 1 means file is direct child of path
		s32 ioutils::isInSameDirectory(const core::stringc& path,
				const core::stringc& file)
		{
			s32 subA = 0;
			s32 subB = 0;
			s32 pos;

			if (path.size() && !path.equalsn(file, path.size()))
				return -1;

			pos = 0;
			while ((pos = path.findFirst('/', pos)) >= 0)
			{
				subA += 1;
				pos += 1;
			}

			pos = 0;
			while ((pos = file.findFirst('/', pos)) >= 0)
			{
				subB += 1;
				pos += 1;
			}

			return subB - subA;
		}

//! returns the directory part of a filename, i.e. all until the first
//! slash or backslash, excluding it. If no directory path is prefixed, a '.'
//! is returned.
		core::stringc ioutils::getFileDir(const core::stringc& filename)
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

		s32 ioutils::isdigit(s32 c)
		{
			return c >= '0' && c <= '9';
		}
		s32 ioutils::isspace(s32 c)
		{
			return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
					|| c == '\v';
		}
		s32 ioutils::isupper(s32 c)
		{
			return c >= 'A' && c <= 'Z';
		}

//! returns true if a character is whitespace
		bool ioutils::isWhiteSpace(c8 c)
		{
			return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
		}

		s32 ioutils::getByteFromHex(c8 h)
		{
			if (h >= '0' && h <= '9')
				return h - '0';

			if (h >= 'a' && h <= 'f')
				return h - 'a' + 10;

			return 0;
		}

		void ioutils::getHexStrFromByte(c8 byte, c8* out)
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
	}  // namespace io
}  // namespace irrgame
