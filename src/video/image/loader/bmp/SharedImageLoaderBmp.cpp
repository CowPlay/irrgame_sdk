/*
 * CImageLoaderBmp.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#include "SharedImageLoaderBmp.h"
#include "SBMPHeader.h"
#include "video/image/IImage.h"

#include "video/color/SharedColorConverter.h"
#include "io/IReadFile.h"

namespace irrgame
{
	namespace video
	{

		//! Singleton realization
		SharedImageLoaderBmp& SharedImageLoaderBmp::getInstance()
		{
			static SharedImageLoaderBmp instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		SharedImageLoaderBmp::SharedImageLoaderBmp()
		{
		}

		//! Destructor. Should use only one time.
		SharedImageLoaderBmp::~SharedImageLoaderBmp()
		{
		}

		//! Returns BMP image
		IImage* SharedImageLoaderBmp::createImage(io::IReadFile* file)
		{
			SBMPHeader header;

			file->read(&header, sizeof(header));

			s32 pitch = 0;

			//if the header is false
			IRR_ASSERT(header.Id == 0x4d42);

			// we'll only handle RLE-Compression
			IRR_ASSERT(header.Compression <= 2);

			// adjust bitmap data size to dword boundary
			header.BitmapDataSize += (4 - (header.BitmapDataSize % 4)) % 4;

			/*
			 * read palette
			 */

			long pos = file->getPos();
			s32 paletteSize = (header.BitmapDataOffset - pos) / 4;

			s32* paletteData = 0;
			if (paletteSize)
			{
				paletteData = new s32[paletteSize];
				file->read(paletteData, paletteSize * sizeof(s32));
			}

			/*
			 * read image data
			 */

			if (!header.BitmapDataSize)
			{
				// okay, lets guess the size
				// some tools simply don't set it
				header.BitmapDataSize = static_cast<u32>(file->getSize())
						- header.BitmapDataOffset;
			}

			file->seek(header.BitmapDataOffset);

			f32 t = (header.Width) * (header.BPP / 8.0f);
			s32 widthInBytes = (s32) t;
			t -= widthInBytes;
			if (t != 0.0f)
			{
				++widthInBytes;
			}

			s32 lineData = widthInBytes + ((4 - (widthInBytes % 4))) % 4;
			pitch = lineData - widthInBytes;

			u8* bmpData = new u8[header.BitmapDataSize];
			file->read(bmpData, header.BitmapDataSize);

			// decompress data if needed
			switch (header.Compression)
			{
				case 1: // 8 bit rle
				{
					decompress8BitRLE(bmpData, header.BitmapDataSize,
							header.Width, header.Height, pitch);
					break;
				}
				case 2: // 4 bit rle
				{
					decompress4BitRLE(bmpData, header.BitmapDataSize,
							header.Width, header.Height, pitch);
					break;
				}
			}

			/*
			 * create surface
			 */

			// no default constructor from packed area! ARM problem!
			dimension2du dim;
			dim.Width = header.Width;
			dim.Height = header.Height;

			IImage* result = 0;

			switch (header.BPP)
			{
				case 1:
				{
					result = IImage::createEmptyImage(ECF_A1R5G5B5, dim);//new CImage(ECF_A1R5G5B5, dim);

					SharedColorConverter::getInstance().convert1BitTo16Bit(
							bmpData, (s16*) result->lock(), header.Width,
							header.Height, pitch, true);

					break;
				}
				case 4:
				{
					result = IImage::createEmptyImage(ECF_A1R5G5B5, dim);

					SharedColorConverter::getInstance().convert4BitTo16Bit(
							bmpData, (s16*) result->lock(), header.Width,
							header.Height, paletteData, pitch, true);

					break;
				}
				case 8:
				{
					result = IImage::createEmptyImage(ECF_A1R5G5B5, dim);

					SharedColorConverter::getInstance().convert8BitTo16Bit(
							bmpData, (s16*) result->lock(), header.Width,
							header.Height, paletteData, pitch, true);

					break;
				}
				case 16:
				{
					result = IImage::createEmptyImage(ECF_A1R5G5B5, dim);

					SharedColorConverter::getInstance().convert16BitTo16Bit(
							(s16*) bmpData, (s16*) result->lock(), header.Width,
							header.Height, pitch, true);
					break;
				}
				case 24:
				{
					result = IImage::createEmptyImage(ECF_R8G8B8, dim);

					SharedColorConverter::getInstance().convert24BitTo24Bit(
							bmpData, (u8*) result->lock(), header.Width,
							header.Height, pitch, true, true);

					break;
				}
				case 32:
				{ // thx to Reinhard Ostermeier
					result = IImage::createEmptyImage(ECF_A8R8G8B8, dim);

					SharedColorConverter::getInstance().convert32BitTo32Bit(
							(s32*) bmpData, (s32*) result->lock(), header.Width,
							header.Height, pitch, true);

					break;
				}
				default:
				{
					//Not implemented
					IRR_ASSERT(false);
					break;
				}
			};

			result->unlock();

			// clean up
			delete[] paletteData;
			delete[] bmpData;

			return result;
		}

		void SharedImageLoaderBmp::decompress8BitRLE(u8*& bmpData, s32 size,
				s32 width, s32 height, s32 pitch) const
		{
			u8* p = bmpData;
			u8* newBmp = new u8[(width + pitch) * height];
			u8* d = newBmp;
			u8* destEnd = newBmp + (width + pitch) * height;
			s32 line = 0;

			while (bmpData - p < size && d < destEnd)
			{
				if (*p == 0)
				{
					++p;

					switch (*p)
					{
						case 0: // end of line
						{
							++p;
							++line;
							d = newBmp + (line * (width + pitch));
							break;
						}
						case 1: // end of bmp
						{
							delete[] bmpData;
							bmpData = newBmp;
							return;
						}
						case 2:
						{
							++p;
							d += (u8) *p;  // delta
							++p;
							d += ((u8) *p) * (width + pitch);
							++p;
							break;
						}
						default:
						{
							// absolute mode
							s32 count = (u8) *p;
							++p;
							s32 readAdditional = ((2 - (count % 2)) % 2);
							s32 i;

							for (i = 0; i < count; ++i)
							{
								*d = *p;
								++p;
								++d;
							}

							for (i = 0; i < readAdditional; ++i)
							{
								++p;
							}

							break;
						}
					}
				}
				else
				{
					s32 count = (u8) *p;
					++p;
					u8 color = *p;
					++p;

					for (s32 i = 0; i < count; ++i)
					{
						*d = color;
						++d;
					}
				}
			}

			delete[] bmpData;
			bmpData = newBmp;
		}

		void SharedImageLoaderBmp::decompress4BitRLE(u8*& bmpData, s32 size,
				s32 width, s32 height, s32 pitch) const
		{
			s32 lineWidth = (width + 1) / 2 + pitch;
			u8* p = bmpData;
			u8* newBmp = new u8[lineWidth * height];
			u8* d = newBmp;
			u8* destEnd = newBmp + lineWidth * height;
			s32 line = 0;
			s32 shift = 4;

			while (bmpData - p < size && d < destEnd)
			{
				if (*p == 0)
				{
					++p;

					switch (*p)
					{
						case 0: // end of line
						{
							++p;
							++line;
							d = newBmp + (line * lineWidth);
							shift = 4;
							break;
						}
						case 1: // end of bmp
						{
							delete[] bmpData;
							bmpData = newBmp;
							return;
						}
						case 2:
						{
							++p;
							s32 x = (u8) *p;
							++p;
							s32 y = (u8) *p;
							++p;
							d += x / 2 + y * lineWidth;
							shift = x % 2 == 0 ? 4 : 0;

							break;
						}
						default:
						{
							// absolute mode
							s32 count = (u8) *p;
							++p;
							s32 readAdditional = ((2 - ((count) % 2)) % 2);
							s32 readShift = 4;
							s32 i;

							for (i = 0; i < count; ++i)
							{
								s32 color = (((u8) *p) >> readShift) & 0x0f;
								readShift -= 4;
								if (readShift < 0)
								{
									++*p;
									readShift = 4;
								}

								u8 mask = 0x0f << shift;
								*d = (*d & (~mask)) | ((color << shift) & mask);

								shift -= 4;
								if (shift < 0)
								{
									shift = 4;
									++d;
								}

							}

							for (i = 0; i < readAdditional; ++i)
							{
								++p;
							}

							break;
						}
					}
				}
				else
				{
					s32 count = (u8) *p;
					++p;
					s32 color1 = (u8) *p;
					color1 = color1 & 0x0f;
					s32 color2 = (u8) *p;
					color2 = (color2 >> 4) & 0x0f;
					++p;

					for (s32 i = 0; i < count; ++i)
					{
						u8 mask = 0x0f << shift;
						u8 toSet = (shift == 0 ? color1 : color2) << shift;
						*d = (*d & (~mask)) | (toSet & mask);

						shift -= 4;
						if (shift < 0)
						{
							shift = 4;
							++d;
						}
					}
				}
			}

			delete[] bmpData;
			bmpData = newBmp;
		}

	} /* namespace video */
} /* namespace irrgame */
