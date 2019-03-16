//! @file     ISoundRecognizer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ISoundRecognizer
//----------------------------------------------------------------------------

class ISoundRecognizer : public IObject
{
public:
	//!	login.
	//!	@param		app_id		The application ID.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Login( WStringPtr app_id ) PURE;
	//!	login.
	//!	@param		app_id		The application ID.
	//!	@param		working_dir	The working dir.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Login( WStringPtr app_id, WStringPtr working_dir ) PURE;
	//!	logout.
	//!	@param		none.
	//!	@return		The result of expression.
	virtual _void Logout( ) PURE;

	//!	Start convert PCM buffer to string.
	//!	@param		audio_info	The audio format.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Start( const SoundRecognizerAudioInfo& audio_info ) PURE;
	//!	Listen.
	//!	@param		size		The buffer size.
	//!	@param		buffer		The buffer data.
	//!	@param		string		The string from audio data.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool Listen( _dword size, const _byte* buffer, WString& string ) PURE;
	//!	Stop convert PCM buffer to string.
	//!	@param		string		The last string from audio data.
	//! @return		none.
	virtual _void Stop( WString& string ) PURE;

	//!	Convert text to WAV file.
	//!	@param		string		The string text.
	//!	@param		config		The configure info.
	//!	@return		The WAV file.
	virtual IWAVFilePassRef ConvertText2WAVFile( WStringPtr string, const SoundRecognizerText2PCMInfo& config ) PURE;
};

}