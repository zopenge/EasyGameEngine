//! @file     ITask.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITask
//----------------------------------------------------------------------------

class ITask : public ITFlagsObject< IObservable >
{
public:
	//!	The flags of task
	enum _FLAGS
	{
		_FLAG_AUTO_START = 1 << 0, //! Enable auto-start feature
		_FLAG_KEEP_ALIVE = 1 << 1, //! Keep the group alive even though all tasks finished
	};

	//!	The operation type
	enum _OPERATION_TYPE
	{
		_OPT_ERR = -1,
		_OPT_CONTINUE,
		_OPT_DELAY,
		_OPT_FINISH,
	};

public:
	//!	Set the last error ID.
	//!	@param		errorid		The last error ID of task.
	//! @return		none.
	virtual _void SetLastErrorID( _dword errorid ) PURE;
	//!	Get the last error ID.
	//!	@param		none.
	//! @return		The last error ID of task.
	virtual _dword GetLastErrorID( ) const PURE;

	//!	Get the state.
	//!	@param		none.
	//! @return		The state of task.
	virtual _PROCESS_STATE GetState( ) const PURE;

	//!	Wait.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Wait( ) PURE;
	//!	Start.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Start( ) PURE;
	//!	Resume.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Resume( ) PURE;
	//!	Suspend.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Suspend( ) PURE;
	//!	Abort.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Abort( ) PURE;
	//!	Finish.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Finish( ) PURE;
};

}