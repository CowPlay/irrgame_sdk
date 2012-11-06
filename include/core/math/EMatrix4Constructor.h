/*
 * EMatrix4Constructor.h
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#ifndef EMATRIX4CONSTRUCTOR_H_
#define EMATRIX4CONSTRUCTOR_H_

namespace irrgame
{
	namespace core
	{

		//! Matrix4 Constructor Flags
		enum EMatrix4Constructor
		{
			EM4CONST_NOTHING = 0,
			EM4CONST_COPY,
			EM4CONST_IDENTITY,
			EM4CONST_TRANSPOSED,
			EM4CONST_INVERSE,
			EM4CONST_INVERSE_TRANSPOSED,

			//! Not used
			EM4CONST_COUNT
		};

	}  // namespace core
}  // namespace irrgame

#endif /* EMATRIX4CONSTRUCTOR_H_ */
