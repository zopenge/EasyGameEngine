//! @file     _jscCallStack.spidermonkey.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_SPIDER_MONKEY_ == 1)

//----------------------------------------------------------------------------
// _jscCallStack Implementation
//----------------------------------------------------------------------------

_ubool _jscCallStack::DumpCallStack( FrameInfoArray& callstack )
{
#ifdef _SCRIPT_USE_OLD_SPIDER_MONKEY_
	JSStackFrame* js_stack_frame = _null;
	for ( JS_FrameIterator( mJSContext, &js_stack_frame ); js_stack_frame != _null; JS_FrameIterator( mJSContext, &js_stack_frame ) )
	{
		JSScript* js_script = JS_GetFrameScript( mJSContext, js_stack_frame );
		if ( js_script == _null )
			continue;

		jsbytecode* js_pc = JS_GetFramePC( mJSContext, js_stack_frame );
		if ( js_pc == _null )
			continue;

		_dword line_number = JS_PCToLineNumber( mJSContext, js_script, js_pc );
		if ( line_number == 0 )
			continue;

		callstack.Append( FrameInfo( line_number, js_script->filename ) );
	}
#else
	JS::StackDescription* js_stack_desc = JS::DescribeStack( mJSContext, -1 );
	if ( js_stack_desc == _null )
		return _false;

	for ( _dword i = 0; i < js_stack_desc->nframes; i ++ )
	{
		const JS::FrameDescription& js_desc = js_stack_desc->frames[i];

		// Get the JS script file name
		const _chara* js_script_filename = ::JS_GetScriptFilename( mJSContext, js_desc.script );
		if ( js_script_filename == _null )
			continue;

		callstack.Append( FrameInfo( js_desc.lineno, js_script_filename ) );
	}

	JS::FreeStackDescription( mJSContext, js_stack_desc );
#endif

	return _true;
}

#endif