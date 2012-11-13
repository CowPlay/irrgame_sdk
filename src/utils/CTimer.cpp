/*
 * CTimer.cpp
 *
 *  Created on: Aug 1, 2012
 *      Author: gregorytkach
 */

#include "utils/CTimer.h"
namespace irrgame
{
	namespace utils
	{
		ITimer* ITimer::createTimer()
		{
			ITimer* result = new CTimer;

			ITimer::registerTimer(result);

			return result;
		}

		//! Default constructor
		CTimer::CTimer() :
				Monitor(0), IsStarted(false), Time(0), StartTime(0), EndTime(0), AlarmTime(
						0), Speed(1.0F)
		{
			Monitor = threads::createIrrgameMonitor();
		}

		//! Destructor
		CTimer::~CTimer()
		{
			ITimer::unregisterTimer(this);

			if (Monitor)
				Monitor->drop();
		}

		//! Starts the virtual timer.
		void CTimer::start()
		{
			IRR_ASSERT(IsStarted != true);

			Monitor->enter();

			StartTime = getRealTime();

			IsStarted = true;

			Monitor->exit();
		}

		//! Stops the virtual timer.
		void CTimer::stop()
		{
			IRR_ASSERT(IsStarted != false);

			Monitor->enter();

			EndTime = getRealTime();

			IsStarted = false;

			Monitor->exit();
		}

		//! Set alarm time in milliseconds.
		void CTimer::setAlarm(u32 time)
		{
			AlarmTime = time;
		}

		//! sets current virtual time
		void CTimer::setTime(u32 value)
		{
			Monitor->enter();

			Time = value;

			Monitor->exit();
		}

		//! Returns current virtual time in milliseconds.
		u32 CTimer::getTime() const
		{
			Monitor->enter();
			u32 result = Time;
			Monitor->exit();

			return result;
		}

		//! Sets the speed of the timer
		/** The speed is the factor with which the time is running faster or
		 slower then the real system time. */
		void CTimer::setSpeed(f32 value)
		{
			Monitor->enter();
			Speed = value;
			Monitor->exit();
		}

		//! Returns current speed of the timer
		/** The speed is the factor with which the time is running faster or
		 slower then the real system time. */
		f32 CTimer::getSpeed() const
		{
			Monitor->enter();
			f32 result = Speed;
			Monitor->exit();

			return result;
		}

		//! Returns if the timer currently is started
		bool CTimer::isStarted() const
		{
			Monitor->enter();
			bool result = IsStarted;
			Monitor->exit();

			return result;
		}

		//! Advances the virtual time
		void CTimer::tickInternal()
		{
			Monitor->enter();

			if (!IsStarted)
			{
				Monitor->exit();
				return;
			}

			u32 realTime = getRealTime();

			Time = (u32) ((realTime - StartTime) * Speed);

			if (Time > AlarmTime)
			{
				if (OnTimerAlarm)
				{
					(*OnTimerAlarm)(this);
				}
			}

			Monitor->exit();
		}

	}
}

