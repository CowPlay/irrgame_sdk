// Copyright (C) 2002-2008 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CMemoryFile.h"

namespace irrgame
{
	namespace io
	{

		CMemoryFile::CMemoryFile(void* memory, long len,
				const core::stringc& fileName, bool d) :
				Buffer(memory), Len(len), Pos(0), Filename(fileName), deleteMemoryWhenDropped(
						d)
		{
			IRR_ASSERT(memory != 0);
			IRR_ASSERT(len >= 0);

#ifdef DEBUG
			setDebugName("CMemoryFile");
#endif
		}

		CMemoryFile::~CMemoryFile()
		{
			if (deleteMemoryWhenDropped && Buffer)
				delete[] (c8*) Buffer;
		}

		//! returns how much was read
		s32 CMemoryFile::read(void* buffer, u32 sizeToRead)
		{
			IRR_ASSERT(buffer != 0);

			s32 amount = static_cast<s32>(sizeToRead);
			if (Pos + amount > Len)
				amount -= Pos + amount - Len;

			if (amount <= 0)
				return 0;

			c8* p = (c8*) Buffer;
			memcpy(buffer, p + Pos, amount);

			Pos += amount;

			return amount;
		}

		//! returns how much was written
		s32 CMemoryFile::write(const void* buffer, u32 sizeToWrite)
		{
			s32 amount = static_cast<s32>(sizeToWrite);

			if (Pos + amount > Len)
				amount -= Pos + amount - Len;

			if (amount <= 0)
				return 0;

			c8* p = (c8*) Buffer;
			memcpy(p + Pos, buffer, amount);

			Pos += amount;

			return amount;
		}

		//! changes position in file, returns true if successful
		//! if relativeMovement==true, the pos is changed relative to current pos,
		//! otherwise from begin of file
		bool CMemoryFile::seek(long finalPos, bool relativeMovement)
		{
			if (relativeMovement)
			{
				if (Pos + finalPos > Len)
					return false;

				Pos += finalPos;
			}
			else
			{
				if (finalPos > Len)
					return false;

				Pos = finalPos;
			}

			return true;
		}

		//! returns size of file
		long CMemoryFile::getSize() const
		{
			return Len;
		}

		//! returns where in the file we are.
		long CMemoryFile::getPos() const
		{
			return Pos;
		}

		//! returns name of file
		const core::stringc& CMemoryFile::getFileName() const
		{
			return Filename;
		}

		//! Internal function, please do not use.
		IReadFile* createMemoryReadFile(void* memory, long size,
				const core::stringc& fileName, bool deleteMemoryWhenDropped)
		{
			return new CMemoryFile(memory, size, fileName,
					deleteMemoryWhenDropped);
		}

		//! Internal function, please do not use.
		IWriteFile* createMemoryWriteFile(void* memory, long size,
				const core::stringc& fileName, bool deleteMemoryWhenDropped)
		{
			return new CMemoryFile(memory, size, fileName,
					deleteMemoryWhenDropped);
		}

	} // end namespace io
} // end namespace irr

