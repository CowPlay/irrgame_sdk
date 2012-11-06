/*
 * SColorf.h
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#ifndef SCOLORF_H_
#define SCOLORF_H_

#include "compileConfig.h"

namespace irrgame
{

	namespace video
	{

		struct SColor;

		//! Class representing a color with four floats.
		/** The color values for red, green, blue
		 and alpha are each stored in a 32 bit floating point variable.
		 So all four values may be between 0.0f and 1.0f.
		 Another, faster way to define colors is using the class SColor, which
		 stores the color values in a single 32 bit integer.
		 */
		class SColorf
		{
			public:
				//! Default constructor for SColorf.
				/** Sets red, green and blue to 0.0f and alpha to 1.0f. */
				SColorf();

				//! Constructs a color from up to four color values: red, green, blue, and alpha.
				/** \param r: Red color component. Should be a value between
				 0.0f meaning no red and 1.0f, meaning full red.
				 \param g: Green color component. Should be a value between 0.0f
				 meaning no green and 1.0f, meaning full green.
				 \param b: Blue color component. Should be a value between 0.0f
				 meaning no blue and 1.0f, meaning full blue.
				 \param a: Alpha color component of the color. The alpha
				 component defines how transparent a color should be. Has to be
				 a value between 0.0f and 1.0f, 1.0f means not transparent
				 (opaque), 0.0f means fully transparent. */
				SColorf(f32 r, f32 g, f32 b, f32 a = 1.0f);

				//! Constructs a color from 32 bit Color.
				/** \param c: 32 bit color from which this SColorf class is
				 constructed from. */
				SColorf(SColor c);

				//! Converts this color to a SColor without floats.
				SColor toSColor() const;

				//! Sets three color components to new values at once.
				/** \param rr: Red color component. Should be a value between 0.0f meaning
				 no red (=black) and 1.0f, meaning full red.
				 \param gg: Green color component. Should be a value between 0.0f meaning
				 no green (=black) and 1.0f, meaning full green.
				 \param bb: Blue color component. Should be a value between 0.0f meaning
				 no blue (=black) and 1.0f, meaning full blue. */
				void set(f32 rr, f32 gg, f32 bb);

				//! Sets all four color components to new values at once.
				/** \param aa: Alpha component. Should be a value between 0.0f meaning
				 fully transparent and 1.0f, meaning opaque.
				 \param rr: Red color component. Should be a value between 0.0f meaning
				 no red and 1.0f, meaning full red.
				 \param gg: Green color component. Should be a value between 0.0f meaning
				 no green and 1.0f, meaning full green.
				 \param bb: Blue color component. Should be a value between 0.0f meaning
				 no blue and 1.0f, meaning full blue. */
				void set(f32 aa, f32 rr, f32 gg, f32 bb);

				//! Interpolates the color with a f32 value to another color
				/** \param other: Other color
				 \param d: value between 0.0f and 1.0f
				 \return Interpolated color. */
				SColorf getInterpolated(const SColorf &other, f32 d) const;

				//! Returns interpolated color. ( quadratic )
				/** \param c1: first color to interpolate with
				 \param c2: second color to interpolate with
				 \param d: value between 0.0f and 1.0f. */
				inline SColorf getInterpolated_quadratic(const SColorf& c1,
						const SColorf& c2, f32 d) const;

				//! Sets a color component by index. R=0, G=1, B=2, A=3
				//TODO: refactor it
				void setColorComponentValue(s32 index, f32 value);

				//! Returns the alpha component of the color in the range 0.0 (transparent) to 1.0 (opaque)
				f32 getAlpha() const;

				//! Returns the red component of the color in the range 0.0 to 1.0
				f32 getRed() const;

				//! Returns the green component of the color in the range 0.0 to 1.0
				f32 getGreen() const;

				//! Returns the blue component of the color in the range 0.0 to 1.0
				f32 getBlue() const;

			public:

				//! red color component
				f32 Red;

				//! green color component
				f32 Green;

				//! blue component
				f32 Blue;

				//! alpha color component
				f32 Alpha;
		};

	}  // namespace video

}  // namespace irrgame

#endif /* SCOLORF_H_ */
