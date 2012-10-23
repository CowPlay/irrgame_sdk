/*
 * IEventSheduler.cpp
 *
 *  Created on: Aug 22, 2012
 *      Author: gregorytkach
 */

#include "events/engine/IEventScheduler.h"
#include "threads/irrgameThread.h"

using namespace irrgame::threads;

namespace irrgame
{
	namespace events
	{

		//! Singleton realization
		IEventScheduler& IEventScheduler::getInstance()
		{
			static IEventScheduler instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		IEventScheduler::IEventScheduler()
		{
		}

		//! Destructor. Should use only one time.
		IEventScheduler::~IEventScheduler()
		{
		}

		//! Adds event to specify queue
		void IEventScheduler::addEvent(delegateEvent* e,
				EEventPriority qType)
		{
			IRR_ASSERT(e != 0);

			switch (qType)
			{
				case EAP_REALTIME:
					this->RealtimeEvents.pushBack(e);
					break;

				case EAP_HIGHPRIORITY:
					this->HighpriorityEvents.pushBack(e);
					break;

				case EAP_BACKGROUND:
					this->BackgroundEvents.pushBack(e);
					break;
			}
		}

		//! Start process events.
		void IEventScheduler::startProcess()
		{
			delegateThreadCallback* callback1 = new delegateThreadCallback;
			(*callback1) += NewDelegate(this,
					&IEventScheduler::proceedHPEvents);

			irrgameThread* thread1 = createIrrgameThread(callback1, 0,
					ETP_NORMAL);

			delegateThreadCallback* callback2 = new delegateThreadCallback;
			(*callback2) += NewDelegate(this,
					&IEventScheduler::proceedBGEvents);

			irrgameThread* thread2 = createIrrgameThread(callback2, 0, ETP_LOW);

			thread1->start();
			thread2->start();
		}

		//! Proceed next real time event in main thread.
		void IEventScheduler::proceedNextRealTimeEvent()
		{
			if (RealtimeEvents.empty())
			{
				return;
			}

			core::list<delegateEvent*>::Iterator it = RealtimeEvents.begin();

			(*(*it))((void*) 0);

			//remove event from list
			RealtimeEvents.erase(it);

			printf("proceedRTEvents\n");
		}

		int IEventScheduler::proceedHPEvents(void* stub)
		{
			while (true)
			{
				if (HighpriorityEvents.empty())
				{
					irrgameThread::sleep(50);
					continue;
				}

				core::list<delegateEvent*>::Iterator it =
						HighpriorityEvents.begin();

				(*(*it))((void*) 0);

				//remove event from list
				HighpriorityEvents.erase(it);

				printf("proceedHPEvents\n");
			}

			return 0;
		}

		int IEventScheduler::proceedBGEvents(void* stub)
		{
			while (true)
			{
				if (BackgroundEvents.empty())
				{
					irrgameThread::sleep(50);
					continue;
				}

				core::list<delegateEvent*>::Iterator it =
						BackgroundEvents.begin();

				(*(*it))((void*) 0);

				//remove event from list
				BackgroundEvents.erase(it);

				printf("proceedBGEvents\n");
			}

			return 0;
		}

	}
}

