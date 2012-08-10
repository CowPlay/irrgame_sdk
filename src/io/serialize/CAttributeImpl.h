//// Copyright (C) 2002-2009 Nikolaus Gebhardt
//// This file is part of the "Irrlicht Engine".
//// For conditions of distribution and use, see copyright notice in irrlicht.h
//
//#include "CAttributes.h"
//#include "fast_atof.h"
//#include "ITexture.h"
//#include "IVideoDriver.h"
//
//namespace irr
//{
//namespace io
//{
//
///*
//	basic types
//*/
//

//

//
//
//

//

//
//

//
//
//

//
//

//

//
//
//

//

//

//
//

//
//// Attribute implemented for planes
//class CPlaneAttribute : public CNumbersAttribute
//{
//public:
//
//	CPlaneAttribute(const char* name, core::plane3df value) : CNumbersAttribute(name, value) { }
//
//	virtual E_ATTRIBUTE_TYPE getType() const
//	{
//		return EAT_PLANE;
//	}
//
//	virtual const wchar_t* getTypeString() const
//	{
//		return L"plane";
//	}
//};
//
//// Attribute implemented for triangles
//class CTriangleAttribute : public CNumbersAttribute
//{
//public:
//
//	CTriangleAttribute(const char* name, core::triangle3df value) : CNumbersAttribute(name, value) { }
//
//	virtual E_ATTRIBUTE_TYPE getType() const
//	{
//		return EAT_TRIANGLE3D;
//	}
//
//	virtual core::plane3df getPlane()
//	{
//		return getTriangle().getPlane();
//	}
//
//	virtual const wchar_t* getTypeString() const
//	{
//		return L"triangle";
//	}
//};
//
//
//// Attribute implemented for 2d lines
//class CLine2dAttribute : public CNumbersAttribute
//{
//public:
//
//	CLine2dAttribute(const char* name, core::line2df value) : CNumbersAttribute(name, value) { }
//
//	virtual E_ATTRIBUTE_TYPE getType() const
//	{
//		return EAT_LINE2D;
//	}
//
//	virtual const wchar_t* getTypeString() const
//	{
//		return L"line2d";
//	}
//};
//
//// Attribute implemented for 3d lines
//class CLine3dAttribute : public CNumbersAttribute
//{
//public:
//
//	CLine3dAttribute(const char* name, core::line3df value) : CNumbersAttribute(name, value) { }
//
//	virtual E_ATTRIBUTE_TYPE getType() const
//	{
//		return EAT_LINE3D;
//	}
//
//	virtual const wchar_t* getTypeString() const
//	{
//		return L"line3d";
//	}
//};
//
//
//// vector2df
//// dimension2du
//
///*
//	Special attributes
//*/
//
//

//
//
//
//
//

//
//

//
//

//
//
//

//
//
//// Attribute implemented for user pointers
//class CUserPointerAttribute : public IAttribute
//{
//public:
//
//	CUserPointerAttribute(const char* name, void* value)
//	{
//		Name = name;
//		Value = value;
//	}
//
//	virtual s32 getInt()
//	{
//		return *static_cast<s32*>(Value);
//	}
//
//	virtual bool getBool()
//	{
//		return (Value != 0);
//	}
//
//	virtual core::stringw getStringW()
//	{
//		wchar_t buf[32];
//		swprintf(buf, 32, L"%p", Value);
//
//		return core::stringw(buf);
//	}
//
//	virtual void setString(const char* text)
//	{
//		sscanf(text, "0x%x", (unsigned int*)(&Value));
//	}
//
//	virtual E_ATTRIBUTE_TYPE getType() const
//	{
//		return EAT_USER_POINTER;
//	}
//
//	virtual void setUserPointer(void* v)
//	{
//		Value = v;
//	}
//
//	virtual void* getUserPointer()
//	{
//		return Value;
//	}
//
//
//	virtual const wchar_t* getTypeString() const
//	{
//		return L"userPointer";
//	}
//
//	void* Value;
//};

//
//} // end namespace io
//} // end namespace irr
