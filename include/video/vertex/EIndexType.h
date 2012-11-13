// Copyright (C) 2008-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef EINDEX_TYPE_H_INCLUDED_
#define EINDEX_TYPE_H_INCLUDED_

namespace irrgame
{
	namespace video
	{
		enum EIndexType
		{
			EIT_16BIT = 0, EIT_32BIT,

			//! Not used
			EIT_COUNT
		};

	/*
	 //! vertex index used by the Irrlicht engine.
	 template <class T>
	 struct SSpecificVertexIndex
	 {
	 T Index;

	 //! default constructor
	 SSpecificVertexIndex() {}

	 //! constructor
	 SSpecificVertexIndex(u32 _index) :Index(_index) {}

	 bool operator==(const SSpecificVertexIndex& other) const
	 {
	 return (Index == other.Index);
	 }

	 bool operator!=(const SSpecificVertexIndex& other) const
	 {
	 return (Index != other.Index);
	 }

	 bool operator<(const SSpecificVertexIndex& other) const
	 {
	 return (Index < other.Index);
	 }

	 SSpecificVertexIndex operator+(const u32& other) const
	 {
	 return SSpecificVertexIndex(Index + other);
	 }

	 operator const u32() const
	 {
	 return (const u32)Index;
	 }

	 E_INDEX_TYPE getType() const
	 {
	 if (sizeof(T)==sizeof(u16))
	 	 return video::EIT_16BIT;
	 return video::EIT_32BIT;
	 }

	 };

	 //typedef SSpecificVertexIndex<u16> SVertexIndex;

	 typedef u32 SVertexIndex;
	 */

	} // end namespace video
} // end namespace irrgame

#endif /* EINDEX_TYPE_H_INCLUDED_ */

