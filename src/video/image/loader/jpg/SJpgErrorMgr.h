/*
 * SJpgErrorMgr.h
 *
 *  Created on: Nov 8, 2012
 *      Author: gregorytkach
 */

#ifndef SJPGERRORMGR_H_
#define SJPGERRORMGR_H_

#include "stdio.h" // required for JPEG lib
#include "libjpeg/jpeglib.h"

namespace irrgame
{
	namespace video
	{
		// struct for handling jpeg errors
		struct SJpgErrorMgr
		{
			public:
				// public jpeg error fields
				struct jpeg_error_mgr pub;

				// for longjmp, to return to caller on a fatal error
				jmp_buf setjmp_buffer;
		};

	}  // namespace video
}  // namespace irrgame

#endif /* SJPGERRORMGR_H_ */
