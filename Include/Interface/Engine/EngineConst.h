#pragma once

namespace EGE {

/// <summary>
/// The log type.
/// </summary>
enum class LogType {
	Debug,
	Warn,
	Error
};

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
/// The align type.
/// </summary>
enum class AlignType {
	Horz,
	Vert,
};

/// /// <summary>
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
namespace LerpType {
typedef _float (*OnLerp)(_float);
OnLerp Linear = (OnLerp)Interpolation::Linear;
OnLerp SineIn = (OnLerp)Interpolation::SineIn;
OnLerp SineOut = (OnLerp)Interpolation::SineOut;
OnLerp SineInOut = (OnLerp)Interpolation::SineInOut;
OnLerp SineOutIn = (OnLerp)Interpolation::SineOutIn;
OnLerp QuadIn = (OnLerp)Interpolation::QuadIn;
OnLerp QuadOut = (OnLerp)Interpolation::QuadOut;
OnLerp QuadInOut = (OnLerp)Interpolation::QuadInOut;
OnLerp QuadOutIn = (OnLerp)Interpolation::QuadOutIn;
OnLerp CubicIn = (OnLerp)Interpolation::CubicIn;
OnLerp CubicOut = (OnLerp)Interpolation::CubicOut;
OnLerp CubicInOut = (OnLerp)Interpolation::CubicInOut;
OnLerp CubicOutIn = (OnLerp)Interpolation::CubicOutIn;
OnLerp QuartIn = (OnLerp)Interpolation::QuartIn;
OnLerp QuartOut = (OnLerp)Interpolation::QuartOut;
OnLerp QuartInOut = (OnLerp)Interpolation::QuartInOut;
OnLerp QuartOutIn = (OnLerp)Interpolation::QuartOutIn;
OnLerp QuintIn = (OnLerp)Interpolation::QuintIn;
OnLerp QuintOut = (OnLerp)Interpolation::QuintOut;
OnLerp QuintInOut = (OnLerp)Interpolation::QuintInOut;
OnLerp QuintOutIn = (OnLerp)Interpolation::QuintOutIn;
OnLerp ExpoIn = (OnLerp)Interpolation::ExpoIn;
OnLerp ExpoOut = (OnLerp)Interpolation::ExpoOut;
OnLerp ExpoInOut = (OnLerp)Interpolation::ExpoInOut;
OnLerp ExpoOutIn = (OnLerp)Interpolation::ExpoOutIn;
OnLerp CircIn = (OnLerp)Interpolation::CircIn;
OnLerp CircOut = (OnLerp)Interpolation::CircOut;
OnLerp CircInOut = (OnLerp)Interpolation::CircInOut;
OnLerp CircOutIn = (OnLerp)Interpolation::CircOutIn;
OnLerp ElasticIn = (OnLerp)Interpolation::ElasticIn;
OnLerp ElasticOut = (OnLerp)Interpolation::ElasticOut;
OnLerp ElasticInOut = (OnLerp)Interpolation::ElasticInOut;
OnLerp ElasticOutIn = (OnLerp)Interpolation::ElasticOutIn;
OnLerp BackIn = (OnLerp)Interpolation::BackIn;
OnLerp BackOut = (OnLerp)Interpolation::BackOut;
OnLerp BackInOut = (OnLerp)Interpolation::BackInOut;
OnLerp BackOutIn = (OnLerp)Interpolation::BackOutIn;
OnLerp BounceIn = (OnLerp)Interpolation::BounceIn;
OnLerp BounceOut = (OnLerp)Interpolation::BounceOut;
OnLerp BounceInOut = (OnLerp)Interpolation::BounceInOut;
OnLerp BounceOutIn = (OnLerp)Interpolation::BounceOutIn;
} // namespace LerpType

/// <summary>
/// The font style.
/// </summary>
namespace FontStyle {
static unsigned int Bold = 1 << 0;
static unsigned int Italic = 1 << 1;
static unsigned int Underline = 1 << 2;
} // namespace FontStyle

} // namespace EGE