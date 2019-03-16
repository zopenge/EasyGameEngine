//! @file     FontFaceFreeType2Lib.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FontFaceFreeType2Lib
//----------------------------------------------------------------------------

class FontFaceFreeType2Lib
{
	SINGLETON( FontFaceFreeType2Lib )

public:
	enum 
	{ 
		//!	The font texture size
		_TEXTURE_SIZE = 512,
	};

private:
	//!	The FreeType2 library
	FT_Library	mFTLibrary;
	FT_Memory	mFTMemory;

	//!	The thread lock
	Lock*		mLocker;

	//!	The UV table info
	_float		mUVTable[ _TEXTURE_SIZE ];

public:
	EGE_GET_ACCESSOR( FT_Library, FTLibrary )

	//!	Get the lock.
	inline Lock& GetLocker( );

	//!	Get the UV.
	inline Vector2 GetUV( _dword x, _dword y ) const;

public:
	//!	Initialize.
	_ubool Initialize( );
	//!	Finalize.
	_void Finalize( );
};

//----------------------------------------------------------------------------
// FontFaceFreeType2Lib Implementation
//----------------------------------------------------------------------------

Lock& FontFaceFreeType2Lib::GetLocker( )
{
	return *mLocker;
}

Vector2 FontFaceFreeType2Lib::GetUV( _dword x, _dword y ) const
{
	return Vector2( mUVTable[x], mUVTable[y] );
}

}