/*
 * IFPSCounter.h
 *
 *  Created on: Oct 16, 2012
 *      Author: gregorytkach
 */

#ifndef IFPSCOUNTER_H_
#define IFPSCOUNTER_H_

#include "core/engine/IReferenceCounted.h"

namespace irrgame
{

	namespace video
	{

		class IFPSCounter: public IReferenceCounted
		{
			public:
				//! Destructor
				virtual ~IFPSCounter()
				{
				}

				//! returns current fps
				/** This value is updated approximately every 1.5 seconds and
				 is only intended to provide a rough guide to the average frame
				 rate. It is not suitable for use in performing timing
				 calculations or framerate independent movement.
				 \return Approximate amount of frames per second drawn. */
				virtual s32 getFPS() const = 0;

				//! returns primitive count
				virtual u32 getPrimitive() const = 0;

				//! returns average primitive count of last period
				virtual u32 getPrimitiveAverage() const = 0;

				//! returns accumulated primitive count since start
				virtual u32 getPrimitiveTotal() const = 0;

				//! to be called every frame
				virtual void registerFrame(u32 now, u32 primitive) = 0;
		};

		//! Internal function. Please do not use.
		IFPSCounter* createFPSCounter();

	}  // namespace video
}  // namespace irrgame

#endif /* IFPSCOUNTER_H_ */
