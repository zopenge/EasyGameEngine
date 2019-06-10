#pragma once

// Enable/Disable google-break-pad SDK: http://code.google.com/p/google-breakpad/
#if defined(_PLATFORM_WINDOWS_) || defined(_PLATFORM_ANDROID_) || defined(_PLATFORM_IOS_)
#	if (_PLATFORM_ARCH_64 == 1)
#		define USE_GOOGLE_BREAK_PAD 1
// SigCatch : http://stackoverflow.com/questions/1083154/how-can-i-catch-sigsegv-segmentation-fault-and-get-a-stack-trace-under-jni-on
#		define USE_SIG_ACTION 0
#	else
#		define USE_GOOGLE_BREAK_PAD 0
#	endif
#else
#	define USE_GOOGLE_BREAK_PAD 0
#endif

#if (USE_GOOGLE_BREAK_PAD == 1) && (USE_SIG_ACTION == 1)
#	error We must choose to use google-breakpad or sig action
#endif

#if (USE_GOOGLE_BREAK_PAD == 1)

#	ifdef _PLATFORM_WINDOWS_
#		include "client/windows/crash_generation/client_info.h"
#		include "client/windows/crash_generation/crash_generation_server.h"
#		include "client/windows/handler/exception_handler.h"
#		include "client/windows/common/ipc_protocol.h"
#	elif _PLATFORM_ANDROID_
#		include "client/linux/handler/minidump_descriptor.h"
#		include "client/linux/handler/exception_handler.h"
#	elif _PLATFORM_IOS_
#		ifdef __OBJC__
#			import "client/ios/Breakpad.h"
#		endif
#	endif

#endif

// Pcre SDK
#define PCRE_EXP_DEFN
#define PCRE_EXP_DATA_DEFN
#include "config.h"
#include "pcre.h"

// FreeType2 SDK
#ifdef __cplusplus
extern "C" {
#endif
#ifdef _PLATFORM_WINDOWS_
// http://stackoverflow.com/questions/13122266/freetype-generic-conflict-with-c-cx-keyword
#	define generic GenericFromFreeTypeLibrary
#endif
#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_GLYPH_H
#include FT_STROKER_H
#include FT_MODULE_H
#undef generic // The freetype2 SDK will compile failed by using this keyword in CLR mode
#ifdef __cplusplus
}
#endif

// ZLib SDK
#include "zlib.h"

// The ZIP SDK library config
//#define _USE_LITE_ZIP_SDK_
#define _USE_LIBZIP_SDK_

// ZipUtils SDK
#include "LiteUnzip.h"
#include "LiteZip.h"

// tinyxml2 SDK
#include "tinyxml2.h"

// cJSON SDK
#include "cJSON.h"

// LibPNG SDK
#include "png.h"
#include "pngstruct.h"

// LibWebP SDK
#include "webp/decode.h"
#include "webp/demux.h"

// LibJPEG SDK
#include "jerror.h"
#include "jinclude.h"
#include "jpeglib.h"
#include "jversion.h"

// LibGif SDK
#include "gif_lib.h"

// LibWebM SDK
#ifdef _PLATFORM_WINDOWS_
#	pragma warning(push)
#	pragma warning(disable : 4819)
#	pragma warning(disable : 4146)
#	pragma warning(disable : 4369)
#endif
#include "mkvparser/mkvparser.h"
#include "webm/callback.h"
#include "webm/status.h"
#include "webm/webm_parser.h"
#ifdef _PLATFORM_WINDOWS_
#	pragma warning(pop)
#endif

// Lib7z SDK
#ifndef _EGE_DISABLE_7Z_FILE_
#	ifdef __cplusplus
extern "C" {
#	endif
#	include "7z.h"
#	include "7zCrc.h"
#	include "7zFile.h"
#	include "7zVersion.h"
#	ifdef __cplusplus
}
#	endif
#endif

// LibCSV SDK
#ifndef _EGE_DISABLE_CSV_FILE_
#	include "csv.h"
#endif

// LibFlac SDK
#ifndef _EGE_DISABLE_FLAC_FILE_
#	include "FLAC/all.h"
#endif

// LibOGG SDK
#include "ogg/ogg.h"

// LibVorbis SDK
#include "vorbis/vorbisenc.h"
#include "vorbis/vorbisfile.h"

// LibSpeex SDK
#ifndef _EGE_DISABLE_SPEEX_FILE_
#	include "speex/speex.h"
#endif

// DESCrypto SDK
#include "des.h"

// AESCrypto SDK
#include "oaes_lib.h"