//! @file     ScriptThread.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ScriptThreadTask
//----------------------------------------------------------------------------

class ScriptThreadTask : public INTERFACE_TASK_IMPL( IThreadTask )
{
private:
	typedef INTERFACE_TASK_IMPL( IThreadTask ) BaseClass;

private:
	//!	The script function.
	IScriptFunctionRef	mScriptFunction;

	//!	The parameters what pass to script function
	VariableArray	mScriptArgs;

public:
	ScriptThreadTask( IScriptFunction* script_func );
	ScriptThreadTask( IScriptFunction* script_func, const VariableArray& vars );
	virtual ~ScriptThreadTask( );

// IThreadTask Interface
public:
	virtual _OPERATION_TYPE OnProcess( _thread_id threadid, _dword& err_id ) override;
};

//----------------------------------------------------------------------------
// ScriptThreadPool
//----------------------------------------------------------------------------

class ScriptThreadPool
{
	SINGLETON( ScriptThreadPool )

private:
	//!	The thread pool
	IThreadPoolRef	mThreadPool;

public:
	//!	Initialize.
	_ubool Initialize( _dword thread_number );
	//!	Finalize.
	_void Finalize( );

	//!	Tick.
	_void Tick( _time_t tick, _dword elapse );

	//!	Add thread task.
	_void AddTask( ScriptThreadTask* task );
};

}