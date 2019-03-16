//! @file     anyPlatformNetwork.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// anyPlatformNetwork Helpful Enumerations
//----------------------------------------------------------------------------

//! The operation type
enum _NET_OP_TYPE
{
 _NET_OP_NO_DATA,
 _NET_OP_CONTINUE,
 _NET_OP_FINISHED,
 _NET_OP_ERROR,
};

//! The address info
struct AddrInfo 
{
 int   ai_flags;
 int   ai_family;
 int   ai_socktype;
 int   ai_protocol;
 int   ai_addrlen;
 sockaddr* ai_addr;
 AddrInfo* ai_next;
};

//! Free address info
_void FreeAddrInfo( AddrInfo* cahead )
{
 AddrInfo* volatile canext;
 AddrInfo* ca;

 for ( ca = cahead; ca != _null; ca = canext ) 
 {
  free( ca->ai_addr );
  canext = ca->ai_next;

  free( ca );
 }
}

//! Get the address info.
int GetAddrInfoEx( const char *nodename, const char *servname, const struct addrinfo *hints, AddrInfo **result )
{
 const struct addrinfo *ai;
 struct addrinfo *aihead;
 AddrInfo *cafirst = _null;
 AddrInfo *calast = _null;
 AddrInfo *ca;
 size_t ss_size;
 int error;

 *result = _null; /* assume failure */

 error = getaddrinfo( nodename, servname, hints, &aihead );
 if ( error )
  return error;

 /* traverse the addrinfo list */

 for ( ai = aihead; ai != _null; ai = ai->ai_next ) {

  /* ignore elements with unsupported address family, */
  /* settle family-specific sockaddr structure size.  */
  if ( ai->ai_family == AF_INET )
   ss_size = sizeof( struct sockaddr_in );
  else if ( ai->ai_family == AF_INET6 )
   ss_size = sizeof( struct sockaddr_in6 );
  else
   continue;

  /* ignore elements without required address info */
  if ( (ai->ai_addr == _null) || !(ai->ai_addrlen > 0) )
   continue;

  /* ignore elements with bogus address size */
  if ( (size_t)ai->ai_addrlen < ss_size )
   continue;

  ca = (AddrInfo*)malloc( sizeof( AddrInfo ) );
  if ( !ca ) {
   error = EAI_MEMORY;
   break;
  }

  /* copy each structure member individually, member ordering, */
  /* size, or padding might be different for each platform.    */

  ca->ai_flags = ai->ai_flags;
  ca->ai_family = ai->ai_family;
  ca->ai_socktype = ai->ai_socktype;
  ca->ai_protocol = ai->ai_protocol;
  ca->ai_addrlen = (int)ss_size;
  ca->ai_addr = _null;
  ca->ai_next = _null;

  ca->ai_addr = (sockaddr*)malloc( ss_size );
  if ( !ca->ai_addr ) {
   error = EAI_MEMORY;
   free( ca );
   break;
  }
  memcpy( ca->ai_addr, ai->ai_addr, ss_size );

  /* if the return list is empty, this becomes the first element */
  if ( !cafirst )
   cafirst = ca;

  /* add this element last in the return list */
  if ( calast )
   calast->ai_next = ca;
  calast = ca;

 }

 /* destroy the addrinfo list */
 if ( aihead )
  freeaddrinfo( aihead );

 /* if we failed, also destroy the AddrInfo list */
 if ( error ) {
  FreeAddrInfo( cafirst );
  cafirst = _null;
 }
 else if ( !cafirst ) {
  error = EAI_NONAME;
 }

 *result = cafirst;

 /* This is not a CURLcode */
 return error;
}

void SetAddrInfoPort( AddrInfo *addrinfo, int port )
{
 AddrInfo *ca;
 struct sockaddr_in *addr;
 struct sockaddr_in6 *addr6;

 for ( ca = addrinfo; ca != NULL; ca = ca->ai_next ) {
  switch ( ca->ai_family ) {
  case AF_INET:
   addr = (sockaddr_in*)ca->ai_addr; /* storage area for this info */
   addr->sin_port = htons( (unsigned short)port );
   break;

  case AF_INET6:
   addr6 = (sockaddr_in6*)ca->ai_addr; /* storage area for this info */
   addr6->sin6_port = htons( (unsigned short)port );
   break;
  }
 }
}

//----------------------------------------------------------------------------
// anyPlatformNetwork Helpful Functions Implementation
//----------------------------------------------------------------------------

static _dword TranslateDomainFamilyType( _DOMAIN_FAMILY_TYPE families )
{
 switch ( families )
 {
  case _DOMAIN_AF_INET: return AF_INET;
  case _DOMAIN_AF_INET6: return AF_INET6;
  default:
   return 0;
 }
}

static _dword TranslateSocketType( _SOCKET_TYPE type )
{
 switch ( type )
 {
  case _SOCK_STREAM:  return SOCK_STREAM;
  case _SOCK_DGRAM:  return SOCK_DGRAM;
  case _SOCK_RAW:   return SOCK_RAW;
  case _SOCK_SEQPACKET: return SOCK_SEQPACKET;
  default:
   return 0;
 }
}

static _NET_OP_TYPE CheckConnectionError( )
{
 // Process it with error ID
 _dword err_id = errno;
 switch ( err_id )
 {
  // The operation be interrupted, so try it again
  case EINTR:
  case EAGAIN:
  {
   return _NET_OP_CONTINUE;
  }
  break;

  case 0:
  case EBADF:
  {
   return _NET_OP_ERROR;
  }
  break;

  default:
   break;
 }

 return _NET_OP_FINISHED;
}

static _int CheckConnectionStatus( _socket handle, _dword timeout )
{
 // Set the interval
 struct timeval tm;
 tm.tv_sec = 0;
 tm.tv_usec = timeout * 1000;

 // Initialize the interval
 fd_set set, rset;
 FD_ZERO( &set );
 FD_ZERO( &rset );
 FD_SET( handle, &set );
 FD_SET( handle, &rset );

 // Wait for event
 return select( handle + 1, &rset, &set, _null, &tm );
}

static _NET_OP_TYPE GetOperationResult( _socket handle, _dword ret )
{
 switch ( ret )
 {
  // Connection closed
  case 0:
   return _NET_OP_ERROR;

  // Check the error, maybe something wrong
  case 0xFFFFFFFF:
  {
   // Check connection error
   _NET_OP_TYPE op_type = CheckConnectionError( );
   if ( op_type == _NET_OP_ERROR )
   {
    _int result = CheckConnectionStatus( handle, 10 );
    if ( result != 0 && result != 1 )
     return _NET_OP_ERROR;

    return _NET_OP_NO_DATA;
   }
  }
  break;

  // Read successful
  default:
   break;
 }

 return _NET_OP_FINISHED;
}

//----------------------------------------------------------------------------
// anyPlatformNetwork Implementation
//----------------------------------------------------------------------------

_dword anyPlatformNetwork::GetURLIPAddress( const _chara* url_address )
{
 if ( url_address == _null )
  return 0;

 // Get the address info of URL address
 addrinfo* result = _null;
 addrinfo hints = { 0 };
 hints.ai_family  = AF_UNSPEC;
 hints.ai_socktype = SOCK_STREAM;
 hints.ai_protocol = IPPROTO_TCP;
 if ( getaddrinfo( url_address, 0, &hints, &result ) != 0 )
  return 0;

 // Get the IP address
 for ( const addrinfo* ptr = result; ptr != _null; ptr = ptr->ai_next )
 {
  switch ( ptr->ai_family ) 
  {
   case AF_INET:
   case AF_INET6:
   {
    return ( ( struct sockaddr_in * ) ptr->ai_addr )->sin_addr.s_addr;
   }
   break;

   default:
    break;
  }
 }

 return 0;
}

_DOMAIN_FAMILY_TYPE anyPlatformNetwork::GetFamilyType( _dword port, const _chara* url_address )
{
 if ( port == 0 || url_address == _null )
  return _DOMAIN_AF_INET;
  
 _DOMAIN_FAMILY_TYPE family_type = _DOMAIN_AF_INET;

 addrinfo *result = _null;
 addrinfo *res = _null;

 addrinfo addr_criteria;
 EGE_MEM_SET( &addr_criteria, 0, sizeof( addr_criteria ) );

 int error = getaddrinfo( url_address, AString( ).FromValue( port, 10 ).Str( ), &addr_criteria, &result );
 if ( error == 0 )
 {
  for ( res = result; res != NULL; res = res->ai_next )
  {
   if ( AF_INET6 == res->ai_addr->sa_family )
   {
    family_type = _DOMAIN_AF_INET6;
    break;
   }
   else if ( AF_INET == res->ai_addr->sa_family )
   {
    family_type = _DOMAIN_AF_INET;
   }
  }
 }

 return family_type;
}

_socket anyPlatformNetwork::CreateSocket( _DOMAIN_FAMILY_TYPE families, _SOCKET_TYPE type, _ubool block_mode )
{
 // Create socket
 _socket handle = ::socket( TranslateDomainFamilyType( families ), TranslateSocketType( type ), 0 );
 if ( handle == INVALID_SOCKET )
  return _null;

 // Check whether to enable block mode
 u_long nb = !block_mode;
 if ( ::ioctlsocket( handle, FIONBIO, &nb ) )
 {
  Platform::CloseSocket( handle );
  return _null;
 }

 return handle;
}

_socket anyPlatformNetwork::CreateListenedSocket( _DOMAIN_FAMILY_TYPE families, _SOCKET_TYPE type, _ubool block_mode, _dword port, _dword max_connection_number )
{
 // Create socket
 _socket handle = CreateSocket( families, type, block_mode );
 if ( handle == _null )
  return _null;

 // Initialize and bind address with port
 sockaddr_in my_addr  = {0};
 my_addr.sin_family  = AF_INET; /* host byte order */
 my_addr.sin_port  = htons( port ); /* short, network byte order */
 my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
 bind( handle, (const ::sockaddr *)&my_addr, sizeof( my_addr ) );

 // Set the max connections number of socket
 listen( handle, max_connection_number );

 return handle;
}

_void anyPlatformNetwork::CloseSocket( _socket handle )
{
 if ( handle == _null )
  return;

 ::closesocket( handle );
}

_dword anyPlatformNetwork::GetLastSocketErrorID( _socket handle )
{
 // Get the socket last error ID
 _dword err_id = anyPlatformNetwork::GetSocketOperationStatus< _dword >( handle, SOL_SOCKET, SO_ERROR );

 // Skip for block and progressing status
 if ( err_id == EWOULDBLOCK || err_id == EINPROGRESS )
  return 0;

 // Feedback the error ID
 return err_id;
}

_socket anyPlatformNetwork::AcceptSocket( _socket handle )
{
 sockaddr_in their_addr = {0};
 socklen_t sin_size = sizeof( their_addr );
 
 _socket connection_socket = accept( handle, (::sockaddr*)&their_addr, &sin_size );
 if ( connection_socket == _null || connection_socket == -1 )
  return _null;

 return connection_socket;
}

_ubool anyPlatformNetwork::ConnectSocket( _socket handle, const _chara* remote_address, _dword port, Platform::OnIsBreakConnectingProc func, _void* userdata )
{
 if ( handle == _null )
  return _false;

 // Enable none-block mode
 u_long nb = 1;
 if ( ::ioctlsocket( handle, FIONBIO, &nb ) )
  return _false;

 // Copy IP address
 _chara ip[128] = {0};
 SafeCopyString( ip, remote_address );

 // Copy port number as string
 _chara port_string[128] = {0};
 SafeCopyString( port_string, AString( ).FromValue( port, 10 ).Str( ) );

 // Get the address info
 addrinfo hints = {0}; AddrInfo* result = _null;
 if ( GetAddrInfoEx( ip, port_string, &hints, &result ) != 0 )
  return _false;

 // Set port number
 SetAddrInfoPort( result, port );

 // Connect
 _ubool err_occurred = _false;
 if ( ::connect( handle, result->ai_addr, result->ai_addrlen ) == -1 )
 {
  _dword err_id = errno;

  // Skip for connected, block and progressing status
  if ( err_id != 0 && err_id != EINPROGRESS && err_id != EWOULDBLOCK && err_id != EBADF )
  {
   OUTPUT_DEBUG_STRING( FORMAT_ASTRING_4( "Connect to '%s:%d' (%d) socket failed (%d)\n", 
    remote_address, port, (_dword) handle, err_id ) );

   err_occurred = _true;
  }
 }

 // Free address info
 FreeAddrInfo( result );

 // Check error
 if ( err_occurred )
  return _false;

 // Query the connection status
 _dword times = 0;
 while ( _true )
 {
  // Check whether to break it
  if ( func != _null && (*func)( times SEC, userdata ) )
  {
   OUTPUT_DEBUG_STRING( FORMAT_ASTRING_3( "Connect to '%s:%d' (%d) socket failed, due to timeout\n", 
    remote_address, port, (_dword) handle ) );

   return _false;
  }

  // Set the interval
  struct timeval tm;
  tm.tv_sec = 1;
  tm.tv_usec = 0;

  // Initialize the interval
  fd_set set, rset;
  FD_ZERO( &set );
  FD_ZERO( &rset );
  FD_SET( handle, &set );
  FD_SET( handle, &rset );

  // Wait for event
  int ret = select( handle + 1, &rset, &set, NULL, &tm );
  if (ret < 0)
  {
   OUTPUT_DEBUG_STRING( FORMAT_ASTRING_4( "Connect to '%s:%d' (%d) socket failed when wait for event (%d)\n", 
    remote_address, port, (_dword) handle, ret ) );

   return _false;
  }
  // Connect successful
  else if (ret == 1)
  {
   // Connect OK
   break;
  }

  times ++;
 }

 return _true;
}

_dword anyPlatformNetwork::ReadSocket( _socket handle, _void* buffer, _dword size )
{
 _dword ret = 0;

 while ( _true )
 {
  ret = ::recv( handle, (char*) buffer, size, MSG_NOSIGNAL );

  _NET_OP_TYPE op_type = GetOperationResult( handle, ret );
  switch ( op_type )
  {
   case _NET_OP_NO_DATA:
    return 0;

   case _NET_OP_CONTINUE:
    Platform::Sleep( 10 );
    break;

   case _NET_OP_ERROR:
    return -1;

   case _NET_OP_FINISHED:
    return ret;

   default:
    EGE_ASSERT( 0 );
    break;
  }
 }

 return ret;
}

_dword anyPlatformNetwork::WriteSocket( _socket handle, const _void* buffer, _dword size )
{
 _dword ret = 0;

 while ( _true )
 {
  ret = ::send( handle, (const char*) buffer, size, MSG_NOSIGNAL );

  _NET_OP_TYPE op_type = GetOperationResult( handle, ret );
  switch ( op_type )
  {
   case _NET_OP_NO_DATA:
    return 0;

   case _NET_OP_CONTINUE:
    Platform::Sleep( 10 );
    break;

   case _NET_OP_ERROR:
    return -1;

   case _NET_OP_FINISHED:
    return ret;

   default:
    EGE_ASSERT( 0 );
    break;
  }
 }

 return ret;
}
