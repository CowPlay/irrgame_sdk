// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_READ_FILE_H_INCLUDED__
#define __C_READ_FILE_H_INCLUDED__

#include <stdio.h>
#include "io/IReadFile.h"

namespace irrgame
{

	namespace io
	{

		/*!
		 Class for reading a real file from disk.
		 */
		class CReadFile: public IReadFile
		{
			public:

				CReadFile(const core::stringc& fileName);

				virtual ~CReadFile();

				//! returns how much was read
				virtual s32 read(void* buffer, u32 sizeToRead);

				//! changes position in file, returns true if successful
				virtual bool seek(long finalPos, bool relativeMovement = false);

				//! returns size of file
				virtual long getSize() const;

				//! returns if file is open
				virtual bool isOpen() const;

				//! returns where in the file we are.
				virtual long getPos() const;

				//! returns name of file
				virtual const core::stringc& getFileName() const;

			private:

				//! opens the file
				void openFile();

			private:
				FILE* File;
				long FileSize;
				core::stringc Filename;
		};

	} // end namespace io
} // end namespace irr

#endif

