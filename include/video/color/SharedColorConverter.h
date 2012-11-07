/*
 * IColorConverter.h
 *
 *  Created on: Nov 1, 2012
 *      Author: gregorytkach
 */

#ifndef ICOLORCONVERTER_H_
#define ICOLORCONVERTER_H_

#include "compileConfig.h"
#include "video/color/EColorFormat.h"

namespace irrgame
{
	namespace video
	{
		class SharedColorConverter
		{

			public:
				//! Singleton realization
				static SharedColorConverter& getInstance();

			private:
				//! Default constructor. Should use only one time.
				SharedColorConverter();

				//! Destructor. Should use only one time.
				virtual ~SharedColorConverter();

				//! Copy constructor. Do not implement.
				SharedColorConverter(const SharedColorConverter& root);

				//! Override equal operator. Do not implement.
				const SharedColorConverter& operator=(SharedColorConverter&);

			public:

				//! Creates a 16 bit A1R5G5B5 color
				u16 RGBA16(u32 r, u32 g, u32 b, u32 a = 0xFF);

				//! Creates a 16 bit A1R5G5B5 color
				u16 RGB16(u32 r, u32 g, u32 b);

				//! Creates a 16bit A1R5G5B5 color, based on 16bit input values
				u16 RGB16from16(u16 r, u16 g, u16 b);

				//! Converts a 32bit (X8R8G8B8) color to a 16bit A1R5G5B5 color
				u16 X8R8G8B8toA1R5G5B5(u32 color);

				//! Converts a 32bit (A8R8G8B8) color to a 16bit A1R5G5B5 color
				u16 A8R8G8B8toA1R5G5B5(u32 color);

				//! Converts a 32bit (A8R8G8B8) color to a 16bit R5G6B5 color
				u16 A8R8G8B8toR5G6B5(u32 color);

				//! Convert A8R8G8B8 Color from A1R5G5B5 color
				/** build a nicer 32bit Color by extending dest lower bits with source high bits. */
				u32 A1R5G5B5toA8R8G8B8(u16 color);

				//! Returns A8R8G8B8 Color from R5G6B5 color
				u32 R5G6B5toA8R8G8B8(u16 color);

				//! Returns A1R5G5B5 Color from R5G6B5 color
				u16 R5G6B5toA1R5G5B5(u16 color);

				//! Returns R5G6B5 Color from A1R5G5B5 color
				u16 A1R5G5B5toR5G6B5(u16 color);

				//! converts a monochrome bitmap to A1R5G5B5
				void convert1BitTo16Bit(const u8* in, s16* out, s32 width,
						s32 height, s32 linepad = 0, bool flip = false);

				//! converts a 4 bit palettized image to A1R5G5B5
				void convert4BitTo16Bit(const u8* in, s16* out, s32 width,
						s32 height, const s32* palette, s32 linepad = 0,
						bool flip = false);

				//! converts a 8 bit palettized image to A1R5G5B5
				void convert8BitTo16Bit(const u8* in, s16* out, s32 width,
						s32 height, const s32* palette, s32 linepad = 0,
						bool flip = false);

				//! converts R8G8B8 16 bit data to A1R5G5B5 data
				void convert16BitTo16Bit(const s16* in, s16* out, s32 width,
						s32 height, s32 linepad = 0, bool flip = false);

				//! copies R8G8B8 24 bit data to 24 data, and flips and
				//! mirrors the image during the process.
				void convert24BitTo24Bit(const u8* in, u8* out, s32 width,
						s32 height, s32 linepad = 0, bool flip = false,
						bool bgr = false);

				//! Resizes the surface to a new size and converts it at the same time
				//! to an A8R8G8B8 format, returning the pointer to the new buffer.
				void convert16bitToA8R8G8B8andResize(const s16* in, s32* out,
						s32 newWidth, s32 newHeight, s32 currentWidth,
						s32 currentHeight);

				//! copies X8R8G8B8 32 bit data, and flips and
				//! mirrors the image during the process.
				void convert32BitTo32Bit(const s32* in, s32* out, s32 width,
						s32 height, s32 linepad, bool flip = false);

				//! functions for converting one image format to another efficiently
				//! and hopefully correctly.
				//!
				//! \param sP pointer to source pixel data
				//! \param sN number of source pixels to copy
				//! \param dP pointer to destination data buffer. must be big enough
				//! to hold sN pixels in the output format.
				void convert_A1R5G5B5toR8G8B8(const void* sP, s32 sN, void* dP);
				void convert_A1R5G5B5toB8G8R8(const void* sP, s32 sN, void* dP);
				void convert_A1R5G5B5toA8R8G8B8(const void* sP, s32 sN,
						void* dP);
				void convert_A1R5G5B5toA1R5G5B5(const void* sP, s32 sN,
						void* dP);
				void convert_A1R5G5B5toR5G5B5A1(const void* sP, s32 sN,
						void* dP);
				void convert_A1R5G5B5toR5G6B5(const void* sP, s32 sN, void* dP);

				void convert_A8R8G8B8toR8G8B8(const void* sP, s32 sN, void* dP);
				void convert_A8R8G8B8toB8G8R8(const void* sP, s32 sN, void* dP);
				void convert_A8R8G8B8toA8R8G8B8(const void* sP, s32 sN,
						void* dP);
				void convert_A8R8G8B8toA1R5G5B5(const void* sP, s32 sN,
						void* dP);
				void convert_A8R8G8B8toR5G6B5(const void* sP, s32 sN, void* dP);

				void convert_A8R8G8B8toR3G3B2(const void* sP, s32 sN, void* dP);
				void convert_R8G8B8toR8G8B8(const void* sP, s32 sN, void* dP);
				void convert_R8G8B8toA8R8G8B8(const void* sP, s32 sN, void* dP);
				void convert_R8G8B8toA1R5G5B5(const void* sP, s32 sN, void* dP);
				void convert_R8G8B8toB8G8R8(const void* sP, s32 sN, void* dP);
				void convert_R8G8B8toR5G6B5(const void* sP, s32 sN, void* dP);
				void convert_B8G8R8toA8R8G8B8(const void* sP, s32 sN, void* dP);
				void convert_B8G8R8A8toA8R8G8B8(const void* sP, s32 sN,
						void* dP);
				void convert_A8R8G8B8toR8G8B8A8(const void* sP, s32 sN,
						void* dP);
				void convert_A8R8G8B8toA8B8G8R8(const void* sP, s32 sN,
						void* dP);

				void convert_R5G6B5toR5G6B5(const void* sP, s32 sN, void* dP);
				void convert_R5G6B5toR8G8B8(const void* sP, s32 sN, void* dP);
				void convert_R5G6B5toB8G8R8(const void* sP, s32 sN, void* dP);
				void convert_R5G6B5toA8R8G8B8(const void* sP, s32 sN, void* dP);
				void convert_R5G6B5toA1R5G5B5(const void* sP, s32 sN, void* dP);
				void convert_viaFormat(const void* sP, EColorFormat sF, s32 sN,
						void* dP, EColorFormat dF);
		};
	}  // namespace video
}  // namespace irrgame

#endif /* ICOLORCONVERTER_H_ */
