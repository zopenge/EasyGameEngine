//! @file     IThreadTaskSet.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IThreadTaskSet
//----------------------------------------------------------------------------

class IThreadTaskSet : public ITask
{
public:
	//! Get the sub-tasks number
	//! @param		none.
	//! @return		The sub-tasks number.
	virtual _dword GetSubTaskNumber( ) const PURE;

	//!	Get the maximal working range of sub-tasks.
	//!	@param		none.
	//!	@return		The maximal working range of sub-tasks.
	virtual _dword GetMaxRangeOfSubTask( ) const PURE;

	//!	Process the sub-task.
	//!	@param		threadid	The thread ID.
	//!	@param		index		The sub-task index.
	//!	@param		err_id		The error ID, 0 indicates no error occurred.
	//! @return		The operation type.
	virtual _OPERATION_TYPE ProcessSubTask( _thread_id threadid, _dword index, _dword& err_id ) PURE;
};

}