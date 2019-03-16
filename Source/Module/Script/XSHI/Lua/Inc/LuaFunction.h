//! @file     LuaFunction.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// LuaFunctionArgDef
//----------------------------------------------------------------------------

struct LuaFunctionArgDef
{
	//!	The argument data type ID
	_XSCRIPT_DATA_TYPE	mDataTypeID;
};
typedef Array< LuaFunctionArgDef > LuaFunctionArgDefArray;

//----------------------------------------------------------------------------
// LuaFunctionDef
//----------------------------------------------------------------------------

struct LuaFunctionDef
{
	//!	The function return type
	WString					mRetType;
	//!	The call type
	_XSCRIPT_CALL_TYPE		mCallType;
};

//----------------------------------------------------------------------------
// LuaFunction
//----------------------------------------------------------------------------

class LuaFunction : public TFunctionXSHI< FunctionXSHI >
{
private:
	//!	Invoke registered function from LUA.
	static _long Invoke( lua_State* state );

public:
	LuaFunction( );
	virtual ~LuaFunction( );

public:
	//!	Initialize.
	_ubool Initialize( lua_State* state, const NativeFunctionDefXSHI& def );
};

}