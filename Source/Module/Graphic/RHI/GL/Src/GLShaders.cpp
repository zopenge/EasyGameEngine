//! @file     GLShaders.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLDrv-Shaders Implementation
//----------------------------------------------------------------------------

PixelShaderRHIPassRef GLDrv::CreatePixelShader( AStringPtr code )
{
	if ( code.IsEmpty( ) )
		return _null;

	GLPixelShader* shader = new GLPixelShader( code );
	if ( shader->CompileShader( ) == _false )
		{ EGE_RELEASE( shader ); return _null; }

	return shader;
}

VertexShaderRHIPassRef GLDrv::CreateVertexShader( AStringPtr code )
{
	if ( code.IsEmpty( ) )
		return _null;

	GLVertexShader* shader = new GLVertexShader( code );
	if ( shader->CompileShader( ) == _false )
		{ EGE_RELEASE( shader ); return _null; }

	return shader;
}

BoundShaderRHIPassRef GLDrv::CreateBoundShader( VertexShaderRHI* vertexshader, PixelShaderRHI* pixelshader )
{
	GLBoundShader* bound_shader = new GLBoundShader( vertexshader, pixelshader );
	if ( bound_shader->Initialize( ) == _false )
		{ EGE_RELEASE( bound_shader ); return _null; }

	return bound_shader;
}

PixelShaderRHI* GLDrv::GetPixelShader( BoundShaderRHI* shader ) 
{
	DYNAMIC_CAST_GLRESOURCE( BoundShader, shader );

	return gl_shader->GetPixelShader( );
}

VertexShaderRHI* GLDrv::GetVertexShader( BoundShaderRHI* shader ) 
{
	DYNAMIC_CAST_GLRESOURCE( BoundShader, shader );

	return gl_shader->GetVertexShader( );
}

const AStringObj& GLDrv::GetPixelShaderCode( BoundShaderRHI* shader )
{
	DYNAMIC_CAST_GLRESOURCE( BoundShader, shader );

	return gl_shader->GetPixelShader( )->GetCode( );
}

const AStringObj& GLDrv::GetVertexShaderCode( BoundShaderRHI* shader )
{
	DYNAMIC_CAST_GLRESOURCE( BoundShader, shader );

	return gl_shader->GetVertexShader( )->GetCode( );
}

_dword GLDrv::GetShaderResourceID( const BoundShaderRHI* shader ) const
{
	DYNAMIC_CAST_GLRESOURCE_CONST( BoundShader, shader );

	return gl_shader->GetShaderResourceID( );
}

_dword GLDrv::GetUniformBufferLocation( BoundShaderRHI* shader, AStringPtr name )
{
	DYNAMIC_CAST_GLRESOURCE( BoundShader, shader );

	return gl_shader->GetUniformLocation( name );
}

_dword GLDrv::ActiveUniformBuffer( BoundShaderRHI* shader, _UNIFORM_BUFFER_DATA_TYPE type, const AStringObj& name, _dword size )
{
	DYNAMIC_CAST_GLRESOURCE( BoundShader, shader );

	return gl_shader->ActiveUniformBuffer( type, name, size );
}

_ubool GLDrv::UpdateUniformBuffer( BoundShaderRHI* shader, _dword location, const _void* buffer, _dword size )
{
	DYNAMIC_CAST_GLRESOURCE( BoundShader, shader );

	return gl_shader->UpdateUniformBuffer( location, buffer, size );
}

_ubool GLDrv::SetUniformPropertyValue( BoundShaderRHI* shader, AStringPtr name, _int value )
{
	DYNAMIC_CAST_GLRESOURCE( BoundShader, shader );

	return gl_shader->SetUniformPropertyValue( name, value );
}

//----------------------------------------------------------------------------
// GLBoundShader Implementation
//----------------------------------------------------------------------------

GLBoundShader::GLBoundShader( VertexShaderRHI* vs, PixelShaderRHI* ps )
{
	EGE_ASSERT( vs != _null );
	EGE_ASSERT( ps != _null );

	mGLSLProgram	= _null;

	mVertexShader	= (GLVertexShader*) vs;
	mPixelShader	= (GLPixelShader*) ps;

	GetResourceManagerRHI( )->CreateShader( this );
}

GLBoundShader::~GLBoundShader( )
{
	DeleteShader( );

	GetResourceManagerRHI( )->RemoveShader( this );
}

_ubool GLBoundShader::IsNeedUpdateUniformBuffer( _dword location, const _void* buffer, _dword size )
{
	MemArrayPtr< _byte >& latest_uniform_buffer = mUniformBuffers[ location ].mBuffer;
	if ( latest_uniform_buffer.SizeOfBytes( ) < size )
	{
		latest_uniform_buffer.Create( size, (const _byte*) buffer );
		return _true;
	}

	if ( EGE_MEM_CMP( latest_uniform_buffer, buffer, size ) != 0 )
	{
		EGE_MEM_CPY( latest_uniform_buffer, buffer, size );
		return _true;
	}

	return _false;
}

_ubool GLBoundShader::Initialize( )
{
	// Clear current uniform buffers data
	for ( _dword i = 0; i < mUniformBuffers.Number( ); i ++ )
		mUniformBuffers[i].mBuffer.Clear( );

	// Compile VS and PS
	if ( mVertexShader->CompileShader( ) == _false || mPixelShader->CompileShader( ) == _false )
		return _false;

	// Create GLSL program
	mGLSLProgram = new GLSLProgram( );
	if ( mGLSLProgram->Link( mVertexShader, mPixelShader ) == _false )
	{
		EGE_RELEASE( mGLSLProgram );
		return _false;
	}

	return _true;
}

_dword GLBoundShader::GetShaderResourceID( ) const
{
	return mGLSLProgram->GetProgramResource( );
}

_void GLBoundShader::DeleteShader( )
{
	// Release GLSL program
	EGE_RELEASE( mGLSLProgram );
}

_void GLBoundShader::Bind( )
{
	if ( mGLSLProgram == _null )
		Initialize( );

	mGLSLProgram->Bind( );
}

_dword GLBoundShader::GetUniformLocation( AStringPtr name ) const
{
	// Locate the uniform buffer
	return mGLSLProgram->GetUniformLocation( name );
}

_dword GLBoundShader::ActiveUniformBuffer( _UNIFORM_BUFFER_DATA_TYPE type, const AStringObj& name, _dword size )
{
	// Check the duplicate active operation
	UniformBufferInfoArray::Iterator it = mUniformBuffers.Search( name );
	if ( it.IsValid( ) )
		return it.mIndex;

	// Locate the uniform buffer
	_dword location = GetUniformLocation( name );
	if ( location == -1 )
		return -1;

	// Build uniform buffer
	UniformBufferInfo uniform_buffer;
	uniform_buffer.mType		= type;
	uniform_buffer.mLocation	= location;
	uniform_buffer.mSize		= size;
	uniform_buffer.mName		= G_STROBJ( name );

	// Append it
	_dword index = mUniformBuffers.Append( uniform_buffer );
	return index;
}

_ubool GLBoundShader::UpdateUniformBuffer( _dword location, const _void* buffer, _dword size )
{
	// The uniform buffer must be initialized
	EGE_ASSERT( location != -1 );

	// Get the uniform buffer info
	const UniformBufferInfo& uniform_buffer = mUniformBuffers[ location ];

	// Check the uniform buffer size bounds
	EGE_ASSERT( size <= uniform_buffer.mSize );
	if ( IsNeedUpdateUniformBuffer( location, buffer, size ) == _false )
		return _true; // Skip to update by the same buffer data

	// Update the uniform buffer
	switch ( uniform_buffer.mType )
	{
		case _UBDT_BOOL:
		case _UBDT_LONG:
			GL_CHECK_ERROR( __glUniform1i( uniform_buffer.mLocation, *(const GLint*) buffer ) );
			break;

		case _UBDT_VEC1:
			GL_CHECK_ERROR( __glUniform1fv( uniform_buffer.mLocation, size / sizeof( _float ), (const _float*) buffer ) );
			break;

		case _UBDT_VEC2:
			GL_CHECK_ERROR( __glUniform2fv( uniform_buffer.mLocation, size / (sizeof( _float ) * 2), (const _float*) buffer ) );
			break;

		case _UBDT_VEC3:
			GL_CHECK_ERROR( __glUniform3fv( uniform_buffer.mLocation, size / (sizeof( _float ) * 3), (const _float*) buffer ) );
			break;

		case _UBDT_VEC4:
			GL_CHECK_ERROR( __glUniform4fv( uniform_buffer.mLocation, size / (sizeof( _float ) * 4), (const _float*) buffer ) );
			break;

		case _UBDT_MATRIX_3x3:
			GL_CHECK_ERROR( __glUniformMatrix3fv( uniform_buffer.mLocation, size / sizeof( Matrix3 ), GL_FALSE, (const _float*) buffer ) );
			break;

		case _UBDT_MATRIX_4x4:
			GL_CHECK_ERROR( __glUniformMatrix4fv( uniform_buffer.mLocation, size / sizeof( Matrix4 ), GL_FALSE, (const _float*) buffer ) );
			break;

		case _UBDT_BUFFER:
			GL_CHECK_ERROR( __glUniform1fv( uniform_buffer.mLocation, size, (const _float*) buffer ) );
			break;

		default:
			EGE_ASSERT( 0 );
			break;
	}

	return _true;
}

_ubool GLBoundShader::SetUniformPropertyValue( AStringPtr name, _int value )
{
	// Get the location of uniform variable
	GLint location = mGLSLProgram->GetUniformLocation( name );
	if ( location == -1 )
		return _false;

	GL_CHECK_ERROR( __glUniform1i( location, value ) );

	return _true;
}
