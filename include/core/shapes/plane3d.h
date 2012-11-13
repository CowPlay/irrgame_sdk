// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_PLANE_3D_H_INCLUDED__
#define __IRR_PLANE_3D_H_INCLUDED__

#include "core/math/SharedFastMath.h"
#include "core/shapes/vector3d.h"
#include "EIntersectionRelation3D.h"

namespace irrgame
{
	namespace core
	{
		//! Template plane class with some intersection testing methods.
		template<class T>
		class plane3d
		{
			public:
				//! Return empty 3d plane
				static const plane3d& getEmpty(void);

			public:

				/*
				 * Constructors
				 */

				//! Default constructor
				plane3d();

				plane3d(const vector3d<T>& MPoint, const vector3d<T>& Normal);

				plane3d(T px, T py, T pz, T nx, T ny, T nz);

				plane3d(const vector3d<T>& point1, const vector3d<T>& point2,
						const vector3d<T>& point3);

				plane3d(const vector3d<T> & normal, const T d);

				/*
				 * Operators
				 */

				bool operator==(const plane3d<T>& other) const;

				bool operator!=(const plane3d<T>& other) const;

				/*
				 * Methods
				 */

				void setPlane(const vector3d<T>& point,
						const vector3d<T>& nvector);

				void setPlane(const vector3d<T>& nvect, T d);

				void setPlane(const vector3d<T>& point1,
						const vector3d<T>& point2, const vector3d<T>& point3);

				//! Get an intersection with a 3d line.
				/** \param lineVect Vector of the line to intersect with.
				 \param linePoint Point of the line to intersect with.
				 \param outIntersection Place to store the intersection point, if there is one.
				 \return True if there was an intersection, false if there was not.
				 */
				bool getIntersectionWithLine(const vector3d<T>& linePoint,
						const vector3d<T>& lineVect,
						vector3d<T>& outIntersection) const;

				//! Get percentage of line between two points where an intersection with this plane happens.
				/** Only useful if known that there is an intersection.
				 \param linePoint1 Point1 of the line to intersect with.
				 \param linePoint2 Point2 of the line to intersect with.
				 \return Where on a line between two points an intersection with this plane happened.
				 For example, 0.5 is returned if the intersection happened exactly in the middle of the two points.
				 */
				f32 getKnownIntersectionWithLine(const vector3d<T>& linePoint1,
						const vector3d<T>& linePoint2) const;

				//! Get an intersection with a 3d line, limited between two 3d points.
				/** \param linePoint1 Point 1 of the line.
				 \param linePoint2 Point 2 of the line.
				 \param outIntersection Place to store the intersection point, if there is one.
				 \return True if there was an intersection, false if there was not.
				 */
				bool getIntersectionWithLimitedLine(
						const vector3d<T>& linePoint1,
						const vector3d<T>& linePoint2,
						vector3d<T>& outIntersection) const;

				//! Classifies the relation of a point to this plane.
				/** \param point Point to classify its relation.
				 \return ISREL3D_FRONT if the point is in front of the plane,
				 ISREL3D_BACK if the point is behind of the plane, and
				 ISREL3D_PLANAR if the point is within the plane. */
				EIntersectionRelation3D classifyPointRelation(
						const vector3d<T>& point) const;

				//! Recalculates the distance from origin by applying a new member point to the plane.
				void recalculateD(const vector3d<T>& MPoint);

				//! Gets a member point of the plane.
				vector3d<T> getMemberPoint() const;

				//! Tests if there is an intersection with the other plane
				/** \return True if there is a intersection. */
				bool existsIntersection(const plane3d<T>& other) const;

				//! Intersects this plane with another.
				/** \param other Other plane to intersect with.
				 \param outLinePoint Base point of intersection line.
				 \param outLineVect Vector of intersection.
				 \return True if there is a intersection, false if not. */
				bool getIntersectionWithPlane(const plane3d<T>& other,
						vector3d<T>& outLinePoint,
						vector3d<T>& outLineVect) const;

				//! Get the intersection point with two other planes if there is one.
				bool getIntersectionWithPlanes(const plane3d<T>& o1,
						const plane3d<T>& o2, vector3d<T>& outPoint) const;

				//! Test if the triangle would be front or backfacing from any point.
				/** Thus, this method assumes a camera position from
				 which the triangle is definitely visible when looking into
				 the given direction.
				 Note that this only works if the normal is Normalized.
				 Do not use this method with points as it will give wrong results!
				 \param lookDirection: Look direction.
				 \return True if the plane is front facing and
				 false if it is backfacing. */
				bool isFrontFacing(const vector3d<T>& lookDirection) const;

				//! Get the distance to a point.
				/** Note that this only works if the normal is normalized. */
				T getDistanceTo(const vector3d<T>& point) const;

			public:

				//! Normal vector of the plane.
				vector3d<T> Normal;

				//! Distance from origin.
				T D;
		};

		//! Return empty 3d plane
		template<class T>
		inline const plane3d<T>& plane3d<T>::getEmpty(void)
		{
			static const plane3d<T> empty;
			return empty;
		}

		/*
		 * Constructors
		 */

		//! Default constructor
		template<class T>
		inline plane3d<T>::plane3d() :
				Normal(0, 1, 0)
		{
			recalculateD(vector3d<T>(0, 0, 0));
		}

		template<class T>
		inline plane3d<T>::plane3d(const vector3d<T>& MPoint,
				const vector3d<T>& Normal) :
				Normal(Normal)
		{
			recalculateD(MPoint);
		}

		template<class T>
		inline plane3d<T>::plane3d(T px, T py, T pz, T nx, T ny, T nz) :
				Normal(nx, ny, nz)
		{
			recalculateD(vector3d<T>(px, py, pz));
		}

		template<class T>
		inline plane3d<T>::plane3d(const vector3d<T>& point1,
				const vector3d<T>& point2, const vector3d<T>& point3)
		{
			setPlane(point1, point2, point3);
		}

		template<class T>
		inline plane3d<T>::plane3d(const vector3d<T> & normal, const T d) :
				Normal(normal), D(d)
		{
		}

		/*
		 * Operators
		 */
		template<class T>
		inline bool plane3d<T>::operator==(const plane3d<T>& other) const
		{
			return (SharedMath::getInstance().equals(D, other.D)
					&& Normal == other.Normal);
		}
		template<class T>
		inline bool plane3d<T>::operator!=(const plane3d<T>& other) const
		{
			return !(*this == other);
		}

		/*
		 * Methods
		 */
		template<class T>
		inline void plane3d<T>::setPlane(const vector3d<T>& point,
				const vector3d<T>& nvector)
		{
			Normal = nvector;
			recalculateD(point);
		}

		template<class T>
		inline void plane3d<T>::setPlane(const vector3d<T>& nvect, T d)
		{
			Normal = nvect;
			D = d;
		}

		template<class T>
		inline void plane3d<T>::setPlane(const vector3d<T>& point1,
				const vector3d<T>& point2, const vector3d<T>& point3)
		{
			// creates the plane from 3 memberpoints
			Normal = (point2 - point1).crossProduct(point3 - point1);
			Normal.normalize();

			recalculateD(point1);
		}

		//! Get an intersection with a 3d line.
		template<class T>
		inline bool plane3d<T>::getIntersectionWithLine(
				const vector3d<T>& linePoint, const vector3d<T>& lineVect,
				vector3d<T>& outIntersection) const
		{
			bool result = false;

			T t2 = Normal.dotProduct(lineVect);

			if (t2 != 0)
			{
				T t = -(Normal.dotProduct(linePoint) + D) / t2;
				outIntersection = linePoint + (lineVect * t);

				result = true;
			}

			return result;
		}

		//! Get percentage of line between two points where an intersection with this plane happens.
		template<class T>
		inline f32 plane3d<T>::getKnownIntersectionWithLine(
				const vector3d<T>& linePoint1,
				const vector3d<T>& linePoint2) const
		{
			vector3d<T> vect = linePoint2 - linePoint1;
			T t2 = (f32) Normal.dotProduct(vect);

			return (f32) -((Normal.dotProduct(linePoint1) + D) / t2);
		}

		//! Get an intersection with a 3d line, limited between two 3d points.
		template<class T>
		inline bool plane3d<T>::getIntersectionWithLimitedLine(
				const vector3d<T>& linePoint1, const vector3d<T>& linePoint2,
				vector3d<T>& outIntersection) const
		{
			return (getIntersectionWithLine(linePoint1, linePoint2 - linePoint1,
					outIntersection)
					&& outIntersection.isBetweenPoints(linePoint1, linePoint2));
		}

		//! Classifies the relation of a point to this plane.
		template<class T>
		inline EIntersectionRelation3D plane3d<T>::classifyPointRelation(
				const vector3d<T>& point) const
		{
			EIntersectionRelation3D result = ISREL3D_COUNT;

			const T d = Normal.dotProduct(point) + D;

			if (d < -SharedMath::RoundErrF32)
			{
				result = ISREL3D_BACK;
			}
			else if (d > SharedMath::RoundErrF32)
			{
				result = ISREL3D_FRONT;
			}
			else
			{
				result = ISREL3D_PLANAR;
			}

			return result;
		}

		//! Recalculates the distance from origin by applying a new member point to the plane.
		template<class T>
		inline void plane3d<T>::recalculateD(const vector3d<T>& MPoint)
		{
			D = -MPoint.dotProduct(Normal);
		}

		//! Gets a member point of the plane.
		template<class T>
		inline vector3d<T> plane3d<T>::getMemberPoint() const
		{
			return Normal * -D;
		}

		//! Tests if there is an intersection with the other plane
		template<class T>
		inline bool plane3d<T>::existsIntersection(
				const plane3d<T>& other) const
		{
			vector3d<T> cross = other.Normal.crossProduct(Normal);

			return cross.getLength() > SharedMath::RoundErrF32;
		}

		//! Intersects this plane with another.
		template<class T>
		inline bool plane3d<T>::getIntersectionWithPlane(
				const plane3d<T>& other, vector3d<T>& outLinePoint,
				vector3d<T>& outLineVect) const
		{
			bool result = false;

			const T fn00 = Normal.getLength();
			const T fn01 = Normal.dotProduct(other.Normal);
			const T fn11 = other.Normal.getLength();
			const f32 det = fn00 * fn11 - fn01 * fn01;

			if (fabs(det) > SharedMath::RoundErrF32)
			{
				const f32 invdet = 1.0 / det;
				const f32 fc0 = (fn11 * -D + fn01 * other.D) * invdet;
				const f32 fc1 = (fn00 * -other.D + fn01 * D) * invdet;

				outLineVect = Normal.crossProduct(other.Normal);
				outLinePoint = Normal * (T) fc0 + other.Normal * (T) fc1;

				result = true;
			}

			return result;
		}

		//! Get the intersection point with two other planes if there is one.
		template<class T>
		inline bool plane3d<T>::getIntersectionWithPlanes(const plane3d<T>& o1,
				const plane3d<T>& o2, vector3d<T>& outPoint) const
		{
			bool result = false;

			vector3d<T> linePoint, lineVect;
			if (getIntersectionWithPlane(o1, linePoint, lineVect))
			{
				result = o2.getIntersectionWithLine(linePoint, lineVect,
						outPoint);
			}

			return result;
		}

		//! Test if the triangle would be front or backfacing from any point.
		template<class T>
		inline bool plane3d<T>::isFrontFacing(
				const vector3d<T>& lookDirection) const
		{
			const f32 d = Normal.dotProduct(lookDirection);

			return SharedFastMath::F32_LOWER_EQUAL_0(d);
		}

		//! Get the distance to a point.
		template<class T>
		inline T plane3d<T>::getDistanceTo(const vector3d<T>& point) const
		{
			return point.dotProduct(Normal) + D;
		}

	} // end namespace core
} // end namespace irrgame

//! Typedefs for plane3d
typedef irrgame::core::plane3d<f32> plane3df;
typedef irrgame::core::plane3d<s32> plane3di;

#endif

