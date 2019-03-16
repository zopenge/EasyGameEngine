//! @file     FontFaceFNT.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// FontFaceFNT Implementation
//----------------------------------------------------------------------------

FontFaceFNT::FontFaceFNT( )
{
	mPixelWidth		= 0;
	mPixelHeight	= 0;
	mPixelBuffer	= _null;
}

FontFaceFNT::~FontFaceFNT( )
{
	EGE_DELETE_ARRAY( mPixelBuffer );
}

_ubool FontFaceFNT::Initialize( IStreamReader* stream_reader )
{
	// Parse *.FNT file
	mFNTFile = GetInterfaceFactory( )->ParseFNTFile( stream_reader );
	if ( mFNTFile.IsNull( ) )
		return _false;

	// Get the image file name
	WStringPtr image_file_name = mFNTFile->GetPageImageFileName( 0 );
	if ( image_file_name.IsEmpty( ) )
		return _false;

	// Load stream by file name
	IStreamReaderRef image_stream_reader = GetWorkingArchive( )->LoadResourceByName( image_file_name );
	if ( image_stream_reader.IsNull( ) )
	{
		WLOG_ERROR_1( L"The '%s' file name is not existing, load FNT file failed", image_file_name.Str( ) );
		return _false;
	}

	// Parse image file
	IImageFileRef image_file = GetInterfaceFactory( )->ParseImageFile( image_stream_reader );
	if ( image_file.IsNull( ) )
	{
		WLOG_ERROR_1( L"Load '%s' image file failed, load FNT file failed", image_file_name.Str( ) );
		return _false;
	}

	// We only support ARGB-8 mode
	if ( image_file->GetPixelFormat( ) != _PF_A8R8G8B8 )
	{
		WLOG_ERROR_1( L"The '%s' image file's pixel format is not support, load FNT file failed", image_file_name.Str( ) );
		return _false;
	}

	mPixelWidth		= image_file->GetWidth( );
	mPixelHeight	= image_file->GetHeight( );
	mPixelBuffer	= new _dword[ mPixelWidth * mPixelHeight ];
	EGE_MEM_CPY( mPixelBuffer, image_file->GetPixelBuffer( ), mPixelWidth * mPixelHeight * sizeof( _dword ) );

	return _true;
}

IObject* FontFaceFNT::CloneTo( _ubool standalone ) const
{
	FontFaceFNT* font	= new FontFaceFNT( );
	font->mFNTFile		= mFNTFile;
	font->mPixelWidth	= mPixelWidth;
	font->mPixelHeight	= mPixelHeight;
	font->mPixelBuffer	= new _dword[ mPixelWidth * mPixelHeight ];
	EGE_MEM_CPY( font->mPixelBuffer, mPixelBuffer, mPixelWidth * mPixelHeight * sizeof( _dword ) );

	return font;
}

_FONT_FACE_TYPE FontFaceFNT::GetFaceType( ) const
{
	return _FONT_FACE_FNT;
}

_ubool FontFaceFNT::HasCharacter( _dword code ) const
{
	return mFNTFile->HasCharacter( code );
}

PointU FontFaceFNT::GetCharSize( _dword code )
{
	return mFNTFile->GetCharSize( code );
}

_dword FontFaceFNT::GetCharMaxHeight( ) const
{
	return mFNTFile->GetCharMaxHeight( );
}

Vector2	FontFaceFNT::GetUV( _dword x, _dword y ) const
{
	Vector2 uv;
	uv.x = EGE_RATIO( x, mPixelWidth );
	uv.y = EGE_RATIO( y, mPixelHeight );

	return uv;
}

_int FontFaceFNT::GetAmountBetweenCharacters( _dword first_code, _dword second_code ) const
{
	return mFNTFile->GetAmountBetweenCharacters( first_code, second_code );
}

_dword FontFaceFNT::GetFontSize( ) const
{
	// Not support this operation
	return 0;
}

_ubool FontFaceFNT::SetFontSize( _dword size )
{
	// Not support this operation
	return _false;
}

_ubool FontFaceFNT::GetFontCodeInfo( _dword code, _dword flags, FontFaceCodeInfoBase& info )
{
	return mFNTFile->GetFontCodeInfo( code, flags, info );
}

_ubool FontFaceFNT::RenderCharacter( _dword code, FontFaceCodeInfo& info )
{
	if ( mFNTFile->RenderCharacter( code, info ) == _false )
		return _false;

	info.mBitmapBuffer = (const _byte*)mPixelBuffer;

	return _true;
}

_ubool FontFaceFNT::RenderCharacterByStrokeInfo( _dword code, _dword stroke_size, FontFaceCodeInfo& stroke_info )
{
	return _false;
}

_ubool FontFaceFNT::RenderCharacterByBlurInfo( _dword code, _dword blur_size, _float blur_factor, FontFaceCodeInfo& blur_info )
{
	return _false;
}

_ubool FontFaceFNT::IsImageType( ) const
{
	return _true;
}

_dword FontFaceFNT::GetImageCodesNumber( ) const
{
	return mFNTFile->GetImageCodesNumber( );
}

_ubool FontFaceFNT::GetImageCodeInfoByIndex( _dword index, FontFaceCodeInfo& info ) const
{
	if ( mFNTFile->GetImageCodeInfoByIndex( index, info ) == _false )
		return _false;

	info.mBitmapBuffer = (const _byte*)mPixelBuffer;

	return _true;
}

const _dword* FontFaceFNT::GetImagePixelBuffer( PointU& size ) const
{
	if ( IsImageType( ) == _false )
		return _null;

	// Feedback image size
	size.x = mPixelWidth;
	size.y = mPixelHeight;

	return mPixelBuffer;
}
