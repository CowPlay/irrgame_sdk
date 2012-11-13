// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_LINE_3D_H_INCLUDED__
#define __IRR_LINE_3D_H_INCLUDED__

#include "core/shapes/vector3d.h"

namespace irrgame
{
	namespace core
	{

		//! 3D line between two points with intersection methods.
		template<class T>
		class line3d
		{
			public:
				//! Return empty 3d line
				static const line3d& getEmpty(void);

			public:

				/*
				 * Constructors
				 */

				//! Default constructor
				/** line from (0,0,0) to (1,1,1) */
				line3d();

				//! Constructor with two points
				line3d(T xa, T ya, T za, T xb, T yb, T zb);

				//! Constructor with two points as vectors
				line3d(const vector3d<T>& start, const vector3d<T>& end);

				/*
				 * Operators
				 */

				line3d<T> operator+(const vector3d<T>& point) const;
				line3d<T>& operator+=(const vector3d<T>& point);

				line3d<T> operator-(const vector3d<T>& point) const;
				line3d<T>& operator-=(const vector3d<T>& point);

				bool operator==(const line3d<T>& other) const;
				bool operator!=(const line3d<T>& other) const;

				/*
				 * Methods
				 */

				//! Set this line to a new line going through the two points.
				void setLine(const T& xa, const T& ya, const T& za, const T& xb,
						const T& yb, const T& zb);
				//! Set this line to a new line going through the two points.
				void setLine(const vector3d<T>& nstart,
						const vector3d<T>& nend);
				//! Set this line to new line given as parameter.
				void setLine(const line3d<T>& line);

				//! Get length of line
				/** \return Length of line. */
				T getLength() const;

				//! Get squared length of line
				/** \return Squared length of line. */
				T getLengthSQ() const;

				//! Get middle of line
				/** \return Center of line. */
				vector3d<T> getMiddle() const;

				//! Get vector of line
				/** \return vector of line. */
				vector3d<T> getVector() const;

				//! Check if the given point is between start and end of the line.
				/** Assumes that the point is already somewhere on the line.
				 \param point The point to test.
				 \return True if point is on the line between start and end, else false.
				 */
				bool isPointBetweenStartAndEnd(const vector3d<T>& point) const;

				//! Get the closest point on this line to a point
				/** \param point The point to compare to.
				 \return The nearest point which is part of the line. */
				vector3d<T> getClosestPoint(const vector3d<T>& point) const;

				//! Check if the line intersects with a shpere
				/** \param sorigin: Origin of the shpere.
				 \param sradius: Radius of the sphere.
				 \param outdistance: The distance to the first intersection point.
				 \return True if there is an intersection.
				 If there is one, the distance to the first intersection point
				 is stored in outdistance. */
				bool getIntersectionWithSphere(vector3d<T> sorigin, T sradius,
						f32& outdistance) const;

			public:

				//! Start point of line
				vector3d<T> Start;
				//! End point of line
				vector3d<T> End;
		};

		template<class T>
		inline const line3d<T>& line3d<T>::getEmpty(void)
		{
			static const line3d<T> empty;
			return empty;
		}

		//! Default constructor
		template<class T>
		inline line3d<T>::line3d() :
				Start(0, 0, 0), End(1, 1, 1)
		{
		}

		//! Constructor with two points
		template<class T>
		inline line3d<T>::line3d(T xa, T ya, T za, T xb, T yb, T zb) :
				Start(xa, ya, za), End(xb, yb, zb)
		{
		}

		//! Constructor with two points as vectors
		template<class T>
		inline line3d<T>::line3d(const vector3d<T>& start,
				const vector3d<T>& end) :
				Start(start), End(end)
		{
		}

		template<class T>
		inline line3d<T> line3d<T>::operator+(const vector3d<T>& point) const
		{
			return line3d<T>(Start + point, End + point);
		}

		template<class T>
		inline line3d<T>& line3d<T>::operator+=(const vector3d<T>& point)
		{
			Start += point;
			End += point;
			return *this;
		}

		template<class T>
		inline line3d<T> line3d<T>::operator-(const vector3d<T>& point) const
		{
			return line3d<T>(Start - point, End - point);
		}

		template<class T>
		inline line3d<T>& line3d<T>::operator-=(const vector3d<T>& point)
		{
			Start -= point;
			End -= point;
			return *this;
		}

		template<class T>
		inline bool line3d<T>::operator==(const line3d<T>& other) const
		{
			return (Start == other.Start && End == other.End)
					|| (End == other.Start && Start == other.End);
		}

		template<class T>
		inline bool line3d<T>::operator!=(const line3d<T>& other) const
		{
			return !(Start == other.Start && End == other.End)
					|| (End == other.Start && Start == other.End);
		}

		//! Set this line to a new line going through the two points.
		template<class T>
		inline void line3d<T>::setLine(const T& xa, const T& ya, const T& za,
				const T& xb, const T& yb, const T& zb)
		{
			Start.set(xa, ya, za);
			End.set(xb, yb, zb);
		}

		//! Set this line to a new line going through the two points.
		template<class T>
		inline void line3d<T>::setLine(const vector3d<T>& nstart,
				const vector3d<T>& nend)
		{
			Start.set(nstart);
			End.set(nend);
		}

		//! Set this line to new line given as parameter.
		template<class T>
		inline void line3d<T>::setLine(const line3d<T>& line)
		{
			Start.set(line.Start);
			End.set(line.End);
		}

		//! Get length of line
		template<class T>
		inline T line3d<T>::getLength() const
		{
			return Start.getDistanceFrom(End);
		}

		//! Get squared length of line
		template<class T>
		inline T line3d<T>::getLengthSQ() const
		{
			return Start.getDistanceFromSQ(End);
		}

		//! Get middle of line
		template<class T>
		inline vector3d<T> line3d<T>::getMiddle() const
		{
			return (Start + End) * (T) 0.5;
		}

		//! Get vector of line
		template<class T>
		inline vector3d<T> line3d<T>::getVector() const
		{
			return End - Start;
		}

		//! Check if the given point is between start and end of the line.
		template<class T>
		inline bool line3d<T>::isPointBetweenStartAndEnd(
				const vector3d<T>& point) const
		{
			return point.isBetweenPoints(Start, End);
		}

		//! Get the closest point on this line to a point
		template<class T>
		inline vector3d<T> line3d<T>::getClosestPoint(
				const vector3d<T>& point) const
		{
			vector3d<T> c = point - Start;
			vector3d<T> v = End - Start;
			T d = (T) v.getLength();
			v /= d;
			T t = v.dotProduct(c);

			if (t < (T) 0.0)
				return Start;
			if (t > d)
				return End;

			v *= t;
			return Start + v;
		}

		//! Check if the line intersects with a shpere
		template<class T>
		inline bool line3d<T>::getIntersectionWithSphere(vector3d<T> sorigin,
				T sradius, f32& outdistance) const
		{
			const vector3d<T> q = sorigin - Start;
			T c = q.getLength();
			T v = q.dotProduct(getVector().normalize());
			T d = sradius * sradius - (c * c - v * v);

			if (d < 0.0)
				return false;

			outdistance = v - core::SharedMath::getInstance().squareroot(d);
			return true;
		}

	} // end namespace core
} // end namespace irrgame

//! Typedefs for line3d
typedef irrgame::core::line3d<f32> line3df;
typedef irrgame::core::line3d<s32> line3di;

#endif

