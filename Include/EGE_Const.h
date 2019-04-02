#pragma once

namespace EGE {

/// <summary>
/// The seek flag.
/// </summary>
enum class SeekFlag {
	/// <summary>
	/// Seek from beginning.
	/// </summary>
	Begin,
	/// <summary>
	/// Seek from current position.
	/// </summary>
	Current,
	/// <summary>
	/// Seek from end plus "offset".
	/// </summary>
	End,
};

/// <summary>
/// The encode type.
/// </summary>
enum class Encoding {
	/// <summary>
	/// Unknown encoding.
	/// </summary>
	Unknown,
	/// <summary>
	/// ANSI encoding.
	/// </summary>
	Ansi,
	/// <summary>
	/// UTF-8 encoding.
	/// </summary>
	Utf8,
	/// <summary>
	/// UTF-16 encoding.
	/// </summary>
	Utf16,
};

/// <summary>
/// The endian type.
/// </summary>
enum class Endian {
	/// <summary>
	/// Unknown endian.
	/// </summary>
	Unknown,
	/// <summary>
	/// Little endian.
	/// </summary>
	Little,
	/// <summary>
	/// Big endian.
	/// </summary>
	Big,
};

/// <summary>
/// The mouse button type.
/// </summary>
enum class MouseButton {
	/// <summary>
	/// The left button.
	/// </summary>
	Left,
	/// <summary>
	/// The middle button.
	/// </summary>
	Middle,
	/// <summary>
	/// The right button.
	/// </summary>
	Right,
};

/// <summary>
/// The domain family type
/// </summary>
enum class DomainFamilyType {
	INET,
	INET6,
};

/// <summary>
/// The socket type
/// </summary>
enum class SocketType {
	Stream,
	Dgram,
	Raw,
	SeqPacket,
};

/// <summary>
/// The file attribute
/// </summary>
namespace FileAttribute {
static unsigned int ReadOnly = 0x00000001;
static unsigned int Hidden = 0x00000002;
static unsigned int System = 0x00000004;
static unsigned int Directory = 0x00000010;
static unsigned int Archive = 0x00000020;
static unsigned int Device = 0x00000040;
static unsigned int Normal = 0x00000080;
static unsigned int Temporary = 0x00000100;
static unsigned int SparseFile = 0x00000200;
static unsigned int ReparsePoint = 0x00000400;
static unsigned int Compressed = 0x00000800;
static unsigned int Offline = 0x00001000;
static unsigned int NotContentIndexed = 0x00002000;
static unsigned int Encrypted = 0x00004000;
static unsigned int IntegrityStream = 0x00008000;
}; // namespace FileAttribute

} // namespace EGE