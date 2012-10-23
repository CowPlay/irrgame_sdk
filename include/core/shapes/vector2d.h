// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_POINT_2D_H_INCLUDED__
#define __IRR_POINT_2D_H_INCLUDED__

#include "core/math/irrMath.h"
#include "core/shapes/dimension2d.h"

namespace irrgame
{
	namespace core
	{

		//! 2d vector template class with lots of operators and methods.
		/** As of Irrlicht 1.6, this class supercedes position2d, which should
		 be considered deprecated. */
		template<class T>
		class vector2d
		{
			public:
				static const vector2d& getEmpty(void)
				{
					static const vector2d empty;
					return empty;
				}
			public:
				//! Default constructor (null vector)
				vector2d() :
						_X(0), _Y(0)
				{
				}
				//! Constructor with two different values
				vector2d(T nx, T ny) :
						_X(nx), _Y(ny)
				{
				}
				//! Constructor with the same value for both members
				explicit vector2d(T n) :
						_X(n), _Y(n)
				{
				}
				//! Copy constructor
				vector2d(const vector2d<T>& other) :
						_X(other._X), _Y(other._Y)
				{
				}

				vector2d(const dimension2d<T>& other) :
						_X(other.Width), _Y(other.Height)
				{
				}

				// operators

				vector2d<T> operator-() const
				{
					return vector2d<T>(-_X, -_Y);
				}

				vector2d<T>& operator=(const vector2d<T>& other)
				{
					_X = other._X;
					_Y = other._Y;
					return *this;
				}

				vector2d<T>& operator=(const dimension2d<T>& other)
				{
					_X = other.Width;
					_Y = other.Height;
					return *this;
				}

				vector2d<T> operator+(const vector2d<T>& other) const
				{
					return vector2d<T>(_X + other._X, _Y + other._Y);
				}
				vector2d<T> operator+(const dimension2d<T>& other) const
				{
					return vector2d<T>(_X + other.Width, _Y + other.Height);
				}
				vector2d<T>& operator+=(const vector2d<T>& other)
				{
					_X += other._X;
					_Y += other._Y;
					return *this;
				}
				vector2d<T> operator+(const T v) const
				{
					return vector2d<T>(_X + v, _Y + v);
				}
				vector2d<T>& operator+=(const T v)
				{
					_X += v;
					_Y += v;
					return *this;
				}
				vector2d<T>& operator+=(const dimension2d<T>& other)
				{
					_X += other.Width;
					_Y += other.Height;
					return *this;
				}

				vector2d<T> operator-(const vector2d<T>& other) const
				{
					return vector2d<T>(_X - other._X, _Y - other._Y);
				}
				vector2d<T> operator-(const dimension2d<T>& other) const
				{
					return vector2d<T>(_X - other.Width, _Y - other.Height);
				}
				vector2d<T>& operator-=(const vector2d<T>& other)
				{
					_X -= other._X;
					_Y -= other._Y;
					return *this;
				}
				vector2d<T> operator-(const T v) const
				{
					return vector2d<T>(_X - v, _Y - v);
				}
				vector2d<T>& operator-=(const T v)
				{
					_X -= v;
					_Y -= v;
					return *this;
				}
				vector2d<T>& operator-=(const dimension2d<T>& other)
				{
					_X -= other.Width;
					_Y -= other.Height;
					return *this;
				}

				vector2d<T> operator*(const vector2d<T>& other) const
				{
					return vector2d<T>(_X * other._X, _Y * other._Y);
				}
				vector2d<T>& operator*=(const vector2d<T>& other)
				{
					_X *= other._X;
					_Y *= other._Y;
					return *this;
				}
				vector2d<T> operator*(const T v) const
				{
					return vector2d<T>(_X * v, _Y * v);
				}
				vector2d<T>& operator*=(const T v)
				{
					_X *= v;
					_Y *= v;
					return *this;
				}

				vector2d<T> operator/(const vector2d<T>& other) const
				{
					return vector2d<T>(_X / other._X, _Y / other._Y);
				}
				vector2d<T>& operator/=(const vector2d<T>& other)
				{
					_X /= other._X;
					_Y /= other._Y;
					return *this;
				}
				vector2d<T> operator/(const T v) const
				{
					return vector2d<T>(_X / v, _Y / v);
				}
				vector2d<T>& operator/=(const T v)
				{
					_X /= v;
					_Y /= v;
					return *this;
				}

				//! sort in order _X, _Y. Equality with rounding tolerance.
				bool operator<=(const vector2d<T>&other) const
				{
					return (_X < other._X || core::equals(_X, other._X))
							|| (core::equals(_X, other._X)
									&& (_Y < other._Y
											|| core::equals(_Y, other._Y)));
				}

				//! sort in order _X, _Y. Equality with rounding tolerance.
				bool operator>=(const vector2d<T>&other) const
				{
					return (_X > other._X || core::equals(_X, other._X))
							|| (core::equals(_X, other._X)
									&& (_Y > other._Y
											|| core::equals(_Y, other._Y)));
				}

				//! sort in order _X, _Y. Difference must be above rounding tolerance.
				bool operator<(const vector2d<T>&other) const
				{
					return (_X < other._X && !core::equals(_X, other._X))
							|| (core::equals(_X, other._X) && _Y < other._Y
									&& !core::equals(_Y, other._Y));
				}

				//! sort in order _X, _Y. Difference must be above rounding tolerance.
				bool operator>(const vector2d<T>&other) const
				{
					return (_X > other._X && !core::equals(_X, other._X))
							|| (core::equals(_X, other._X) && _Y > other._Y
									&& !core::equals(_Y, other._Y));
				}

				bool operator==(const vector2d<T>& other) const
				{
					return equals(other);
				}
				bool operator!=(const vector2d<T>& other) const
				{
					return !equals(other);
				}

				// functions

				//! Checks if this vector equals the other one.
				/** Takes floating point rounding errors into account.
				 \param other Vector to compare with.
				 \return True if the two vector are (almost) equal, else false. */
				bool equals(const vector2d<T>& other) const
				{
					return core::equals(_X, other._X)
							&& core::equals(_Y, other._Y);
				}

				vector2d<T>& set(T nx, T ny)
				{
					_X = nx;
					_Y = ny;
					return *this;
				}
				vector2d<T>& set(const vector2d<T>& p)
				{
					_X = p._X;
					_Y = p._Y;
					return *this;
				}

				//! Gets the length of the vector.
				/** \return The length of the vector. */
				T getLength() const
				{
					return core::squareroot(_X * _X + _Y * _Y);
				}

				//! Get the squared length of this vector
				/** This is useful because it is much faster than getLength().
				 \return The squared length of the vector. */
				T getLengthSQ() const
				{
					return _X * _X + _Y * _Y;
				}

				//! Get the dot product of this vector with another.
				/** \param other Other vector to take dot product with.
				 \return The dot product of the two vectors. */
				T dotProduct(const vector2d<T>& other) const
				{
					return _X * other._X + _Y * other._Y;
				}

				//! Gets distance from another point.
				/** Here, the vector is interpreted as a point in 2-dimensional space.
				 \param other Other vector to measure from.
				 \return Distance from other point. */
				T getDistanceFrom(const vector2d<T>& other) const
				{
					return vector2d<T>(_X - other._X, _Y - other._Y).getLength();
				}

				//! Returns squared distance from another point.
				/** Here, the vector is interpreted as a point in 2-dimensional space.
				 \param other Other vector to measure from.
				 \return Squared distance from other point. */
				T getDistanceFromSQ(const vector2d<T>& other) const
				{
					return vector2d<T>(_X - other._X, _Y - other._Y).getLengthSQ();
				}

				//! rotates the point anticlockwise around a center by an amount of degrees.
				/** \param degrees Amount of degrees to rotate by, anticlockwise.
				 \param center Rotation center.
				 \return This vector after transformation. */
				vector2d<T>& rotateBy(f32 degrees, const vector2d<T>& center =
						vector2d<T>())
				{
					degrees *= DEGTORAD;
					const f32 cs = cos(degrees);
					const f32 sn = sin(degrees);

					_X -= center._X;
					_Y -= center._Y;

					set((T) (_X * cs - _Y * sn), (T) (_X * sn + _Y * cs));

					_X += center._X;
					_Y += center._Y;
					return *this;
				}

				//! Normalize the vector.
				/** The null vector is left untouched.
				 \return Reference to this vector, after normalization. */
				vector2d<T>& normalize()
				{
					f32 length = (f32) (_X * _X + _Y * _Y);
					if (core::equals(length, 0.f))
						return *this;
					length = core::reciprocal_squareroot(length);
					_X = (T) (_X * length);
					_Y = (T) (_Y * length);
					return *this;
				}

				//! Calculates the angle of this vector in degrees in the trigonometric sense.
				/** 0 is to the right (3 o'clock), values increase counter-clockwise.
				 This method has been suggested by Pr3t3nd3r.
				 \return Returns a value between 0 and 360. */
				f32 getAngleTrig() const
				{
					if (_Y == 0)
						return _X < 0 ? 180 : 0;
					else if (_X == 0)
						return _Y < 0 ? 270 : 90;

					if (_Y > 0)
						if (_X > 0)
							return atan(_Y / _X) * RADTODEG;
						else
							return 180.0 - atan(_Y / -_X) * RADTODEG;
					else if (_X > 0)
						return 360.0 - atan(-_Y / _X) * RADTODEG;
					else
						return 180.0 + atan(-_Y / -_X) * RADTODEG;
				}

				//! Calculates the angle of this vector in degrees in the counter trigonometric sense.
				/** 0 is to the right (3 o'clock), values increase clockwise.
				 \return Returns a value between 0 and 360. */
				inline f32 getAngle() const
				{
					if (_Y == 0) // corrected thanks to a suggestion by Jox
						return _X < 0 ? 180 : 0;
					else if (_X == 0)
						return _Y < 0 ? 90 : 270;

					// don't use getLength here to avoid precision loss with s32 vectors
					f32 tmp = _Y / sqrt((f32) (_X * _X + _Y * _Y));
					tmp = atan(core::squareroot(1 - tmp * tmp) / tmp)
							* RADTODEG;

					if (_X > 0 && _Y > 0)
						return tmp + 270;
					else if (_X > 0 && _Y < 0)
						return tmp + 90;
					else if (_X < 0 && _Y < 0)
						return 90 - tmp;
					else if (_X < 0 && _Y > 0)
						return 270 - tmp;

					return tmp;
				}

				//! Calculates the angle between this vector and another one in degree.
				/** \param b Other vector to test with.
				 \return Returns a value between 0 and 90. */
				inline f32 getAngleWith(const vector2d<T>& b) const
				{
					f32 tmp = _X * b._X + _Y * b._Y;

					if (tmp == 0.0)
						return 90.0;

					tmp = tmp
							/ core::squareroot(
									(f32) ((_X * _X + _Y * _Y)
											* (b._X * b._X + b._Y * b._Y)));
					if (tmp < 0.0)
						tmp = -tmp;

					return atan(sqrt(1 - tmp * tmp) / tmp) * RADTODEG;
				}

				//! Returns if this vector interpreted as a point is on a line between two other points.
				/** It is assumed that the point is on the line.
				 \param begin Beginning vector to compare between.
				 \param end Ending vector to compare between.
				 \return True if this vector is between begin and end, false if not. */
				bool isBetweenPoints(const vector2d<T>& begin,
						const vector2d<T>& end) const
				{
					if (begin._X != end._X)
					{
						return ((begin._X <= _X && _X <= end._X)
								|| (begin._X >= _X && _X >= end._X));
					}
					else
					{
						return ((begin._Y <= _Y && _Y <= end._Y)
								|| (begin._Y >= _Y && _Y >= end._Y));
					}
				}

				//! Creates an interpolated vector between this vector and another vector.
				/** \param other The other vector to interpolate with.
				 \param d Interpolation value between 0.0f (all the other vector) and 1.0f (all this vector).
				 Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
				 \return An interpolated vector.  This vector is not modified. */
				vector2d<T> getInterpolated(const vector2d<T>& other,
						f32 d) const
				{
					f32 inv = 1.0f - d;
					return vector2d<T>((T) (other._X * inv + _X * d),
							(T) (other._Y * inv + _Y * d));
				}

				//! Creates a quadratically interpolated vector between this and two other vectors.
				/** \param v2 Second vector to interpolate with.
				 \param v3 Third vector to interpolate with (maximum at 1.0f)
				 \param d Interpolation value between 0.0f (all this vector) and 1.0f (all the 3rd vector).
				 Note that this is the opposite direction of interpolation to getInterpolated() and interpolate()
				 \return An interpolated vector. This vector is not modified. */
				vector2d<T> getInterpolated_quadratic(const vector2d<T>& v2,
						const vector2d<T>& v3, f32 d) const
				{
					// this*(1-d)*(1-d) + 2 * v2 * (1-d) + v3 * d * d;
					const f32 inv = 1.0f - d;
					const f32 mul0 = inv * inv;
					const f32 mul1 = 2.0f * d * inv;
					const f32 mul2 = d * d;

					return vector2d<T>(
							(T) (_X * mul0 + v2._X * mul1 + v3._X * mul2),
							(T) (_Y * mul0 + v2._Y * mul1 + v3._Y * mul2));
				}

				//! Sets this vector to the linearly interpolated vector between a and b.
				/** \param a first vector to interpolate with, maximum at 1.0f
				 \param b second vector to interpolate with, maximum at 0.0f
				 \param d Interpolation value between 0.0f (all vector b) and 1.0f (all vector a)
				 Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
				 */
				vector2d<T>& interpolate(const vector2d<T>& a,
						const vector2d<T>& b, f32 d)
				{
					_X = (T) ((f32) b._X + ((a._X - b._X) * d));
					_Y = (T) ((f32) b._Y + ((a._Y - b._Y) * d));
					return *this;
				}

				//! Getter\setter for _X coordinate of the vector
				T& X()
				{
					return _X;
				}

				//! Getter\setter for _Y coordinate of the vector
				T& Y()
				{
					return _Y;
				}

				//! Getter for _X coordinate of the const vector
				const T X() const
				{
					return _X;
				}

				//! Getter for _Y coordinate of the const vector
				const T Y() const
				{
					return _Y;
				}
			private:

				//! _X coordinate of vector.
				T _X;

				//! _Y coordinate of vector.
				T _Y;
		};

		template<class S, class T>
		vector2d<T> operator*(const S scalar, const vector2d<T>& vector)
		{
			return vector * scalar;
		}

		// These methods are declared in dimension2d, but need definitions of vector2d
		template<class T>
		dimension2d<T>::dimension2d(const vector2d<T>& other) :
				Width(other._X), Height(other._Y)
		{
		}

		template<class T>
		bool dimension2d<T>::operator==(const vector2d<T>& other) const
		{
			return Width == other._X && Height == other._Y;
		}

	} // end namespace core
} // end namespace irr

#endif

