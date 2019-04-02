#pragma once

namespace EGE {

class anyPlatformEndian {
public:
	static _ubool IsLittleEndian();
	static _ubool IsBigEndian();
	static Endian GetEndianType();
};

} // namespace EGE