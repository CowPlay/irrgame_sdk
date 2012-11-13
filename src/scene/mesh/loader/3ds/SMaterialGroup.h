/*
 * SMaterialGroup.h
 *
 *  Created on: Nov 12, 2012
 *      Author: gregorytkach
 */

#ifndef SMATERIALGROUP_H_
#define SMATERIALGROUP_H_

namespace irrgame
{
	namespace scene
	{
		struct SMaterialGroup
		{
			public:

				//! Default constructor
				SMaterialGroup();

				//! Copy constructor
				SMaterialGroup(const SMaterialGroup& other);

				//! Destructor
				virtual ~SMaterialGroup();

				void clear();

				void operator=(const SMaterialGroup& other);

			public:

				core::stringc MaterialName;
				u16 faceCount;
				u16* faces;
		};

		//! Default constructor
		SMaterialGroup::SMaterialGroup() :
				faceCount(0), faces(0)
		{
		}

		//! Copy constructor
		SMaterialGroup::SMaterialGroup(const SMaterialGroup& other)
		{
			*this = other;
		}

		//! Destructor
		SMaterialGroup::~SMaterialGroup()
		{
			clear();
		}

		void SMaterialGroup::clear()
		{
			delete[] faces;
			faces = 0;
			faceCount = 0;
		}

		void SMaterialGroup::operator=(const SMaterialGroup& other)
		{
			MaterialName = other.MaterialName;
			faceCount = other.faceCount;
			faces = new u16[faceCount];
			for (u32 i = 0; i < faceCount; ++i)
			{
				faces[i] = other.faces[i];
			}
		}

	}  // namespace scene
}  // namespace irrgame

#endif /* SMATERIALGROUP_H_ */
