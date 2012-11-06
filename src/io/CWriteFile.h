// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_WRITE_FILE_H_INCLUDED__
#define __C_WRITE_FILE_H_INCLUDED__

#include <stdio.h>
#include "io/IWriteFile.h"

namespace irrgame
{
	namespace io
	{
		//! Class for writing a real file to disk.
		class CWriteFile: public IWriteFile
		{
			public:

				//! Default constructor
				//! @param fileName;
				//! @param append. If set True - if you want open already exists file and write to the end of file set True.
				//!	If you want open a file with the same name and its content is erased and the file is treated as a new empty file - set False.
				CWriteFile(const core::stringc& fileName, bool append);

				//! Destructor
				virtual ~CWriteFile();

				//! Reads an amount of bytes from the file.
				virtual s32 write(const void* buffer, u32 sizeToWrite);

				//! Changes position in file, returns true if successful.
				virtual bool seek(long finalPos, bool relativeMovement = false);

				//! Returns the current position in the file.
				virtual long getPos() const;

				//! Returns name of file.
				virtual const core::stringc& getFileName() const;

				//! returns if file is open
				bool isOpen() const;

			private:

				//! opens the file
				void openFile(bool append);

			private:
				FILE* File;
				long FileSize;
				core::stringc Filename;

		};

	} // end namespace io
} // end namespace irr

#endif

