/*
 * CNumbersAttribute.cpp
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */
#include "CNumbersAttribute.h"
#include "core/fast_atof.h"
namespace irrgame
{
	namespace io
	{
		//! Default constructor for colorf list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				video::SColorf value) :
				ValueI(), ValueF(), Count(4), IsFloat(true)
		{
			Name = name;
			ValueF.push_back(value.r);
			ValueF.push_back(value.g);
			ValueF.push_back(value.b);
			ValueF.push_back(value.a);
		}

		//! Default constructor for color list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				video::SColor value) :
				ValueI(), ValueF(), Count(4), IsFloat(false)
		{
			Name = name;
			ValueI.push_back(value.getRed());
			ValueI.push_back(value.getGreen());
			ValueI.push_back(value.getBlue());
			ValueI.push_back(value.getAlpha());
		}

		//! Default constructor for vector3df list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				core::vector3df value) :
				ValueI(), ValueF(), Count(3), IsFloat(true)
		{
			Name = name;
			ValueF.push_back(value.X);
			ValueF.push_back(value.Y);
			ValueF.push_back(value.Z);
		}

		//! Default constructor for recti list
		CNumbersAttribute::CNumbersAttribute(const c8* name, core::recti value) :
				ValueI(), ValueF(), Count(4), IsFloat(false)
		{
			Name = name;
			ValueI.push_back(value.UpperLeftCorner.X);
			ValueI.push_back(value.UpperLeftCorner.Y);
			ValueI.push_back(value.LowerRightCorner.X);
			ValueI.push_back(value.LowerRightCorner.Y);
		}

		//! Default constructor for rectf list
		CNumbersAttribute::CNumbersAttribute(const c8* name, core::rectf value) :
				ValueI(), ValueF(), Count(4), IsFloat(true)
		{
			Name = name;
			ValueF.push_back(value.UpperLeftCorner.X);
			ValueF.push_back(value.UpperLeftCorner.Y);
			ValueF.push_back(value.LowerRightCorner.X);
			ValueF.push_back(value.LowerRightCorner.Y);
		}

		//! Default constructor for matrix4 list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				core::matrix4 value) :
				ValueI(), ValueF(), Count(16), IsFloat(true)
		{
			Name = name;
			for (s32 r = 0; r < 4; ++r)
				for (s32 c = 0; c < 4; ++c)
					ValueF.push_back(value(r, c));
		}

		//! Default constructor for quaternion list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				core::quaternion value) :
				ValueI(), ValueF(), Count(4), IsFloat(true)
		{
			Name = name;
			ValueF.push_back(value.X);
			ValueF.push_back(value.Y);
			ValueF.push_back(value.Z);
			ValueF.push_back(value.W);
		}

		//! Default constructor for aabbox3df list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				core::aabbox3df value) :
				ValueI(), ValueF(), Count(6), IsFloat(true)
		{
			Name = name;
			ValueF.push_back(value.MinEdge.X);
			ValueF.push_back(value.MinEdge.Y);
			ValueF.push_back(value.MinEdge.Z);
			ValueF.push_back(value.MaxEdge.X);
			ValueF.push_back(value.MaxEdge.Y);
			ValueF.push_back(value.MaxEdge.Z);
		}

		//! Default constructor for plane3df list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				core::plane3df value) :
				ValueI(), ValueF(), Count(4), IsFloat(true)
		{
			Name = name;
			ValueF.push_back(value.Normal.X);
			ValueF.push_back(value.Normal.Y);
			ValueF.push_back(value.Normal.Z);
			ValueF.push_back(value.D);
		}

		//! Default constructor for triangle3df list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				core::triangle3df value) :
				ValueI(), ValueF(), Count(9), IsFloat(true)
		{
			Name = name;
			ValueF.push_back(value.pointA.X);
			ValueF.push_back(value.pointA.Y);
			ValueF.push_back(value.pointA.Z);
			ValueF.push_back(value.pointB.X);
			ValueF.push_back(value.pointB.Y);
			ValueF.push_back(value.pointB.Z);
			ValueF.push_back(value.pointC.X);
			ValueF.push_back(value.pointC.Y);
			ValueF.push_back(value.pointC.Z);
		}

		//! Default constructor for vector2df list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				core::vector2df value) :
				ValueI(), ValueF(), Count(2), IsFloat(true)
		{
			Name = name;
			ValueF.push_back(value.X);
			ValueF.push_back(value.Y);
		}

		//! Default constructor for line2di list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				core::line2di value) :
				ValueI(), ValueF(), Count(4), IsFloat(false)
		{
			Name = name;
			ValueI.push_back(value.start.X);
			ValueI.push_back(value.start.Y);
			ValueI.push_back(value.end.X);
			ValueI.push_back(value.end.Y);
		}

		//! Default constructor for line2df list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				core::line2df value) :
				ValueI(), ValueF(), Count(4), IsFloat(true)
		{
			Name = name;
			ValueF.push_back(value.start.X);
			ValueF.push_back(value.start.Y);
			ValueF.push_back(value.end.X);
			ValueF.push_back(value.end.Y);
		}

		//! Default constructor for line3df list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				core::line3df value) :
				ValueI(), ValueF(), Count(6), IsFloat(true)
		{
			Name = name;
			ValueF.push_back(value.start.X);
			ValueF.push_back(value.start.Y);
			ValueF.push_back(value.start.Z);
			ValueF.push_back(value.end.X);
			ValueF.push_back(value.end.Y);
			ValueF.push_back(value.end.Z);
		}

		//! Default constructor for dimension2du list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				core::dimension2du value) :
				ValueI(), ValueF(), Count(2), IsFloat(false)
		{
			Name = name;
			ValueI.push_back(value.Width);
			ValueI.push_back(value.Height);
		}

		//! Default constructor for dimension2df list
		CNumbersAttribute::CNumbersAttribute(const c8* name,
				core::dimension2df value) :
				ValueI(), ValueF(), Count(2), IsFloat(true)
		{
			Name = name;
			ValueF.push_back(value.Width);
			ValueF.push_back(value.Height);
		}

		// getting values
		s32 CNumbersAttribute::getInt()
		{
			if (Count == 0)
				return 0;

			return IsFloat ? (s32) ValueF[0] : ValueI[0];
		}

		f32 CNumbersAttribute::getFloat()
		{
			if (Count == 0)
				return 0.0f;

			return IsFloat ? ValueF[0] : (f32) ValueI[0];
		}

		bool CNumbersAttribute::getBool()
		{
			// return true if any number is nonzero
			bool ret = false;

			for (u32 i = 0; i < Count; ++i)
				if (IsFloat ? (ValueF[i] != 0) : (ValueI[i] != 0))
				{
					ret = true;
					break;
				}

			return ret;
		}

		core::stringc CNumbersAttribute::getString()
		{
			core::stringc outstr;

			for (u32 i = 0; i < Count; ++i)
			{
				outstr += IsFloat ? ValueF[i] : ValueI[i];

				if (i < Count - 1)
					outstr += ", ";
			}
			return outstr;
		}

		core::vector2df CNumbersAttribute::getVector2d()
		{
			core::vector2df v;

			if (IsFloat)
			{
				v.X = Count > 0 ? ValueF[0] : 0;
				v.Y = Count > 1 ? ValueF[1] : 0;

			}
			else
			{
				v.X = (f32) (Count > 0 ? ValueI[0] : 0);
				v.Y = (f32) (Count > 1 ? ValueI[1] : 0);
			}

			return v;
		}

		core::vector3df CNumbersAttribute::getVector3d()
		{
			core::vector3df v;

			if (IsFloat)
			{
				v.X = Count > 0 ? ValueF[0] : 0;
				v.Y = Count > 1 ? ValueF[1] : 0;
				v.Z = Count > 2 ? ValueF[2] : 0;
			}
			else
			{
				v.X = (f32) (Count > 0 ? ValueI[0] : 0);
				v.Y = (f32) (Count > 1 ? ValueI[1] : 0);
				v.Z = (f32) (Count > 2 ? ValueI[2] : 0);
			}

			return v;
		}

		video::SColorf CNumbersAttribute::getColorf()
		{
			video::SColorf c;
			if (IsFloat)
			{
				c.setColorComponentValue(0, Count > 0 ? ValueF[0] : 0);
				c.setColorComponentValue(1, Count > 1 ? ValueF[1] : 0);
				c.setColorComponentValue(2, Count > 2 ? ValueF[2] : 0);
				c.setColorComponentValue(3, Count > 3 ? ValueF[3] : 0);
			}
			else
			{
				c.setColorComponentValue(0,
						Count > 0 ? (f32) (ValueI[0]) / 255.0f : 0);
				c.setColorComponentValue(1,
						Count > 1 ? (f32) (ValueI[1]) / 255.0f : 0);
				c.setColorComponentValue(2,
						Count > 2 ? (f32) (ValueI[2]) / 255.0f : 0);
				c.setColorComponentValue(3,
						Count > 3 ? (f32) (ValueI[3]) / 255.0f : 0);
			}

			return c;
		}

		video::SColor CNumbersAttribute::getColor()
		{
			return getColorf().toSColor();
		}

		core::recti CNumbersAttribute::getRect()
		{
			core::recti r;

			if (IsFloat)
			{
				r.UpperLeftCorner.X = (s32) (Count > 0 ? ValueF[0] : 0);
				r.UpperLeftCorner.Y = (s32) (Count > 1 ? ValueF[1] : 0);
				r.LowerRightCorner.X = (s32) (
						Count > 2 ? ValueF[2] : r.UpperLeftCorner.X);
				r.LowerRightCorner.Y = (s32) (
						Count > 3 ? ValueF[3] : r.UpperLeftCorner.Y);
			}
			else
			{
				r.UpperLeftCorner.X = Count > 0 ? ValueI[0] : 0;
				r.UpperLeftCorner.Y = Count > 1 ? ValueI[1] : 0;
				r.LowerRightCorner.X =
						Count > 2 ? ValueI[2] : r.UpperLeftCorner.X;
				r.LowerRightCorner.Y =
						Count > 3 ? ValueI[3] : r.UpperLeftCorner.Y;
			}
			return r;
		}

		core::matrix4 CNumbersAttribute::getMatrix()
		{
			core::matrix4 ret;
			if (IsFloat)
			{
				for (u32 r = 0; r < 4; ++r)
					for (u32 c = 0; c < 4; ++c)
						if (Count > c + r * 4)
							ret(r, c) = ValueF[c + r * 4];
			}
			else
			{
				for (u32 r = 0; r < 4; ++r)
					for (u32 c = 0; c < 4; ++c)
						if (Count > c + r * 4)
							ret(r, c) = (f32) ValueI[c + r * 4];
			}
			return ret;
		}

		core::quaternion CNumbersAttribute::getQuaternion()
		{
			core::quaternion ret;
			if (IsFloat)
			{
				ret.X = Count > 0 ? ValueF[0] : 0.0f;
				ret.Y = Count > 1 ? ValueF[1] : 0.0f;
				ret.Z = Count > 2 ? ValueF[2] : 0.0f;
				ret.W = Count > 3 ? ValueF[3] : 0.0f;
			}
			else
			{
				ret.X = Count > 0 ? (f32) ValueI[0] : 0.0f;
				ret.Y = Count > 1 ? (f32) ValueI[1] : 0.0f;
				ret.Z = Count > 2 ? (f32) ValueI[2] : 0.0f;
				ret.W = Count > 3 ? (f32) ValueI[3] : 0.0f;
			}
			return ret;
		}

		core::triangle3df CNumbersAttribute::getTriangle()
		{
			core::triangle3df ret;

			if (IsFloat)
			{
				ret.pointA.X = Count > 0 ? ValueF[0] : 0.0f;
				ret.pointA.Y = Count > 1 ? ValueF[1] : 0.0f;
				ret.pointA.Z = Count > 2 ? ValueF[2] : 0.0f;
				ret.pointB.X = Count > 3 ? ValueF[3] : 0.0f;
				ret.pointB.Y = Count > 4 ? ValueF[4] : 0.0f;
				ret.pointB.Z = Count > 5 ? ValueF[5] : 0.0f;
				ret.pointC.X = Count > 6 ? ValueF[6] : 0.0f;
				ret.pointC.Y = Count > 7 ? ValueF[7] : 0.0f;
				ret.pointC.Z = Count > 8 ? ValueF[8] : 0.0f;
			}
			else
			{
				ret.pointA.X = Count > 0 ? (f32) ValueI[0] : 0.0f;
				ret.pointA.Y = Count > 1 ? (f32) ValueI[1] : 0.0f;
				ret.pointA.Z = Count > 2 ? (f32) ValueI[2] : 0.0f;
				ret.pointB.X = Count > 3 ? (f32) ValueI[3] : 0.0f;
				ret.pointB.Y = Count > 4 ? (f32) ValueI[4] : 0.0f;
				ret.pointB.Z = Count > 5 ? (f32) ValueI[5] : 0.0f;
				ret.pointC.X = Count > 6 ? (f32) ValueI[6] : 0.0f;
				ret.pointC.Y = Count > 7 ? (f32) ValueI[7] : 0.0f;
				ret.pointC.Z = Count > 8 ? (f32) ValueI[8] : 0.0f;
			}

			return ret;
		}

		core::plane3df CNumbersAttribute::getPlane()
		{
			core::plane3df ret;

			if (IsFloat)
			{
				ret.Normal.X = Count > 0 ? ValueF[0] : 0.0f;
				ret.Normal.Y = Count > 1 ? ValueF[1] : 0.0f;
				ret.Normal.Z = Count > 2 ? ValueF[2] : 0.0f;
				ret.D = Count > 3 ? ValueF[3] : 0.0f;
			}
			else
			{
				ret.Normal.X = Count > 0 ? (f32) ValueI[0] : 0.0f;
				ret.Normal.Y = Count > 1 ? (f32) ValueI[1] : 0.0f;
				ret.Normal.Z = Count > 2 ? (f32) ValueI[2] : 0.0f;
				ret.D = Count > 3 ? (f32) ValueI[3] : 0.0f;
			}

			return ret;
		}

		core::aabbox3df CNumbersAttribute::getBBox()
		{
			core::aabbox3df ret;
			if (IsFloat)
			{
				ret.MinEdge.X = Count > 0 ? ValueF[0] : 0.0f;
				ret.MinEdge.Y = Count > 1 ? ValueF[1] : 0.0f;
				ret.MinEdge.Z = Count > 2 ? ValueF[2] : 0.0f;
				ret.MaxEdge.X = Count > 3 ? ValueF[3] : 0.0f;
				ret.MaxEdge.Y = Count > 4 ? ValueF[4] : 0.0f;
				ret.MaxEdge.Z = Count > 5 ? ValueF[5] : 0.0f;
			}
			else
			{
				ret.MinEdge.X = Count > 0 ? (f32) ValueI[0] : 0.0f;
				ret.MinEdge.Y = Count > 1 ? (f32) ValueI[1] : 0.0f;
				ret.MinEdge.Z = Count > 2 ? (f32) ValueI[2] : 0.0f;
				ret.MaxEdge.X = Count > 3 ? (f32) ValueI[3] : 0.0f;
				ret.MaxEdge.Y = Count > 4 ? (f32) ValueI[4] : 0.0f;
				ret.MaxEdge.Z = Count > 5 ? (f32) ValueI[5] : 0.0f;
			}
			return ret;

		}

		core::line2df CNumbersAttribute::getLine2d()
		{
			core::line2df ret;
			if (IsFloat)
			{
				ret.start.X = Count > 0 ? ValueF[0] : 0.0f;
				ret.start.Y = Count > 1 ? ValueF[1] : 0.0f;
				ret.end.X = Count > 2 ? ValueF[2] : 0.0f;
				ret.end.Y = Count > 3 ? ValueF[3] : 0.0f;
			}
			else
			{
				ret.start.X = Count > 0 ? (f32) ValueI[0] : 0.0f;
				ret.start.Y = Count > 1 ? (f32) ValueI[1] : 0.0f;
				ret.end.X = Count > 2 ? (f32) ValueI[2] : 0.0f;
				ret.end.Y = Count > 3 ? (f32) ValueI[3] : 0.0f;
			}
			return ret;
		}

		core::line3df CNumbersAttribute::getLine3d()
		{
			core::line3df ret;
			if (IsFloat)
			{
				ret.start.X = Count > 0 ? ValueF[0] : 0.0f;
				ret.start.Y = Count > 1 ? ValueF[1] : 0.0f;
				ret.start.Z = Count > 2 ? ValueF[2] : 0.0f;
				ret.end.X = Count > 3 ? ValueF[3] : 0.0f;
				ret.end.Y = Count > 4 ? ValueF[4] : 0.0f;
				ret.end.Z = Count > 5 ? ValueF[5] : 0.0f;
			}
			else
			{
				ret.start.X = Count > 0 ? (f32) ValueI[0] : 0.0f;
				ret.start.Y = Count > 1 ? (f32) ValueI[1] : 0.0f;
				ret.start.Z = Count > 2 ? (f32) ValueI[2] : 0.0f;
				ret.end.X = Count > 3 ? (f32) ValueI[3] : 0.0f;
				ret.end.Y = Count > 4 ? (f32) ValueI[4] : 0.0f;
				ret.end.Z = Count > 5 ? (f32) ValueI[5] : 0.0f;
			}
			return ret;
		}

		//! get float array
		core::array<f32> CNumbersAttribute::getFloatArray()
		{
			if (!IsFloat)
			{
				ValueF.clear();
				for (u32 i = 0; i < Count; ++i)
					ValueF.push_back((f32) ValueI[i]);
			}

			return ValueF;
		}

		//! get int array
		core::array<s32> CNumbersAttribute::getIntArray()
		{
			if (IsFloat)
			{
				ValueI.clear();
				for (u32 i = 0; i < Count; ++i)
					ValueI.push_back((s32) ValueF[i]);
			}

			return ValueI;
		}

		// setting values
		void CNumbersAttribute::setInt(s32 intValue)
		{
			// set all values
			for (u32 i = 0; i < Count; ++i)
				if (IsFloat)
					ValueF[i] = (f32) intValue;
				else
					ValueI[i] = intValue;
		}

		void CNumbersAttribute::setFloat(f32 floatValue)
		{
			// set all values
			for (u32 i = 0; i < Count; ++i)
				if (IsFloat)
					ValueF[i] = floatValue;
				else
					ValueI[i] = (s32) floatValue;
		}

		void CNumbersAttribute::setBool(bool boolValue)
		{
			setInt(boolValue ? 1 : 0);
		}

		void CNumbersAttribute::setString(const c8* text)
		{
			// parse text

			const c8* P = (const c8*) text;

			reset();

			u32 i = 0;

			for (i = 0; i < Count && *P; ++i)
			{
				while (*P && P[0] != '-'
						&& (P[0] == ' ' || (P[0] < '0' || P[0] > '9')))
					++P;

				// set value
				if (*P)
				{
					if (IsFloat)
					{
						f32 c = 0;
						P = core::fast_atof_move(P, c);
						ValueF[i] = c;
					}
					else
					{
						// todo: fix this to read ints properly
						f32 c = 0;
						P = core::fast_atof_move(P, c);
						ValueI[i] = (s32) c;

					}
				}
			}
			// todo: warning message
			//if (i < Count-1)
			//{
			//
			//}
		}

		void CNumbersAttribute::setVector2d(core::vector2df v)
		{
			reset();
			if (IsFloat)
			{
				if (Count > 0)
					ValueF[0] = v.X;
				if (Count > 1)
					ValueF[1] = v.Y;
			}
			else
			{
				if (Count > 0)
					ValueI[0] = (s32) v.X;
				if (Count > 1)
					ValueI[1] = (s32) v.Y;
			}
		}

		void CNumbersAttribute::setVector3d(core::vector3df v)
		{
			reset();
			if (IsFloat)
			{
				if (Count > 0)
					ValueF[0] = v.X;
				if (Count > 1)
					ValueF[1] = v.Y;
				if (Count > 2)
					ValueF[2] = v.Z;
			}
			else
			{
				if (Count > 0)
					ValueI[0] = (s32) v.X;
				if (Count > 1)
					ValueI[1] = (s32) v.Y;
				if (Count > 2)
					ValueI[2] = (s32) v.Z;
			}
		}

		void CNumbersAttribute::setColor(video::SColorf color)
		{
			reset();
			if (IsFloat)
			{
				if (Count > 0)
					ValueF[0] = color.r;
				if (Count > 1)
					ValueF[1] = color.g;
				if (Count > 2)
					ValueF[2] = color.b;
				if (Count > 3)
					ValueF[3] = color.a;
			}
			else
			{
				if (Count > 0)
					ValueI[0] = (s32) (color.r * 255);
				if (Count > 1)
					ValueI[1] = (s32) (color.g * 255);
				if (Count > 2)
					ValueI[2] = (s32) (color.b * 255);
				if (Count > 3)
					ValueI[3] = (s32) (color.a * 255);
			}

		}

		void CNumbersAttribute::setColor(video::SColor color)
		{
			reset();
			if (IsFloat)
			{
				if (Count > 0)
					ValueF[0] = (f32) color.getRed() / 255.0f;
				if (Count > 1)
					ValueF[1] = (f32) color.getGreen() / 255.0f;
				if (Count > 2)
					ValueF[2] = (f32) color.getBlue() / 255.0f;
				if (Count > 3)
					ValueF[3] = (f32) color.getAlpha() / 255.0f;
			}
			else
			{
				if (Count > 0)
					ValueI[0] = color.getRed();
				if (Count > 1)
					ValueI[1] = color.getGreen();
				if (Count > 2)
					ValueI[2] = color.getBlue();
				if (Count > 3)
					ValueI[3] = color.getAlpha();
			}
		}

		void CNumbersAttribute::setRect(core::recti value)
		{
			reset();
			if (IsFloat)
			{
				if (Count > 0)
					ValueF[0] = (f32) value.UpperLeftCorner.X;
				if (Count > 1)
					ValueF[1] = (f32) value.UpperLeftCorner.Y;
				if (Count > 2)
					ValueF[2] = (f32) value.LowerRightCorner.X;
				if (Count > 3)
					ValueF[3] = (f32) value.LowerRightCorner.Y;
			}
			else
			{
				if (Count > 0)
					ValueI[0] = value.UpperLeftCorner.X;
				if (Count > 1)
					ValueI[1] = value.UpperLeftCorner.Y;
				if (Count > 2)
					ValueI[2] = value.LowerRightCorner.X;
				if (Count > 3)
					ValueI[3] = value.LowerRightCorner.Y;
			}
		}

		void CNumbersAttribute::setMatrix(core::matrix4 value)
		{
			reset();
			if (IsFloat)
			{
				for (u32 r = 0; r < 4; ++r)
					for (u32 c = 0; c < 4; ++c)
						if (Count > c + r * 4)
							ValueF[c + r * 4] = value(r, c);
			}
			else
			{
				for (u32 r = 0; r < 4; ++r)
					for (u32 c = 0; c < 4; ++c)
						if (Count > c + r * 4)
							ValueI[c + r * 4] = (s32) value(r, c);
			}
		}

		void CNumbersAttribute::setQuaternion(core::quaternion value)
		{
			reset();
			if (IsFloat)
			{
				if (Count > 0)
					ValueF[0] = value.X;
				if (Count > 1)
					ValueF[1] = value.Y;
				if (Count > 2)
					ValueF[2] = value.Z;
				if (Count > 3)
					ValueF[3] = value.W;
			}
			else
			{
				if (Count > 0)
					ValueI[0] = (s32) value.X;
				if (Count > 1)
					ValueI[1] = (s32) value.Y;
				if (Count > 2)
					ValueI[2] = (s32) value.Z;
				if (Count > 3)
					ValueI[3] = (s32) value.W;
			}
		}

		void CNumbersAttribute::setBoundingBox(core::aabbox3d<f32> value)
		{
			reset();
			if (IsFloat)
			{
				if (Count > 0)
					ValueF[0] = value.MinEdge.X;
				if (Count > 1)
					ValueF[1] = value.MinEdge.Y;
				if (Count > 2)
					ValueF[2] = value.MinEdge.Z;
				if (Count > 3)
					ValueF[3] = value.MaxEdge.X;
				if (Count > 4)
					ValueF[4] = value.MaxEdge.Y;
				if (Count > 5)
					ValueF[5] = value.MaxEdge.Z;
			}
			else
			{
				if (Count > 0)
					ValueI[0] = (s32) value.MinEdge.X;
				if (Count > 1)
					ValueI[1] = (s32) value.MinEdge.Y;
				if (Count > 2)
					ValueI[2] = (s32) value.MinEdge.Z;
				if (Count > 3)
					ValueI[3] = (s32) value.MaxEdge.X;
				if (Count > 4)
					ValueI[4] = (s32) value.MaxEdge.Y;
				if (Count > 5)
					ValueI[5] = (s32) value.MaxEdge.Z;
			}
		}

		void CNumbersAttribute::setPlane(core::plane3df value)
		{
			reset();
			if (IsFloat)
			{
				if (Count > 0)
					ValueF[0] = value.Normal.X;
				if (Count > 1)
					ValueF[1] = value.Normal.Y;
				if (Count > 2)
					ValueF[2] = value.Normal.Z;
				if (Count > 3)
					ValueF[3] = value.D;
			}
			else
			{
				if (Count > 0)
					ValueI[0] = (s32) value.Normal.X;
				if (Count > 1)
					ValueI[1] = (s32) value.Normal.Y;
				if (Count > 2)
					ValueI[2] = (s32) value.Normal.Z;
				if (Count > 3)
					ValueI[3] = (s32) value.D;
			}
		}

		void CNumbersAttribute::setTriangle3d(core::triangle3df value)
		{
			reset();
			if (IsFloat)
			{
				if (Count > 0)
					ValueF[0] = value.pointA.X;
				if (Count > 1)
					ValueF[1] = value.pointA.Y;
				if (Count > 2)
					ValueF[2] = value.pointA.Z;
				if (Count > 3)
					ValueF[3] = value.pointB.X;
				if (Count > 4)
					ValueF[4] = value.pointB.Y;
				if (Count > 5)
					ValueF[5] = value.pointB.Z;
				if (Count > 6)
					ValueF[6] = value.pointC.X;
				if (Count > 7)
					ValueF[7] = value.pointC.Y;
				if (Count > 8)
					ValueF[8] = value.pointC.Z;
			}
			else
			{
				if (Count > 0)
					ValueI[0] = (s32) value.pointA.X;
				if (Count > 1)
					ValueI[1] = (s32) value.pointA.Y;
				if (Count > 2)
					ValueI[2] = (s32) value.pointA.Z;
				if (Count > 3)
					ValueI[3] = (s32) value.pointB.X;
				if (Count > 4)
					ValueI[4] = (s32) value.pointB.Y;
				if (Count > 5)
					ValueI[5] = (s32) value.pointB.Z;
				if (Count > 6)
					ValueI[6] = (s32) value.pointC.X;
				if (Count > 7)
					ValueI[7] = (s32) value.pointC.Y;
				if (Count > 8)
					ValueI[8] = (s32) value.pointC.Z;
			}
		}

		void CNumbersAttribute::setLine2d(core::line2di v)
		{
			reset();
			if (IsFloat)
			{
				if (Count > 0)
					ValueF[0] = (f32) v.start.X;
				if (Count > 1)
					ValueF[1] = (f32) v.start.Y;
				if (Count > 2)
					ValueF[2] = (f32) v.end.X;
				if (Count > 3)
					ValueF[3] = (f32) v.end.Y;
			}
			else
			{
				if (Count > 0)
					ValueI[0] = v.start.X;
				if (Count > 1)
					ValueI[1] = v.start.Y;
				if (Count > 2)
					ValueI[2] = v.end.X;
				if (Count > 3)
					ValueI[3] = v.end.Y;
			}
		}

		void CNumbersAttribute::setLine2d(core::line2df v)
		{
			reset();
			if (IsFloat)
			{
				if (Count > 0)
					ValueF[0] = v.start.X;
				if (Count > 1)
					ValueF[1] = v.start.Y;
				if (Count > 2)
					ValueF[2] = v.end.X;
				if (Count > 3)
					ValueF[3] = v.end.Y;
			}
			else
			{
				if (Count > 0)
					ValueI[0] = (s32) v.start.X;
				if (Count > 1)
					ValueI[1] = (s32) v.start.Y;
				if (Count > 2)
					ValueI[2] = (s32) v.end.X;
				if (Count > 3)
					ValueI[3] = (s32) v.end.Y;
			}
		}

		void CNumbersAttribute::setDimension2d(core::dimension2du v)
		{
			reset();
			if (IsFloat)
			{
				if (Count > 0)
					ValueF[0] = (f32) v.Width;
				if (Count > 1)
					ValueF[1] = (f32) v.Height;
			}
			else
			{
				if (Count > 0)
					ValueI[0] = v.Width;
				if (Count > 1)
					ValueI[1] = v.Height;
			}
		}

		//! set float array
		void CNumbersAttribute::setFloatArray(core::array<f32> &vals)
		{
			reset();

			for (u32 i = 0; i < vals.size() && i < Count; ++i)
			{
				if (IsFloat)
					ValueF[i] = vals[i];
				else
					ValueI[i] = (s32) vals[i];
			}
		}

		//! set int array
		void CNumbersAttribute::setIntArray(core::array<s32> &vals)
		{
			reset();

			for (u32 i = 0; i < vals.size() && i < Count; ++i)
			{
				if (IsFloat)
					ValueF[i] = (f32) vals[i];
				else
					ValueI[i] = vals[i];
			}
		}

		//! is it a number list?
		bool CNumbersAttribute::isNumberList()
		{
			return true;
		}

		//! is it a float list?
		bool CNumbersAttribute::isFloat()
		{
			return IsFloat;
		}

		E_ATTRIBUTE_TYPE CNumbersAttribute::getType() const
		{
			if (IsFloat)
				return EAT_FLOATARRAY;
			else
				return EAT_INTARRAY;
		}

		const c8* CNumbersAttribute::getTypeString() const
		{
			if (IsFloat)
				return "floatlist";
			else
				return "intlist";
		}

		//! clear all values
		void CNumbersAttribute::reset()
		{
			if (IsFloat)
				for (u32 i = 0; i < Count; ++i)
					ValueF[i] = 0.0f;
			else
				for (u32 i = 0; i < Count; ++i)
					ValueI[i] = 0;
		}
	}
}
