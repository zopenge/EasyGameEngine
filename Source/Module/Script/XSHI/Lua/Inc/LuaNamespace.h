//! @file     LuaNamespace.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// LuaNamespace
//----------------------------------------------------------------------------

class LuaNamespace : public LuaTable< ClassXSHI >
{
public:
	LuaNamespace( );
	virtual ~LuaNamespace( );
};

}