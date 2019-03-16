//! @file     NSApplication.mm
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEEngine.h"

//!	The application delegate what be implemented by user
extern "C" IViewBasedAppDelegate* CreateNSAppDelegate( );

//----------------------------------------------------------------------------
// NSApplication Implementation
//----------------------------------------------------------------------------

@implementation NSApplication
@synthesize ViewBasedApp = mViewBasedApp, AppDelegate = mAppDelegate;

- (void)applicationDidFinishLaunching:(UIApplication *)application
{
    
}

- (void)RestartEngine
{
	// All modules power off
	GetModuleManager( )->PowerOff( );

    mAppDelegate->OnUnload( );
    EGE_Finalize( );
    EGE_RELEASE( mAppDelegate );
	EGE_Initialize( );
	
	// Launch application
	[self LaunchApplication];
}

- (bool) LaunchApplication
{
	// Initialize options
	mAppLoadingTimes = 0;
	
	// Create the application delegate
	if ( mAppDelegate == _null )
	{
		mAppDelegate = CreateNSAppDelegate( );
		if ( mAppDelegate == _null )
			return _false;
	}
	
	// Bind application delegate with view controller
	self.viewController.AppDelegate = mAppDelegate;
	
	// Build the multi-arguments
	_dword argc = 0; const _charw* argv[512]; NSString* ns_argv[512];
	for ( id key in mInitLaunchOptions )
	{
		// Build the argument with key name as the '-keyname=value' style
		ns_argv[ argc ]	= [[NSString alloc] initWithFormat:@"-%@=%@",key,[mInitLaunchOptions objectForKey:key]];
		argv[ argc ]	= (const _charw*) [ns_argv[ argc ] cStringUsingEncoding:NSUTF16StringEncoding];
		
		// Jump to analyze the next argument
		argc ++;
	}
	
	// Create the command line parser
	ICommandLineParserPassRef command_line_parser( GetInterfaceFactory( )->CreateCommandLineParser( argc, argv ) );
	if ( command_line_parser.IsNull( ) )
		return _false;
	
	// Create the application
	mViewBasedApp = GetInterfaceFactory( )->CreateViewBasedApplication( (__bridge_retained _handle)self );
	if ( mViewBasedApp.IsNull( ) )
		return _false;
	
	// Set the main viewbased application
	SetMainViewBasedApp( mViewBasedApp );
	
	// Register the application delegate
	GetModuleManager( )->RegisterAppDelegate( mAppDelegate );
	
	// Initialize ratio
	Ratio& ratio = mViewBasedApp.cast_static<iosViewBasedApp>( )->GetRatio( );
	ratio.Init( (_float)mAppDelegate->OnGetInitialSize( ).x, (_float)mAppDelegate->OnGetInitialSize( ).y );
	
	// Initialize accelerometer
	GetAccelerometer( )->Initialize( mViewBasedApp, 1.0f / 60.0f );
	
	// Register application as observer
	GetModuleManager( )->RegisterObserver( mViewBasedApp );
	
	// Launch the application
	EventBeforeLaunchApp before_launch_app_event;
	GetModuleManager( )->ProcessEvent( before_launch_app_event );
	{
		if ( mAppDelegate->OnLaunch( mViewBasedApp.GetPtr( ), command_line_parser.GetPtr( ) ) == _false )
			return _false;
	}
	EventAfterLaunchApp after_launch_app_event;
	GetModuleManager( )->ProcessEvent( after_launch_app_event );

	EventBeforeLoadApp before_load_app_event;
	GetModuleManager( )->ProcessEvent( before_load_app_event );

	// Post resize message to modules and application delegate
	[self PostResizeMsg];
	
	return _true;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Initialize EGE
	if ( EGE_Initialize( ) == _false )
		return _false;

    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];  
    
    // Hide the status bar
    if ( application != nil )
        application.statusBarHidden = YES;

	// Enable shake feature for application (default: YES ...)
	application.applicationSupportsShakeToEdit = YES;

    // Save the initial options
	mUIApplication		= application;
    mInitLaunchOptions  = launchOptions;
	
    // Create UI window
	self.window	= [[UIWindow alloc]initWithFrame:[[UIScreen mainScreen] bounds]];

    // Create UI view controller
	self.viewController = [[NSUIViewController alloc]init];
	[self.viewController setApplication:self];

	// Create UI view
	self.view = [NSUIView viewWithFrame:[self.window bounds] pixelFormat:kEAGLColorFormatRGBA8];
	
	// Create the application delegate
	mAppDelegate = CreateNSAppDelegate( );
	if ( mAppDelegate == _null )
		return _false;

	// Get the window size
    CGSize window_size = self.window.bounds.size;
    switch ( mAppDelegate->OnGetInitialOrientation( ) )
    {
        case _VIEWBASED_APP_ORIENTATION_PORT:
        {
            window_size = self.window.bounds.size;
        }
        break;
            
        case _VIEWBASED_APP_ORIENTATION_LAND:
        {
            float version = [[[UIDevice currentDevice] systemVersion] floatValue];
            if (version >= 8.0)
            {
                window_size = self.window.bounds.size;
            }
            else
            {
                window_size.width = self.window.bounds.size.height;
                window_size.height = self.window.bounds.size.width;
            }
        }
        break;
        
        default:
            break;
    }
	
	// Set the window region and bind delegate
    self.view.bounds = CGRectMake( 0, 0, window_size.width, window_size.height );
    self.view.center = CGPointMake( window_size.width * 0.5f, window_size.height * 0.5f );
    [self.view setUIViewController:self.viewController];
	self.viewController.view        = self.view;
	self.viewController.AppDelegate = mAppDelegate;

    // Add sub view and set root view controller
    [self.window addSubview:self.viewController.view];
    if ([self.window respondsToSelector:@selector(setRootViewController:)])
        [self.window setRootViewController:self.viewController];
	
	// Make it visible
    [self.window makeKeyAndVisible];

	// Launch application
	if ( [self LaunchApplication] == _false )
		return _false;

	return _true;
}

- (NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window
{
	return UIInterfaceOrientationMaskAll;
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
	// Activate the application
	[self.viewController Activate];
    
    EventActivityResume message;
    [self HandleEvent:message];
}

- (void)applicationWillResignActive:(UIApplication *)application
{
	// Deactivate the application
	[self.viewController Deactivate];

	EventActivityPause message;
	[self HandleEvent:message];
}

// No equiv. notification. return NO if the application can't open for some reason
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation 
{
    WStringPtr url_utf16 = (const _charw*) [[url absoluteString] cStringUsingEncoding:NSUnicodeStringEncoding];
    
    EventApplicationOpenUrl message;
    message.mURL = url_utf16;
    
    [self HandleEvent:message];
    
	return _false;
}

// Try to clean up as much memory as possible. next step is to terminate app
- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application
{
	EventLowMemory message;
	
	[self HandleEvent:message];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	// Deactivate the application
	[self.viewController Deactivate];

	// All modules power off
	GetModuleManager( )->PowerOff( );

	// Unload the application
	mAppDelegate->OnUnload( );

	// Finalize EGE
	EGE_Finalize( );
}

// M, carrier time update, daylight savings time change
- (void)applicationSignificantTimeChange:(UIApplication *)application
{

}

- (void)application:(UIApplication *)application willChangeStatusBarOrientation:(UIInterfaceOrientation)newStatusBarOrientation duration:(NSTimeInterval)duration
{

}

- (void)application:(UIApplication *)application didChangeStatusBarOrientation:(UIInterfaceOrientation)oldStatusBarOrientation
{

}

// In screen coordinates
- (void)application:(UIApplication *)application willChangeStatusBarFrame:(CGRect)newStatusBarFrame;  
{

}

- (void)application:(UIApplication *)application didChangeStatusBarFrame:(CGRect)oldStatusBarFrame
{

}

// one of these will be called after calling -registerForRemoteNotifications
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    NSString* ns_deviceToken = [NSString stringWithFormat:@"%@", deviceToken];
    
    EventApplicationRegisterForPushNotification  registerforpushnotification;
    registerforpushnotification.mSuccess    = _true;
    registerforpushnotification.mResult     = (const _charw*) [ns_deviceToken cStringUsingEncoding:NSUnicodeStringEncoding];
    
    [self HandleEvent:registerforpushnotification];
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
    NSString* ns_error = [NSString stringWithFormat:@"%@", error];
    
    EventApplicationRegisterForPushNotification  registerforpushnotification;
    registerforpushnotification.mSuccess    = _false;
    registerforpushnotification.mResult     = (const _charw*) [ns_error cStringUsingEncoding:NSUnicodeStringEncoding];
    
    [self HandleEvent:registerforpushnotification];
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{

}

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification
{

}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    EventEnterBackground client_enter_background;
    [self HandleEvent:client_enter_background];
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    EventEnterForeground client_enter_foreground;
    [self HandleEvent:client_enter_foreground];
}

- (void)applicationProtectedDataWillBecomeUnavailable:(UIApplication *)application
{

}

- (void)applicationProtectedDataDidBecomeAvailable:(UIApplication *)application
{

}

- (void) PostResizeMsg
{
	// Get the frame size
	CGSize frame_size = [self.view getSize];
    mViewBasedApp.cast_static<iosViewBasedApp>( )->GetRatio( ).UpdateSize( (_float) frame_size.width, (_float) frame_size.height );
	// Tell the application delegate to handle message
	EventClientSizeChanged client_size_changed_msg;
	client_size_changed_msg.mClientSize = PointU( (_dword) frame_size.width, (_dword) frame_size.height );
    if ( mViewBasedApp->IsEnableOptions( IViewBasedApp::_OPTION_KEEP_RATIO ) )
        client_size_changed_msg.mRatio = mViewBasedApp.cast_static<iosViewBasedApp>( )->GetRatio( );
    else
        client_size_changed_msg.mRatio.Init( frame_size.width, frame_size.height );
    
    //if ( GetModuleManager( ) != _null )
    //    GetModuleManager( )->AddDelayMessage( client_size_changed_msg );
	[self HandleEvent:client_size_changed_msg];
}

- (void) UpdateFrame
{
	// Load the application
	if ( GetModuleManager( )->HasLoadedApp( ) == _false )
	{
		_ubool keep_loading = _false;
		if ( mAppDelegate->OnLoad( mViewBasedApp.GetPtr( ), mAppLoadingTimes ++, keep_loading ) == _false )
		{
			mAppLoadingTimes = 0;
			return;
		}

		if ( keep_loading == _false )
		{
			EventAfterLoadApp after_load_app_event;
			GetModuleManager( )->ProcessEvent( after_load_app_event );
		}
	}
	else
	{
		// Check whether need to restart it
		if ( mViewBasedApp->IsRestart( ) )
		{
			[self RestartEngine];
		}
		// Update application
		else
		{
			static unsigned int last_tickcount = Platform::GetCurrentTickCount( );
		
			// Calculate the elapse in milliseconds
			_dword tick		= Platform::GetCurrentTickCount( );
			_dword elapse	= tick - last_tickcount;
		
			// Get the limited elapsed time
			_dword limited_elapse = Math::Min( mMaxLimitedElapsedTime, elapse );

			// Update the engine
			EGE_Tick( limited_elapse, elapse );
        
			// Update the application
			mViewBasedApp->Tick( limited_elapse, elapse );
        
			// Update the application delegate
			mAppDelegate->OnTick( limited_elapse, elapse );

			// Clear temporary info
			Memory::GetInstance( ).ClearCurAllocNumber( );

			// Update the last tickcount for calculating the elapse
			last_tickcount = tick;
		}
	}
}

- (void) HandleEvent:(EventBase&) event
{
	// Handle modules message
	if ( GetModuleManager( ) != _null )
		GetModuleManager( )->ProcessEvent( event );
}

//! Fix Input pos
- (PointF) ConvertPos:(PointF) pos
{
    iosViewBasedApp* app = mViewBasedApp.cast_static<iosViewBasedApp>( );
    return app->ConvertPos( pos );
}

- (void) dealloc
{
	EGE_RELEASE( mAppDelegate );
	mViewBasedApp.Clear( );
}

@end
