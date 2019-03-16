//! @file     _jscException.v8.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_GOOGLE_V8_ == 1)

//----------------------------------------------------------------------------
// _jscException Implementation
//----------------------------------------------------------------------------

_dword _jscException::GetLineNumber( ) const
{
	return 0;
}

WString _jscException::GetMessage( ) const
{
	return _jscHelper::GetJSStringW( gGlobalJSContext, mJSException );
}

#endif