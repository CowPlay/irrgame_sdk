/*
 * SharedImageLoaderJpg.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: gregorytkach
 */

#include "SharedImageLoaderJpg.h"
#include "StaticJpgExtension.h"
#include "SJpgErrorMgr.h"

#include "io/IReadFile.h"

#include "video/image/IImage.h"

#include <stdio.h> // required for jpeglib.h
#include "libjpeg/jpeglib.h"
#include <setjmp.h>

namespace irrgame
{
	namespace video
	{

		//! Singleton realization
		SharedImageLoaderJpg& SharedImageLoaderJpg::getInstance()
		{
			static SharedImageLoaderJpg instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		SharedImageLoaderJpg::SharedImageLoaderJpg()
		{
		}

		//! Destructor. Should use only one time.
		SharedImageLoaderJpg::~SharedImageLoaderJpg()
		{
		}

		/*
		 * Methods
		 */

		//! Returns JPG image
		IImage* SharedImageLoaderJpg::createImage(io::IReadFile* file)
		{
			IRR_ASSERT(file);

			s32 jfif = 0;
			file->seek(6);
			file->read(&jfif, sizeof(s32));

			bool isJpegFile = jfif == 0x4a464946 || jfif == 0x4649464a;

			IRR_ASSERT(isJpegFile);

			file->seek(0);

			u8 **rowPtr = 0;
			u8* input = new u8[file->getSize()];
			file->read(input, file->getSize());

			// allocate and initialize JPEG decompression object
			struct jpeg_decompress_struct cinfo;

			struct SJpgErrorMgr jerr;

			//We have to set up the error handler first, in case the initialization
			//step fails.  (Unlikely, but it could happen if you are out of memory.)
			//This routine fills in the contents of struct jerr, and returns jerr's
			//address which we place into the link field in cinfo.

			cinfo.err = jpeg_std_error(&jerr.pub);

			cinfo.err->error_exit = StaticJpgExtension::errorExit;
			cinfo.err->output_message = StaticJpgExtension::outputMessage;

			// compatibility fudge:
			// we need to use setjmp/longjmp for error handling as gcc-linux
			// crashes when throwing within external c code
			if (setjmp(jerr.setjmp_buffer))
			{
				// If we get here, the JPEG code has signaled an error.
				// We need to clean up the JPEG object and return.

				jpeg_destroy_decompress(&cinfo);

				delete[] input;

				// if the row pointer was created, we delete it.
				if (rowPtr)
				{
					delete[] rowPtr;
				}

				IRR_ASSERT(false);
			}

			// Now we can initialize the JPEG decompression object.
			jpeg_create_decompress(&cinfo);

			// specify data source
			jpeg_source_mgr jsrc;

			// Set up data pointer
			jsrc.bytes_in_buffer = file->getSize();
			jsrc.next_input_byte = (JOCTET*) input;
			cinfo.src = &jsrc;

			jsrc.init_source = StaticJpgExtension::initSource;
			jsrc.fill_input_buffer = StaticJpgExtension::fillInputBuffer;
			jsrc.skip_input_data = StaticJpgExtension::skipInputData;
			jsrc.resync_to_restart = jpeg_resync_to_restart;
			jsrc.term_source = StaticJpgExtension::termSource;

			// Decodes JPG input from whatever source
			// Does everything AFTER jpeg_create_decompress
			// and BEFORE jpeg_destroy_decompress
			// Caller is responsible for arranging these + setting up cinfo

			// read file parameters with jpeg_read_header()
			jpeg_read_header(&cinfo, TRUE);

			bool useCMYK = false;
			if (cinfo.jpeg_color_space == JCS_CMYK)
			{
				cinfo.out_color_space = JCS_CMYK;
				cinfo.out_color_components = 4;
				useCMYK = true;
			}
			else
			{
				cinfo.out_color_space = JCS_RGB;
				cinfo.out_color_components = 3;
			}
			cinfo.do_fancy_upsampling = FALSE;

			// Start decompressor
			jpeg_start_decompress(&cinfo);

			// Get image data
			u16 rowspan = cinfo.image_width * cinfo.out_color_components;
			u32 width = cinfo.image_width;
			u32 height = cinfo.image_height;

			// Allocate memory for buffer
			u8* output = new u8[rowspan * height];

			// Here we use the library's state variable cinfo.output_scanline as the
			// loop counter, so that we don't have to keep track ourselves.
			// Create array of row pointers for lib
			rowPtr = new u8*[height];

			for (u32 i = 0; i < height; i++)
			{
				rowPtr[i] = &output[i * rowspan];
			}

			u32 rowsRead = 0;

			while (cinfo.output_scanline < cinfo.output_height)
			{
				rowsRead += jpeg_read_scanlines(&cinfo, &rowPtr[rowsRead],
						cinfo.output_height - rowsRead);
			}

			delete[] rowPtr;

			// Finish decompression
			jpeg_finish_decompress(&cinfo);

			// Release JPEG decompression object
			// This is an important step since it will release a good deal of memory.
			jpeg_destroy_decompress(&cinfo);

			// convert image
			IImage* result = 0;
			if (useCMYK)
			{
				result = IImage::createEmptyImage(ECF_R8G8B8,
						dimension2du(width, height));

				const u32 size = 3 * width * height;
				u8* data = (u8*) result->lock();
				if (data)
				{
					for (u32 i = 0, j = 0; i < size; i += 3, j += 4)
					{
						// Also works without K, but has more contrast with K multiplied in
						//				data[i+0] = output[j+2];
						//				data[i+1] = output[j+1];
						//				data[i+2] = output[j+0];
						data[i + 0] = (char) (output[j + 2]
								* (output[j + 3] / 255.f));
						data[i + 1] = (char) (output[j + 1]
								* (output[j + 3] / 255.f));
						data[i + 2] = (char) (output[j + 0]
								* (output[j + 3] / 255.f));
					}
				}
				result->unlock();
				delete[] output;
			}
			else
			{
				result = IImage::createRawImage(ECF_R8G8B8,
						dimension2du(width, height), output);
			}

			delete[] input;

			return result;
		}

	} /* namespace video */
} /* namespace irrgame */
