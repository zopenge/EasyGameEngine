//! @file     _jscCallStack.jsc.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (_SCRIPT_USE_JAVA_SCRIPT_CORE_ == 1)

//----------------------------------------------------------------------------
// _jscCallStack Implementation
//----------------------------------------------------------------------------

_ubool _jscCallStack::DumpCallStack( FrameInfoArray& callstack )
{
	return _true;
}

#endif