//! @file     EGENetwork.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#ifndef _EGE_NETWORK_PCH_
#define _EGE_NETWORK_PCH_

// Windows Platform
#if defined _PLATFORM_WINDOWS_

	#include "Platform/OS/windows/Win32Headers.h"
	#include "Platform/OS/windows/Win32Macros.h"

	// Use cURL SDK
	#define _USE_CRUL_SDK	1

// IOS Platform
#elif defined _PLATFORM_IOS_

	#include <netdb.h>

	// Use cURL SDK
	#define _USE_CRUL_SDK	1

// Android Platform
#elif defined _PLATFORM_ANDROID_

	// Use cURL SDK
	#define _USE_CRUL_SDK	1

// Chrome Platform
#elif defined _PLATFORM_CHROME_

	// Use Chrome SDK
	#define _USE_CHROME_SDK	1

#endif

// cURL SDK
#if (_USE_CRUL_SDK == 1)
extern "C" {
#include "curl/curl.h"
}
#endif

// EasyGameEngine Configures
#include "EGE_Compile.h"

// Protocol Files
#include <google/protobuf/message_lite.h>
#include "Protocols/NetworkPacket/CPP/NetworkPacket.pb.h"

// EasyGameEngine Headers
#include "EGE_Always.h"
#include "EGE_Engine.h"
#include "EGE_Modules.h"
#include "Interface/Module/EGE_Network.h"

// Log Files
#undef DEFINE_MODULE 
#define DEFINE_MODULE gNetworkModule->
#include "EGE_Logs.h"

// Outside Function Implementations
#include "EGEExterns.h"

// Null Classes
#include "Module/Network/NetworkNullClasses.h"

// Global variables
extern EGE::INetworkResourceManager*	gNetworkResourceManager;
extern EGE::INetworkModule*				gNetworkModule;

// Network SDK Files
#include "Module/Network/network/_networkHelper.h"
#include "Module/Network/network/_networkRequest.h"
#if (_USE_CRUL_SDK == 1)
#include "Module/Network/network/curl/_curlHelper.h"
#include "Module/Network/network/curl/_curlDataList.h"
#include "Module/Network/network/curl/_curlHandle.h"
#include "Module/Network/network/curl/_curlMultiHandle.h"
#elif (_USE_CHROME_SDK == 1)
#include "Module/Network/network/chrome/_chromeHelper.h"
#endif

// Network Operation Files
#include "Module/Network/Operations/NetworkConnectOperation.h"
#include "Module/Network/Operations/NetworkRecvOperation.h"
#include "Module/Network/Operations/NetworkSendOperation.h"

// Network Notifier Files
#include "Module/Network/NetworkProtoBufNotifier.h"

// Template Files
#include "Module/Network/Template/TNetworkStreamReader.h"
#include "Module/Network/Template/TNetworkConnection.h"
#include "Module/Network/Template/TNetworkHTTPConnection.h"
#include "Module/Network/Template/TNetworkStation.h"
#include "Module/Network/Template/TNetworkProtoBufConnection.h"

// Network Files
#include "Module/Network/NetworkVersion.h"
#include "Module/Network/NetworkFTPCodes.h"
#include "Module/Network/NetworkProtocol.h"
// Network HTTP/FTP Files
#if (_USE_CRUL_SDK == 1)
#include "Module/Network/network/curl/NetworkHTTPConnection.curl.h"
#include "Module/Network/network/curl/NetworkFTPStreamReader.curl.h"
#include "Module/Network/network/curl/NetworkFTPConnection.curl.h"
#elif (_USE_CHROME_SDK == 1)
#include "Module/Network/network/chrome/NetworkHTTPStreamReader.chrome.h"
#include "Module/Network/network/chrome/NetworkHTTPConnection.chrome.h"
#include "Module/Network/network/chrome/NetworkFTPStreamReader.chrome.h"
#include "Module/Network/network/chrome/NetworkFTPConnection.chrome.h"
#endif
#include "Module/Network/NetworkConnectionNotifier.h"
#include "Module/Network/NetworkTCPConnection.h"
#include "Module/Network/NetworkTCPStation.h"
#include "Module/Network/NetworkNamedPipeConnection.h"
#include "Module/Network/NetworkNamedPipeStation.h"
#include "Module/Network/NetworkBluetoothConnection.h"
#include "Module/Network/NetworkBluetoothStation.h"
#include "Module/Network/NetworkProtoBufTCPConnection.h"
#include "Module/Network/NetworkProtoBufHTTPConnection.h"
#include "Module/Network/NetworkProtoBufNamedPipeConnection.h"
#include "Module/Network/NetworkConnectionThread.h"
#include "Module/Network/NetworkHTTPStreamReader.h"
#include "Module/Network/NetworkHTTPArchive.h"
#include "Module/Network/NetworkResourceManager.h"
#include "Module/Network/NetworkModule.h"

// Using namespace here to prevent some name conflict 
using namespace EGE;

// Link external libraries
#if defined _PLATFORM_WINDOWS_
	#pragma comment( lib, "libc-ares.lib" )
	#if (_USE_CRUL_SDK == 1)
	#pragma comment( lib, "libcurl.lib" )
	#endif
#elif defined _PLATFORM_IOS_

#endif

#endif // _EGE_NETWORK_PCH_
