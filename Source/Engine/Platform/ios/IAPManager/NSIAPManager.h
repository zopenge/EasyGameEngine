//! @file     NSEditBoxView.h
//! @author   foreven
//! @version  1.0.0.621
//! @date     2013/09/24

#pragma once

@interface NSIAPManager : NSObject< SKProductsRequestDelegate, SKPaymentTransactionObserver >
{
@private
    SKProductsRequest*      mProductsRequest;
    EGE::iosIAPManager*     mIAPManagerDelegate;
    EGE::_dword             mCurrentTick;
    EGE::_dword             mTimeout;
    EGE::UString            mTransactionKey;
}

- (void)SetTimeout: (EGE::_dword) timeout;
- (void)Tick: (EGE::_dword) tick;

- (void)setIAPManagerDelegate: (EGE::iosIAPManager*) iapmanager_delegate;
- (void)loadStore;
- (void)closeStore;
- (void)getProductsInfo: (const EGE::UStringArray&) productids;
- (BOOL)canMakePurchases;
- (void)purchaseProduct: (EGE::UStringPtr) productid;

- (void)setTransactionKey: (EGE::UStringPtr) transaction_key;
- (void)deleteTransactionInfo;
- (EGE::UString)getTransactionInfo;
- (EGE::UString)getProductID;
@end