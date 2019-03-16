//! @file     NSAdWebBrowserDelegate.mm
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// NSAdWebBrowserDelegate Implementation
//----------------------------------------------------------------------------

@implementation NSAdWebBrowserDelegate
@synthesize ViewController = mUIViewController, AdView = mAdView;

- (void) webBrowserWillAppear
{
	mAdView->GetWebBrowserDelegate( )->OnWillAppear( );
}

- (void) webBrowserDidAppear
{
	mAdView->GetWebBrowserDelegate( )->OnDidAppear( );
}

- (void) webBrowserWillClosed
{
	mAdView->GetWebBrowserDelegate( )->OnWillClosed( );
}

- (void) webBrowserDidClosed
{
	mAdView->GetWebBrowserDelegate( )->OnDidClosed( );
}

- (void) webBrowserShare:(NSString*) url
{
	WStringPtr url_utf16 = (const _charw*) [url cStringUsingEncoding:NSUnicodeStringEncoding];

	mAdView->GetWebBrowserDelegate( )->OnShare( url_utf16 );
}

@end