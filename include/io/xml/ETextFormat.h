/*
 * ETextFormat.h
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#ifndef ETEXTFORMAT_H_
#define ETEXTFORMAT_H_

namespace irrgame
{
	namespace io
	{
		//! Enumeration of all supported source text file formats
		enum ETextFormat
		{
			//! ASCII, file without byte order mark, or not a text file
			ETF_ASCII,

			//! UTF-8 format
			ETF_UTF8,

			//! UTF-16 format, big endian
			ETF_UTF16_BE,

			//! UTF-16 format, little endian
			ETF_UTF16_LE,

			//! UTF-32 format, big endian
			ETF_UTF32_BE,

			//! UTF-32 format, little endian
			ETF_UTF32_LE,

			//! Not used
			ETF_COUNT
		};
	}  // namespace io
}  // namespace irrgame

#endif /* ETEXTFORMAT_H_ */
