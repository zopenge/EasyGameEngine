#pragma once

namespace EGE {

/// <summary>
/// The (PowerVR Texture Compression, PVRTC) file.
/// </summary>
class IPVRTCFile : public ICompressedTexFile {
public:
	//!	The header info
	//!	http://www.brokenteapotstudios.com/android-game-development-blog/2011/06/android-pvrtc-texture-encoding-and-performance.html
	struct HeaderInfo {
		//!	PVR3 file ID
		_dword mVersion;
		//!	Give the format the ability to specify flags that can dictate how the texture data is stored.
		//!	Pre-multiplied	0x02	this flag is set, colour values within the texture have been pre-multiplied by the alpha values.
		_dword mFlags;
		//!	A 64bit unsigned integer containing the pixel format of the texture data.
		//!	If the most significant 4 bytes contain a value, the full 8 bytes are used to determine the pixel format.
		//!	The least significant 4 bytes contain the channel order, each byte containing a single character, or a null character if there are fewer than four channels.
		//!	The most significant 4 bytes state the bit rate for each channel in the same order, each byte containing a single 8bit unsigned integer value, or zero if there are fewer than four channels, e.g., {8, 8, 8, 8} or {5, 6, 5, 0}.
		_qword mPixelFormat;
		//!	A 32bit unsigned integer that specifies which colour space the texture data is in.
		//!	Linear RGB		0		Texture data is in the Linear RGB colour space
		//!	sRGB			1		Texture data is in the Standard RGB colour space
		_dword mColourSpace;
		//!	A 32bit unsigned integer that determines the data type of the colour channels within the texture data.
		//!	Unsigned Byte Normalised	0
		//!	Signed Byte Normalised		1
		//!	Unsigned Byte				2
		//!	Signed Byte					3
		//!	Unsigned Short Normalised	4
		//!	Signed Short Normalised		5
		//!	Unsigned Short				6
		//!	Signed Short				7
		//!	Unsigned Integer Normalised	8
		//!	Signed Integer Normalised	9
		//!	Unsigned Integer			10
		//!	Signed Integer				11
		//!	Float						12
		_dword mChannelType;
		_dword mHeight;
		_dword mWidth;
		_dword mDepth;
		_dword mNumSurfaces;
		_dword mNumFaces;
		_dword mMipmapCount;
		_dword mMetaDataSize;
	};

public:
	//!	Get the header info.
	//!	@param		none.
	//!	@return		The header info.
	virtual const HeaderInfo& GetHeader() const PURE;
};

} // namespace EGE