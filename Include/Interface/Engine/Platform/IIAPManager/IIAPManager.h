//! @file     IIAPManager.h
//! @author   foreven
//! @version  1.0.0.621
//! @date     2013/09/25

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IIAPManagerNotifier
//----------------------------------------------------------------------------

class IIAPManagerNotifier : public IObject
{
public:
	virtual _void		OnGetProductsInfo( AStringPtr products_info ) PURE;
	virtual _void		OnPurchaseProduct( AStringPtr purchase_result , AStringPtr product_id) PURE;
};

//----------------------------------------------------------------------------
// IIAPManager
//----------------------------------------------------------------------------

class IIAPManager : public IObject
{
public:
    virtual _void       SetTransactionKey( UStringPtr transaction_key ) PURE;
    virtual _void       DeleteTransactionInfo( ) PURE;
    virtual UStringR     GetTransactionInfo( ) PURE;
    virtual UStringR     GetProductID( ) PURE;
    
    virtual _void       SetTimeout( _dword timeout ) PURE;
    
	virtual IIAPManagerNotifierRef SetNotifier( IIAPManagerNotifier* notifier ) PURE;
	virtual IIAPManagerNotifierRef GetNotifier( ) PURE;

	virtual _void       InitIAPManager( ) PURE;
    virtual _void       GetProductsInfo( const UStringArray& products ) PURE;
    virtual _ubool      CanMakePurchases( ) PURE;
    virtual _void       PurchaseProduct( UStringPtr productid ) PURE;
    
};

}