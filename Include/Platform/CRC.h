//! @file     CRC.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// CRC
//----------------------------------------------------------------------------

class CRC
{
public:
	//! The build string flag
	enum _BUILD_STRING_FLAG
	{
		_BUILD_STRING_NORMAL,
		_BUILD_STRING_LOWERCASE,
		_BUILD_STRING_UPPERCASE,
	};

public:
	//! Build the CRC value from buffer.
	//! @param		buffer		The buffer data.
	//! @param		size		The buffer size.
	//! @param		oldcrc		The old CRC value.
	//! @return		The CRC value.
	static _crcvalue BuildFromBuffer( const _byte* buffer, _dword size, _crcvalue oldcrc = 0 );

	//! Build the CRC value from ANSI string.
	//! @param		string		The ANSI string.
	//! @param		flag		The build string flag.
	//! @param		oldcrc		The old CRC value.
	//! @return		The CRC value.
	static _crcvalue BuildFromString( const _chara* string, _dword flag = _BUILD_STRING_NORMAL, _crcvalue oldcrc = 0 );
	//! Build the CRC value from UNICODE string.
	//! @param		string		The UNICODE string.
	//! @param		flag		The build string flag.
	//! @param		oldcrc		The old CRC value.
	//! @return		The CRC value.
	static _crcvalue BuildFromString( const _charw* string, _dword flag = _BUILD_STRING_NORMAL, _crcvalue oldcrc = 0 );
};

}