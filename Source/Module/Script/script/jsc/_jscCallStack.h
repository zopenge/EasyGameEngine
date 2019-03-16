//! @file     _jscCallStack.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _jscCallStack
//----------------------------------------------------------------------------

class _jscCallStack
{
public:
	//!	The callstack frame info
	struct FrameInfo
	{
		AString	mFileName;
		_dword	mLineNumber;

		FrameInfo( )
		{
			mLineNumber = 0;
		}
		FrameInfo( _dword line_number, AStringPtr file_name )
		{
			mLineNumber = line_number;
			mFileName	= file_name;
		}
	};
	typedef Array< FrameInfo > FrameInfoArray;

private:
	JSContextRef	mJSContext;

public:
	_jscCallStack( JSContextRef js_context );
	~_jscCallStack( );

public:
	//!	Dump the callstack frame info.
	//!	@param		callstack		The callstack frames.
	//!	@return		True indicates successful, otherwise indicates failure.
	_ubool DumpCallStack( FrameInfoArray& callstack );

public:
	//!	Print the callstack.
	//!	@param		js_context		The JS context.
	//!	@return		none.
	static _void PrintCallStack( JSContextRef js_context );
};

}