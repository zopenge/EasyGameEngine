//! @file     iosIAPManager.h
//! @author   foreven
//! @version  1.0.0.621
//! @date     2013/09/24

#pragma once

namespace EGE
{
    
//----------------------------------------------------------------------------
// iosIAPManager
//----------------------------------------------------------------------------
    
class iosIAPManager : public TObject< IIAPManager >
{
private:
    struct NSIAPManagerHandle;
public:
    iosIAPManager( );
    virtual ~iosIAPManager( );
    
private:
    NSIAPManagerHandle*		mNSIAPManagerHandle;
	IIAPManagerNotifierRef	mIIAPManagerNotifier;
    _ubool                  mInitIAPManager;

public:
    virtual _void       Tick( _time_t tick, _dword elapse ) override;
    
// IIAPManager Interface
    virtual _void       SetTransactionKey( UStringPtr transaction_key ) override;
    virtual _void       DeleteTransactionInfo( ) override;
    virtual UStringR     GetTransactionInfo( ) override;
    virtual UStringR     GetProductID( ) override;
    
    virtual _void       SetTimeout( _dword timeout );

    virtual IIAPManagerNotifierRef SetNotifier( IIAPManagerNotifier* notifier ) override;
	virtual IIAPManagerNotifierRef GetNotifier( ) override;

    virtual _void       InitIAPManager( ) override;
    virtual _void       GetProductsInfo( const UStringArray& products ) override;
    virtual _ubool      CanMakePurchases( ) override;
    virtual _void       PurchaseProduct( UStringPtr productid ) override;
};
    
//----------------------------------------------------------------------------
// iosIAPManager Implementation
//----------------------------------------------------------------------------
    
}