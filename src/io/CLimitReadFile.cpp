// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CLimitReadFile.h"
#include "core/math/SharedMath.h"

namespace irrgame
{
	namespace io
	{

		CLimitReadFile::CLimitReadFile(IReadFile* alreadyOpenedFile, long pos,
				long areaSize, const core::stringc& name) :
				Filename(name), AreaStart(pos), AreaEnd(AreaStart + areaSize), Pos(
						0), File(alreadyOpenedFile)
		{
			IRR_ASSERT(alreadyOpenedFile != 0);
			IRR_ASSERT((AreaStart + AreaEnd) < alreadyOpenedFile->getSize());

#ifdef DEBUG
			setDebugName("CLimitReadFile");
#endif
			File->grab();
		}

		CLimitReadFile::~CLimitReadFile()
		{
			if (File)
				File->drop();
		}

		//! returns how much was read
		s32 CLimitReadFile::read(void* buffer, u32 sizeToRead)
		{
			if (0 == File)
				return 0;

			s32 r = AreaStart + Pos;
			s32 toRead = core::SharedMath::getInstance().s32Min(AreaEnd,
					r + sizeToRead)
					- core::SharedMath::getInstance().s32Max(AreaStart, r);
			if (toRead < 0)
				return 0;
			File->seek(r);
			r = File->read(buffer, toRead);
			Pos += r;
			return r;
		}

		//! changes position in file, returns true if successful
		bool CLimitReadFile::seek(long finalPos, bool relativeMovement)
		{
			Pos = core::SharedMath::getInstance().s32Clamp(
					finalPos + (relativeMovement ? Pos : 0), 0,
					AreaEnd - AreaStart);
			return true;
		}

		//! returns size of file
		long CLimitReadFile::getSize() const
		{
			return AreaEnd - AreaStart;
		}

		//! returns where in the file we are.
		long CLimitReadFile::getPos() const
		{
			return Pos;
		}

		//! returns name of file
		const core::stringc& CLimitReadFile::getFileName() const
		{
			return Filename;
		}

		IReadFile* createLimitReadFile(const core::stringc& fileName,
				IReadFile* alreadyOpenedFile, long pos, long areaSize)
		{
			return new CLimitReadFile(alreadyOpenedFile, pos, areaSize,
					fileName);
		}

	} // end namespace io
} // end namespace irr

