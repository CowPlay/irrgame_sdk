/*
 * IThreadPool.h
 *
 *  Created on: Jul 25, 2012
 *      Author: gregorytkach
 */

#ifndef ITHREADPOOL_H_
#define ITHREADPOOL_H_

#include "core/delegate.h"
#include "core/collections/list/list.h"
#include "EEventPriority.h"

namespace irrgame
{
	namespace events
	{
		//! Use this delegate for add event to specify queue
		typedef delegate<s32, void*> delegateEvent;

		//! Event sheduler which manage engine events.
		//! Represents a simple scheduler which have 3 threads with different priorities.
		//! Напрямую разраб не должен обращаться к шедулеру. Все ивенты должны закидывать сюда манагеры.
		class SharedEventScheduler
		{
			public:
				//! Singleton realization
				static SharedEventScheduler& getInstance();

			private:
				//! Default constructor. Should use only one time.
				SharedEventScheduler();

				//! Destructor. Should use only one time.
				virtual ~SharedEventScheduler();

				//! Copy constructor. Do not implement.
				SharedEventScheduler(const SharedEventScheduler& root);

				//! Override equal operator. Do not implement.
				const SharedEventScheduler& operator=(SharedEventScheduler&);

			public:

				//! Adds event to specify queue
				void addEvent(delegateEvent* e, EEventPriority qType);

				//! Start process events.
				void startProcess();

				//! Proceed next real time event in main thread.
				//! Must be call manually
				void proceedNextRealTimeEvent();

			private:
				int proceedHPEvents(void* stub);
				int proceedBGEvents(void* stub);

			private:
				core::list<delegateEvent*> RealtimeEvents;
				core::list<delegateEvent*> HighpriorityEvents;
				core::list<delegateEvent*> BackgroundEvents;
		};
	}

}

#endif /* ITHREADPOOL_H_ */
