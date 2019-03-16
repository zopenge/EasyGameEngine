//! @file     ActionRecorder.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ActionRecorder
//----------------------------------------------------------------------------

class ActionRecorder : public INTERFACE_OBJECT_IMPL( IActionRecorder )
{
private:
	typedef Array< IActionRecordRef > ActionArray;

private:
	Lock		mLock;
	_ubool		mIsClearing;

	ActionArray	mProcessingActions;
	ActionArray	mActions;

private:
	//!	Check whether it's removable status.
	_ubool IsRemovableStatus( _PROCESS_STATE state ) const;

public:
	ActionRecorder( );
	virtual ~ActionRecorder( );

// IActionRecorder Interface
public:
	virtual _void			ProcessActions( ) override;

	virtual _dword			GetActionsNumber( ) const override;
	virtual IActionRecord*	GetActionByIndex( _dword index ) override;
	virtual IActionRecord*	GetLastAction( ) override;
	virtual _void			ClearAllActions( _ubool wait_for_all ) override;
	virtual _void			AddAction( IActionRecord* action ) override;
	virtual _void			InsertAction( _dword index, IActionRecord* action ) override;
};

//----------------------------------------------------------------------------
// ActionRecorder Implementation
//----------------------------------------------------------------------------

}