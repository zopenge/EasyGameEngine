//! @file     EGE_AndroidMain.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

// ViewBased Application
#define RUN_VIEWBASED_APP( creation_flag /*not used*/, x )										\
	extern "C" {																				\
		/* Be used by Android-Application to create the user application delegate in core */	\
		EGE_INTERNAL EGE::IViewBasedAppDelegate* CreateAndroidAppDelegate( )					\
			{ return new x( ); }																\
	}
#define RUN_CLIENT_APP( creation_flag, x, client )												\
	extern "C" {																				\
		/* Be used by Android-Application to create the user application delegate in core */	\
		EGE::IViewBasedAppDelegate* CreateAndroidAppDelegate( )									\
		{																						\
			PassRefPtr< client > client_app( new client );										\
			return new x( client.GetPtr( ) );													\
		}																						\
	}

//!	Get the Java VM handle.
extern "C" EGE::_handle GetJavaVMHandle( );