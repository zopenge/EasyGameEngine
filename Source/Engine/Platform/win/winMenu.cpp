//! @file     winMenu.cpp
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// Helper Functions
//----------------------------------------------------------------------------

static _dword TranslateAlignmentFlags( _dword alignment )
{
	_dword menu_align = 0;

	// Horz or Vert alignment
	if ( ( alignment & _ALIGNMENT_HORZ_CENTER ) == _ALIGNMENT_HORZ_CENTER )
	{
		menu_align = TPM_CENTERALIGN;
	}
	else if ( ( alignment & _ALIGNMENT_VERT_CENTER ) == _ALIGNMENT_VERT_CENTER )
	{
		menu_align = TPM_VCENTERALIGN;
	}
	// Combine flags
	else
	{
		if ( alignment & _ALIGNMENT_BOTTOM )
			menu_align |= TPM_BOTTOMALIGN;
		else if ( alignment & _ALIGNMENT_RIGHT )
			menu_align |= TPM_RIGHTALIGN;
		else
			menu_align = TPM_LEFTALIGN | TPM_TOPALIGN;
	}

	return menu_align;
}

//----------------------------------------------------------------------------
// winMenu Implementation
//----------------------------------------------------------------------------

winMenu::winMenu( _ubool popup )
{
	if ( popup )
		mFlags.CombineFlags( _FLAG_IS_POPUP );

	mMenu = _null;
}

winMenu::~winMenu( )
{
	// Destroy menu
	if ( mMenu != _null )
		::DestroyMenu( mMenu );
}

_ubool winMenu::Initialize( )
{
	// Create menu
	if ( mFlags.HasFlags( _FLAG_IS_POPUP ) )
		mMenu = CreatePopupMenu( );
	else
		mMenu = CreateMenu( );

	if ( mMenu == _null )
		return _false;

	return _true;
}

_void winMenu::AddItem( _dword message, WStringPtr name )
{
	::InsertMenuW( mMenu, -1, MF_BYPOSITION, message, name.Str( ) );
}

_ubool winMenu::Show( const PointI& position, _dword alignment, const IViewBasedApp* application )
{
	if ( application == _null )
		return _false;

	// Get the window handle
	HWND hwnd = (HWND) application->GetApplicationHandle( );
	if ( hwnd == _null )
		return _false;

	// Show and track the menu
	::TrackPopupMenu( mMenu, TranslateAlignmentFlags( alignment ), position.x, position.y, 0, hwnd, _null );

	return _true;
}