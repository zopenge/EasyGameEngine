//! @file     IProcessDebugger.h
//! @author   LiCode
//! @version  1.0.0.702
//! @date     2011/02/15
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IProcessDebugger
//----------------------------------------------------------------------------

class IProcessDebugger : public IObservable
{
public:
	//!	Get the exit code.
	//!	@param		none.
	//!	@return		The exit code of process.
	virtual _dword GetExitCode( ) const PURE;

	//!	Run the process.
	//!	@param		modulename		The module name of launching.
	//!	@param		cmdline			The command line of launching.
	//!	@param		creationflags	The creation flags.
	//!	@param		workdir			The working directory.
	//!	@param		nodebugheap		True indicates set the environment '_NO_DEBUG_HEAP' variable to not use the debug heap routines.
	//!	@param		fastmode		True indicates we will run the process without any information collection.
	//! @return		True indicates success false indicates failure.
	virtual _ubool Run( WStringPtr modulename, WStringPtr cmdline, _dword creationflags, WStringPtr workdir, _ubool nodebugheap = _true, _ubool fastmode = _false ) PURE;
};

}