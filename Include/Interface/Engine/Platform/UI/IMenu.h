//! @file     IMenu.h
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IMenu
//----------------------------------------------------------------------------

class IMenu : public IObject
{
public:
	//!	Add item.
	//!	@param		message		The message ID.
	//!	@param		name		The item name.
	//! @return		none.
	virtual _void AddItem( _dword message, WStringPtr name ) PURE;

	//!	Show the menu.
	//!	@remark		This function will block procession until the menu's item is selected.
	//!	@param		position	The position.
	//!	@param		alignment	The alignment flags.
	//!	@param		application	The viewbased application what will receive all messages from the menu.
	//! @return		True indicates success false indicates failure.
	virtual _ubool Show( const PointI& position, _dword alignment, const IViewBasedApp* application ) PURE;
};

}