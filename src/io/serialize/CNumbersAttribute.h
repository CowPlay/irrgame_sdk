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
				CNumbersAttribute(const c8* name, vector2df value);

				//! Default constructor for vector3df list
				CNumbersAttribute(const c8* name, vector3df value);

				//! Default constructor for recti list
				CNumbersAttribute(const c8* name, recti value);

				//! Default constructor for rectf list
				CNumbersAttribute(const c8* name, rectf value);

				//! Default constructor for matrix list
				CNumbersAttribute(const c8* name, matrix4f value);

				CNumbersAttribute(const c8* name, core::quaternion value);

				CNumbersAttribute(const c8* name, aabbox3df value);

				CNumbersAttribute(const c8* name, plane3df value);

				CNumbersAttribute(const c8* name, triangle3df value);

				CNumbersAttribute(const c8* name, line2di value);

				CNumbersAttribute(const c8* name, line2df value);

				CNumbersAttribute(const c8* name, line3df value);

				//! Default constructor for dimension2du list
				CNumbersAttribute(const c8* name, dimension2du value);

				//! Default constructor for dimension2df list
				CNumbersAttribute(const c8* name, dimension2df value);

				// getting values
				virtual s32 getInt();

				virtual f32 getFloat();

				virtual bool getBool();

				virtual core::stringc getString();

				virtual vector2df getVector2d();

				virtual vector3df getVector3d();

				virtual video::SColorf getColorf();

				virtual video::SColor getColor();

				virtual recti getRect();

				virtual matrix4f getMatrix();

				virtual core::quaternion getQuaternion();

				virtual triangle3df getTriangle();

				virtual plane3df getPlane();

				virtual aabbox3df getBBox();

				virtual line2df getLine2d();

				virtual line3df getLine3d();

				//! get float array
				virtual arrayf getFloatArray();

				//! get int array
				virtual arrayi getIntArray();

				// setting values
				virtual void setInt(s32 intValue);

				virtual void setFloat(f32 floatValue);

				virtual void setBool(bool boolValue);

				virtual void setString(const c8* text);

				virtual void setVector2d(vector2df v);

				virtual void setVector3d(vector3df v);

				virtual void setColor(video::SColorf color);

				virtual void setColor(video::SColor color);

				virtual void setRect(recti value);

				virtual void setMatrix(matrix4f value);

				virtual void setQuaternion(core::quaternion value);

				virtual void setBoundingBox(aabbox3df value);

				virtual void setPlane(plane3df value);

				virtual void setTriangle3d(triangle3df value);

				virtual void setLine2d(line2di v);

				virtual void setLine2d(line2df v);

				virtual void setDimension2d(dimension2du v);

				//! set float array
				virtual void setFloatArray(arrayf &vals);

				//! set int array
				virtual void setIntArray(arrayi &vals);

				//! is it a number list?
				virtual bool isNumberList();

				//! is it a float list?
				virtual bool isFloat();

				virtual EAttributeType getType() const;

				virtual const c8* getTypeString() const;

			protected:

				//! clear all values
				void reset();

			protected:
				arrayi ValueI;
				arrayf ValueF;
				u32 Count;
				bool IsFloat;
		};

	}
}

#endif /* CNUMBERSATTRIBUTE_H_ */
