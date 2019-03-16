//! @file     NSUIViewController.mm
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// NSUIViewController Implementation
//----------------------------------------------------------------------------

@implementation NSUIViewController
@synthesize UIView = mUIView, Application = mApplication, DisplayLink = mDisplayLink, LeaderBoardID = mLeaderBoardID, AppDelegate = mAppDelegate;

- (void) dealloc
{
    //[mUIView release]; 
}

- (BOOL)shouldAutorotate
{
    return YES;
}

-(BOOL)canBecomeFirstResponder
{
	return YES;
}

-(void)viewDidAppear:(BOOL)animated
{
	[super viewDidAppear:animated];
	[self becomeFirstResponder];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[self resignFirstResponder];
	[super viewWillDisappear:animated];
}

- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event{
	
	if (motion == UIEventSubtypeMotionShake)
	{
		// Handle the shake message
		EventShakeMotion msg_shake;
		msg_shake.mEvent		= EventShakeMotion::_EVENT_BEGAN;
		msg_shake.mTimestamp	= Platform::GetCurrentTickCount( );
		[mApplication HandleEvent:msg_shake];
	}
}

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
	if (motion == UIEventSubtypeMotionShake)
	{
		// Handle the shake message
		EventShakeMotion msg_shake;
		msg_shake.mEvent		= EventShakeMotion::_EVENT_ENDED;
		msg_shake.mTimestamp	= Platform::GetCurrentTickCount( );
		[mApplication HandleEvent:msg_shake];
	}
}

- (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
	if (motion == UIEventSubtypeMotionShake)
	{
		// Handle the shake message
		EventShakeMotion msg_shake;
		msg_shake.mEvent		= EventShakeMotion::_EVENT_CANCELLED;
		msg_shake.mTimestamp	= Platform::GetCurrentTickCount( );
		[mApplication HandleEvent:msg_shake];
	}
}

- (NSUInteger)supportedInterfaceOrientations
{
    _VIEWBASED_APP_ORIENTATION orientation = mAppDelegate->OnGetInitialOrientation( );
	EGE_ASSERT( orientation != _VIEWBASED_APP_ORIENTATION_UNKNOWN );

    // Return YES for supported orientations
	if ( orientation == _VIEWBASED_APP_ORIENTATION_ANY )
		return UIInterfaceOrientationMaskAll;
	else if ( orientation == _VIEWBASED_APP_ORIENTATION_PORT )
		return UIInterfaceOrientationMaskPortrait;
	else if ( orientation == _VIEWBASED_APP_ORIENTATION_LAND )
		return UIInterfaceOrientationMaskLandscape;
	else
		return UIInterfaceOrientationMaskAllButUpsideDown; // Unknown orientation type ( we should never go there ... )
}

// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	_VIEWBASED_APP_ORIENTATION orientation = mAppDelegate->OnGetInitialOrientation( );
	EGE_ASSERT( orientation != _VIEWBASED_APP_ORIENTATION_UNKNOWN );

    // Return YES for supported orientations
	if ( orientation == _VIEWBASED_APP_ORIENTATION_ANY )
		return YES;
	else if ( orientation == _VIEWBASED_APP_ORIENTATION_PORT )
		return interfaceOrientation == UIInterfaceOrientationPortrait || interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown;
	else if ( orientation == _VIEWBASED_APP_ORIENTATION_LAND )
		return interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight;
	else
		return NO; // Unknown orientation type
}

- (void) processTouches:(NSSet*)touches withEvent:(UIEvent*)event touches_event:(EGE::Events::EventTouch::_EVENT)touches_event
{
	// Build the touch message
	EventTouch msg_touch;
	msg_touch.mEvent = touches_event;
    UITouch* touch;
    
    static _dword sTouchId = 0;
    static Map< _dword, _dword > sTouchIdMap;
    
	_dword index = 0;

	// Notify each touch event to application
	for ( touch in touches )
	{
		msg_touch.mIndex		= index ++;
        msg_touch.mTimestamp	= Platform::GetCurrentTickCount( );//[touch timestamp];
        
        if ( msg_touch.mEvent == EventTouch::_EVENT_BEGAN )
        {
            sTouchId ++;
            sTouchIdMap.Insert( sTouchId, (_dword)(size_t)touch );
            msg_touch.mTouchID = sTouchId;
        }
        else if ( msg_touch.mEvent == EventTouch::_EVENT_ENDED )
        {
            msg_touch.mTouchID = *sTouchIdMap.Search( (_dword)(size_t)touch );
            sTouchIdMap.Remove( (_dword)(size_t)touch );
        }
        else if ( msg_touch.mEvent == EventTouch::_EVENT_MOVED )
        {
            msg_touch.mTouchID = *sTouchIdMap.Search( (_dword)(size_t)touch );
        }
        
		// Get the location info
		CGPoint location			= [touch locationInView:mApplication.view];
		msg_touch.mLocation.x		= location.x;
		msg_touch.mLocation.y		= location.y;

		// Get the previous location info
		CGPoint prevlocation		= [touch previousLocationInView:mApplication.view];
		msg_touch.mPrevLocation.x	= prevlocation.x;
		msg_touch.mPrevLocation.y	= prevlocation.y;
		
		// Here we need to multiple the position by content scale factor
        _float scale = [mApplication.view contentScaleFactor];
		msg_touch.mLocation		*= scale;
		msg_touch.mPrevLocation	*= scale;
        
        msg_touch.mLocation         = [mApplication ConvertPos: msg_touch.mLocation];
        msg_touch.mPrevLocation     = [mApplication ConvertPos: msg_touch.mPrevLocation];
        
		// Handle the touch message
		[mApplication HandleEvent:msg_touch];
	}
}

- (void) processPinchGesture:(CGFloat)scale_factor zoom_flag:(EGE::Events::EventPinchGesture::_ZOOM_FLAG)zoom_flag state:(EGE::Events::EventPinchGesture::_STATE)state
{
	// Initialize touches message
	EventPinchGesture msg_pinch_gesture;
	msg_pinch_gesture.mState		= state;
	msg_pinch_gesture.mZoomFlag		= zoom_flag;
	msg_pinch_gesture.mScaleFactor	= scale_factor;

	// Handle the touches message
	[mApplication HandleEvent:msg_pinch_gesture];
}

- (void) Activate
{
	// Create display link    
	mDisplayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(UpdateFrame)];
	[mDisplayLink setFrameInterval:1];

	// Add into the run loop
	[mDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

- (void) Deactivate;
{
	// Release display link
	[mDisplayLink invalidate];
	mDisplayLink = nil;
}

- (void) UpdateFrame
{
	// Update the application
	[mApplication UpdateFrame];
}

#pragma mark - View lifecycle

- (void) LoadAdView : (AStringPtr)app_id type:(IAdView::_TYPE)type
{
	mAdView = GetPlatform( )->CreateAdView( app_id, mApplication.ViewBasedApp, type );
	EGE_ASSERT( mAdView.IsValid( ) );
}

- (void) ShowAdView : (bool)show
{
	mAdView->Show( show );
}

- (void) ShowAlertWithTitle : (NSString*)title message:(NSString*)message
{
    UIAlertView* alert = [[UIAlertView alloc] initWithTitle:title message:message delegate:NULL cancelButtonTitle:@"OK" otherButtonTitles:NULL];
    [alert show];
}

- (void) LoadGameCenter : (NSString*)leader_board_id
{
	mLeaderBoardID = leader_board_id;
    
    //if ( [GameCenterManager isGameCenterAvailable] )
    //{
    //    self.gameCenterManager = [[[GameCenterManager alloc] init] autorelease];
    //    [self.gameCenterManager setDelegate:self];
    //    [self.gameCenterManager authenticateLocalUser];
    //    
    //    GKLocalPlayer* localplayer = [GKLocalPlayer localPlayer];
    //    [localplayer authenticateWithCompletionHandler:^(NSError *error)
    //    {
    //        if (localplayer.isAuthenticated)
    //        {
    //            NSLog( @"User alias: %@", [[GKLocalPlayer localPlayer] alias] );
    //            NSLog( @"User id: %@", [[GKLocalPlayer localPlayer] playerID] );
    //        }
    //    }];
    //}
    //else
    //{
    //    [self ShowAlertWithTitle: @"Game Center Support Required!"
    //                     message: @"The current device does not support Game Center, which this app requires."];
    //}
}

- (void) ShowGameCenterLeaderboard
{
    GKLeaderboardViewController* leaderboardController = [[GKLeaderboardViewController alloc] init];
    if ( leaderboardController != NULL )
    {
        leaderboardController.category = mLeaderBoardID;
        leaderboardController.timeScope = GKLeaderboardTimeScopeAllTime;
        leaderboardController.leaderboardDelegate = self;
        [self presentModalViewController: leaderboardController animated: YES];
        
        //[self stopAnimation];
    }
}

- (void) ShowGameCenterAchievement
{
}

- (void) leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController
{
    [self dismissModalViewControllerAnimated: YES];
    
    //[self startAnimation];
}

- (void) achievementViewControllerDidFinish:(GKAchievementViewController *)viewController
{
    [self dismissModalViewControllerAnimated: YES];
    
    //[self startAnimation];
}

@end
