//! @file     NSWebView.h
//! @author   foreven
//! @version  1.0.0.621
//! @date     2013/09/24

#pragma once

@interface NSWebView : UIView<UIWebViewDelegate>
{
    NSUIView*           parentView;
	UIWebView*          ns_webView;
    EGE::IWebView*      c_webView;
}

- (void)webViewDidStartLoad:(UIWebView *)webView;
- (void)webViewDidFinishLoad:(UIWebView *)webView;
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error;

- (void) initialize: (const EGE::PointI&) pos size:(const EGE::PointI&) size parent_view:(NSUIView*) parent_view web_view:(EGE::IWebView*) web_view;
- (void) show : (EGE::_ubool) is_show;
- (void) setRegion : (const EGE::RectI&) region;
- (void) openURL : (EGE::WStringPtr) url_address;
- (void) refresh;
- (void) destroyView;
@end