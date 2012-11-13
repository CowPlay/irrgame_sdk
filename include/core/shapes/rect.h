// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_RECT_H_INCLUDED__
#define __IRR_RECT_H_INCLUDED__

#include "core/shapes/vector2d.h"
namespace irrgame
{
	namespace core
	{

		//! Rectangle template.
		/** Mostly used by 2D GUI elements and for 2D drawing methods.
		 It has 2 positions instead of position and dimension and a fast
		 method for collision detection with other rectangles and points.

		 Coordinates are (0,0) for top-left corner, and increasing to the right
		 and to the bottom.
		 */
		template<class T>
		class rect
		{
			public:
				//! Returns empty rect
				static const rect& getEmpty(void);

			public:

				/*
				 * Constructors
				 */

				//! Default constructor creating empty rectangle at (0,0)
				rect();

				//! Constructor with two corners
				rect(T x, T y, T x2, T y2);

				//! Constructor with two corners
				rect(const vector2d<T>& upperLeft,
						const vector2d<T>& lowerRight);

				//! Constructor with upper left corner and dimension
				template<class U>
				rect(const vector2d<T>& pos, const dimension2d<U>& size) :
						UpperLeftCorner(pos), LowerRightCorner(
								pos.X + size.Width, pos.Y + size.Height)
				{
				}

				/*
				 * Methods
				 */

				//! Returns size of rectangle
				T getArea() const;

				//! Get width of rectangle.
				T getWidth() const;

				//! Get height of rectangle.
				T getHeight() const;

				//! Returns if a 2d point is within this rectangle.
				/** \param pos Position to test if it lies within this rectangle.
				 \return True if the position is within the rectangle, false if not. */
				bool isPointInside(const vector2d<T>& pos) const;

				//! Check if the rectangle collides with another rectangle.
				/** \param other Rectangle to test collision with
				 \return True if the rectangles collide. */
				bool isRectCollided(const rect<T>& other) const;

				//! Clips this rectangle with another one.
				/** \param other Rectangle to clip with */
				void clipAgainst(const rect<T>& other);

				//! Moves this rectangle to fit inside another one.
				/** \return True on success, false if not possible */
				bool constrainTo(const rect<T>& other);

				//! If the lower right corner of the rect is smaller then the upper left, the points are swapped.
				void repair();

				//! Returns if the rect is valid to draw.
				/** It would be invalid if the UpperLeftCorner is lower or more
				 right than the LowerRightCorner. */
				bool isValid() const;

				//! Get the center of the rectangle
				vector2d<T> getCenter() const;

				//! Get the dimensions of the rectangle
				dimension2d<T> getSize() const;

				//! Adds a point to the rectangle
				/** Causes the rectangle to grow bigger if point is outside of
				 the box
				 \param p Point to add to the box. */
				void addInternalPoint(const vector2d<T>& p);

				//! Adds a point to the bounding rectangle
				/** Causes the rectangle to grow bigger if point is outside of
				 the box
				 \param x X-Coordinate of the point to add to this box.
				 \param y Y-Coordinate of the point to add to this box. */
				void addInternalPoint(T x, T y);

				/*
				 * Operators
				 */

				//! move right by given numbers
				rect<T> operator+(const vector2d<T>& pos) const;

				//! move right by given numbers
				rect<T>& operator+=(const vector2d<T>& pos);

				//! move left by given numbers
				rect<T> operator-(const vector2d<T>& pos) const;

				//! move left by given numbers
				rect<T>& operator-=(const vector2d<T>& pos);

				//! equality operator
				bool operator==(const rect<T>& other) const;

				//! inequality operator
				bool operator!=(const rect<T>& other) const;

				//! compares size of rectangles
				bool operator<(const rect<T>& other) const;

			public:

				//! Upper left corner
				vector2d<T> UpperLeftCorner;
				//! Lower right corner
				vector2d<T> LowerRightCorner;
		};

		//! Returns empty rect
		template<class T>
		inline const rect<T>& rect<T>::getEmpty(void)
		{
			static const rect<T> empty;
			return empty;
		}

		//! Default constructor creating empty rectangle at (0,0)
		template<class T>
		rect<T>::rect() :
				UpperLeftCorner(0, 0), LowerRightCorner(0, 0)
		{
		}

		//! Constructor with two corners
		template<class T>
		inline rect<T>::rect(T x, T y, T x2, T y2) :
				UpperLeftCorner(x, y), LowerRightCorner(x2, y2)
		{
		}

		//! Constructor with two corners
		template<class T>
		inline rect<T>::rect(const vector2d<T>& upperLeft,
				const vector2d<T>& lowerRight) :
				UpperLeftCorner(upperLeft), LowerRightCorner(lowerRight)
		{
		}

		/*
		 * Methods
		 */

		//! Returns size of rectangle
		template<class T>
		inline T rect<T>::getArea() const
		{
			return getWidth() * getHeight();
		}

		//! Get width of rectangle.
		template<class T>
		inline T rect<T>::getWidth() const
		{
			return LowerRightCorner.X - UpperLeftCorner.X;
		}

		//! Get height of rectangle.
		template<class T>
		inline T rect<T>::getHeight() const
		{
			return LowerRightCorner.Y - UpperLeftCorner.Y;
		}

		//! Returns if a 2d point is within this rectangle.
		template<class T>
		inline bool rect<T>::isPointInside(const vector2d<T>& pos) const
		{
			return (UpperLeftCorner.X <= pos.X && UpperLeftCorner.Y <= pos.Y
					&& LowerRightCorner.X >= pos.X
					&& LowerRightCorner.Y >= pos.Y);
		}

		//! Check if the rectangle collides with another rectangle.
		template<class T>
		inline bool rect<T>::isRectCollided(const rect<T>& other) const
		{
			return (LowerRightCorner.Y > other.UpperLeftCorner.Y
					&& UpperLeftCorner.Y < other.LowerRightCorner.Y
					&& LowerRightCorner.X > other.UpperLeftCorner.X
					&& UpperLeftCorner.X < other.LowerRightCorner.X);
		}

		//! Clips this rectangle with another one.
		template<class T>
		inline void rect<T>::clipAgainst(const rect<T>& other)
		{
			if (other.LowerRightCorner.X < LowerRightCorner.X)
			{
				LowerRightCorner.X = other.LowerRightCorner.X;
			}
			if (other.LowerRightCorner.Y < LowerRightCorner.Y)
			{
				LowerRightCorner.Y = other.LowerRightCorner.Y;
			}

			if (other.UpperLeftCorner.X > UpperLeftCorner.X)
			{
				UpperLeftCorner.X = other.UpperLeftCorner.X;
			}
			if (other.UpperLeftCorner.Y > UpperLeftCorner.Y)
			{
				UpperLeftCorner.Y = other.UpperLeftCorner.Y;
			}

			// correct possible invalid rect resulting from clipping
			if (UpperLeftCorner.Y > LowerRightCorner.Y)
			{
				UpperLeftCorner.Y = LowerRightCorner.Y;
			}
			if (UpperLeftCorner.X > LowerRightCorner.X)
			{
				UpperLeftCorner.X = LowerRightCorner.X;
			}
		}

		//! Moves this rectangle to fit inside another one.
		template<class T>
		inline bool rect<T>::constrainTo(const rect<T>& other)
		{
			if (other.getWidth() < getWidth()
					|| other.getHeight() < getHeight())
				return false;

			T diff = other.LowerRightCorner.X - LowerRightCorner.X;
			if (diff < 0)
			{
				LowerRightCorner.X += diff;
				UpperLeftCorner.X += diff;
			}

			diff = other.LowerRightCorner.Y - LowerRightCorner.Y;
			if (diff < 0)
			{
				LowerRightCorner.Y += diff;
				UpperLeftCorner.Y += diff;
			}

			diff = UpperLeftCorner.X - other.UpperLeftCorner.X;
			if (diff < 0)
			{
				UpperLeftCorner.X -= diff;
				LowerRightCorner.X -= diff;
			}

			diff = UpperLeftCorner.Y - other.UpperLeftCorner.Y;
			if (diff < 0)
			{
				UpperLeftCorner.Y -= diff;
				LowerRightCorner.Y -= diff;
			}

			return true;
		}

		//! If the lower right corner of the rect is smaller then the upper left, the points are swapped.
		template<class T>
		inline void rect<T>::repair()
		{
			if (LowerRightCorner.X < UpperLeftCorner.X)
			{
				T t = LowerRightCorner.X;
				LowerRightCorner.X = UpperLeftCorner.X;
				UpperLeftCorner.X = t;
			}

			if (LowerRightCorner.Y < UpperLeftCorner.Y)
			{
				T t = LowerRightCorner.Y;
				LowerRightCorner.Y = UpperLeftCorner.Y;
				UpperLeftCorner.Y = t;
			}
		}

		//! Returns if the rect is valid to draw.
		template<class T>
		inline bool rect<T>::isValid() const
		{
			return ((LowerRightCorner.X >= UpperLeftCorner.X)
					&& (LowerRightCorner.Y >= UpperLeftCorner.Y));
		}

		//! Get the center of the rectangle
		template<class T>
		inline vector2d<T> rect<T>::getCenter() const
		{
			return vector2d<T>((UpperLeftCorner.X + LowerRightCorner.X) / 2,
					(UpperLeftCorner.Y + LowerRightCorner.Y) / 2);
		}

		//! Get the dimensions of the rectangle
		template<class T>
		inline dimension2d<T> rect<T>::getSize() const
		{
			return dimension2d<T>(getWidth(), getHeight());
		}

		//! Adds a point to the rectangle
		template<class T>
		inline void rect<T>::addInternalPoint(const vector2d<T>& p)
		{
			addInternalPoint(p.X, p.Y);
		}

		//! Adds a point to the bounding rectangle
		template<class T>
		inline void rect<T>::addInternalPoint(T x, T y)
		{
			if (x > LowerRightCorner.X)
			{
				LowerRightCorner.X = x;
			}
			if (y > LowerRightCorner.Y)
			{
				LowerRightCorner.Y = y;
			}

			if (x < UpperLeftCorner.X)
			{
				UpperLeftCorner.X = x;
			}
			if (y < UpperLeftCorner.Y)
			{
				UpperLeftCorner.Y = y;
			}
		}

		//! move right by given numbers
		template<class T>
		inline rect<T> rect<T>::operator+(const vector2d<T>& pos) const
		{
			rect<T> ret(*this);
			return ret += pos;
		}

		//! move right by given numbers
		template<class T>
		inline rect<T>& rect<T>::operator+=(const vector2d<T>& pos)
		{
			UpperLeftCorner += pos;
			LowerRightCorner += pos;
			return *this;
		}

		//! move left by given numbers
		template<class T>
		inline rect<T> rect<T>::operator-(const vector2d<T>& pos) const
		{
			rect<T> ret(*this);
			return ret -= pos;
		}

		//! move left by given numbers
		template<class T>
		inline rect<T>& rect<T>::operator-=(const vector2d<T>& pos)
		{
			UpperLeftCorner -= pos;
			LowerRightCorner -= pos;
			return *this;
		}

		//! equality operator
		template<class T>
		inline bool rect<T>::operator==(const rect<T>& other) const
		{
			return (UpperLeftCorner == other.UpperLeftCorner
					&& LowerRightCorner == other.LowerRightCorner);
		}

		//! inequality operator
		template<class T>
		inline bool rect<T>::operator!=(const rect<T>& other) const
		{
			return (UpperLeftCorner != other.UpperLeftCorner
					|| LowerRightCorner != other.LowerRightCorner);
		}

		//! compares size of rectangles
		template<class T>
		bool rect<T>::operator<(const rect<T>& other) const
		{
			return getArea() < other.getArea();
		}

	} // end namespace core
} // end namespace irrgame

//! Typedefs for rect
typedef irrgame::core::rect<f32> rectf;
typedef irrgame::core::rect<s32> recti;

#endif

