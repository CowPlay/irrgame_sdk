/*
 * SharedJpgExtension.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: gregorytkach
 */

#include "SharedJpgExtension.h"
#include "vendors/jpeglib/jpeglib.h"

namespace irrgame
{
	namespace video
	{

		//! Singleton realization
		SharedJpgExtension& SharedJpgExtension::getInstance()
		{
			static SharedJpgExtension instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		SharedJpgExtension::SharedJpgExtension()
		{
		}

		//! Destructor. Should use only one time.
		SharedJpgExtension::~SharedJpgExtension()
		{
		}

		/*
		 * Methods
		 */

		void SharedJpgExtension::initSource(j_decompress_ptr cinfo)
		{
			// DO NOTHING
		}

		boolean SharedJpgExtension::fillInputBuffer(j_decompress_ptr cinfo)
		{
			// DO NOTHING
			return 1;
		}

		void SharedJpgExtension::skipInputData(j_decompress_ptr cinfo,
				long count)
		{
			jpeg_source_mgr * src = cinfo->src;
			if (count > 0)
			{
				src->bytes_in_buffer -= count;
				src->next_input_byte += count;
			}
		}

		void SharedJpgExtension::termSource(j_decompress_ptr cinfo)
		{
			// DO NOTHING
		}

		void SharedJpgExtension::errorExit(j_common_ptr cinfo)
		{
			// unfortunately we need to use a goto rather than throwing an exception
			// as gcc crashes under linux crashes when using throw from within
			// extern c code

			// Always display the message
			(*cinfo->err->output_message)(cinfo);

			// cinfo->err really points to a irr_error_mgr struct
			irr_jpeg_error_mgr *myerr = (irr_jpeg_error_mgr*) cinfo->err;

			longjmp(myerr->setjmp_buffer, 1);
		}

		void SharedJpgExtension::outputMessage(j_common_ptr cinfo)
		{
			// display the error message.
			c8 temp1[JMSG_LENGTH_MAX];
			(*cinfo->err->format_message)(cinfo, temp1);
			IRR_ASSERT(false);
			// JPEG Fatal error
		}
	//#endif // _IRR_COMPILE_WITH_LIBJPEG_
	////! returns true if the file maybe is able to be loaded by this class
	//		bool CImageLoaderJPG::isALoadableFileFormat(io::IReadFile* file) const
	//		{
	//#ifndef _IRR_COMPILE_WITH_LIBJPEG_
	//			return false;
	//#else
	//
	//			if (!file)
	//			return false;
	//
	//			s32 jfif = 0;
	//			file->seek(6);
	//			file->read(&jfif, sizeof(s32));
	//			return (jfif == 0x4a464946 || jfif == 0x4649464a);
	//
	//#endif
	//		}
	} /* namespace video */
} /* namespace irrgame */
