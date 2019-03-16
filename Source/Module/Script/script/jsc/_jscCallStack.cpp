//! @file     _jscCallStack.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JS_ == 1)

//----------------------------------------------------------------------------
// _jscCallStack Implementation
//----------------------------------------------------------------------------

_jscCallStack::_jscCallStack( JSContextRef js_context )
{
	mJSContext = js_context;
}

_jscCallStack::~_jscCallStack( )
{
}

_void _jscCallStack::PrintCallStack( JSContextRef js_context )
{
	_jscCallStack jsc_callstack( js_context );

	_jscCallStack::FrameInfoArray call_stack;
	if ( jsc_callstack.DumpCallStack( call_stack ) )
	{
		for ( _dword i = 0; i < call_stack.Number( ); i ++ )
		{
			const _jscCallStack::FrameInfo& frame_info = call_stack[i];

			ALOG_ERROR_2( "\t=> %s(%u)",
				frame_info.mFileName.Str( ),
				frame_info.mLineNumber );
		}
	}
}

#endif