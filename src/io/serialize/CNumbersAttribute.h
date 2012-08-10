/*
 * CNumbersAttribute.h
 *
 *  Created on: Aug 9, 2012
 *      Author: gregorytkach
 */

#ifndef CNUMBERSATTRIBUTE_H_
#define CNUMBERSATTRIBUTE_H_
#include "io/serialize/IAttribute.h"

namespace irrgame
{
	namespace io
	{
		// Base class for all attributes which are a list of numbers-
		// vectors, colors, positions, triangles, etc
		class CNumbersAttribute: public IAttribute
		{
			public:

				//! Default constructor for colorf list
				CNumbersAttribute(const c8* name, video::SColorf value);

				//! Default constructor for color list
				CNumbersAttribute(const c8* name, video::SColor value);

				//! Default constructor for vector2df list
				CNumbersAttribute(const c8* name, core::vector2df value);

				//! Default constructor for vector3df list
				CNumbersAttribute(const c8* name, core::vector3df value);

				//! Default constructor for recti list
				CNumbersAttribute(const c8* name, core::recti value);

				//! Default constructor for rectf list
				CNumbersAttribute(const c8* name, core::rectf value);

				//! Default constructor for matrix list
				CNumbersAttribute(const c8* name, core::matrix4 value);

				CNumbersAttribute(const c8* name, core::quaternion value);

				CNumbersAttribute(const c8* name, core::aabbox3df value);

				CNumbersAttribute(const c8* name, core::plane3df value);

				CNumbersAttribute(const c8* name, core::triangle3df value);

				CNumbersAttribute(const c8* name, core::line2di value);

				CNumbersAttribute(const c8* name, core::line2df value);

				CNumbersAttribute(const c8* name, core::line3df value);

				//! Default constructor for dimension2du list
				CNumbersAttribute(const c8* name, core::dimension2du value);

				//! Default constructor for dimension2df list
				CNumbersAttribute(const c8* name, core::dimension2df value);

				// getting values
				virtual s32 getInt();

				virtual f32 getFloat();

				virtual bool getBool();

				virtual core::stringc getString();

				virtual core::vector2df getVector2d();

				virtual core::vector3df getVector3d();

				virtual video::SColorf getColorf();

				virtual video::SColor getColor();

				virtual core::recti getRect();

				virtual core::matrix4 getMatrix();

				virtual core::quaternion getQuaternion();

				virtual core::triangle3df getTriangle();

				virtual core::plane3df getPlane();

				virtual core::aabbox3df getBBox();

				virtual core::line2df getLine2d();

				virtual core::line3df getLine3d();

				//! get float array
				virtual core::array<f32> getFloatArray();

				//! get int array
				virtual core::array<s32> getIntArray();

				// setting values
				virtual void setInt(s32 intValue);

				virtual void setFloat(f32 floatValue);

				virtual void setBool(bool boolValue);

				virtual void setString(const c8* text);

				virtual void setVector2d(core::vector2df v);

				virtual void setVector3d(core::vector3df v);

				virtual void setColor(video::SColorf color);

				virtual void setColor(video::SColor color);

				virtual void setRect(core::recti value);

				virtual void setMatrix(core::matrix4 value);

				virtual void setQuaternion(core::quaternion value);

				virtual void setBoundingBox(core::aabbox3d<f32> value);

				virtual void setPlane(core::plane3df value);

				virtual void setTriangle3d(core::triangle3df value);

				virtual void setLine2d(core::line2di v);

				virtual void setLine2d(core::line2df v);

				virtual void setDimension2d(core::dimension2du v);

				//! set float array
				virtual void setFloatArray(core::array<f32> &vals);

				//! set int array
				virtual void setIntArray(core::array<s32> &vals);

				//! is it a number list?
				virtual bool isNumberList();

				//! is it a float list?
				virtual bool isFloat();

				virtual E_ATTRIBUTE_TYPE getType() const;

				virtual const c8* getTypeString() const;

			protected:

				//! clear all values
				void reset();

			protected:
				core::array<s32> ValueI;
				core::array<f32> ValueF;
				u32 Count;
				bool IsFloat;
		};

	}
}

#endif /* CNUMBERSATTRIBUTE_H_ */
