//! @file     ISoundSource.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ISoundSource
//----------------------------------------------------------------------------

class ISoundSource : public IObject
{
public:
	//!	Process in background.
	//!	@param		none.
	//! @return		none.
	virtual _void ProcessInBackground( ) PURE;

	//!	Set sound file.
	//!	@param		sound_file		The sound file.
	//! @return		none.
	virtual _void SetSoundFile( ISoundFile* sound_file ) PURE;
	//!	Get sound file.
	//!	@param		none.
	//! @return		The sound file.
	virtual ISoundFileRef GetSoundFile( ) PURE;

	//!	Play.
	//!	@param		fade_in_time	The fade in time in milliseconds.
	//!	@param		loop			True indicates play in loop way.
	//!	@param		append			True indicates append the sound file to the tail (smooth play).
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Play( _dword fade_in_time, _ubool loop, _ubool append ) PURE;

	virtual _void ClearFadeInfo( ) PURE;
	//!	Stop.
	//!	@param		fade_out_time	The fade out time in milliseconds.
	//! @return		none.
	virtual _void Stop( _dword fade_out_time ) PURE;
	//!	Pause.
	//!	@param		fade_out_time	The fade out time in milliseconds.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Pause( _dword fade_out_time ) PURE;
	//!	Resume.
	//!	@param		fade_out_time	The fade out time in milliseconds.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Resume( _dword fade_out_time ) PURE;

	//!	Get state.
	//!	@param		none.
	//!	@return		The state of source.
	virtual _SOUND_SOURCE_STATE GetState( ) const PURE;

	//!	Seek current time.
	//!	@param		flag	The seek flag.
	//!	@param		time	The time in seconds.
	//!	@return		The current time in seconds.
	virtual _double TimeSeek( _SEEK flag, _double time ) PURE;
	//!	Get the current time.
	//!	@param		none.
	//!	@return		The current time in seconds.
	virtual _double GetCurTime( ) const PURE;

	//!	Set the pitch.
	//!	@param		pitch		The pitch value in [0.5, 2.0].
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetPitch( _float pitch ) PURE;
	//!	Get the pitch.
	//!	@param		none.
	//! @return		The pitch value in [0.5, 2.0].
	virtual _float GetPitch( ) const PURE;

	//!	Set the position.
	//!	@param		position		The position.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetPosition( const Vector3& position ) PURE;
	//!	Get the position.
	//!	@param		none.
	//! @return		The position.
	virtual const Vector3& GetPosition( ) const PURE;
	//!	Set the velocity.
	//!	@param		velocity		The velocity.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetVelocity( const Vector3& velocity ) PURE;
	//!	Get the velocity.
	//!	@param		none.
	//! @return		The velocity.
	virtual const Vector3& GetVelocity( ) const PURE;

	//!	Set the volume.
	//!	@param		volume		The volume value in [0.0, 1.0].
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetVolume( _float volume ) PURE;
	//!	Get the volume.
	//!	@param		none.
	//! @return		The volume value in [0.0, 1.0].
	virtual _float GetVolume( ) const PURE;

	//! Set the sound attenuation factor
	//! @param		factor			The factor value is [0.0 - ]. default is 1.0.  At 0.0, no distance attenuation ever occurs.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttenuationFactor( _float factor ) PURE;
	//!	Get the attenuation factor.
	//!	@param		none.
	//! @return		The attenuation factor.
	virtual _float GetAttenuationFactor( ) const PURE;
	//! Set the sound attenuation reference distance
	//! @param		distance		The distance value is [0.0 - ]. default is 1.0.  At 0.0, no distance attenuation ever occurs on non-linear attenuation models.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttenuationReferenceDistance( _float distance ) PURE;
	//!	Get the attenuation reference distance.
	//!	@param		none.
	//! @return		The attenuation reference distance.
	virtual _float GetAttenuationReferenceDistance( ) const PURE;
	//! Set the sound attenuation max distance
	//! @param		distance		The distance value is [0.0 - ]. default is +inf.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttenuationMaxDistance( _float distance ) PURE;
	//!	Get the attenuation max distance.
	//!	@param		none.
	//! @return		The attenuation max distance.
	virtual _float GetAttenuationMaxDistance( ) const PURE;

	//!	Get the format.
	//!	@param		none.
	//!	@return		The sound format.
	virtual _AUDIO_FORMAT GetFormat( ) const PURE;
	//!	Get the sample rate.
	//!	@param		none.
	//!	@return		The sample rate.
	virtual _dword GetSampleRate( ) const PURE;
	//!	Get the length in seconds.
	//!	@param		none.
	//!	@return		The sound length in seconds.
	virtual _double GetLength( ) const PURE;
	//!	Get the channels number.
	//!	@param		none.
	//!	@return		The channels number.
	virtual _dword GetChannelsNumber( ) const PURE;

	//! Get the sound is stopped.
	//! @param		none.
	//! @return		The sound is stopped.
	virtual _ubool IsStopped( ) const PURE;
	//! Get the sound is stopping ( in fade out procession ).
	//! @param		none.
	//! @return		The sound is stopping.
	virtual _ubool IsStopping( ) const PURE;
	//! Get the sound is paused.
	//! @param		none.
	//! @return		The sound is paused.
	virtual _ubool IsPaused( ) const PURE;
	//! Get the sound is playing.
	//! @param		none.
	//! @return		The sound is playing.
	virtual _ubool IsPlaying( ) const PURE;

	//!	Get the sound resource.
	//!	@param		none.
	//!	@return		The sound resource.
	virtual SourceSHIRef GetResource( ) PURE;
};

}