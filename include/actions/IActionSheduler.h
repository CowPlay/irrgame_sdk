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

		enum EActionPriority
		{
			//! Use for render
			EAP_REALTIME = 0,

			//! Use for logic
			EAP_HIGHPRIORITY,

			//! Use for load resources in background or actions with low priority
			EAP_BACKGROUND
		};

		//! Use this delegate for add action to specify queue
		typedef C_DELEGATE<int, void*> delegateAction;

		//! Action sheduler which manage engine actions.
		//! Represents a simple scheduler which have 3 threads with different priorities.
		class IActionSheduler: public IReferenceCounted
		{
			public:

				//! Adds action to specify queue
				static void addAction(delegateAction* action, EQueueType qType);

				//! Start process actions.
				static void startProcess();
		};

	}
}

#endif /* ITHREADPOOL_H_ */
