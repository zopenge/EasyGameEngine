//! @file     GLSLProgram.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLSLProgram Implementation
//----------------------------------------------------------------------------

GLSLProgram::GLSLProgram( )
{
	mProgramResource = 0;
}

GLSLProgram::~GLSLProgram( )
{
	if ( mProgramResource != 0 )
	{
		// Delete GLSL program
		WLOG_TRACE_1( L"Delete (%d) GLSL program", (_dword) mProgramResource );
		GL_CHECK_ERROR( __glDeleteProgram( mProgramResource ) );
	}
}

_void GLSLProgram::SetAttributes( )
{
	// GLSL attributes name table
	static const GLchar* sNameTable[ _GL_ATTRI_MAXNUMBER ] = 
	{
		"cPosition",
		"cColor0",
		"cColor1",
		"cNormal",
		"cBlendWeight",
		"cBlendIndices",
		"cTexCoords0",
		"cTexCoords1",
		"cTangent",
	};

	// Get VS code
	AStringPtr vs_code = mVertexShader->GetCode( ).Str( );

	// Locate at the attributes section
	_dword	func_section_index = vs_code.SearchL2R( "{" );
	AString	attributes_section( vs_code.Str( ), func_section_index );

	// Bind GLSL attributes
	for ( _dword i = 0; i < _GL_ATTRI_MAXNUMBER; i ++ )
	{
		const GLchar* name = sNameTable[i];
		EGE_ASSERT( name != _null );

		if ( attributes_section.SearchL2R( name, _false ) == -1 )
			continue;

		GL_CHECK_ERROR( __glBindAttribLocation( mProgramResource, i, name ) );
	}
}

_ubool GLSLProgram::Link( GLVertexShader* vertexshader, GLPixelShader* pixelshader )
{
	mVertexShader	= vertexshader;
	mPixelShader	= pixelshader;

	// Create GLSL program resource
	mProgramResource = __glCreateProgram( );
	EGE_ASSERT( mProgramResource != 0 );

	ALOG_TRACE_1( "Create GLSL program (%d)", mProgramResource );

	// Get the shader resource ID
	GLuint vs_res_id = mVertexShader->GetResource( );
	GLuint ps_res_id = mPixelShader->GetResource( );

	// Attach GLSL shaders
	GL_CHECK_ERROR( __glAttachShader( mProgramResource, vs_res_id ) );
	GL_CHECK_ERROR( __glAttachShader( mProgramResource, ps_res_id ) );

	// Set attributes
	SetAttributes( );

	// Link GLSL program
	GL_CHECK_ERROR( __glLinkProgram( mProgramResource ) );

	// Bind the GLSL shader for set texture slots
	GLCachedBindProgram( mProgramResource );

	// Check GLSL program
	if ( GL_CHECK_PROGRAM( mProgramResource ) == _false )
	{
		// Get VS and PS code
		AStringPtr vs_code = mVertexShader->GetCode( ).Str( );
		AStringPtr ps_code = mPixelShader->GetCode( ).Str( );

		ALOG_ERROR_5( "Attach VS(%d), PS(%d) to GLSL(%d) failed\n"
			"==============================\n"
			"VS:\n%s\n"
			"PS:\n%s\n"
			"==============================\n",
			vs_res_id, ps_res_id, mProgramResource,
			vs_code.Str( ),
			ps_code.Str( ) );

		return _false;
	}

	ALOG_TRACE_3( "Attach VS(%d), PS(%d) to GLSL(%d) OK", vs_res_id, ps_res_id, mProgramResource );

	return _true;
}

_void GLSLProgram::Bind( )
{
	GLCachedBindProgram( mProgramResource );
}

GLint GLSLProgram::GetUniformLocation( AStringPtr name )
{
	return __glGetUniformLocation( mProgramResource, name.Str( ) );
}