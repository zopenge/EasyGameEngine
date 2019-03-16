#include "EGEEngine.h"

//----------------------------------------------------------------------------
// iosEditBox Internal Implementation
//----------------------------------------------------------------------------

struct iosEditBox::NSEditBoxViewManager
{
    NSEditBoxView*  mNSEditBoxView;

    NSEditBoxViewManager( )
    {
        mNSEditBoxView = nil;
    }
    ~NSEditBoxViewManager( )
    {
        if ( mNSEditBoxView != nil )
        {
            [mNSEditBoxView destroyView];
        }
        mNSEditBoxView = nil;
    }
};

//----------------------------------------------------------------------------
// iosEditBox Implementation
//----------------------------------------------------------------------------

iosEditBox::iosEditBox( )
{
    mNSEditBoxViewManager = new NSEditBoxViewManager;
}

iosEditBox::~iosEditBox( )
{
    EGE_DELETE( mNSEditBoxViewManager );
}

_ubool iosEditBox::Open( _INPUT_TYPE input_type, UStringPtr text, UStringPtr defaulttext, _dword max_length, const RectF& region )
{
    NSApplication* ns_app = (__bridge NSApplication*) GetMainViewBasedApp( )->GetApplicationHandle( );
    
    if ( mNSEditBoxViewManager->mNSEditBoxView == nil )
    {
        mNSEditBoxViewManager->mNSEditBoxView = [[NSEditBoxView alloc] initWithFrame:CGRectMake( 0.0, 0.0, ns_app.view.bounds.size.width, ns_app.view.bounds.size.height)];
    }
    
	[mNSEditBoxViewManager->mNSEditBoxView createTextField:input_type inittext:text default_text:defaulttext edit_delegate:this parent_view:ns_app.view max_length:max_length];
    
    return _true;
}

_ubool iosEditBox::Open( _INPUT_TYPE input_type, WStringPtr text, WStringPtr defaulttext, _dword max_length, const RectF& region )
{
	return Open( input_type, UString( ).FromString( text ), UString( ).FromString( defaulttext ), max_length );
}

_void iosEditBox::Close( )
{
    [mNSEditBoxViewManager->mNSEditBoxView cancelTextField];
}

_void iosEditBox::Commit( )
{
	
}
