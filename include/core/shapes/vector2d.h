// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_POINT_2D_H_INCLUDED__
#define __IRR_POINT_2D_H_INCLUDED__

#include "core/math/SharedFastMath.h"
#include "core/shapes/dimension2d.h"

namespace irrgame
{
	namespace core
	{

		//! 2d vector template class with lots of operators and methods.
		template<class T>
		class vector2d
		{
			public:
				//! Returns empty 2d vector
				static const vector2d& getEmpty(void);

			public:

				/*
				 * Constructors
				 */

				//! Default constructor (null vector)
				vector2d();

				//! Constructor with two different values
				vector2d(T nx, T ny);

				//! Constructor with the same value for both members
				explicit vector2d(T n);

				//! Copy constructor
				vector2d(const vector2d<T>& other);

				//! Constructor from dimension
				vector2d(const dimension2d<T>& other);

				/*
				 * Operators
				 */

				vector2d<T> operator-() const;

				vector2d<T>& operator=(const vector2d<T>& other);

				vector2d<T>& operator=(const dimension2d<T>& other);

				vector2d<T> operator+(const vector2d<T>& other) const;
				vector2d<T> operator+(const dimension2d<T>& other) const;
				vector2d<T>& operator+=(const vector2d<T>& other);
				vector2d<T> operator+(const T v) const;
				vector2d<T>& operator+=(const T v);
				vector2d<T>& operator+=(const dimension2d<T>& other);

				vector2d<T> operator-(const vector2d<T>& other) const;
				vector2d<T> operator-(const dimension2d<T>& other) const;
				vector2d<T>& operator-=(const vector2d<T>& other);
				vector2d<T> operator-(const T v) const;
				vector2d<T>& operator-=(const T v);
				vector2d<T>& operator-=(const dimension2d<T>& other);

				vector2d<T> operator*(const vector2d<T>& other) const;
				vector2d<T>& operator*=(const vector2d<T>& other);
				vector2d<T> operator*(const T v) const;
				vector2d<T>& operator*=(const T v);

				vector2d<T> operator/(const vector2d<T>& other) const;
				vector2d<T>& operator/=(const vector2d<T>& other);
				vector2d<T> operator/(const T v) const;
				vector2d<T>& operator/=(const T v);

				//! sort in order X, Y. Equality with rounding tolerance.
				bool operator<=(const vector2d<T>&other) const;

				//! sort in order X, Y. Equality with rounding tolerance.
				bool operator>=(const vector2d<T>&other) const;

				//! sort in order X, Y. Difference must be above rounding tolerance.
				bool operator<(const vector2d<T>&other) const;

				//! sort in order X, Y. Difference must be above rounding tolerance.
				bool operator>(const vector2d<T>&other) const;

				bool operator==(const vector2d<T>& other) const;
				bool operator!=(const vector2d<T>& other) const;

				/*
				 * Methods
				 */

				//! Checks if this vector equals the other one.
				/** Takes floating point rounding errors into account.
				 \param other Vector to compare with.
				 \return True if the two vector are (almost) equal, else false. */
				bool equals(const vector2d<T>& other) const;

				vector2d<T>& set(T nx, T ny);
				vector2d<T>& set(const vector2d<T>& p);

				//! Gets the length of the vector.
				/** \return The length of the vector. */
				T getLength() const;

				//! Get the squared length of this vector
				/** This is useful because it is much faster than getLength().
				 \return The squared length of the vector. */
				T getLengthSQ() const;

				//! Get the dot product of this vector with another.
				/** \param other Other vector to take dot product with.
				 \return The dot product of the two vectors. */
				T dotProduct(const vector2d<T>& other) const;

				//! Gets distance from another point.
				/** Here, the vector is interpreted as a point in 2-dimensional space.
				 \param other Other vector to measure from.
				 \return Distance from other point. */
				T getDistanceFrom(const vector2d<T>& other) const;

				//! Returns squared distance from another point.
				/** Here, the vector is interpreted as a point in 2-dimensional space.
				 \param other Other vector to measure from.
				 \return Squared distance from other point. */
				T getDistanceFromSQ(const vector2d<T>& other) const;

				//! rotates the point anticlockwise around a center by an amount of degrees.
				/** \param degrees Amount of degrees to rotate by, anticlockwise.
				 \param center Rotation center.
				 \return This vector after transformation. */
				vector2d<T>& rotateBy(f32 degrees, const vector2d<T>& center =
						vector2d<T>());

				//! Normalize the vector.
				/** The null vector is left untouched.
				 \return Reference to this vector, after normalization. */
				vector2d<T>& normalize();

				//! Calculates the angle of this vector in degrees in the trigonometric sense.
				/** 0 is to the right (3 o'clock), values increase counter-clockwise.
				 This method has been suggested by Pr3t3nd3r.
				 \return Returns a value between 0 and 360. */
				f32 getAngleTrig() const;

				//! Calculates the angle of this vector in degrees in the counter trigonometric sense.
				/** 0 is to the right (3 o'clock), values increase clockwise.
				 \return Returns a value between 0 and 360. */
				inline f32 getAngle() const;

				//! Calculates the angle between this vector and another one in degree.
				/** \param b Other vector to test with.
				 \return Returns a value between 0 and 90. */
				inline f32 getAngleWith(const vector2d<T>& b) const;

				//! Returns if this vector interpreted as a point is on a line between two other points.
				/** It is assumed that the point is on the line.
				 \param begin Beginning vector to compare between.
				 \param end Ending vector to compare between.
				 \return True if this vector is between begin and end, false if not. */
				bool isBetweenPoints(const vector2d<T>& begin,
						const vector2d<T>& end) const;

				//! Creates an interpolated vector between this vector and another vector.
				/** \param other The other vector to interpolate with.
				 \param d Interpolation value between 0.0f (all the other vector) and 1.0f (all this vector).
				 Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
				 \return An interpolated vector.  This vector is not modified. */
				vector2d<T> getInterpolated(const vector2d<T>& other,
						f32 d) const;

				//! Creates a quadratically interpolated vector between this and two other vectors.
				/** \param v2 Second vector to interpolate with.
				 \param v3 Third vector to interpolate with (maximum at 1.0f)
				 \param d Interpolation value between 0.0f (all this vector) and 1.0f (all the 3rd vector).
				 Note that this is the opposite direction of interpolation to getInterpolated() and interpolate()
				 \return An interpolated vector. This vector is not modified. */
				vector2d<T> getInterpolated_quadratic(const vector2d<T>& v2,
						const vector2d<T>& v3, f32 d) const;

				//! Sets this vector to the linearly interpolated vector between a and b.
				/** \param a first vector to interpolate with, maximum at 1.0f
				 \param b second vector to interpolate with, maximum at 0.0f
				 \param d Interpolation value between 0.0f (all vector b) and 1.0f (all vector a)
				 Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
				 */
				vector2d<T>& interpolate(const vector2d<T>& a,
						const vector2d<T>& b, f32 d);

			public:

				//! X coordinate of vector.
				T X;

				//! Y coordinate of vector.
				T Y;
		};

		//TODO: review mb need delete
//		template<class S, class T>
//		vector2d<T> operator*(const S scalar, const vector2d<T>& vector)
//		{
//			return vector * scalar;
//		}

		// These methods are declared in dimension2d, but need definitions of vector2d
		template<class T>
		dimension2d<T>::dimension2d(const vector2d<T>& other) :
				Width(other.X), Height(other.Y)
		{
		}

		template<class T>
		bool dimension2d<T>::operator==(const vector2d<T>& other) const
		{
			return Width == other.X && Height == other.Y;
		}

		//! Returns empty 2d vector
		template<class T>
		inline const vector2d<T>& vector2d<T>::getEmpty()
		{
			static const vector2d<T> empty;
			return empty;
		}
		//! Default constructor (null vector)
		template<class T>
		inline vector2d<T>::vector2d() :
				X(0), Y(0)
		{
		}
		//! Constructor with two different values
		template<class T>
		inline vector2d<T>::vector2d(T nx, T ny) :
				X(nx), Y(ny)
		{
		}
		//! Constructor with the same value for both members
		template<class T>
		inline vector2d<T>::vector2d(T n) :
				X(n), Y(n)
		{
		}
		//! Copy constructor
		template<class T>
		inline vector2d<T>::vector2d(const vector2d<T>& other) :
				X(other.X), Y(other.Y)
		{
		}

		//! Constructor from dimension
		template<class T>
		inline vector2d<T>::vector2d(const dimension2d<T>& other) :
				X(other.Width), Y(other.Height)
		{
		}

		template<class T>
		inline vector2d<T> vector2d<T>::operator-() const
		{
			return vector2d<T>(-X, -Y);
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::operator=(const vector2d<T>& other)
		{
			X = other.X;
			Y = other.Y;
			return *this;
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::operator=(const dimension2d<T>& other)
		{
			X = other.Width;
			Y = other.Height;
			return *this;
		}

		template<class T>
		inline vector2d<T> vector2d<T>::operator+(
				const vector2d<T>& other) const
		{
			return vector2d<T>(X + other.X, Y + other.Y);
		}

		template<class T>
		inline vector2d<T> vector2d<T>::operator+(
				const dimension2d<T>& other) const
		{
			return vector2d<T>(X + other.Width, Y + other.Height);
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::operator+=(const vector2d<T>& other)
		{
			X += other.X;
			Y += other.Y;
			return *this;
		}

		template<class T>
		inline vector2d<T> vector2d<T>::operator+(const T v) const
		{
			return vector2d<T>(X + v, Y + v);
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::operator+=(const T v)
		{
			X += v;
			Y += v;
			return *this;
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::operator+=(const dimension2d<T>& other)
		{
			X += other.Width;
			Y += other.Height;
			return *this;
		}

		template<class T>
		inline vector2d<T> vector2d<T>::operator-(
				const vector2d<T>& other) const
		{
			return vector2d<T>(X - other.X, Y - other.Y);
		}

		template<class T>
		inline vector2d<T> vector2d<T>::operator-(
				const dimension2d<T>& other) const
		{
			return vector2d<T>(X - other.Width, Y - other.Height);
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::operator-=(const vector2d<T>& other)
		{
			X -= other.X;
			Y -= other.Y;
			return *this;
		}

		template<class T>
		inline vector2d<T> vector2d<T>::operator-(const T v) const
		{
			return vector2d<T>(X - v, Y - v);
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::operator-=(const T v)
		{
			X -= v;
			Y -= v;
			return *this;
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::operator-=(const dimension2d<T>& other)
		{
			X -= other.Width;
			Y -= other.Height;
			return *this;
		}

		template<class T>
		inline vector2d<T> vector2d<T>::operator*(
				const vector2d<T>& other) const
		{
			return vector2d<T>(X * other.X, Y * other.Y);
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::operator*=(const vector2d<T>& other)
		{
			X *= other.X;
			Y *= other.Y;
			return *this;
		}

		template<class T>
		inline vector2d<T> vector2d<T>::operator*(const T v) const
		{
			return vector2d<T>(X * v, Y * v);
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::operator*=(const T v)
		{
			X *= v;
			Y *= v;
			return *this;
		}

		template<class T>
		inline vector2d<T> vector2d<T>::operator/(
				const vector2d<T>& other) const
		{
			return vector2d<T>(X / other.X, Y / other.Y);
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::operator/=(const vector2d<T>& other)
		{
			X /= other.X;
			Y /= other.Y;
			return *this;
		}

		template<class T>
		inline vector2d<T> vector2d<T>::operator/(const T v) const
		{
			return vector2d<T>(X / v, Y / v);
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::operator/=(const T v)
		{
			X /= v;
			Y /= v;
			return *this;
		}

		//! sort in order X, Y. Equality with rounding tolerance.
		template<class T>
		inline bool vector2d<T>::operator<=(const vector2d<T>&other) const
		{
			return (X < other.X
					|| core::SharedMath::getInstance().equals(X, other.X))
					|| (core::SharedMath::getInstance().equals(X, other.X)
							&& (Y < other.Y
									|| core::SharedMath::getInstance().equals(Y,
											other.Y)));
		}

		//! sort in order X, Y. Equality with rounding tolerance.
		template<class T>
		inline bool vector2d<T>::operator>=(const vector2d<T>&other) const
		{
			return (X > other.X
					|| core::SharedMath::getInstance().equals(X, other.X))
					|| (core::SharedMath::getInstance().equals(X, other.X)
							&& (Y > other.Y
									|| core::SharedMath::getInstance().equals(Y,
											other.Y)));
		}

		//! sort in order X, Y. Difference must be above rounding tolerance.
		template<class T>
		inline bool vector2d<T>::operator<(const vector2d<T>&other) const
		{
			return (X < other.X
					&& !core::SharedMath::getInstance().equals(X, other.X))
					|| (core::SharedMath::getInstance().equals(X, other.X)
							&& Y < other.Y
							&& !core::SharedMath::getInstance().equals(Y,
									other.Y));
		}

		//! sort in order X, Y. Difference must be above rounding tolerance.
		template<class T>
		inline bool vector2d<T>::operator>(const vector2d<T>&other) const
		{
			return (X > other.X
					&& !core::SharedMath::getInstance().equals(X, other.X))
					|| (core::SharedMath::getInstance().equals(X, other.X)
							&& Y > other.Y
							&& !core::SharedMath::getInstance().equals(Y,
									other.Y));
		}

		template<class T>
		inline bool vector2d<T>::operator==(const vector2d<T>& other) const
		{
			return equals(other);
		}

		template<class T>
		inline bool vector2d<T>::operator!=(const vector2d<T>& other) const
		{
			return !equals(other);
		}

		//! Checks if this vector equals the other one.
		template<class T>
		inline bool vector2d<T>::equals(const vector2d<T>& other) const
		{
			return core::SharedMath::getInstance().equals(X, other.X)
					&& core::SharedMath::getInstance().equals(Y, other.Y);
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::set(T nx, T ny)
		{
			X = nx;
			Y = ny;
			return *this;
		}

		template<class T>
		inline vector2d<T>& vector2d<T>::set(const vector2d<T>& p)
		{
			X = p.X;
			Y = p.Y;
			return *this;
		}

		//! Gets the length of the vector.
		template<class T>
		inline T vector2d<T>::getLength() const
		{
			return core::SharedMath::getInstance().squareroot(X * X + Y * Y);
		}

		//! Get the squared length of this vector
		template<class T>
		inline T vector2d<T>::getLengthSQ() const
		{
			return X * X + Y * Y;
		}

		//! Get the dot product of this vector with another.
		template<class T>
		inline T vector2d<T>::dotProduct(const vector2d<T>& other) const
		{
			return X * other.X + Y * other.Y;
		}

		//! Gets distance from another point.
		template<class T>
		inline T vector2d<T>::getDistanceFrom(const vector2d<T>& other) const
		{
			return vector2d<T>(X - other.X, Y - other.Y).getLength();
		}

		//! Returns squared distance from another point.
		template<class T>
		inline T vector2d<T>::getDistanceFromSQ(const vector2d<T>& other) const
		{
			return vector2d<T>(X - other.X, Y - other.Y).getLengthSQ();
		}

		//! rotates the point anticlockwise around a center by an amount of degrees.
		template<class T>
		inline vector2d<T>& vector2d<T>::rotateBy(f32 degrees,
				const vector2d<T>& center)
		{
			degrees *= SharedMath::DegToRad;
			const f32 cs = cos(degrees);
			const f32 sn = sin(degrees);

			X -= center.X;
			Y -= center.Y;

			set((T) (X * cs - Y * sn), (T) (X * sn + Y * cs));

			X += center.X;
			Y += center.Y;
			return *this;
		}

		//! Normalize the vector.
		template<class T>
		inline vector2d<T>& vector2d<T>::normalize()
		{
			f32 length = (f32) (X * X + Y * Y);
			if (core::SharedMath::getInstance().equals(length, 0.f))
				return *this;
			length = core::SharedFastMath::getInstance().invertSqrt(length);
			X = (T) (X * length);
			Y = (T) (Y * length);
			return *this;
		}

		//! Calculates the angle of this vector in degrees in the trigonometric sense.
		template<class T>
		inline f32 vector2d<T>::getAngleTrig() const
		{
			if (Y == 0)
				return X < 0 ? 180 : 0;
			else if (X == 0)
				return Y < 0 ? 270 : 90;

			if (Y > 0)
				if (X > 0)
					return atan(Y / X) * SharedMath::RadToDeg;
				else
					return 180.0 - atan(Y / -X) * SharedMath::RadToDeg;
			else if (X > 0)
				return 360.0 - atan(-Y / X) * SharedMath::RadToDeg;
			else
				return 180.0 + atan(-Y / -X) * SharedMath::RadToDeg;
		}

		//! Calculates the angle of this vector in degrees in the counter trigonometric sense.
		template<class T>
		inline f32 vector2d<T>::getAngle() const
		{
			if (Y == 0) // corrected thanks to a suggestion by Jox
				return X < 0 ? 180 : 0;
			else if (X == 0)
				return Y < 0 ? 90 : 270;

			// don't use getLength here to avoid precision loss with s32 vectors
			f32 tmp = Y / sqrt((f32) (X * X + Y * Y));
			tmp = atan(
					core::SharedMath::getInstance().squareroot(1 - tmp * tmp)
							/ tmp) * SharedMath::RadToDeg;

			if (X > 0 && Y > 0)
				return tmp + 270;
			else if (X > 0 && Y < 0)
				return tmp + 90;
			else if (X < 0 && Y < 0)
				return 90 - tmp;
			else if (X < 0 && Y > 0)
				return 270 - tmp;

			return tmp;
		}

		//! Calculates the angle between this vector and another one in degree.
		template<class T>
		inline f32 vector2d<T>::getAngleWith(const vector2d<T>& b) const
		{
			f32 tmp = X * b.X + Y * b.Y;

			if (tmp == 0.0)
				return 90.0;

			tmp = tmp
					/ core::SharedMath::getInstance().squareroot(
							(f32) ((X * X + Y * Y) * (b.X * b.X + b.Y * b.Y)));
			if (tmp < 0.0)
				tmp = -tmp;

			return atan(sqrt(1 - tmp * tmp) / tmp) * SharedMath::RadToDeg;
		}

		//! Returns if this vector interpreted as a point is on a line between two other points.
		template<class T>
		inline bool vector2d<T>::isBetweenPoints(const vector2d<T>& begin,
				const vector2d<T>& end) const
		{
			if (begin.X != end.X)
			{
				return ((begin.X <= X && X <= end.X)
						|| (begin.X >= X && X >= end.X));
			}
			else
			{
				return ((begin.Y <= Y && Y <= end.Y)
						|| (begin.Y >= Y && Y >= end.Y));
			}
		}

		//! Creates an interpolated vector between this vector and another vector.
		template<class T>
		inline vector2d<T> vector2d<T>::getInterpolated(
				const vector2d<T>& other, f32 d) const
		{
			f32 inv = 1.0f - d;
			return vector2d<T>((T) (other.X * inv + X * d),
					(T) (other.Y * inv + Y * d));
		}

		//! Creates a quadratically interpolated vector between this and two other vectors.
		template<class T>
		inline vector2d<T> vector2d<T>::getInterpolated_quadratic(
				const vector2d<T>& v2, const vector2d<T>& v3, f32 d) const
		{
			// this*(1-d)*(1-d) + 2 * v2 * (1-d) + v3 * d * d;
			const f32 inv = 1.0f - d;
			const f32 mul0 = inv * inv;
			const f32 mul1 = 2.0f * d * inv;
			const f32 mul2 = d * d;

			return vector2d<T>((T) (X * mul0 + v2.X * mul1 + v3.X * mul2),
					(T) (Y * mul0 + v2.Y * mul1 + v3.Y * mul2));
		}

		//! Sets this vector to the linearly interpolated vector between a and b.
		template<class T>
		inline vector2d<T>& vector2d<T>::interpolate(const vector2d<T>& a,
				const vector2d<T>& b, f32 d)
		{
			X = (T) ((f32) b.X + ((a.X - b.X) * d));
			Y = (T) ((f32) b.Y + ((a.Y - b.Y) * d));
			return *this;
		}

	} // end namespace core
} // end namespace irrgame

//! Typedefs for vector2d
typedef irrgame::core::vector2d<f32> vector2df;
typedef irrgame::core::vector2d<s32> vector2di;

#endif

