/*
 * IUserEventsHandler.h
 *
 *  Created on: Oct 19, 2012
 *      Author: gregorytkach
 */

#ifndef IUSEREVENTSHANDLER_H_
#define IUSEREVENTSHANDLER_H_

#include "events/IEventReceiver.h"
#include "events/user/EUserKeys.h"
#include "events/user/EUserKeyStates.h"
#include "events/user/SCursorInfo.h"
#include "core/collections/map/map.h"

namespace irrgame
{
	namespace events
	{
		//! Interface of an object which handle all user events
		class IUserEventHandler: public IEventReceiver
		{
			public:

				//! Fires when any user action detected
				delegateUserEventHandler OnUserEvent;

			public:

				//! Default constructor
				IUserEventHandler();

				//! Destructor
				virtual ~IUserEventHandler();

				//! Starts process event process
				virtual void startEventProcess();

				//! Stops process event process
				virtual void stopEventProcess();

				//reset all key states. If key have state pressed/release, after call this func - it will have down/up state.
				virtual void resetKeyStates();

				//! Called if an event happened.
				/** Please take care that you should only return 'true' when you want to _prevent_ Irrlicht
				 * from processing the event any further. So 'true' does mean that an event is completely done.
				 * Therefore your return value for all unprocessed events should be 'false'.
				 \return True if the event was processed.
				 */
				virtual bool onEvent(IEvent* e);

				//! This func must call from player when any key event from user detected.
				//Platform dependent
				virtual void handleKeyEvent(void* e) = 0;

				//! This func must call from player when any mouse event from user detected.
				//Platform dependent
				virtual void handleMouseEvent(void* e) = 0;

			protected:

				//Platform dependent
				virtual void initKeyMap() = 0;

				//Platform dependent
				virtual void initCursorsInfo() = 0;

				virtual void initKeyStates();

			protected:

				//user event handler state
				bool IsRunning;
				//key map collection
				core::map<s32, EUserKeys> KeyMap;
				//key states collection
				core::map<EUserKeys, EUserKeyStates> KeyStates;
				//cursors info collection
				core::map<u32, SCursorInfo*> CursorsInfo;
		};

		//! Internal function. Please do not use.
		IUserEventHandler* createUserEventsHandler();
	}  // namespace events

}  // namespace irrgame

#endif /* IUSEREVENTSHANDLER_H_ */
