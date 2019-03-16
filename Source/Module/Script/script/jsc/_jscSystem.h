//! @file     _jscSystem.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _jscSystem
//----------------------------------------------------------------------------

class _jscSystem : public _t_scriptSystem< _scriptSystem >
{
private:
	//!	The default stack allocator size
	enum { _DEFAULT_STACK_ALLOCATOR_SIZE = 256 KB };
	//!	The default GC collection interval time in milliseconds
	enum { _DEFAULT_GC_COLLECTION_INTERVAL = 60 SEC };

private:
	//!	The GC cleanup timer
	Timer				mGCCleanupTimer;

	//!	The stack allocator 
	IStackAllocatorRef	mAllocator;

	//!	The global JS class
	JSClassRef			mJSClass;
	//!	The global JS context
	JSGlobalContextRef	mJSContext;
	//!	The handle scope
	JSHandleScope		mJSHandleScope;
	//!	The run time
	JSRunTimeRef		mJSRunTime;

private:
	//!	When initialize.
	_ubool OnInititalize( );
	//!	When finalize.
	_void OnFinalize( );

public:
	_jscSystem( );
	virtual ~_jscSystem( );

public:
	//!	Get the allocator.
	EGE_GET_ACCESSOR( IStackAllocatorRef, Allocator )

// IObject Interface
public:
	virtual _void				Tick( _dword limited_elapse, _dword elapse ) override;

// _scriptSystem Interface
public:
	virtual _ubool				Initialize( ) override;

	virtual _scriptModuleRef	CreateScriptModule( AStringPtr name, AStringPtr desc ) override;

	virtual _scriptVMPassRef	CreateScriptVM( ) override;
};

}