//! @file     FontFaceFreeType2Lib.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// The Memory Allocations Implementation
//----------------------------------------------------------------------------

static void* FTAlloc( FT_Memory memory, long size )
{
	return Memory::GetInstance( ).Alloc( size, _FILENAME_A, _LINENUMBER );
}

static void FTFree( FT_Memory memory, void* block )
{
	Memory::GetInstance( ).Free( block, _FILENAME_A, _LINENUMBER );
}

static void* FTRealloc( FT_Memory memory, long cur_size, long new_size, void* block )
{
	return Memory::GetInstance( ).Realloc( block, new_size, _FILENAME_A, _LINENUMBER );
}

//----------------------------------------------------------------------------
// FontFaceFreeType2Lib Implementation
//----------------------------------------------------------------------------

FontFaceFreeType2Lib::FontFaceFreeType2Lib( )
{
	mFTLibrary	= _null;
	mFTMemory	= _null;

	mLocker		= _null;
}

FontFaceFreeType2Lib::~FontFaceFreeType2Lib( )
{
}

_ubool FontFaceFreeType2Lib::Initialize( )
{
	// Skip compile error for redefined memory operation macros
#ifndef _USE_STANDARD_MALLOC_OPERATOR_
	#undef malloc
	#undef alloc
	#undef free
	#undef realloc
#endif

	// Initialize freetype2 memory allocations
	mFTMemory			= (FT_Memory) malloc( sizeof( *mFTMemory ) );
	mFTMemory->alloc	= FTAlloc;
	mFTMemory->free		= FTFree;
	mFTMemory->realloc	= FTRealloc;
	mFTMemory->user		= _null;

	// Create freetype library
	if ( ::FT_New_Library( mFTMemory, &mFTLibrary ) != FT_Err_Ok )
		return _false;

	// Add default modules
	::FT_Add_Default_Modules( mFTLibrary );

	// Initialize UV table info
	for ( _dword i = 0; i < _TEXTURE_SIZE; i ++ )
		mUVTable[i] = EGE_RATIO( i, _TEXTURE_SIZE );

	// Create lock
	mLocker = new Lock( );

	// Show the freetype SDK version
	OUTPUT_DEBUG_STRING( FORMAT_WSTRING_3( L"Initialize freetype (%d.%d.%d) library OK\n", FREETYPE_MAJOR, FREETYPE_MINOR, FREETYPE_PATCH ) );

	return _true;
}

_void FontFaceFreeType2Lib::Finalize( )
{
	// Release freetype library
	if ( mFTLibrary != _null )
	{
		::FT_Done_FreeType( mFTLibrary );
		mFTLibrary = _null;
	}

	// The freetype memory will be deleted in FT_Done_FreeType( ) function
	mFTMemory = _null;

	// Clear lock
	EGE_DELETE( mLocker );
}