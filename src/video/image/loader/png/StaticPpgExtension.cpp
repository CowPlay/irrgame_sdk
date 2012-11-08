/*
 * StaticPpgExtension.cpp
 *
 *  Created on: Nov 8, 2012
 *      Author: gregorytkach
 */

#include "StaticPpgExtension.h"

#include "io/IReadFile.h"

namespace irrgame
{
	namespace video
	{
		// PNG function for error handling
		void StaticPpgExtension::png_cpexcept_error(png_structp png_ptr,
				png_const_charp msg)
		{
			//PNG FATAL ERROR"
			longjmp(png_ptr->jmpbuf, 1);
			IRR_ASSERT(false);
		}

		// PNG function for file reading
		void PNGAPI StaticPpgExtension::user_read_data_fcn(png_structp png_ptr,
				png_bytep data, png_size_t length)
		{
			png_size_t check;

			// changed by zola {
			io::IReadFile* file = (io::IReadFile*) png_ptr->io_ptr;
			check = (png_size_t) file->read((void*) data, (u32) length);
			// }

			if (check != length)
			{
				png_error(png_ptr, "Read Error");
			}
		}

	} /* namespace video */
} /* namespace irrgame */
