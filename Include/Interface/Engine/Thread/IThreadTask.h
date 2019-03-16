//! @file     IThreadTask.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IThreadTask
//----------------------------------------------------------------------------

class IThreadTask : public ITask
{
public:
	//!	When process the task in thread.
	//!	@param		threadid	The thread ID.
	//!	@param		err_id		The error ID, 0 indicates no error occurred.
	//! @return		The operation type.
	virtual _OPERATION_TYPE OnProcess( _thread_id threadid, _dword& err_id ) PURE;
};

}