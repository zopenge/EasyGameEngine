//! @file     ISoundResourceManager.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ISoundResourceManager
//----------------------------------------------------------------------------

class ISoundResourceManager : public IObject
{
public:
	//!	Get the sounds number.
	//!	@param		none.
	//!	@return		The sounds number.
	virtual _dword GetSoundsNumber( ) const PURE;
	//!	Get the sound by index.
	//!	@param		none.
	//!	@return		The sound interface.
	virtual ISoundSourceRef GetSoundByIndex( _dword index ) PURE;

	//!	Stop all sounds.
	//!	@param		none.
	//!	@return		none.
	virtual _void StopAllSounds( ) PURE;
	//!	Play sound from stream.
	//!	@param		file_format		The file format.
	//!	@param		stream_reader	The sound stream reader.
	//!	@param		loop			True indicates playing infinite.
	//!	@param		volume			The volume of sound.
	//!	@return		The sound source.
	virtual ISoundSourceRef PlaySoundFromStream( _FILE_FORMAT file_format, IStreamReader* stream_reader, _dword fade_in_time, _ubool loop, _float volume = 1.0f ) PURE;
	//!	Play sound from file.
	//!	@param		file_format		The file format.
	//!	@param		stream_reader	The sound stream reader.
	//!	@param		loop			True indicates playing infinite.
	//!	@param		volume			The volume of sound.
	//!	@return		The sound source.
	virtual ISoundSourceRef PlaySoundFromFile( ISoundFile* sound_file, _dword fade_in_time, _ubool loop, _float volume = 1.0f ) PURE;

	//!	Create sound recorder.
	//!	@param		notifier		The notifier.
	//!	@return		The sound recorder.
	virtual ISoundRecorderPassRef CreateSoundRecorder( ISoundRecorderNotifier* notifier ) PURE;

	//!	Create sound recognizer.
	//!	@param		none.
	//!	@return		The sound recognizer.
	virtual ISoundRecognizerPassRef CreateSoundRecognizer( ) PURE;
};

}