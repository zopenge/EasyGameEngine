//! @file     _jscException.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JS_ == 1)

//----------------------------------------------------------------------------
// _jscException Implementation
//----------------------------------------------------------------------------

_jscException::_jscException( JSValueRef js_exception )
{
	mJSException = js_exception;
}

_jscException::~_jscException( )
{
}

#endif