#pragma once

namespace EGE {

// Windows Platform
#if defined _PLATFORM_WINDOWS_

#	include <WinSock2.h>
#	include <errno.h>

#	define MSG_NOSIGNAL 0

//! The socket handle
typedef SOCKET _socket;

// IOS Platform
#elif defined(_PLATFORM_IOS_)

#	include <arpa/inet.h>
#	include <errno.h>
#	include <fcntl.h>
#	include <netdb.h>
#	include <netinet/in.h>
#	include <netinet/tcp.h>
#	include <signal.h>
#	include <sys/ioctl.h>
#	include <sys/select.h>
#	include <sys/stat.h>
#	include <sys/types.h>
#	include <sys/uio.h>
#	include <unistd.h>

#	ifndef SOCKET
#		define SOCKET int
#	endif

#	ifndef MSG_NOSIGNAL
#		define MSG_NOSIGNAL 0
#	endif

#	ifndef INVALID_SOCKET
#		define INVALID_SOCKET (SOCKET)(~0)
#	endif

#	define closesocket close
#	define ioctlsocket ioctl

//! The socket handle
typedef SOCKET _socket;

// Android Platform
#elif defined(_PLATFORM_ANDROID_)

#	include <arpa/inet.h>
#	include <errno.h>
#	include <fcntl.h>
#	include <netdb.h>
#	include <netinet/in.h>
#	include <netinet/tcp.h>
#	include <signal.h>
#	include <sys/ioctl.h>
#	include <sys/select.h>
#	include <sys/stat.h>
#	include <sys/types.h>
#	include <sys/uio.h>
#	include <unistd.h>

#	ifndef SOCKET
#		define SOCKET int
#	endif

#	ifndef MSG_NOSIGNAL
#		define MSG_NOSIGNAL 0x4000
#	endif

#	ifndef INVALID_SOCKET
#		define INVALID_SOCKET (SOCKET)(~0)
#	endif

#	define closesocket close
#	define ioctlsocket ioctl

//! The socket handle
typedef SOCKET _socket;

// Linux Platform
#elif defined(_PLATFORM_LINUX_)

#	include <unistd.h>
#	include <sys/socket.h>

//! The socket handle
typedef int _socket;

#endif

} // namespace EGE
