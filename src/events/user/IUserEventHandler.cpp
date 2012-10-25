/*
 * IUserEventHandler.cpp
 *
 *  Created on: Oct 23, 2012
 *      Author: gregorytkach
 */

#include "events/user/IUserEventHandler.h"

namespace irrgame
{
	namespace events
	{
//		CUserActionEventReceiver::CUserActionEventReceiver(irrgameDevice* device) :
		//			Device(device), IsRunning(false), HandleActionThread(0), IsMousePressed(
		//					false)
		//	{
		//		KeyStates.insert(irr::KEY_F1, KEY_STATE_UP);
		//		KeyStates.insert(irr::KEY_F2, KEY_STATE_UP);
		//
		//		//KeyStates.insert(irr::KEY_UP, KEY_STATE_UP);
		//		//KeyStates.insert(irr::KEY_DOWN, KEY_STATE_UP);
		//		//KeyStates.insert(irr::KEY_LEFT, KEY_STATE_UP);
		//		//KeyStates.insert(irr::KEY_RIGHT, KEY_STATE_UP);
		//
		//		//KeyStates.insert(irr::KEY_START, KEY_STATE_UP);
		//		//KeyStates.insert(irr::KEY_SELECT, KEY_STATE_UP);
		//
		//		//KeyStates.insert(irr::KEY_TRIANGLE, KEY_STATE_UP);
		//		//KeyStates.insert(irr::KEY_CROSS, KEY_STATE_UP);
		//		//KeyStates.insert(irr::KEY_SQUARE, KEY_STATE_UP);
		//		//KeyStates.insert(irr::KEY_CIRCLE, KEY_STATE_UP);
		//	}
		//
		//	CUserActionEventReceiver::~CUserActionEventReceiver()
		//	{
		//		IsRunning = false;
		//
		//	}
		//
		//	bool CUserActionEventReceiver::handleAction(const irr::SEvent& e)
		//	{
		//		bool result = false;
		//
		//		switch (e.EventType)
		//		{
		//			case irr::EET_KEY_INPUT_EVENT:
		//			{
		//				if (this->KeyStates.find(e.KeyInput.Key))
		//				{
		//					SUserAction keyInputAction;
		//
		//					keyInputAction.KeyCode = e.KeyInput.Key;
		//
		//					// if key is Pressed Down
		//					if (e.KeyInput.PressedDown == true)
		//					{
		//						if (this->KeyStates[e.KeyInput.Key] == KEY_STATE_PRESSED
		//								|| this->KeyStates[e.KeyInput.Key]
		//										== KEY_STATE_DOWN)
		//						{
		//							// if key was down before
		//							this->KeyStates[e.KeyInput.Key] = KEY_STATE_DOWN; // Set to Down
		//
		//							keyInputAction.KeyState = KEY_STATE_DOWN;
		//						}
		//						else // If key was not down before
		//						{
		//							this->KeyStates[e.KeyInput.Key] = KEY_STATE_PRESSED; // Set to Pressed
		//
		//							keyInputAction.KeyState = KEY_STATE_PRESSED;
		//						}
		//					}
		//					else
		//					{
		//						// if the key is down
		//						if (this->KeyStates[e.KeyInput.Key] != KEY_STATE_UP)
		//						{
		//							this->KeyStates[e.KeyInput.Key] =
		//									KEY_STATE_RELEASED; // Set to Released
		//							keyInputAction.KeyState = KEY_STATE_RELEASED;
		//						}
		//					}
		//
		//					if (!UAction.IsNull())
		//					{
		//						result = UAction(keyInputAction);
		//					}
		//				}
		//
		//				break;
		//			}
		//			case irr::EET_MOUSE_INPUT_EVENT:
		//			{
		//				SUserAction mouseAction;
		//
		//				mouseAction.KeyCode = irr::KEY_MOUSE;
		//				mouseAction.MouseInfo.CursorPos = irr::core::position2di(
		//						e.MouseInput.X, e.MouseInput.Y);
		//
		//				switch (e.MouseInput.Event)
		//				{
		//					case irr::EMIE_MOUSE_MOVED:
		//					{
		//						mouseAction.KeyState = KEY_STATE_MOUSE_MOVE;
		//
		//						mouseAction.MouseInfo.Offset = irr::core::vector2di(
		//								e.MouseInput.X - LastCursorPos.X,
		//								e.MouseInput.Y - LastCursorPos.Y);
		//
		//						//update last cursor position
		//						LastCursorPos = irr::core::position2di(e.MouseInput.X,
		//								e.MouseInput.Y);
		//
		//						//some devices(example windows) sends not actually information
		//						if (mouseAction.MouseInfo.Offset
		//								== irr::core::vector2di(0, 0))
		//							return result;
		//
		//						break;
		//					}
		//					case irr::EMIE_LMOUSE_PRESSED_DOWN:
		//					{
		//						mouseAction.KeyState = KEY_STATE_PRESSED;
		//						IsMousePressed = true;
		//
		//						break;
		//					}
		//					case irr::EMIE_LMOUSE_LEFT_UP:
		//					{
		//						mouseAction.KeyState = KEY_STATE_RELEASED;
		//						IsMousePressed = false;
		//
		//						break;
		//					}
		//				}
		//
		//				mouseAction.MouseInfo.MousePressed = IsMousePressed;
		//
		//				if (!this->UAction.IsNull())
		//				{
		//					result = UAction(mouseAction);
		//				}
		//
		//				break;
		//			}
		//			default:
		//			{
		//				break;
		//			}
		//		}
		//
		//		return result;
		//	}
		//

		//
		//	void CUserActionEventReceiver::resetKeyStates()
		//	{
		//		irr::core::map<irr::EKEY_CODE, irrgame::EKEY_STATE>::Iterator it =
		//				this->KeyStates.getIterator();
		//		it.reset(false);
		//
		//		for (s32 i = this->KeyStates.size() - 1; i >= 0; i--, it--)
		//		{
		//			if (it.getNode()->getValue() == irrgame::KEY_STATE_RELEASED)
		//			{
		//				it.getNode()->setValue(irrgame::KEY_STATE_UP);
		//			}
		//			else if (it.getNode()->getValue() == irrgame::KEY_STATE_PRESSED)
		//			{
		//				it.getNode()->setValue(irrgame::KEY_STATE_DOWN);
		//			}
		//		}
		//	}
		//

		//! Default constructor
		IUserEventHandler::IUserEventHandler() :
				IsRunning(false)
		{
		}

		//! Destructor
		IUserEventHandler::~IUserEventHandler()
		{
			//drops all cursors info
			core::map<u32, SCursorInfo*>::ParentFirstIterator it =
					CursorsInfo.getParentFirstIterator();

			for (; it.atEnd(); it++)
			{
				(*it).getValue()->drop();
			}
		}

		//Platform dependent
		void IUserEventHandler::initKeyMap()
		{
//			IRR_ASSERT(false);
		}

		//Platform dependent
		void IUserEventHandler::initCursorsInfo()
		{
			IRR_ASSERT(false);
		}

		void IUserEventHandler::initKeyStates()
		{
			//drops all cursors info
			core::map<s32, EUserKeys>::ParentFirstIterator it =
					KeyMap.getParentFirstIterator();

			for (; it.atEnd(); it++)
			{
				KeyStates.insert((*it).getValue(), EUKS_RELEASED);
			}
		}

		//! Starts process event process
		void IUserEventHandler::startEventProcess()
		{
			resetKeyStates();

			this->IsRunning = true;
		}
		//
		//! Stops process event process
		void IUserEventHandler::stopEventProcess()
		{
			this->IsRunning = false;

			resetKeyStates();
		}

		//reset all key states. If key have state pressed/release, after call this func - it will have down/up state.
		void IUserEventHandler::resetKeyStates()
		{
			//drops all cursors info
			core::map<u32, SCursorInfo*>::ParentFirstIterator it =
					CursorsInfo.getParentFirstIterator();

			for (; it.atEnd(); it++)
			{
				ECursorStates state = (*it).getValue()->State;
				if (state == ECS_PRESSED || ECS_CURSOR_DRAGGED || ECS_DOWN)
				{
					(*it).getValue()->State = ECS_DOWN;
				}
				else
				{
					(*it).getValue()->State = ECS_RELEASED;
				}
			}
		}

		//! Called if an event happened.
		bool IUserEventHandler::onEvent(IEvent* e)
		{
			if (!IsRunning)
			{
				return false;
			}

			return OnUserEvent(e);
		}

	}  // namespace events
}  // namespace irrgame

