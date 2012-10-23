/*
 * Timer.cpp
 *
 *  Created on: Aug 1, 2012
 *      Author: gregorytkach
 */

#include "utils/Timer.h"
namespace irrgame
{
	namespace utils
	{
		f32 Timer::VirtualTimerSpeed = 1.0f;
		s32 Timer::VirtualTimerStopCounter = 0;
		u32 Timer::LastVirtualTime = 0;
		u32 Timer::StartRealTime = 0;
		u32 Timer::StaticTime = 0;

		//! returns current virtual time
		u32 Timer::getTime()
		{
			if (isStopped())
				return LastVirtualTime;

			return LastVirtualTime
					+ (u32) ((StaticTime - StartRealTime) * VirtualTimerSpeed);
		}

		//! ticks, advances the virtual timer
		void Timer::tick()
		{
			StaticTime = getRealTime();
		}

		//! sets the current virtual time
		void Timer::setTime(u32 time)
		{
			StaticTime = getRealTime();
			LastVirtualTime = time;
			StartRealTime = StaticTime;
		}

		//! stops the virtual timer
		void Timer::stopTimer()
		{
			if (!isStopped())
			{
				// stop the virtual timer
				LastVirtualTime = getTime();
			}

			--VirtualTimerStopCounter;
		}

		//! starts the virtual timer
		void Timer::startTimer()
		{
			++VirtualTimerStopCounter;

			if (!isStopped())
			{
				// restart virtual timer
				setTime(LastVirtualTime);
			}
		}

		//! sets the speed of the virtual timer
		void Timer::setSpeed(f32 speed)
		{
			setTime(getTime());

			VirtualTimerSpeed = speed;
			if (VirtualTimerSpeed < 0.0f)
				VirtualTimerSpeed = 0.0f;
		}

		//! gets the speed of the virtual timer
		f32 Timer::getSpeed()
		{
			return VirtualTimerSpeed;
		}

		//! returns if the timer currently is stopped
		bool Timer::isStopped()
		{
			return VirtualTimerStopCounter < 0;
		}

		void Timer::initVirtualTimer()
		{
			StaticTime = getRealTime();
			StartRealTime = StaticTime;
		}
	}
}

