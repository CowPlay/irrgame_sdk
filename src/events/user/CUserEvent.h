/*
 * CUserEvent.h
 *
 *  Created on: Oct 19, 2012
 *      Author: gregorytkach
 */

#ifndef CUSEREVENT_H_
#define CUSEREVENT_H_

#include "events/user/IUserEvent.h"

namespace irrgame
{
	namespace events
	{

		class CUserEvent: public IUserEvent
		{
			public:
				//! Default constructor for key events
				CUserEvent(EUserKeys key, EUserKeyStates keyState);

				//! Default constructor for cursor events
				CUserEvent(SCursorInfo* info);

				//! Destructor
				virtual ~CUserEvent();

				//! Returns event type
				EEventTypes getType();

				//! Returns user event type
				EUserEventTypes getUserEventType();

				//! If this event have type - returns cursor info. Otherwise - return NULL;
				SCursorInfo* getCursorInfo();

				//! If this event have type - return key, otherwise return EUK_COUNT
				EUserKeys getKey();

				//! If this event have type - return key state, otherwise return EUKS_COUNT
				EUserKeyStates getKeyState();

			private:
				//user event type
				EUserEventTypes Type;

				//key
				EUserKeys Key;
				//key state
				EUserKeyStates KeyState;

				//cursor info
				SCursorInfo* CursorInfo;

		};

	} /* namespace events */
} /* namespace irrgame */
#endif /* CUSEREVENT_H_ */
