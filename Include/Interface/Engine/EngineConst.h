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

//!	The font face load flags
enum _FONT_FACE_LOAD_FLAGS {
	_FONT_FACE_LOAD_DEFAULT = 0,

	_FONT_FACE_LOAD_NO_SCALE = 1 << 0,
	_FONT_FACE_LOAD_NO_HINTING = 1 << 1,
	_FONT_FACE_LOAD_RENDER = 1 << 2,
	_FONT_FACE_LOAD_NO_BITMAP = 1 << 3,
};

//!	The image filler type
enum _IMAGE_FILLTER_TYPE {
	_IMAGE_FILLER_BINARY_TREE, //! Binary tree image filler ( fastest, best fill rate, but only support for rectangle filling )
	_IMAGE_FILLER_SCAN_LINES, //! Scan lines image filler ( slower, medium fill rate, but can support for polygon filling )
	_IMAGE_FILLER_LINEAR, //! Linear image filler ( faster, but less fill rate and not support to free image )
};

//!	The media type
enum _MEDIA_TYPE {
	_MEDIA_TYPE_UNKNOWN,
	_MEDIA_TYPE_AUDIO,
	_MEDIA_TYPE_VIDEO,
};

//!	The application type
enum _APPLICATION_TYPE {
	_APPLICATION_TYPE_UNKNOWN,
	_APPLICATION_TYPE_CONSOLE,
	_APPLICATION_TYPE_VIEWBASED,
};

//!	The geometry vertex type function table
#define GVT_ENUM(name, value, type) _GVT##name
#define GVT_VALUE(name, value, type) _GVT##name = value
#define GVT_TYPE(name, value, type) type
#define GVT_SIZE_OF_TYPE(name, value, type) sizeof(type)
#define GVT_NAME(name, value, type) #name
#define GVT_TABLE(MACRO_NAME)                      \
	MACRO_NAME(_POS, 1 << 0, Vector3),             \
	    MACRO_NAME(_COLOR0, 1 << 1, _dword),       \
	    MACRO_NAME(_COLOR1, 1 << 2, _dword),       \
	    MACRO_NAME(_NORMAL, 1 << 3, Vector3),      \
	    MACRO_NAME(_UV1, 1 << 4, Vector2),         \
	    MACRO_NAME(_UV2, 1 << 5, Vector2),         \
	    MACRO_NAME(_BONE_INDICES, 1 << 6, _dword), \
	    MACRO_NAME(_BONE_WEIGHT, 1 << 7, Vector4), \
	    MACRO_NAME(_TANGENT, 1 << 8, Vector4),

//!	The geometry vertex type.
enum _GEOMETRY_VERTEX_TYPE {
	GVT_TABLE(GVT_VALUE)
};

//!	@export_script_enum("EnumInterpolatorType", "Enum of interpolator type")
enum _INTERPOLATOR_TYPE {
	//!	@enum("CURRENT", "")
	_INTERPOLATOR_CURRENT = 0,
	//!	@enum("NEXT", "")
	_INTERPOLATOR_NEXT,
	//!	@enum("MIDDLE", "")
	_INTERPOLATOR_MIDDLE,
	//!	@enum("LINEAR", "")
	_INTERPOLATOR_LINEAR,
	//!	@enum("SINE_IN", "")
	_INTERPOLATOR_SINE_IN,
	//!	@enum("SINE_OUT", "")
	_INTERPOLATOR_SINE_OUT,
	//!	@enum("SINE_IN_OUT", "")
	_INTERPOLATOR_SINE_INOUT,
	//!	@enum("SINE_OUT_IN", "")
	_INTERPOLATOR_SINE_OUTIN,
	//!	@enum("QUAD_IN", "")
	_INTERPOLATOR_QUAD_IN,
	//!	@enum("QUAD_OUT", "")
	_INTERPOLATOR_QUAD_OUT,
	//!	@enum("QUAD_IN_OUT", "")
	_INTERPOLATOR_QUAD_INOUT,
	//!	@enum("QUAD_OUT_IN", "")
	_INTERPOLATOR_QUAD_OUTIN,
	//!	@enum("CUBIC_IN", "")
	_INTERPOLATOR_CUBIC_IN,
	//!	@enum("CUBIC_OUT", "")
	_INTERPOLATOR_CUBIC_OUT,
	//!	@enum("CUBIC_IN_OUT", "")
	_INTERPOLATOR_CUBIC_INOUT,
	//!	@enum("CUBIC_OUT_IN", "")
	_INTERPOLATOR_CUBIC_OUTIN,
	//!	@enum("QUART_IN", "")
	_INTERPOLATOR_QUART_IN,
	//!	@enum("QUART_OUT", "")
	_INTERPOLATOR_QUART_OUT,
	//!	@enum("QUART_IN_OUT", "")
	_INTERPOLATOR_QUART_INOUT,
	//!	@enum("QUART_OUT_IN", "")
	_INTERPOLATOR_QUART_OUTIN,
	//!	@enum("QUINT_IN", "")
	_INTERPOLATOR_QUINT_IN,
	//!	@enum("QUINT_OUT", "")
	_INTERPOLATOR_QUINT_OUT,
	//!	@enum("QUINT_IN_OUT", "")
	_INTERPOLATOR_QUINT_INOUT,
	//!	@enum("QUINT_OUT_IN", "")
	_INTERPOLATOR_QUINT_OUTIN,
	//!	@enum("EXPO_IN", "")
	_INTERPOLATOR_EXPO_IN,
	//!	@enum("EXPO_OUT", "")
	_INTERPOLATOR_EXPO_OUT,
	//!	@enum("EXPO_INOUT", "")
	_INTERPOLATOR_EXPO_INOUT,
	//!	@enum("EXPO_OUTIN", "")
	_INTERPOLATOR_EXPO_OUTIN,
	//!	@enum("CIRC_IN", "")
	_INTERPOLATOR_CIRC_IN,
	//!	@enum("CIRC_OUT", "")
	_INTERPOLATOR_CIRC_OUT,
	//!	@enum("CIRC_INOUT", "")
	_INTERPOLATOR_CIRC_INOUT,
	//!	@enum("CIRC_OUTIN", "")
	_INTERPOLATOR_CIRC_OUTIN,
	//!	@enum("ELASTIC_IN", "")
	_INTERPOLATOR_ELASTIC_IN,
	//!	@enum("ELASTIC_OUT", "")
	_INTERPOLATOR_ELASTIC_OUT,
	//!	@enum("ELASTIC_INOUT", "")
	_INTERPOLATOR_ELASTIC_INOUT,
	//!	@enum("ELASTIC_OUTIN", "")
	_INTERPOLATOR_ELASTIC_OUTIN,
	//!	@enum("BACK_IN", "")
	_INTERPOLATOR_BACK_IN,
	//!	@enum("BACK_OUT", "")
	_INTERPOLATOR_BACK_OUT,
	//!	@enum("BACK_INOUT", "")
	_INTERPOLATOR_BACK_INOUT,
	//!	@enum("BACK_OUTIN", "")
	_INTERPOLATOR_BACK_OUTIN,
	//!	@enum("BOUNCE_IN", "")
	_INTERPOLATOR_BOUNCE_IN,
	//!	@enum("BOUNCE_OUT", "")
	_INTERPOLATOR_BOUNCE_OUT,
	//!	@enum("BOUNCE_INOUT", "")
	_INTERPOLATOR_BOUNCE_INOUT,
	//!	@enum("BOUNCE_OUTIN", "")
	_INTERPOLATOR_BOUNCE_OUTIN,
};

//!	The message box type
enum _MESSAGE_BOX_TYPE {
	_MBT_OK,
	_MBT_OK_CANCEL,
	_MBT_ABORT_RETRY_IGNORE,
	_MBT_YES_NO_CANCEL,
	_MBT_YES_NO,
	_MBT_RETRY_CANCEL,
};

//!	The message box button ID
enum _MESSAGE_BOX_BUTTON_ID {
	_MBB_ID_OK,
	_MBB_ID_CANCEL,
	_MBB_ID_ABORT,
	_MBB_ID_RETRY,
	_MBB_ID_IGNORE,
	_MBB_ID_YES,
	_MBB_ID_NO,
};

//!	The user interface type
enum _USER_INTERFACE {
	_USER_INTERFACE_UNKNOWN,
	_USER_INTERFACE_PC,
	_USER_INTERFACE_PHONE,
	_USER_INTERFACE_PAD,
};

//!	The stream type
enum _STREAM_TYPE {
	_STREAM_TYPE_MEMORY,
	_STREAM_TYPE_FILE,
};

//!	The stream share mode
enum _STREAM_SHARE_MODE {
	_STREAM_SHARE_MODE_NONE,
	_STREAM_SHARE_MODE_MANAGED,
	_STREAM_SHARE_MODE_READ_ONLY,
};

/// <summary>
/// The font style.
/// </summary>
namespace FontStyle {
static unsigned int Bold = 1 << 0;
static unsigned int Italic = 1 << 1;
static unsigned int Underline = 1 << 2;
} // namespace FontStyle

//!	The font face code info
struct FontFaceCodeInfoBase {
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

	FontFaceCodeInfoBase() {
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

//!	The font face code info
struct FontFaceCodeInfo : public FontFaceCodeInfoBase {
	_short mBitmapLeft;
	_short mBitmapTop;
	_short mBitmapWidth;
	_short mBitmapHeight;
	const _byte* mBitmapBuffer;

	FontFaceCodeInfo() {
		mBitmapLeft = 0;
		mBitmapTop = 0;
		mBitmapWidth = 0;
		mBitmapHeight = 0;
		mBitmapBuffer = _null;
	}

	FontFaceCodeInfo& operator=(const FontFaceCodeInfoBase& info) {
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

//!	The base bitmap info
template <typename PixelBufferType>
struct BaseBitmapInfo {
	//!	The pixel format
	_PIXEL_FORMAT mPixelFormat;
	//!	The pre-pixel size in bytes
	_dword mPixelBytes;
	//!	The pitch of pixel buffer
	_dword mPitch;
	//!	The bitmap width in pixel
	_dword mWidth;
	//!	The bitmap height in pixel
	_dword mHeight;
	//!	The pixel buffer
	PixelBufferType mPixelBuffer;

	//!	Validate.
	_ubool IsValid() const {
		if (mPitch == 0 || mWidth == 0 || mHeight == 0)
			return _false;

		if (mPixelBytes == 0)
			return _false;

		if (mPixelFormat == _PF_UNKNOWN || mPixelFormat >= _PF_MAX)
			return _false;

		if (mPixelBuffer == _null)
			return _false;

		return _true;
	}

	//! Get pixel buffer by position.
	PixelBufferType GetPixelBufferByPos(_int x, _int y) const {
		return mPixelBuffer + y * mPitch + x * mPixelBytes;
	}

	BaseBitmapInfo()
	    : mPixelFormat(_PF_UNKNOWN), mPixelBytes(0), mPitch(0), mWidth(0), mHeight(0), mPixelBuffer(_null) {
	}

	BaseBitmapInfo(_PIXEL_FORMAT format, _dword pixel_bytes, _dword pitch, _dword width, _dword height, PixelBufferType pixelbuffer)
	    : mPixelFormat(format), mPixelBytes(pixel_bytes), mPitch(pitch), mWidth(width), mHeight(height), mPixelBuffer(pixelbuffer) {
	}
};

//!	The bitmap info
struct BitmapInfo : public BaseBitmapInfo<_byte*> {
	BitmapInfo() {
	}

	BitmapInfo(_PIXEL_FORMAT format, _dword pixel_bytes, _dword pitch, _dword width, _dword height, _byte* pixelbuffer)
	    : BaseBitmapInfo<_byte*>(format, pixel_bytes, pitch, width, height, pixelbuffer) {
	}
};

//!	The readonly bitmap info
struct BitmapInfoReadOnly : public BaseBitmapInfo<const _byte*> {
	BitmapInfoReadOnly() {
	}

	BitmapInfoReadOnly(_PIXEL_FORMAT format, _dword pixel_bytes, _dword pitch, _dword width, _dword height, const _byte* pixelbuffer)
	    : BaseBitmapInfo<const _byte*>(format, pixel_bytes, pitch, width, height, pixelbuffer) {
	}

	BitmapInfoReadOnly(const BitmapInfo& bitmap_info)
	    : BaseBitmapInfo<const _byte*>(bitmap_info.mPixelFormat, bitmap_info.mPixelBytes, bitmap_info.mPitch, bitmap_info.mWidth, bitmap_info.mHeight, bitmap_info.mPixelBuffer) {
	}
};

//!	The manifest item
struct ManifestItemInfo {
	//!	The item name
	WString mName;
	//!	The item MD5 checksum code
	MD5Code mMD5Code;

	//!	Use the name as key
	operator WStringPtr() const {
		return mName;
	}

	//!	Compare.
	_ubool operator==(const ManifestItemInfo& item_info) const {
		if (mName != item_info.mName)
			return _false;

		if (mMD5Code != item_info.mMD5Code)
			return _false;

		return _true;
	}
	//!	Compare.
	_ubool operator!=(const ManifestItemInfo& item_info) const {
		if (mName != item_info.mName)
			return _true;

		if (mMD5Code != item_info.mMD5Code)
			return _true;

		return _false;
	}

	ManifestItemInfo() {
	}
};
typedef Array<ManifestItemInfo> ManifestItemArray;

//!	The manifest item node
struct ManifestItemNodeInfo : public ManifestItemInfo {
	//!	The parent directory
	IManifestDirRef mParentDir;

	ManifestItemNodeInfo() {
	}
	ManifestItemNodeInfo(const ManifestItemInfo& item, IManifestDir* dir)
	    : mParentDir(dir) {
		(ManifestItemInfo&)* this = item;
	}
};
typedef Array<ManifestItemNodeInfo> ManifestItemNodeInfoArray;

//!	The manifest walker item info
struct ManifestWalkerItemInfo {
	//!	The depth of item, start from 1
	_dword mDepth;
	//!	The current item index of enumeration
	_dword mItemNumber;

	//!	The relative path
	WString mRelativePath;
	//!	The absolute path
	WString mAbsolutePath;

	//!	If it set then indicates it's directory
	IManifestDirRef mDirectory;
	//!	If it set then indicates it's file
	const ManifestItemInfo* mItem;
};

//!	The sound ID3 tags info
struct SoundID3TagsInfo {
	WString mTitle;
	WString mArtist;
	WString mAlbum;
	WString mGenre;
	WString mComment;
	WString mYear;
	WString mTrack;

	WString mAlbumArtist;
	WString mComposer;
	WString mOriginalArtist;
	WString mCopyright;
	WString mUrl;
	WString mEncoder;
	WString mPublisher;
	WString mBpm;

	WString mPictureMime;
	WString mPictureDescription;
	_dword mPictureType;
	_byte* mPictureData;
	_dword mPictureDataSize;

	SoundID3TagsInfo() {
		mPictureType = 0;
		mPictureData = _null;
		mPictureDataSize = 0;
	}
	~SoundID3TagsInfo() {
		EGE_DELETE_ARRAY(mPictureData);
	}
};

//!	The sound header info.
struct SoundHeaderInfo {
	//!	The format
	_AUDIO_FORMAT mFormat;
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
			case _AF_MONO8:
				return 1;
			case _AF_MONO16:
				return 2;
			case _AF_STEREO8:
				return 2;
			case _AF_STEREO16:
				return 4;
			default:
				return 0;
		}
	}

	//!	Get the total bytes of sound in 1 second.
	_dword GetTotalBytesInOneSecond() const {
		return GetBytesFromFormat() * mSampleRate;
	}

	SoundHeaderInfo() {
		mFormat = _AF_UNKNOWN;
		mChannels = 0;
		mSampleRate = 0;
		mSampleBitSize = 0;
		mLength = 0.0;
	}
};

//!	The sound vorbis format info
struct SoundVorbisFormatInfoBase {
	_dword mChannels;
	_dword mSampleRate;
	_dword mSampleBitSize;
	_dword mHeaderSize[3];

	SoundVorbisFormatInfoBase() {
		mChannels = 0;
		mSampleRate = 0;
		mSampleBitSize = 0;
		EGE_INIT_ARRAY(mHeaderSize);
	}
};

//!	The sound vorbis format info
struct SoundVorbisFormatInfo : public SoundVorbisFormatInfoBase {
	_dword GetIDSectionSize() const {
		return mHeaderSize[0];
	}
	_dword GetCommentSectionSize() const {
		return mHeaderSize[1];
	}
	_dword GetCodeBookSectionSize() const {
		return mHeaderSize[2];
	}

	const _byte* GetIDSection() const {
		return (const _byte*)this + sizeof(SoundVorbisFormatInfo);
	}
	const _byte* GetCommentSection() const {
		return (const _byte*)this + sizeof(SoundVorbisFormatInfo) + mHeaderSize[0];
	}
	const _byte* GetCodeBookSection() const {
		return (const _byte*)this + sizeof(SoundVorbisFormatInfo) + mHeaderSize[0] + mHeaderSize[1];
	}

	SoundVorbisFormatInfo() {
	}
};

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
	//! hardware ID
	WString mHardwareIDv2;
	//!	The user interface type
	_USER_INTERFACE mUserInterface;
};

} // namespace EGE