/*
 * SharedImageLoaderPng.cpp
 *
 *  Created on: Nov 8, 2012
 *      Author: gregorytkach
 */

#include "SharedImageLoaderPng.h"
#include "StaticPpgExtension.h"
#include "video/image/IImage.h"
#include "io/IReadFile.h"
#include "libpng/png.h"

namespace irrgame
{
	namespace video
	{

		//! Singleton realization
		SharedImageLoaderPng& SharedImageLoaderPng::getInstance()
		{
			static SharedImageLoaderPng instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		SharedImageLoaderPng::SharedImageLoaderPng()
		{
		}

		//! Destructor. Should use only one time.
		SharedImageLoaderPng::~SharedImageLoaderPng()
		{
		}

		/*
		 * Methods
		 */
		//! Returns PNG image
		IImage* SharedImageLoaderPng::createImage(io::IReadFile* file)
		{
			IRR_ASSERT(file);

			video::IImage* result = 0;

			//Used to point to image rows
			u8** RowPointers = 0;

			png_byte buffer[8];
			// Read the first few bytes of the PNG file
			IRR_ASSERT(file->read(buffer, 8) == 8);

			// Check if it really is a PNG file
			IRR_ASSERT(!png_sig_cmp(buffer, 0, 8));

			// Allocate the png read struct
			png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
					NULL,
					(png_error_ptr) StaticPpgExtension::png_cpexcept_error,
					NULL);

			// Internal PNG create read struct failure
			IRR_ASSERT(png_ptr);

			// Allocate the png info struct
			png_infop info_ptr = png_create_info_struct(png_ptr);

			//Internal PNG create info struct failure
			IRR_ASSERT(info_ptr);

			// for proper error handling
			IRR_ASSERT(!setjmp(png_jmpbuf(png_ptr)));

			// changed by zola so we don't need to have public FILE pointers
			png_set_read_fn(png_ptr, file,
					StaticPpgExtension::user_read_data_fcn);

			png_set_sig_bytes(png_ptr, 8); // Tell png that we read the signature

			png_read_info(png_ptr, info_ptr); // Read the info section of the png file

			u32 Width;
			u32 Height;
			s32 BitDepth;
			s32 ColorType;
			{
				// Use temporary variables to avoid passing casted pointers
				png_uint_32 w, h;
				// Extract info
				png_get_IHDR(png_ptr, info_ptr, &w, &h, &BitDepth, &ColorType,
						NULL, NULL, NULL);
				Width = w;
				Height = h;
			}

			// Convert palette color to true color
			if (ColorType == PNG_COLOR_TYPE_PALETTE)
			{
				png_set_palette_to_rgb(png_ptr);
			}

			// Convert low bit colors to 8 bit colors
			if (BitDepth < 8)
			{
				if (ColorType == PNG_COLOR_TYPE_GRAY
						|| ColorType == PNG_COLOR_TYPE_GRAY_ALPHA)
				{
					png_set_gray_1_2_4_to_8(png_ptr);
				}
				else
				{
					png_set_packing(png_ptr);
				}
			}

			if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
			{
				png_set_tRNS_to_alpha(png_ptr);
			}

			// Convert high bit colors to 8 bit colors
			if (BitDepth == 16)
			{
				png_set_strip_16(png_ptr);
			}

			// Convert gray color to true color
			if (ColorType == PNG_COLOR_TYPE_GRAY
					|| ColorType == PNG_COLOR_TYPE_GRAY_ALPHA)
			{
				png_set_gray_to_rgb(png_ptr);
			}

			// Update the changes
			png_read_update_info(png_ptr, info_ptr);
			{
				// Use temporary variables to avoid passing casted pointers
				png_uint_32 w, h;
				// Extract info
				png_get_IHDR(png_ptr, info_ptr, &w, &h, &BitDepth, &ColorType,
						NULL, NULL, NULL);
				Width = w;
				Height = h;
			}

			// Convert RGBA to BGRA
			if (ColorType == PNG_COLOR_TYPE_RGB_ALPHA)
			{
				png_set_bgr(png_ptr);
			}

			// Update the changes
			{
				// Use temporary variables to avoid passing casted pointers
				png_uint_32 w, h;
				// Extract info
				png_get_IHDR(png_ptr, info_ptr, &w, &h, &BitDepth, &ColorType,
						NULL, NULL, NULL);
				Width = w;
				Height = h;
			}

			// Create the image structure to be filled by png data
			if (ColorType == PNG_COLOR_TYPE_RGB_ALPHA)
			{
				result = IImage::createEmptyImage(ECF_A8R8G8B8,
						dimension2du(Width, Height));
			}
			else
			{
				result = IImage::createEmptyImage(ECF_R8G8B8,
						dimension2du(Width, Height));
			}

			//Internal PNG create image struct failure
			IRR_ASSERT(result);

			// Create array of pointers to rows in image data
			RowPointers = new png_bytep[Height];

			//Internal PNG create row pointers failure
			IRR_ASSERT(RowPointers);

			// Fill array of pointers to rows in image data
			unsigned char* data = (unsigned char*) result->lock();
			for (u32 i = 0; i < Height; ++i)
			{
				RowPointers[i] = data;
				data += result->getPitch();
			}

			// for proper error handling
			IRR_ASSERT(!setjmp(png_jmpbuf(png_ptr)));

			// Read data using the library function that handles all transformations including interlacing
			png_read_image(png_ptr, RowPointers);

			png_read_end(png_ptr, NULL);
			delete[] RowPointers;
			result->unlock();
			png_destroy_read_struct(&png_ptr, &info_ptr, 0); // Clean up memory

			return result;
		}

	} /* namespace video */
} /* namespace irrgame */
