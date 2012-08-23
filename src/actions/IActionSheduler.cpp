/*
 * IActionSheduler.cpp
 *
 *  Created on: Aug 22, 2012
 *      Author: gregorytkach
 */

#include "actions/IActionScheduler.h"
#include "threads/irrgameThread.h"

using namespace irrgame::threads;

namespace irrgame
{
	namespace actions
	{

		//! Singleton realization
		IActionScheduler& IActionScheduler::getInstance()
		{
			static IActionScheduler instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		IActionScheduler::IActionScheduler()
		{
		}

		//! Destructor. Should use only one time.
		IActionScheduler::~IActionScheduler()
		{
		}

		//! Adds action to specify queue
		void IActionScheduler::addAction(delegateAction* action,
				EActionPriority qType)
		{
			IRR_ASSERT(action != 0);

			//TODO: add monitor::enter

			switch (qType)
			{
				case EAP_REALTIME:
					this->RealtimeActions.push_back(action);
					break;

				case EAP_HIGHPRIORITY:
					this->HighpriorityActions.push_back(action);
					break;

				case EAP_BACKGROUND:
					this->BackgroundActions.push_back(action);
					break;
			}
		}

		//! Start process actions.
		void IActionScheduler::startProcess()
		{
			delegateThreadCallback* callback0 = new delegateThreadCallback;
			(*callback0) += NewDelegate(this,
					&IActionScheduler::proceedRTActions);

			irrgameThread* thread0 = createIrrgameThread(callback0, 0,
					ETP_HIGH);

			delegateThreadCallback* callback1 = new delegateThreadCallback;
			(*callback1) += NewDelegate(this,
					&IActionScheduler::proceedHPActions);

			irrgameThread* thread1 = createIrrgameThread(callback1, 0,
					ETP_NORMAL);

			delegateThreadCallback* callback2 = new delegateThreadCallback;
			(*callback2) += NewDelegate(this,
					&IActionScheduler::proceedBGActions);

			irrgameThread* thread2 = createIrrgameThread(callback2, 0, ETP_LOW);

			thread0->start();
			thread1->start();
			thread2->start();
		}

		int IActionScheduler::proceedRTActions(void* stub)
		{
			while (true)
			{
				printf("proceedRTActions\n");
			}

			return 0;
		}

		int IActionScheduler::proceedHPActions(void* stub)
		{
			while (true)
			{
				printf("proceedHPActions\n");
			}

			return 0;
		}

		int IActionScheduler::proceedBGActions(void* stub)
		{
			while (true)
			{
				printf("proceedBGActions\n");
			}

			return 0;
		}

	}
}

