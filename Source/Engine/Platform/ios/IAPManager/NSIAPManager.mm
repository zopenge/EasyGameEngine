//! @file     NSIAPManager.mm
//! @author   foreven
//! @version  1.1
//! @date     2013/09/24
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// NSIAPManager Implementation
//----------------------------------------------------------------------------

@implementation NSIAPManager

- (void)SetTimeout: (EGE::_dword) timeout
{
    mTimeout = timeout;
}

- (void)Tick: (EGE::_dword) tick
{
    if ( mProductsRequest != nil )
    {
        mCurrentTick += tick;
        if ( mCurrentTick >= mTimeout )
        {
            mProductsRequest.delegate = nil;
            mProductsRequest = nil;
            
#ifdef _DEBUG
            NSLog(@"getProductsInfo timeout" );
#endif
            if ( mIAPManagerDelegate->GetNotifier( ).IsValid( ) )
                mIAPManagerDelegate->GetNotifier( )->OnGetProductsInfo( "" );
            
        }
    }
}

- (void)setIAPManagerDelegate: (EGE::iosIAPManager*) iapmanager_delegate
{
    mIAPManagerDelegate = iapmanager_delegate;
}

//StoreManager在初始化时调用如下方法，完成SKProductsRequest的初始化
- (void)getProductsInfo: (const EGE::UStringArray&) productids
{
    NSMutableSet* product_mutable_set = [[NSMutableSet alloc] init];
    for ( EGE::_dword i = 0; i < productids.Number( ); ++ i )
    {
        NSString* product_id = [NSString stringWithUTF8String:productids[i].Str( )];
        [product_mutable_set addObject:product_id];
    }
    
    NSSet* productIdentifiers = [NSSet setWithSet:product_mutable_set];
    
    mProductsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:productIdentifiers];
    mProductsRequest.delegate = self;
    [mProductsRequest start];
    // 我们将发布在请求对象的委托回调
    
    //mProductsRequest.delegate = nil;

    mCurrentTick = 0;
}

#pragma mark -
#pragma mark SKProductsRequestDelegate methods
//本地化 价格
- (NSString *)GetLocalizedPrice:(SKProduct*) product
{
    NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];
    [numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
    [numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    [numberFormatter setLocale:product.priceLocale];
    NSString *formattedString = [numberFormatter stringFromNumber:product.price];
    return formattedString;
}

//我们能够得到其返回的一些product信息，如可以购买成功的Product id序列:response.products；购买失败的序列：response.invalidProductIdentifiers。
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    IMarkupLangFileRef jsonfile = GetInterfaceFactory( )->CreateJSONFile( );
    IMarkupLangElement* productlist_node = jsonfile->GetRootElement( )->InsertChildArrayObj( L"productlist" );
    
    //可以购买的product集合:
    NSArray *products = response.products;
    for ( int i = 0; i < [products count]; ++ i )
    {
        SKProduct* product = [products objectAtIndex:i];
        
#ifdef _DEBUG
        NSLog(@"Product title: %@" , product.localizedTitle);
        NSLog(@"Product description: %@" , product.localizedDescription);
        NSLog(@"Product price: %@" , [self GetLocalizedPrice:product]);
        NSLog(@"Product id: %@" , product.productIdentifier);
#endif
        UString product_localprice = [[self GetLocalizedPrice:product] cStringUsingEncoding:NSUTF8StringEncoding];
        UString product_id = [product.productIdentifier cStringUsingEncoding:NSUTF8StringEncoding];
        
        IMarkupLangElement* product_node = productlist_node->AppendElementOfArrayObj( );
        product_node->SetAttributeString( L"price", product_localprice );
        product_node->SetAttributeString( L"id", product_id );
    }
    
    for ( NSString *invalidProductId in response.invalidProductIdentifiers )
    {
#ifdef _DEBUG
        NSLog(@"Invalid product id: %@" , invalidProductId);
#endif
    }
    
    // finally release the reqest we alloc/init’ed in requestProUpgradeProductData
    // 最后释放在requestProUpgradeProductData reqest我们的alloc /初始化“版
    mProductsRequest = nil;
	
	WString dump_string = jsonfile->GetRootElement()->DumpToString( );
    AString json_astring = AString( ).FromString( dump_string );
    
    if ( mIAPManagerDelegate->GetNotifier( ).IsValid( ) )
        mIAPManagerDelegate->GetNotifier( )->OnGetProductsInfo( json_astring );
}

//
// call this method once on startup  一旦启动时调用此方法
//
- (void)loadStore
{
    //创建一个StoreObserver类来监控购买流程，它要实现协议：SKPaymentTransactionObserver。
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    
    mTimeout = 10000;
    mCurrentTick = 0;
    mProductsRequest = nil;
}

- (void)closeStore
{
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
}

//
// call this before making a purchase 在购买前调用此方法
//
- (BOOL)canMakePurchases
{
    return [SKPaymentQueue canMakePayments];
}


//购买一个产品,传入我们要购买的product id即可(如果是一次购买多个，可以使用SKMutablePayment)：
- (void)purchaseProduct: (EGE::UStringPtr) productid
{
    
    SKPayment *payment = [SKPayment paymentWithProductIdentifier:[NSString stringWithUTF8String:productid.Str( )]];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}

#pragma -
#pragma Purchase helpers

//
// saves a record of the transaction by storing the receipt to disk
- (NSString *)encodebase64:(const uint8_t *)input length:(NSInteger)length {
    static char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    
    NSMutableData *data = [NSMutableData dataWithLength:((length + 2) / 3) * 4];
    uint8_t *output = (uint8_t *)data.mutableBytes;
    
    for (NSInteger i = 0; i < length; i += 3) {
        NSInteger value = 0;
        for (NSInteger j = i; j < (i + 3); j++) {
            value <<= 8;
            
            if (j < length) {
                value |= (0xFF & input[j]);
            }
        }
        
        NSInteger index = (i / 3) * 4;
        output[index + 0] =                    table[(value >> 18) & 0x3F];
        output[index + 1] =                    table[(value >> 12) & 0x3F];
        output[index + 2] = (i + 1) < length ? table[(value >> 6)  & 0x3F] : '=';
        output[index + 3] = (i + 2) < length ? table[(value >> 0)  & 0x3F] : '=';
    }
    
    return [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
}

//交易记录保存到磁盘存储收据
- (void)recordTransaction:(SKPaymentTransaction *)transaction
{
#ifdef _DEBUG
    NSLog(@"NSIAPManager recordTransaction transaction.payment.productIdentifier: %@" , transaction.payment.productIdentifier);
    NSString *encodedString = [self encodebase64:(const uint8_t*)transaction.transactionReceipt.bytes length:transaction.transactionReceipt.length];
    NSLog(@"transaction.transactionReceipt: %@", encodedString );
#endif
    // save the transaction receipt to disk
    [[NSUserDefaults standardUserDefaults] setValue:transaction.transactionReceipt forKey:[NSString stringWithUTF8String:mTransactionKey.Str( )] ];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    NSString *key = [NSString stringWithUTF8String:mTransactionKey.Str( )];
    
    NSString *appleIdKey = [NSString stringWithFormat:@"%@%@",key,@"appleID"];
    
    [[NSUserDefaults standardUserDefaults] setValue:transaction.payment.productIdentifier forKey:appleIdKey];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (void)setTransactionKey: (EGE::UStringPtr) transaction_key
{
    mTransactionKey = transaction_key;
}

- (void)deleteTransactionInfo
{
    NSString* transaction_key   = [NSString stringWithUTF8String:mTransactionKey.Str( )];
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:transaction_key];
    NSString *key = [NSString stringWithUTF8String:mTransactionKey.Str( )];
    
    NSString *appleIdKey = [NSString stringWithFormat:@"%@%@",key,@"appleID"];
    
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:appleIdKey];
}

- (EGE::UString)getTransactionInfo
{
    NSString* transaction_key   = [NSString stringWithUTF8String:mTransactionKey.Str( )];
    NSData* ns_transaction_object = [[NSUserDefaults standardUserDefaults] objectForKey:transaction_key];
    
    if ( ns_transaction_object == nil )
        return UString( "" );
    
    NSString *encodedString = [self encodebase64:(const uint8_t*)ns_transaction_object.bytes length:ns_transaction_object.length];
    
    UString transaction_object = [encodedString cStringUsingEncoding:NSUTF8StringEncoding];
    
    return transaction_object;
}

- (EGE::UString)getProductID
{
    NSString *key = [NSString stringWithUTF8String:mTransactionKey.Str( )];
    
    NSString *appleIdKey = [NSString stringWithFormat:@"%@%@",key,@"appleID"];
    NSString* ns_transaction_object = [[NSUserDefaults standardUserDefaults] objectForKey:appleIdKey];
    
    if ( ns_transaction_object == nil || [@"" isEqualToString:ns_transaction_object] )
        return UString( "" );
    
//    NSString *encodedString = [self encodebase64:(const uint8_t*)ns_transaction_object.bytes length:ns_transaction_object.length];
    
    UString transaction_object = [ns_transaction_object cStringUsingEncoding:NSUTF8StringEncoding];
    
    return transaction_object;
}

//
// removes the transaction from the queue and posts a notification with the transaction result
// 从队列中删除，职位与交易结果通知交易
- (void)finishTransaction:(SKPaymentTransaction *)transaction wasSuccessful:(BOOL)wasSuccessful
{
    // remove the transaction from the payment queue.
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    
    AString message;
    if (wasSuccessful)
    {
        // send out a notification that we’ve finished the transaction
        //发送，我们已经完成了交易的通知
        
        message = "success:";
    }
    else
    {
        // send out a notification for the failed transaction
        //发送一个失败的交易的通知
        
        message = "fail";
    }
    
    if ( mIAPManagerDelegate->GetNotifier( ).IsValid( ) )
        mIAPManagerDelegate->GetNotifier( )->OnPurchaseProduct( message ,transaction.payment.productIdentifier.UTF8String );
}

//
// called when the transaction was successful 所谓交易成功
//在响应的方法里要去除该次事物，比如在购买成功的方法里：
- (void)completeTransaction:(SKPaymentTransaction *)transaction
{
    [self recordTransaction:transaction];
    [self finishTransaction:transaction wasSuccessful:YES];
}

//
// called when a transaction has been restored and and successfully completed
// 所谓当交易已经恢复，并成功完成
- (void)restoreTransaction:(SKPaymentTransaction *)transaction
{
    [self recordTransaction:transaction.originalTransaction];
    [self finishTransaction:transaction wasSuccessful:YES];
}

//
// called when a transaction has failed
// 交易失败时调用
- (void)failedTransaction:(SKPaymentTransaction *)transaction
{
#ifdef _DEBUG
    NSLog( @"transaction.error.code: %ld", transaction.error.code );
#endif
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        // error!
        [self finishTransaction:transaction wasSuccessful:NO];
    }
    else
    {
        // this is fine, the user just cancelled, so don’t notify
        // 这是刚刚取消的用户，所以没有通知
        [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
        
        if ( mIAPManagerDelegate->GetNotifier( ).IsValid( ) )
            mIAPManagerDelegate->GetNotifier( )->OnPurchaseProduct( "cancel" ,transaction.payment.productIdentifier.UTF8String);
    }
}

#pragma mark -
#pragma mark SKPaymentTransactionObserver methods

//
// called when the transaction status is updated
//这个方法会在购买有响应的时候调用。
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
        case SKPaymentTransactionStatePurchased:
            {
                [self completeTransaction:transaction];//调用自己的购买成功的方法
            }
            break;
        case SKPaymentTransactionStateFailed:
            {
                [self failedTransaction:transaction];//调用自己的购买失败的方法
            }
            break;
        case SKPaymentTransactionStateRestored:
            {
                [self restoreTransaction:transaction];//调用自己的重新购买的方法
            }
            break;
            default:
                break;
        }
    }
}

@end
