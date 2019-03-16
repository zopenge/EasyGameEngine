//! @file     NetworkOSHeader.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

// Windows Platform
#if defined _PLATFORM_WINDOWS_

	#include <WinSock2.h>
	#include <errno.h>

	#define MSG_NOSIGNAL	0

	//!	The socket handle
	typedef SOCKET	_socket;

// IOS Platform
#elif defined(_PLATFORM_IOS_)

    #include <errno.h>
    #include <unistd.h>
    #include <fcntl.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <signal.h>
    #include <sys/stat.h>
    #include <sys/select.h>
	#include <sys/ioctl.h>
	#include <sys/types.h>
	#include <sys/uio.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>

	#ifndef SOCKET
		#define SOCKET int
	#endif

	#ifndef MSG_NOSIGNAL
		#define MSG_NOSIGNAL 0
	#endif

	#ifndef INVALID_SOCKET
		#define INVALID_SOCKET  (SOCKET)(~0)
	#endif

	#define closesocket close
	#define ioctlsocket ioctl

	//!	The socket handle
	typedef SOCKET	_socket;

// Android Platform
#elif defined(_PLATFORM_ANDROID_)
	
	#include <errno.h>
	#include <unistd.h>
	#include <fcntl.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <signal.h>
	#include <sys/stat.h>
	#include <sys/select.h>
	#include <sys/ioctl.h>
	#include <sys/types.h>
	#include <sys/uio.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>
		
	#ifndef SOCKET
	#define SOCKET int
	#endif
		
	#ifndef MSG_NOSIGNAL
	#define MSG_NOSIGNAL 0x4000
	#endif
		
	#ifndef INVALID_SOCKET
	#define INVALID_SOCKET  (SOCKET)(~0)
	#endif
		
	#define closesocket close
	#define ioctlsocket ioctl
	
	//!	The socket handle
	typedef SOCKET	_socket;
	
// OSX Platform
#elif defined(_PLATFORM_OSX_)

// Chrome Platform
#elif defined(_PLATFORM_CHROME_)

	//!	The socket handle
	typedef void* _socket;

#endif

}
