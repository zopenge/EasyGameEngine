//! @file     RenderFontTextureSet.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FontTexture
//----------------------------------------------------------------------------

class RenderFontTextureSet
{
private:
	enum 
	{ 
		//!	The max stroke size
		_MAX_STROKE_SIZE	= 0xFF,
		//!	The max blur size
		_MAX_BLUR_SIZE		= 0xFF,
		//!	The max blur factor
		_MAX_BLUR_FACTOR	= 0xFFFF,

		//!	The font texture size
		_TEXTURE_SIZE  		= 512,
		//!	The font code number in one page
		_MAX_PAGE_SIZE		= 64,
		//!	The font page number
		_MAX_PAGE_NUMBER	= 1024,
	};

private:
	//!	The textures array
	typedef Array< IGraphicTexture2DRef > Texture2DArray;
	//! The font code page pool
	typedef PagePool< FontCodeRHI, _MAX_PAGE_SIZE > CodePagePool;
	//!	The code page pool in map, use (stroke and blur) as key.
	typedef Map< CodePagePool, _dword > CodePagePoolMap;

private:
	//!	The thread locker
	Lock			mLocker;

	//! The image filler
	IImageFillerRef	mImageFiller;

	//! Character page pool
	CodePagePoolMap	mCodePages;

	//! Textures
	Texture2DArray	mTextures;

private:
	//!	Build the key.
	_dword BuildKey( _dword stroke_size, _dword blur_size, _dword blur_factor ) const;

	//!	Fix the bitmap's size.
	_void FixBitmapSize( FontFaceCodeInfo& code_info ) const;

	//!	Create image font code.
	_ubool CreateImageFontCode( IFontFace* font_face, _dword code, FontCodeRHI& font_code );
	//!	Create font code.
	_ubool CreateFontCode( IFontFace* font_face, _dword code, FontCodeRHI& font_code );
	//!	Create font code by stroke info.
	_ubool CreateFontCodeByStrokeInfo( IFontFace* font_face, _dword code, _dword stroke_size, FontCodeRHI& font_code );
	//!	Create font code by blur info.
	_ubool CreateFontCodeByBlurInfo( IFontFace* font_face, _dword code, _dword blur_size, _dword blur_factor, FontCodeRHI& font_code );

	//!	Render character.
	_ubool RenderCharacter( IFontFace* font_face, _dword code, FontFaceCodeInfo& code_info );
	//!	Render character by stroke info.
	_ubool RenderCharacterByStrokeInfo( IFontFace* font_face, _dword code, _dword stroke_size, FontFaceCodeInfo& code_info );
	//!	Render character by blur info.
	_ubool RenderCharacterByBlurInfo( IFontFace* font_face, _dword code, _dword blur_size, _dword blur_factor, FontFaceCodeInfo& code_info );

	//!	Update character.
	_ubool UpdateCharacter( const FontFaceCodeInfo& code_info, FontCodeRHI& font_code );

public:
	RenderFontTextureSet( );
	~RenderFontTextureSet( );

public:
	//!	Get the texture number.
	_dword GetTextureNumber( ) const;
	//!	Get the texture by index.
	Texture2DRHI* GetTextureByIndex( _dword index ) const;

	//!	Get font code.
	FontCodeRHI& GetFontCode( _dword code );
	//!	Get font code with stroke info.
	FontCodeRHI& GetFontCodeByStrokeInfo( _dword code, _dword stroke_size );
	//!	Get font code with blur info.
	FontCodeRHI& GetFontCodeByBlurInfo( _dword code, _dword blur_size, _dword blur_factor );

public:
	//!	Create code.
	const FontCodeRHI* CreateCode( IFontFace* font_face, _dword code );
	//!	Create code with stroke info.
	const FontCodeRHI* CreateCodeByStrokeInfo( IFontFace* font_face, _dword code, _dword stroke_size );
	//!	Create code with blur info.
	const FontCodeRHI* CreateCodeByBlurInfo( IFontFace* font_face, _dword code, _dword blur_size, _dword blur_factor );

	//!	Clear caches.
	_void ClearCaches( );
};

//----------------------------------------------------------------------------
// FontTexture Implementation
//----------------------------------------------------------------------------

inline _dword RenderFontTextureSet::BuildKey( _dword stroke_size, _dword blur_size, _dword blur_factor ) const
{
	EGE_ASSERT( stroke_size <= _MAX_STROKE_SIZE );
	EGE_ASSERT( blur_size <= _MAX_BLUR_SIZE );
	EGE_ASSERT( blur_factor <= _MAX_BLUR_FACTOR );

	return (stroke_size << 24) | (blur_size << 16) | (blur_factor & 0xFFFF);
}

inline _dword RenderFontTextureSet::GetTextureNumber( ) const
{
	return mTextures.Number( );
}

inline Texture2DRHI* RenderFontTextureSet::GetTextureByIndex( _dword index ) const
{
	return mTextures[ index ]->GetResource( );
}

inline FontCodeRHI& RenderFontTextureSet::GetFontCode( _dword code )
{
	CodePagePool& page_pool = mCodePages[BuildKey( 0, 0, 0 )];
	if ( page_pool.GetPageNumber( ) == 0 )
		page_pool.Create( _MAX_PAGE_NUMBER );

	return page_pool[code];
}

inline FontCodeRHI& RenderFontTextureSet::GetFontCodeByStrokeInfo( _dword code, _dword stroke_size )
{
	CodePagePool& page_pool = mCodePages[BuildKey( stroke_size, 0, 0 )];
	if ( page_pool.GetPageNumber( ) == 0 )
		page_pool.Create( _MAX_PAGE_NUMBER );

	return page_pool[code];
}

inline FontCodeRHI& RenderFontTextureSet::GetFontCodeByBlurInfo( _dword code, _dword blur_size, _dword blur_factor )
{
	CodePagePool& page_pool = mCodePages[BuildKey( 0, blur_size, blur_factor )];
	if ( page_pool.GetPageNumber( ) == 0 )
		page_pool.Create( _MAX_PAGE_NUMBER );

	return page_pool[code];
}

}