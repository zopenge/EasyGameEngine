//! @file     _jscException.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// _jscException
//----------------------------------------------------------------------------

class _jscException
{
private:
	//!	The JS exception
	JSValueRef	mJSException;

public:
	_jscException( JSValueRef js_exception );
	~_jscException( );

public:
	//!	Get the line number.
	_dword GetLineNumber( ) const;
	//!	Get the message.
	WString GetMessage( ) const;
};

}