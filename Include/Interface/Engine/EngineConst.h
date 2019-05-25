#pragma once

namespace EGE {

/// <summary>
/// The orientation mode.
/// </summary>
enum class OrientationMode {
	Unknown,
	Any, //! Any type
	Port, //! Portrait
	Land, //! Landscape
	Square, //!	Square
};

/// <summary>
/// The process state.
/// </summary>
enum class ProcessState {
	Normal, //!	Initial state
	Continue, //! Continue to work
	Error, //! Some error occurred
	Skipped, //! Skipped to do something
	Releasing, //! It's releasing now
	Suspending, //!	Suspending
	Waiting, //! Waiting to process
	Aborted, //! Aborted
	Timeout, //! Timeout
	Running, //! Running
	Finished, //! Finished
};

/// <summary>
/// The animation mode.
/// </summary>
enum class AnimationMode {
	/// <summary>
	/// Play only once
	/// </summary>
	Once,
	/// <summary>
	/// Loop playing.
	/// </summary>
	Repeat,
	/// <summary>
	/// A->B->A loop playing.
	/// </summary>
	Pingpong,
};

/// <summary>
/// The animation direction type.
/// </summary>
enum class AnimationDirection {
	Forward,
	Backward,
};

/// <summary>
/// The animation state.
/// </summary>
enum class AnimationState {
	Stopped,
	Playing,
	Pausing,
};

/// <summary>
/// The connection state.
/// </summary>
enum class ConnectionState {
	Unknown,
	Connecting,
	Connected,
	Disconnected,
};

/// <summary>
/// The pixel format.
/// </summary>
enum class PixelFormat {
	UNKNOWN,
	A1,
	A8,
	R5G6B5,
	R5G5B5A1,
	R4G4B4A4,
	R8G8B8,
	A8R8G8B8,
	DXT1,
	DXT3,
	DXT5,
	ETC1_RGB8,
	ETC2_RGBA8,
	RGB_PVRTC_4BPP,
	RGB_PVRTC_2BPP,
	RGBA_PVRTC_4BPP,
	RGBA_PVRTC_2BPP,
	DEPTH_STENCIL,
	SHADOW_DEPTH,
};

/// <summary>
/// The image filter type.
/// </summary>
enum class ImageFilterType {
	BOX, //! Box, pulse, Fourier window, 1st order (constant) b-spline
	BICUBIC, //! Mitchell & Netravali's two-param cubic filter
	BILINEAR, //! Bilinear filter
	BSPLINE, //! 4th order (cubic) b-spline
	CATMULLROM, //! Catmull-Rom spline, Overhauser spline
	LANCZOS3, //! Lanczos3 filter
};

/// <summary>
/// The compression type.
/// </summary>
enum class CompressionType {
	UNKNOWN,
	ZLIB,
};

/// <summary>
/// The audio format.
/// </summary>
enum class AudioFormat {
	UNKNOWN,
	MONO8,
	MONO16,
	STEREO8,
	STEREO16,
};

/// <summary>
/// The image filler type.
/// </summary>
enum class ImageFillerType {
	BinaryTree, //! Binary tree image filler ( fastest, best fill rate, but only support for rectangle filling )
	ScanLines, //! Scan lines image filler ( slower, medium fill rate, but can support for polygon filling )
	Linear, //! Linear image filler ( faster, but less fill rate and not support to free image )
};

/// <summary>
/// The lerp type.
/// </summary>
enum class LerpType {
	Linear,
	SineIn,
	SineOut,
	SineInOut,
	SineOutIn,
	QuadIn,
	QuadOut,
	QuadInOut,
	QuadOutIn,
	CubicIn,
	CubicOut,
	CubicInOut,
	CubicOutIn,
	QuartIn,
	QuartOut,
	QuartInOut,
	QuartOutIn,
	QuintIn,
	QuintOut,
	QuintInOut,
	QuintOutIn,
	ExpoIn,
	ExpoOut,
	ExpoInOut,
	ExpoOutIn,
	CircIn,
	CircOut,
	CircInOut,
	CircOutIn,
	ElasticIn,
	ElasticOut,
	ElasticInOut,
	ElasticOutIn,
	BackIn,
	BackOut,
	BackInOut,
	BackOutIn,
	BounceIn,
	BounceOut,
	BounceInOut,
	BounceOutIn,
};

/// <summary>
/// The font style.
/// </summary>
namespace FontStyle {
static unsigned int Bold = 1 << 0;
static unsigned int Italic = 1 << 1;
static unsigned int Underline = 1 << 2;
} // namespace FontStyle

/// <summary>
/// The base font face code data.
/// </summary>
struct BaseFontFaceCodeData {
	_charw mCode;

	_short mCharWidth;
	_short mCharHeight;
	_short mMaxCharWidth;
	_short mMaxCharHeight;

	_short mAdvanceX;
	_short mBearingY;
	_short mOffsetX;
	_short mOffsetY;

	_short mAscender;
	_short mDescender;
	_short mBaseLine;

	BaseFontFaceCodeData() {
		mCode = 0;

		mCharWidth = 0;
		mCharHeight = 0;
		mMaxCharWidth = 0;
		mMaxCharHeight = 0;

		mAdvanceX = 0;
		mBearingY = 0;
		mOffsetX = 0;
		mOffsetY = 0;

		mAscender = 0;
		mDescender = 0;
		mBaseLine = 0;
	}
};

/// <summary>
/// The font face code with bitmap pixel buffer data.
/// </summary>
struct FontFaceCodeData : public BaseFontFaceCodeData {
	_short mBitmapLeft;
	_short mBitmapTop;
	_short mBitmapWidth;
	_short mBitmapHeight;
	const _byte* mBitmapBuffer;

	FontFaceCodeData() {
		mBitmapLeft = 0;
		mBitmapTop = 0;
		mBitmapWidth = 0;
		mBitmapHeight = 0;
		mBitmapBuffer = _null;
	}

	FontFaceCodeData& operator=(const FontFaceCodeData& info) {
		mCharWidth = info.mCharWidth;
		mCharHeight = info.mCharHeight;
		mMaxCharWidth = info.mMaxCharWidth;
		mMaxCharHeight = info.mMaxCharHeight;

		mAdvanceX = info.mAdvanceX;
		mBearingY = info.mBearingY;
		mOffsetX = info.mOffsetX;
		mOffsetY = info.mOffsetY;

		mAscender = info.mAscender;
		mDescender = info.mDescender;

		return *this;
	}
};

/// <summary>
/// The manifest item data.
/// </summary>
struct ManifestItemData {
	//!	The item name
	WString mName;
	//!	The item MD5 checksum code
	MD5Code mMD5Code;

	//!	Use the name as key
	operator WStringPtr() const {
		return mName;
	}

	_ubool operator==(const ManifestItemInfo& item_info) const {
		if (mName != item_info.mName)
			return _false;

		if (mMD5Code != item_info.mMD5Code)
			return _false;

		return _true;
	}

	_ubool operator!=(const ManifestItemInfo& item_info) const {
		if (mName != item_info.mName)
			return _true;

		if (mMD5Code != item_info.mMD5Code)
			return _true;

		return _false;
	}

	ManifestItemData() {
	}
};
typedef Array<ManifestItemData> ManifestItemDataArray;

//!	The platform device info
struct PlatformDeviceInfo {
	//!	The advertising identifier
	WString mAdvertisingIdentifier;
	//!	The identifier for vendor
	WString mIdentifierForVendor;
	//!	The device name
	WString mDeviceName;
	//!	The model name.
	WString mModelName;
	//!	The system name
	WString mSystemName;
	//!	The system version
	WString mSystemVersion;
	//! hardware unique ID
	WString mHardwareUniqueID;
};

} // namespace EGE