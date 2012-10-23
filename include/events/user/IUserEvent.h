/*
 * IUserEvent.h
 *
 *  Created on: Oct 19, 2012
 *      Author: gregorytkach
 */

#ifndef IUSEREVENT_H_
#define IUSEREVENT_H_

#include "events/IEvent.h"
#include "events/user/EUserEventTypes.h"
#include "events/user/EUserKeyStates.h"
#include "events/user/EUserKeys.h"
#include "events/user/SCursorInfo.h"

namespace irrgame
{
	namespace events
	{

		//! Interface of an object which represent any user event.
		class IUserEvent: public IEvent
		{
			public:

				//! Destructor
				virtual ~IUserEvent()
				{
				}

				//! Returns user event type
				virtual EUserEventTypes getUserEventType() = 0;

				//! If user event have type - returns cursor info. Otherwise - return NULL;
				virtual SCursorInfo* getCursorInfo() = 0;
		};

		//! Internal function. Please do not use.
		IUserEvent* createUserEvent(EUserKeys key, EUserKeyStates keyState);

		//! Internal function. Please do not use.
		IUserEvent* createUserEvent(SCursorInfo* info);

	}  // namespace events
}  // namespace irrgame

#endif /* IUSEREVENT_H_ */
