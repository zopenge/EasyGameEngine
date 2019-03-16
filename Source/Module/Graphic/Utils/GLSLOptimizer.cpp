//! @file     GLSLOptimizer.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLSLOptimizer Implementation
//----------------------------------------------------------------------------

GLSLOptimizer::GLSLOptimizer( )
{
	mContext	= _null;
}

GLSLOptimizer::~GLSLOptimizer( )
{
	Finalize( );
}

_ubool GLSLOptimizer::OptimizeShaderCode( AStringPtr code, glslopt_shader_type shader_type, AString& optimized_code )
{
	// Create GLSL optimizer
	glslopt_shader* shader = ::glslopt_optimize( mContext, shader_type, code.Str( ), 0 );
	if ( shader == _null )
		return _false;

	// Check the GLSL optimizer status
	if ( ::glslopt_get_status( shader ) )
	{
		// Get the optimized shader code string
		optimized_code = ::glslopt_get_output( shader );
		optimized_code.ReplaceAll( "lowp", "highp" );
		optimized_code.ReplaceAll( "mediump", "highp" );
	}
	else
	{
		optimized_code = "";

		// Get the error log if it's failed
		const _chara* err_log = ::glslopt_get_log( shader );
		if ( err_log != _null )
			ALOG_ERROR_1( "Optimize shader code failed, error log is :\n%s", err_log );
	}

	// Delete GLSL shader optimizer
	::glslopt_shader_delete( shader );

	// Check whether optimize successful
	if ( optimized_code.IsEmpty( ) )
		return _false;

	return _true;
}

_ubool GLSLOptimizer::Initialize( glslopt_target target )
{
	mContext = ::glslopt_initialize( target );
	if ( mContext == _null )
		return _false;

	return _true;
}

_void GLSLOptimizer::Finalize( )
{
	if ( mContext != _null )
	{
		::glslopt_cleanup( mContext );
		mContext = _null;
	}
}

_ubool GLSLOptimizer::OptimizeVSCode( AStringPtr code, AString& optimized_code )
{
	if ( OptimizeShaderCode( code, kGlslOptShaderVertex, optimized_code ) == _false )
		return _false;

	return _true;
}

_ubool GLSLOptimizer::OptimizePSCode( AStringPtr code, AString& optimized_code )
{
	if ( OptimizeShaderCode( code, kGlslOptShaderFragment, optimized_code ) == _false )
		return _false;

	return _true;
}
