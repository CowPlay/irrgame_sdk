/*
 * CUserEvent.cpp
 *
 *  Created on: Oct 19, 2012
 *      Author: gregorytkach
 */

#include "CUserEvent.h"

namespace irrgame
{
	namespace events
	{
		//! Default constructor for key events
		CUserEvent::CUserEvent(EUserKeys key, EUserKeyStates keyState) :
				Type(EUET_KEY_EVENT), Key(key), KeyState(keyState), CursorInfo(
						0)
		{
		}

		//! Default constructor for cursor events
		CUserEvent::CUserEvent(SCursorInfo* info) :
				Type(EUET_CURSOR_EVENT), Key(EUK_COUNT), KeyState(EUKS_COUNT), CursorInfo(
						info)
		{
		}

		//! Destructor
		CUserEvent::~CUserEvent()
		{
			// TODO Auto-generated destructor stub
		}

		//! Returns event type
		EEventTypes CUserEvent::getType()
		{
			return EET_USER;
		}

		//! Returns user event type
		EUserEventTypes CUserEvent::getUserEventType()
		{
			return Type;
		}

		//! If user event have type - returns cursor info. Otherwise - return NULL;
		SCursorInfo* CUserEvent::getCursorInfo()
		{
			return CursorInfo;
		}

		//! If this event have type - return key, otherwise return EUK_COUNT
		EUserKeys CUserEvent::getKey()
		{
			return Key;
		}

		//! If this event have type - return key state, otherwise return EUKS_COUNT
		EUserKeyStates CUserEvent::getKeyState()
		{
			return KeyState;
		}

		//! Internal function. Please do not use.
		IUserEvent* createUserEvent(SCursorInfo* info)
		{
			return new CUserEvent(info);
		}

		//! Internal function. Please do not use.
		IUserEvent* createUserEvent(EUserKeys key, EUserKeyStates keyState)
		{
			return new CUserEvent(key, keyState);
		}

	} /* namespace events */
} /* namespace irrgame */
