/*
 * StaticPpgExtension.h
 *
 *  Created on: Nov 8, 2012
 *      Author: gregorytkach
 */

#ifndef STATICPPGEXTENSION_H_
#define STATICPPGEXTENSION_H_

#include "compileConfig.h"
#include "libpng/png.h"

namespace irrgame
{
	namespace video
	{
		//! Class which contains several static methods used via function pointers by libpng
		class StaticPpgExtension
		{
			public:
				// PNG function for error handling
				static void png_cpexcept_error(png_structp png_ptr,
						png_const_charp msg);

				// PNG function for file reading
				static void PNGAPI user_read_data_fcn(png_structp png_ptr,
						png_bytep data, png_size_t length);

		};

	} /* namespace video */
} /* namespace irrgame */
#endif /* STATICPPGEXTENSION_H_ */
