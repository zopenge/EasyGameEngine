//! @file     NSAccelerometerDelegate.mm
//! @author   foreven
//! @version  1.1
//! @date     2013/09/24
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// NSAccelerometerDelegate Implementation
//----------------------------------------------------------------------------

@implementation NSAccelerometerDelegate


- (void)SetViewbasedApp : (EGE::IViewBasedApp*) viewbased_app
{
    mViewBasedApp = viewbased_app;
}

// Implement this method to get the lastest data from the accelerometer
- (void)accelerometer:(UIAccelerometer*)accelerometer didAccelerate:(UIAcceleration*)acceleration
{
    //Use a basic low-pass filter to only keep the gravity in the accelerometer values
    EGE::Events::EventAcceleration message;
    
    message.mTimestamp = acceleration.timestamp;
    
    UIInterfaceOrientation interfaceOrientation = [[UIApplication sharedApplication] statusBarOrientation];
    switch (interfaceOrientation) {
        case UIInterfaceOrientationPortrait:
            message.mX = -acceleration.x;
            message.mY = acceleration.y;
            message.mZ = acceleration.z;
            break;
        case UIInterfaceOrientationPortraitUpsideDown:
            message.mX = acceleration.x;
            message.mY = -acceleration.y;
            message.mZ = acceleration.z;
            break;
        case UIInterfaceOrientationLandscapeLeft:
            message.mX = acceleration.y;
            message.mY = acceleration.x;
            message.mZ = acceleration.z;
            break;
        case UIInterfaceOrientationLandscapeRight:
            message.mX = -acceleration.y;
            message.mY = -acceleration.x;
            message.mZ = acceleration.z;
            break;
        default:
            message.mX = acceleration.x;
            message.mY = acceleration.y;
            message.mZ = acceleration.z;
            break;
    }
    
    NSApplication* ns_app = (__bridge NSApplication*) mViewBasedApp->GetApplicationHandle( );
    
    [ns_app HandleEvent:message];
}

@end
