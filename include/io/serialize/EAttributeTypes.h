// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __E_ATTRIBUTES_H_INCLUDED__
#define __E_ATTRIBUTES_H_INCLUDED__

namespace irrgame
{
	namespace io
	{

		//! Types of attributes available for IAttributes
		enum EAttributeType
		{
			// integer attribute
			EAT_INT = 0,

			// float attribute
			EAT_FLOAT,

			// string attribute
			EAT_STRING,

			// boolean attribute
			EAT_BOOL,

			// enumeration attribute
			EAT_ENUM,

			// color attribute
			EAT_COLOR,

			// floating point color attribute
			EAT_COLORF,

			// dimension2df attribute
			EAT_DIMENSION2D,

			// 2d vector attribute
			EAT_VECTOR2D,

			// 3d vector attribute
			EAT_VECTOR3D,

			// rectangle attribute
			EAT_RECT,

			// matrix attribute
			EAT_MATRIX,

			// quaternion attribute
			EAT_QUATERNION,

			// 3d bounding box
			EAT_BBOX,

			// plane
			EAT_PLANE,

			// 3d triangle
			EAT_TRIANGLE3D,

			// line 2d
			EAT_LINE2D,

			// line 3d
			EAT_LINE3D,

			// array of stringws attribute
			EAT_STRINGARRAY,

			// array of float
			EAT_FLOATARRAY,

			// array of int
			EAT_INTARRAY,

			// binary data attribute
			EAT_BINARY,

			// user pointer void*
			EAT_USER_POINTER,

			// known attribute type count
			EAT_COUNT,

			// unknown attribute
			EAT_UNKNOWN
		};

	} // end namespace io
} // end namespace irr

#endif
