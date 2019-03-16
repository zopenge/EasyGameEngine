//! @file     IScriptRegisteredClass.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IScriptRegisteredClass
//----------------------------------------------------------------------------

class IScriptRegisteredClass : public IObject
{
public:
	//!	Register.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool Register( ) PURE;
};

}