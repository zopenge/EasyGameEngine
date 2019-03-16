//! @file     NSAdView.mm
//! @author   LiCode
//! @version  1.1.1.804
//! @date     2011/03/10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Helpful Functions Implementation
//----------------------------------------------------------------------------

AdViewType TranslateAdViewType( IAdView::_TYPE type )
{
	switch ( type )
	{
		case IAdView::_TYPE_UNKNOWN:			return AdViewTypeUnknown;
	    case IAdView::_TYPE_NORMAL_BANNER:		return AdViewTypeNormalBanner;
	    case IAdView::_TYPE_LARGE_BANNER:		return AdViewTypeLargeBanner;
	    case IAdView::_TYPE_MEDIUM_BANNER:		return AdViewTypeMediumBanner;
	    case IAdView::_TYPE_RECTANGLE:			return AdViewTypeRectangle;
	    case IAdView::_TYPE_FULL_SCREEN:		return AdViewTypeFullScreen;
	    case IAdView::_TYPE_IPAD_NORMAL_BANNER:	return AdViewTypeiPadNormalBanner;
		default:
			return AdViewTypeUnknown;
	}
}

//----------------------------------------------------------------------------
// NS-AdView Implementation
//----------------------------------------------------------------------------

_handle	NSAdView_Create( AStringPtr app_id, IAdView::_TYPE type, _handle viewbased_app, IAdView* ad_view )
{
    // Get the NS-Application
//	NSApplication* ns_app = (__bridge NSApplication*) viewbased_app;
//	EGE_ASSERT( ns_app != _null );
//
//	// Create view delegate
//    NSAdViewDelegate* ad_view_delegate = [NSAdViewDelegate alloc];
//
//	// Create view
//    AdMoGoView* ad_mogo_view = [[AdMoGoView alloc] initWithAppKey:[NSString stringWithUTF8String:app_id.Str( )]
//		adType:TranslateAdViewType( type )
//		expressMode:NO
//		adMoGoViewDelegate:ad_view_delegate];
//
//	// Let view to manage it
//	ad_view_delegate.ViewController = ns_app.viewController;
//
//	// Create web browser delegate
//	NSAdWebBrowserDelegate* ad_web_browser_delegate = [NSAdWebBrowserDelegate alloc];
//    ad_mogo_view.adWebBrowswerDelegate = ad_web_browser_delegate;
//
//	// Let view to manage it
//	ad_web_browser_delegate.AdView			= ad_view;
//	ad_web_browser_delegate.ViewController	= ad_view_delegate.ViewController;
//
//	// Add into main view
//    ad_mogo_view.frame = CGRectZero;
//    [ns_app.view addSubview:ad_mogo_view];

	return ad_view;
}

_void NSAdView_Show( _handle app, _ubool show )
{
	AdMoGoView* ad_view = (__bridge AdMoGoView*) app;
	EGE_ASSERT( ad_view != _null );

    ad_view.hidden = !show;
}