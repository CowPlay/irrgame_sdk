// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_ATTRIBUTE_H_INCLUDED__
#define __I_ATTRIBUTE_H_INCLUDED__

#include "core/engine/IReferenceCounted.h"

#include "core/collections/stringc.h"
#include "core/collections/array.h"

#include "core/shapes/vector2d.h"
#include "core/shapes/vector3d.h"
#include "core/shapes/rect.h"
#include "core/shapes/triangle3d.h"
#include "core/shapes/line2d.h"
#include "core/shapes/line3d.h"

#include "core/math/matrix4.h"
#include "core/math/quaternion.h"

#include "video/color/SColor.h"
#include "video/color/SColorf.h"

#include "io/serialize/EAttributeTypes.h"

namespace irrgame
{
	namespace io
	{

		class IAttribute: public virtual IReferenceCounted
		{
				//! Interface
			public:

				//! Destructor
				virtual ~IAttribute()
				{
				}

				virtual EAttributeType getType() const = 0;

				virtual const c8* getTypeString() const = 0;

			public:

				/*
				 *
				 *Getters
				 *
				 */

				//! Dummies
				virtual s32 getInt()
				{
					return 0;
				}

				virtual f32 getFloat()
				{
					return 0;
				}

				virtual bool getBool()
				{
					return false;
				}

				virtual core::stringc getString()
				{
					return core::stringc();
				}

				virtual void getBinary(void* outdata, s32 maxLength)
				{
				}

				virtual arraystr getArray()
				{
					return arraystr();
				}

				virtual video::SColorf getColorf()
				{
					return video::SColorf(1.0f, 1.0f, 1.0f, 1.0f);
				}

				virtual video::SColor getColor()
				{
					return video::SColor(255, 255, 255, 255);
				}

				virtual const c8* getEnum()
				{
					return 0;
				}

				virtual vector2df getVector2d()
				{
					return vector2df();
				}

				virtual vector3df getVector3d()
				{
					return vector3df();
				}

				virtual recti getRect()
				{
					return recti();
				}

				virtual matrix4f getMatrix()
				{
					return matrix4f();
				}

				virtual core::quaternion getQuaternion()
				{
					return core::quaternion();
				}

				virtual aabbox3df getBBox()
				{
					return aabbox3df();
				}

				virtual triangle3df getTriangle()
				{
					return triangle3df();
				}

				virtual plane3df getPlane()
				{
					return plane3df();
				}

				virtual line2df getLine2d()
				{
					return line2df();
				}

				virtual line3df getLine3d()
				{
					return line3df();
				}

				virtual dimension2df getDimension2d()
				{
					return dimension2df();
				}

				/*
				 *
				 *Setters
				 *
				 */

				virtual void setInt(s32 intValue)
				{
				}

				virtual void setFloat(f32 floatValue)
				{
				}

				virtual void setString(const c8* text)
				{
				}

				virtual void setBinary(void* data, s32 maxLenght)
				{
				}

				virtual void setArray(const arraystr& arr)
				{
				}

				virtual void setBool(bool boolValue)
				{
				}

				virtual void setEnum(const c8* enumValue,
						const c8* const * enumerationLiterals)
				{
				}

				virtual void setColor(video::SColorf color)
				{
				}

				virtual void setColor(video::SColor color)
				{
				}

				virtual void setVector2d(vector2df v)
				{
				}

				virtual void setVector3d(vector3df v)
				{
				}

				virtual void setRect(recti v)
				{
				}

				virtual void setMatrix(matrix4f v)
				{
				}

				virtual void setQuaternion(core::quaternion v)
				{
				}

				virtual void setBBox(aabbox3df v)
				{
				}

				virtual void setTriangle(triangle3df v)
				{
				}

				virtual void setPlane(plane3df v)
				{
				}

				virtual void setLine2d(line2df v)
				{
				}

				virtual void setLine3d(line3df v)
				{
				}

				virtual void setDimension2d(dimension2df v)
				{
				}

			public:

				core::stringc Name;

		};
	} // end namespace io
} // end namespace irrgame

#endif
