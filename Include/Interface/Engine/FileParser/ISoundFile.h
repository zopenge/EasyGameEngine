//! @file     ISoundFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ISoundFileWriter
//----------------------------------------------------------------------------

class ISoundFileWriter : public IFileWriter
{
public:
	//!	Initialize.
	virtual _ubool Start( _dword channels, _dword sample_rate, _dword sample_bit_size ) PURE;
	virtual _void Stop( ) PURE;

	//!	Encode.
	//!	@param		buffer			The buffer data.
	//!	@param		size			The buffer size.
	//! @return		The actual encoded buffer size in bytes.
	virtual _dword Encode( const _byte* buffer, _dword size ) PURE;
};

//----------------------------------------------------------------------------
// ISoundFile
//----------------------------------------------------------------------------

class ISoundFile : public IBaseFile
{
public:
	//!	Check whether it's streaming sound file.
	//!	@param		none.
	//!	@return		True indicates it's streaming sound file.
	virtual _ubool IsStreaming( ) const PURE;

	//!	Get the ID3 tags info.
	//!	@param		none.
	//!	@return		The ID3 tags info.
	virtual const SoundID3TagsInfo& GetID3TagsInfo( ) const PURE;

	//!	Get the audio header info.
	//!	@param		none.
	//!	@return		The audio header info.
	virtual const SoundHeaderInfo& GetHeaderInfo( ) const PURE;

	//!	Seek current time.
	//!	@param		flag	The seek flag.
	//!	@param		time	The time in seconds.
	//!	@return		The current time in seconds.
	virtual _double TimeSeek( _SEEK flag, _double time ) PURE;
	//!	Get the current time.
	//!	@param		none.
	//!	@return		The current time in seconds.
	virtual _double GetCurTime( ) const PURE;

	//!	Decode from the current position.
	//!	@param		buffer			The PCM buffer data.
	//!	@param		size			The PCM buffer size.
	//! @return		The actual decoded buffer size in bytes.
	virtual _dword Decode( _byte* buffer, _dword size ) PURE;
};

}