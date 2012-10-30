// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CReadFile.h"

namespace irrgame
{
	namespace io
	{

		CReadFile::CReadFile(const core::stringc& fileName) :
				File(0), FileSize(0), Filename(fileName)
		{
#ifdef DEBUG
			setDebugName("CReadFile");
#endif
			IRR_ASSERT(sizeof(fileName) > 0);

			openFile();
		}

		CReadFile::~CReadFile()
		{
			if (File)
				fclose(File);
		}

		//! returns how much was read
		s32 CReadFile::read(void* buffer, u32 sizeToRead)
		{
			return (s32) fread(buffer, 1, sizeToRead, File);
		}

		//! changes position in file, returns true if successful
		//! if relativeMovement==true, the pos is changed relative to current pos,
		//! otherwise from begin of file
		bool CReadFile::seek(long finalPos, bool relativeMovement)
		{
			return fseek(File, finalPos, relativeMovement ? SEEK_CUR : SEEK_SET)
					== 0;
		}

		//! returns size of file
		long CReadFile::getSize() const
		{
			return FileSize;
		}

		//! returns if file is open
		bool CReadFile::isOpen() const
		{
			return File != 0;
		}

		//! returns where in the file we are.
		long CReadFile::getPos() const
		{
			return ftell(File);
		}

		//! opens the file for read
		void CReadFile::openFile()
		{
			File = fopen(Filename.cStr(), "rb");

			// could not open file
			IRR_ASSERT(File != 0);

			// get FileSize
			fseek(File, 0, SEEK_END);
			FileSize = getPos();
			fseek(File, 0, SEEK_SET);

		}

		//! returns name of file
		const core::stringc& CReadFile::getFileName() const
		{
			return Filename;
		}

		//! Internal function, please do not use.
		IReadFile* createReadFile(const core::stringc& fileName)
		{
			return new CReadFile(fileName);
		}

	} // end namespace io
} // end namespace irr

