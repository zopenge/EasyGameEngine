//! @file     EGE_Enums.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! @brief    Globals enumerations and structure
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Global enumerations
//----------------------------------------------------------------------------

//!	The power of 2 values
enum _ENUM_VALUE
{
	_ENUM_VALUE_2		= 1 << 1,
	_ENUM_VALUE_4		= 1 << 2,
	_ENUM_VALUE_8		= 1 << 3,
	_ENUM_VALUE_16		= 1 << 4,
	_ENUM_VALUE_32		= 1 << 5,
	_ENUM_VALUE_64		= 1 << 6,
	_ENUM_VALUE_128		= 1 << 7,
	_ENUM_VALUE_256		= 1 << 8,
	_ENUM_VALUE_512		= 1 << 9,
	_ENUM_VALUE_1024	= 1 << 10,
	_ENUM_VALUE_2048	= 1 << 11,
	_ENUM_VALUE_4096	= 1 << 12,
	_ENUM_VALUE_8192	= 1 << 13,
	_ENUM_VALUE_16384	= 1 << 14,
	_ENUM_VALUE_32768	= 1 << 15,
};

//!	The Priority
enum _PRIORITY
{
	_PRIORITY_LOWEST		= 0,
	_PRIORITY_BELOW_NORMAL	= 1,
	_PRIORITY_NORMAL		= 2,
	_PRIORITY_ABOVE_NORMAL	= 3,
	_PRIORITY_HIGHEST		= 4,
};

//!	The log Type
enum _LOG
{
	_LOG_DEBUG		= 1 << 0,	//! Debug message type
	_LOG_TRACE		= 1 << 1, 	//! Trace message type
	_LOG_ERROR		= 1 << 2, 	//! Error message type
	_LOG_WARNING	= 1 << 3,	//! Warning message type
	_LOG_FATAL		= 1 << 4,	//! Fatal message type
};

//!	The seek flag
enum _SEEK
{
	_SEEK_BEGIN		= 0, //! Seek from beginning.
	_SEEK_CURRENT	= 1, //! Seek from current position.
	_SEEK_END		= 2, //! Seek from end plus "offset"
};

//!	@export_script_enum("Encoding", "The encode type")
enum _ENCODING
{
	//!	@enum("unknown", "It's unknown text")
	_ENCODING_UNKNOWN	= -1,
	//!	@enum("ansi", "It's ANSI text")
	_ENCODING_ANSI		= 0,
	//!	@enum("utf-8", "It's UTF-8 text")
	_ENCODING_UTF8		= 1,
	//!	@enum("utf-16", "It's UTF-16 text")
	_ENCODING_UTF16		= 2,
};

//!	The endian type
enum _ENDIAN
{
	_ENDIAN_UNKNOWN	= 0,
	_ENDIAN_LITTLE	= 1,
	_ENDIAN_BIG		= 2,
};

//!	@export_script_enum("PlatformType", "The platform type")
enum _PLATFORM_TYPE
{
	//!	@enum("Unknown", "It's unknown platform")
	_PLATFORM_TYPE_UNKNOWN,
	//!	@enum("Windows", "It's unknown platform")
	_PLATFORM_TYPE_WINDOWS,
	//!	@enum("Android", "It's unknown platform")
	_PLATFORM_TYPE_ANDROID,
	//!	@enum("IOS", "It's unknown platform")
	_PLATFORM_TYPE_IOS,
	//!	@enum("Chrome", "It's unknown platform")
	_PLATFORM_TYPE_CHROME,
};

//! CPU
enum _CPU_FAMILY
{
	_CPU_FAMILY_UNKNOWN,

	_CPU_FAMILY_X86,
	_CPU_FAMILY_ARM,
	_CPU_FAMILY_MIPS,
};

//!	CPU features
enum _CPU_FEATURES
{
	_CPU_FEATURE_SSSE3			= 1 << 0,
	_CPU_FEATURE_POPCNT			= 1 << 1,
	_CPU_FEATURE_MOVBE			= 1 << 2,
	_CPU_FEATURE_ARMv7			= 1 << 3,
	_CPU_FEATURE_VFPv3			= 1 << 4,
	_CPU_FEATURE_NEON			= 1 << 5,
	_CPU_FEATURE_LDREX_STREX	= 1 << 6,
};

//!	Process Creation Flags
enum _PROCESS_CREATION
{
	_PROCESS_CREATION_BREAKAWAY_FROM_JOB			= 0x01000000,
	_PROCESS_CREATION_DEFAULT_ERROR_MODE			= 0x04000000,
	_PROCESS_CREATION_NEW_CONSOLE					= 0x00000010,
	_PROCESS_CREATION_NEW_PROCESS_GROUP				= 0x00000200,
	_PROCESS_CREATION_NO_WINDOW						= 0x08000000,
	_PROCESS_CREATION_PROTECTED_PROCESS				= 0x00040000,
	_PROCESS_CREATION_PRESERVE_CODE_AUTHZ_LEVEL		= 0x02000000,
	_PROCESS_CREATION_SEPARATE_WOW_VDM				= 0x00000800,
	_PROCESS_CREATION_SHARED_WOW_VDM				= 0x00001000,
	_PROCESS_CREATION_SUSPENDED						= 0x00000004,
	_PROCESS_CREATION_UNICODE_ENVIRONMENT			= 0x00000400,
	_PROCESS_CREATION_DEBUG_ONLY_THIS_PROCESS		= 0x00000002,
	_PROCESS_CREATION_DEBUG_PROCESS					= 0x00000001,
	_PROCESS_CREATION_DETACHED_PROCESS				= 0x00000008,
	_PROCESS_CREATION_EXTENDED_STARTUPINFO_PRESENT	= 0x00080000,
	_PROCESS_CREATION_INHERIT_PARENT_AFFINITY		= 0x00010000,
};

//!	File Attributes
enum _FILE_ATTRIBUTE
{
	_FILE_ATTRIBUTE_READONLY             = 0x00000001,  
	_FILE_ATTRIBUTE_HIDDEN               = 0x00000002,  
	_FILE_ATTRIBUTE_SYSTEM               = 0x00000004,  
	_FILE_ATTRIBUTE_DIRECTORY            = 0x00000010,  
	_FILE_ATTRIBUTE_ARCHIVE              = 0x00000020,  
	_FILE_ATTRIBUTE_DEVICE               = 0x00000040,  
	_FILE_ATTRIBUTE_NORMAL               = 0x00000080,  
	_FILE_ATTRIBUTE_TEMPORARY            = 0x00000100,  
	_FILE_ATTRIBUTE_SPARSE_FILE          = 0x00000200,  
	_FILE_ATTRIBUTE_REPARSE_POINT        = 0x00000400,  
	_FILE_ATTRIBUTE_COMPRESSED           = 0x00000800,  
	_FILE_ATTRIBUTE_OFFLINE              = 0x00001000,  
	_FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  = 0x00002000,  
	_FILE_ATTRIBUTE_ENCRYPTED            = 0x00004000,  
	_FILE_ATTRIBUTE_VIRTUAL              = 0x00010000,
};

//! Flag of how to create a file.
enum _FILE_CREATE_FLAG
{
	//! Creates a new file, if the file exists, the function will fail.
	_FILE_CREATE_NEW	= 1,
	//! Creates a new file, if the file exists, the function overwrites it.
	_FILE_CREATE_ALWAYS	= 2,
	//! Opens the file, if the file does not exist, the function will fail.
	_FILE_OPEN_EXISTING	= 3,
	//! Opens the file if the file exists, or create it if the it does not exist.
	_FILE_OPEN_ALWAYS	= 4,
};

//! Flag of how to operate a file.
enum _FILE_OPERATION_FLAG
{
	//! Read from a file.
	_FILE_OPERATION_READ			= 0x80000000,
	//! Write into a file.
	_FILE_OPERATION_WRITE			= 0x40000000,
	//! Perform all SocketOperations on a file.
	_FILE_OPERATION_ALL				= _FILE_OPERATION_READ | _FILE_OPERATION_WRITE,
	//!	Open a file and seek the file pointer to the end
	_FILE_OPERATION_WRITE_APPEND	= _FILE_OPERATION_WRITE | 0x08000000,
};

//! Flag of how to share the file with other processes.
enum _FILE_SHARE_FLAG
{
	//! Do not share the file.
	_FILE_SHARE_NONE	= 0x00000000,
	//! Other processes can read the file.
	_FILE_SHARE_READ	= 0x00000001,
	//! Other processes can write the file.
	_FILE_SHARE_WRITE	= 0x00000002,
	//! Other processes can delete the file.
	_FILE_SHARE_DELETE	= 0x00000004,
};

//!	The file finder enumeration flags
enum _FILE_FINDER_ENUMERATION
{
	//!	Whether search in subdirectories.
	_FILE_FINDER_ENUMERATION_RECURSIVE				= 1 << 0,
	//!	Enumerate files only
	_FILE_FINDER_ENUMERATION_FILE_ONLY				= 1 << 1,
	//!	Enumerate directories only
	_FILE_FINDER_ENUMERATION_DIRECTORY_ONLY			= 1 << 2,
	//!	Skip the hidden files
	_FILE_FINDER_ENUMERATION_SKIP_HIDDEN_FILE		= 1 << 3,
	//!	Skip the hidden directories
	_FILE_FINDER_ENUMERATION_SKIP_HIDDEN_DIRECTORY	= 1 << 4,
	//!	Skip the hidden items
	_FILE_FINDER_ENUMERATION_SKIP_HIDDEN_ITEM		= _FILE_FINDER_ENUMERATION_SKIP_HIDDEN_FILE | _FILE_FINDER_ENUMERATION_SKIP_HIDDEN_DIRECTORY,
	//!	The directory mask
	_FILE_FINDER_DIRECTORY_MASK						= _FILE_FINDER_ENUMERATION_RECURSIVE | _FILE_FINDER_ENUMERATION_SKIP_HIDDEN_ITEM | _FILE_FINDER_ENUMERATION_DIRECTORY_ONLY,
	//!	The file mask
	_FILE_FINDER_FILE_MASK							= _FILE_FINDER_ENUMERATION_RECURSIVE | _FILE_FINDER_ENUMERATION_SKIP_HIDDEN_ITEM | _FILE_FINDER_ENUMERATION_FILE_ONLY,
};

//! Language
enum _LANG
{
	_LANG_UNKNOWN,

	_LANG_ENG,
	_LANG_CHS,
	_LANG_CHT,
};

//!	Pipe access mode
enum _PIPE_ACCESS
{
	_PIPE_ACCESS_INBOUND    = 1,
	_PIPE_ACCESS_OUTBOUND   = 2,
	_PIPE_ACCESS_DUPLEX		= 3,
};

//!	Pipe type mode
enum _PIPE_TYPE
{
	_PIPE_TYPE_BYTE              		= 0x00000000,
	_PIPE_TYPE_NOWAIT                 	= 0x00000001,
	_PIPE_TYPE_READMODE_MESSAGE			= 0x00000002,
	_PIPE_TYPE_MESSAGE           		= 0x00000004,
	_PIPE_TYPE_REJECT_REMOTE_CLIENTS	= 0x00000008,
};

//!	Clipboard flag
enum _CLIPBOARD_FLAG
{
	_CLIPBOARD_TEXT			= 1,
	_CLIPBOARD_BITMAP       = 2,
	_CLIPBOARD_METAFILEPICT = 3,
	_CLIPBOARD_SYLK         = 4,
	_CLIPBOARD_DIF          = 5,
	_CLIPBOARD_TIFF         = 6,
	_CLIPBOARD_OEMTEXT      = 7,
	_CLIPBOARD_DIB          = 8,
	_CLIPBOARD_PALETTE      = 9,
	_CLIPBOARD_PENDATA      = 10,
	_CLIPBOARD_RIFF         = 11,
	_CLIPBOARD_WAVE         = 12,
	_CLIPBOARD_UNICODETEXT  = 13,
	_CLIPBOARD_ENHMETAFILE  = 14,
};

//!	The mouse button type
enum _MOUSE_BUTTON
{
	_MB_UNKNOWN,
	_MB_LEFT,
	_MB_MIDDLE,
	_MB_RIGHT,
};

//!	The domain family type
enum _DOMAIN_FAMILY_TYPE
{
	_DOMAIN_AF_INET,
	_DOMAIN_AF_INET6,
};

//!	The socket type
enum _SOCKET_TYPE
{
	_SOCK_STREAM,
	_SOCK_DGRAM,
	_SOCK_RAW,
	_SOCK_SEQPACKET,
};

}