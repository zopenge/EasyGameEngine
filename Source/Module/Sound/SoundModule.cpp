//! @file     SoundModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

//----------------------------------------------------------------------------
// SoundModule Implementation
//----------------------------------------------------------------------------

SoundModule::SoundModule( ) : BaseClass( L"Sound", Version( SOUND_FILEVER ) )
{
	mSoundResourceManager = _null;

	// Set the default options
	mSoundOptions.CombineFlags( _SOUND_OPTION_PAUSE_ALL_WHEN_APP_PAUSE );
}

SoundModule::~SoundModule( )
{
	Finalize( );

	GetModuleManager( )->UnregisterModule( this );
}

_ubool SoundModule::CreateDynamicSHI( )
{
#if (_USE_OPENAL_ == 1)
	mDynamicSHI = new ALDrv( );
#elif (_USE_OPENSL_ == 1)
	mDynamicSHI = new SLDrv( );
#elif (_USE_PPB_ == 1)
	mDynamicSHI = new PPBDrv( );
#else
	mDynamicSHI = &sNullDynamicSHI;
#endif

	// Initialize dynamic SHI driver
	gDynamicSHI = mDynamicSHI.GetPtr( );
	return gDynamicSHI->Initialize( );
}

_ubool SoundModule::CreateResourceManager( )
{
	mSoundResourceManager = new SoundResourceManager( );
	if ( mSoundResourceManager->Initialize( ) == _false )
		return _false;

	gSoundResourceManager = mSoundResourceManager;

	return _true;
}

_ubool SoundModule::Initialize( )
{
	WLOG_TRACE( L"Create sound module ..." );

	// Create SHI driver
	if ( CreateDynamicSHI( ) == _false )
	{
		WLOG_WARNING( L"Create DynamicSHI failed" );
		return _false;
	}

	// Create resource manager
	if ( CreateResourceManager( ) == _false )
	{
		WLOG_ERROR( L"Create sound resource manager failed" );
		return _false;
	}

	// Initialize the listener
	gDynamicSHI->SetListenerPosition( Vector3::cOrigin );
	gDynamicSHI->SetListenerVelocity( Vector3::cOrigin );
	gDynamicSHI->SetListenerOrientation( - Vector3::cZAxis, Vector3::cYAxis );

	WLOG_TRACE( L"Create sound module DONE" );

	return _true;
}

_void SoundModule::Finalize( )
{
	WLOG_TRACE( L"Release sound module ..." );

	// Release resource manager
	EGE_RELEASE( mSoundResourceManager );

	// Release global resources
	mDynamicSHI.Clear( );

	WLOG_TRACE( L"Release sound module DONE" );

	// Clear global module
	gDynamicSHI				= &NullSound::GetInstance( ).GetDynamicSHI( );
	gSoundResourceManager	= &NullSound::GetInstance( ).GetSoundResourceManager( );
	gSoundModule			= &NullSound::GetInstance( ).GetSoundModule( );
}

_void SoundModule::Tick( _dword limited_elapse, _dword elapse )
{
	mSoundResourceManager->Tick( limited_elapse, elapse );
}

_void SoundModule::HandleEvent( EventBase& event )
{
	switch ( event.mEventID )
	{
		case _EVENT_ENTER_BACKGROUND:
		case _EVENT_ACTIVITY_PAUSE:
		{
			if ( IsEnableOptions( _SOUND_OPTION_PAUSE_ALL_WHEN_APP_PAUSE ) )
				mSoundResourceManager->Pause( );
		}
		break;

		case _EVENT_ENTER_FOREGROUND:
		case _EVENT_ACTIVITY_RESUME:
		{
			if ( IsEnableOptions( _SOUND_OPTION_PAUSE_ALL_WHEN_APP_PAUSE ) )
				mSoundResourceManager->Resume( );
		}
		break;

		default:
			break;
	}
}

_void SoundModule::EnableOptions( _dword options, _ubool enable )
{
	mSoundOptions.EnableFlags( options, enable );
}

_ubool SoundModule::IsEnableOptions( _dword options ) const
{
	return mSoundOptions.HasFlags( options, _true );
}