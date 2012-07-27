// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine" and the "irrXML" project.
// For conditions of distribution and use, see copyright notice in irrlicht.h and/or irrXML.h

#include "./io/irrXML.h"
#include "./core/irrString.h"
#include "./core/irrArray.h"
#include "./core/fast_atof.h"
#include "CXMLReaderImpl.h"

namespace irrgame
{
	namespace io
	{

		//! Implementation of the file read callback for ordinary files
		class CFileReadCallBack: public IFileReadCallBack
		{
			public:

				//! construct from filename
				CFileReadCallBack(const char* filename) :
						File(0), Size(-1), Close(true)
				{
					// open file
					File = fopen(filename, "rb");

					if (File)
						getFileSize();
				}

				//! construct from FILE pointer
				CFileReadCallBack(FILE* file) :
						File(file), Size(-1), Close(false)
				{
					if (File)
						getFileSize();
				}

				//! destructor
				virtual ~CFileReadCallBack()
				{
					if (Close && File)
						fclose(File);
				}

				//! Reads an amount of bytes from the file.
				virtual int read(void* buffer, int sizeToRead)
				{
					if (!File)
						return 0;

					return (int) fread(buffer, 1, sizeToRead, File);
				}

				//! Returns size of file in bytes
				virtual long getSize() const
				{
					return Size;
				}

			private:

				//! retrieves the file size of the open file
				void getFileSize()
				{
					fseek(File, 0, SEEK_END);
					Size = ftell(File);
					fseek(File, 0, SEEK_SET);
				}

				FILE* File;
				long Size;
				bool Close;

		};
		// end class CFileReadCallBack

		// FACTORY FUNCTIONS:

		//! Creates an instance of an UFT-8 or ASCII character xml parser.
		IrrXMLReader* createIrrXMLReader(const char* filename)
		{
			return createIrrXMLReader(new CFileReadCallBack(filename), true);
		}

		//! Creates an instance of an UFT-8 or ASCII character xml parser.
		IrrXMLReader* createIrrXMLReader(FILE* file)
		{
			return createIrrXMLReader(new CFileReadCallBack(file), true);
		}

		//! Creates an instance of an UFT-8 or ASCII character xml parser.
		IrrXMLReader* createIrrXMLReader(IFileReadCallBack* callback,
				bool deleteCallback)
		{
			if (callback && (callback->getSize() >= 0))
			{
				return new CXMLReaderImpl<char, IXMLBase>(callback,
						deleteCallback);
			}
			else
			{
				if (callback && deleteCallback)
					delete callback;

				return 0;
			}
		}

		//! Creates an instance of an UTF-16 xml parser.
		IrrXMLReaderUTF16* createIrrXMLReaderUTF16(const char* filename)
		{
			return createIrrXMLReaderUTF16(new CFileReadCallBack(filename),
					true);
		}

		//! Creates an instance of an UTF-16 xml parser.
		IrrXMLReaderUTF16* createIrrXMLReaderUTF16(FILE* file)
		{
			return createIrrXMLReaderUTF16(new CFileReadCallBack(file), true);
		}

		//! Creates an instance of an UTF-16 xml parser.
		IrrXMLReaderUTF16* createIrrXMLReaderUTF16(IFileReadCallBack* callback,
				bool deleteCallback)
		{
			if (callback && (callback->getSize() >= 0))
			{
				return new CXMLReaderImpl<char16, IXMLBase>(callback,
						deleteCallback);
			}
			else
			{
				if (callback && deleteCallback)
					delete callback;

				return 0;
			}
		}

		//! Creates an instance of an UTF-32 xml parser.
		IrrXMLReaderUTF32* createIrrXMLReaderUTF32(const char* filename)
		{
			return createIrrXMLReaderUTF32(new CFileReadCallBack(filename),
					true);
		}

		//! Creates an instance of an UTF-32 xml parser.
		IrrXMLReaderUTF32* createIrrXMLReaderUTF32(FILE* file)
		{
			return createIrrXMLReaderUTF32(new CFileReadCallBack(file), true);
		}

		//! Creates an instance of an UTF-32 xml parser.
		IrrXMLReaderUTF32* createIrrXMLReaderUTF32(IFileReadCallBack* callback,
				bool deleteCallback)
		{
			if (callback && (callback->getSize() >= 0))
			{
				return new CXMLReaderImpl<char32, IXMLBase>(callback,
						deleteCallback);
			}
			else
			{
				if (callback && deleteCallback)
					delete callback;

				return 0;
			}
		}

	}
// end namespace io
}// end namespace irr
