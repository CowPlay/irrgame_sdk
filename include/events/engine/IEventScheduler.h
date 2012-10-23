/*
 * IThreadPool.h
 *
 *  Created on: Jul 25, 2012
 *      Author: gregorytkach
 */

#ifndef ITHREADPOOL_H_
#define ITHREADPOOL_H_

#include "core/irrgamebase.h"
#include "core/irrgamecollections.h"
#include "delegate/delegate.h"
namespace irrgame
{
	namespace events
	{

		enum EEventPriority
		{
			//! Use for render
			EAP_REALTIME = 0,

			//! Use for logic
			EAP_HIGHPRIORITY,

			//! Use for load resources in background or events with low priority
			EAP_BACKGROUND
		};

		//! Use this delegate for add event to specify queue
		typedef CDelegate<int, void*> delegateEvent;

		//! Event sheduler which manage engine events.
		//! Represents a simple scheduler which have 3 threads with different priorities.
		//! Напрямую разраб не должен обращаться к шедулеру. Все ивенты должны закидывать сюда манагеры.
		class IEventScheduler: public IReferenceCounted
		{
			public:
				//! Singleton realization
				static IEventScheduler& getInstance();

			private:
				//! Default constructor. Should use only one time.
				IEventScheduler();

				//! Destructor. Should use only one time.
				~IEventScheduler();

				//! Copy constructor. Do not implement.
				IEventScheduler(const IEventScheduler& root);

				//! Override equal operator. Do not implement.
				const IEventScheduler& operator=(IEventScheduler&);

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
