//! @file     RHIAsyncDrv.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
struct RHIAsyncCommand;

//----------------------------------------------------------------------------
// RHIAsyncDrvThread
//----------------------------------------------------------------------------

class RHIAsyncDrvThread : public Thread
{
private:
	typedef Thread BaseClass;

private:
	//!	The max commands in one render cycle
	enum { _MAX_COMMANDS_NUMBER_PRE_CYCLE = 256 KB };

private:
	//!	The internal dynamic render hardware interface
	IDynamicRHIRef		mDynamicRHI;

	//!	The current command buffer index
	volatile _dword		mCurCommandBufferIndex;
	//!	The current command buffer number
	volatile _dword		mCurCommandBufferNumber;
	//!	The commands buffer
	RHIAsyncCommand*	mCommands[ _MAX_COMMANDS_NUMBER_PRE_CYCLE ];

private:
	//!	Process command.
	_void ProcessCommand( RHIAsyncCommand& command );

// Thread Interface
private:
	virtual _dword OnRunThread( const QwordParameters2& parameters ) override;

public:
	RHIAsyncDrvThread( IDynamicRHI* dynamic_rhi );
	virtual ~RHIAsyncDrvThread( );

public:
	//!	Post command.
	_void PostCommand( RHIAsyncCommand* command );

	//!	Reset commands buffer.
	_void ResetCommandsBuffer( );
};

//----------------------------------------------------------------------------
// RHIAsyncDrv
//----------------------------------------------------------------------------

class RHIAsyncDrv : public INTERFACE_OBJECT_IMPL( IDynamicRHI )
{
private:
	//!	The max buffer size
	enum { _MAX_BUFFER_SIZE = 1 MB };

private:
	IDynamicRHIRef		mDynamicRHI;

	IStackAllocatorRef	mAllocator;

	EventObject			mEvent;
	RHIAsyncDrvThread*	mAsyncThread;

public:
	RHIAsyncDrv( IDynamicRHI* dynamic_rhi );
	virtual ~RHIAsyncDrv( );

public:
	// The RHI methods are defined as virtual functions.
	#define DEFINE_RHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Graphic/RHIMethods.h"
	#undef DEFINE_RHIMETHOD
};

}