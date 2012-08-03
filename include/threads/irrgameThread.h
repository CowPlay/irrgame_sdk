/*
 * irrgameThread.h
 *
 *  Created on: Jul 25, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMETHREAD_H_
#define IRRGAMETHREAD_H_


#include "./core/IReferenceCounted.h"
#include "./core/irrString.h"
namespace irrgame
{
	namespace threads
	{

		//use this delegate for run func in individual thread
		typedef C_DELEGATE<int, void*> delegateThreadCallback;

		class irrgameThread: public IReferenceCounted
		{

			public:

				virtual ~irrgameThread()
				{
				}

				//! Causes the operating system to start thread, and optionally supplies an object containing data to be used by the method the thread executes
				virtual void start(void* data = NULL) = 0;

				//! Blocks the calling thread until a thread terminates.
				virtual void join() = 0;

				//! Causes the operating system to kill thread
				virtual void kill() = 0;

				//! Gets thread name
				virtual core::stringc getName() = 0;

		};
	}
}

#endif /* IRRGAMETHREAD_H_ */
