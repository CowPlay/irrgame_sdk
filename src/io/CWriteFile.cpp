// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CWriteFile.h"

namespace irrgame
{
	namespace io
	{
		int foo()
		{
			int i = 0;
			return i;
		}

		CWriteFile::CWriteFile(const core::stringc& fileName, bool append) :
				File(0), FileSize(0), Filename(fileName)
		{
#ifdef DEBUG
			setDebugName("CWriteFile");
#endif
			IRR_ASSERT(sizeof(fileName) > 0);

			foo();
			openFile(append);
		}

		CWriteFile::~CWriteFile()
		{
			if (File)
				fclose(File);
		}

		//! returns how much was read
		s32 CWriteFile::write(const void* buffer, u32 sizeToWrite)
		{
			return (s32) fwrite(buffer, 1, sizeToWrite, File);
		}

		//! changes position in file, returns true if successful
		//! if relativeMovement==true, the pos is changed relative to current pos,
		//! otherwise from begin of file
		bool CWriteFile::seek(long finalPos, bool relativeMovement)
		{
			return fseek(File, finalPos, relativeMovement ? SEEK_CUR : SEEK_SET)
					== 0;
		}

		//! returns where in the file we are.
		long CWriteFile::getPos() const
		{
			return ftell(File);
		}

		//! opens the file
		void CWriteFile::openFile(bool append)
		{
			File = fopen(Filename.cStr(), append ? "ab" : "wb");

			IRR_ASSERT(File != 0);

			// get FileSize
			fseek(File, 0, SEEK_END);
			FileSize = ftell(File);
			fseek(File, 0, SEEK_SET);
		}

		//! returns name of file
		const core::stringc& CWriteFile::getFileName() const
		{
			return Filename;
		}

		//! Internal function, please do not use.
		IWriteFile* createWriteFile(const core::stringc& fileName, bool append)
		{
			return new CWriteFile(fileName, append);
		}

	} // end namespace io
} // end namespace irr

