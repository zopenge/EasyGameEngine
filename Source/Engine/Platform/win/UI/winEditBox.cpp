//! @file     winEditBox.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// winEditBox-Windows Implementation
//----------------------------------------------------------------------------

static winEditBox*	sWinEditBox		= _null;
static HWND			sEditHwnd		= _null;
static WNDPROC		sEditWndProc	= _null;

static _void winEditBoxCloseWindow( )
{
	if ( sEditHwnd != _null )
	{
		::SetWindowTextW( (HWND) sEditHwnd, L"" );
		::SetWindowLong( sEditHwnd, GWL_WNDPROC, 0 );
		::ShowWindow( sEditHwnd, SW_HIDE );
		::DestroyWindow( sEditHwnd );

		sEditHwnd = _null;
		sEditWndProc = _null;
	}
}

static _void winEditBoxCancelEdit( )
{
	if ( sWinEditBox != _null )
	{
		sWinEditBox->mHandleEventFunc.Invoke( IEditBox::_EVENT_CANCEL, "" );
		sWinEditBox = _null;
	}

	winEditBoxCloseWindow( );
}

static _void winEditBoxReturnEdit( )
{
	if ( sWinEditBox != _null )
	{
		if ( sEditHwnd != _null )
		{
			_charw text[4096];
			::GetWindowTextW( (HWND) sEditHwnd, text, 4096 );
			sWinEditBox->mHandleEventFunc.Invoke( IEditBox::_EVENT_RETURN, UString( ).FromString( WString( text ) ) );
		}		
		sWinEditBox = _null;
	}

	winEditBoxCloseWindow( );
}

static LRESULT CALLBACK EditCallBackProcedure( HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	switch ( msg )
	{
		case WM_DESTROY:
		case WM_KILLFOCUS:
		{
			winEditBoxCancelEdit( );
		}
		return 0;

		case WM_CHAR:
		{
			switch ( wparam )
			{
				case VK_ESCAPE:
				{
					winEditBoxCancelEdit( );
				}
				return 0;

				case VK_RETURN:
				{
					winEditBoxReturnEdit( );
				}
				return 0;

				default:
					break;
			}
		}
		break;

		default:
			break;
	}

	return ::CallWindowProc( sEditWndProc, hWnd, msg, wparam, lparam );
}

//----------------------------------------------------------------------------
// winEditBox Implementation
//----------------------------------------------------------------------------

winEditBox::winEditBox( )
{
	
}

winEditBox::~winEditBox( )
{
}

_ubool winEditBox::Open( _INPUT_TYPE input_type, UStringPtr text, UStringPtr defaulttext, _dword max_length, const RectF& region )
{
	return Open( input_type, WString( ).FromString( text ), WString( ).FromString( defaulttext ), max_length, region );
}

_ubool winEditBox::Open( _INPUT_TYPE input_type, WStringPtr text, WStringPtr defaulttext, _dword max_length, const RectF& region )
{
	sWinEditBox = this;

	if ( sEditHwnd == _null )
	{
		_dword edit_style = WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL;
		switch ( input_type )
		{
			case IEditBox::_INPUT_TYPE_NUMBER_PAD:
			case IEditBox::_INPUT_TYPE_PHONE_PAD:
				edit_style |= ES_NUMBER;
				break;

			case IEditBox::_INPUT_TYPE_PASSWORD:
				edit_style |= ES_PASSWORD;
				break;

			default:
				break;
		}

		sEditHwnd = ::CreateWindowExW( WS_EX_CLIENTEDGE, L"EDIT", L"", edit_style, (_int) region.l, (_int) region.t, (_int) region.GetWidth( ), (_int) region.GetHeight( ), (HWND) gMainWindowHandle, _null, _null, _null );
		sEditWndProc = ( WNDPROC ) ::SetWindowLongPtr( (HWND) sEditHwnd, GWL_WNDPROC, (LONG_PTR) &EditCallBackProcedure );
		HFONT hFont = ::CreateFontW( Math::Max<_dword>( 4, (_int) region.GetHeight( ) - 8 ), 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"simhei" );
		::SendMessageW( sEditHwnd, WM_SETFONT, WPARAM( hFont ), TRUE );
	}
	
	if ( sEditHwnd != _null )
	{
		::SendMessageW( sEditHwnd, EM_SETLIMITTEXT, WPARAM( max_length ), 0 );
		::SetWindowTextW( (HWND) sEditHwnd, text.Str( ) );
		::SetFocus( (HWND) sEditHwnd );
	}

	return _true;
}

_void winEditBox::Close( )
{
	winEditBoxCancelEdit( );
}

_void winEditBox::Commit( )
{
	winEditBoxReturnEdit( );
}