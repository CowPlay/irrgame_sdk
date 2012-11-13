// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "video/color/SharedColorConverter.h"
#include "video/color.h"
#include "utils/StaticByteSwap.h"
#include "video/utils/SharedVideoUtils.h"
#include "string.h"

namespace irrgame
{
	namespace video
	{
		//! Singleton realization
		SharedColorConverter& SharedColorConverter::getInstance()
		{
			static SharedColorConverter instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		SharedColorConverter::SharedColorConverter()
		{
		}

		//! Destructor. Should use only one time.
		SharedColorConverter::~SharedColorConverter()
		{
		}

		//! Creates a 16 bit A1R5G5B5 color
		u16 SharedColorConverter::RGBA16(u32 r, u32 g, u32 b, u32 a)
		{
			return (u16) ((a & 0x80) << 8 | (r & 0xF8) << 7 | (g & 0xF8) << 2
					| (b & 0xF8) >> 3);
		}

		//! Creates a 16 bit A1R5G5B5 color
		u16 SharedColorConverter::RGB16(u32 r, u32 g, u32 b)
		{
			return RGBA16(r, g, b);
		}

		//! Creates a 16bit A1R5G5B5 color, based on 16bit input values
		u16 SharedColorConverter::RGB16from16(u16 r, u16 g, u16 b)
		{
			return (0x8000 | (r & 0x1F) << 10 | (g & 0x1F) << 5 | (b & 0x1F));
		}

		//! Converts a 32bit (X8R8G8B8) color to a 16bit A1R5G5B5 color
		u16 SharedColorConverter::X8R8G8B8toA1R5G5B5(u32 color)
		{
			return (u16) (0x8000 | (color & 0x00F80000) >> 9
					| (color & 0x0000F800) >> 6 | (color & 0x000000F8) >> 3);
		}

		//! Converts a 32bit (A8R8G8B8) color to a 16bit A1R5G5B5 color
		u16 SharedColorConverter::A8R8G8B8toA1R5G5B5(u32 color)
		{
			return (u16) ((color & 0x80000000) >> 16 | (color & 0x00F80000) >> 9
					| (color & 0x0000F800) >> 6 | (color & 0x000000F8) >> 3);
		}

		//! Converts a 32bit (A8R8G8B8) color to a 16bit R5G6B5 color
		u16 SharedColorConverter::A8R8G8B8toR5G6B5(u32 color)
		{
			return (u16) ((color & 0x00F80000) >> 8 | (color & 0x0000FC00) >> 5
					| (color & 0x000000F8) >> 3);
		}

		//! Convert A8R8G8B8 Color from A1R5G5B5 color
		/** build a nicer 32bit Color by extending dest lower bits with source high bits. */
		u32 SharedColorConverter::A1R5G5B5toA8R8G8B8(u16 color)
		{
			return (((-((s32) color & 0x00008000) >> (s32) 31) & 0xFF000000)
					| ((color & 0x00007C00) << 9) | ((color & 0x00007000) << 4)
					| ((color & 0x000003E0) << 6) | ((color & 0x00000380) << 1)
					| ((color & 0x0000001F) << 3) | ((color & 0x0000001C) >> 2));
		}

		//! Returns A8R8G8B8 Color from R5G6B5 color
		u32 SharedColorConverter::R5G6B5toA8R8G8B8(u16 color)
		{
			return 0xFF000000 | ((color & 0xF800) << 8)
					| ((color & 0x07E0) << 5) | ((color & 0x001F) << 3);
		}

		//! Returns A1R5G5B5 Color from R5G6B5 color
		u16 SharedColorConverter::R5G6B5toA1R5G5B5(u16 color)
		{
			return 0x8000 | (((color & 0xFFC0) >> 1) | (color & 0x1F));
		}

		//! Returns R5G6B5 Color from A1R5G5B5 color
		u16 SharedColorConverter::A1R5G5B5toR5G6B5(u16 color)
		{
			return (((color & 0x7FE0) << 1) | (color & 0x1F));
		}

		//! converts a monochrome bitmap to A1R5G5B5 data
		void SharedColorConverter::convert1BitTo16Bit(const u8* in, s16* out,
				s32 width, s32 height, s32 linepad, bool flip)
		{
			if (!in || !out)
				return;

			if (flip)
				out += width * height;

			for (s32 y = 0; y < height; ++y)
			{
				s32 shift = 7;
				if (flip)
					out -= width;

				for (s32 x = 0; x < width; ++x)
				{
					out[x] = *in >> shift & 0x01 ? (s16) 0xffff : (s16) 0x8000;

					if ((--shift) < 0) // 8 pixel done
					{
						shift = 7;
						++in;
					}
				}

				if (shift != 7) // width did not fill last byte
					++in;

				if (!flip)
					out += width;
				in += linepad;
			}
		}

		//! converts a 4 bit palettized image to A1R5G5B5
		void SharedColorConverter::convert4BitTo16Bit(const u8* in, s16* out,
				s32 width, s32 height, const s32* palette, s32 linepad,
				bool flip)
		{
			if (!in || !out || !palette)
				return;

			if (flip)
				out += width * height;

			for (s32 y = 0; y < height; ++y)
			{
				s32 shift = 4;
				if (flip)
					out -= width;

				for (s32 x = 0; x < width; ++x)
				{
					out[x] = X8R8G8B8toA1R5G5B5(
							palette[(u8) ((*in >> shift) & 0xf)]);

					if (shift == 0)
					{
						shift = 4;
						++in;
					}
					else
						shift = 0;
				}

				if (shift == 0) // odd width
					++in;

				if (!flip)
					out += width;
				in += linepad;
			}
		}

		//! converts a 8 bit palettized image into A1R5G5B5
		void SharedColorConverter::convert8BitTo16Bit(const u8* in, s16* out,
				s32 width, s32 height, const s32* palette, s32 linepad,
				bool flip)
		{
			if (!in || !out || !palette)
				return;

			if (flip)
				out += width * height;

			for (s32 y = 0; y < height; ++y)
			{
				if (flip)
					out -= width; // one line back
				for (s32 x = 0; x < width; ++x)
				{
					out[x] = X8R8G8B8toA1R5G5B5(palette[(u8) (*in)]);
					++in;
				}
				if (!flip)
					out += width;
				in += linepad;
			}
		}

		//! converts 16bit data to 16bit data
		void SharedColorConverter::convert16BitTo16Bit(const s16* in, s16* out,
				s32 width, s32 height, s32 linepad, bool flip)
		{
			if (!in || !out)
				return;

			if (flip)
			{
				out += width * height;
			}

			for (s32 y = 0; y < height; ++y)
			{
				if (flip)
					out -= width;
				memcpy(out, in, width * sizeof(s16));

				if (!flip)
				{
					out += width;
				}

				in += width;
				in += linepad;
			}
		}

		//! copies R8G8B8 24bit data to 24bit data
		void SharedColorConverter::convert24BitTo24Bit(const u8* in, u8* out,
				s32 width, s32 height, s32 linepad, bool flip, bool bgr)
		{
			if (!in || !out)
				return;

			const s32 lineWidth = 3 * width;
			if (flip)
				out += lineWidth * height;

			for (s32 y = 0; y < height; ++y)
			{
				if (flip)
					out -= lineWidth;
				if (bgr)
				{
					for (s32 x = 0; x < lineWidth; x += 3)
					{
						out[x + 0] = in[x + 2];
						out[x + 1] = in[x + 1];
						out[x + 2] = in[x + 0];
					}
				}
				else
				{
					memcpy(out, in, lineWidth);
				}
				if (!flip)
					out += lineWidth;
				in += lineWidth;
				in += linepad;
			}
		}

		//! Resizes the surface to a new size and converts it at the same time
		//! to an A8R8G8B8 format, returning the pointer to the new buffer.
		void SharedColorConverter::convert16bitToA8R8G8B8andResize(
				const s16* in, s32* out, s32 newWidth, s32 newHeight,
				s32 currentWidth, s32 currentHeight)
		{
			if (!newWidth || !newHeight)
				return;

			// note: this is very very slow. (i didn't want to write a fast version.
			// but hopefully, nobody wants to convert surfaces every frame.

			f32 sourceXStep = (f32) currentWidth / (f32) newWidth;
			f32 sourceYStep = (f32) currentHeight / (f32) newHeight;
			f32 sy;
			s32 t;

			for (s32 x = 0; x < newWidth; ++x)
			{
				sy = 0.0f;

				for (s32 y = 0; y < newHeight; ++y)
				{
					t = in[(s32) (((s32) sy) * currentWidth + x * sourceXStep)];
					t = (((t >> 15) & 0x1) << 31) | (((t >> 10) & 0x1F) << 19)
							| (((t >> 5) & 0x1F) << 11) | (t & 0x1F) << 3;
					out[(s32) (y * newWidth + x)] = t;

					sy += sourceYStep;
				}
			}
		}

		//! copies X8R8G8B8 32 bit data
		void SharedColorConverter::convert32BitTo32Bit(const s32* in, s32* out,
				s32 width, s32 height, s32 linepad, bool flip)
		{
			if (!in || !out)
				return;

			if (flip)
				out += width * height;

			for (s32 y = 0; y < height; ++y)
			{
				if (flip)
					out -= width;
#ifdef __BIG_ENDIAN__
				for (s32 x=0; x<width; ++x)
				out[x]=os::Byteswap::byteswap(in[x]);
#else
				memcpy(out, in, width * sizeof(s32));
#endif
				if (!flip)
					out += width;
				in += width;
				in += linepad;
			}
		}

		void SharedColorConverter::convert_A1R5G5B5toR8G8B8(const void* sP,
				s32 sN, void* dP)
		{
			u16* sB = (u16*) sP;
			u8 * dB = (u8 *) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				dB[2] = (*sB & 0x7c00) >> 7;
				dB[1] = (*sB & 0x03e0) >> 2;
				dB[0] = (*sB & 0x1f) << 3;

				sB += 1;
				dB += 3;
			}
		}

		void SharedColorConverter::convert_A1R5G5B5toB8G8R8(const void* sP,
				s32 sN, void* dP)
		{
			u16* sB = (u16*) sP;
			u8 * dB = (u8 *) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				dB[0] = (*sB & 0x7c00) >> 7;
				dB[1] = (*sB & 0x03e0) >> 2;
				dB[2] = (*sB & 0x1f) << 3;

				sB += 1;
				dB += 3;
			}
		}

		void SharedColorConverter::convert_A1R5G5B5toR5G5B5A1(const void* sP,
				s32 sN, void* dP)
		{
			const u16* sB = (const u16*) sP;
			u16* dB = (u16*) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				*dB = (*sB << 1) | (*sB >> 15);
				++sB;
				++dB;
			}
		}

		void SharedColorConverter::convert_A1R5G5B5toA8R8G8B8(const void* sP,
				s32 sN, void* dP)
		{
			u16* sB = (u16*) sP;
			u32* dB = (u32*) dP;

			for (s32 x = 0; x < sN; ++x)
				*dB++ = A1R5G5B5toA8R8G8B8(*sB++);
		}

		void SharedColorConverter::convert_A1R5G5B5toA1R5G5B5(const void* sP,
				s32 sN, void* dP)
		{
			memcpy(dP, sP, sN * 2);
		}

		void SharedColorConverter::convert_A1R5G5B5toR5G6B5(const void* sP,
				s32 sN, void* dP)
		{
			u16* sB = (u16*) sP;
			u16* dB = (u16*) dP;

			for (s32 x = 0; x < sN; ++x)
				*dB++ = A1R5G5B5toR5G6B5(*sB++);
		}

		void SharedColorConverter::convert_A8R8G8B8toR8G8B8(const void* sP,
				s32 sN, void* dP)
		{
			u8* sB = (u8*) sP;
			u8* dB = (u8*) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				// sB[3] is alpha
				dB[0] = sB[2];
				dB[1] = sB[1];
				dB[2] = sB[0];

				sB += 4;
				dB += 3;
			}
		}

		void SharedColorConverter::convert_A8R8G8B8toB8G8R8(const void* sP,
				s32 sN, void* dP)
		{
			u8* sB = (u8*) sP;
			u8* dB = (u8*) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				// sB[3] is alpha
				dB[0] = sB[0];
				dB[1] = sB[1];
				dB[2] = sB[2];

				sB += 4;
				dB += 3;
			}
		}

		void SharedColorConverter::convert_A8R8G8B8toA8R8G8B8(const void* sP,
				s32 sN, void* dP)
		{
			memcpy(dP, sP, sN * 4);
		}

		void SharedColorConverter::convert_A8R8G8B8toA1R5G5B5(const void* sP,
				s32 sN, void* dP)
		{
			u32* sB = (u32*) sP;
			u16* dB = (u16*) dP;

			for (s32 x = 0; x < sN; ++x)
				*dB++ = A8R8G8B8toA1R5G5B5(*sB++);
		}

		void SharedColorConverter::convert_A8R8G8B8toR5G6B5(const void* sP,
				s32 sN, void* dP)
		{
			u8 * sB = (u8 *) sP;
			u16* dB = (u16*) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				s32 r = sB[2] >> 3;
				s32 g = sB[1] >> 2;
				s32 b = sB[0] >> 3;

				dB[0] = (r << 11) | (g << 5) | (b);

				sB += 4;
				dB += 1;
			}
		}

		void SharedColorConverter::convert_A8R8G8B8toR3G3B2(const void* sP,
				s32 sN, void* dP)
		{
			u8* sB = (u8*) sP;
			u8* dB = (u8*) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				u8 r = sB[2] & 0xe0;
				u8 g = (sB[1] & 0xe0) >> 3;
				u8 b = (sB[0] & 0xc0) >> 6;

				dB[0] = (r | g | b);

				sB += 4;
				dB += 1;
			}
		}

		void SharedColorConverter::convert_R8G8B8toR8G8B8(const void* sP,
				s32 sN, void* dP)
		{
			memcpy(dP, sP, sN * 3);
		}

		void SharedColorConverter::convert_R8G8B8toA8R8G8B8(const void* sP,
				s32 sN, void* dP)
		{
			u8* sB = (u8*) sP;
			u32* dB = (u32*) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				*dB = 0xff000000 | (sB[0] << 16) | (sB[1] << 8) | sB[2];

				sB += 3;
				++dB;
			}
		}

		void SharedColorConverter::convert_R8G8B8toA1R5G5B5(const void* sP,
				s32 sN, void* dP)
		{
			u8 * sB = (u8 *) sP;
			u16* dB = (u16*) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				s32 r = sB[0] >> 3;
				s32 g = sB[1] >> 3;
				s32 b = sB[2] >> 3;

				dB[0] = (0x8000) | (r << 10) | (g << 5) | (b);

				sB += 3;
				dB += 1;
			}
		}

		void SharedColorConverter::convert_B8G8R8toA8R8G8B8(const void* sP,
				s32 sN, void* dP)
		{
			u8* sB = (u8*) sP;
			u32* dB = (u32*) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				*dB = 0xff000000 | (sB[2] << 16) | (sB[1] << 8) | sB[0];

				sB += 3;
				++dB;
			}
		}

		void SharedColorConverter::convert_A8R8G8B8toR8G8B8A8(const void* sP,
				s32 sN, void* dP)
		{
			const u32* sB = (const u32*) sP;
			u32* dB = (u32*) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				*dB++ = (*sB << 8) | (*sB >> 24);
				++sB;
			}
		}

		void SharedColorConverter::convert_A8R8G8B8toA8B8G8R8(const void* sP,
				s32 sN, void* dP)
		{
			const u32* sB = (const u32*) sP;
			u32* dB = (u32*) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				*dB++ = (*sB & 0xff00ff00) | ((*sB & 0x00ff0000) >> 16)
						| ((*sB & 0x000000ff) << 16);
				++sB;
			}
		}

		void SharedColorConverter::convert_B8G8R8A8toA8R8G8B8(const void* sP,
				s32 sN, void* dP)
		{
			const u32* sB = static_cast<const u32*>(sP);
			u32* dB = static_cast<u32*>(dP);

			for (s32 x = 0; x < sN; ++x)
			{

				*dB++ = utils::StaticByteSwap::byteswap(*sB);

				++sB;
			}

		}

		void SharedColorConverter::convert_R8G8B8toB8G8R8(const void* sP,
				s32 sN, void* dP)
		{
			u8* sB = (u8*) sP;
			u8* dB = (u8*) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				dB[2] = sB[0];
				dB[1] = sB[1];
				dB[0] = sB[2];

				sB += 3;
				dB += 3;
			}
		}

		void SharedColorConverter::convert_R8G8B8toR5G6B5(const void* sP,
				s32 sN, void* dP)
		{
			u8 * sB = (u8 *) sP;
			u16* dB = (u16*) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				s32 r = sB[0] >> 3;
				s32 g = sB[1] >> 2;
				s32 b = sB[2] >> 3;

				dB[0] = (r << 11) | (g << 5) | (b);

				sB += 3;
				dB += 1;
			}
		}

		void SharedColorConverter::convert_R5G6B5toR5G6B5(const void* sP,
				s32 sN, void* dP)
		{
			memcpy(dP, sP, sN * 2);
		}

		void SharedColorConverter::convert_R5G6B5toR8G8B8(const void* sP,
				s32 sN, void* dP)
		{
			u16* sB = (u16*) sP;
			u8 * dB = (u8 *) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				dB[0] = (*sB & 0xf800) << 8;
				dB[1] = (*sB & 0x07e0) << 2;
				dB[2] = (*sB & 0x001f) << 3;

				sB += 4;
				dB += 3;
			}
		}

		void SharedColorConverter::convert_R5G6B5toB8G8R8(const void* sP,
				s32 sN, void* dP)
		{
			u16* sB = (u16*) sP;
			u8 * dB = (u8 *) dP;

			for (s32 x = 0; x < sN; ++x)
			{
				dB[2] = (*sB & 0xf800) << 8;
				dB[1] = (*sB & 0x07e0) << 2;
				dB[0] = (*sB & 0x001f) << 3;

				sB += 4;
				dB += 3;
			}
		}

		void SharedColorConverter::convert_R5G6B5toA8R8G8B8(const void* sP,
				s32 sN, void* dP)
		{
			u16* sB = (u16*) sP;
			u32* dB = (u32*) dP;

			for (s32 x = 0; x < sN; ++x)
				*dB++ = R5G6B5toA8R8G8B8(*sB++);
		}

		void SharedColorConverter::convert_R5G6B5toA1R5G5B5(const void* sP,
				s32 sN, void* dP)
		{
			u16* sB = (u16*) sP;
			u16* dB = (u16*) dP;

			for (s32 x = 0; x < sN; ++x)
				*dB++ = R5G6B5toA1R5G5B5(*sB++);
		}

		void SharedColorConverter::convert_viaFormat(const void* sP,
				EColorFormat sF, s32 sN, void* dP, EColorFormat dF)
		{
			switch (sF)
			{
				case ECF_A1R5G5B5:
					switch (dF)
					{
						case ECF_A1R5G5B5:
							convert_A1R5G5B5toA1R5G5B5(sP, sN, dP);
							break;
						case ECF_R5G6B5:
							convert_A1R5G5B5toR5G6B5(sP, sN, dP);
							break;
						case ECF_A8R8G8B8:
							convert_A1R5G5B5toA8R8G8B8(sP, sN, dP);
							break;
						case ECF_R8G8B8:
							convert_A1R5G5B5toR8G8B8(sP, sN, dP);
							break;
						case ECF_R16F:
						case ECF_G16R16F:
						case ECF_A16B16G16R16F:
						case ECF_R32F:
						case ECF_G32R32F:
						case ECF_A32B32G32R32F:
						case ECF_UNKNOWN:
						default:
							break;
					}
					break;
				case ECF_R5G6B5:
					switch (dF)
					{
						case ECF_A1R5G5B5:
							convert_R5G6B5toA1R5G5B5(sP, sN, dP);
							break;
						case ECF_R5G6B5:
							convert_R5G6B5toR5G6B5(sP, sN, dP);
							break;
						case ECF_A8R8G8B8:
							convert_R5G6B5toA8R8G8B8(sP, sN, dP);
							break;
						case ECF_R8G8B8:
							convert_R5G6B5toR8G8B8(sP, sN, dP);
							break;
						case ECF_R16F:
						case ECF_G16R16F:
						case ECF_A16B16G16R16F:
						case ECF_R32F:
						case ECF_G32R32F:
						case ECF_A32B32G32R32F:
						case ECF_UNKNOWN:
						default:
							break;
					}
					break;
				case ECF_A8R8G8B8:
					switch (dF)
					{
						case ECF_A1R5G5B5:
							convert_A8R8G8B8toA1R5G5B5(sP, sN, dP);
							break;
						case ECF_R5G6B5:
							convert_A8R8G8B8toR5G6B5(sP, sN, dP);
							break;
						case ECF_A8R8G8B8:
							convert_A8R8G8B8toA8R8G8B8(sP, sN, dP);
							break;
						case ECF_R8G8B8:
							convert_A8R8G8B8toR8G8B8(sP, sN, dP);
							break;
						case ECF_R16F:
						case ECF_G16R16F:
						case ECF_A16B16G16R16F:
						case ECF_R32F:
						case ECF_G32R32F:
						case ECF_A32B32G32R32F:
						case ECF_UNKNOWN:
						default:
							break;
					}
					break;
				case ECF_R8G8B8:
					switch (dF)
					{
						case ECF_A1R5G5B5:
							convert_R8G8B8toA1R5G5B5(sP, sN, dP);
							break;
						case ECF_R5G6B5:
							convert_R8G8B8toR5G6B5(sP, sN, dP);
							break;
						case ECF_A8R8G8B8:
							convert_R8G8B8toA8R8G8B8(sP, sN, dP);
							break;
						case ECF_R8G8B8:
							convert_R8G8B8toR8G8B8(sP, sN, dP);
							break;
						case ECF_R16F:
						case ECF_G16R16F:
						case ECF_A16B16G16R16F:
						case ECF_R32F:
						case ECF_G32R32F:
						case ECF_A32B32G32R32F:
						case ECF_UNKNOWN:
						default:
							break;
					}
					break;

				case ECF_R16F:
				case ECF_G16R16F:
				case ECF_A16B16G16R16F:
				case ECF_R32F:
				case ECF_G32R32F:
				case ECF_A32B32G32R32F:
				case ECF_UNKNOWN:
				default:
					break;
			}
		}

	} // end namespace video
} // end namespace irr
