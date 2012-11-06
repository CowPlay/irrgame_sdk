// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __COLOR_H_INCLUDED__
#define __COLOR_H_INCLUDED__

#include "compileConfig.h"

namespace irrgame
{
	namespace video
	{

		//! Class representing a 32 bit ARGB color.
		/** The color values for alpha, red, green, and blue are
		 stored in a single u32. So all four values may be between 0 and 255.
		 Alpha in Irrlicht is opacity, so 0 is fully transparent, 255 is fully opaque (solid).
		 This class is used by most parts of the Irrlicht Engine
		 to specify a color. Another way is using the class SColorf, which
		 stores the color values in 4 floats.
		 This class must consist of only one u32 and must not use virtual functions.
		 */
		class SColor
		{
			public:

				//! Constructor of the Color. Does nothing.opaque
				/** The color value is not initialized to save time. */
				SColor();

				//! Constructs the color from 4 values representing the alpha, red, green and blue component.
				/** Must be values between 0 and 255. */
				SColor(u32 a, u32 r, u32 g, u32 b);

				//! Constructs the color from a 32 bit value. Could be another color.
				SColor(u32 clr);

				//! Returns the alpha component of the color.
				/** The alpha component defines how opaque a color is.
				 \return The alpha value of the color. 0 is fully transparent, 255 is fully opaque. */
				u32 getAlpha() const;

				//! Returns the red component of the color.
				/** \return Value between 0 and 255, specifying how red the color is.
				 0 means no red, 255 means full red. */
				u32 getRed() const;

				//! Returns the green component of the color.
				/** \return Value between 0 and 255, specifying how green the color is.
				 0 means no green, 255 means full green. */
				u32 getGreen() const;

				//! Returns the blue component of the color.
				/** \return Value between 0 and 255, specifying how blue the color is.
				 0 means no blue, 255 means full blue. */
				u32 getBlue() const;

				//! Get lightness of the color in the range [0,255]
				f32 getLightness() const;

				//! Get luminance of the color in the range [0,255].
				f32 getLuminance() const;

				//! Get average intensity of the color in the range [0,255].
				u32 getAverage() const;

				//! Sets the alpha component of the Color.
				/** The alpha component defines how transparent a color should be.
				 \param a The alpha value of the color. 0 is fully transparent, 255 is fully opaque. */
				void setAlpha(u32 a);

				//! Sets the red component of the Color.
				/** \param r: Has to be a value between 0 and 255.
				 0 means no red, 255 means full red. */
				void setRed(u32 r);

				//! Sets the green component of the Color.
				/** \param g: Has to be a value between 0 and 255.
				 0 means no green, 255 means full green. */
				void setGreen(u32 g);

				//! Sets the blue component of the Color.
				/** \param b: Has to be a value between 0 and 255.
				 0 means no blue, 255 means full blue. */
				void setBlue(u32 b);

				//! Calculates a 16 bit A1R5G5B5 value of this color.
				/** \return 16 bit A1R5G5B5 value of this color. */
				u16 toA1R5G5B5() const;

				//! Converts color to OpenGL color format
				/** From ARGB to RGBA in 4 byte components for endian aware
				 passing to OpenGL
				 \param dest: address where the 4x8 bit OpenGL color is stored. */
				void toOpenGLColor(u8* dest) const;

				//! Sets all four components of the color at once.
				/** Constructs the color from 4 values representing the alpha,
				 red, green and blue components of the color. Must be values
				 between 0 and 255.
				 \param a: Alpha component of the color. The alpha component
				 defines how transparent a color should be. Has to be a value
				 between 0 and 255. 255 means not transparent (opaque), 0 means
				 fully transparent.
				 \param r: Sets the red component of the Color. Has to be a
				 value between 0 and 255. 0 means no red, 255 means full red.
				 \param g: Sets the green component of the Color. Has to be a
				 value between 0 and 255. 0 means no green, 255 means full
				 green.
				 \param b: Sets the blue component of the Color. Has to be a
				 value between 0 and 255. 0 means no blue, 255 means full blue. */
				void set(u32 a, u32 r, u32 g, u32 b);

				void set(u32 col);

				//! Compares the color to another color.
				/** \return True if the colors are the same, and false if not. */
				bool operator==(const SColor& other) const;

				//! Compares the color to another color.
				/** \return True if the colors are different, and false if they are the same. */
				bool operator!=(const SColor& other) const;

				//! comparison operator
				/** \return True if this color is smaller than the other one */
				bool operator<(const SColor& other) const;

				//! Adds two colors, result is clamped to 0..255 values
				/** \param other Color to add to this color
				 \return Addition of the two colors, clamped to 0..255 values */
				SColor operator+(const SColor& other) const;

				//! Interpolates the color with a f32 value to another color
				/** \param other: Other color
				 \param d: value between 0.0f and 1.0f
				 \return Interpolated color. */
				SColor getInterpolated(const SColor &other, f32 d) const;

				//! Returns interpolated color. ( quadratic )
				/** \param c1: first color to interpolate with
				 \param c2: second color to interpolate with
				 \param d: value between 0.0f and 1.0f. */
				SColor getInterpolated_quadratic(const SColor& c1,
						const SColor& c2, f32 d) const;

			public:
				//! color in A8R8G8B8 Format
				u32 color;
		};

	} // end namespace video
} // end namespace irr

#endif

