/*
 * irrgameThread.h
 *
 *  Created on: Jul 25, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMETHREAD_H_
#define IRRGAMETHREAD_H_

#include "core/IReferenceCounted.h"
#include "core/irrString.h"
namespace irrgame
{
	namespace threads
	{

		class irrgameThread: public IReferenceCounted
		{
			public:

				//! Causes the operating system to sleep current thread.
				//@ param0 - time in msec.
				static void sleep(s32 time);

			public:

				//! Default constructor
				//@ param1 - thread name
				//@ param2 - input params
				irrgameThread(core::stringc name, void* data);

				//! Destructor
				virtual ~irrgameThread();

				//! Causes the operating system to start thread, and optionally supplies an object containing data to be used by the method the thread executes
				virtual void start();

				//! Blocks the calling thread until a thread terminates.
				virtual void join();

				//! Causes the operating system to kill thread
				virtual void kill();

				//! Gets thread name
				virtual core::stringc getName();

			protected:
				core::stringc Name;

		};

		//! irrgameThread creator. Internal function. Please do not use.
		irrgameThread* createIrrgameThread(core::stringc name,
				void* data = NULL);
	}
}

#endif /* IRRGAMETHREAD_H_ */
