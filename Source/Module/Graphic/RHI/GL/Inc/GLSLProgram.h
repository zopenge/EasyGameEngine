//! @file     GLSLProgram.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GLSLProgram
//----------------------------------------------------------------------------

class GLSLProgram : public TObject< IObject >
{
private:
	typedef RefPtr< GLVertexShader > GLVertexShaderRef;
	typedef RefPtr< GLPixelShader > GLPixelShaderRef;

private:
	//!	The GLSL program resource
	GLuint				mProgramResource;

	//!	The vertex shader resource
	GLVertexShaderRef	mVertexShader;
	//!	The pixel shader resource
	GLPixelShaderRef	mPixelShader;

private:
	//!	Set attributs.
	_void SetAttributes( );

public:
	GLSLProgram( );
	virtual ~GLSLProgram( );

public:
	//!	Get the GLSL program resource.
	EGE_GET_ACCESSOR_CONST( GLuint, ProgramResource )
	//!	Get the vertex shader resource.
	EGE_GET_ACCESSOR( GLVertexShader*, VertexShader )
	//!	Get the pixel shader resource.
	EGE_GET_ACCESSOR( GLPixelShader*, PixelShader )

public:
	//!	Link GLSL program.
	_ubool Link( GLVertexShader* vertexshader, GLPixelShader* pixelshader );

	//!	Bind.
	_void Bind( );

	//! Get the uniform location.
	GLint GetUniformLocation( AStringPtr name );
};

//----------------------------------------------------------------------------
// GLSLProgram Implementation
//----------------------------------------------------------------------------

}