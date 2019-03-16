//! @file     SoundModule.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// SoundModule
//----------------------------------------------------------------------------

class SoundModule : public INTERFACE_MODULE_IMPL( ISoundModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( ISoundModule ) BaseClass;

private:
	//!	The dynamic SHI
	IDynamicSHIPassRef		mDynamicSHI;

	//!	The sound options
	FlagsObject				mSoundOptions;

	//!	The sound resource manager
	SoundResourceManager*	mSoundResourceManager;

private:
	//!	Create dynamic SHI.
	_ubool CreateDynamicSHI( );
	//!	Create resource manager.
	_ubool CreateResourceManager( );

public:
	SoundModule( );
	virtual ~SoundModule( );

public:
	//!	Initialize.
	_ubool Initialize( );
	//!	Finalize.
	_void Finalize( );

// IModule Interface
public:
	virtual _void	Tick( _dword limited_elapse, _dword elapse ) override;

	virtual _void	HandleEvent( EventBase& event ) override;

// ISoundModule Interface
public:
	virtual _void	EnableOptions( _dword options, _ubool enable ) override;
	virtual _ubool	IsEnableOptions( _dword options ) const override;
};

}