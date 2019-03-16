//! @file     GLFramebuffer.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GLFramebuffer Implementation
//----------------------------------------------------------------------------

GLFramebuffer::GLFramebuffer( )
{
	mResource = 0;
}

GLFramebuffer::~GLFramebuffer( )
{
	// Delete FBO
	if ( mResource != 0 )
	{
		ALOG_TRACE_1( "Delete FBO(%d)", mResource );
		GL_CHECK_ERROR( __glDeleteFramebuffers( 1, &mResource ) );
	}
}

AString GLFramebuffer::DumpTextureParameters( GLenum attachment, GLuint id ) const
{
	if ( glIsTexture( id ) == GL_FALSE )
		return AString( "Not texture object" );

	int width = 0, height = 0, format = 0;

#if (_OPENGLES_ == 0)
	// Get the texture target type
	GLenum tex_target = GL_TEXTURE_2D; GLint cube_face = 0;
	GL_CHECK_ERROR( __glGetFramebufferAttachmentParameteriv( GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE, &cube_face ) );
	if ( cube_face != 0 )
		tex_target = GL_TEXTURE_CUBE_MAP;

	// Get the texture level parameter target
	GLenum tex_level_par_target = tex_target == GL_TEXTURE_2D ? GL_TEXTURE_2D : cube_face;

	// Get the texture size and format
	GLCachedBindTexture( tex_target, id );
	GL_CHECK_ERROR( __glGetTexLevelParameteriv( tex_level_par_target, 0, GL_TEXTURE_WIDTH, &width ) );
	GL_CHECK_ERROR( __glGetTexLevelParameteriv( tex_level_par_target, 0, GL_TEXTURE_HEIGHT, &height ) );
	GL_CHECK_ERROR( __glGetTexLevelParameteriv( tex_level_par_target, 0, GL_TEXTURE_INTERNAL_FORMAT, &format ) );
	GLCachedBindTexture( tex_target, 0 );
#endif
    
	return FORMAT_ASTRING_3( "%dx%d,%s", width, height, GLHelper::ConvertInternalFormat2String( format ).Str( ) );
}

AString GLFramebuffer::DumpRenderbufferParameters( GLuint id ) const
{
	if ( __glIsRenderbuffer( id ) == GL_FALSE )
		return AString( "Not render buffer object" );

	int width = 0, height = 0, format = 0;

	GL_CHECK_ERROR( __glBindRenderbuffer( GL_RENDERBUFFER, id ) );
	GL_CHECK_ERROR( __glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width ) );
	GL_CHECK_ERROR( __glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height ) );
	GL_CHECK_ERROR( __glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_INTERNAL_FORMAT, &format ) );
	GL_CHECK_ERROR( __glBindRenderbuffer( GL_RENDERBUFFER, 0 ) );

	return FORMAT_ASTRING_3( "%dx%d,%s", width, height, GLHelper::ConvertInternalFormat2String( format ).Str( ) );
}

AString GLFramebuffer::DumpAttachmentParameters( AStringPtr type_name, GLenum attachment, GLuint object_type, GLuint object_id ) const
{
	if ( object_type == GL_NONE || object_id == 0 )
		return AString( "" );

	AString dump_string;
	dump_string += FORMAT_ASTRING_2( "%s: %d\n", type_name.Str( ), object_id );

	if ( object_type == GL_TEXTURE )
		dump_string += FORMAT_ASTRING_1( "GL_TEXTURE: %s\n", DumpTextureParameters( attachment, object_id ).Str( ) );
	else if ( object_type == GL_RENDERBUFFER )
		dump_string += FORMAT_ASTRING_1( "GL_RENDERBUFFER: %s\n", DumpRenderbufferParameters( object_id ).Str( ) );

	return dump_string;
}

_ubool GLFramebuffer::Initialize( )
{
	// Generate frame buffer
	GL_CHECK_ERROR( __glGenFramebuffers( 1, &mResource ) );
	if ( mResource == 0 )
		return _false;

	// Bind the frame buffer
	Bind( );

	ALOG_TRACE_1( "Create FBO(%d)", mResource );

	return _true;
}

AString GLFramebuffer::DumpInfo( ) const
{
	AString dump_string;

	// Start to dump
	dump_string += FORMAT_ASTRING_1( "\n===== FBO(%d) STATUS =====\n", mResource );

	// Print max # of color buffers supported by FBO
	GLint max_color_attachments_number = 0;
#if (_OPENGLES_ == 1)
    max_color_attachments_number = 1;
#else
	GL_CHECK_ERROR( __glGetIntegerv( GL_MAX_COLOR_ATTACHMENTS, &max_color_attachments_number ) );
#endif
	dump_string += FORMAT_ASTRING_1( "Max Number of Color Buffer Attachment Points: %d\n", max_color_attachments_number );

	int object_type = 0, object_id = 0;

	// Print info of the color buffer attachable image
	for ( GLint i = 0; i < max_color_attachments_number; i ++ )
	{
		GLenum attachment = GL_COLOR_ATTACHMENT0 + i;

		GL_CHECK_ERROR( __glGetFramebufferAttachmentParameteriv( GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &object_type ) );
		GL_CHECK_ERROR( __glGetFramebufferAttachmentParameteriv( GL_FRAMEBUFFER, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &object_id ) );

		if ( object_type == GL_NONE || object_id == 0 )
			continue;

		dump_string += DumpAttachmentParameters( "Color attachment" + AString( ).FromValue( i, 10 ), attachment, object_type, object_id );
	}

	// Print info of the depthbuffer attachable image
	GL_CHECK_ERROR( __glGetFramebufferAttachmentParameteriv( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &object_type ) );
	if ( object_type != GL_NONE )
	{
		GL_CHECK_ERROR( __glGetFramebufferAttachmentParameteriv( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &object_id ) );

		dump_string += DumpAttachmentParameters( "Depth attachment", GL_DEPTH_ATTACHMENT, object_type, object_id );
	}

	// Print info of the stencilbuffer attachable image
	GL_CHECK_ERROR( __glGetFramebufferAttachmentParameteriv( GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &object_type ) );
	if ( object_type != GL_NONE )
	{
		GL_CHECK_ERROR( __glGetFramebufferAttachmentParameteriv( GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &object_id ) );

		dump_string += DumpAttachmentParameters( "Stencil attachment", GL_STENCIL_ATTACHMENT, object_type, object_id );
	}

	return dump_string;
}

_void GLFramebuffer::Bind( )
{
	// Clear GL cache for change FBO
	if ( mResource != gGLCachedState.mCurFBO )
	{
		EGE_DELETE( gGLCachedState.mClearColor );
		EGE_DELETE( gGLCachedState.mClearDepth );
		EGE_DELETE( gGLCachedState.mClearStencil );
	}

	GLCachedBindFBO( mResource );
}

_void GLFramebuffer::Unbind( )
{
	GLCachedBindFBO( 0 );
}

_void GLFramebuffer::AttachTexture2D( GLenum attachment, GLuint resource )
{
	Bind( );

	ALOG_TRACE_2( "Attach '%d' texture 2D to '%d' FBO", resource, mResource );

	GL_CHECK_ERROR( __glFramebufferTexture2D( GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, resource, 0 ) );
}

_void GLFramebuffer::AttachTextureCube( GLenum attachment, _dword index, GLuint resource )
{
	Bind( );

	ALOG_TRACE_3( "Attach '%d:%d' texture cube to '%d' FBO", index, resource, mResource );

	GL_CHECK_ERROR( __glFramebufferTexture2D( GL_FRAMEBUFFER, attachment, GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, resource, 0 ) );
}

_void GLFramebuffer::AttachRenderbuffer( GLenum attachment, GLuint resource )
{
	Bind( );

	ALOG_TRACE_2( "Attach '%d' render buffer to '%d' FBO", resource, mResource );

	GL_CHECK_ERROR( __glFramebufferRenderbuffer( GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, resource ) );
}