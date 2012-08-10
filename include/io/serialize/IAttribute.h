// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_ATTRIBUTE_H_INCLUDED__
#define __I_ATTRIBUTE_H_INCLUDED__

#include "core/IReferenceCounted.h"
#include "core/irrString.h"
#include "core/irrArray.h"
#include "core/line2d.h"
#include "core/line3d.h"
#include "core/triangle3d.h"
#include "core/rect.h"
#include "core/matrix4.h"
#include "core/quaternion.h"
#include "core/plane3d.h"
#include "core/vector2d.h"
#include "core/vector3d.h"

#include "video/SColor.h"

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

				virtual E_ATTRIBUTE_TYPE getType() const = 0;

				virtual const c8* getTypeString() const = 0;

			public:
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

				virtual core::array<core::stringc> getArray()
				{
					return core::array<core::stringc>();
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

				virtual core::vector2df getVector2d()
				{
					return core::vector2df();
				}

				virtual core::vector3df getVector3d()
				{
					return core::vector3df();
				}

				virtual core::recti getRect()
				{
					return core::recti();
				}

				virtual core::matrix4 getMatrix()
				{
					return core::matrix4();
				}

				virtual core::quaternion getQuaternion()
				{
					return core::quaternion();
				}

				virtual core::aabbox3df getBBox()
				{
					return core::aabbox3df();
				}

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

				virtual void setArray(const core::array<core::stringc>& arr)
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

				virtual void setVector2d(core::vector2df v)
				{
				}

				virtual void setVector3d(core::vector3df v)
				{
				}

				virtual void setRect(core::recti v)
				{
				}

				virtual void setMatrix(core::matrix4 v)
				{
				}

				virtual void setQuaternion(core::quaternion v)
				{
				}

				virtual void setBBox(core::aabbox3df v)
				{
				}

			public:

				core::stringc Name;

//				virtual core::triangle3df getTriangle()
//				{
//					return core::triangle3df();
//				}
//
//
//
//				virtual core::line2df getLine2d()
//				{
//					return core::line2df();
//				}
//
//				virtual core::line2di getLine2di()
//				{
//					return core::line2di();
//				}
//
//				virtual core::line3df getLine3d()
//				{
//					return core::line3df();
//				}
//
//				virtual core::line3di getLine3di()
//				{
//					return core::line3di();
//				}
//				virtual core::dimension2du getDimension2d()
//				{
//					return core::dimension2du();
//				}
//
//				virtual core::plane3df getPlane()
//				{
//					return core::plane3df();
//				}
//
//
//
//				virtual void* getUserPointer()
//				{
//					return 0;
//				}

//
//				virtual void setVector(core::vector3df v)
//				{
//				}
//

//				virtual void setTriangle(core::triangle3df v)
//				{
//				}

//				virtual void setLine2d(core::line2df v)
//				{
//				}
//
//				virtual void setLine2d(core::line2di v)
//				{
//				}
//
//				virtual void setLine3d(core::line3df v)
//				{
//				}
//
//				virtual void setLine3d(core::line3di v)
//				{
//				}
//
//				virtual void setDimension2d(core::dimension2du v)
//				{
//				}
//
//
//
//				virtual void setPlane(core::plane3df v)
//				{
//				}
//
//				virtual void setUserPointer(void* v)
//				{
//				}
//
//
//
//
//
//

		};

	} // end namespace io
} // end namespace irrgame

#endif
