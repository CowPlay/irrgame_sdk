/*
 * SharedJpgExtension.cpp
 *
 *  Created on: Nov 7, 2012
 *      Author: gregorytkach
 */

#include "StaticJpgExtension.h"
#include "SJpgErrorMgr.h"

namespace irrgame
{
	namespace video
	{

		void StaticJpgExtension::initSource(j_decompress_ptr cinfo)
		{
			// DO NOTHING
		}

		boolean StaticJpgExtension::fillInputBuffer(j_decompress_ptr cinfo)
		{
			// DO NOTHING
			return true;
		}

		void StaticJpgExtension::skipInputData(j_decompress_ptr cinfo,
				long count)
		{
			jpeg_source_mgr * src = cinfo->src;
			if (count > 0)
			{
				src->bytes_in_buffer -= count;
				src->next_input_byte += count;
			}
		}

		void StaticJpgExtension::termSource(j_decompress_ptr cinfo)
		{
			// DO NOTHING
		}

		void StaticJpgExtension::errorExit(j_common_ptr cinfo)
		{
			// unfortunately we need to use a goto rather than throwing an exception
			// as gcc crashes under linux crashes when using throw from within
			// extern c code

			// Always display the message
			(*cinfo->err->output_message)(cinfo);

			// cinfo->err really points to a irr_error_mgr struct
			SJpgErrorMgr *myerr = (SJpgErrorMgr*) cinfo->err;

			longjmp(myerr->setjmp_buffer, 1);

			IRR_ASSERT(false);
		}

		void StaticJpgExtension::outputMessage(j_common_ptr cinfo)
		{
			// display the error message.
			c8 temp1[JMSG_LENGTH_MAX];
			(*cinfo->err->format_message)(cinfo, temp1);

			// JPEG Fatal error
			IRR_ASSERT(false);
		}
	} /* namespace video */
} /* namespace irrgame */
