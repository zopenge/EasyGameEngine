//! @file     EGE_IOSMain.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#endif

// ViewBased Application
#define RUN_VIEWBASED_APP( creation_flag /*not used*/, x )									\
	extern "C" {																			\
		/* Be used by IOS-Application to create the user application delegate in core */	\
		EGE::IViewBasedAppDelegate* CreateNSAppDelegate( )									\
			{ return new x( ); }															\
	}
#define RUN_CLIENT_APP( creation_flag, x, client )											\
	extern "C" {																			\
		/* Be used by IOS-Application to create the user application delegate in core */	\
		EGE::IViewBasedAppDelegate* CreateNSAppDelegate( )									\
		{																					\
			PassRefPtr< client > client_app( new client );									\
			return new x( client.GetPtr( ) );												\
		}																					\
	}

#ifdef __OBJC__

//! The main entry
EGE::_int main( EGE::_int argc, char* argv[] )
{
#if !__has_feature(objc_arc)
	// Create auto release pool
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
#endif
	
	// Start IOS application
	EGE::_int ret = UIApplicationMain( argc, argv, nil, @"NSApplication" );

	// Release auto release pool
#if !__has_feature(objc_arc)
	[pool release];
#endif
	return ret;
}

#endif
