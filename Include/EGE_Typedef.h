//! @file     EGE_Typedef.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

#ifdef _PLATFORM_IOS_
#	include <sys/types.h>
#endif

namespace EGE {

//! 8-bits ANSI character.
typedef char _chara;
//! 16-bits UNICODE character.
typedef wchar_t _charw;
//! Signed 8-bits integer.
typedef signed char _tiny;
//! Signed 16-bits integer.
typedef signed short _short;
//! Signed 32-bits integer.
typedef signed int _int;
//! Unsigned 8-bits integer.
typedef unsigned char _byte;
//! Unsigned 16-bits integer.
typedef unsigned short _word;
//! Unsigned 32-bits integer.
//! @remark: Be careful, we use 'unsigned long' before, but the arm64 compile
//! will make it as 64-bits data type ! so here we use 'unsigned int' to replace
//! it.
typedef unsigned int _dword;
//! Signed 64-bits integer.
typedef signed long long _large;
//! Unsigned 64-bits integer.
typedef unsigned long long _qword;
//! Signed 32/64-bits integer, (Base on compiler, BE CAREFUL TO USE IT !!!)
typedef long _long;
//! 32-bits floating point number.
typedef float _float;
//! 64-bits floating point number.
typedef double _double;
//! Boolean value ( 8 Bits ), 0 indicates false, other values indicate true.
typedef bool _boolean;
//!	Boolean value ( 32 Bits ), Only use for return value of function.
typedef unsigned int _ubool_ret;
//! Any type.
typedef void _void;
//! Handle to a win32 kernel object.
typedef void* _handle;
//! A time value in seconds.
typedef time_t _time_t;
//! The unsigned int pointer
typedef uintptr_t _uintptr_t;

//!	The CRC value
typedef unsigned int _crcvalue;

//!	The arguments list
typedef va_list _va_list;

//! The thread ID
typedef _qword _thread_id;
//!	The thread return type
#if defined _PLATFORM_WINDOWS_
typedef _dword _thread_ret;
#elif defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_)
typedef void* _thread_ret;
#endif

//! Boolean value ( 32 Bits ), 0 indicates false, other values indicate true.
struct _ubool {
	_dword mValue;

	_ubool() {
	}
	_ubool(_boolean value) {
		mValue = value;
	}
	_ubool(_int value) {
		mValue = EGE_BOOLEAN(value);
	}
	_ubool(_dword value) {
		mValue = EGE_BOOLEAN(value);
	}
	_ubool(const _ubool& value) {
		mValue = value.mValue;
	}

	operator _boolean() const {
		return EGE_BOOLEAN(mValue);
	}

	_ubool& operator=(_boolean value) {
		mValue = value;
		return *this;
	}
	_ubool& operator&=(_boolean value) {
		mValue &= (_dword)value;
		return *this;
	}
	_ubool& operator|=(_boolean value) {
		mValue |= (_dword)value;
		return *this;
	}
	_ubool& operator^=(_boolean value) {
		mValue ^= (_dword)value;
		return *this;
	}
};

} // namespace EGE
