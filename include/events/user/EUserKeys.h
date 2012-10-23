// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef EUSER_KEYS_H_INCLUDED__
#define EUSER_KEYS_H_INCLUDED__

namespace irrgame
{
	namespace events
	{
		enum EUserKeys
		{
			/*
			 * Number keys
			 */
			EUK_0 = 0x01,  // 0 key
			EUK_1 = 0x02,  // 1 key
			EUK_2 = 0x03,  // 2 key
			EUK_3 = 0x04,  // 3 key
			EUK_4 = 0x05,  // 4 key
			EUK_5 = 0x06,  // 5 key
			EUK_6 = 0x07,  // 6 key
			EUK_7 = 0x08,  // 7 key
			EUK_8 = 0x09,  // 8 key
			EUK_9 = 0x1A,  // 9 key

			/*
			 * Character keys
			 */
			EUK_A = 0x1B,  // A key
			EUK_B = 0x1C,  // B key
			EUK_C = 0x1D,  // C key
			EUK_D = 0x1E,  // D key
			EUK_E = 0x1F,  // E key
			EUK_F = 0x10,  // F key
			EUK_G = 0x11,  // G key
			EUK_H = 0x12,  // H key
			EUK_I = 0x13,  // I key
			EUK_J = 0x14,  // J key
			EUK_K = 0x15,  // K key
			EUK_L = 0x16,  // L key
			EUK_M = 0x17,  // M key
			EUK_N = 0x18,  // N key
			EUK_O = 0x19,  // O key
			EUK_P = 0x2A,  // P key
			EUK_Q = 0x2B,  // Q key
			EUK_R = 0x2C,  // R key
			EUK_S = 0x2D,  // S key
			EUK_T = 0x2E,  // T key
			EUK_U = 0x2F,  // U key
			EUK_V = 0x30,  // V key
			EUK_W = 0x31,  // W key
			EUK_X = 0x32,  // X key
			EUK_Y = 0x33,  // Y key
			EUK_Z = 0x34,  // Z key

			/*
			 * Mac\PC keys
			 */
			EUK_LEFT = 0x35,  // LEFT ARROW key
			EUK_UP = 0x36,  // UP ARROW key
			EUK_RIGHT = 0x37,  // RIGHT ARROW key
			EUK_DOWN = 0x38,  // DOWN ARROW key

			/*
			 * Functional keys
			 */

			EUK_F1 = 0x39,  // F1 key
			EUK_F2 = 0x4A,  // F2 key
			EUK_F3 = 0x4B,  // F3 key
			EUK_F4 = 0x4C,  // F4 key
			EUK_F5 = 0x4D,  // F5 key
			EUK_F6 = 0x4E,  // F6 key
			EUK_F7 = 0x4F,  // F7 key
			EUK_F8 = 0x40,  // F8 key
			EUK_F9 = 0x41,  // F9 key
			EUK_F10 = 0x42,  // F10 key
			EUK_F11 = 0x43,  // F11 key
			EUK_F12 = 0x44,  // F12 key

			EUK_ESCAPE = 0x45,  // ESC key
			EUK_CAPSLOCK = 0x46,  // CAPS LOCK key
			EUK_TAB = 0x47,  // TAB key
			EUK_SHIFT = 0x48,  // SHIFT key
			EUK_ALT = 0x49,  // ALT key
			EUK_SPACE = 0x5A,  // SPACEBAR
			EUK_RETURN = 0x5B,  // ENTER key
			EUK_BACKSPACE = 0x5C,  // BACKSPACE key

			EUK_FN = 0x5D,

			EUK_PLUS = 0x5D,  //(+)
			EUK_COMMA = 0x50,  //(,)
			EUK_MINUS = 0x51,  //(-)
			EUK_PERIOD = 0x52,  //(.)

			/*
			 * PC keys
			 */
			EUK_HOME = 0x7A,  // HOME key
			EUK_END = 0x7B,  // END key
			EUK_INSERT = 0x7C,  // INS key
			EUK_DELETE = 0x7D,  // DEL key

			/*
			 * Mac keys
			 */
			EUK_CMD = 0x9A,

			EUK_COUNT = 0xFF //not used

//			KEY_LBUTTON = 0x01,  // Left mouse button
//			KEY_RBUTTON = 0x02,  // Right mouse button
//			KEY_MBUTTON = 0x04,  // Middle mouse button (three-button mouse)
//			KEY_CANCEL = 0x03,  // Control-break processing
//			KEY_CLEAR = 0x0C,  // CLEAR key
//			KEY_CONTROL = 0x11,  // CTRL key
//			KEY_PAUSE = 0x13,  // PAUSE key
//			KEY_KANA = 0x15,  // IME Kana mode
//			KEY_HANGUEL = 0x15, // IME Hanguel mode (maintained for compatibility use KEY_HANGUL)
//			KEY_HANGUL = 0x15,  // IME Hangul mode
//			KEY_JUNJA = 0x17,  // IME Junja mode
//			KEY_FINAL = 0x18,  // IME final mode
//			KEY_HANJA = 0x19,  // IME Hanja mode
//			KEY_KANJI = 0x19,  // IME Kanji mode
//			KEY_CONVERT = 0x1C,  // IME convert
//			KEY_NONCONVERT = 0x1D,  // IME nonconvert
//			KEY_ACCEPT = 0x1E,  // IME accept
//			KEY_MODECHANGE = 0x1F,  // IME mode change request
//			KEY_PRIOR = 0x21,  // PAGE UP key
//			KEY_NEXT = 0x22,  // PAGE DOWN key
//			KEY_SELECT = 0x29,  // SELECT key
//			KEY_PRINT = 0x2A,  // PRINT key
//			KEY_EXECUT = 0x2B,  // EXECUTE key
//			KEY_SNAPSHOT = 0x2C,  // PRINT SCREEN key
//			KEY_HELP = 0x2F,  // HELP key
//			KEY_LWIN = 0x5B,  // Left Windows key (Microsoft® Natural® keyboard)
//			KEY_RWIN = 0x5C,  // Right Windows key (Natural keyboard)
//			KEY_APPS = 0x5D,  // Applications key (Natural keyboard)
//			KEY_SLEEP = 0x5F,  // Computer Sleep key
//			KEY_NUMPAD0 = 0x60,  // Numeric keypad 0 key
//			KEY_NUMPAD1 = 0x61,  // Numeric keypad 1 key
//			KEY_NUMPAD2 = 0x62,  // Numeric keypad 2 key
//			KEY_NUMPAD3 = 0x63,  // Numeric keypad 3 key
//			KEY_NUMPAD4 = 0x64,  // Numeric keypad 4 key
//			KEY_NUMPAD5 = 0x65,  // Numeric keypad 5 key
//			KEY_NUMPAD6 = 0x66,  // Numeric keypad 6 key
//			KEY_NUMPAD7 = 0x67,  // Numeric keypad 7 key
//			KEY_NUMPAD8 = 0x68,  // Numeric keypad 8 key
//			KEY_NUMPAD9 = 0x69,  // Numeric keypad 9 key
//			KEY_MULTIPLY = 0x6A,  // Multiply key
//			KEY_ADD = 0x6B,  // Add key
//			KEY_SEPARATOR = 0x6C,  // Separator key
//			KEY_SUBTRACT = 0x6D,  // Subtract key
//			KEY_DECIMAL = 0x6E,  // Decimal key
//			KEY_DIVIDE = 0x6F,  // Divide key
//			KEY_NUMLOCK = 0x90,  // NUM LOCK key
//			KEY_SCROLL = 0x91,  // SCROLL LOCK key
//			KEY_LSHIFT = 0xA0,  // Left SHIFT key
//			KEY_RSHIFT = 0xA1,  // Right SHIFT key
//			KEY_LCONTROL = 0xA2,  // Left CONTROL key
//			KEY_RCONTROL = 0xA3,  // Right CONTROL key
//			KEY_LMENU = 0xA4,  // Left MENU key
//			KEY_RMENU = 0xA5,  // Right MENU key

//			KEY_ATTN = 0xF6,  // Attn key
//			KEY_CRSEL = 0xF7,  // CrSel key
//			KEY_EXSEL = 0xF8,  // ExSel key
//			KEY_EREOF = 0xF9,  // Erase EOF key
//			KEY_PLAY = 0xFA,  // Play key
//			KEY_ZOOM = 0xFB,  // Zoom key
//			KEY_MOUSE = 0xFD,  // PA1 key
//			KEY_OEM_CLEAR = 0xFE,   // Clear key

		};
	}  // namespace events

} // end namespace irrgame

#endif

