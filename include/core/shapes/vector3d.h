// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include "core/math/SharedFastMath.h"

namespace irrgame
{
	namespace core
	{

		//! 3d vector template class with lots of operators and methods.
		/** The vector3d class is used in Irrlicht for three main purposes:
		 1) As a direction vector (most of the methods assume this).
		 2) As a position in 3d space (which is synonymous with a direction vector from the origin to this position).
		 3) To hold three Euler rotations, where X is pitch, Y is yaw and Z is roll.
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

				//! sort in order X, Y, Z. Equality with rounding tolerance.
				bool operator<=(const vector3d<T>&other) const;
				//! sort in order X, Y, Z. Equality with rounding tolerance.
				bool operator>=(const vector3d<T>&other) const;

				//! sort in order X, Y, Z. Difference must be above rounding tolerance.
				bool operator<(const vector3d<T>&other) const;
				//! sort in order X, Y, Z. Difference must be above rounding tolerance.
				bool operator>(const vector3d<T>&other) const;

				//! use weak float compare
				bool operator==(const vector3d<T>& other) const;
				bool operator!=(const vector3d<T>& other) const;

				// functions

				//! returns if this vector equals the other one, taking floating point rounding errors into account
				bool equals(const vector3d<T>& other, const T tolerance =
						(T) SharedMath::RoundErrF32) const;

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

				//! Rotates the vector by a specified number of degrees around the Y axis and the specified center.
				/** \param degrees Number of degrees to rotate around the Y axis.
				 \param center The center of the rotation. */
				void rotateXZBy(f32 degrees, const vector3d<T>& center =
						vector3d<T>());

				//! Rotates the vector by a specified number of degrees around the Z axis and the specified center.
				/** \param degrees: Number of degrees to rotate around the Z axis.
				 \param center: The center of the rotation. */
				void rotateXYBy(f32 degrees, const vector3d<T>& center =
						vector3d<T>());

				//! Rotates the vector by a specified number of degrees around the X axis and the specified center.
				/** \param degrees: Number of degrees to rotate around the X axis.
				 \param center: The center of the rotation. */
				void rotateYZBy(f32 degrees, const vector3d<T>& center =
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
							(T) (X * mul0 + v2.X * mul1 + v3.X * mul2),
							(T) (Y * mul0 + v2.Y * mul1 + v3.Y * mul2),
							(T) (Z * mul0 + v2.Z * mul1 + v3.Z * mul2));
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

					X = (T) ((f32) b.X + ((a.X - b.X) * d));
					Y = (T) ((f32) b.Y + ((a.Y - b.Y) * d));
					Z = (T) ((f32) b.Z + ((a.Z - b.Z) * d));

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

				 \return A rotation vector containing the X (pitch) and Y (raw) rotations (in degrees) that when applied to a
				 +Z (e.g. 0, 0, 1) direction vector would make it point in the same direction as this vector. The Z (roll) rotation
				 is always 0, since two Euler rotations are sufficient to point in any given direction. */
				vector3d<T> getHorizontalAngle() const;

				//! Get the spherical coordinate angles
				/** This returns Euler degrees for the point represented by
				 this vector.  The calculation assumes the pole at (0,1,0) and
				 returns the angles in X and Y.
				 */
				vector3d<T> getSphericalCoordinateAngles();

				//! Builds a direction vector from (this) rotation vector.
				/** This vector is assumed to be a rotation vector composed of 3 Euler angle rotations, in degrees.
				 The implementation performs the same calculations as using a matrix to do the rotation.

				 \param[in] forwards  The direction representing "forwards" which will be rotated by this vector.
				 If you do not provide a direction, then the +Z axis (0, 0, 1) will be assumed to be forwards.
				 \return A direction vector calculated by rotating the forwards direction by the 3 Euler angles
				 (in degrees) represented by this vector. */
				vector3d<T> rotationToDirection(const vector3d<T> & forwards =
						vector3d<T>(0, 0, 1)) const;

				//! Fills an array of 4 values with the vector data (usually floats).
				/** Useful for setting in shader constants for example. The fourth value
				 will always be 0. */
				void getAs4Values(T* array) const;

			public:
				T X;
				T Y;
				T Z;
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
				X(0), Y(0), Z(0)
		{
		}

		//! Constructor with three different values
		template<class T>
		inline vector3d<T>::vector3d(T nx, T ny, T nz) :
				X(nx), Y(ny), Z(nz)
		{
		}

		//! Constructor with the same value for all elements
		template<class T>
		inline vector3d<T>::vector3d(T n) :
				X(0), Y(0), Z(0)
		{
		}

		//! Copy constructor
		template<class T>
		inline vector3d<T>::vector3d(const vector3d<T>& other)

		{
			*this = other;
		}

		//! Assignment operator
		template<class T>
		inline vector3d<T>& vector3d<T>::operator=(const vector3d<T>& other)
		{
			//handle self-assignment
			if (this == &other)
				return *this;

			X = other.X;
			Y = other.Y;
			Z = other.Z;

			return *this;
		}

		// operators
		template<class T>
		inline vector3d<T> vector3d<T>::operator-() const
		{
			return vector3d<T>(-X, -Y, -Z);
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator+(
				const vector3d<T>& other) const
		{
			return vector3d<T>(X + other.X, Y + other.Y, Z + other.Z);
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator+(const T val) const
		{
			return vector3d<T>(X + val, Y + val, Z + val);
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator+=(const vector3d<T>& other)
		{

			X += other.X;
			Y += other.Y;
			Z += other.Z;

			return *this;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator+=(const T val)
		{

			X += val;
			Y += val;
			Z += val;

			return *this;
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator-(
				const vector3d<T>& other) const
		{
			if (this == &other)
				return vector3d<T>();

			vector3d<T> result = vector3d<T>(X - other.X, Y - other.Y,
					Z - other.Z);

			return result;
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator-(const T val) const
		{
			return vector3d<T>(X - val, Y - val, Z - val);
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator-=(const vector3d<T>& other)
		{
			X -= other.X;
			Y -= other.Y;
			Z -= other.Z;

			return *this;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator-=(const T val)
		{

			X -= val;
			Y -= val;
			Z -= val;

			return *this;
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator*(
				const vector3d<T>& other) const
		{
			return vector3d<T>(X * other.X, Y * other.Y, Z * other.Z);
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator*(const T v) const
		{
			return vector3d<T>(X * v, Y * v, Z * v);
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator*=(const vector3d<T>& other)
		{
			X *= other.X;
			Y *= other.Y;
			Z *= other.Z;

			return *this;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator*=(const T v)
		{
			X *= v;
			Y *= v;
			Z *= v;

			return *this;
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator/(
				const vector3d<T>& other) const
		{
			IRR_ASSERT(other.X != 0 && other.Y != 0 && other.Z != 0);

			return vector3d<T>(X / other.X, Y / other.Y, Z / other.Z);
		}

		template<class T>
		inline vector3d<T> vector3d<T>::operator/(const T v) const
		{
			IRR_ASSERT(v != 0);

			vector3d<T> result = vector3d<T>((T) X / v, (T) Y / v, (T) Z / v);

			return result;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator/=(const vector3d<T>& other)
		{
			IRR_ASSERT(other.X != 0 && other.Y != 0 && other.Z != 0);

			X /= other.X;
			Y /= other.Y;
			Z /= other.Z;

			return *this;
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::operator/=(const T v)
		{
			IRR_ASSERT(v != 0);

			X /= v;
			Y /= v;
			Z /= v;

			return *this;
		}

		//! sort in order X, Y, Z. Equality with rounding tolerance.
		template<class T>
		inline bool vector3d<T>::operator<=(const vector3d<T>&other) const
		{
			if (this == &other)
				return true;

			bool result = (X < other.X
					|| core::SharedMath::getInstance().equals(X, other.X))
					|| (core::SharedMath::getInstance().equals(X, other.X)
							&& (Y < other.Y
									|| core::SharedMath::getInstance().equals(Y,
											other.Y)))
					|| (core::SharedMath::getInstance().equals(X, other.X)
							&& core::SharedMath::getInstance().equals(Y,
									other.Y)
							&& (Z < other.Z
									|| core::SharedMath::getInstance().equals(Z,
											other.Z)));

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! sort in order X, Y, Z. Equality with rounding tolerance.
		template<class T>
		inline bool vector3d<T>::operator>=(const vector3d<T>&other) const
		{
			if (this == &other)
				return true;

			bool result = (X > other.X
					|| core::SharedMath::getInstance().equals(X, other.X))
					|| (core::SharedMath::getInstance().equals(X, other.X)
							&& (Y > other.Y
									|| core::SharedMath::getInstance().equals(Y,
											other.Y)))
					|| (core::SharedMath::getInstance().equals(X, other.X)
							&& core::SharedMath::getInstance().equals(Y,
									other.Y)
							&& (Z > other.Z
									|| core::SharedMath::getInstance().equals(Z,
											other.Z)));

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! sort in order X, Y, Z. Difference must be above rounding tolerance.
		template<class T>
		inline bool vector3d<T>::operator<(const vector3d<T>&other) const
		{
			if (this == &other)
			{
				_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
				return false;
			}

			bool result = (X < other.X
					&& !core::SharedMath::getInstance().equals(X, other.X))
					|| (core::SharedMath::getInstance().equals(X, other.X)
							&& Y < other.Y
							&& !core::SharedMath::getInstance().equals(Y,
									other.Y))
					|| (core::SharedMath::getInstance().equals(X, other.X)
							&& core::SharedMath::getInstance().equals(Y,
									other.Y) && Z < other.Z
							&& !core::SharedMath::getInstance().equals(Z,
									other.Z));

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! sort in order X, Y, Z. Difference must be above rounding tolerance.
		template<class T>
		inline bool vector3d<T>::operator>(const vector3d<T>&other) const
		{
			if (this == &other)
			{
				_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
				return false;
			}

			bool result = (X > other.X
					&& !core::SharedMath::getInstance().equals(X, other.X))
					|| (core::SharedMath::getInstance().equals(X, other.X)
							&& Y > other.Y
							&& !core::SharedMath::getInstance().equals(Y,
									other.Y))
					|| (core::SharedMath::getInstance().equals(X, other.X)
							&& core::SharedMath::getInstance().equals(Y,
									other.Y) && Z > other.Z
							&& !core::SharedMath::getInstance().equals(Z,
									other.Z));

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
			return core::SharedMath::getInstance().equals(X, other.X, tolerance)

			&& core::SharedMath::getInstance().equals(Y, other.Y, tolerance)
					&& core::SharedMath::getInstance().equals(Z, other.Z,
							tolerance);
		}

		template<class T>
		inline vector3d<T>& vector3d<T>::set(const T nx, const T ny, const T nz)
		{
			X = nx;
			Y = ny;
			Z = nz;

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
			return core::SharedMath::getInstance().squareroot(
					X * X + Y * Y + Z * Z);
		}

		//! Get squared length of the vector.
		template<class T>
		inline T vector3d<T>::getLengthSQ() const
		{
			return X * X + Y * Y + Z * Z;
		}

		//! Get the dot product with another vector.
		template<class T>
		inline T vector3d<T>::dotProduct(const vector3d<T>& other) const
		{
			if (this == &other)
				return getLengthSQ();

			return X * other.X + Y * other.Y + Z * other.Z;
		}

		//! Get distance from another point.
		template<class T>
		inline T vector3d<T>::getDistanceFrom(const vector3d<T>& other) const
		{
			if (this == &other)
				return 0;

			return vector3d<T>(X - other.X, Y - other.Y, Z - other.Z).getLength();
		}

		//! Returns squared distance from another point.
		template<class T>
		inline T vector3d<T>::getDistanceFromSQ(const vector3d<T>& other) const
		{
			if (this == &other)
				return 0;

			return vector3d<T>(X - other.X, Y - other.Y, Z - other.Z).getLengthSQ();
		}

		//! Calculates the cross product with another vector.
		template<class T>
		inline vector3d<T> vector3d<T>::crossProduct(const vector3d<T>& p) const
		{
			return vector3d<T>(Y * p.Z - Z * p.Y, Z * p.X - X * p.Z,
					X * p.Y - Y * p.X);
		}

		//! Returns if this vector interpreted as a point is on a line between two other points.
		template<class T>
		inline bool vector3d<T>::isBetweenPoints(const vector3d<T>& begin,
				const vector3d<T>& end) const
		{
			const T f;

			if (&begin == &end)
			{
				f = 0;
			}
			else
			{
				f = (end - begin).getLengthSQ();
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
			f32 length = X * X + Y * Y + Z * Z;

			if (core::SharedMath::getInstance().equals(length, 0.0)) // this check isn't an optimization but prevents getting NAN in the sqrt.
			{
				return *this;
			}

			length = core::SharedFastMath::getInstance().invertSqrt(length);

			X = (T) (X * length);
			Y = (T) (Y * length);
			Z = (T) (Z * length);

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

			X *= -1;
			Y *= -1;
			Z *= -1;

			return *this;
		}

		//! Rotates the vector by a specified number of degrees around the Y axis and the specified center.
		template<class T>
		inline void vector3d<T>::rotateXZBy(f32 degrees,
				const vector3d<T>& center)
		{
			if (this == &center)
				return;

			degrees *= core::SharedMath::DegToRad;
			f32 cs = cos(degrees);
			f32 sn = sin(degrees);
			X -= center.X;
			Z -= center.Z;

			X = (T) (X * cs - Z * sn);
			Z = (T) (X * sn + Z * cs);

			X += center.X;
			Z += center.Z;

		}

		//! Rotates the vector by a specified number of degrees around the Z axis and the specified center.
		template<class T>
		inline void vector3d<T>::rotateXYBy(f32 degrees,
				const vector3d<T>& center)
		{
			if (this == &center)
				return;

			degrees *= core::SharedMath::DegToRad;
			f32 cs = cos(degrees);
			f32 sn = sin(degrees);

			X -= center.X;
			Y -= center.Y;

			X = (T) (X * cs - Y * sn);
			Y = (T) (X * sn + Y * cs);

			X += center.X;
			Y += center.Y;

		}

		//! Rotates the vector by a specified number of degrees around the X axis and the specified center.
		template<class T>
		inline void vector3d<T>::rotateYZBy(f32 degrees,
				const vector3d<T>& center)
		{
			if (this == &center)
				return;

			degrees *= core::SharedMath::DegToRad;
			f32 cs = cos(degrees);
			f32 sn = sin(degrees);
			Z -= center.Z;
			Y -= center.Y;

			Y = (T) (Y * cs - Z * sn);
			Z = (T) (Y * sn + Z * cs);

			Z += center.Z;
			Y += center.Y;

		}

		//! Creates an interpolated vector between this vector and another vector.
		template<class T>
		inline vector3d<T> vector3d<T>::getInterpolated(
				const vector3d<T>& other, f32 d) const
		{
			if (this == &other)
				return *this;

			const f32 inv = 1.0 - d;

			return vector3d<T>((T) (other.X * inv + X * d),
					(T) (other.Y * inv + Y * d), (T) (other.Z * inv + Z * d));
		}

		//! Get the rotations that would make a (0,0,1) direction vector point in the same direction as this direction vector.
		template<class T>
		inline vector3d<T> vector3d<T>::getHorizontalAngle() const
		{
			vector3d<T> result;

			const f32 tmp = (atan2((f32) X, (f32) Z)
					* core::SharedMath::RadToDeg);
			result.Y = (T) tmp;

			if (result.Y < 0)
				result.Y += 360;
			if (result.Y >= 360)
				result.Y -= 360;

			const f32 z1 = core::SharedMath::getInstance().squareroot(
					X * X + Z * Z);

			result.X = (T) (atan2((f32) z1, (f32) Y)
					* core::SharedMath::RadToDeg - 90.0);

			if (result.X < 0)
				result.X += 360;
			if (result.X >= 360)
				result.X -= 360;

			return result;
		}

		//! Get the spherical coordinate angles
		template<class T>
		inline vector3d<T> vector3d<T>::getSphericalCoordinateAngles()
		{
			vector3d<T> result;

			const f32 length = X * X + Y * Y + Z * Z;

			if (length)
			{
				if (X != 0)
				{
					result.Y = (T) (atan2((f32) Z, (f32) X)
							* core::SharedMath::RadToDeg);
				}
				else if (Z < 0)
				{
					result.Y = 180;
				}

				result.X =
						(T) (acos(
								Y
										* core::SharedFastMath::getInstance().invertSqrt(
												length))
								* core::SharedMath::RadToDeg);
			}

			return result;
		}

		//! Builds a direction vector from (this) rotation vector.
		template<class T>
		inline vector3d<T> vector3d<T>::rotationToDirection(
				const vector3d<T>& forwards) const
		{

			const f32 cr = cos(core::SharedMath::DegToRad * X);
			const f32 sr = sin(core::SharedMath::DegToRad * X);
			const f32 cp = cos(core::SharedMath::DegToRad * Y);
			const f32 sp = sin(core::SharedMath::DegToRad * Y);
			const f32 cy = cos(core::SharedMath::DegToRad * Z);
			const f32 sy = sin(core::SharedMath::DegToRad * Z);

			const f32 srsp = sr * sp;
			const f32 crsp = cr * sp;

			const f32 pseudoMatrix[] =
			{ (cp * cy), (cp * sy), (-sp), (srsp * cy - cr * sy), (srsp * sy
					+ cr * cy), (sr * cp), (crsp * cy + sr * sy), (crsp * sy
					- sr * cy), (cr * cp) };

			vector3d<T> result = vector3d<T>(
					(T) (forwards.X * pseudoMatrix[0]
							+ forwards.Y * pseudoMatrix[3]
							+ forwards.Z * pseudoMatrix[6]),
					(T) (forwards.X * pseudoMatrix[1]
							+ forwards.Y * pseudoMatrix[4]
							+ forwards.Z * pseudoMatrix[7]),
					(T) (forwards.X * pseudoMatrix[2]
							+ forwards.Y * pseudoMatrix[5]
							+ forwards.Z * pseudoMatrix[8]));

			return result;
		}

		//! Fills an array of 4 values with the vector data (usually floats).
		template<class T>
		inline void vector3d<T>::getAs4Values(T* array) const
		{
			array[0] = X;
			array[1] = Y;
			array[2] = Z;
			array[3] = 0;
		}

//		//TODO: review this funcs. Mb need delete.
//		//! partial specialization for integer vectors
//		// Implementor note: inline keyword needed due to template specialization for s32. Otherwise put specialization into a .cpp
//		template<>
//		inline vector3d<s32> vector3d<s32>::operator /(s32 val) const
//		{
//
//			vector3d<s32> result = vector3d<s32>(X / val, Y / val, Z / val);
//
//
//			return result;
//		}
//
//		template<>
//		inline vector3d<s32>& vector3d<s32>::operator /=(s32 val)
//		{
//			X /= val;
//			Y /= val;
//			Z /= val;
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

#endif /* VECTOR3D_H_ */

