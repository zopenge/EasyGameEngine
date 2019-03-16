//! @file     IActionRecord.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IActionRecord
//----------------------------------------------------------------------------

class IActionRecord : public IObject
{
public:
	//!	Process.
	//!	@param		none.
	//! @return		The process state.
	virtual _PROCESS_STATE Process( ) PURE;
};

}