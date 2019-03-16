//! @file     GLPlatformANDROID.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

_handle CreateGLContext( _handle app_handle )
{
	MemPtr< GLESContext > gles_context( new GLESContext( ) );

	// Create EGL context
	if ( gles_context->Create( app_handle ) == _false )
		return _null;

	// Check GL features
	if ( CheckGLFeatures( ) == _false )
		return _null;

	// Initialize pixel formats
	GLHelper::InitPixelFormats( );

	WLOG_TRACE_1( L"Create Android GL context:0x%.16llx", (_qword) gles_context.GetPointer( ) );

	// Create EGL handle successful, so we skip to delete it
	gles_context.EnableAutoDelete( _false );

	return gles_context;
}

_void ReleaseGLContext( _handle context )
{
	GLESContext* gles_context = (GLESContext*) context;
	EGE_ASSERT( gles_context != _null );

	WLOG_TRACE_1( L"Release Android GL context:0x%.16llx", (_qword) context );

	EGE_DELETE( gles_context );
}

_ubool MakeCurrentGLContext( _handle context )
{
	GLESContext* gles_context = (GLESContext*) context;
	EGE_ASSERT( gles_context != _null );

	return gles_context->MakeCurrentGLContext( );
}

_ubool ShareGLContext( _handle context_1, _handle context_2 )
{
	// EGL does not support for this operation
	return _false;
}

_dword GetGLContextNumber( )
{
	return 1;
}

_void FlushGLBuffers( _handle context )
{
	GLESContext* gles_context = (GLESContext*) context;
	EGE_ASSERT( gles_context != _null );

	gles_context->FlushGLBuffers( );
}

_void SetVRRenderTargetTexID( _handle context, _dword index, _dword tex_id, const PointU& tex_size )
{
}

PointU GetVRTextureSize( _handle context, _dword index )
{
	GLESContext* gles_context = (GLESContext*) context;
	EGE_ASSERT( gles_context != _null );

#if (_ENABLE_VR_SOFTWARE == 1)
	static PointU size( _VR_EMULATOR_RENDER_TARGET_WIDTH, _VR_EMULATOR_RENDER_TARGET_HEIGHT );
	return size;
#else
	return PointU::cZeroPoint;
#endif
}

VREyeRHI GetVREyeInfo( _handle context, _dword index )
{
	GLESContext* gles_context = (GLESContext*) context;
	EGE_ASSERT( gles_context != _null );

#if (_ENABLE_VR_SOFTWARE == 1)
	static VREyeRHI	sGraphicOVREyeInfo[2];
	static PointU	sPrevSize[2] = { PointU::cZeroPoint, PointU::cZeroPoint };

	// Get the client size
	PointU size = GetMainViewBasedApp( )->GetClientSize( );
	if ( sPrevSize[ index ] != size )
	{
		// Update previous size
		sPrevSize[ index ] = size;

		// Get the eye default height
		_float eye_height	= 1.675f;

		// Get the ratio and fov-Y, fov-X
		_float ratio	= EGE_RATIO( size.x / 2.0f, size.y );
		_float fov_y	= Math::Degree2Radian( 45.0f );
		_float fov_x	= ratio * fov_y;
		_float u_d_tan	= Math::Tan( fov_y / 2.0f );
		_float l_r_tan	= Math::Tan( fov_x / 2.0f );

		// Update the eye info
		sGraphicOVREyeInfo[index].mHeight					= eye_height;
		sGraphicOVREyeInfo[index].mDefaultEyeFov.mUpTan		= u_d_tan;
		sGraphicOVREyeInfo[index].mDefaultEyeFov.mDownTan	= u_d_tan;
		sGraphicOVREyeInfo[index].mDefaultEyeFov.mLeftTan	= l_r_tan;
		sGraphicOVREyeInfo[index].mDefaultEyeFov.mRightTan	= l_r_tan;
	}

	return sGraphicOVREyeInfo[index];
#else
	static VREyeRHI sGraphicOVREyeInfo;
	return sGraphicOVREyeInfo;
#endif
}