/*
 * SharedJpgExtension.h
 *
 *  Created on: Nov 7, 2012
 *      Author: gregorytkach
 */

#include "compileConfig.h"
#include "stdio.h" // required for JPEG lib
#include "libjpeg/jpeglib.h"
#include <setjmp.h>

#ifndef SHAREDJPGEXTENSION_H_
#define SHAREDJPGEXTENSION_H_

namespace irrgame
{
	namespace video
	{

		//! Class which contains several static methods used via function pointers by libjpeg
		class StaticJpgExtension
		{

				/*
				 * Methods
				 */
			public:

				/* 	Receives control for a fatal error.  Information sufficient to
				 generate the error message has been stored in cinfo->err; call
				 output_message to display it.  Control must NOT return to the caller;
				 generally this routine will exit() or longjmp() somewhere.
				 Typically you would override this routine to get rid of the exit()
				 default behavior.  Note that if you continue processing, you should
				 clean up the JPEG object with jpeg_abort() or jpeg_destroy().
				 */
				static void errorExit(j_common_ptr cinfo);

				/* output error messages via Irrlicht logger. */
				static void outputMessage(j_common_ptr cinfo);

				/*	Initialize source.  This is called by jpeg_read_header() before any
				 data is actually read.  Unlike init_destination(), it may leave
				 bytes_in_buffer set to 0 (in which case a fill_input_buffer() call
				 will occur immediately). */
				static void initSource(j_decompress_ptr cinfo);

				/*	This is called whenever bytes_in_buffer has reached zero and more
				 data is wanted.  In typical applications, it should read fresh data
				 into the buffer (ignoring the current state of next_input_byte and
				 bytes_in_buffer), reset the pointer & count to the start of the
				 buffer, and return TRUE indicating that the buffer has been reloaded.
				 It is not necessary to fill the buffer entirely, only to obtain at
				 least one more byte.  bytes_in_buffer MUST be set to a positive value
				 if TRUE is returned.  A FALSE return should only be used when I/O
				 suspension is desired (this mode is discussed in the next section). */
				static boolean fillInputBuffer(j_decompress_ptr cinfo);

				/* Skip num_bytes worth of data.  The buffer pointer and count should
				 be advanced over num_bytes input bytes, refilling the buffer as
				 needed.  This is used to skip over a potentially large amount of
				 uninteresting data (such as an APPn marker).  In some applications
				 it may be possible to optimize away the reading of the skipped data,
				 but it's not clear that being smart is worth much trouble; large
				 skips are uncommon.  bytes_in_buffer may be zero on return.
				 A zero or negative skip count should be treated as a no-op. */
				static void skipInputData(j_decompress_ptr cinfo,
						long num_bytes);

				/* Terminate source --- called by jpeg_finish_decompress() after all
				 data has been read.  Often a no-op. */
				static void termSource(j_decompress_ptr cinfo);
		};

	} /* namespace video */
} /* namespace irrgame */
#endif /* SHAREDJPGEXTENSION_H_ */
