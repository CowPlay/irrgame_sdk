// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_POINT_3D_H_INCLUDED__
#define __IRR_POINT_3D_H_INCLUDED__

#include "core/math/irrMath.h"
#include "threads/irrgameMonitor.h"

namespace irrgame
{
	namespace core
	{

		//! 3d vector template class with lots of operators and methods.
		/** The vector3d class is used in Irrlicht for three main purposes:
		 1) As a direction vector (most of the methods assume this).
		 2) As a position in 3d space (which is synonymous with a direction vector from the origin to this position).
		 3) To hold three Euler rotations, where _X is pitch, _Y is yaw and _Z is roll.
		 */
		template<class T>
		class vector3d
		{
			public:
				//! Returns empty string
				static const vector3d& getEmpty(void);

			public:
				//! Default constructor (null vector).
				vector3d();

				//! Constructor with three different values
				vector3d(T nx, T ny, T nz);

				//! Constructor with the same value for all elements
				explicit vector3d(T n);

				//! Copy constructor
				vector3d(const vector3d<T>& other);

				//! Assignment operator
				vector3d<T>& operator=(const vector3d<T>& other);

				// operators
				vector3d<T> operator-() const;
				vector3d<T> operator+(const vector3d<T>& other) const;
				vector3d<T> operator+(const T val) const;
				vector3d<T>& operator+=(const vector3d<T>& other);
				vector3d<T>& operator+=(const T val);
				vector3d<T> operator-(const vector3d<T>& other) const;
				vector3d<T> operator-(const T val) const;
				vector3d<T>& operator-=(const vector3d<T>& other);
				vector3d<T>& operator-=(const T val);
				vector3d<T> operator*(const vector3d<T>& other) const;
				vector3d<T> operator*(const T v) const;
				vector3d<T>& operator*=(const vector3d<T>& other);
				vector3d<T>& operator*=(const T v);
				vector3d<T> operator/(const vector3d<T>& other) const;
				vector3d<T> operator/(const T v) const;
				vector3d<T>& operator/=(const vector3d<T>& other);
				vector3d<T>& operator/=(const T v);

				//! sort in order _X, _Y, _Z. Equality with rounding tolerance.
				bool operator<=(const vector3d<T>&other) const;
				//! sort in order _X, _Y, _Z. Equality with rounding tolerance.
				bool operator>=(const vector3d<T>&other) const;

				//! sort in order _X, _Y, _Z. Difference must be above rounding tolerance.
				bool operator<(const vector3d<T>&other) const;
				//! sort in order _X, _Y, _Z. Difference must be above rounding tolerance.
				bool operator>(const vector3d<T>&other) const;

				//! use weak float compare
				bool operator==(const vector3d<T>& other) const;
				bool operator!=(const vector3d<T>& other) const;

				// functions

				//! returns if this vector equals the other one, taking floating point rounding errors into account
				bool equals(const vector3d<T>& other, const T tolerance =
						(T) ROUNDING_ERROR_f32) const;

				vector3d<T>& set(const T nx, const T ny, const T nz);
				vector3d<T>& set(const vector3d<T>& p);

				//! Get length of the vector.
				T getLength() const;

				//! Get squared length of the vector.
				/** This is useful because it is much faster than getLength().
				 \return Squared length of the vector. */
				T getLengthSQ() const;

				//! Get the dot product with another vector.
				T dotProduct(const vector3d<T>& other) const;

				//! Get distance from another point.
				/** Here, the vector is interpreted as point in 3 dimensional space. */
				T getDistanceFrom(const vector3d<T>& other) const;

				//! Returns squared distance from another point.
				/** Here, the vector is interpreted as point in 3 dimensional space. */
				T getDistanceFromSQ(const vector3d<T>& other) const;

				//! Calculates the cross product with another vector.
				/** \param p Vector to multiply with.
				 \return Crossproduct of this vector with p. */
				vector3d<T> crossProduct(const vector3d<T>& p) const;

				//! Returns if this vector interpreted as a point is on a line between two other points.
				/** It is assumed that the point is on the line.
				 \param begin Beginning vector to compare between.
				 \param end Ending vector to compare between.
				 \return True if this vector is between begin and end, false if not. */
				bool isBetweenPoints(const vector3d<T>& begin,
						const vector3d<T>& end) const;

				//! Normalizes the vector.
				/** In case of the 0 vector the result is still 0, otherwise
				 the length of the vector will be 1.
				 \return Reference to this vector after normalization. */
				vector3d<T>& normalize();

				//! Sets the length of the vector to a new value
				vector3d<T>& setLength(T newlength);

				//! Inverts the vector.
				vector3d<T>& invert();

				//! Rotates the vector by a specified number of degrees around the _Y axis and the specified center.
				/** \param degrees Number of degrees to rotate around the _Y axis.
				 \param center The center of the rotation. */
				void rotate_X_ZBy(f32 degrees, const vector3d<T>& center =
						vector3d<T>());

				//! Rotates the vector by a specified number of degrees around the _Z axis and the specified center.
				/** \param degrees: Number of degrees to rotate around the _Z axis.
				 \param center: The center of the rotation. */
				void rotate_X_YBy(f32 degrees, const vector3d<T>& center =
						vector3d<T>());

				//! Rotates the vector by a specified number of degrees around the _X axis and the specified center.
				/** \param degrees: Number of degrees to rotate around the _X axis.
				 \param center: The center of the rotation. */
				void rotate_Y_ZBy(f32 degrees, const vector3d<T>& center =
						vector3d<T>());

				//! Creates an interpolated vector between this vector and another vector.
				/** \param other The other vector to interpolate with.
				 \param d Interpolation value between 0.0f (all the other vector) and 1.0f (all this vector).
				 Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
				 \return An interpolated vector.  This vector is not modified. */
				vector3d<T> getInterpolated(const vector3d<T>& other,
						f32 d) const;

				//! Creates a quadratically interpolated vector between this and two other vectors.
				/** \param v2 Second vector to interpolate with.
				 \param v3 Third vector to interpolate with (maximum at 1.0f)
				 \param d Interpolation value between 0.0f (all this vector) and 1.0f (all the 3rd vector).
				 Note that this is the opposite direction of interpolation to getInterpolated() and interpolate()
				 \return An interpolated vector. This vector is not modified. */
				vector3d<T> getInterpolated_quadratic(const vector3d<T>& v2,
						const vector3d<T>& v3, f32 d) const
				{
					// this*(1-d)*(1-d) + 2 * v2 * (1-d) + v3 * d * d;
					const f32 inv = (T) 1.0 - d;
					const f32 mul0 = inv * inv;
					const f32 mul1 = (T) 2.0 * d * inv;
					const f32 mul2 = d * d;

					return vector3d<T>(
							(T) (_X * mul0 + v2._X * mul1 + v3._X * mul2),
							(T) (_Y * mul0 + v2._Y * mul1 + v3._Y * mul2),
							(T) (_Z * mul0 + v2._Z * mul1 + v3._Z * mul2));
				}

				//! Sets this vector to the linearly interpolated vector between a and b.
				/** \param a first vector to interpolate with, maximum at 1.0f
				 \param b second vector to interpolate with, maximum at 0.0f
				 \param d Interpolation value between 0.0f (all vector b) and 1.0f (all vector a)
				 Note that this is the opposite direction of interpolation to getInterpolated_quadratic()
				 */
				vector3d<T>& interpolate(const vector3d<T>& a,
						const vector3d<T>& b, f32 d)
				{

					_X = (T) ((f32) b._X + ((a._X - b._X) * d));
					_Y = (T) ((f32) b._Y + ((a._Y - b._Y) * d));
					_Z = (T) ((f32) b._Z + ((a._Z - b._Z) * d));

					return *this;
				}

				//! Get the rotations that would make a (0,0,1) direction vector point in the same direction as this direction vector.
				/** Thanks to Arras on the Irrlicht forums for this method.  This utility method is very useful for
				 orienting scene nodes towards specific targets.  For example, if this vector represents the difference
				 between two scene nodes, then applying the result of getHorizontalAngle() to one scene node will point
				 it at the other one.
				 Example code:
				 // Where target and seeker are of type ISceneNode*
				 const vector3df toTarget(target->getAbsolutePosition() - seeker->getAbsolutePosition());
				 const vector3df requiredRotation = toTarget.getHorizontalAngle();
				 seeker->setRotation(requiredRotation);

				 \return A rotation vector containing the _X (pitch) and _Y (raw) rotations (in degrees) that when applied to a
				 +_Z (e.g. 0, 0, 1) direction vector would make it point in the same direction as this vector. The _Z (roll) rotation
				 is always 0, since two Euler rotations are sufficient to point in any given direction. */
				vector3d<T> getHorizontalAngle() const;

				//! Get the spherical coordinate angles
				/** This returns Euler degrees for the point represented by
				 this vector.  The calculation assumes the pole at (0,1,0) and
				 returns the angles in _X and _Y.
				 */
				vector3d<T> getSphericalCoordinateAngles();

				//! Builds a direction vector from (this) rotation vector.
				/** This vector is assumed to be a rotation vector composed of 3 Euler angle rotations, in degrees.
				 The implementation performs the same calculations as using a matrix to do the rotation.

				 \param[in] forwards  The direction representing "forwards" which will be rotated by this vector.
				 If you do not provide a direction, then the +_Z axis (0, 0, 1) will be assumed to be forwards.
				 \return A direction vector calculated by rotating the forwards direction by the 3 Euler angles
				 (in degrees) represented by this vector. */
				vector3d<T> rotationToDirection(const vector3d<T> & forwards =
						vector3d<T>(0, 0, 1)) const;

				//! Fills an array of 4 values with the vector data (usually floats).
				/** Useful for setting in shader constants for example. The fourth value
				 will always be 0. */
				void getAs4Values(T* array) const;

				//getters/setters

				//! Getter\setter for _X coordinate of the vector
				T& X();
				//! Getter\setter for _Y coordinate of the vector
				T& Y();
				//! Getter\setter for _Z coordinate of the vector
				T& Z();

				//! Getter for _X coordinate of the const vector
				const T X() const;
				//! Getter for _Y coordinate of the const vector
				const T Y() const;
				//! Getter for _Z coordinate of the const vector
				const T Z() const;

			public:
				T _X;
				T _Y;
				T _Z;

			private:

				threads::irrgameMonitor* Monitor;
		};

		//! Returns empty string
		template<class T>
		inline const vector3d<T>& vector3d<T>::getEmpty(void)
		{
			static const vector3d<T> empty;
			return empty;
		}

		//! Default constructor (null vector).
		template<class T>
		inline vector3d<T>::vector3d() :
				_X(0), _Y(0), _Z(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
		}

		//! Constructor with three different values
		template<class T>
		inline vector3d<T>::vector3d(T nx, T ny, T nz) :
				_X(nx), _Y(ny), _Z(nz), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
		}

		//! Constructor with the same value for all elements
		template<class T>
		inline vector3d<T>::vector3d(T n) :
				_X(0), _Y(0), _Z(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
		}

		//! Copy constructor
		template<class T>
		inline vector3d<T>::vector3d(const vector3d<T>& other) :
				Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
			*this = other;
		}

		//! Assignment operator
		template<class T>
		inline vector3d<T>& vector3d<T>::operator=(const vector3d<T>& other)
		{
			//handle self-assignment
			if (this == &other)
				return *this;

			Monitor->enter();
			other.Monitor->enter();

			_X = other._X;
			_Y = other._Y;
			_Z = other._Z;

			Monitor->exit();
			other.Monitor->exit();

			return *this;
		}

		// operators
		template<class T>
		inline vector3d<T> vector3d<T>::operator-() const
		{
			Monitor->enter();
			vector3d<T> result = vector3d<T>(-_X, -_Y, -_Z);
			Monitor->exit();

			return result;
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator+(
				const vector3d<T>& other) const
		{
			bool selfAppending = false;

			//handle self-appending
			if (this == &other)
				selfAppending = true;

			if (!selfAppending)
				other.Monitor->enter();
			Monitor->enter();

			vector3d<T> result = vector3d<T>(_X + other._X, _Y + other._Y,
					_Z + other._Z);

			if (!selfAppending)
				other.Monitor->exit();
			Monitor->exit();

			return result;
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator+(const T val) const
		{
			Monitor->enter();
			vector3d<T> result = vector3d<T>(_X + val, _Y + val, _Z + val);
			Monitor->exit();

			return result;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator+=(const vector3d<T>& other)
		{
			bool selfAppending = false;

			//handle self-appending
			if (this == &other)
				selfAppending = true;

			if (!selfAppending)
				other.Monitor->enter();
			Monitor->enter();

			_X += other._X;
			_Y += other._Y;
			_Z += other._Z;

			if (!selfAppending)
				other.Monitor->exit();
			Monitor->exit();

			return *this;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator+=(const T val)
		{
			Monitor->enter();
			_X += val;
			_Y += val;
			_Z += val;
			Monitor->exit();

			return *this;
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator-(
				const vector3d<T>& other) const
		{
			bool selfSubtracting = false;

			if (this == &other)
				selfSubtracting = true;

			if (!selfSubtracting)
				other.Monitor->enter();
			Monitor->enter();

			vector3d<T> result = vector3d<T>(_X - other._X, _Y - other._Y,
					_Z - other._Z);

			if (!selfSubtracting)
				other.Monitor->exit();
			Monitor->exit();

			return result;
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator-(const T val) const
		{
			Monitor->enter();
			vector3d<T> result = vector3d<T>(_X - val, _Y - val, _Z - val);
			Monitor->exit();

			return result;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator-=(const vector3d<T>& other)
		{
			bool selfSubtracting = false;

			if (this == &other)
				selfSubtracting = true;

			if (!selfSubtracting)
				other.Monitor->enter();
			Monitor->enter();

			_X -= other._X;
			_Y -= other._Y;
			_Z -= other._Z;

			if (!selfSubtracting)
				other.Monitor->exit();
			Monitor->exit();

			return *this;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator-=(const T val)
		{
			Monitor->enter();
			_X -= val;
			_Y -= val;
			_Z -= val;
			Monitor->enter();

			return *this;
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator*(
				const vector3d<T>& other) const
		{
			bool selfMultiplication = false;

			if (this == &other)
				selfMultiplication = true;

			if (!selfMultiplication)
				other.Monitor->enter();
			Monitor->enter();

			vector3d<T> result = vector3d<T>(_X * other._X, _Y * other._Y,
					_Z * other._Z);

			if (!selfMultiplication)
				other.Monitor->exit();
			Monitor->exit();

			return result;
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator*(const T v) const
		{
			Monitor->enter();
			vector3d<T> result = vector3d<T>(_X * v, _Y * v, _Z * v);
			Monitor->exit();

			return result;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator*=(const vector3d<T>& other)
		{
			bool selfMultiplication = false;

			if (this == &other)
				selfMultiplication = true;

			if (!selfMultiplication)
				other.Monitor->enter();
			Monitor->enter();

			_X *= other._X;
			_Y *= other._Y;
			_Z *= other._Z;

			if (!selfMultiplication)
				other.Monitor->exit();
			Monitor->exit();

			return *this;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator*=(const T v)
		{
			Monitor->enter();
			_X *= v;
			_Y *= v;
			_Z *= v;
			Monitor->exit();

			return *this;
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator/(
				const vector3d<T>& other) const
		{
			bool selfDivision = false;

			if (this == &other)
				selfDivision = true;

			if (!selfDivision)
				other.Monitor->enter();
			Monitor->enter();

			IRR_ASSERT(other._X != 0 && other._Y != 0 && other._Z != 0);

			vector3d<T> result = vector3d<T>(_X / other._X, _Y / other._Y,
					_Z / other._Z);

			if (!selfDivision)
				other.Monitor->exit();
			Monitor->exit();

			return result;
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator/(const T v) const
		{
			IRR_ASSERT(v != 0);

			Monitor->enter();
			vector3d<T> result = vector3d<T>((T) _X / v, (T) _Y / v,
					(T) _Z / v);
			Monitor->exit();

			return result;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator/=(const vector3d<T>& other)
		{
			bool selfDivision = false;

			if (this == &other)
				selfDivision = true;

			if (!selfDivision)
				other.Monitor->enter();
			Monitor->enter();

			IRR_ASSERT(other._X != 0 && other._Y != 0 && other._Z != 0);

			_X /= other._X;
			_Y /= other._Y;
			_Z /= other._Z;

			if (!selfDivision)
				other.Monitor->exit();
			Monitor->exit();

			return *this;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator/=(const T v)
		{
			IRR_ASSERT(v != 0);

			Monitor->enter();
			_X /= v;
			_Y /= v;
			_Z /= v;
			Monitor->exit();

			return *this;
		}

		//! sort in order _X, _Y, _Z. Equality with rounding tolerance.
		template<class T>
		inline bool vector3d<T>::operator<=(const vector3d<T>&other) const
		{
			if (this == &other)
				return true;

			Monitor->enter();
			other.Monitor->enter();

			bool result = (_X < other._X || core::equals(_X, other._X))
					|| (core::equals(_X, other._X)
							&& (_Y < other._Y || core::equals(_Y, other._Y)))
					|| (core::equals(_X, other._X) && core::equals(_Y, other._Y)
							&& (_Z < other._Z || core::equals(_Z, other._Z)));

			Monitor->exit();
			other.Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! sort in order _X, _Y, _Z. Equality with rounding tolerance.
		template<class T>
		inline bool vector3d<T>::operator>=(const vector3d<T>&other) const
		{
			if (this == &other)
				return true;

			Monitor->enter();
			other.Monitor->enter();

			bool result = (_X > other._X || core::equals(_X, other._X))
					|| (core::equals(_X, other._X)
							&& (_Y > other._Y || core::equals(_Y, other._Y)))
					|| (core::equals(_X, other._X) && core::equals(_Y, other._Y)
							&& (_Z > other._Z || core::equals(_Z, other._Z)));

			Monitor->exit();
			other.Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! sort in order _X, _Y, _Z. Difference must be above rounding tolerance.
		template<class T>
		inline bool vector3d<T>::operator<(const vector3d<T>&other) const
		{
			if (this == &other)
			{
				_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
				return false;
			}

			Monitor->enter();
			other.Monitor->enter();

			bool result = (_X < other._X && !core::equals(_X, other._X))
					|| (core::equals(_X, other._X) && _Y < other._Y
							&& !core::equals(_Y, other._Y))
					|| (core::equals(_X, other._X) && core::equals(_Y, other._Y)
							&& _Z < other._Z && !core::equals(_Z, other._Z));

			Monitor->exit();
			other.Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! sort in order _X, _Y, _Z. Difference must be above rounding tolerance.
		template<class T>
		inline bool vector3d<T>::operator>(const vector3d<T>&other) const
		{
			if (this == &other)
			{
				_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
				return false;
			}

			Monitor->enter();
			other.Monitor->enter();

			bool result = (_X > other._X && !core::equals(_X, other._X))
					|| (core::equals(_X, other._X) && _Y > other._Y
							&& !core::equals(_Y, other._Y))
					|| (core::equals(_X, other._X) && core::equals(_Y, other._Y)
							&& _Z > other._Z && !core::equals(_Z, other._Z));
			Monitor->exit();
			other.Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! use weak float compare
		template<class T>
		inline bool vector3d<T>::operator==(const vector3d<T>& other) const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return this->equals(other);
		}

		template<class T>
		inline bool vector3d<T>::operator!=(const vector3d<T>& other) const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return !this->equals(other);
		}

		//! returns if this vector equals the other one, taking floating point rounding errors into account
		template<class T>
		inline bool vector3d<T>::equals(const vector3d<T>& other,
				const T tolerance) const
		{
			return core::equals(_X, other._X, tolerance)
					&& core::equals(_Y, other._Y, tolerance)
					&& core::equals(_Z, other._Z, tolerance);
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::set(const T nx, const T ny, const T nz)
		{
			Monitor->enter();
			_X = nx;
			_Y = ny;
			_Z = nz;
			Monitor->exit();

			return *this;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::set(const vector3d<T>& p)
		{
			return (*this = p);
		}

		//! Get length of the vector.
		template<class T>
		inline T vector3d<T>::getLength() const
		{
			Monitor->enter();
			T result = core::squareroot(_X * _X + _Y * _Y + _Z * _Z);
			Monitor->exit();

			return result;
		}

		//! Get squared length of the vector.
		template<class T>
		inline T vector3d<T>::getLengthSQ() const
		{
			Monitor->enter();
			T result = _X * _X + _Y * _Y + _Z * _Z;
			Monitor->exit();

			return result;
		}

		//! Get the dot product with another vector.
		template<class T>
		inline T vector3d<T>::dotProduct(const vector3d<T>& other) const
		{
			if (this == &other)
				return getLengthSQ();

			Monitor->enter();
			other.Monitor->enter();

			T result = _X * other._X + _Y * other._Y + _Z * other._Z;

			Monitor->exit();
			other.Monitor->exit();

			return result;
		}

		//! Get distance from another point.
		template<class T>
		inline T vector3d<T>::getDistanceFrom(const vector3d<T>& other) const
		{
			T result = 0;

			if (this == &other)
				return result;

			Monitor->enter();
			other.Monitor->enter();

			result =
					vector3d<T>(_X - other._X, _Y - other._Y, _Z - other._Z).getLength();

			Monitor->exit();
			other.Monitor->exit();

			return result;
		}

		//! Returns squared distance from another point.
		template<class T>
		inline T vector3d<T>::getDistanceFromSQ(const vector3d<T>& other) const
		{
			T result = 0;

			if (this == &other)
				return result;

			Monitor->enter();
			other.Monitor->enter();

			result =
					vector3d<T>(_X - other._X, _Y - other._Y, _Z - other._Z).getLengthSQ();

			Monitor->exit();
			other.Monitor->exit();

			return result;
		}

		//! Calculates the cross product with another vector.
		template<class T>
		inline vector3d<T> vector3d<T>::crossProduct(const vector3d<T>& p) const
		{
			bool selfCrossProduct = false;

			if (this == &p)
				selfCrossProduct = true;

			Monitor->enter();
			if (!selfCrossProduct)
				p.Monitor->enter();

			vector3d<T> result = vector3d<T>(_Y * p._Z - _Z * p._Y,
					_Z * p._X - _X * p._Z, _X * p._Y - _Y * p._X);

			Monitor->exit();
			if (!selfCrossProduct)
				p.Monitor->exit();

			return result;
		}

		//! Returns if this vector interpreted as a point is on a line between two other points.
		template<class T>
		inline bool vector3d<T>::isBetweenPoints(const vector3d<T>& begin,
				const vector3d<T>& end) const
		{
			const T f;

			if (&begin == &end)
				f = 0;
			else
			{
				begin.Monitor->enter();
				end.Monitor->enter();

				f = (end - begin).getLengthSQ();

				begin.Monitor->exit();
				end.Monitor->exit();

			}

			bool result = getDistanceFromSQ(begin) <= f
					&& getDistanceFromSQ(end) <= f;

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! Normalizes the vector.
		template<class T>
		inline vector3d<T>& vector3d<T>::normalize()
		{
			Monitor->enter();

			f32 length = _X * _X + _Y * _Y + _Z * _Z;

			if (core::equals(length, 0.0)) // this check isn't an optimization but prevents getting NAN in the sqrt.
			{
				Monitor->exit();
				return *this;
			}

			length = core::reciprocal_squareroot(length);

			_X = (T) (_X * length);
			_Y = (T) (_Y * length);
			_Z = (T) (_Z * length);

			Monitor->exit();

			return *this;
		}

		//! Sets the length of the vector to a new value
		template<class T>
		inline vector3d<T>& vector3d<T>::setLength(T newlength)
		{
			normalize();
			return (*this *= newlength);
		}

		//! Inverts the vector.
		template<class T>
		inline vector3d<T>& vector3d<T>::invert()
		{
			Monitor->enter();

			_X *= -1;
			_Y *= -1;
			_Z *= -1;

			Monitor->exit();

			return *this;
		}

		//! Rotates the vector by a specified number of degrees around the _Y axis and the specified center.
		template<class T>
		inline void vector3d<T>::rotate_X_ZBy(f32 degrees,
				const vector3d<T>& center)
		{
			if (this == &center)
				return;

			Monitor->enter();
			center.Monitor->enter();

			degrees *= DEGTORAD;
			f32 cs = cos(degrees);
			f32 sn = sin(degrees);
			_X -= center._X;
			_Z -= center._Z;

			_X = (T) (_X * cs - _Z * sn);
			_Z = (T) (_X * sn + _Z * cs);

			_X += center._X;
			_Z += center._Z;

			Monitor->exit();
			center.Monitor->exit();
		}

		//! Rotates the vector by a specified number of degrees around the _Z axis and the specified center.
		template<class T>
		inline void vector3d<T>::rotate_X_YBy(f32 degrees,
				const vector3d<T>& center)
		{
			if (this == &center)
				return;

			Monitor->enter();
			center.Monitor->enter();

			degrees *= DEGTORAD;
			f32 cs = cos(degrees);
			f32 sn = sin(degrees);

			_X -= center._X;
			_Y -= center._Y;

			_X = (T) (_X * cs - _Y * sn);
			_Y = (T) (_X * sn + _Y * cs);

			_X += center._X;
			_Y += center._Y;

			Monitor->exit();
			center.Monitor->exit();
		}

		//! Rotates the vector by a specified number of degrees around the _X axis and the specified center.
		template<class T>
		inline void vector3d<T>::rotate_Y_ZBy(f32 degrees,
				const vector3d<T>& center)
		{
			if (this == &center)
				return;

			Monitor->enter();
			center.Monitor->enter();

			degrees *= DEGTORAD;
			f32 cs = cos(degrees);
			f32 sn = sin(degrees);
			_Z -= center._Z;
			_Y -= center._Y;

			_Y = (T) (_Y * cs - _Z * sn);
			_Z = (T) (_Y * sn + _Z * cs);

			_Z += center._Z;
			_Y += center._Y;

			Monitor->exit();
			center.Monitor->exit();
		}

		//! Creates an interpolated vector between this vector and another vector.
		template<class T>
		inline vector3d<T> vector3d<T>::getInterpolated(
				const vector3d<T>& other, f32 d) const
		{
			if (this == &other)
				return *this;

			Monitor->enter();
			other.Monitor->enter();

			const f32 inv = 1.0 - d;

			vector3d<T> result = vector3d<T>((T) (other._X * inv + _X * d),
					(T) (other._Y * inv + _Y * d),
					(T) (other._Z * inv + _Z * d));

			Monitor->exit();
			other.Monitor->exit();

			return result;
		}

		//! Get the rotations that would make a (0,0,1) direction vector point in the same direction as this direction vector.
		template<class T>
		inline vector3d<T> vector3d<T>::getHorizontalAngle() const
		{
			vector3d<T> result;

			Monitor->enter();

			const f32 tmp = (atan2((f32) _X, (f32) _Z) * RADTODEG);
			result._Y = (T) tmp;

			if (result._Y < 0)
				result._Y += 360;
			if (result._Y >= 360)
				result._Y -= 360;

			const f32 z1 = core::squareroot(_X * _X + _Z * _Z);

			result._X = (T) (atan2((f32) z1, (f32) _Y) * RADTODEG - 90.0);

			if (result._X < 0)
				result._X += 360;
			if (result._X >= 360)
				result._X -= 360;

			Monitor->exit();

			return result;
		}

		//! Get the spherical coordinate angles
		template<class T>
		inline vector3d<T> vector3d<T>::getSphericalCoordinateAngles()
		{
			vector3d<T> result;

			Monitor->enter();

			const f32 length = _X * _X + _Y * _Y + _Z * _Z;

			if (length)
			{
				if (_X != 0)
				{
					result._Y = (T) (atan2((f32) _Z, (f32) _X) * RADTODEG);
				}
				else if (_Z < 0)
					result._Y = 180;

				result._X = (T) (acos(_Y * core::reciprocal_squareroot(length))
						* RADTODEG);
			}

			Monitor->exit();

			return result;
		}

		//! Builds a direction vector from (this) rotation vector.
		//TODO: check forwards and adds monitor for him
		template<class T>
		inline vector3d<T> vector3d<T>::rotationToDirection(
				const vector3d<T>& forwards) const
		{
			Monitor->enter();

			const f32 cr = cos(core::DEGTORAD * _X);
			const f32 sr = sin(core::DEGTORAD * _X);
			const f32 cp = cos(core::DEGTORAD * _Y);
			const f32 sp = sin(core::DEGTORAD * _Y);
			const f32 cy = cos(core::DEGTORAD * _Z);
			const f32 sy = sin(core::DEGTORAD * _Z);

			const f32 srsp = sr * sp;
			const f32 crsp = cr * sp;

			const f32 pseudoMatrix[] =
			{ (cp * cy), (cp * sy), (-sp), (srsp * cy - cr * sy), (srsp * sy
					+ cr * cy), (sr * cp), (crsp * cy + sr * sy), (crsp * sy
					- sr * cy), (cr * cp) };

			vector3d<T> result = vector3d<T>(
					(T) (forwards._X * pseudoMatrix[0]
							+ forwards._Y * pseudoMatrix[3]
							+ forwards._Z * pseudoMatrix[6]),
					(T) (forwards._X * pseudoMatrix[1]
							+ forwards._Y * pseudoMatrix[4]
							+ forwards._Z * pseudoMatrix[7]),
					(T) (forwards._X * pseudoMatrix[2]
							+ forwards._Y * pseudoMatrix[5]
							+ forwards._Z * pseudoMatrix[8]));

			Monitor->exit();

			return result;
		}

		//! Fills an array of 4 values with the vector data (usually floats).
		template<class T>
		inline void vector3d<T>::getAs4Values(T* array) const
		{
			Monitor->enter();

			array[0] = _X;
			array[1] = _Y;
			array[2] = _Z;
			array[3] = 0;

			Monitor->exit();
		}

		//getters/setters

		//! Getter\setter for _X coordinate of the vector
		template<class T>
		inline T& vector3d<T>::X()
		{
			Monitor->enter();
			T& result = _X;
			Monitor->exit();

			return result;
		}

		//! Getter\setter for _Y coordinate of the vector
		template<class T>
		inline T& vector3d<T>::Y()
		{
			Monitor->enter();
			T& result = _Y;
			Monitor->exit();

			return result;
		}

		//! Getter\setter for _Z coordinate of the vector
		template<class T>
		inline T& vector3d<T>::Z()
		{
			Monitor->enter();
			T& result = _Z;
			Monitor->exit();

			return result;
		}

		//! Getter for _X coordinate of the const vector
		template<class T>
		inline const T vector3d<T>::X() const
		{
			Monitor->enter();
			const T result = _X;
			Monitor->exit();

			return result;
		}

		//! Getter for _Y coordinate of the const vector
		template<class T>
		inline const T vector3d<T>::Y() const
		{
			Monitor->enter();
			const T result = _Y;
			Monitor->exit();

			return result;
		}

		//! Getter for _Z coordinate of the const vector
		template<class T>
		inline const T vector3d<T>::Z() const
		{
			Monitor->enter();
			const T result = _Z;
			Monitor->exit();

			return result;
		}

//		//TODO: review this funcs. Mb need delete.
//		//! partial specialization for integer vectors
//		// Implementor note: inline keyword needed due to template specialization for s32. Otherwise put specialization into a .cpp
//		template<>
//		inline vector3d<s32> vector3d<s32>::operator /(s32 val) const
//		{
//			Monitor->enter();
//			vector3d<s32> result = vector3d<s32>(_X / val, _Y / val, _Z / val);
//			Monitor->exit();
//
//			return result;
//		}
//
//		template<>
//		inline vector3d<s32>& vector3d<s32>::operator /=(s32 val)
//		{
//			_X /= val;
//			_Y /= val;
//			_Z /= val;
//			return *this;
//		}
//
//		//! Function multiplying a scalar and a vector component-wise.
//		template<class S, class T>
//		vector3d<T> operator*(const S scalar, const vector3d<T>& vector)
//		{
//			return vector * scalar;
//		}

	}// end namespace core
} // end namespace irr

//! Typedefs for vector3d
typedef irrgame::core::vector3d<f32> vector3df;
typedef irrgame::core::vector3d<s32> vector3di;

#endif

