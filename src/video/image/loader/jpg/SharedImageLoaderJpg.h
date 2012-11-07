/*
 * SharedImageLoaderJpg.h
 *
 *  Created on: Nov 7, 2012
 *      Author: gregorytkach
 */

#ifndef SHAREDIMAGELOADERJPG_H_
#define SHAREDIMAGELOADERJPG_H_

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

		class SharedImageLoaderJpg
		{
			public:
				//! Singleton realization
				static SharedImageLoaderJpg& getInstance();

			private:
				//! Default constructor. Should use only one time.
				SharedImageLoaderJpg();

				//! Destructor. Should use only one time.
				virtual ~SharedImageLoaderJpg();

				//! Copy constructor. Do not implement.
				SharedImageLoaderJpg(const SharedImageLoaderJpg& root);

				//! Override equal operator. Do not implement.
				const SharedImageLoaderJpg& operator=(SharedImageLoaderJpg&);

				/*
				 * Methods
				 */
			public:
				//! Returns JPG image
				IImage* createImage(io::IReadFile* file);

		};

	} /* namespace video */
} /* namespace irrgame */
#endif /* SHAREDIMAGELOADERJPG_H_ */
