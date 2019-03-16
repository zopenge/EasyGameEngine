//! @file     GLSLOptimizer.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GLSLOptimizer
//----------------------------------------------------------------------------

class GLSLOptimizer
{
	SINGLETON( GLSLOptimizer )

private:
	glslopt_ctx*	mContext;

private:
	//! Optimize shader code.
	_ubool OptimizeShaderCode( AStringPtr code, glslopt_shader_type shader_type, AString& optimized_code );

public:
	//!	Initialize.
	//!	@param		target			The GLSL target.
	//!	@return		True indicates success false indicates failure.
	_ubool Initialize( glslopt_target target );
	//!	Finalize.
	//!	@param		none.
	//!	@return		none.
	_void Finalize( );

	//! Optimize VS code.
	//!	@param		code			The shader code.
	//!	@param		optimized_code	The optimized code.
	//!	@return		True indicates success false indicates failure.
	_ubool OptimizeVSCode( AStringPtr code, AString& optimized_code );
	//! Optimize PS code.
	//!	@param		code			The shader code.
	//!	@param		optimized_code	The optimized code.
	//!	@return		True indicates success false indicates failure.
	_ubool OptimizePSCode( AStringPtr code, AString& optimized_code );
};

//----------------------------------------------------------------------------
// GLSLOptimizer Implementation
//----------------------------------------------------------------------------

}