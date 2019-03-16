//! @file     UID.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// UID Useful Macros
//----------------------------------------------------------------------------

// Microsecond per second ( 1s = 1000000us = 1000000000ns )
#define NSEC100_PER_SEC 10000000
#define USEC_PER_SEC    1000000
#define USEC_PER_MSEC   1000
#define NSEC_SINCE_1582 ( (_qword) ( 0x01B21DD213814000LL ) )

//----------------------------------------------------------------------------
// IsHex Implementation
//----------------------------------------------------------------------------

template< typename Type >
inline _ubool IsHex( Type c )
{
 if ( ( c >= 'A' && c <= 'F' ) || ( c >= 'a' && c <= 'f' ) )
  return _true;

 if ( c >= '0' && c <= '9' )
  return _true;

 return _false;
}

//----------------------------------------------------------------------------
// UID128 Implementation
//----------------------------------------------------------------------------

UID128::UID128( )
{
 mData1 = 0;
 mData2 = 0;
 mData3 = 0;
 EGE_INIT_ARRAY( mData4 );
}

UID128::UID128( const _chara* uidstring )
{
 *this = UID::String2UUID( uidstring );
}

UID128::UID128( const _charw* uidstring )
{
 *this = UID::String2UUID( uidstring );
}

_ubool UID128::operator == ( const UID128& uid ) const
{
 return UID::CompareUUID( *this, uid ) == 0;
}

_ubool UID128::operator != ( const UID128& uid ) const
{
 return UID::CompareUUID( *this, uid ) != 0;
}

_ubool UID128::operator > ( const UID128& uid ) const
{
 return UID::CompareUUID( *this, uid ) > 0;
}

_ubool UID128::operator >= ( const UID128& uid ) const
{
 return UID::CompareUUID( *this, uid ) >= 0;
}

_ubool UID128::operator < ( const UID128& uid ) const
{
 return UID::CompareUUID( *this, uid ) < 0;
}

_ubool UID128::operator <= ( const UID128& uid ) const
{
 return UID::CompareUUID( *this, uid ) <= 0;
}

AStringR UID128::ToStringA( _ubool to_upper ) const
{
 _chara uidstring[1024]; uidstring[0] = 0;
 UID::UUID2String( *this, uidstring, 1024 );

 if ( to_upper )
  Platform::UppercaseString( uidstring );

 return uidstring;
}

UStringR UID128::ToStringU( _ubool to_upper ) const
{
 _chara uidstring[1024]; uidstring[0] = 0;
 UID::UUID2String( *this, uidstring, 1024 );

 if ( to_upper )
  Platform::UppercaseString( uidstring );

 return uidstring;
}

WStringR UID128::ToStringW( _ubool to_upper ) const
{
 _charw uidstring[1024]; uidstring[0] = 0;
 UID::UUID2String( *this, uidstring, 1024 );

 if ( to_upper )
  Platform::UppercaseString( uidstring );

 return uidstring;
}

UID128& UID128::FromString( AStringPtr string )
{
 *this = UID::String2UUID( string.Str( ) );
 return *this;
}

UID128& UID128::FromString( UStringPtr string )
{
 *this = UID::String2UUID( string.Str( ) );
 return *this;
}

UID128& UID128::FromString( WStringPtr string )
{
 *this = UID::String2UUID( string.Str( ) );
 return *this;
}

UID128 UID128::Negation( ) const
{
 UID128 negation_uuid;
 negation_uuid.mData1 = ~mData1;
 negation_uuid.mData2 = ~mData2;
 negation_uuid.mData3 = ~mData3;
 for ( _dword i = 0; i < 8; i ++ )
  negation_uuid.mData4[i] = ~mData4[i];

 return negation_uuid;
}

//----------------------------------------------------------------------------
// UID Implementation
//----------------------------------------------------------------------------

const _dword UID::cStandardUID128StringLength = 36;
const UID128 UID::cNullUID128;

_ubool UID::IsUUIDString( const _chara* uidstring )
{
 if ( uidstring == _null )
  return _false;

 static const _chara fmt[] = "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx";

 for ( _dword i = 0; i < sizeof( fmt ); i ++ )
 {
  // Number
  if ( fmt[i] == 'x' )
  {
   if ( IsHex( uidstring[i] ) == _false )
    return _false;
  }
  // '-' character
  else if ( uidstring[i] != fmt[i] )
  {
   return _false;
  }
 }

 return _true;
}

_ubool UID::IsUUIDString( const _charw* uidstring )
{
 if ( uidstring == _null )
  return _false;

 static const _charw fmt[] = L"xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx";

 for ( _dword i = 0; i < sizeof( fmt ) / sizeof( _charw ); i ++ )
 {
  // Number
  if ( fmt[i] == 'x' )
  {
   if ( IsHex( uidstring[i] ) == _false )
    return _false;
  }
  // '-' character
  else if ( uidstring[i] != fmt[i] )
  {
   return _false;
  }
 }

 return _true;
}

UID128 UID::CreateUUID( )
{
 static _ubool initialized = _false;
 static _qword   timestamp = 0;
 static _dword advance  = 0;
 static _word clockseq = 0;
 static _word node_high = 0;
 static _dword node_low = 0;

 // Get the current system time for random seed
 CalendarTime systemtime;
 Platform::GetSystemTime( systemtime );

 // Convert system to file time
 FileTime filetime;
 Platform::SystemTimeToFileTime( filetime, systemtime );

 // Time is counter of 100ns time interval since Oct.15, 1582
 _qword time = ( ( *(_qword*) &filetime ) * USEC_PER_SEC + ( (_qword) systemtime.mMilliseconds * USEC_PER_MSEC ) );
 time = time * 10 + NSEC_SINCE_1582;

 // Initialize UID generator
 if ( initialized == _false ) 
 {
  // Update the time stamp
  timestamp = time;

  _dword value = Random::GenByUTC( );

  clockseq = value >> 16;
  node_high = (_word) ( value | 0x0100 );
  node_low = Random::GenByUTC( );

  initialized = _true;
 } 
 else if ( time < timestamp )
 {
  timestamp = time;
  advance  = 0;

  clockseq ++;
 } 
 else if ( time == timestamp ) 
 {
  advance ++; 
  
  time += advance;
 }
 else
 {
  timestamp = time;
  advance  = 0;
 } 

 // Build the UID
 UID128 uid;
 uid.mData1       = (_dword) time;
 uid.mData2       = (_word) ( ( time >> 32 ) & 0xFFFF );
 uid.mData3       = (_word) ( ( ( time >> 48 ) & 0x0FFFF ) | 0x1000 );
 ( *(_word*) &uid.mData4[6] )  = (_word) ( ( clockseq & 0x3FFF ) | 0x8000 );    
 ( *(_word*) &uid.mData4[4] )  = (_word) node_high;
 ( *(_dword*) &uid.mData4[0] ) = node_low;

 return uid;
}

_chara* UID::CreateUUIDString( _chara* uidstring, _dword length )
{
 if ( uidstring == _null )
  return _null;

 // Convert UID to string
 return UUID2String( CreateUUID( ), uidstring, length );
}

_charw* UID::CreateUUIDString( _charw* uidstring, _dword length )
{
 if ( uidstring == _null )
  return _null;

 // Convert UID to string
 return UUID2String( CreateUUID( ), uidstring, length );
}

UID128 UID::String2UUID( const _chara* uidstring )
{
 // Convert to UNICODE string
 _charw uidstring_unicode[1024];
 Platform::AnsiToUtf16( uidstring_unicode, 1024, uidstring );

 return String2UUID( uidstring_unicode );
}

UID128 UID::String2UUID( const _charw* uidstring )
{
 // Check the UID string format
 if ( IsUUIDString( uidstring ) == _false )
  return cNullUID128;

 // The sub-string table of "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx" UID string format
 WString substring[6];
 substring[0] = WString( uidstring, 8 ); uidstring += 9; // contains '-' character
 substring[1] = WString( uidstring, 4 ); uidstring += 5; // contains '-' character
 substring[2] = WString( uidstring, 4 ); uidstring += 5; // contains '-' character
 substring[3] = WString( uidstring, 4 ); uidstring += 5; // contains '-' character
 substring[4] = WString( uidstring, 4 ); uidstring += 4;
 substring[5] = WString( uidstring, 8 );

 // Build the UID by string
 UID128 uid;
 uid.mData1      = substring[0].ToDword( 16 );
 uid.mData2      = (_word) substring[1].ToDword( 16 );
 uid.mData3      = (_word) substring[2].ToDword( 16 );
 *(_word*) &uid.mData4[6] = (_word) substring[3].ToDword( 16 );
 *(_word*) &uid.mData4[4] = (_word) substring[4].ToDword( 16 );
 *(_dword*) &uid.mData4[0] = substring[5].ToDword( 16 );

 return uid;
}

_chara* UID::UUID2String( const UID128& uid, _chara* uidstring, _dword length )
{
 _word  a = *(_word*) &uid.mData4[6];
 _word  b = *(_word*) &uid.mData4[4];
 _dword c = *(_dword*) &uid.mData4[0];

 // Build the UID string
 Platform::FormatStringBuffer( uidstring, length, "%08lx-%04x-%04x-%04x-%04x%08lx", 
  uid.mData1, uid.mData2, uid.mData3, a, b, c );

 return uidstring;
}

_charw* UID::UUID2String( const UID128& uid, _charw* uidstring, _dword length )
{
 _word  a = *(_word*) &uid.mData4[6];
 _word  b = *(_word*) &uid.mData4[4];
 _dword c = *(_dword*) &uid.mData4[0];

 // Build the UID string
 Platform::FormatStringBuffer( uidstring, length, L"%08lx-%04x-%04x-%04x-%04x%08lx", 
  uid.mData1, uid.mData2, uid.mData3, a, b, c );

 return uidstring;
}

_int UID::CompareUUID( const UID128& uuid1, const UID128& uuid2 )
{
 EGE_CHECK_COMP( uuid1.mData1, uuid2.mData1);
 EGE_CHECK_COMP( uuid1.mData2, uuid2.mData2);
 EGE_CHECK_COMP( uuid1.mData3, uuid2.mData3);

 for ( _dword i = 0; i < 8; i ++ )
  EGE_CHECK_COMP( uuid1.mData4[i], uuid2.mData4[i] );

 return 0;
}