/*
 * CImageLoaderBmp.h
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#ifndef CIMAGELOADERBMP_H_
#define CIMAGELOADERBMP_H_

#include "core/engine/IReferenceCounted.h"

namespace irrgame
{
	namespace io
	{
		class IReadFile;
	}  // namespace io

	namespace video
	{

		class IImage;

		/*!
		 Surface Loader for Windows bitmaps
		 */
		class ImageLoaderBmp: public IReferenceCounted
		{
			public:
				//! Default constructor
				ImageLoaderBmp();

				//! Destructor
				virtual ~ImageLoaderBmp();

				//! Returns BMP image
				IImage* createImage(io::IReadFile* file);

			private:

				void decompress8BitRLE(u8*& BmpData, s32 size, s32 width,
						s32 height, s32 pitch) const;

				void decompress4BitRLE(u8*& BmpData, s32 size, s32 width,
						s32 height, s32 pitch) const;
		};

	}
/* namespace video */
} /* namespace irrgame */
#endif /* CIMAGELOADERBMP_H_ */
