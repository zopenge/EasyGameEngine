//! @file     FontFaceFreeType2.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// FontFaceFreeType2 Implementation
//----------------------------------------------------------------------------

FontFaceFreeType2::FontFaceFreeType2( )
{
	mFTFace		= _null;
	mFontSize	= 0;
}

FontFaceFreeType2::~FontFaceFreeType2( )
{
	// Release freetype font face
	if ( mFTFace != _null )
		::FT_Done_Face( mFTFace );
}

_ubool FontFaceFreeType2::IsControlCharCode( _dword id ) const
{
	if ( id == '\r' || id == '\n' )
		return _true;

	return _false;
}

_ubool FontFaceFreeType2::GetCodeInfo( _dword code, _dword flags, FontFaceCodeInfoBase& char_info )
{
	// Get character index
	_dword char_index = ::FT_Get_Char_Index( mFTFace, code );
	if ( char_index == 0 )
		return _false;

	// Load character glyph slot
	::FT_Load_Glyph( mFTFace, (FT_UInt)char_index, (FT_Int32)flags );

	// Get the glyph slot
	const FT_GlyphSlot glyphslot = mFTFace->glyph;

	// Get the char info
	char_info.mCode				= (_charw) code;
	// Get the char width and height
	char_info.mCharWidth		= (_short) glyphslot->metrics.width / 64;
	char_info.mCharHeight		= (_short) glyphslot->metrics.height / 64;
	char_info.mMaxCharWidth		= (_short) mFTFace->size->metrics.max_advance / 64;
	char_info.mMaxCharHeight	= (_short) mFTFace->size->metrics.height / 64;
	// Get the baseline position
	char_info.mAscender			= (_short) mFTFace->size->metrics.ascender / 64;
	char_info.mDescender		= (_short) mFTFace->size->metrics.descender / 64;
	char_info.mBaseLine			= char_info.mAscender;
	// Get the advance
	char_info.mAdvanceX			= (_short) glyphslot->metrics.horiAdvance / 64;
	// Get the bearing
	char_info.mBearingY			= (_short) glyphslot->metrics.horiBearingY / 64;

	// Fix the character size
	if ( char_info.mCharWidth == 0 )
		char_info.mCharWidth = char_info.mAdvanceX;
	if ( char_info.mCharHeight == 0 )
		char_info.mCharHeight = char_info.mMaxCharHeight;

	return _true;
}

const FontFaceCodeInfoBase* FontFaceFreeType2::CacheCodeInfoIfNotExisting( _dword code, _dword flags )
{
	LockOwner lock_owner( FontFaceFreeType2Lib::GetInstance( ).GetLocker( ) );

	// Get the character info from pool
	FontFaceCodeInfoBase& char_info = mCharInfoPagePool[ code ];

	// If the character info is empty then we need to query it to get the size
	if ( char_info.mCharWidth == 0 && char_info.mCharHeight == 0 )
	{
		if ( GetCodeInfo( code, flags, char_info ) == _false )
			return _null;
	}

	return &char_info;
}

_void FontFaceFreeType2::RenderSpans( FT_Outline* const outline, SpanInfoArray& spans )
{
	FT_Raster_Params params = {0};
	params.flags			= FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
	params.gray_spans		= OnRenderSpinsCallback;
	params.user				= &spans;

	::FT_Outline_Render( FontFaceFreeType2Lib::GetInstance( ).GetFTLibrary( ), outline, &params );
}

_void FontFaceFreeType2::RenderCharacterWithSpans( _dword stroke_size, _byte* pixel_buffer, const SpanInfoArray& spans, FontFaceCodeInfo& info )
{
	// Figure out what the bounding rect is for both the span lists.
	RectI rect( spans[0].mPos.x, spans[0].mPos.y, spans[0].mPos.x, spans[0].mPos.y );
	for ( _dword i = 0; i < spans.Number( ); i ++ )
	{
		const SpanInfo& span = spans[i];

		rect.l = Math::Min< _int >( rect.l, span.mPos.x );
		rect.t = Math::Min< _int >( rect.t, span.mPos.y );
		rect.r = Math::Max< _int >( rect.r, span.mPos.x + span.mWidth );
		rect.b = Math::Max< _int >( rect.b, span.mPos.y );
	}

	// Set the offset Y
	info.mOffsetX = rect.l;
	info.mOffsetY = info.mBitmapTop + (_int) stroke_size;

	// Get the image size
	_int image_width	= rect.GetWidth( );
	_int image_height	= rect.GetHeight( );

	// The start position
	_int start_x = Math::cMaxInt;
	_int start_y = Math::cMaxInt;

	// Get bitmap width, height, stride and buffer
	info.mBitmapTop		= info.mBearingY;
	info.mBitmapWidth	= (_short) image_width;
	info.mBitmapHeight	= (_short) image_height + 1;
	info.mBitmapBuffer	= pixel_buffer;

	// Initialize pixel buffers
	EGE_MEM_SET( pixel_buffer, 0, info.mBitmapWidth * info.mBitmapHeight );

	// Fill the pixel buffer
	for ( _dword i = 0; i < spans.Number( ); i ++ )
	{
		const SpanInfo& span = spans[i];

		_int y = span.mPos.y - rect.t;
		start_y = Math::Min< _int >( start_y, y );

		_int fixed_y = image_height - y;
		EGE_ASSERT( fixed_y >= 0 );

		for ( _int w = 0; w < span.mWidth; w ++ )
		{
			_int x = span.mPos.x - rect.l + w;

			start_x = Math::Min< _int >( start_x, x );

			pixel_buffer[ fixed_y * image_width + x ] = span.mCoverage;
		}
	}

	// Get bitmap left position
	info.mBitmapLeft = (_short) start_x;
}

_void FontFaceFreeType2::OnRenderSpinsCallback( const _int y, const _int count, const FT_Span* const spans, void* const user )
{
	SpanInfoArray* span_info_array = (SpanInfoArray*) user;
	EGE_ASSERT( span_info_array != _null );

	for ( _int i = 0; i < count; i ++ ) 
	{
		const FT_Span& span = spans[i];

		span_info_array->Append( SpanInfo( PointI( span.x, y ), span.len, span.coverage ) );
	}
}

_ubool FontFaceFreeType2::Initialize( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	LockOwner lock_owner( FontFaceFreeType2Lib::GetInstance( ).GetLocker( ) );

	// Create pages
	mCharInfoPagePool.Create( _MAX_PAGE_NUMBER );

	// Clone stream reader
	mStreamReader = stream_reader;

	// Get buffer and size
	const _byte* buffer = mStreamReader->GetBuffer( );
	_dword		 size	= mStreamReader->GetSize( );
	if ( buffer == _null || size == 0 )
		return _false;

	// Create freetype face
	if ( ::FT_New_Memory_Face( FontFaceFreeType2Lib::GetInstance( ).GetFTLibrary( ), buffer, size, 0, &mFTFace ) != 0 )
		return _false;

	return _true;
}

IObject* FontFaceFreeType2::CloneTo( _ubool standalone ) const
{
	FontFaceFreeType2* font = new FontFaceFreeType2( );
	if ( font->Initialize( (IStreamReader*) mStreamReader.GetPtr( ) ) == _false )
		{ EGE_RELEASE( font ); return _null; }

	return font;
}

_FONT_FACE_TYPE FontFaceFreeType2::GetFaceType( ) const
{
	return _FONT_FACE_FREETYPE2;
}

_ubool FontFaceFreeType2::HasCharacter( _dword code ) const
{
	return ::FT_Get_Char_Index( mFTFace, code ) != 0;
}

PointU FontFaceFreeType2::GetCharSize( _dword code )
{
	if ( IsControlCharCode( code ) )
		return PointU::cZeroPoint;

	// Get the code info
	const FontFaceCodeInfoBase* cached_char_info = CacheCodeInfoIfNotExisting( code, _FONT_FACE_LOAD_DEFAULT );
	if ( cached_char_info == _null )
		return PointU::cZeroPoint;

	return PointU( cached_char_info->mCharWidth, cached_char_info->mCharHeight );
}

_dword FontFaceFreeType2::GetCharMaxHeight( ) const
{
	return (_dword)(mFTFace->size->metrics.height / 64);
}

Vector2	FontFaceFreeType2::GetUV( _dword x, _dword y ) const
{
	return FontFaceFreeType2Lib::GetInstance( ).GetUV( x, y );
}

_int FontFaceFreeType2::GetAmountBetweenCharacters( _dword first_code, _dword second_code ) const
{
	return 0;
}

_dword FontFaceFreeType2::GetFontSize( ) const
{
	return mFontSize;
}

_ubool FontFaceFreeType2::SetFontSize( _dword size )
{
	LockOwner lock_owner( FontFaceFreeType2Lib::GetInstance( ).GetLocker( ) );

	// Clear char info
	mCharInfoPagePool.Clear( );

	// Update font size
	mFontSize = size;

	// Set the font size
	if ( ::FT_Set_Char_Size( mFTFace, 0, size * 64, 0, 96 ) != 0 )
		return _false;

	return _true;
}

_ubool FontFaceFreeType2::GetFontCodeInfo( _dword code, _dword flags, FontFaceCodeInfoBase& info )
{
	const FontFaceCodeInfoBase* cached_char_info = CacheCodeInfoIfNotExisting( code, flags );
	if ( cached_char_info == _null )
		return _false;

	info = *cached_char_info;

	return _true;
}

_ubool FontFaceFreeType2::RenderCharacter( _dword code, FontFaceCodeInfo& info )
{
	// Load character and get width and height
	if ( GetCodeInfo( code, _FONT_FACE_LOAD_DEFAULT, info ) == _false )
		return _false;

	// Render character
	::FT_Render_Glyph( mFTFace->glyph, FT_RENDER_MODE_NORMAL );

	// Get the glyph slot of character
	const FT_GlyphSlot glyphslot = mFTFace->glyph;

	// Get bitmap width, height, stride and buffer
	info.mBitmapLeft	= (_short) glyphslot->bitmap_left;
	info.mBitmapTop		= (_short) glyphslot->bitmap_top;
	info.mBitmapWidth	= (_short) glyphslot->bitmap.width;
	info.mBitmapHeight	= (_short) glyphslot->bitmap.rows;
	info.mBitmapBuffer	= glyphslot->bitmap.buffer;
	// Get the offset
	info.mOffsetX		= info.mBitmapLeft;
	info.mOffsetY		= info.mBitmapTop;

	return _true;
}

_ubool FontFaceFreeType2::RenderCharacterByStrokeInfo( _dword code, _dword stroke_size, FontFaceCodeInfo& stroke_info )
{
	LockOwner lock_owner( FontFaceFreeType2Lib::GetInstance( ).GetLocker( ) );

	// Render character
	if ( RenderCharacter( code, stroke_info ) == _false )
		return _false;

	// Get character index
	_dword char_index = ::FT_Get_Char_Index( mFTFace, code );
	if ( char_index == 0 )
		return _false;

	// Load character glyph
	if ( ::FT_Load_Glyph( mFTFace, (FT_UInt)char_index, FT_LOAD_NO_BITMAP ) != 0 )
		return _false;

	// Need an outline for this to work.
	if ( mFTFace->glyph->format != FT_GLYPH_FORMAT_OUTLINE )
		return _false;

	// Get character glyph
	FT_Glyph glyph;
	if ( ::FT_Get_Glyph( mFTFace->glyph, &glyph ) != 0 )
		return _false;

	// Again, this needs to be an outline to work.
	if ( glyph->format != FT_GLYPH_FORMAT_OUTLINE )
		return _false;

	// Get the glyph slot
	const FT_GlyphSlot glyphslot = mFTFace->glyph;

	// Get the char width and height
	stroke_info.mCharWidth		= (_short) glyphslot->metrics.width / 64;
	stroke_info.mCharHeight		= (_short) glyphslot->metrics.height / 64;
	stroke_info.mMaxCharWidth	= (_short) mFTFace->size->metrics.max_advance / 64;
	stroke_info.mMaxCharHeight	= (_short) mFTFace->size->metrics.height / 64;
	// Get the baseline position
	stroke_info.mAscender		= (_short) mFTFace->size->metrics.ascender / 64;
	stroke_info.mDescender		= (_short) mFTFace->size->metrics.descender / 64;
	stroke_info.mBaseLine		= stroke_info.mAscender;
	// Get the advance
	stroke_info.mAdvanceX		= (_short) glyphslot->metrics.horiAdvance / 64;
	// Get the bearing
	stroke_info.mBearingY		= (_short) glyphslot->metrics.horiBearingY / 64;

	// Fix the character size
	if ( stroke_info.mCharWidth == 0 )
		stroke_info.mCharWidth = stroke_info.mAdvanceX;
	if ( stroke_info.mCharHeight == 0 )
		stroke_info.mCharHeight = stroke_info.mMaxCharHeight;

	// Set up a stroker.
	FT_Stroker stroker;
	::FT_Stroker_New( FontFaceFreeType2Lib::GetInstance( ).GetFTLibrary( ), &stroker );
	::FT_Stroker_Set( stroker, (int)(stroke_size * 64), FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0 );
	::FT_Glyph_StrokeBorder( &glyph, stroker, 0, 1 );

	// The outline spans
	SpanInfoArray outline_spans;

	// Render outline info
	FT_Outline* ft_outline = &reinterpret_cast< FT_OutlineGlyph >(glyph)->outline;
	RenderSpans( ft_outline, outline_spans );

	// Build outline character info
	if ( outline_spans.Number( ) != 0 )
	{
		static _byte sPixelBuffer[ FontFaceFreeType2Lib::_TEXTURE_SIZE * FontFaceFreeType2Lib::_TEXTURE_SIZE ];
		RenderCharacterWithSpans( stroke_size, sPixelBuffer, outline_spans, stroke_info );
	}

	// Clean up afterwards.
	::FT_Stroker_Done( stroker );
	::FT_Done_Glyph( glyph );

	return _true;
}

_ubool FontFaceFreeType2::RenderCharacterByBlurInfo( _dword code, _dword blur_size, _float blur_factor, FontFaceCodeInfo& blur_info )
{
	// Render character with stroke effect
	if ( RenderCharacterByStrokeInfo( code, blur_size, blur_info ) == _false )
		return _false;

	// Create pixel buffer for blur effect
	static _byte sPixelBuffer[FontFaceFreeType2Lib::_TEXTURE_SIZE * FontFaceFreeType2Lib::_TEXTURE_SIZE];
	EGE_MEM_SET( sPixelBuffer, 0, blur_info.mBitmapWidth * blur_info.mBitmapHeight );

	// Create target and source image info
	BitmapInfo des_image( _PF_A8, blur_info.mBitmapWidth * blur_info.mBitmapHeight, blur_info.mBitmapWidth, blur_info.mBitmapWidth, blur_info.mBitmapHeight, sPixelBuffer );
	BitmapInfoReadOnly src_image( _PF_A8, blur_info.mBitmapWidth * blur_info.mBitmapHeight, blur_info.mBitmapWidth, blur_info.mBitmapWidth, blur_info.mBitmapHeight, blur_info.mBitmapBuffer );

	// Create target and source region
	RectI region( 0, 0, blur_info.mBitmapWidth, blur_info.mBitmapHeight );

	// Process blur effect
	if ( GetImageProcessor( )->GaussianBlur( des_image, src_image, region, region, blur_factor ) == _false )
		return _false;

	// Save the blur pixel info
	blur_info.mBitmapBuffer = des_image.mPixelBuffer;

	return _true;
}

_ubool FontFaceFreeType2::IsImageType( ) const
{
	return _false;
}

_dword FontFaceFreeType2::GetImageCodesNumber( ) const
{
	return 0;
}

_ubool FontFaceFreeType2::GetImageCodeInfoByIndex( _dword index, FontFaceCodeInfo& info ) const
{
	return _false;
}

const _dword* FontFaceFreeType2::GetImagePixelBuffer( PointU& size ) const
{
	return _null;
}
