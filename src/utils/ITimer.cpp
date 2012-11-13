/*
 * ITimer.cpp
 *
 *  Created on: Oct 24, 2012
 *      Author: gregorytkach
 */

#include "utils/ITimer.h"

namespace irrgame
{
	namespace utils
	{
		core::list<ITimer*> ITimer::RegisteredTimers;

		//! Destructor
		ITimer::~ITimer()
		{
		}

		//register timer for tick
		void ITimer::registerTimer(ITimer* timer)
		{
			IRR_ASSERT(timer != 0);
			RegisteredTimers.pushBack(timer);
		}

		//unregister timer. This mean for specify timer there wil be no call tick.
		void ITimer::unregisterTimer(ITimer* timer)
		{
			IRR_ASSERT(timer != 0);
			RegisteredTimers.remove(timer);
		}

		//! Advances the virtual time
		void ITimer::tick()
		{
			for (core::list<ITimer*>::Iterator it = RegisteredTimers.begin();
					it != RegisteredTimers.getLastIterator(); it++)
			{
				(*it)->tickInternal();
			}
		}

	}  // namespace utils
}  // namespace irrgame

