/*
 * EAllocStrategy.h
 *
 *  Created on: Nov 1, 2012
 *      Author: gregorytkach
 */

#ifndef EALLOCSTRATEGY_H_
#define EALLOCSTRATEGY_H_

namespace irrgame
{
	namespace core
	{
		//! defines an allocation strategy
		enum EAllocStrategy
		{
			AS_SAFE = 0,
			AS_DOUBLE = 1,
			AS_SQRT = 2,

			//! Not used
			AS_COUNT
		};
	}  // namespace core
}  // namespace irrgame

#endif /* EALLOCSTRATEGY_H_ */
