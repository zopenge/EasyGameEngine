//! @file     GLInfo.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLInfo Implementation
//----------------------------------------------------------------------------

GLInfo::GLInfo( )
{
}

GLInfo::~GLInfo( )
{
}

_void GLInfo::InitShaderInfo( )
{
	// Start to get OpenGL capacity
	// http://www.khronos.org/opengles/sdk/docs/man/xhtml/glGet.xml
	// We do not check GL error here, because the virtual machine will failed to raise an error even though it's succeed
	__glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, (GLint*)&mShaderInfo.mMaxTexturesUnitNumber );
	__glGetIntegerv( GL_MAX_VARYING_VECTORS, (GLint*)&mShaderInfo.mMaxVaryingVectorsNumber );
	__glGetIntegerv( GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, (GLint*) &mShaderInfo.mMaxVertexTextureImageUnitsNumber );
	__glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, (GLint*) &mShaderInfo.mMaxCombinedTextureImageUnitsNumber );

	// Get the vertex shader configure info
	GPUVertexShaderInfoRHI& vs = mShaderInfo.mVSInfo;
	__glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, (GLint*) &vs.mMaxAttributesNumber );
	__glGetIntegerv( GL_MAX_VERTEX_UNIFORM_VECTORS, (GLint*) &vs.mMaxVectorsUniformNumber );

	// Get the pixel shader configure info
	GPUPixelShaderInfoRHI& ps = mShaderInfo.mPSInfo;
	__glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_VECTORS, (GLint*) &ps.mMaxVectorsUniformNumber );

	// Fix the GL device info, sometimes the video card driver give the error info to us
	#define CHECK_DEFAULT_VALUE( attri_name, default_value ) if ( mShaderInfo.m##attri_name == 0 ) { ALOG_TRACE_2( "Fix '%s' attribute to default value (%d)", (const _chara*) #attri_name, default_value ); mShaderInfo.m##attri_name = default_value; }
	#define CHECK_VS_DEFAULT_VALUE( attri_name, default_value ) if ( vs.m##attri_name == 0 ) { ALOG_TRACE_2( "Fix VS '%s' attribute to default value (%d)", (const _chara*) #attri_name, default_value ); vs.m##attri_name = default_value; }
	#define CHECK_PS_DEFAULT_VALUE( attri_name, default_value ) if ( ps.m##attri_name == 0 ) { ALOG_TRACE_2( "Fix PS '%s' attribute to default value (%d)", (const _chara*) #attri_name, default_value ); ps.m##attri_name = default_value; }
	CHECK_DEFAULT_VALUE( MaxTexturesUnitNumber, 4 )
	CHECK_DEFAULT_VALUE( MaxVaryingVectorsNumber, 8 )
	CHECK_DEFAULT_VALUE( MaxVertexTextureImageUnitsNumber, 0 )
	CHECK_DEFAULT_VALUE( MaxCombinedTextureImageUnitsNumber, 8 )
	CHECK_VS_DEFAULT_VALUE( MaxAttributesNumber, 8 )
	CHECK_VS_DEFAULT_VALUE( MaxVectorsUniformNumber, 256 )
	CHECK_PS_DEFAULT_VALUE( MaxVectorsUniformNumber, 256 )

	// Build the GLSL info string
	AString info;
	info += "GLSL Shader Info:\n";
	info += FORMAT_ASTRING_1( "	GL_MAX_TEXTURE_IMAGE_UNITS: %d\n", mShaderInfo.mMaxTexturesUnitNumber );
	info += FORMAT_ASTRING_1( "	GL_MAX_VARYING_VECTORS: %d\n", mShaderInfo.mMaxVaryingVectorsNumber );
	info += FORMAT_ASTRING_1( "	GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS: %d\n", mShaderInfo.mMaxVertexTextureImageUnitsNumber );
	info += FORMAT_ASTRING_1( "	GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS: %d\n", mShaderInfo.mMaxCombinedTextureImageUnitsNumber );
	info += "VS:\n";
	info += FORMAT_ASTRING_1( "	GL_MAX_VERTEX_ATTRIBS: %d\n", vs.mMaxAttributesNumber );
	info += FORMAT_ASTRING_1( "	GL_MAX_VERTEX_UNIFORM_VECTORS: %d\n", vs.mMaxVectorsUniformNumber );
	info += "PS:\n";
	info += FORMAT_ASTRING_1( "	GL_MAX_VERTEX_UNIFORM_VECTORS: %d\n", ps.mMaxVectorsUniformNumber );
	info += "GS:\n";
	info += "\n";

	// Output GLSL state info
	ALOG_TRACE( info );

	// Clear the GL error status, because the error code will save in virtual machine mode
	__glGetError( );
}

_void GLInfo::InitTextureInfo( )
{
	// Query texture info
	__glGetIntegerv( GL_MAX_TEXTURE_SIZE, (GLint*) &mTextureInfo.mMaxTextureSize );

	// Build the texture info string
	AString info;
	info += "Texture Info:\n";
	info += FORMAT_ASTRING_1( "	GL_MAX_TEXTURE_SIZE: %d\n", mTextureInfo.mMaxTextureSize );
	info += "\n";

	// Output texture state info
	ALOG_TRACE( info );

	// Clear the GL error status, because the error code will save in virtual machine mode
	__glGetError( );
}

_void GLInfo::Initialize( )
{
	InitShaderInfo( );
	InitTextureInfo( );
}