//! @file     NSUIViewController.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

@class NSApplication;

//----------------------------------------------------------------------------
// NSUIViewController
//----------------------------------------------------------------------------

@interface NSUIViewController : UIViewController< GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate >
{
@private
	//!	The UI View
	NSUIView*                   mUIView;
	//!	The NSApplication
	NSApplication*              mApplication;
	//!	The timer bound to display
	CADisplayLink*              mDisplayLink;

	//!	The advertisement view
    EGE::IAdViewRef             mAdView;
    //! The viewbased application delegate
    EGE::IViewBasedAppDelegate* mAppDelegate;

	//!	The leader board ID
	NSString*                   mLeaderBoardID;
}

@property (strong, nonatomic) NSUIView* UIView;
@property (strong, nonatomic) NSApplication* Application;
@property (strong, nonatomic) CADisplayLink* DisplayLink;
@property (strong, nonatomic) NSString* LeaderBoardID;
@property (nonatomic, assign) EGE::IViewBasedAppDelegate* AppDelegate;

//!	Process touches event.
- (void) processTouches:(NSSet*)touches withEvent:(UIEvent*)event touches_event:(EGE::Events::EventTouch::_EVENT)touches_event;

//!	Process pinch gesture event.
- (void) processPinchGesture:(CGFloat)scale_factor zoom_flag:(EGE::Events::EventPinchGesture::_ZOOM_FLAG)zoom_flag state:(EGE::Events::EventPinchGesture::_STATE)state;

//!	Activate/Deactivate
- (void) Activate;
- (void) Deactivate;

//! Load advertisement view.
- (void) LoadAdView : (EGE::AStringPtr)app_id type:(EGE::IAdView::_TYPE)type;
//! Show/Hide advertisement view.
- (void) ShowAdView : (bool)show;

//! Show alert dialog.
- (void) ShowAlertWithTitle : (NSString*)title message:(NSString*)message;

//! Load game center
- (void) LoadGameCenter : (NSString*)leader_board_id;
- (void) ShowGameCenterLeaderboard;
- (void) ShowGameCenterAchievement;

@end
