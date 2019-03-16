//! @file     RenderFontTextureSet.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// RenderFontTextureSet Implementation
//----------------------------------------------------------------------------

RenderFontTextureSet::RenderFontTextureSet( )
{
	// Create image filler ( use simple filler just ok for font texture )
	mImageFiller = GetInterfaceFactory( )->CreateImageFiller( _IMAGE_FILLER_LINEAR, PointU( _TEXTURE_SIZE, _TEXTURE_SIZE ), PointU( 1, 1 ) );
	EGE_ASSERT( mImageFiller.IsValid( ) );
}

RenderFontTextureSet::~RenderFontTextureSet( )
{
}

_void RenderFontTextureSet::FixBitmapSize( FontFaceCodeInfo& code_info ) const
{
	// If no any bitmap info of character then we do not update texture pixel at all
	if ( code_info.mBitmapBuffer == _null )
	{
		code_info.mBitmapWidth	= code_info.mAdvanceX;
		code_info.mBitmapHeight	= code_info.mMaxCharHeight;
		code_info.mBitmapBuffer = _null;
	}
}

_ubool RenderFontTextureSet::CreateImageFontCode( IFontFace* font_face, _dword code, FontCodeRHI& font_code )
{
	EGE_ASSERT( font_face != _null );
	EGE_ASSERT( font_face->IsImageType( ) );

	// Check whether support code
	if ( font_face->HasCharacter( code ) == _false )
		return _false;

	// Get codes number
	_dword codes_number = font_face->GetImageCodesNumber( );
	if ( codes_number == 0 )
		return _false;

	// Get image pixel buffer and codes
	PointU size = PointU::cZeroPoint;
	const _dword* pixel_buffer = font_face->GetImagePixelBuffer( size );
	if ( pixel_buffer == _null )
		return _false;

	// Create font texture
	IGraphicTexture2DRef texture = gGraphicResourceManager->CreateTexture2D( L"", size.x, size.y, _PF_A8R8G8B8, 1, (const _byte*)pixel_buffer, _true );
	if ( texture.IsNull( ) )
		return _false;

	// Append it into texture array
	mTextures.Append( texture );

	// Build font codes information
	for ( _dword i = 0; i < codes_number; i ++ )
	{
		FontFaceCodeInfo code_info;
		if ( font_face->GetImageCodeInfoByIndex( i, code_info ) == _false )
			return _false;

		// Update font code info
		FontCodeRHI& font_code	= GetFontCode( code_info.mCode );
		font_code.mTexture		= texture->GetResource( );
		font_code.mCharHeight	= code_info.mCharHeight;
		font_code.mStartX		= code_info.mBitmapLeft;
		font_code.mStartY		= code_info.mBitmapTop;
		font_code.mOffsetX		= code_info.mOffsetX;
		font_code.mOffsetY		= code_info.mAscender - code_info.mOffsetY;
		font_code.mAdvanceX		= code_info.mAdvanceX;
		font_code.mDescender	= code_info.mDescender;
		font_code.mBaseLine		= code_info.mBaseLine;
		font_code.mBitmapTop	= 0;
		font_code.mBitmapWidth	= code_info.mBitmapWidth;
		font_code.mBitmapHeight	= code_info.mBitmapHeight;
	}

	return _true;
}

_ubool RenderFontTextureSet::CreateFontCode( IFontFace* font_face, _dword code, FontCodeRHI& font_code )
{
	LockOwner lock_owner( mLocker );

	// If it's font image type then load the image as texture now
	if ( font_face->IsImageType( ) )
	{
		return CreateImageFontCode( font_face, code, font_code );
	}
	// It's none font image type
	else
	{
		// Render character code
		FontFaceCodeInfo code_info;
		if ( RenderCharacter( font_face, code, code_info ) == _false )
			return _false;

		// Update outline character code
		if ( UpdateCharacter( code_info, font_code ) == _false )
			return _false;
	}

	return _true;
}

_ubool RenderFontTextureSet::CreateFontCodeByStrokeInfo( IFontFace* font_face, _dword code, _dword stroke_size, FontCodeRHI& font_code )
{
	LockOwner lock_owner( mLocker );

	// If it's font image type then load the image as texture now
	if ( font_face->IsImageType( ) )
	{
		return CreateImageFontCode( font_face, code, font_code );
	}
	// It's none font image type
	else
	{
		// Render character code
		FontFaceCodeInfo code_info;
		if ( RenderCharacterByStrokeInfo( font_face, code, stroke_size, code_info ) == _false )
			return _false;

		// Update outline character code
		if ( UpdateCharacter( code_info, font_code ) == _false )
			return _false;
	}

	return _true;
}

_ubool RenderFontTextureSet::CreateFontCodeByBlurInfo( IFontFace* font_face, _dword code, _dword blur_size, _dword blur_factor, FontCodeRHI& font_code )
{
	LockOwner lock_owner( mLocker );

	// If it's font image type then load the image as texture now
	if ( font_face->IsImageType( ) )
	{
		return CreateImageFontCode( font_face, code, font_code );
	}
	// It's none font image type
	else
	{
		// Render character code
		FontFaceCodeInfo code_info;
		if ( RenderCharacterByBlurInfo( font_face, code, blur_size, blur_factor, code_info ) == _false )
			return _false;

		// Update outline character code
		if ( UpdateCharacter( code_info, font_code ) == _false )
			return _false;
	}

	return _true;
}

_ubool RenderFontTextureSet::RenderCharacter( IFontFace* font_face, _dword code, FontFaceCodeInfo& code_info )
{
	EGE_ASSERT( font_face != _null );

	// Render character with stroke
	if ( font_face->RenderCharacter( code, code_info ) == _false )
		return _false;

	// Fix the bitmap's size
	FixBitmapSize( code_info );

	return _true;
}

_ubool RenderFontTextureSet::RenderCharacterByStrokeInfo( IFontFace* font_face, _dword code, _dword stroke_size, FontFaceCodeInfo& code_info )
{
	EGE_ASSERT( font_face != _null );

	// Render character with stroke
	if ( font_face->RenderCharacterByStrokeInfo( code, stroke_size, code_info ) == _false )
		return _false;

	// Fix the bitmap's size
	FixBitmapSize( code_info );

	return _true;
}

_ubool RenderFontTextureSet::RenderCharacterByBlurInfo( IFontFace* font_face, _dword code, _dword blur_size, _dword blur_factor, FontFaceCodeInfo& code_info )
{
	EGE_ASSERT( font_face != _null );

	// Get the blur factor in float mode
	_float factor = EGE_RATIO( blur_factor, 100.0f );

	// Render character with stroke
	if ( font_face->RenderCharacterByBlurInfo( code, blur_size, factor, code_info ) == _false )
		return _false;

	// Fix the bitmap's size
	FixBitmapSize( code_info );

	return _true;
}

_ubool RenderFontTextureSet::UpdateCharacter( const FontFaceCodeInfo& code_info, FontCodeRHI& font_code )
{
	// If font texture array is empty then need to create font textures
	_ubool createnewtex = mTextures.Number( ) == 0 ? _true : _false;

	// Get the char size in pixel
	PointU font_code_size( code_info.mBitmapWidth, code_info.mBitmapHeight );

	// Calculate the font code image region
	RectU font_code_rect;
	if ( mImageFiller->AddImage( font_code_size, font_code_rect ) == _false )
	{
		// The current image/texture is full, so we need to create a new one
		createnewtex = _true;

		// Recalculate the font code image region after clear
		mImageFiller->ClearAllImages( );
		if ( mImageFiller->AddImage( font_code_size, font_code_rect ) == _false )
			return _false; // Still failed to fill font code image, maybe it's really so big
	}

	// Create a new font texture if we need
	if ( createnewtex )
	{
		//!	The black pixel buffer for un-render character or initial pixel buffer usage
		const _byte cBlackPixelBuffer[_TEXTURE_SIZE * _TEXTURE_SIZE] = {0};

		// Create font texture
		IGraphicTexture2DRef texture = gGraphicResourceManager->CreateTexture2D( L"", _TEXTURE_SIZE, _TEXTURE_SIZE, _PF_A8, 1, cBlackPixelBuffer, _true );
		if ( texture.IsNull( ) )
			return _false;

		// Append it into texture array
		mTextures.Append( texture );
	}

	// Set font code information
	font_code.mTexture		= mTextures.GetTailElement( )->GetResource( );
	font_code.mStartX		= (_short)font_code_rect.l;
	font_code.mStartY		= (_short)font_code_rect.t;
	font_code.mCharHeight	= code_info.mCharHeight;
	font_code.mOffsetX		= code_info.mOffsetX;
	font_code.mOffsetY		= code_info.mAscender - code_info.mOffsetY;
	font_code.mAdvanceX		= code_info.mAdvanceX;
	font_code.mDescender	= code_info.mDescender;
	font_code.mBaseLine		= code_info.mBaseLine;
	font_code.mBitmapTop	= code_info.mBitmapTop;
	font_code.mBitmapWidth	= code_info.mBitmapWidth;
	font_code.mBitmapHeight	= code_info.mBitmapHeight;

	// Update font texture if we have pixel buffer
	if ( code_info.mBitmapBuffer != _null )
	{
		if ( gDynamicRHI->UpdateTexture2D( font_code.mTexture, font_code_rect, code_info.mBitmapBuffer ) == _false )
			return _false;
	}

	return _true;
}

const FontCodeRHI* RenderFontTextureSet::CreateCode( IFontFace* font_face, _dword code )
{
	if ( font_face == _null )
		return _null;

	// Get the font code
	FontCodeRHI& font_code = GetFontCode( code );
	if ( font_code.mTexture != _null )
		return &font_code;

	// If the texture pool is full then need to clear it
	if ( mTextures.Number( ) == _MAX_PAGE_NUMBER )
		ClearCaches( );

	// Create font code
	if ( CreateFontCode( font_face, code, font_code ) == _false )
		return _null;

	return &font_code;
}

const FontCodeRHI* RenderFontTextureSet::CreateCodeByStrokeInfo( IFontFace* font_face, _dword code, _dword stroke_size )
{
	if ( font_face == _null )
		return _null;

	// Check the max stroke size
	if ( stroke_size >= _MAX_STROKE_SIZE )
		return _null;

	// Get the font code
	FontCodeRHI& stroke_font_code = GetFontCodeByStrokeInfo( code, stroke_size );
	if ( stroke_font_code.mTexture != _null )
		return &stroke_font_code;

	// If the texture pool is full then need to clear it
	if ( mTextures.Number( ) == _MAX_PAGE_NUMBER )
		ClearCaches( );

	// Create font code
	if ( CreateFontCodeByStrokeInfo( font_face, code, stroke_size, stroke_font_code ) == _false )
		return _null;

	return &stroke_font_code;
}

const FontCodeRHI* RenderFontTextureSet::CreateCodeByBlurInfo( IFontFace* font_face, _dword code, _dword blur_size, _dword blur_factor )
{
	if ( font_face == _null )
		return _null;

	// Check the max blur size
	if ( blur_size >= _MAX_BLUR_SIZE )
		return _null;

	// Check the max blur factor
	if ( blur_factor >= _MAX_BLUR_FACTOR )
		return _null;

	// Get the font code
	FontCodeRHI& blur_font_code = GetFontCodeByBlurInfo( code, blur_size, blur_factor );
	if ( blur_font_code.mTexture != _null )
		return &blur_font_code;

	// If the texture pool is full then need to clear it
	if ( mTextures.Number( ) == _MAX_PAGE_NUMBER )
		ClearCaches( );

	// Create font code
	if ( CreateFontCodeByBlurInfo( font_face, code, blur_size, blur_factor, blur_font_code ) == _false )
		return _null;

	return &blur_font_code;
}

_void RenderFontTextureSet::ClearCaches( )
{
	LockOwner lock_owner( mLocker );

	mImageFiller->ClearAllImages( );

	mTextures.Clear( _true );
	mCodePages.Clear( );
}