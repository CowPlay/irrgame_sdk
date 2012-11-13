/*
 * ITimer.h
 *
 *  Created on: Aug 1, 2012
 *      Author: gregorytkach
 */

#ifndef ITIMER_H_
#define ITIMER_H_

#include "core/engine/IReferenceCounted.h"
#include "core/irrgamecollections.h"
#include "core/delegate.h"

namespace irrgame
{
	namespace utils
	{
		//! Interface for getting and manipulating the virtual time
		class ITimer: public IReferenceCounted
		{
			public:

				typedef delegate<s32, ITimer*> delegateTimerAlarm;

				/*
				 * Static funcs
				 */

			public:

				//! Returns current real time in milliseconds of the system.
				//! Platform dependent
				/* This value does not start with 0 when the application starts.
				 * For example in one implementation the value returned could be the
				 * amount of milliseconds which have elapsed since the system was started.
				 */
				static u32 getRealTime();

				//! Advances the virtual time
				/* Makes the all timers update the time value based on the real
				 * time. This is called automatically when calling irrgamePlayer::run(),
				 * but you can call it manually if you don't use this method.
				 */
				static void tick();

				//! Create new timer
				/* After use, the reader has to be deleted using its IXMLReader::drop() method.
				 * See IReferenceCounted::drop() for more information.
				 */
				static ITimer* createTimer();

			protected:

				//register timer for tick
				static void registerTimer(ITimer* timer);

				//unregister timer. This mean for specify timer there wil be no call tick.
				static void unregisterTimer(ITimer* timer);

			protected:

				static core::list<ITimer*> RegisteredTimers;

				/*
				 * Instance funcs
				 */

			public:

				//! This event fires when alarm time comes.
				delegateTimerAlarm* OnTimerAlarm;

			public:
				//! Destructor
				virtual ~ITimer();

				//! Starts the virtual timer.
				virtual void start() = 0;

				//! Stops the virtual timer.
				virtual void stop() = 0;

				//! Set alarm time in milliseconds.
				virtual void setAlarm(u32 time) = 0;

				//! sets current virtual time
				virtual void setTime(u32 value) = 0;

				//! Returns current virtual time in milliseconds.
				/* This value starts with 0 and can be manipulated using setTime(),
				 * stopTimer(), startTimer(), etc. This value depends on the set speed of
				 * the timer if the timer is stopped, etc. If you need the system time,
				 * use getRealTime()
				 */
				virtual u32 getTime() const = 0;

				//! Sets the speed of the timer
				/** The speed is the factor with which the time is running faster or
				 slower then the real system time. */
				virtual void setSpeed(f32 value) = 0;

				//! Returns current speed of the timer
				/* The speed is the factor with which the time is running faster or
				 * slower then the real system time.
				 */
				virtual f32 getSpeed() const = 0;

				//! Returns if the virtual timer is currently started
				virtual bool isStarted() const = 0;

			protected:

				//! Advances the virtual time
				/* Makes the timer update the time value based on the real
				 * time. This is called automatically when calling ITimer::tick(),
				 * but you can call it manually if you don't use this method.
				 */
				virtual void tickInternal() = 0;

		};
	}	// namespace utils

}  // namespace irrgame

#endif /* ITIMER_H_ */
