/*
 * CImageLoaderBmp.h
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#ifndef CIMAGELOADERBMP_H_
#define CIMAGELOADERBMP_H_

#include "compileConfig.h"

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
		class SharedImageLoaderBmp
		{
			public:
				//! Singleton realization
				static SharedImageLoaderBmp& getInstance();

			private:
				//! Default constructor. Should use only one time.
				SharedImageLoaderBmp();

				//! Destructor. Should use only one time.
				virtual ~SharedImageLoaderBmp();

				//! Copy constructor. Do not implement.
				SharedImageLoaderBmp(const SharedImageLoaderBmp& root);

				//! Override equal operator. Do not implement.
				const SharedImageLoaderBmp& operator=(SharedImageLoaderBmp&);

				/*
				 * Methods
				 */

			public:

				//! Returns BMP image
				IImage* createImage(io::IReadFile* file);

			private:

				void decompress8BitRLE(u8*& BmpData, s32 size, s32 width,
						s32 height, s32 pitch) const;

				void decompress4BitRLE(u8*& BmpData, s32 size, s32 width,
						s32 height, s32 pitch) const;
		};

	} /* namespace video */
} /* namespace irrgame */
#endif /* CIMAGELOADERBMP_H_ */
