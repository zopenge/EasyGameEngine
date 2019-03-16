#include "EGEEngine.h"

//----------------------------------------------------------------------------
// iosIAPManager Implementation
//----------------------------------------------------------------------------
struct iosIAPManager::NSIAPManagerHandle
{
public:
    NSIAPManager*    mNSIAPManager;
    
public:
    NSIAPManagerHandle( )
    {
        mNSIAPManager = nil;
    }
    ~NSIAPManagerHandle( )
    {
        mNSIAPManager = nil;
    }
};

iosIAPManager::iosIAPManager( )
{
    mInitIAPManager = _false;
    mNSIAPManagerHandle    = new NSIAPManagerHandle;
}

iosIAPManager::~iosIAPManager( )
{
    if ( mInitIAPManager )
    {
        [mNSIAPManagerHandle->mNSIAPManager closeStore];
        mInitIAPManager = _false;
    }
    EGE_DELETE( mNSIAPManagerHandle );
}

_void iosIAPManager::InitIAPManager( )
{
    mNSIAPManagerHandle->mNSIAPManager  = [NSIAPManager alloc];
    [mNSIAPManagerHandle->mNSIAPManager setIAPManagerDelegate:this];
    [mNSIAPManagerHandle->mNSIAPManager loadStore];
    mInitIAPManager = _true;
}

_void iosIAPManager::GetProductsInfo( const UStringArray& products )
{
    if ( GetNet( )->GetStatus( ) == INet::_STATUS_OFFLINE )
    {
        if ( GetNotifier( ).IsValid( ) )
            GetNotifier( )->OnGetProductsInfo( "" );
        return;
    }
    
    [mNSIAPManagerHandle->mNSIAPManager getProductsInfo:products];
}

_ubool iosIAPManager::CanMakePurchases( )
{
    return [mNSIAPManagerHandle->mNSIAPManager canMakePurchases];
}

_void iosIAPManager::PurchaseProduct( UStringPtr productid )
{
    UString _productid = productid;
    if ( GetNet( )->GetStatus( ) == INet::_STATUS_OFFLINE )
    {
        if ( GetNotifier( ).IsValid( ) )
            GetNotifier( )->OnPurchaseProduct( "",_productid.Str() );
        return;
    }
    
    [mNSIAPManagerHandle->mNSIAPManager purchaseProduct:_productid];
}

IIAPManagerNotifierRef iosIAPManager::SetNotifier( IIAPManagerNotifier* notifier )
{
	mIIAPManagerNotifier = notifier;
	return mIIAPManagerNotifier;
}

IIAPManagerNotifierRef iosIAPManager::GetNotifier( )
{
	return mIIAPManagerNotifier;
}

_void iosIAPManager::SetTimeout( _dword timeout )
{
    [mNSIAPManagerHandle->mNSIAPManager SetTimeout:timeout];
}

_void iosIAPManager::Tick( _time_t tick, _dword elapse )
{
    [mNSIAPManagerHandle->mNSIAPManager Tick:elapse];
}

_void iosIAPManager::SetTransactionKey( UStringPtr transaction_key )
{
    [mNSIAPManagerHandle->mNSIAPManager setTransactionKey:transaction_key];
}

_void iosIAPManager::DeleteTransactionInfo( )
{
    [mNSIAPManagerHandle->mNSIAPManager deleteTransactionInfo];
}

UStringR iosIAPManager::GetTransactionInfo( )
{
    return [mNSIAPManagerHandle->mNSIAPManager getTransactionInfo];
}

UStringR iosIAPManager::GetProductID( )
{
     return [mNSIAPManagerHandle->mNSIAPManager getProductID];
}
