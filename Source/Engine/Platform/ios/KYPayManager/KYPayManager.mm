#include "EGEEngine.h"

//----------------------------------------------------------------------------
// iosIAPManager Implementation
//----------------------------------------------------------------------------
struct iosKYPayManager::NSKYPayViewHandle
{
public:
    NSKYPayView*    mNSKYPayView;
public:
    NSKYPayViewHandle( )
    {
        mNSKYPayView = nil;
    }
    ~NSKYPayViewHandle( )
    {
        if ( mNSKYPayView != nil )
            [mNSKYPayView OnRelease];
        
        mNSKYPayView = nil;
    }
};


iosKYPayManager::iosKYPayManager( )
{
    mNSKYPayViewHandle    = new NSKYPayViewHandle;
}

iosKYPayManager::~iosKYPayManager( )
{
    EGE_DELETE( mNSKYPayViewHandle );
}

_void iosKYPayManager::Initialize( _handle application, UStringPtr appid, UStringPtr url_scheme )
{
    NSApplication* ns_app = (__bridge NSApplication*) application;
    
    mAppID = appid;
 
    mNSKYPayViewHandle->mNSKYPayView = [[NSKYPayView alloc] init];
    [mNSKYPayViewHandle->mNSKYPayView setControllerAndUrlScheme:ns_app.viewController urlScheme:url_scheme];
}

IKYPayManagerNotifierRef iosKYPayManager::SetNotifier( IKYPayManagerNotifier* notifier )
{
    mKYPayManagerNotifier = notifier;
	return mKYPayManagerNotifier;
}

IKYPayManagerNotifierRef iosKYPayManager::GetNotifier( )
{
    return mKYPayManagerNotifier;
}

_void iosKYPayManager::PurchaseProduct( _handle application, UStringPtr uid, UStringPtr product_name, UStringPtr price, UStringPtr dealseq )
{
    NSApplication* ns_app = (__bridge NSApplication*) application;
    
    [mNSKYPayViewHandle->mNSKYPayView PachaseProduct:mAppID uid:uid product_name:product_name price:price dealseq:dealseq parentview:ns_app.view];
}
