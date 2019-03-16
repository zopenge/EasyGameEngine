//! @file     Library.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEPlatform.h"

//----------------------------------------------------------------------------
// Library Implementation
//----------------------------------------------------------------------------

Library::Library( )
{
	mLibInMemory	= _false;
	mModule			= _null;
	mNTHeader		= _null;
	mDllMainFunc	= _null;
}

Library::~Library( )
{
	Free( );
}

_ubool Library::Load( WStringPtr filename )
{
	// Free the previous DLL module
	Free( );

	// It's loaded from the file
	mLibInMemory = _false;

	// Load DLL module
	mModule	= Platform::LoadLibrary( filename.Str( ) );
	if ( mModule == _null )
		return _false;

	return _true;
}

_void* Library::GetFunction( WStringPtr functionname ) const
{
	_chara funcname_ansi[1024];
	Platform::Utf16ToAnsi( funcname_ansi, 1024, functionname.Str( ) );

	return GetFunction( funcname_ansi );
}

_ubool Library::IsLoaded( ) const
{
	return mModule != _null;
}

WStringPtr Library::GetInternalName( ) const
{
	return mInternalName.Str( );
}

WStringPtr Library::GetCopyright( ) const
{
	return mCopyright.Str( );
}

const Version& Library::GetVersion( ) const
{
	return mVersion;
}

AStringPtr Library::GetEmbeddedManifest( ) const
{
	return mEmbeddedManifest.Str( );
}