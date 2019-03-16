//! @file     IShell.h
//! @author   LiCode
//! @version  1.0.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IShellTaskbar
//----------------------------------------------------------------------------

class IShellTaskbar
{
public:
	//!	Adds an icon to the status area.
	//!	@param		application		The application.
	//!	@param		item_id			The icon unique ID.
	//!	@param		item_icon		The icon resource ID.
	//!	@param		tip_mesage		The icon tip message.
	//! @return		True indicates success false indicates failure.
	virtual _ubool AddIcon( IApplication* application, _dword item_id, _dword item_icon, WStringPtr tip_message ) PURE;
};

//----------------------------------------------------------------------------
// IShell
//----------------------------------------------------------------------------

class IShell : public IObject
{
public:
	//!	Get the task bar interface.
	//!	@param		none.
	//!	@return		The task bar interface.
	virtual IShellTaskbar* GetTaskbar( ) PURE;

	//!	Create file link.
	//!	@param		linktarget		The link file target file name.
	//!	@param		workdir			The working directory.
	//!	@param		linkpath		The save link path.
	//!	@param		linkdesc		The link description.
	//!	@param		cmdline			The command line of creation.
	//! @return		True indicates success false indicates failure.
	virtual _ubool CreateFileLink( WStringPtr linktarget, WStringPtr workdir, WStringPtr linkpath, WStringPtr linkdesc, WStringPtr cmdline ) PURE;
};

}