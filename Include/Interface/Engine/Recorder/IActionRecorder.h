//! @file     IActionRecorder.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IActionRecorder
//----------------------------------------------------------------------------

class IActionRecorder : public IObject
{
public:
	//!	Process actions.
	//!	@param		none.
	//! @return		none.
	virtual _void ProcessActions( ) PURE;

	//!	Get actions number.
	//!	@param		none.
	//!	@return		The actions number.
	virtual _dword GetActionsNumber( ) const PURE;
	//!	Get action by index.
	//!	@param		index	The action index.
	//!	@return		The action interface.
	virtual IActionRecord* GetActionByIndex( _dword index ) PURE;
	//!	Get the last action.
	//!	@param		none.
	//!	@return		The action interface.
	virtual IActionRecord* GetLastAction( ) PURE;
	//!	Clear all actions.
	//!	@param		wait_for_all	True indicates wait for all processing tasks finished.
	//!	@return		none.
	virtual _void ClearAllActions( _ubool wait_for_all ) PURE;
	//!	Add action.
	//!	@param		action	The action.
	//!	@return		none.
	virtual _void AddAction( IActionRecord* action ) PURE;
	//!	Insert action.
	//!	@param		index	The action index ( start from 0 ).
	//!	@param		action	The action.
	//!	@return		none.
	virtual _void InsertAction( _dword index, IActionRecord* action ) PURE;
};

}