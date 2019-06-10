#ifndef _EGE_ENGINE_PCH_
#define _EGE_ENGINE_PCH_

// Capture std stream
#ifdef _PLATFORM_WINDOWS_
#	define _ENABLE_CAPTURE_STD_STREAM 1
#else
#	define _ENABLE_CAPTURE_STD_STREAM 0
#endif

// Standard Files
#if _ENABLE_CAPTURE_STD_STREAM == 1
#	include <iostream>
#	include <streambuf>
#endif

// Windows Platform
#if defined _PLATFORM_WINDOWS_

// Windows Files
#	include "Platform/OS/windows/Win32Headers.h"
#	include <psapi.h>
#	include <iostream>
#	include <setupapi.h>
#	include <shlwapi.h>
#	include <unknwn.h>
#	include <objbase.h>
#	include <shobjidl.h>
#	include <netfw.h>
#	include <shellapi.h>
#	include <wininet.h>
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <wspiapi.h>
#	include <ws2bth.h>
#	include <MMSystem.h>
#	include <cguid.h>
#	include <atlbase.h>
#	include <atlwin.h>
#	include <exdispid.h>
#	include <exdisp.h>
#	include "Platform/OS/windows/Win32Macros.h"

// IOS Platform
#elif defined _PLATFORM_IOS_

// Foundation Files
#	ifdef __OBJC__
#		import <Availability.h>
#		import <Foundation/Foundation.h>
#		import <QuartzCore/QuartzCore.h>
#		import <UIKit/UIKit.h>
#		import <GameKit/GameKit.h>
#		import <StoreKit/StoreKit.h>
#		import <AdSupport/ASIdentifierManager.h>
#		import <Security/SecItem.h>
#		import <CoreBluetooth/CoreBluetooth.h>
#	endif

// System Files
#	include <net/if.h>
#	include <net/if_dl.h>
#	include <netdb.h>
#	include <sys/stat.h>
#	include <sys/sysctl.h>

// Pass the 'libtiff' compile error when typedef the 'int64/uint64' types
#	define __xlc__

// Android Platform
#elif defined _PLATFORM_ANDROID_

// Android Files
#	include <netdb.h>
#	include <signal.h>
#	include <unistd.h>
#	include <errno.h>
#	include <sys/wait.h>
#	include <sys/stat.h>
#	include <linux/un.h>

// NDK Files
#	include <android/keycodes.h>
#	include <android/configuration.h>
#	include <android/asset_manager.h>
#	include <android/asset_manager_jni.h>
#	include <android/native_window_jni.h>

// android-ndk-profiler Files
#	include "prof.h"

// Unknown Platform
#else
#	error "Unknown Platform"
#endif

// EasyGameEngine SDK Files
#include "Engine/EngineSDKFiles.h"

// EasyGameEngine Headers
#include "EGE_Always.h"
#include "EGE_Engine.h"
#include "EGE_Modules.h"

// Log Files
#undef DEFINE_MODULE
#define DEFINE_MODULE gModuleManager->
#include "EGE_Logs.h"

// Null Classes
#include "Engine/EngineNullClasses.h"

// Global variables
extern EGE::_dword gFrameNumber;
extern EGE::_handle gMainWindowHandle;
extern EGE::IViewBasedApp* gMainViewBasedApp;
extern EGE::IGarbageCollector* gGarbageCollector;
extern EGE::IAppDelegate* gAppDelegate;
extern EGE::IModuleManager* gModuleManager;

// std-Platform Files
#if _ENABLE_CAPTURE_STD_STREAM == 1
#	include "Engine/std/stdCapture.h"
#	include "Engine/std/stdStreamBuf.h"
#	include "Engine/std/stdStreamPipe.h"
#endif

// Engine Files
#include "Engine/Allocator/BufferAllocator.h"
#include "Engine/Allocator/LinearAllocator.h"
#include "Engine/Allocator/MemAllocator.h"
#include "Engine/Allocator/OffsetAllocator.h"
#include "Engine/Allocator/PageAllocator.h"
#include "Engine/Allocator/RangeAllocator.h"
#include "Engine/Allocator/RingAllocator.h"
#include "Engine/Allocator/StackAllocator.h"
#include "Engine/Allocator/StdAllocator.h"
#include "Engine/Archive/FileArchive.h"
#include "Engine/Archive/LocalArchive.h"
#include "Engine/Archive/MemoryArchive.h"
#include "Engine/Archive/PEResArchive.h"
#include "Engine/Buffer/CacheBuffer.h"
#include "Engine/Compression/CompressionDecoderZLIB.h"
#include "Engine/Compression/CompressionEncoderZLIB.h"
#include "Engine/Decoder/OGGDecoder.h"
#include "Engine/Encryption/AESDecryptor.h"
#include "Engine/Encryption/AESEncryptor.h"
#include "Engine/Encryption/DESDecryptor.h"
#include "Engine/Encryption/DESEncryptor.h"
#include "Engine/EngineVersion.h"
#include "Engine/File/FileCopier.h"
#include "Engine/FileParser/ASTCFile.h"
#include "Engine/FileParser/BMPFile.h"
#include "Engine/FileParser/BinaryXMLFile.h"
#include "Engine/FileParser/CSVFile.h"
#include "Engine/FileParser/DDSFile.h"
#include "Engine/FileParser/FLACFile.h"
#include "Engine/FileParser/FNTFile.h"
#include "Engine/FileParser/GIFFile.h"
#include "Engine/FileParser/GeometryFile.h"
#include "Engine/FileParser/HTMLFile.h"
#include "Engine/FileParser/JPGFile.h"
#include "Engine/FileParser/JSONFile.h"
#include "Engine/FileParser/KTXFile.h"
#include "Engine/FileParser/MIDIFile.h"
#include "Engine/FileParser/ManifestFile.h"
#include "Engine/FileParser/MarkupFileLangFile.h"
#include "Engine/FileParser/OGGFile.h"
#include "Engine/FileParser/PKMFile.h"
#include "Engine/FileParser/PNGFile.h"
#include "Engine/FileParser/PSDFile.h"
#include "Engine/FileParser/PVRTexFile.h"
#include "Engine/FileParser/PackageFile.h"
#include "Engine/FileParser/SZFile.h"
#include "Engine/FileParser/SpeexFile.h"
#include "Engine/FileParser/StreamingPCMFile.h"
#include "Engine/FileParser/TGAFile.h"
#include "Engine/FileParser/WAVFile.h"
#include "Engine/FileParser/WEBMFile.h"
#include "Engine/FileParser/WEBPFile.h"
#include "Engine/FileParser/XMLFile.h"
#include "Engine/FileParser/ZIPFile.h"
#include "Engine/Font/FontFaceFNT.h"
#include "Engine/Font/FontFaceFreeType2.h"
#include "Engine/Font/FontFaceFreeType2Lib.h"
#include "Engine/GarbageCollector.h"
#include "Engine/Image/Filter/Filter.h"
#include "Engine/Image/Filter/Resize.h"
#include "Engine/Image/ImageFillerBinaryTree.h"
#include "Engine/Image/ImageFillerLinear.h"
#include "Engine/Image/ImageFillerScanLines.h"
#include "Engine/Image/ImageProcessor.h"
#include "Engine/InterfaceFactory/InterfaceFactory.h"
#include "Engine/Layout/Aligner.h"
#include "Engine/Layout/AlignerObjectBase.h"
#include "Engine/Layout/AlignerObjectBlock.h"
#include "Engine/Layout/AlignerObjectLine.h"
#include "Engine/Layout/MeasurableObject.h"
#include "Engine/Logger/Logger.h"
#include "Engine/Manifest/ManifestFileManager.h"
#include "Engine/Math/Interpolator.h"
#include "Engine/Math/MD5ChecksumBuilder.h"
#include "Engine/Math/ProjectileObject.h"
#include "Engine/ModuleManager.h"
#include "Engine/Parser/CommandLineParser.h"
#include "Engine/Parser/RegularExpression.h"
#include "Engine/Platform/TBluetoothAdapter.h"
#include "Engine/Platform/TBluetoothDevice.h"
#include "Engine/Platform/TControllerManager.h"
#include "Engine/Platform/TEditBox.h"
#include "Engine/Platform/TJoystick.h"
#include "Engine/Platform/TMessageBox.h"
#include "Engine/Platform/TPlatform.h"
#include "Engine/Platform/TWebView.h"
#include "Engine/Properties/Properties.h"
#include "Engine/ProtoBuf/ProtoBufMessageProcessor.h"
#include "Engine/ProtoBuf/ProtoBufProcessor.h"
#include "Engine/Recorder/ActionRecorder.h"
#include "Engine/Recorder/InputRecordTrace.h"
#include "Engine/Recorder/InputRecorder.h"
#include "Engine/Recorder/OperationRecorder.h"
#include "Engine/Resource/ResCaches.h"
#include "Engine/Resource/ResLoader.h"
#include "Engine/Resource/ResLoaderTask.h"
#include "Engine/Resource/ResLoaderTaskGroup.h"
#include "Engine/Serialization/MarkupLangSerializableNode.h"
#include "Engine/Serialization/MarkupLangSerializableNodeWalker.h"
#include "Engine/Stream/AStringStreamReader.h"
#include "Engine/Stream/BitStreamReader.h"
#include "Engine/Stream/BitStreamWriter.h"
#include "Engine/Stream/FileStreamReader.h"
#include "Engine/Stream/FileStreamWriter.h"
#include "Engine/Stream/MemStreamReader.h"
#include "Engine/Stream/MemStreamWriter.h"
#include "Engine/Stream/PEResStreamReader.h"
#include "Engine/Stream/PEResStreamWriter.h"
#include "Engine/Stream/SafeStreamReader.h"
#include "Engine/Stream/StreamWriterProcessor.h"
#include "Engine/Stream/UStringStreamReader.h"
#include "Engine/Stream/WStringStreamReader.h"
#include "Engine/StringTable/StringTable.h"
#include "Engine/Thread/SingleThreadPool.h"
#include "Engine/Thread/ThreadPool.h"
#include "Engine/Thread/ThreadTaskProcessor.h"
#include "Engine/Thread/ThreadTaskQueue.h"
#include "Engine/Thread/ThreadTaskWorker.h"
#include "Engine/Transaction/TransactionManager.h"

// Template Files
#include "Engine/Application/TApplication.h"
#include "Engine/Application/TViewBasedApp.h"

// Windows Platform
#if defined _PLATFORM_WINDOWS_

#	include "Engine/Platform/win/COMBSTR.h"
#	include "Engine/Platform/win/UI/winEditBox.h"
#	include "Engine/Platform/win/UI/winWebView.h"
#	include "Engine/Platform/win/UI/winMenu.h"
#	include "Engine/Platform/win/UI/winMessageBox.h"
#	include "Engine/Platform/win/Network/winBluetooth.h"
#	include "Engine/Platform/win/Network/winNet.h"
#	include "Engine/Platform/win/Network/winNetFirewall.h"
#	include "Engine/Platform/win/Kernel/winShell.h"
#	include "Engine/Platform/win/Kernel/winRegistry.h"
#	include "Engine/Platform/win/Kernel/winProcessDebugger.h"
#	include "Engine/Platform/win/SensorManager/winSensorManager.h"
#	include "Engine/Platform/win/Controller/winJoystick.h"
#	include "Engine/Platform/win/Controller/winControllerManager.h"
#	include "Engine/Platform/win/winPlatform.h"

#	include "Engine/Application/win/winConsoleApp.h"
#	include "Engine/Application/win/winApp.h"
#	include "Engine/Application/win/winViewBasedApp.h"

// IOS Platform
#elif defined _PLATFORM_IOS_

#	include "Engine/Platform/ios/NSAPI.h"

#	include "Engine/Platform/ios/Network/iosBluetooth.h"
#	include "Engine/Platform/ios/Network/iosNet.h"
#	include "Engine/Platform/ios/SensorManager/iosSensorManager.h"
#	include "Engine/Platform/ios/Controller/iosControllerManager.h"
#	include "Engine/Platform/ios/Kernel/iosKeychain.h"
#	include "Engine/Platform/ios/UI/WebView/iosWebView.h"
#	include "Engine/Platform/ios/UI/EditBox/iosEditBox.h"
#	include "Engine/Platform/ios/iosPlatform.h"
#	include "Engine/Application/ios/iosViewBasedApp.h"

#	ifdef __OBJC__
#		import "Engine/Application/ios/NSUIView.h"
#		import "Engine/Application/ios/NSUIViewController.h"
#		import "Engine/Application/ios/NSApplication.h"
#		import "Engine/Platform/ios/Network/NSReachability.h"
#		import "Engine/Platform/ios/SensorManager/NSSensorManager.h"
#		import "Engine/Platform/ios/Kernel/KeychainItemWrapper.h"
#		import "Engine/Platform/ios/UI/EditBox/NSEditBoxView.h"
#		import "Engine/Platform/ios/UI/WebView/NSWebView.h"
#	endif

// Android Platform
#elif defined _PLATFORM_ANDROID_

#	include "Engine/Application/android/androidMessages.h"
using namespace EGE::AndroidMessages;

#	include "Engine/Application/android/androidJNI.h"
#	include "Engine/Application/android/androidAppXML.h"
#	include "Engine/Application/android/androidViewBasedApp.h"

#	include "Engine/Platform/android/JNIClasses.h"
#	include "Engine/Platform/android/JNIObject.h"

#	include "Engine/Platform/android/UI/androidEditBox.h"
#	include "Engine/Platform/android/UI/androidMessageBox.h"
#	include "Engine/Platform/android/UI/androidWebView.h"
#	include "Engine/Platform/android/Network/androidBluetooth.h"
#	include "Engine/Platform/android/Network/androidNet.h"
#	include "Engine/Platform/android/SensorManager/androidSensorManager.h"
#	include "Engine/Platform/android/Controller/androidJoystick.h"
#	include "Engine/Platform/android/Controller/androidControllerManager.h"
#	include "Engine/Platform/android/androidPlatform.h"

// The ZLIB SDK not define 'z_const' on android
#	ifndef z_const
#		define z_const
#	endif

#endif

// The global variables
#if _ENABLE_CAPTURE_STD_STREAM == 1
extern EGE::stdCapture* sstdCapture;
extern EGE::stdTraceStreamBuf* sstdTraceStreamBuf;
extern EGE::stdErrorStreamBuf* sstdErrorStreamBuf;
extern EGE::stdTraceStreamPipe* sstdTraceStreamPipe;
extern EGE::stdErrorStreamPipe* sstdErrorStreamPipe;
#endif
#if defined(_PLATFORM_ANDROID_)
extern EGE::androidViewBasedApp gAndroidViewbasedApp;
#endif

// Using namespace here to prevent some name conflict
using namespace EGE;

// Link external libraries
#if defined _PLATFORM_WINDOWS_
#	pragma comment(lib, "psapi")
#	pragma comment(lib, "libgoogle-breakpad.lib")
#	pragma comment(lib, "liblibfreetype.lib")
#	pragma comment(lib, "liblibjpeg.lib")
#	pragma comment(lib, "liblibgif.lib")
#	pragma comment(lib, "liblibpng.lib")
#	pragma comment(lib, "liblibpcre.lib")
#	pragma comment(lib, "liblibflac.lib")
#	pragma comment(lib, "liblibwebp.lib")
#	pragma comment(lib, "liblibogg.lib")
#	pragma comment(lib, "liblibvorbis.lib")
#	pragma comment(lib, "liblib7z.lib")
#	pragma comment(lib, "libzlib.lib")
#	pragma comment(lib, "liblibwebm.lib")
#	ifndef _EGE_DISABLE_HTML_FILE_
#		pragma comment(lib, "libgumbo.lib")
#	endif
#	ifndef _USE_TINY_XML2_
#		pragma comment(lib, "libxml2.lib")
#	endif
#	if defined(_USE_LIBZIP_SDK_)
#		pragma comment(lib, "liblibzip.lib")
#	endif
#	pragma comment(lib, "libprotobuf.lib")

#elif defined _PLATFORM_IOS_

#endif

#endif // _EGE_ENGINE_PCH_