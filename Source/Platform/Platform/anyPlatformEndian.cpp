//! @file     anyPlatformEndian.cpp
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// anyPlatformEndian Implementation
//----------------------------------------------------------------------------

_ubool anyPlatformEndian::IsLittleEndian( )
{
 static _dword value = 1;
 static _ubool ret = ( (_byte*) &value )[0] == 1;

 return ret;
}

_ubool anyPlatformEndian::IsBigEndian( )
{
 static _dword value = 1;
 static _ubool ret = ( (_byte*) &value )[3] == 1;

 return ret;
}

_ENDIAN anyPlatformEndian::GetEndianType( )
{
 if ( IsLittleEndian( ) )
  return _ENDIAN_LITTLE;
 else
  return _ENDIAN_BIG;
}