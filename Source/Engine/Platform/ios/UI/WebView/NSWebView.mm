//! @file     NSWebView.mm
//! @author   foreven
//! @version  1.1
//! @date     2013/09/24
//! Copyright ...

#include "EGEEngine.h"

@interface NSWebView ()

@end

@implementation NSWebView 

- (void)webViewDidStartLoad:(UIWebView *)webView
{
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    c_webView->GetNotifier( )->OnPageFinished( c_webView->GetURLAddress( ) );
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    _dword  err_id  = (_dword)[error code];
	WString domain  = NSPlatform::NSStringToUtf16([error domain]);
    WString desc    = NSPlatform::NSStringToUtf16([error localizedDescription]);
    
    c_webView->GetNotifier( )->OnReceivedError( err_id, desc, domain );
}

- (void) initialize: (const EGE::PointI&) pos size:(const PointI&) size parent_view:(NSUIView*) parent_view web_view:(EGE::IWebView*) web_view
{
    parentView = parent_view;
    
    c_webView = web_view;
    
	ns_webView = [[UIWebView alloc]initWithFrame:CGRectMake(pos.x, pos.y, size.x, size.y)];
	ns_webView.delegate=self;
	[ns_webView setOpaque:NO];
	[ns_webView setUserInteractionEnabled:YES];
	[ns_webView setScalesPageToFit:YES];

    [parentView addSubview:ns_webView];
}

- (void) show : (_ubool) is_show
{
	ns_webView.hidden = EGE_BOOLEAN( !is_show );
}

- (void) setRegion : (const RectI&) region
{
	_float scale = [[UIScreen mainScreen]scale];
	
	RectI fixed_region = region / PointI( (_int)scale, (_int)scale );
	
    ns_webView.frame = CGRectMake(fixed_region.l, fixed_region.t, fixed_region.GetWidth( ), fixed_region.GetHeight( ));
}

- (void) openURL : (WStringPtr) url_address
{
	[ns_webView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:NSPlatform::Utf16ToNSString( url_address )]]];
}

- (void) refresh
{
}

- (void) destroyView
{
    [parentView willRemoveSubview:ns_webView];
}

@end
