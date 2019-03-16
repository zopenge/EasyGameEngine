//! @file     GLViewport.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GLViewport
//----------------------------------------------------------------------------

class GLViewport : public ViewportRHI
{
private:
	//!	The GL context
	GLContext*	mGLContext;
	//! The size of the viewport
	PointU		mSize;

public:
	GLViewport( );
	virtual ~GLViewport( );

public:
	//!	Get the GL context.
	EGE_GET_ACCESSOR_CONST( GLContext*, GLContext )
	//!	Get the viewport size.
	EGE_GET_ACCESSOR_CONST( const PointU&, Size )

public:
	//!	Initialize.
	_ubool Initialize( _handle app_handle, const PointU& size );
	//!	Reset.
	_ubool Reset( );
	//!	Unload.
	_void Unload( );

	//!	Get the size.
	_dword GetWidth( ) const;
	_dword GetHeight( ) const;

	//!	Resize.
	_ubool Resize( const PointU& size );

	//!	Present.
	_void Present( );
};

}