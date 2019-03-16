//! @file     NSKYPayView.mm
//! @author   foreven
//! @version  1.1
//! @date     2013/10/22
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// NSKYPayView Implementation
//----------------------------------------------------------------------------

@implementation NSKYPayView
@synthesize isOrientation = isOrientation;
- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code
        isOrientation = YES;
        
        [KY_PaySDK instance].hidden = YES;
        
        [KY_PaySDK instance].ky_delegate = self;
        
        [self addSubview:[KY_PaySDK instance]];
        
        //注册支付宝通知接收
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(payResult:) name:@"KY_NOTIFICATION" object:nil];
    }
    return self;
}

-(void)setControllerAndUrlScheme:(UIViewController*)vc urlScheme:(EGE::UStringPtr)urlScheme
{
    [[KY_PaySDK instance] setViewController:vc andAppScheme:[NSString stringWithUTF8String:urlScheme.Str( )]];
}

//支付宝 '直接' 通知结果
- (void)payResult:(NSNotification*)notification{
    
    [KY_PaySDK instance].hidden = YES;
    
    id obj = [notification object];
    NSURL * url = obj;
    CHECK result = [[KY_PaySDK instance] checkAlipayResult:url];
    
    [self checkCode:result];
}

- (void) PachaseProduct:(EGE::UStringPtr)game_id uid:(EGE::UStringPtr)uid product_name:(EGE::UStringPtr)product_name price:(EGE::UStringPtr)price dealseq:(EGE::UStringPtr)dealseq  parentview:(NSUIView*)parentview
{
    NSString* ns_game_id    = [NSString stringWithUTF8String:game_id.Str( )];
    NSString* ns_uid        = [NSString stringWithUTF8String:uid.Str( )];
    NSString* ns_pname      = [NSString stringWithUTF8String:product_name.Str( )];
    NSString* ns_price      = [NSString stringWithUTF8String:price.Str( )];
    NSString* ns_dealseq    = [NSString stringWithUTF8String:dealseq.Str( )];
    NSString* ns_version    = @"1.3";
    NSString* ns_paytype    = @"alipaywap";
    
    NSMutableDictionary * map = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                 //@"iPhone", @"d",
                                 ns_dealseq, @"dealseq",
                                 ns_price, @"fee",
                                 ns_game_id, @"game",
                                 //@"", @"gamesvr",
                                 ns_pname, @"subject",
                                 ns_version, @"v",
                                 ns_uid, @"uid",
                                 ns_paytype, @"paytype",
                                 nil];
    
    NSString * ss = [KY_PaySDK getMD5Str:map];
    NSString * sign = [KY_PaySDK getMD5:[NSString stringWithFormat:@"%@3PXupxWAJoR5ULbgU6J82FLZxamxYJwi",ss]];
    sign = [sign lowercaseString];
    
    [map setObject:sign forKey:@"sign"];
    
    [[KY_PaySDK instance] setValue:map];
}

//回调
/*银联回调
 seq        : dealseq
 code       : 银联状态码 1为成功,-1为失败
 resultStr  : 状态码描述
 */
- (void)unionpayResult:(NSDictionary *)result{
    
    isOrientation = YES;
    if(self.bounds.size.height > self.bounds.size.width){
        
        
        UIWindow *window = [[[UIApplication sharedApplication] delegate] window];
        UIViewController *oldRootViewClr = [window rootViewController];
        
        [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeLeft animated:NO];
        
        oldRootViewClr.view.transform = CGAffineTransformMakeRotation(-M_PI/2);
        
        oldRootViewClr.view.frame = CGRectMake(0, 0, [UIScreen mainScreen].applicationFrame.size.width, [UIScreen mainScreen].applicationFrame.size.height);
    }
    
    NSLog(@"seq = %@, code = %@, resultStr = %@",[result objectForKey:DEALSEQ], [result objectForKey:RESULT_CODE], [result objectForKey:RESULT_STR]);
    
    UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:[result objectForKey:DEALSEQ]
                                                         message:[NSString stringWithFormat:@"demo提示:%@",[result objectForKey:RESULT_STR]]
                                                        delegate:nil
                                               cancelButtonTitle:[result objectForKey:RESULT_CODE]
                                               otherButtonTitles:nil];
    [alertView show];
}

//支付状态点击
/*
 select : @"success" 点击支付成功
 @"fail" 点击支付失败
 seq    : dealseq
 */
- (void)payStateClick:(NSDictionary *)stateMap{
    
    NSLog(@"select = %@, dealseq = %@", [stateMap objectForKey:STATE_SELECT], [stateMap objectForKey:DEALSEQ]);
    
    UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:[stateMap objectForKey:STATE_SELECT]
                                                         message:[stateMap objectForKey:DEALSEQ]
                                                        delegate:nil
                                               cancelButtonTitle:@"确定"
                                               otherButtonTitles:nil];
    [alertView show];
    
}

-(void)userPayCardSuccess{
    UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
                                                         message:@"用户卡类支付提示成功"
                                                        delegate:nil
                                               cancelButtonTitle:@"确定"
                                               otherButtonTitles:nil];
    [alertView show];
}

//支付宝 '服务器' 回调通知
- (void)checkResult:(CHECK)result{
    
    [self checkCode:result];
}

//是否使用银联支付 (在其中处理屏幕横屏时, 将屏幕竖起)
-(void)userSelectUnionpay{
    
    isOrientation = NO;
    if(self.bounds.size.width > self.bounds.size.height){
        
        
        UIWindow *window = [[[UIApplication sharedApplication] delegate] window];
        UIViewController *oldRootViewClr = [window rootViewController];
        
        [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationPortrait animated:NO];
        
        oldRootViewClr.view.transform = CGAffineTransformIdentity;
        
        oldRootViewClr.view.frame = CGRectMake(0, 0, [UIScreen mainScreen].applicationFrame.size.width, [UIScreen mainScreen].applicationFrame.size.height);
    }
}

//状态码对应
- (void)checkCode:(CHECK)result{
    
    if(SERVICE_CHECK == result){
        
        UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
                                                             message:@"等待支付结果"
                                                            delegate:nil
                                                   cancelButtonTitle:@"确定"
                                                   otherButtonTitles:nil];
        [alertView show];
    }else if(PAY_SUCCESS == result){
        
        UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
                                                             message:@"支付成功"
                                                            delegate:nil
                                                   cancelButtonTitle:@"确定"
                                                   otherButtonTitles:nil];
        [alertView show];
    }else if (PAY_FAILE == result){
        UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
                                                             message:@"支付失败"
                                                            delegate:nil
                                                   cancelButtonTitle:@"确定"
                                                   otherButtonTitles:nil];
        [alertView show];
    }else if(PAY_ERROR == result){
        UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
                                                             message:@"支付异常"
                                                            delegate:nil
                                                   cancelButtonTitle:@"确定"
                                                   otherButtonTitles:nil];
        [alertView show];
    }
    
}

- (void) userCloseView{
    
    UIAlertView * alertView = [[UIAlertView alloc] initWithTitle:@"提示"
                                                         message:@"用户关闭了支付"
                                                        delegate:nil
                                               cancelButtonTitle:@"确定"
                                               otherButtonTitles:nil];
    [alertView show];
}

-(void) layoutSubviews
{
    [KY_PaySDK instance].frame = BOUNDS;
}

- (void) userDoAlipaywap
{
#ifdef _DEBUG
    NSLog( @"userDoAlipaywap" );
#endif
}

- (void) OnRelease
{
    [KY_PaySDK instance].ky_delegate = nil;
}

@end
