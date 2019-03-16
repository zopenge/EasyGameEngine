//! @file     IKYPayManager.h
//! @author   foreven
//! @version  1.0.0.621
//! @date     2013/09/25

#pragma once

namespace EGE
{
    
//----------------------------------------------------------------------------
// IKYPayManagerNotifier
//----------------------------------------------------------------------------
    
class IKYPayManagerNotifier : public IObject
{
public:
    virtual _void		OnPurchaseProduct( AStringPtr purchase_result ) PURE;
};
    
//----------------------------------------------------------------------------
// IKYPayManager
//----------------------------------------------------------------------------
    
class IKYPayManager : public IObject
{
public:
    virtual _void       Initialize( _handle application, UStringPtr appid, UStringPtr url_scheme ) PURE;
    
    virtual IKYPayManagerNotifierRef SetNotifier( IKYPayManagerNotifier* notifier ) PURE;
    virtual IKYPayManagerNotifierRef GetNotifier( ) PURE;
    
    virtual _void       PurchaseProduct( _handle application, UStringPtr uid, UStringPtr product_name, UStringPtr price, UStringPtr dealseq ) PURE;
};
    
}