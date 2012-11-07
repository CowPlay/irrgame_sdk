/*
 * IImage.h
 *
 *  Created on: Jul 30, 2012
 *      Author: gregorytkach
 */

#ifndef IIMAGE_H_
#define IIMAGE_H_

// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "core/engine/IReferenceCounted.h"
#include "video/color/EColorFormat.h"
#include "video/color/SColor.h"
#include "core/shapes/dimension2d.h"
#include "core/shapes/vector2d.h"
#include "core/shapes/rect.h"

namespace irrgame
{
	namespace io
	{
		class IReadFile;
	}  // namespace io

	namespace video
	{
		//! Interface for software image data.
		/** Image loaders create these images from files. IVideoDrivers convert
		 these images into their (hardware) textures.
		 */
		class IImage: public virtual IReferenceCounted
		{
				/*
				 * Static methods
				 */
			public:

				//! Image creator;
				static IImage* createImage(io::IReadFile* file);

				//! Create image from raw data
				static IImage* createRawImage(EColorFormat format,
						const dimension2du& size, void* data,
						bool ownForeignMemory = true, bool deleteMemory = true);

				//! Empty image creator;
				static IImage* createEmptyImage(EColorFormat format,
						const dimension2du& size);

				/*
				 * Instance methods
				 */

			public:

				//! Lock function. Use this to get a pointer to the image data.
				/** After you don't need the pointer anymore, you must call unlock().
				 \return Pointer to the image data. What type of data is pointed to
				 depends on the color format of the image. For example if the color
				 format is ECF_A8R8G8B8, it is of u32. Be sure to call unlock() after
				 you don't need the pointer any more. */
				virtual void* lock() = 0;

				//! Unlock function.
				/** Should be called after the pointer received by lock() is not
				 needed anymore. */
				virtual void unlock() = 0;

				//! Returns width and height of image data.
				virtual const dimension2du& getDimension() const = 0;

				//! Returns bits per pixel.
				virtual u32 getBitsPerPixel() const = 0;

				//! Returns bytes per pixel
				virtual u32 getBytesPerPixel() const = 0;

				//! Returns image data size in bytes
				virtual u32 getImageDataSizeInBytes() const = 0;

				//! Returns image data size in pixels
				virtual u32 getImageDataSizeInPixels() const = 0;

				//! Returns a pixel
				virtual SColor getPixel(u32 x, u32 y) const = 0;

				//! Sets a pixel
				virtual void setPixel(u32 x, u32 y, const SColor &color,
						bool blend = false) = 0;

				//! Returns the color format
				virtual EColorFormat getColorFormat() const = 0;

				//! Returns mask for red value of a pixel
				virtual u32 getRedMask() const = 0;

				//! Returns mask for green value of a pixel
				virtual u32 getGreenMask() const = 0;

				//! Returns mask for blue value of a pixel
				virtual u32 getBlueMask() const = 0;

				//! Returns mask for alpha value of a pixel
				virtual u32 getAlphaMask() const = 0;

				//! Returns pitch of image
				virtual u32 getPitch() const = 0;

				//! Copies the image into the target, scaling the image to fit
				virtual void copyToScaling(void* target, u32 width, u32 height,
						EColorFormat format = ECF_A8R8G8B8, u32 pitch = 0) =0;

				//! Copies the image into the target, scaling the image to fit
				virtual void copyToScaling(IImage* target) = 0;

				//! copies this surface into another
				virtual void copyTo(IImage* target, const vector2di& pos =
						vector2di(0, 0)) = 0;

				//! copies this surface into another
				virtual void copyTo(IImage* target, const vector2di& pos,
						const recti& sourceRect, const recti* clipRect = 0) = 0;

				//! copies this surface into another, using the alpha mask, an cliprect and a color to add with
				virtual void copyToWithAlpha(IImage* target,
						const vector2di& pos, const recti& sourceRect,
						const SColor &color, const recti* clipRect = 0) = 0;

				//! copies this surface into another, scaling it to fit, appyling a box filter
				virtual void copyToScalingBoxFilter(IImage* target,
						s32 bias = 0, bool blend = false) = 0;

				//! fills the surface with black or white
				virtual void fill(const SColor &color) = 0;
		};

	} // end namespace video
} // end namespace irr

#endif /* IIMAGE_H_ */
