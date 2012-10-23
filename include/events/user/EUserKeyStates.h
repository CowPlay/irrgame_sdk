/*
 * EUserKeysStates.h
 *
 *  Created on: Oct 19, 2012
 *      Author: gregorytkach
 */

#ifndef EUSERKEYSSTATES_H_
#define EUSERKEYSSTATES_H_

namespace irrgame
{
	namespace events
	{
		//! Enum which contains all user key states
		enum EUserKeyStates
		{
			//! key was left up
			EUKS_UP = 0,
			//! key was pressed down
			EUKS_DOWN,
			//! key  was pressed
			EUKS_PRESSED,
			//! key  was released
			EUKS_RELEASED,

			//! Not used
			EUKS_COUNT
		};

	} // namespace events
}  // namespace irrgame

#endif /* EUSERKEYSSTATES_H_ */
