// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_IMAGE_H_INCLUDED__
#define __C_IMAGE_H_INCLUDED__

#include "video/image/IImage.h"
#include "core/shapes/dimension2d.h"

namespace irrgame
{
	namespace video
	{

		//! IImage implementation with a lot of special image operations for
		//! 16 bit A1R5G5B5/32 Bit A8R8G8B8 images, which are used by the SoftwareDevice.
		class CImage: public IImage
		{
			public:

				//! Constructor from raw image data
				/** \param useForeignMemory: If true, the image will use the data pointer
				 directly and own it from now on, which means it will also try to delete [] the
				 data when the image will be destructed. If false, the memory will by copied. */
				CImage(EColorFormat format, const dimension2du& size,
						void* data, bool ownForeignMemory = true,
						bool deleteMemory = true);

				//! Constructor for empty image
				CImage(EColorFormat format, const dimension2du& size);

				//! destructor
				virtual ~CImage();

				//! Lock function.
				virtual void* lock()
				{
					return Data;
				}

				//! Unlock function.
				virtual void unlock()
				{
				}

				//! Returns width and height of image data.
				virtual const dimension2du& getDimension() const;

				//! Returns bits per pixel.
				virtual u32 getBitsPerPixel() const;

				//! Returns bytes per pixel
				virtual u32 getBytesPerPixel() const;

				//! Returns image data size in bytes
				virtual u32 getImageDataSizeInBytes() const;

				//! Returns image data size in pixels
				virtual u32 getImageDataSizeInPixels() const;

				//! returns mask for red value of a pixel
				virtual u32 getRedMask() const;

				//! returns mask for green value of a pixel
				virtual u32 getGreenMask() const;

				//! returns mask for blue value of a pixel
				virtual u32 getBlueMask() const;

				//! returns mask for alpha value of a pixel
				virtual u32 getAlphaMask() const;

				//! returns a pixel
				virtual SColor getPixel(u32 x, u32 y) const;

				//! sets a pixel
				virtual void setPixel(u32 x, u32 y, const SColor &color,
						bool blend = false);

				//! returns the color format
				virtual EColorFormat getColorFormat() const;

				//! returns pitch of image
				virtual u32 getPitch() const;

				//! copies this surface into another, scaling it to fit.
				virtual void copyToScaling(void* target, u32 width, u32 height,
						EColorFormat format, u32 pitch = 0);

				//! copies this surface into another, scaling it to fit.
				virtual void copyToScaling(IImage* target);

				//! copies this surface into another
				virtual void copyTo(IImage* target, const vector2di& pos =
						vector2di(0, 0));

				//! copies this surface into another
				virtual void copyTo(IImage* target, const vector2di& pos,
						const recti& sourceRect, const recti* clipRect = 0);

				//! copies this surface into another, using the alpha mask, an cliprect and a color to add with
				virtual void copyToWithAlpha(IImage* target,
						const vector2di& pos, const recti& sourceRect,
						const SColor &color, const recti* clipRect = 0);

				//! copies this surface into another, scaling it to fit, appyling a box filter
				virtual void copyToScalingBoxFilter(IImage* target,
						s32 bias = 0, bool blend = false);

				//! fills the surface with black or white
				virtual void fill(const SColor &color);

				//! draws a rectangle
				void drawRectangle(const recti& rect, const SColor &color);

				//! draws a line from to
				void drawLine(const vector2di& from, const vector2di& to,
						const SColor &color);

			private:

				//! assumes format and size has been set and creates the rest
				void initData();

				inline SColor getPixelBox(s32 x, s32 y, s32 fx, s32 fy,
						s32 bias) const;

			private:

				u8* Data;
				dimension2du Size;
				u32 BytesPerPixel;
				u32 Pitch;
				EColorFormat Format;

				bool DeleteMemory;
		};

	} // end namespace video
} // end namespace irr

#endif

