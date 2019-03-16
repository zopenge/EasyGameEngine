//! @file     _scriptModule.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _scriptModule
//----------------------------------------------------------------------------

class _scriptModule : public IObject
{
public:
	//!	Initialize.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Initialize( ) PURE;
};

}