/*
 * ITimer.h
 *
 *  Created on: Aug 1, 2012
 *      Author: gregorytkach
 */

#ifndef ITIMER_H_
#define ITIMER_H_

#include "./core/irrgameTypes.h"

namespace irrgame
{
	namespace utils
	{
		//! Platform dependies
		class Timer
		{
			public:

				//! returns the current time in milliseconds
				//! Platform dependies
				static u32 getTime();

				//! initializes the real timer
				//! Platform dependies
				static void initTimer();

				//! sets the current virtual (game) time
				static void setTime(u32 time);

				//! stops the virtual (game) timer
				static void stopTimer();

				//! starts the game timer
				static void startTimer();

				//! sets the speed of the virtual timer
				static void setSpeed(f32 speed);

				//! gets the speed of the virtual timer
				static f32 getSpeed();

				//! returns if the timer currently is stopped
				static bool isStopped();

				//! makes the virtual timer update the time value based on the real time
				static void tick();

				//! returns the current real time in milliseconds
				static u32 getRealTime();

			private:

				static void initVirtualTimer();

				static f32 VirtualTimerSpeed;
				static s32 VirtualTimerStopCounter;
				static u32 StartRealTime;
				static u32 LastVirtualTime;
				static u32 StaticTime;
		};
	}
}

#endif /* ITIMER_H_ */
