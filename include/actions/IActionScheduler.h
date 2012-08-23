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
		//! Напрямую разраб не должен обращаться к шедулеру. Все экшены должны закидывать сюда манагеры.
		class IActionScheduler: public IReferenceCounted
		{
			public:
				//! Singleton realization
				static IActionScheduler& getInstance();

			private:
				//! Default constructor. Should use only one time.
				IActionScheduler();

				//! Destructor. Should use only one time.
				~IActionScheduler();

				//! Copy constructor. Do not implement.
				IActionScheduler(const IActionScheduler& root);

				//! Override equal operator. Do not implement.
				const IActionScheduler& operator=(IActionScheduler&);

			public:

				//! Adds action to specify queue
				void addAction(delegateAction* action, EActionPriority qType);

				//! Start process actions.
				void startProcess();

			private:
				int proceedRTActions(void* stub);
				int proceedHPActions(void* stub);
				int proceedBGActions(void* stub);

			private:
				//! TODO: mb need change collection
				core::array<delegateAction*> RealtimeActions;
				core::array<delegateAction*> HighpriorityActions;
				core::array<delegateAction*> BackgroundActions;
		};
	}

}

#endif /* ITHREADPOOL_H_ */
