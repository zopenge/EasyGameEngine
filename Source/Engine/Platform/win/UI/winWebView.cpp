//! @file     winWebView.cpp
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

CComModule	winWebView::sComModule;
WNDCLASS	winWebView::sWindowClass		= {0};
AStringPtr	winWebView::sWindowClassName	= "EGE_winWebView";

//----------------------------------------------------------------------------
// WebBrwoser2EventListener Implementation
//----------------------------------------------------------------------------

namespace EGE
{

// http://bbs.csdn.net/topics/390149032
class WebBrwoser2EventListener : public IDispatch
{
private:
	//!	The web view
	winWebView*	mWebView;

public:
	WebBrwoser2EventListener( winWebView* web_view )
	{
		mWebView = web_view;
	}
	virtual ~WebBrwoser2EventListener( )
	{

	}

// IDispatch Interface
public: 
	STDMETHOD(QueryInterface)( REFIID riid, void **ppvObject)
	{
		HRESULT hr = E_NOINTERFACE;
		if (riid == __uuidof(IDispatch))
		{
			*ppvObject = (IDispatch*)this;
			AddRef();
			hr = S_OK;
		}
		else if (riid == __uuidof(DWebBrowserEvents2))
		{
			*ppvObject = (IDispatch*)this;
			AddRef();
			hr = S_OK;
		}

		return hr;
	}
	STDMETHODIMP_(ULONG) AddRef(void)
	{
		return 1;
	};
	STDMETHODIMP_(ULONG) Release(void)
	{
		return 1;
	}
	STDMETHOD(GetTypeInfoCount)(UINT*)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetTypeInfo)(UINT, LCID, ITypeInfo**)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR *rgszNames, UINT, LCID, DISPID *rgDispId)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(Invoke)(DISPID dispIdMember,REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS FAR* pDispParams,VARIANT FAR* pVarResult,EXCEPINFO FAR* pExcepInfo,unsigned int FAR* puArgErr)
	{
		IWebViewNotifier* notifier = mWebView->GetNotifier( );
		EGE_ASSERT( notifier != _null );

		switch ( dispIdMember )
		{
			// Page completed
			case DISPID_DOCUMENTCOMPLETE:
			{
				WStringPtr url = pDispParams->rgvarg[0].pvarVal->bstrVal;
				notifier->OnPageFinished( url );

				if ( mWebView->InitHTML( ) == _false )
					return S_FALSE;
			}
			break;

			// Page downloading
			case DISPID_PROGRESSCHANGE:
			{
				_dword cur_progress = pDispParams->rgvarg[1].lVal;
				if ( cur_progress != -1 )
				{
					_dword max_progress = pDispParams->rgvarg[0].lVal;
					_dword progress		= (_dword)(EGE_RATIO( cur_progress, max_progress ) * 100.0f);

					if ( progress != 0 )
						notifier->OnProgressChanged( progress );
				}
			}
			break;

			// Page error
			case DISPID_NAVIGATEERROR: 
			{
				const VARIANT*	vt_statuscode	= pDispParams->rgvarg[1].pvarVal;
				_dword			status_code		= vt_statuscode->lVal;

				notifier->OnReceivedError( status_code, L"", L"" );
			}
			break;

			default:
				break;
		}

		return S_OK;
	}
};

}

//----------------------------------------------------------------------------
// winWebView Implementation
//----------------------------------------------------------------------------

winWebView::winWebView( )
{
	mWindowHandle				= _null;

	mCookie						= 0;
	mConnectionPoint			= _null;
	mConnectionPointContainer	= _null;
	mEventListener				= new WebBrwoser2EventListener( this );

	mWebBrowser					= _null;

	mHTMLDoc					= _null;
	mHTMLBodyElement			= _null;
	mHTMLElement				= _null;
	mHTMLElement2				= _null;
}

winWebView::~winWebView( )
{
	if ( mConnectionPoint != _null && mCookie != 0 )
		mConnectionPoint->Unadvise( mCookie );

	if ( mConnectionPointContainer != _null )
		mConnectionPointContainer->Release( );

	EGE_DELETE( mEventListener );

	if ( mHTMLElement2 != _null )
		mHTMLElement2->Release( );

	if ( mHTMLElement != _null )
		mHTMLElement->Release( );

	if ( mHTMLBodyElement != _null )
		mHTMLBodyElement->Release( );

	if ( mHTMLDoc != _null )
		mHTMLDoc->Release( );

	if ( mWebBrowser != _null )
		mWebBrowser->Release( );

	if ( mWinContainer.IsWindow( ) )
		mWinContainer.DestroyWindow( );

	if ( mWindowHandle != _null )
		::DestroyWindow( mWindowHandle );
}

_ubool winWebView::Initialize( )
{
	// Register windows class
	sWindowClass.style			= CS_HREDRAW |  CS_VREDRAW;
	sWindowClass.lpfnWndProc	= WindowProc;
	sWindowClass.cbClsExtra		= 0;
	sWindowClass.cbWndExtra		= 0;
	sWindowClass.hInstance		= ::GetModuleHandleA( _null );
	sWindowClass.hIcon			= LoadIcon( ::GetModuleHandleA( _null ),  IDI_APPLICATION );
	sWindowClass.hCursor		= LoadCursor( NULL, IDC_ARROW );
	sWindowClass.lpszClassName	= sWindowClassName.Str( );
	RegisterClassA( &sWindowClass );

	return _true;
}

_void winWebView::Finalize( )
{
	// Unregister window class
	::UnregisterClass( sWindowClassName.Str( ), ::GetModuleHandleA( _null ) );
}

_void winWebView::CreateWindowHandle( )
{
	if ( mWindowHandle != _null )
		return;

	// We must create it in main thread
	if ( Platform::IsMainThread( ) )
	{
		// Get the parent window
		HWND parent_window = (HWND) GetMainWindowHandle( );

		// Create window handle
		mWindowHandle = CreateWindowA( sWindowClassName.Str( ), "", WS_CHILD | WS_CLIPCHILDREN, mPos.x, mPos.y, mSize.x, mSize.y, parent_window, NULL, ::GetModuleHandleA( _null ), this );
		if ( mWindowHandle != _null )
		{
			// Show window if it's set
			if ( IsShow( ) )
			{
				mWinContainer.ShowWindow( SW_SHOW );
				::ShowWindow( mWindowHandle, SW_SHOW );
			}
		}
	}
}

LRESULT winWebView::WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	// Get the web view
	winWebView* web_view = (winWebView*) ::GetWindowLong( hWnd, GWL_USERDATA );

	// Process message
	switch( message )
	{
		case WM_CREATE:
		{
			const CREATESTRUCT* createstruct = (const CREATESTRUCT*) lParam;
			EGE_ASSERT( createstruct != _null );

			// Get the self pointer
			::SetWindowLong( hWnd, GWL_USERDATA, (LONG) createstruct->lpCreateParams );

			// Get the web view
			winWebView* web_view = (winWebView*) createstruct->lpCreateParams;
			EGE_ASSERT( web_view != _null );

			// Get the client rect
			RECT client_rect;
			GetClientRect( hWnd, &client_rect );

			// Create container
			web_view->mWinContainer.Create( hWnd, client_rect, 0, WS_CHILD | WS_VISIBLE );

			// Create shell explorer
			web_view->mWinContainer.CreateControl( OLESTR( "shell.Explorer.2" ) );

			// Get web browser handle
			web_view->mWinContainer.QueryControl( __uuidof(IWebBrowser2), (void**)&web_view->mWebBrowser );
			web_view->mWebBrowser->put_Silent( _true );

			// Register event listener
			web_view->mWebBrowser->QueryInterface( IID_IConnectionPointContainer,(void**)&web_view->mConnectionPointContainer );
			web_view->mConnectionPointContainer->FindConnectionPoint( DIID_DWebBrowserEvents2, &web_view->mConnectionPoint );
			web_view->mConnectionPoint->Advise( (IUnknown*)(void*)web_view->mEventListener, &web_view->mCookie );
		}
		break;

		case WM_KEYUP:
		{
			web_view->GetNotifier( )->OnPageKeyUp( wParam );
		}
		break;

		case WM_KEYDOWN:
		{
			web_view->GetNotifier( )->OnPageKeyDown( wParam );
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
		}
		break;

		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}

_ubool winWebView::Initialize( const PointI& pos, const PointI& size )
{
	mPos	= pos;
	mSize	= size;

	return _true;
}

_ubool winWebView::InitHTML( )
{
	// Get the HTML document
	if ( mHTMLDoc == _null )
	{
		CComPtr< IDispatch > document;
		if ( FAILED( mWebBrowser->get_Document( &document ) ) )
			return _false;
		if ( FAILED( document->QueryInterface( IID_IHTMLDocument2, (void**)&mHTMLDoc ) ) )
			return _false;
	}

	// Get the HTML body element
	if ( mHTMLBodyElement == _null )
	{
		CComPtr< ::IHTMLElement > html_element; 
		if ( FAILED( mHTMLDoc->get_body( &html_element ) ) )
			return _false;
		if ( FAILED( html_element->QueryInterface( IID_IHTMLBodyElement, (void**)&mHTMLBodyElement ) ) )
			return _false;
	}

	// Get the HTML element from body
	if ( mHTMLElement == _null )
	{
		if ( FAILED( mHTMLBodyElement->QueryInterface( IID_IHTMLElement2, (void**)&mHTMLElement ) ) )
			return _false;

		CComPtr< IDispatch > document;
		if ( FAILED( mWebBrowser->get_Document( &document ) ) )
			return _false;

		CComPtr< IHTMLDocument3 > document_3;
		if ( FAILED( document->QueryInterface( IID_IHTMLDocument3, (void**)&document_3) ) )
			return _false;

		CComPtr< ::IHTMLElement > html_of_doc;
		if ( FAILED( document_3->get_documentElement( &html_of_doc ) ) )
			return _false;

		if ( FAILED( html_of_doc->QueryInterface( IID_IHTMLElement2, (void**)&mHTMLElement2 ) ) )
			return _false;
	}

	return _true;
}

_void winWebView::Show( _ubool show )
{
	if ( mIsShowableObject == show )
		return;

	BaseClass::Show( show );

	CreateWindowHandle( );

	if ( mWindowHandle != _null )
	{
		mWebBrowser->put_Visible( EGE_BOOLEAN( show ) );

		::ShowWindow( mWindowHandle, show ? SW_SHOW : SW_HIDE );
	}
}

_void winWebView::ScrollX( _int position )
{
	if ( mHTMLElement == _null || mHTMLElement2 == _null )
		return;

	mHTMLElement->put_scrollLeft( position );
	mHTMLElement2->put_scrollLeft( position );
}

_void winWebView::ScrollY( _int position )
{
	if ( mHTMLElement == _null || mHTMLElement2 == _null )
		return;

	mHTMLElement->put_scrollTop( position );
	mHTMLElement2->put_scrollTop( position );
}

_int winWebView::GetScrollPositionX( )
{
	if ( mHTMLElement == _null || mHTMLElement2 == _null )
		return 0;

	_int scroll_pos_1 = 0, scroll_pos_2 = 0;
	mHTMLElement->get_scrollLeft( (long*)&scroll_pos_1 );
	mHTMLElement2->get_scrollLeft( (long*)&scroll_pos_2 );

	return scroll_pos_1 + scroll_pos_2;
}

_int winWebView::GetScrollPositionY( )
{
	if ( mHTMLElement == _null || mHTMLElement2 == _null )
		return 0;

	_int scroll_pos_1 = 0, scroll_pos_2 = 0;
	mHTMLElement->get_scrollTop( (long*)&scroll_pos_1 );
	mHTMLElement2->get_scrollTop( (long*)&scroll_pos_2 );

	return scroll_pos_1 + scroll_pos_2;
}

_int winWebView::GetScrollWidth( )
{
	if ( mHTMLElement == _null || mHTMLElement2 == _null )
		return 0;

	_int width_1 = 0, width_2 = 0;
	mHTMLElement->get_scrollWidth( (long*)&width_1 );
	mHTMLElement2->get_scrollWidth( (long*)&width_2 );

	return width_1 + width_2;
}

_int winWebView::GetScrollHeight( )
{
	if ( mHTMLElement == _null || mHTMLElement2 == _null )
		return 0;

	_int height_1 = 0, height_2 = 0;
	mHTMLElement->get_scrollHeight( (long*)&height_1 );
	mHTMLElement2->get_scrollHeight( (long*)&height_2 );

	return height_1 + height_2;
}

_void winWebView::SetRegion( const RectI& region )
{
	if ( GetRegion( ) == region )
		return;

	BaseClass::SetRegion( region );

	CreateWindowHandle( );

	if ( mWindowHandle != _null )
	{
		mWinContainer.SetWindowPos( HWND_TOP, 0, 0, mSize.x, mSize.y, 0 );
		::SetWindowPos( mWindowHandle, HWND_TOP, mPos.x, mPos.y, mSize.x, mSize.y, 0 );
	}
}

_ubool winWebView::OpenURL( WStringPtr url_address )
{
	if ( BaseClass::OpenURL( url_address ) == _false )
		return _false;

	Refresh( );

	return _true;
}

_void winWebView::Refresh( )
{
	// Create web view window
	CreateWindowHandle( );

	// Open the web site
	if ( mWebBrowser != _null )
	{
		VARIANT l_varMyURL;
		VariantInit(&l_varMyURL);

		l_varMyURL.vt		= VT_BSTR;
		l_varMyURL.bstrVal  = SysAllocString( mURLAddress.Str( ) );
		mWebBrowser->Navigate2( &l_varMyURL, 0, 0, 0, 0 );

		VariantClear( &l_varMyURL );
	}
}