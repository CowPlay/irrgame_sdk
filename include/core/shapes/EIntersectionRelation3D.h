/*
 * EIntersectionRelation3D.h
 *
 *  Created on: Nov 5, 2012
 *      Author: gregorytkach
 */

#ifndef EINTERSECTIONRELATION3D_H_
#define EINTERSECTIONRELATION3D_H_

namespace irrgame
{
	namespace core
	{
		//! Enumeration for intersection relations of 3d objects
		enum EIntersectionRelation3D
		{
			ISREL3D_FRONT = 0,
			ISREL3D_BACK,
			ISREL3D_PLANAR,
			ISREL3D_SPANNING,
			ISREL3D_CLIPPED,

			//! Not used
			ISREL3D_COUNT
		};
	}  // namespace core
}  // namespace irrgame

#endif /* EINTERSECTIONRELATION3D_H_ */
