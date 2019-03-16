//! @file     NSViewBasedApp.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

//----------------------------------------------------------------------------
// NS-ViewBasedApp
//----------------------------------------------------------------------------

EGE_EXTERN_DLL_OUT_FUNC EGE::_handle	NSViewBasedApp_GetCAEAGLLayer( EGE::_handle app );

EGE_EXTERN_DLL_OUT_FUNC EGE::_void 		NSViewBasedApp_Show( EGE::_handle app );
EGE_EXTERN_DLL_OUT_FUNC EGE::_void 		NSViewBasedApp_Hide( EGE::_handle app );

EGE_EXTERN_DLL_OUT_FUNC EGE::_void 		NSViewBasedApp_Center( EGE::_handle app );

EGE_EXTERN_DLL_OUT_FUNC EGE::_void 		NSViewBasedApp_SetPos( EGE::_handle app, EGE::_dword x, EGE::_dword y );
EGE_EXTERN_DLL_OUT_FUNC EGE::_void 		NSViewBasedApp_SetSize( EGE::_handle app, EGE::_dword width, EGE::_dword height );
EGE_EXTERN_DLL_OUT_FUNC EGE::PointU		NSViewBasedApp_GetSize( EGE::_handle app );
EGE_EXTERN_DLL_OUT_FUNC EGE::_void 		NSViewBasedApp_GetRect( EGE::_handle app, EGE::RectI& rect );
EGE_EXTERN_DLL_OUT_FUNC EGE::_void 		NSViewBasedApp_SetClientSize( EGE::_handle app, EGE::_dword width, EGE::_dword height, EGE::_long* deltawidth, EGE::_long* deltaheight );
EGE_EXTERN_DLL_OUT_FUNC EGE::_void 		NSViewBasedApp_GetClientRect( EGE::_handle app, EGE::RectI& rect );

EGE_EXTERN_DLL_OUT_FUNC EGE::_void 		NSViewBasedApp_SendMessage( EGE::_handle app, const EGE::MessageBase& msg );