//! @file     GLFramebuffer.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GLFramebuffer
//----------------------------------------------------------------------------

class GLFramebuffer
{
private:
	//!	The frame buffer resource
	GLuint	mResource;

private:
	//!	Dump texture/render buffer parameters.
	AString DumpTextureParameters( GLenum attachment, GLuint id ) const;
	AString DumpRenderbufferParameters( GLuint id ) const;
	//!	Dump attachment parameters.
	AString DumpAttachmentParameters( AStringPtr type_name, GLenum attachment, GLuint object_type, GLuint object_id ) const;

public:
	GLFramebuffer( );
	~GLFramebuffer( );

public:
	//!	Get the frame buffer resource.
	EGE_GET_ACCESSOR_CONST( GLuint, Resource )

public:
	//!	Initialize.
	_ubool Initialize( );

	//!	Dump frame buffer info.
	AString DumpInfo( ) const;

	//!	Bind/Unbind frame buffer.
	_void Bind( );
	_void Unbind( );

	//!	Attach texture 2D.
	_void AttachTexture2D( GLenum attachment, GLuint resource );
	//!	Attach texture cube.
	_void AttachTextureCube( GLenum attachment, _dword index, GLuint resource );
	//!	Attach render buffer.
	_void AttachRenderbuffer( GLenum attachment, GLuint resource );
};

}