//! @file     KernelObject.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// KernelObject Implementation
//----------------------------------------------------------------------------

KernelObject::KernelObject( _handle objecthandle ) : mObjectHandle( objecthandle )
{
}

KernelObject::~KernelObject( )
{
 Close( );
}

_ubool KernelObject::IsValid( ) const
{
 return mObjectHandle != _null;
}

_void KernelObject::Close( )
{
 Platform::CloseHandle( mObjectHandle );
 mObjectHandle = _null;
}