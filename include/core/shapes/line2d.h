// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_LINE_2D_H_INCLUDED__
#define __IRR_LINE_2D_H_INCLUDED__

#include "core/shapes/vector2d.h"

namespace irrgame
{
	namespace core
	{

		//! 2D line between two points with intersection methods.
		template<class T>
		class line2d
		{
			public:
				//! Return empty line
				static const line2d& getEmpty(void);

			public:
				/*
				 * Constructors
				 */
				//! Default constructor for line going from (0,0) to (1,1).
				line2d();

				//! Constructor for line between the two points.
				line2d(T xa, T ya, T xb, T yb);

				//! Constructor for line between the two points given as vectors.
				line2d(const vector2d<T>& start, const vector2d<T>& end);

				//! Copy constructor.
				line2d(const line2d<T>& other);

				/*
				 * Operators
				 */

				line2d<T> operator+(const vector2d<T>& point) const;
				line2d<T>& operator+=(const vector2d<T>& point);

				line2d<T> operator-(const vector2d<T>& point) const;
				line2d<T>& operator-=(const vector2d<T>& point);

				bool operator==(const line2d<T>& other) const;
				bool operator!=(const line2d<T>& other) const;

				/*
				 * Methods
				 */
				//! Set this line to new line going through the two points.
				void setLine(const T& x1, const T& y1, const T& x2,
						const T& y2);
				//! Set this line to new line going through the two points.
				void setLine(const vector2d<T>& start, const vector2d<T>& end);
				//! Set this line to new line given as parameter.
				void setLine(const line2d<T>& line);

				//! Get length of line
				/** \return Length of the line. */
				f32 getLength() const;

				//! Get squared length of the line
				/** \return Squared length of line. */
				T getLengthSQ() const;

				//! Get middle of the line
				/** \return center of the line. */
				vector2d<T> getMiddle() const;

				//! Get the vector of the line.
				/** \return The vector of the line. */
				vector2d<T> getVector() const;

				//! Tests if this line intersects with another line.
				/** \param l: Other line to test intersection with.
				 \param out: If there is an intersection, the location of the
				 intersection will be stored in this vector.
				 \return True if there is an intersection, false if not. */
				bool intersectWith(const line2d<T>& l, vector2d<T>& out) const;

				//! Get unit vector of the line.
				/** \return Unit vector of this line. */
				vector2d<T> getUnitVector() const;

				//! Get angle between this line and given line.
				/** \param l Other line for test.
				 \return Angle in degrees. */
				f32 getAngleWith(const line2d<T>& l) const;

				//! Tells us if the given point lies to the left, right, or on the line.
				/** \return 0 if the point is on the line
				 <0 if to the left, or >0 if to the right. */
				T getPointOrientation(const vector2d<T>& point) const;

				//! Check if the given point is a member of the line
				/** \return True if point is between start and end, else false. */
				bool isPointOnLine(const vector2d<T>& point) const;

				//! Check if the given point is between start and end of the line.
				/** Assumes that the point is already somewhere on the line. */
				bool isPointBetweenStartAndEnd(const vector2d<T>& point) const;

				//! Get the closest point on this line to a point
				vector2d<T> getClosestPoint(const vector2d<T>& point) const;

			public:

				//! Start point of the line.
				vector2d<T> Start;
				//! End point of the line.
				vector2d<T> End;
		};

		//! Return empty line
		template<class T>
		inline const line2d<T>& line2d<T>::getEmpty(void)
		{
			static const line2d empty;
			return empty;
		}

		//! Default constructor for line going from (0,0) to (1,1).
		template<class T>
		inline line2d<T>::line2d() :
				Start(0, 0), End(1, 1)
		{
		}
		//! Constructor for line between the two points.
		template<class T>
		line2d<T>::line2d(T xa, T ya, T xb, T yb) :
				Start(xa, ya), End(xb, yb)
		{
		}

		//! Constructor for line between the two points given as vectors.
		template<class T>
		inline line2d<T>::line2d(const vector2d<T>& start,
				const vector2d<T>& end) :
				Start(start), End(end)
		{
		}

		//! Copy constructor.
		template<class T>
		inline line2d<T>::line2d(const line2d<T>& other) :
				Start(other.Start), End(other.End)
		{
		}

		/*
		 * Operators
		 */
		template<class T>
		inline line2d<T> line2d<T>::operator+(const vector2d<T>& point) const
		{
			return line2d<T>(Start + point, End + point);
		}

		template<class T>
		inline line2d<T>& line2d<T>::operator+=(const vector2d<T>& point)
		{
			Start += point;
			End += point;
			return *this;
		}

		template<class T>
		inline line2d<T> line2d<T>::operator-(const vector2d<T>& point) const
		{
			return line2d<T>(Start - point, End - point);
		}

		template<class T>
		inline line2d<T>& line2d<T>::operator-=(const vector2d<T>& point)
		{
			Start -= point;
			End -= point;
			return *this;
		}

		template<class T>
		inline bool line2d<T>::operator==(const line2d<T>& other) const
		{
			return (Start == other.Start && End == other.End)
					|| (End == other.Start && Start == other.End);
		}

		template<class T>
		inline bool line2d<T>::operator!=(const line2d<T>& other) const
		{
			return !(Start == other.Start && End == other.End)
					|| (End == other.Start && Start == other.End);
		}

		/*
		 * Methods
		 */

		//! Set this line to new line going through the two points.
		template<class T>
		inline void line2d<T>::setLine(const T& xa, const T& ya, const T& xb,
				const T& yb)
		{
			Start.set(xa, ya);
			End.set(xb, yb);
		}

		//! Set this line to new line going through the two points.
		template<class T>
		inline void line2d<T>::setLine(const vector2d<T>& nstart,
				const vector2d<T>& nend)
		{
			Start.set(nstart);
			End.set(nend);
		}

		//! Set this line to new line given as parameter.
		template<class T>
		inline void line2d<T>::setLine(const line2d<T>& line)
		{
			Start.set(line.Start);
			End.set(line.End);
		}

		//! Get length of line
		template<class T>
		inline f32 line2d<T>::getLength() const
		{
			return Start.getDistanceFrom(End);
		}

		//! Get squared length of the line
		template<class T>
		inline T line2d<T>::getLengthSQ() const
		{
			return Start.getDistanceFromSQ(End);
		}

		//! Get middle of the line
		template<class T>
		inline vector2d<T> line2d<T>::getMiddle() const
		{
			return (Start + End) * (T) 0.5;
		}

		//! Get the vector of the line.
		template<class T>
		inline vector2d<T> line2d<T>::getVector() const
		{
			return vector2d<T>(End.X - Start.X, End.Y - Start.Y);
		}

		//! Tests if this line intersects with another line.
		template<class T>
		inline bool line2d<T>::intersectWith(const line2d<T>& l,
				vector2d<T>& out) const
		{
			// Uses the method given at:
			// http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/
			const f32 commonDenominator = (f32) ((l.End.Y - l.Start.Y)
					* (End.X - Start.X)
					- (l.End.X - l.Start.X) * (End.Y - Start.Y));

			const f32 numeratorA = (f32) ((l.End.X - l.Start.X)
					* (Start.Y - l.Start.Y)
					- (l.End.Y - l.Start.Y) * (Start.X - l.Start.X));

			const f32 numeratorB = (f32) ((End.X - Start.X)
					* (Start.Y - l.Start.Y)
					- (End.Y - Start.Y) * (Start.X - l.Start.X));

			if (SharedMath::getInstance().equals(commonDenominator, 0.f))
			{
				// The lines are either coincident or parallel
				// if both numerators are 0, the lines are coincident
				if (SharedMath::getInstance().equals(numeratorA, 0.f)
						&& SharedMath::getInstance().equals(numeratorB, 0.f))
				{
					// Try and find a common endpoint
					if (l.Start == Start || l.End == Start)
						out = Start;
					else if (l.End == End || l.Start == End)
						out = End;
					// now check if the two segments are disjunct
					else if (l.Start.X > Start.X && l.End.X > Start.X
							&& l.Start.X > End.X && l.End.X > End.X)
						return false;
					else if (l.Start.Y > Start.Y && l.End.Y > Start.Y
							&& l.Start.Y > End.Y && l.End.Y > End.Y)
						return false;
					else if (l.Start.X < Start.X && l.End.X < Start.X
							&& l.Start.X < End.X && l.End.X < End.X)
						return false;
					else if (l.Start.Y < Start.Y && l.End.Y < Start.Y
							&& l.Start.Y < End.Y && l.End.Y < End.Y)
						return false;
					// else the lines are overlapping to some extent
					else
					{
						// find the points which are not contributing to the
						// common part
						vector2d<T> maxp;
						vector2d<T> minp;
						if ((Start.X > l.Start.X && Start.X > l.End.X
								&& Start.X > End.X)
								|| (Start.Y > l.Start.Y && Start.Y > l.End.Y
										&& Start.Y > End.Y))
							maxp = Start;
						else if ((End.X > l.Start.X && End.X > l.End.X
								&& End.X > Start.X)
								|| (End.Y > l.Start.Y && End.Y > l.End.Y
										&& End.Y > Start.Y))
							maxp = End;
						else if ((l.Start.X > Start.X && l.Start.X > l.End.X
								&& l.Start.X > End.X)
								|| (l.Start.Y > Start.Y && l.Start.Y > l.End.Y
										&& l.Start.Y > End.Y))
							maxp = l.Start;
						else
							maxp = l.End;
						if (maxp != Start
								&& ((Start.X < l.Start.X && Start.X < l.End.X
										&& Start.X < End.X)
										|| (Start.Y < l.Start.Y
												&& Start.Y < l.End.Y
												&& Start.Y < End.Y)))
							minp = Start;
						else if (maxp != End
								&& ((End.X < l.Start.X && End.X < l.End.X
										&& End.X < Start.X)
										|| (End.Y < l.Start.Y && End.Y < l.End.Y
												&& End.Y < Start.Y)))
							minp = End;
						else if (maxp != l.Start
								&& ((l.Start.X < Start.X && l.Start.X < l.End.X
										&& l.Start.X < End.X)
										|| (l.Start.Y < Start.Y
												&& l.Start.Y < l.End.Y
												&& l.Start.Y < End.Y)))
							minp = l.Start;
						else
							minp = l.End;

						// one line is contained in the other. Pick the center
						// of the remaining points, which overlap for sure
						out = core::vector2d<T>();
						if (Start != maxp && Start != minp)
							out += Start;
						if (End != maxp && End != minp)
							out += End;
						if (l.Start != maxp && l.Start != minp)
							out += l.Start;
						if (l.End != maxp && l.End != minp)
							out += l.End;
						out.X = (T) (out.X * 0.5f);
						out.Y = (T) (out.Y * 0.5f);
					}

					return true; // coincident
				}

				return false; // parallel
			}

			// Get the point of intersection on this line, checking that
			// it is within the line segment.
			const f32 uA = numeratorA / commonDenominator;
			if (uA < 0.f || uA > 1.f)
			{
				return false; // Outside the line segment
			}

			const f32 uB = numeratorB / commonDenominator;
			if (uB < 0.f || uB > 1.f)
			{
				return false; // Outside the line segment
			}

			// Calculate the intersection point.
			out.X = (T) (Start.X + uA * (End.X - Start.X));
			out.Y = (T) (Start.Y + uA * (End.Y - Start.Y));

			return true;
		}

		//! Get unit vector of the line.
		template<class T>
		inline vector2d<T> line2d<T>::getUnitVector() const
		{
			T len = (T) (1.0 / getLength());
			return vector2d<T>((End.X - Start.X) * len, (End.Y - Start.Y) * len);
		}

		//! Get angle between this line and given line.
		template<class T>
		inline f32 line2d<T>::getAngleWith(const line2d<T>& l) const
		{
			vector2d<T> vect = getVector();
			vector2d<T> vect2 = l.getVector();
			return vect.getAngleWith(vect2);
		}

		//! Tells us if the given point lies to the left, right, or on the line.
		template<class T>
		inline T line2d<T>::getPointOrientation(const vector2d<T>& point) const
		{
			return ((End.X - Start.X) * (point.Y - Start.Y)
					- (point.X - Start.X) * (End.Y - Start.Y));
		}

		//! Check if the given point is a member of the line
		template<class T>
		inline bool line2d<T>::isPointOnLine(const vector2d<T>& point) const
		{
			T d = getPointOrientation(point);
			return (d == 0 && point.isBetweenPoints(Start, End));
		}

		//! Check if the given point is between start and end of the line.
		template<class T>
		inline bool line2d<T>::isPointBetweenStartAndEnd(
				const vector2d<T>& point) const
		{
			return point.isBetweenPoints(Start, End);
		}

		//! Get the closest point on this line to a point
		template<class T>
		inline vector2d<T> line2d<T>::getClosestPoint(
				const vector2d<T>& point) const
		{
			vector2d<T> c = point - Start;
			vector2d<T> v = End - Start;
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

	} // end namespace core
} // end namespace irrgame

//! Typedefs for line2d
typedef irrgame::core::line2d<f32> line2df;
typedef irrgame::core::line2d<s32> line2di;

#endif

