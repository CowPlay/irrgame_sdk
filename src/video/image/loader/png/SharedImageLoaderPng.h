/*
 * SharedImageLoaderPng.h
 *
 *  Created on: Nov 8, 2012
 *      Author: gregorytkach
 */

#ifndef SHAREDIMAGELOADERPNG_H_
#define SHAREDIMAGELOADERPNG_H_

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

		class SharedImageLoaderPng
		{
			public:
				//! Singleton realization
				static SharedImageLoaderPng& getInstance();

			private:
				//! Default constructor. Should use only one time.
				SharedImageLoaderPng();

				//! Destructor. Should use only one time.
				virtual ~SharedImageLoaderPng();

				//! Copy constructor. Do not implement.
				SharedImageLoaderPng(const SharedImageLoaderPng& root);

				//! Override equal operator. Do not implement.
				const SharedImageLoaderPng& operator=(SharedImageLoaderPng&);

				/*
				 * Methods
				 */

			public:

				//! Returns PNG image
				IImage* createImage(io::IReadFile* file);
		};

	} /* namespace video */
} /* namespace irrgame */
#endif /* SHAREDIMAGELOADERPNG_H_ */
