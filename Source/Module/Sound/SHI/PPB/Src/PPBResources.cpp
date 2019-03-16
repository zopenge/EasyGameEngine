//! @file     ALResources.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGESound.h"

#if (_USE_OPENAL_ == 1)

//----------------------------------------------------------------------------
// AL-Resources Implementation
//----------------------------------------------------------------------------

_void EGE::GenBuffer( ResourceSHI* buffer, ALuint& resource )
{
	ALResourceManager::GetInstance( ).GenBuffer( static_cast< BufferSHI* >( buffer ), resource );
}

_void EGE::DelBuffer( ALuint resource )
{
	ALResourceManager::GetInstance( ).DelBuffer( resource );
}

BufferSHI* EGE::FindBuffer( ALuint resource )
{
	return ALResourceManager::GetInstance( ).FindBuffer( resource );
}

_void EGE::GenSource( ResourceSHI* source, ALuint& resource )
{
	ALResourceManager::GetInstance( ).GenSource( static_cast< SourceSHI* >( source ), resource );
}

_void EGE::DelSource( ALuint resource )
{
	ALResourceManager::GetInstance( ).DelSource( resource );
}

SourceSHI* EGE::FindSource( ALuint resource )
{
	return ALResourceManager::GetInstance( ).FindSource( resource );
}

_void EGE::GenEffect( ResourceSHI* effect, ALuint& resource )
{
	ALResourceManager::GetInstance( ).GenEffect( static_cast< EffectSHI* >( effect ), resource );
}

_void EGE::DelEffect( ALuint resource )
{
	ALResourceManager::GetInstance( ).DelEffect( resource );
}

EffectSHI* EGE::FindEffect( ALuint resource )
{
	return ALResourceManager::GetInstance( ).FindEffect( resource );
}

//----------------------------------------------------------------------------
// ALResourceManager Implementation
//----------------------------------------------------------------------------

ALResourceManager::ALResourceManager( )
{

}

ALResourceManager::~ALResourceManager( )
{

}

_ubool ALResourceManager::Initialize( )
{
#ifdef _PLATFORM_IOS_
	//		[[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayAndRecord error: nil];
	//		UInt32 audioRouteOverride = kAudioSessionOverrideAudioRoute_Speaker;
	//		AudioSessionSetProperty(kAudioSessionProperty_OverrideAudioRoute, 
	//			sizeof(UInt32), &audioRouteOverride);
	//#ifdef __OBJC__
	//		AudioSessionSetActive(1);
	//#endif
#endif

	return _true;
}

_void ALResourceManager::Finalize( )
{
	mBuffers.Clear( );
	mSources.Clear( );
}

_void ALResourceManager::GenBuffer( BufferSHI* buffer, ALuint& resource )
{
	// Check the current context
	if ( ::alcGetCurrentContext( ) == _null )
		return;

	AL_CHECK_ERROR( ::alGenBuffers( 1, &resource ) );

	mBuffers[ resource ] = buffer;
}

_void ALResourceManager::DelBuffer( ALuint resource )
{
	// Check the current context
	if ( ::alcGetCurrentContext( ) == _null )
		return;

	mBuffers.Remove( resource );

	AL_CHECK_ERROR( ::alDeleteBuffers( 1, &resource ) );
}

BufferSHI* ALResourceManager::FindBuffer( ALuint resource )
{
	BufferSHI** buffer = mBuffers.Search( resource );
	if ( buffer == _null )
		return _null;

	return *buffer;
}

_void ALResourceManager::GenSource( SourceSHI* source, ALuint& resource )
{
	// Check the current context
	if ( ::alcGetCurrentContext( ) == _null )
		return;

	AL_CHECK_ERROR( ::alGenSources( 1, &resource ) );

	mSources[ resource ] = source;
}

_void ALResourceManager::DelSource( ALuint resource )
{
	// Check the current context
	if ( ::alcGetCurrentContext( ) == _null )
		return;

	mSources.Remove( resource );

	AL_CHECK_ERROR( ::alDeleteSources( 1, &resource ) );
}

SourceSHI* ALResourceManager::FindSource( ALuint resource )
{
	SourceSHI** source = mSources.Search( resource );
	if ( source == _null )
		return _null;

	return *source;
}

_void ALResourceManager::GenEffect( EffectSHI* effect, ALuint& resource )
{
	// Check the current context
	if ( ::alcGetCurrentContext( ) == _null )
		return;

#if (_USE_OPENAL_EXT_ == 1)
	AL_CHECK_ERROR( ::alGenEffects( 1, &resource ) );

	mEffects[ resource ] = effect;
#else
#endif
}

_void ALResourceManager::DelEffect( ALuint resource )
{
	// Check the current context
	if ( ::alcGetCurrentContext( ) == _null )
		return;

#if (_USE_OPENAL_EXT_ == 1)
	mEffects.Remove( resource );

	AL_CHECK_ERROR( ::alDeleteEffects( 1, &resource ) );
#else
#endif
}

EffectSHI* ALResourceManager::FindEffect( ALuint resource )
{
	EffectSHI** source = mEffects.Search( resource );
	if ( source == _null )
		return _null;

	return *source;
}

#endif