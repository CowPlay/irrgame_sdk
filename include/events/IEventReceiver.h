/*
 * IEventReceiver.h
 *
 *  Created on: Sep 12, 2012
 *      Author: gregorytkach
 */

#ifndef IEVENTRECEIVER_H_
#define IEVENTRECEIVER_H_

#include "core/engine/IReferenceCounted.h"
#include "core/delegate.h"

namespace irrgame
{

	namespace events
	{
		class IEvent;

		typedef delegate<bool, IEvent*> delegateUserEventHandler;

		//! Interface of an object which can receive events.
		/** Every object which want handle user event must implement this interface */
		class IEventReceiver: public IReferenceCounted
		{
			public:

				//! Destructor
				virtual ~IEventReceiver()
				{
				}

				//! Called if an event happened.
				/** Please take care that you should only return 'true' when you want to _prevent_ Irrlicht
				 * from processing the event any further. So 'true' does mean that an event is completely done.
				 * Therefore your return value for all unprocessed events should be 'false'.
				 \return True if the event was processed.
				 */
				virtual bool onEvent(IEvent* e) = 0;
		};
	}  // namespace events

}  // namespace irrgame

#endif /* IEVENTRECEIVER_H_ */
