//! @file     winShell.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// winShellTaskbar
//----------------------------------------------------------------------------

class winShellTaskbar : public IShellTaskbar
{
private:
	//!	The tray notification data
	NOTIFYICONDATAW	mData;

public:
	winShellTaskbar( );
	virtual ~winShellTaskbar( );

// IShellTaskbar Interface
public:
	virtual _ubool AddIcon( IApplication* application, _dword item_id, _dword item_icon, WStringPtr tip_message ) override;
};

//----------------------------------------------------------------------------
// winShell
//----------------------------------------------------------------------------

class winShell : public INTERFACE_OBJECT_IMPL( IShell )
{
private:
	//!	The task bar
	winShellTaskbar	mTaskbar;

public:
	winShell( );
	virtual ~winShell( );

public:
	//!	Initialize.
	//!	@param		none.
	//! @return		True indicates success false indicates failure.
	_ubool Initialize( );

// IShellLink Interface
public:
	virtual IShellTaskbar*	GetTaskbar( ) override;

	virtual _ubool			CreateFileLink( WStringPtr linktarget, WStringPtr workdir, WStringPtr linkpath, WStringPtr linkdesc, WStringPtr cmdline ) override;
};

//----------------------------------------------------------------------------
// winShell Implementation
//----------------------------------------------------------------------------

}