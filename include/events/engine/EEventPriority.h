/*
 * EEventPriority.h
 *
 *  Created on: Nov 1, 2012
 *      Author: gregorytkach
 */

#ifndef EEVENTPRIORITY_H_
#define EEVENTPRIORITY_H_

namespace irrgame
{
	namespace events
	{
		enum EEventPriority
		{
			//! Use for render
			EAP_REALTIME = 0,

			//! Use for logic
			EAP_HIGHPRIORITY,

			//! Use for load resources in background or events with low priority
			EAP_BACKGROUND,

			//! Not used
			EAP_COUNT
		};
	}  // namespace video
}  // namespace irrgame

#endif /* EEVENTPRIORITY_H_ */
