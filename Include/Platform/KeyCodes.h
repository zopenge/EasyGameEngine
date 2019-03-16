//! @file     KeyCodes.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// The Key Codes
//----------------------------------------------------------------------------

enum _KEY {
#ifdef _PLATFORM_WINDOWS_
  _KEY_BACKSPACE = 0x08,
  _KEY_RETURN = 0x0D,
  _KEY_CONTROL = 0x11,
  _KEY_ESCAPE = 0x1B,
  _KEY_CONVERT = 0x1C,
  _KEY_NONCONVERT = 0x1D,
  _KEY_ACCEPT = 0x1E,
  _KEY_MODECHANGE = 0x1F,
  _KEY_SPACE = 0x20,
  _KEY_PRIOR = 0x21,
  _KEY_NEXT = 0x22,
  _KEY_END = 0x23,
  _KEY_HOME = 0x24,
  _KEY_LEFT = 0x25,
  _KEY_UP = 0x26,
  _KEY_RIGHT = 0x27,
  _KEY_DOWN = 0x28,
  _KEY_SELECT = 0x29,
  _KEY_PRINT = 0x2A,
  _KEY_EXECUTE = 0x2B,
  _KEY_SNAPSHOT = 0x2C,
  _KEY_INSERT = 0x2D,
  _KEY_DELETE = 0x2E,
  _KEY_HELP = 0x2F,
  _KEY_NUMPAD0 = 0x60,
  _KEY_NUMPAD1 = 0x61,
  _KEY_NUMPAD2 = 0x62,
  _KEY_NUMPAD3 = 0x63,
  _KEY_NUMPAD4 = 0x64,
  _KEY_NUMPAD5 = 0x65,
  _KEY_NUMPAD6 = 0x66,
  _KEY_NUMPAD7 = 0x67,
  _KEY_NUMPAD8 = 0x68,
  _KEY_NUMPAD9 = 0x69,
  _KEY_MULTIPLY = 0x6A,
  _KEY_ADD = 0x6B,
  _KEY_SEPARATOR = 0x6C,
  _KEY_SUBTRACT = 0x6D,
  _KEY_DECIMAL = 0x6E,
  _KEY_DIVIDE = 0x6F,
  _KEY_F1 = 0x70,
  _KEY_F2 = 0x71,
  _KEY_F3 = 0x72,
  _KEY_F4 = 0x73,
  _KEY_F5 = 0x74,
  _KEY_F6 = 0x75,
  _KEY_F7 = 0x76,
  _KEY_F8 = 0x77,
  _KEY_F9 = 0x78,
  _KEY_F10 = 0x79,
  _KEY_F11 = 0x7A,
  _KEY_F12 = 0x7B,
  _KEY_F13 = 0x7C,
  _KEY_F14 = 0x7D,
  _KEY_F15 = 0x7E,
  _KEY_F16 = 0x7F,
  _KEY_F17 = 0x80,
  _KEY_F18 = 0x81,
  _KEY_F19 = 0x82,
  _KEY_F20 = 0x83,
  _KEY_F21 = 0x84,
  _KEY_F22 = 0x85,
  _KEY_F23 = 0x86,
  _KEY_F24 = 0x87,
  _KEY_SHIFT_LEFT = 0xA0,
  _KEY_SHIFT_RIGHT = 0xA1,
  _KEY_OEM_PLUS = 0xBB,    //! '+' any country
  _KEY_OEM_COMMA = 0xBC,   //! ',' any country
  _KEY_OEM_MINUS = 0xBD,   //! '-' any country
  _KEY_OEM_PERIOD = 0xBE,  //! '.' any country
#elif _PLATFORM_ANDROID_
  _KEY_UNKNOWN = 0,
  _KEY_SOFT_LEFT = 1,
  _KEY_SOFT_RIGHT = 2,
  _KEY_HOME = 3,
  _KEY_BACK = 4,
  _KEY_CALL = 5,
  _KEY_ENDCALL = 6,
  _KEY_0 = 7,
  _KEY_1 = 8,
  _KEY_2 = 9,
  _KEY_3 = 10,
  _KEY_4 = 11,
  _KEY_5 = 12,
  _KEY_6 = 13,
  _KEY_7 = 14,
  _KEY_8 = 15,
  _KEY_9 = 16,
  _KEY_STAR = 17,
  _KEY_POUND = 18,
  _KEY_DPAD_UP = 19,
  _KEY_DPAD_DOWN = 20,
  _KEY_DPAD_LEFT = 21,
  _KEY_DPAD_RIGHT = 22,
  _KEY_DPAD_CENTER = 23,
  _KEY_VOLUME_UP = 24,
  _KEY_VOLUME_DOWN = 25,
  _KEY_POWER = 26,
  _KEY_CAMERA = 27,
  _KEY_CLEAR = 28,
  _KEY_A = 29,
  _KEY_B = 30,
  _KEY_C = 31,
  _KEY_D = 32,
  _KEY_E = 33,
  _KEY_F = 34,
  _KEY_G = 35,
  _KEY_H = 36,
  _KEY_I = 37,
  _KEY_J = 38,
  _KEY_K = 39,
  _KEY_L = 40,
  _KEY_M = 41,
  _KEY_N = 42,
  _KEY_O = 43,
  _KEY_P = 44,
  _KEY_Q = 45,
  _KEY_R = 46,
  _KEY_S = 47,
  _KEY_T = 48,
  _KEY_U = 49,
  _KEY_V = 50,
  _KEY_W = 51,
  _KEY_X = 52,
  _KEY_Y = 53,
  _KEY_Z = 54,
  _KEY_COMMA = 55,
  _KEY_PERIOD = 56,
  _KEY_ALT_LEFT = 57,
  _KEY_ALT_RIGHT = 58,
  _KEY_SHIFT_LEFT = 59,
  _KEY_SHIFT_RIGHT = 60,
  _KEY_TAB = 61,
  _KEY_SPACE = 62,
  _KEY_SYM = 63,
  _KEY_EXPLORER = 64,
  _KEY_ENVELOPE = 65,
  _KEY_ENTER = 66,
  _KEY_DEL = 67,
  _KEY_GRAVE = 68,
  _KEY_MINUS = 69,
  _KEY_EQUALS = 70,
  _KEY_LEFT_BRACKET = 71,
  _KEY_RIGHT_BRACKET = 72,
  _KEY_BACKSLASH = 73,
  _KEY_SEMICOLON = 74,
  _KEY_APOSTROPHE = 75,
  _KEY_SLASH = 76,
  _KEY_AT = 77,
  _KEY_NUM = 78,
  _KEY_HEADSETHOOK = 79,
  _KEY_FOCUS = 80,  // *Camera* focus
  _KEY_PLUS = 81,
  _KEY_MENU = 82,
  _KEY_NOTIFICATION = 83,
  _KEY_SEARCH = 84,
  _KEY_MEDIA_PLAY_PAUSE = 85,
  _KEY_MEDIA_STOP = 86,
  _KEY_MEDIA_NEXT = 87,
  _KEY_MEDIA_PREVIOUS = 88,
  _KEY_MEDIA_REWIND = 89,
  _KEY_MEDIA_FAST_FORWARD = 90,
  _KEY_MUTE = 91,
  _KEY_PAGE_UP = 92,
  _KEY_PAGE_DOWN = 93,
  _KEY_PICTSYMBOLS = 94,
  _KEY_SWITCH_CHARSET = 95,
  _KEY_BUTTON_A = 96,
  _KEY_BUTTON_B = 97,
  _KEY_BUTTON_C = 98,
  _KEY_BUTTON_X = 99,
  _KEY_BUTTON_Y = 100,
  _KEY_BUTTON_Z = 101,
  _KEY_BUTTON_L1 = 102,
  _KEY_BUTTON_R1 = 103,
  _KEY_BUTTON_L2 = 104,
  _KEY_BUTTON_R2 = 105,
  _KEY_BUTTON_THUMBL = 106,
  _KEY_BUTTON_THUMBR = 107,
  _KEY_BUTTON_START = 108,
  _KEY_BUTTON_SELECT = 109,
  _KEY_BUTTON_MODE = 110,
  _KEY_UP = _KEY_DPAD_UP,
  _KEY_DOWN = _KEY_DPAD_DOWN,
  _KEY_LEFT = _KEY_DPAD_LEFT,
  _KEY_RIGHT = _KEY_DPAD_RIGHT,
  _KEY_RETURN = _KEY_DPAD_CENTER,
  _KEY_ESCAPE = _KEY_BACK,
#endif
};

}  // namespace EGE