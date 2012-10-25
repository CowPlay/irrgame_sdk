/*
 * CTimer.h
 *
 *  Created on: Aug 1, 2012
 *      Author: gregorytkach
 */

#ifndef CTIMER_H_
#define CTIMER_H_

#include "utils/ITimer.h"
#include "threads/irrgameMonitor.h"

namespace irrgame
{
	namespace utils
	{
		//! Platform dependent
		class CTimer: public ITimer
		{
			public:

				//! Default constructor
				CTimer();

				//! Destructor
				virtual ~CTimer();

				//! Starts the virtual timer.
				virtual void start();

				//! Stops the virtual timer.
				virtual void stop();

				//! Set alarm time in milliseconds.
				virtual void setAlarm(u32 time);

				//! Advances the virtual time
				/** Makes the timer update the time value based on the real
				 time. This is called automatically when calling ITimer::tick(),
				 but you can call it manually if you don't use this method. */
				virtual void tick();

				//! Sets current virtual time
				/* This func has no effect to alarm. Alarms updates on next tick.
				 */
				virtual void setTime(u32 value);

				//! Returns current virtual time in milliseconds.
				/** This value starts with 0 and can be manipulated using setTime(),
				 stopTimer(), startTimer(), etc. This value depends on the set speed of
				 the timer if the timer is stopped, etc. If you need the system time,
				 use getRealTime() */
				virtual u32 getTime() const;

				//! Sets the speed of the timer
				/** The speed is the factor with which the time is running faster or
				 slower then the real system time. */
				virtual void setSpeed(f32 value);

				//! Returns current speed of the timer
				/** The speed is the factor with which the time is running faster or
				 slower then the real system time. */
				virtual f32 getSpeed() const;

				//! Returns if the timer currently is started
				virtual bool isStarted() const;

			protected:

				//! Advances the virtual time
				/** Makes the timer update the time value based on the real
				 time. This is called automatically when calling ITimer::tick(),
				 but you can call it manually if you don't use this method. */
				virtual void tickInternal();

			private:

				threads::irrgameMonitor* Monitor;

				bool IsStarted;
				//! Represents tick count of current timer
				u32 Time;
				u32 StartTime;
				u32 EndTime;
				u32 AlarmTime;

				f32 Speed;
		};
	}
}

#endif /* ITIMER_H_ */
