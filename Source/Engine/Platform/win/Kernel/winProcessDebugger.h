//! @file     winProcessDebugger.h
//! @author   LiCode
//! @version  1.1.0.702
//! @date     2011/02/15
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winProcessDebugger
//----------------------------------------------------------------------------

class winProcessDebugger : public INTERFACE_OBSERVABLE_IMPL( IProcessDebugger )
{
private:
	//!	The exit code
	_dword		mExitCode;
	//!	The debug event
	DEBUG_EVENT	mDebugEvent;

	//!	The process ID
	_dword		mProcessID;
	//!	The process handle
	_handle		mProcessHandle;

private:
	//!	Run process.
	//!	@param		none.
	//! @return		True indicates success false indicates failure.
	_ubool RunProcess( );

public:
	winProcessDebugger( );
	virtual ~winProcessDebugger( );

// IProcessDebugger Interface
public:
	virtual _dword	GetExitCode( ) const override;

	virtual _ubool	Run( AStringPtr modulename, AStringPtr cmdline, _dword creationflags, AStringPtr workdir, _ubool nodebugheap = _true, _ubool fastmode = _false ) override;
	virtual _ubool	Run( WStringPtr modulename, WStringPtr cmdline, _dword creationflags, WStringPtr workdir, _ubool nodebugheap = _true, _ubool fastmode = _false ) override;
};

//----------------------------------------------------------------------------
// winProcessDebugger Implementation
//----------------------------------------------------------------------------

}