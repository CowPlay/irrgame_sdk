// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine" and the "irrXML" project.
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_PATH_H_INCLUDED__
#define __IRR_PATH_H_INCLUDED__

#include "core/irrgamecollections.h"

namespace irrgame
{
	namespace io
	{
		//! Used in places where we identify objects by a filename, but don't actually work with the real filename
		/** Irrlicht is internally not case-sensitive when it comes to names.
		 Also this class is a first step towards support for correctly serializing renamed objects.
		 */
		struct SPath
		{
				//! Constructor
				SPath()
				{
				}

				//! Constructor
				SPath(const stringc& p) :
						Path(p), InternalName(PathToName(p))
				{
				}

				//! Is smaller comparator
				bool operator <(const SPath& other) const
				{
					return InternalName < other.InternalName;
				}

				//! Set the path.
				void setPath(const stringc& p)
				{
					Path = p;
					InternalName = PathToName(p);
				}

				//! Get the path.
				const stringc& getPath() const
				{
					return Path;
				}
				;

				//! Get the name which is used to identify the file.
				//! This string is similar to the names and filenames used before Irrlicht 1.7
				const stringc& getInternalName() const
				{
					return InternalName;
				}

				//! Implicit cast to io::path
				operator stringc() const
				{
					return stringc(getPath());
				}

			protected:
				// convert the given path string to a name string.
				stringc PathToName(const stringc& p) const
				{
					stringc name(p);
					name.replace('\\', '/');
					name.make_lower();
					return name;
				}

			private:
				stringc Path;
				stringc InternalName;
		};

	} // io
} // irr

#endif // __IRR_PATH_H_INCLUDED__
