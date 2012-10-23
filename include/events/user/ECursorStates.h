/*
 * ECursorStates.h
 *
 *  Created on: Oct 22, 2012
 *      Author: gregorytkach
 */

#ifndef ECURSORSTATES_H_
#define ECURSORSTATES_H_

namespace irrgame
{
	namespace events
	{
		enum ECursorStates
		{
			//! mouse key/touch was pressed down
			ECS_DOWN = 0,
			//! mouse key/touch  was pressed
			ECS_PRESSED,
			//! mouse key/touch  was released
			ECS_RELEASED,

			//! mouse/touch/joystick was move
			ECS_CURSOR_MOVED,
			//! mouse/touch/joystick was stopped
			ECS_CURSOR_STOPPED,
			//! mouse/touch/joystick was dragged
			ECS_CURSOR_DRAGGED,

			ECS_COUNT
		};
	}  // namespace events
}  // namespace irrgame

#endif /* ECURSORSTATES_H_ */
