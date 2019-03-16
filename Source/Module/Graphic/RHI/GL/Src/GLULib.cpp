//! @file     GLULib.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLUMethods
//----------------------------------------------------------------------------

EGE_BEGIN_NAMESPACE_2( EGE, GLU )

#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) _##FuncName FuncName = _null;
#include "Module/Graphic/RHI/GL/Inc/GLUMethods.h"
#undef DEFINE_FUNC_PTR

EGE_END_NAMESPACE_2( )

//----------------------------------------------------------------------------
// Load the GLU library
//----------------------------------------------------------------------------

_ubool LoadGLULibrary( )
{
	// OpenGL mode
#if (_OPENGLES_ == 0)
	// Load GLU library
	_handle glu_dll = Platform::LoadLibrary( "glu32.dll" );
	if ( glu_dll == _null )
		return _false;

	// Get GLU functions
	GET_FUNC_PTR( GLU, glu_dll, gluErrorString )
	GET_FUNC_PTR( GLU, glu_dll, gluErrorUnicodeStringEXT )
	GET_FUNC_PTR( GLU, glu_dll, gluPerspective )
#endif

	return _true;
}
