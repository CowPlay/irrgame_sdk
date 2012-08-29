/*
 * irrgameMonitor.h
 *
 *  Created on: Jul 25, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMEMONITOR_H_
#define IRRGAMEMONITOR_H_

#include "core/irrgamebase.h"
namespace irrgame
{
	namespace threads
	{
		class irrgameMonitor: public IReferenceCounted
		{
			public:
				//! Destructor
				virtual ~irrgameMonitor()
				{
				}

				//! Acquires a lock for an object. This action also marks the beginning of a critical section.
				//! No other thread can enter the critical section unless it is executing the instructions
				//! in the critical section using a different locked object.
				virtual void enter() = 0;

				//! Releases the lock on an object. This action also marks the end of a critical section protected by the locked object.
				virtual void exit() = 0;
		};

		//! irrgameMonitor creator. Internal function. Please do not use.
		irrgameMonitor* createIrrgameMonitor();
	}
}

#endif /* IRRGAMEMONITOR_H_ */
