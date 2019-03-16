//! @file     NSAPI.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

//----------------------------------------------------------------------------
// NS-Device
//----------------------------------------------------------------------------

EGE_INTERNAL EGE::WString			NSDevice_GetIdentifierForVendor( );
EGE_INTERNAL EGE::WString			NSDevice_GetAdvertisingIdentifier( );
EGE_INTERNAL EGE::WString			NSDevice_GetDeviceName( );
EGE_INTERNAL EGE::WString			NSDevice_GetModelName( );
EGE_INTERNAL EGE::WString			NSDevice_GetSystemName( );
EGE_INTERNAL EGE::WString			NSDevice_GetSystemVersion( );
EGE_INTERNAL EGE::_USER_INTERFACE	NSDevice_GetUserInterfaceIdiom( );
EGE_INTERNAL EGE::WString			NSDevice_GetHardwareID( );

//----------------------------------------------------------------------------
// NS-Screen
//----------------------------------------------------------------------------

EGE_INTERNAL EGE::PointU			NS_ScreenGetSize( );

//----------------------------------------------------------------------------
// NS-ViewBasedApp
//----------------------------------------------------------------------------

EGE_INTERNAL EGE::_handle			NSViewBasedApp_GetCAEAGLLayer( EGE::_handle app );

EGE_INTERNAL EGE::_void 			NSViewBasedApp_Show( EGE::_handle app );
EGE_INTERNAL EGE::_void 			NSViewBasedApp_Hide( EGE::_handle app );

EGE_INTERNAL EGE::_void 			NSViewBasedApp_Center( EGE::_handle app );

EGE_INTERNAL EGE::_void 			NSViewBasedApp_SetPos( EGE::_handle app, EGE::_dword x, EGE::_dword y );
EGE_INTERNAL EGE::_void 			NSViewBasedApp_SetSize( EGE::_handle app, EGE::_dword width, EGE::_dword height );
EGE_INTERNAL EGE::PointU			NSViewBasedApp_GetSize( EGE::_handle app );
EGE_INTERNAL EGE::RectI 			NSViewBasedApp_GetRect( EGE::_handle app );
EGE_INTERNAL EGE::_void 			NSViewBasedApp_SetClientSize( EGE::_handle app, EGE::_dword width, EGE::_dword height, EGE::_int* deltawidth, EGE::_int* deltaheight );
EGE_INTERNAL EGE::RectU 			NSViewBasedApp_GetClientRect( EGE::_handle app );

//----------------------------------------------------------------------------
// NS-Net
//----------------------------------------------------------------------------

EGE_INTERNAL EGE::INet::_STATUS		NSNet_GetStatus( );
EGE_INTERNAL EGE::_ubool			NSNet_Ping( EGE::AStringPtr address );

EGE_INTERNAL EGE::_void				NSNet_OpenUrl( const EGE::_chara* url );

//----------------------------------------------------------------------------
// NS-Application
//----------------------------------------------------------------------------

EGE_INTERNAL EGE::_void				NSApplication_RegisterForPushNotification( );