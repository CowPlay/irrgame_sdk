/*
 * EUserEventType.h
 *
 *  Created on: Oct 19, 2012
 *      Author: gregorytkach
 */

#ifndef EUSEREVENTTYPE_H_
#define EUSEREVENTTYPE_H_

namespace irrgame
{

	namespace events
	{
		enum EUserEventTypes
		{
			EUET_KEY_EVENT = 0,
			EUET_CURSOR_EVENT,

			EUET_COUNT
		};
	}  // namespace events

}  // namespace irrgame

#endif /* EUSEREVENTTYPE_H_ */
