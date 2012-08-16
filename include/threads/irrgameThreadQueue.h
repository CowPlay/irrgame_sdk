/*
 * irrgameThreadQueue.h
 *
 *  Created on: Aug 6, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMETHREADQUEUE_H_
#define IRRGAMETHREADQUEUE_H_
#include "core/IReferenceCounted.h"
#include "delegate/delegate.h"

namespace irrgame
{
	namespace threads
	{

		//! Use this delegate for add action to specify queue
		typedef C_DELEGATE<int, void*> delegateAction;

		enum EQueueType
		{
			//! Use for render
			EQT_REALTIME = 0,

			//! Use for logic
			EQT_HIGHPRIORITY,

			//! Use for load resources in background or actions with low priority
			EQT_BACKGROUND
		};

		//! Represents thread queue
		class irrgameThreadQueue: public IReferenceCounted
		{
			public:
				//! Destructor
				~irrgameThreadQueue()
				{

				}

				//! Start process actions.
				static void startProcess();

				//! Adds action to specify queue
				static void addAction(delegateAction* action, EQueueType qType);
		};
	}
}

#endif /* IRRGAMETHREADQUEUE_H_ */
