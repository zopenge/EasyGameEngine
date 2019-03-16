//! @file     GLVertexArray.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLDrv-VertexArray Implementation
//----------------------------------------------------------------------------

VertexArrayRHIPassRef GLDrv::CreateVertexArray( )
{
	if ( gGLSupportVAO )
		return new GLVertexArray( );
	else
		return new GLSoftwareVertexArray( );
}

_void GLDrv::BindVertexArray( VertexArrayRHI* vertex_array )
{
	DYNAMIC_CAST_GLRESOURCE( VertexArrayBase, vertex_array );

	gGLCachedState.mPendingVAO = vertex_array;

	gl_vertex_array->Bind( );
}

_void GLDrv::UnbindVertexArray( )
{
	GLVertexArrayBase* vertex_array = static_cast< GLVertexArrayBase* >( gGLCachedState.mPendingVAO );
	EGE_ASSERT( vertex_array != _null );

	vertex_array->Unbind( );
}

_ubool GLDrv::SetVertexArrayDecl( VertexArrayRHI* vertex_array, VertexDeclarationRHI* declaration, VertexBufferRHI* vbo, IndexBufferRHI* ibo )
{
	DYNAMIC_CAST_GLRESOURCE( VertexArrayBase, vertex_array );

	return gl_vertex_array->Setup( declaration, vbo, ibo );
}

_dword GLDrv::GetVertexArrayResID( VertexArrayRHI* vertex_array )
{
	DYNAMIC_CAST_GLRESOURCE( VertexArrayBase, vertex_array );

	return gl_vertex_array->GetResID( );
}

//----------------------------------------------------------------------------
// GLVertexArray Implementation
//----------------------------------------------------------------------------

GLVertexArray::GLVertexArray( )
{
	mVAOResource = 0;
	mVBOResource = _null;
	mIBOResource = _null;

	GL_CHECK_ERROR( __glGenVertexArraysOES( 1, &mVAOResource ) );
	WLOG_TRACE_1( L"Create VAO(%d)", mVAOResource );

	GetResourceManagerRHI( )->CreateVAOResource( this );
}

GLVertexArray::~GLVertexArray( )
{
	DeleteVAO( );

	GetResourceManagerRHI( )->RemoveVAOResource( this );
}

_ubool GLVertexArray::Setup( )
{
	// Get the stride of vertex in bytes
	_dword stride = mDeclaration->GetStride( );
	EGE_ASSERT( stride != 0 );

	// Set vertex declaration of VAO
	for ( _dword i = 0; i < mDeclaration->GetVertexElements( ).Number( ); i ++ )
	{
		const GLVertexElement& element = mDeclaration->GetVertexElements( )[i];

		GL_CHECK_ERROR( __glEnableVertexAttribArray( element.mUsage ) );
		GL_CHECK_ERROR( __glVertexAttribPointer( element.mUsage, element.mStride, element.mType, (GLboolean) element.mNormalized, stride, EGE_BUFFER_OFFSET( element.mOffset ) ) ); 
	}

	return _true;
}

_ubool GLVertexArray::ResetVAO( )
{
	GL_CHECK_ERROR( __glGenVertexArraysOES( 1, &mVAOResource ) );
	WLOG_TRACE_1( L"Create VAO(%d)", mVAOResource );

	GLCachedBindVAO( mVAOResource );

	mVBOResource->Bind( );
	mIBOResource->Bind( );

	Setup( );

	GLCachedBindVAO( 0 );

	return _true;
}

_void GLVertexArray::DeleteVAO( )
{
	if ( mVAOResource != 0 )
	{
		OnVAODeletion( mVAOResource );

		WLOG_TRACE_1( L"Delete VAO(%d)", mVAOResource );
		GL_CHECK_ERROR( __glDeleteVertexArraysOES( 1, &mVAOResource ) );

		mVAOResource = 0;
	}
}

_void GLVertexArray::Bind( )
{
	GLCachedBindVAO( mVAOResource );
}

_void GLVertexArray::Unbind( )
{
	GLCachedBindVAO( 0 );
}

_ubool GLVertexArray::Setup( VertexDeclarationRHI* declaration, VertexBufferRHI* vbo, IndexBufferRHI* ibo )
{
	DYNAMIC_CAST_GLRESOURCE( VertexDeclaration, declaration );
	DYNAMIC_CAST_GLRESOURCE( VertexBuffer, vbo );
	DYNAMIC_CAST_GLRESOURCE( IndexBuffer, ibo );

	mDeclaration = gl_declaration;
	mVBOResource = gl_vbo;
	mIBOResource = gl_ibo;

	Setup( );

	return _true;
}

_dword GLVertexArray::GetResID( ) const
{
	return mVAOResource;
}

//----------------------------------------------------------------------------
// GLSoftwareVertexArray Implementation
//----------------------------------------------------------------------------

GLSoftwareVertexArray::GLSoftwareVertexArray( )
{
	static _dword sResID = 1;
	mResID = sResID ++;
}

GLSoftwareVertexArray::~GLSoftwareVertexArray( )
{
	// Clear the current binding VAO if it's the same
	if ( gGLCachedState.mCurVAO == mResID )
		gGLCachedState.mCurVAO = 0;
}

_void GLSoftwareVertexArray::EnableVertexElement( const GLVertexElement& element, GLsizei stride, GLuint vbo )
{
	GLVertexAttributeCache& vertex_attribute = gGLCachedState.mVertexAttributeCache[ element.mUsage ];

	// Enable the VAO
	if ( !vertex_attribute.mIsEnabled )
	{
		GL_CHECK_ERROR( __glEnableVertexAttribArray( element.mUsage ) );

		vertex_attribute.mIsEnabled = _true;
	}

	// Set the VAO info
	if ( (vertex_attribute.mVBO != vbo ) ||
		(vertex_attribute.mType != element.mType) ||
		(vertex_attribute.mUsage != element.mUsage) ||
		(vertex_attribute.mOffset != element.mOffset) ||
		(vertex_attribute.mStride != element.mStride) ||
		(vertex_attribute.mNormalized != element.mNormalized) )
	{
		// Set the VAO
		GL_CHECK_ERROR( __glVertexAttribPointer( element.mUsage, element.mStride, element.mType, 
			(GLboolean) element.mNormalized, stride, EGE_BUFFER_OFFSET( element.mOffset ) ) ); 

		// Update the VAO cache
		vertex_attribute.mVBO			= vbo;
		vertex_attribute.mType			= (_word)element.mType;
		vertex_attribute.mUsage			= element.mUsage;
		vertex_attribute.mOffset		= element.mOffset;
		vertex_attribute.mStride		= element.mStride;
		vertex_attribute.mNormalized	= EGE_BOOLEAN( element.mNormalized );
	}
}

_void GLSoftwareVertexArray::SetupVBO( )
{
	// Get the vertex buffer object
	GLVertexBuffer* vbo = mVBO.cast_static< GLVertexBuffer >( );
	EGE_ASSERT( vbo != _null );

	// Get the resource ID of VB
	_dword vb_res_id = vbo->GetResource( );

	// Bind the vertex buffer
	GLCachedBindVBO( vb_res_id );

	// Skip to setup the same VAO
	if ( gGLCachedState.mCurVAO == mResID )
		return;

	// Get the stride of VB
	_dword vb_stride = vbo->GetStride( );

	// The enabled vertex element usage index
	// [Attention] Do not use the boolean type, because the compiler seems only initialize the first element in initializer.
	// So we use the 32 bits unsigned integer here.
	_dword used_vertex_arrays[ _GL_ATTRI_MAXNUMBER ] = {0};

	// Get the vertex declaration object
	GLVertexDeclaration* vertex_decl = mVertexDecl.cast_static< GLVertexDeclaration >( );
	EGE_ASSERT( vertex_decl != _null );

	// Get the vertex elements
	const GLVertexElementArray& vertex_elements = vertex_decl->GetVertexElements( );

	// Enable vertex elements
	for ( _dword i = 0; i < vertex_elements.Number( ); i ++ )
	{
		const GLVertexElement& vc_element = vertex_elements[i];

		EnableVertexElement( vc_element, vb_stride, vb_res_id );
		used_vertex_arrays[ vc_element.mUsage ] = _true;
	}

	// Disable remaining vertex arrays
	for ( _dword i = 0; i < _GL_ATTRI_MAXNUMBER; i ++ )
	{
		GLVertexAttributeCache& vertex_attribute = gGLCachedState.mVertexAttributeCache[i];

		if ( used_vertex_arrays[i] == _false && vertex_attribute.mIsEnabled )
		{
			GL_CHECK_ERROR( __glDisableVertexAttribArray( i ) );
			vertex_attribute.mIsEnabled = _false;
		}
	}
}

_void GLSoftwareVertexArray::SetupIBO( )
{
	GLIndexBuffer* ibo = mIBO.cast_static< GLIndexBuffer >( );
	EGE_ASSERT( ibo != _null );

	GLCachedBindIBO( ibo->GetResource( ) );
}

_void GLSoftwareVertexArray::Bind( )
{
	if ( mVertexDecl.IsNull( ) )
		return;

	SetupVBO( );
	SetupIBO( );

	// Update the current VAO resource ID
	gGLCachedState.mCurVAO = mResID;
}

_void GLSoftwareVertexArray::Unbind( )
{
	mVBO = gGLCachedState.mPendingVBO;
	mIBO = gGLCachedState.mPendingIBO;

	gGLCachedState.mPendingVBO = _null;
	gGLCachedState.mPendingIBO = _null;
}

_ubool GLSoftwareVertexArray::Setup( VertexDeclarationRHI* declaration, VertexBufferRHI* vbo, IndexBufferRHI* ibo )
{
	mVertexDecl = declaration;

	return _true;
}

_dword GLSoftwareVertexArray::GetResID( ) const
{
	return mResID;
}