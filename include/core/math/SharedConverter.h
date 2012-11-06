// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine" and the "irrXML" project.
// For conditions of distribution and use, see copyright notice in irrlicht.h and irrXML.h

#ifndef __FAST_A_TO_F_H_INCLUDED__
#define __FAST_A_TO_F_H_INCLUDED__

#include "core/math/SharedMath.h"

namespace irrgame
{
	namespace core
	{
		class SharedConverter
		{

			public:
				//! Singleton realization
				static SharedConverter& getInstance();

			private:
				//! Default constructor. Should use only one time.
				SharedConverter();

				//! Destructor. Should use only one time.
				virtual ~SharedConverter();

				//! Copy constructor. Do not implement.
				SharedConverter(const SharedConverter& root);

				//! Override equal operator. Do not implement.
				const SharedConverter& operator=(SharedConverter&);

				//! \param[in] in: The string to convert.
				//! \param[out] out: The resultant float will be written here.
				//! \return

				/*
				 * Methods
				 */
			public:
				//! Provides a fast function for converting a string into a float.
				//! This is not guaranteed to be as accurate as atof(), but is
				//! approximately 6 to 8 times as fast.
				//! \param floatAsString: The string to convert.
				//! \param moveStringCursor: If True input string will be a pointer to the first character in the string that wasn't
				//!         use to create the float value.
				//! \return The resultant float.
				f32 convertToFloat(const c8* value, bool moveStringCursor =
						false) const;

				//! Floating-point representation of an integer value.
				f32 convertToFloat(u32 x) const;

				//! Floating-point representation of an integer value.
				f32 convertToFloat(s32 x) const;

				//! code is taken from IceFPU
				//! Integer representation of a floating-point value.
				u32 convertToUInt(f32 x) const;

			private:
				const c8* move(const c8* in, f32& out) const;

				//! Convert a simple string of base 10 digits into a signed 32 bit integer.
				//! \param[in] in: The string of digits to convert. Only a leading - or + followed
				//!					by digits 0 to 9 will be considered.  Parsing stops at the
				//!					first non-digit.
				//! \param[out] out: (optional) If provided, it will be set to point at the first
				//!					 character not used in the calculation.
				//! \return The signed integer value of the digits. If the string specifies too many
				//!			digits to encode in an s32 then +INT_MAX or -INT_MAX will be returned.
				s32 strtol10(const c8* in, const c8** out = 0) const;

				//! Converts a sequence of digits into a whole positive floating point value.
				//! Only digits 0 to 9 are parsed.  Parsing stops at any other character,
				//! including sign characters or a decimal point.
				//! \param in: the sequence of digits to convert.
				//! \param out: (optional) will be set to point at the first non-converted character.
				//! \return The whole positive floating point representation of the digit sequence.
				f32 strtof10(const c8* in, const c8** out = 0) const;

			private:
				// we write [17] here instead of [] to work around a swig bug
				f32 atofTable[17];

		};

	} // end namespace core
} // end namespace irr

#endif

