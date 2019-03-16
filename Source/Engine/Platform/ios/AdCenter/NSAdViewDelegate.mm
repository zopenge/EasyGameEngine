//! @file     NSAdViewDelegate.mm
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// NSAdViewDelegate Implementation
//----------------------------------------------------------------------------

@implementation NSAdViewDelegate
@synthesize ViewController = mUIViewController;

- (UIViewController*) viewControllerForPresentingModalView
{
	return mViewController;
}

- (void) adMoGoDidStartAd : (AdMoGoView*)adMoGoView
{
}

- (void) adMoGoDidReceiveAd : (AdMoGoView*) adMoGoView
{
}

- (void) adMoGoDidFailToReceiveAd : (AdMoGoView*)adMoGoView didFailWithError:(NSError*)error
{
}

- (void) adMoGoClickAd : (AdMoGoView*)adMoGoView
{
}


- (void) adMoGoDeleteAd : (AdMoGoView*) adMoGoView
{
}

-(BOOL) shouldAlertQAView : (UIAlertView*)alertView
{
    return YES;
}

@end