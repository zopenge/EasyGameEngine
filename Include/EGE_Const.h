#pragma once

namespace EGE {

/// <summary>
/// The seek flag.
/// </summary>
enum class Seek {
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

} // namespace EGE