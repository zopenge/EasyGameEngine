//! @file     StorageModule.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StorageModule
//----------------------------------------------------------------------------

class StorageModule : public INTERFACE_MODULE_IMPL( IStorageModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( IStorageModule ) BaseClass;

private:
	//!	The current working directory
	WString		mWorkingDir;

	//!	The current working archive
	IArchiveRef	mWorkingArchive;

private:
	_ubool SetWorkingDirectory( WStringPtr working_dir, _ubool refresh_working_dir );

public:
	StorageModule( );
	virtual ~StorageModule( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr working_dir );
	//!	Finalize.
	_void Finalize( );

// IObject Interface
public:
	virtual _void		Tick( _time_t tick, _dword elapse ) override;

// IModule Interface
public:
	virtual _void		HandleEvent( EventBase& event ) override;

// IStorageModule Interface
public:
	virtual WStringPtr	GetWorkingDirectory( ) const override;
	virtual _ubool		SetWorkingDirectory( WStringPtr working_dir ) override;

	virtual _ubool		AddPatchDirectory( WStringPtr patch_dir ) override;
	virtual _ubool		RemovePatchDirectory( WStringPtr patch_dir ) override;

	virtual IArchive*	GetWorkingArchive( ) override;
};

}
