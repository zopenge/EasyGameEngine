//! @file     anyPlatformEndian.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE {

//----------------------------------------------------------------------------
// anyPlatformEndian
//----------------------------------------------------------------------------

class anyPlatformEndian {
public:
	static _ubool IsLittleEndian();
	static _ubool IsBigEndian();
	static Endian GetEndianType();
};

//----------------------------------------------------------------------------
// anyPlatformEndian Implementation
//----------------------------------------------------------------------------

} // namespace EGE