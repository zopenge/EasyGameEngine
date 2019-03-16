//! @file     KYPayManager.h
//! @author   foreven
//! @version  1.0.0.621
//! @date     2013/09/24

#pragma once

namespace EGE
{
    
//----------------------------------------------------------------------------
// iosKYPayManager
//----------------------------------------------------------------------------
    
class iosKYPayManager : public TObject< IKYPayManager >
{
private:
    struct NSKYPayViewHandle;
public:
    iosKYPayManager( );
    virtual ~iosKYPayManager( );
        
private:
    NSKYPayViewHandle*          mNSKYPayViewHandle;
    IKYPayManagerNotifierRef	mKYPayManagerNotifier;
    UString                     mAppID;
        
public:
    // IKYPayManager Interface
    virtual _void               Initialize( _handle application, UStringPtr appid, UStringPtr url_scheme ) override;
    
    virtual IKYPayManagerNotifierRef SetNotifier( IKYPayManagerNotifier* notifier ) override;
    virtual IKYPayManagerNotifierRef GetNotifier( ) override;
    
    virtual _void               PurchaseProduct( _handle application, UStringPtr uid, UStringPtr product_name, UStringPtr price, UStringPtr dealseq ) override;
};

    
}