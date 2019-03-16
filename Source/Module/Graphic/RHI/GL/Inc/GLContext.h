//! @file     GLContext.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

class GLDrv;

//----------------------------------------------------------------------------
// GLContext
//----------------------------------------------------------------------------

class GLContext
{
private:
	//!	The context handle.
	struct Handle;
	Handle*	mHandle;

public:
	GLContext( );
	~GLContext( );

public:
	//!	Initialize/Finalize.
	_ubool Initialize( _handle app_handle );
	_void Finalize( );

	//!	Get the GL context.
	_handle GetContext( ) const;

	//!	Bind.
	_void Bind( );
	//!	Present.
	_void Present( );

	//!	VR device.
	_void SetVRRenderTargetTexID( _dword index, _dword tex_id, const PointU& tex_size );
	PointU GetVRTextureSize( _dword index ) const;
	VREyeRHI GetVREyeInfo( _dword index ) const;
};

}