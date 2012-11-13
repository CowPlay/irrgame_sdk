/*
 * irrgameThread.h
 *
 *  Created on: Jul 25, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMETHREAD_H_
#define IRRGAMETHREAD_H_

#include "core/collections/stringc.h"
#include "core/delegate.h"

namespace irrgame
{
	namespace threads
	{
		//!
		enum EThreadPriority
		{
			//!
			ETP_LOW = 0,
			//!
			ETP_NORMAL,
			//!
			ETP_HIGH
		};

		//! use this delegate for run some func in individual thread
		typedef delegate<s32, void*> delegateThreadCallback;

		//! Interface providing acces to system thread
		//! TODO: provide acces to change priority
		class irrgameThread: public IReferenceCounted
		{
			public:

				//! Causes the operating system to sleep current thread.
				//! Platform dependent
				//@ param0 - time in ms.
				static void sleep(s32 time);

				//! Returns current thread id
				static s32 getCurrentThreadID();

			public:

				//! Destructor
				virtual ~irrgameThread()
				{
				}

				//! Causes the operating system to start thread, and optionally supplies an object containing data to be used by the method the thread executes
				//! Platform dependent
				virtual void start() = 0;

				//! Blocks the calling thread until a thread terminates.
				//! Platform dependent
				virtual void join() = 0;

				//! Causes the operating system to kill thread
				//! Platform dependent
//				virtual void kill() = 0;

				//! Gets thread name
				virtual core::stringc getName();

				//! Gets thread callback
				virtual delegateThreadCallback* getCallback();

				//! Gets callback input args
				virtual void* getCallbackArg();

			protected:
				//! Thread name
				core::stringc Name;
				//! Function which will be started
				delegateThreadCallback* Callback;
				//! Callback input args
				void* CallbackArg;

		};

		//! irrgameThread creator. Internal function. Please do not use.
		irrgameThread* createIrrgameThread(delegateThreadCallback* callback,
				void* callbackArg = NULL, EThreadPriority prior = ETP_NORMAL,
				core::stringc name = "");
	}
}

#endif /* IRRGAMETHREAD_H_ */
