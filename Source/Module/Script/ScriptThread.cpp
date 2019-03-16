//! @file     ScriptThread.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#ifndef _EGE_DISABLE_SCRIPT_MODULE_

//----------------------------------------------------------------------------
// ScriptThreadTask Implementation
//----------------------------------------------------------------------------

ScriptThreadTask::ScriptThreadTask( IScriptFunction* script_func )
{
	mScriptFunction = script_func;
}

ScriptThreadTask::ScriptThreadTask( IScriptFunction* script_func, const VariableArray& vars )
{
	mScriptFunction = script_func;

	mScriptArgs		= vars;
}

ScriptThreadTask::~ScriptThreadTask( )
{
}

ITask::_OPERATION_TYPE ScriptThreadTask::OnProcess( _thread_id threadid, _dword& err_id )
{
	// Invoke the function with arguments
	IScriptValueRef ret_value = mScriptFunction->InvokeByVars( mScriptArgs );
	EGE_ASSERT( ret_value.IsValid( ) );

	// Finished
	Finish( );

	return _OPT_FINISH;
}

//----------------------------------------------------------------------------
// ScriptThreadPool Implementation
//----------------------------------------------------------------------------

ScriptThreadPool::ScriptThreadPool( )
{

}

ScriptThreadPool::~ScriptThreadPool( )
{
	mThreadPool.Clear( );
}

_void ScriptThreadPool::Tick( _time_t tick, _dword elapse )
{
	mThreadPool->Tick( tick, elapse );
}

_ubool ScriptThreadPool::Initialize( _dword thread_number )
{
//	mThreadPool = GetInterfaceFactory( )->CreateThreadPool( thread_number, L"ScriptThreadPool" );
	mThreadPool = GetInterfaceFactory( )->CreateSingleThreadPool( );
	if ( mThreadPool.IsNull( ) )
		return _false;

	return _true;
}

_void ScriptThreadPool::Finalize( )
{
	mThreadPool.Clear( );
}

_void ScriptThreadPool::AddTask( ScriptThreadTask* task )
{
	EGE_ASSERT( task != _null );

	mThreadPool->AddTask( task );

	mThreadPool->Wakeup( );
}

#endif