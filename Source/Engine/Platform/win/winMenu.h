//! @file     winMenu.h
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winMenu
//----------------------------------------------------------------------------

class winMenu : public INTERFACE_OBJECT_IMPL( IMenu )
{
public:
	//!	The flags
	enum _FLAG
	{
		//!	It's popup menu
		_FLAG_IS_POPUP	= 1 << 0,
	};

private:
	//!	The flags
	FlagsObject	mFlags;
	//!	The menu handle
	HMENU		mMenu;

public:
	winMenu( _ubool popup );
	virtual ~winMenu( );

public:
	//!	Initialize.
	//!	@param		none.
	//! @return		True indicates success false indicates failure.
	_ubool Initialize( );

// IMenu Interface
public:
	virtual _void	AddItem( _dword message, WStringPtr name ) override;

	virtual _ubool	Show( const PointI& position, _dword alignment, const IViewBasedApp* application ) override;
};

//----------------------------------------------------------------------------
// winMenu Implementation
//----------------------------------------------------------------------------

}