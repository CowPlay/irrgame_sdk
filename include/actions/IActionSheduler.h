/*
 * IThreadPool.h
 *
 *  Created on: Jul 25, 2012
 *      Author: gregorytkach
 */

#ifndef ITHREADPOOL_H_
#define ITHREADPOOL_H_

#include "./core/IReferenceCounted.h"
#include "./delegate/delegate.h"
namespace irrgame
{
	namespace actions
	{

		typedef C_DELEGATE<int, void*> delegateAction;

		//! Action sheduler which manage engine actions
		class IActionSheduler : public IReferenceCounted
		{
			public:

			//addAction(delegateAction* action);
		};

	}
}

#endif /* ITHREADPOOL_H_ */
