#pragma once

namespace EGE {

/// <summary>
/// The sound file.
/// </summary>
class ISoundFile : public IObject {
public:
	/// <summary>
	/// The header data.
	/// </summary>
	struct HeaderData {
		//!	The format
		AudioFormat mFormat;
		//!	The channel number
		_dword mChannels;
		//!	The sample rate
		_dword mSampleRate;
		//!	The sample bit size (just for bit, not bytes)
		_dword mSampleBitSize;
		//!	The length in seconds
		_double mLength;

		//!	Get the bytes from format.
		_dword GetBytesFromFormat() const {
			switch (mFormat) {
				case AudioFormat::MONO8:
					return 1;
				case AudioFormat::MONO16:
					return 2;
				case AudioFormat::STEREO8:
					return 2;
				case AudioFormat::STEREO16:
					return 4;
				default:
					return 0;
			}
		}

		//!	Get the total bytes of sound pre second.
		_dword GetTotalBytesPreSecond() const {
			return GetBytesFromFormat() * mSampleRate;
		}

		SoundHeaderInfo() {
			mFormat = AudioFormat::UNKNOWN;
			mChannels = 0;
			mSampleRate = 0;
			mSampleBitSize = 0;
			mLength = 0.0;
		}
	};

public:
	//!	Get the audio header info.
	//!	@param		none.
	//!	@return		The audio header info.
	virtual const HeaderData& GetHeaderData() const PURE;

	//!	Seek current time.
	//!	@param		flag	The seek flag.
	//!	@param		time	The time in seconds.
	//!	@return		The current time in seconds.
	virtual _double TimeSeek(SeekFlag flag, _double time) PURE;
	//!	Get the current time.
	//!	@param		none.
	//!	@return		The current time in seconds.
	virtual _double GetCurTime() const PURE;

	//!	Decode from the current position.
	//!	@param		buffer			The PCM buffer data.
	//!	@param		size			The PCM buffer size.
	//! @return		The actual decoded buffer size in bytes.
	virtual _dword Decode(_byte* buffer, _dword size) PURE;
};

} // namespace EGE