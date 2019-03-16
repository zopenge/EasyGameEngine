//! @file     NSApplication.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

//----------------------------------------------------------------------------
// NSApplication
//----------------------------------------------------------------------------

@interface NSApplication : NSObject< UIApplicationDelegate >
{
@private
	EGE::_dword		mAppLoadingTimes;
	UIApplication*	mUIApplication;
    NSDictionary*	mInitLaunchOptions;
}

@property (strong, nonatomic) UIWindow* window;
@property (strong, nonatomic) NSUIView* view;
@property (strong, nonatomic) NSUIViewController* viewController;

@property (nonatomic, assign) EGE::IViewBasedAppRef ViewBasedApp;
@property (nonatomic, assign) EGE::IViewBasedAppDelegate* AppDelegate;

//!	Post resize message.
- (void) PostResizeMsg;

//!	Update.
- (void) UpdateFrame;
//!	Handle event.
- (void) HandleEvent:(EGE::Events::EventBase&) event;
//! Fix Input pos
- (EGE::PointF) ConvertPos:(EGE::PointF) pos;
//! Restart engine.
- (void) RestartEngine;
//!	Launch application.
- (bool) LaunchApplication;

@end
