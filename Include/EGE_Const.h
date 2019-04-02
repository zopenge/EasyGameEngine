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
/// The file attributes.
/// </summary>
enum class FileAttribute {
	/// <summary>
	/// It's directory.
	/// </summary>
	Directory = 1 << 0,
	/// <summary>
	/// It's hidden item.
	/// </summary>
	Hidden = 1 << 1,
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

enum class FileAttributs {
	ReadOnly = 0x00000001,
	Hidden = 0x00000002,
	System = 0x00000004,
	Directory = 0x00000010,
	Archive = 0x00000020,
	Device = 0x00000040,
	Normal = 0x00000080,
	Temporary = 0x00000100,
	SparseFile = 0x00000200,
	ReparsePoint = 0x00000400,
	Compressed = 0x00000800,
	Offline = 0x00001000,
	NotContentIndexed = 0x00002000,
	Encrypted = 0x00004000,
	IntegrityStream = 0x00008000,
};

} // namespace EGE