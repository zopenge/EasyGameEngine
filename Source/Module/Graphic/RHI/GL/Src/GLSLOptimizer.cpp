//! @file     GLSLOptimizer.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLDrv Implementation
//----------------------------------------------------------------------------

_ubool GLDrv::InitGLSLOptimizer( )
{
	if ( mGLSLOptimizerContext == _null )
	{
#if (_OPENGLES_ == 1)
		_boolean opengl_es = _true;
#else
		_boolean opengl_es = _false;
#endif
		mGLSLOptimizerContext = ::glslopt_initialize( opengl_es );
		if ( mGLSLOptimizerContext == _null )
			return _false;
	}

	return _true;
}

_void GLDrv::FinalizeGLSLOptimizer( )
{
	if ( mGLSLOptimizerContext != _null )
	{
		::glslopt_cleanup( mGLSLOptimizerContext );
		mGLSLOptimizerContext = _null;
	}
}

//----------------------------------------------------------------------------
// GLDrv-Shader-Optimizer Implementation
//----------------------------------------------------------------------------

_ubool GLDrv::OptimizeVertexShaderCode( UStringPtr code, UString& optimized_code )
{
	if ( InitGLSLOptimizer( ) == _false )
		return _false;

	return OptimizeShaderCode( _SHADER_CODE_VS, code, optimized_code );
}

_ubool GLDrv::OptimizePixelShaderCode( UStringPtr code, UString& optimized_code )
{
	if ( InitGLSLOptimizer( ) == _false )
		return _false;

	return OptimizeShaderCode( _SHADER_CODE_PS, code, optimized_code );
}

_ubool GLDrv::OptimizeShaderCode( _SHADER_CODE_TYPE code_type, UStringPtr code, UString& optimized_code )
{
	if ( code_type != _SHADER_CODE_VS && code_type != _SHADER_CODE_PS )
		return _false;

	// Get the shader type
	glslopt_shader_type shader_type = code_type == _SHADER_CODE_VS ? kGlslOptShaderVertex : kGlslOptShaderFragment;

	// Create GLSL optimizer
	glslopt_shader* shader = ::glslopt_optimize( mGLSLOptimizerContext, shader_type, code.Str( ), 0 );
	if ( shader == _null )
		return _false;

	// Check the GLSL optimizer status
	_ubool ret = ::glslopt_get_status( shader );
	if ( ret )
	{
		// Get the optimized shader code string
		optimized_code = ::glslopt_get_output( shader );
		if ( optimized_code.IsEmpty( ) )
			ret = _false;
	}
	
	// Get the error log if it's failed
	if ( ret == _false )
	{
		const _chara* log = ::glslopt_get_log( shader );
		if ( log != _null )
		{
			ALOG_ERROR_1( "Optimize shader code failed, error log is :\n%s", log );
		}
	}

	// Delete GLSL shader optimizer
	::glslopt_shader_delete( shader );

	// Feedback the optimized result
	return ret;
}