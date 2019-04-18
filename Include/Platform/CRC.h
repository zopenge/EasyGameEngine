#pragma once

namespace EGE {

/// <summary>
/// The CRC builder.
/// </summary>
class CRC {
public:
	//! Build the CRC value from buffer.
	//! @param buffer  The buffer data.
	//! @param size  The buffer size.
	//! @param oldcrc  The old CRC value.
	//! @return The CRC value.
	static _dword BuildFromBuffer(const _byte* buffer, _dword size, _dword oldcrc = 0);

	//! Build the CRC value from ANSI string.
	//! @param string  The ANSI string.
	//! @param flag  The build string flag.
	//! @param oldcrc  The old CRC value.
	//! @return The CRC value.
	static _dword BuildFromString(const _chara* string, _dword oldcrc = 0);
	//! Build the CRC value from UNICODE string.
	//! @param string  The UNICODE string.
	//! @param flag  The build string flag.
	//! @param oldcrc  The old CRC value.
	//! @return The CRC value.
	static _dword BuildFromString(const _charw* string, _dword oldcrc = 0);
};

} // namespace EGE