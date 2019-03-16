//! @file     GLULib.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

EGE_BEGIN_NAMESPACE_2( EGE, GLU )

//----------------------------------------------------------------------------
// GLUMethods
//----------------------------------------------------------------------------

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) typedef Ret (APIENTRY *_##FuncName) Args;
#include "Module/Graphic/RHI/GL/Inc/GLUMethods.h"
#undef DEFINE_FUNC_PTR

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) extern _##FuncName FuncName;
#include "Module/Graphic/RHI/GL/Inc/GLUMethods.h"
#undef DEFINE_FUNC_PTR

EGE_END_NAMESPACE_2( )

//!	Load GLU methods from library
extern EGE::_ubool LoadGLULibrary( );