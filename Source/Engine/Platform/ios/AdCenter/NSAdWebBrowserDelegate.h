//! @file     NSAdWebBrowserDelegate.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

//----------------------------------------------------------------------------
// NSAdWebBrowserDelegate
//----------------------------------------------------------------------------

@interface NSAdWebBrowserDelegate : NSObject< AdMoGoWebBrowserControllerUserDelegate >
{
@private
	UIViewController*	mViewController;
    EGE::IAdView*		mAdView;
}

@property (nonatomic, assign) UIViewController* ViewController;
@property (nonatomic, assign) EGE::IAdView* AdView;

@end