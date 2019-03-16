//! @file     NSKYPayManager.h
//! @author   foreven
//! @version  1.0.0.0
//! @date     2013/10/22

#pragma once

@interface NSKYPayView : UIView<KY_PaySDKDelegate>{
}

@property (nonatomic, assign) BOOL isOrientation;

- (void) setControllerAndUrlScheme:(UIViewController*)vc urlScheme:(EGE::UStringPtr)urlScheme;
- (void) OnRelease;
- (void) PachaseProduct:(EGE::UStringPtr)game_id uid:(EGE::UStringPtr)uid product_name:(EGE::UStringPtr)product_name price:(EGE::UStringPtr)price dealseq:(EGE::UStringPtr)dealseq parentview:(NSUIView*)parentview;
@end
