/*
 * EFileArchiveType.h
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#ifndef EFILEARCHIVETYPE_H_
#define EFILEARCHIVETYPE_H_

#include "compileConfig.h"

namespace irrgame
{
	namespace io
	{
		//! Contains the different types of archives
		enum E_FILE_ARCHIVE_TYPE
		{
			//! A PKZIP archive
			EFAT_ZIP = MAKE_IRR_ID('Z', 'I', 'P', 0),

			//! A gzip archive
			EFAT_GZIP = MAKE_IRR_ID('g', 'z', 'i', 'p'),

			//! A virtual directory
			EFAT_FOLDER = MAKE_IRR_ID('f', 'l', 'd', 'r'),

			//! An ID Software PAK archive
			EFAT_PAK = MAKE_IRR_ID('P', 'A', 'K', 0),

			//! A Nebula Device archive
			EFAT_NPK = MAKE_IRR_ID('N', 'P', 'K', 0),

			//! A Tape ARchive
			EFAT_TAR = MAKE_IRR_ID('T', 'A', 'R', 0),

			//! The type of this archive is unknown
			EFAT_UNKNOWN = MAKE_IRR_ID('u', 'n', 'k', 'n')
		};
	}  // namespace io

}  // namespace irrgame

#endif /* EFILEARCHIVETYPE_H_ */
