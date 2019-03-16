//! @file     FontFaceFreeType2.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FontFaceFreeType2
//----------------------------------------------------------------------------

//!	See reference web site: http://liu1227787871.blog.163.com/blog/static/2053631972012628113620362/
class FontFaceFreeType2 : public INTERFACE_OBJECT_IMPL( IFontFace )
{
private:
	enum 
	{ 
		//!	The font code number in one page
		_MAX_PAGE_SIZE		= 256,
		//!	The font page number
		_MAX_PAGE_NUMBER	= 256,
	};

private:
	typedef PagePool< FontFaceCodeInfoBase, _MAX_PAGE_SIZE > CharInfoPagePool;

private:
	//!	The span info
	struct SpanInfo
	{
		PointI	mPos;
		_int	mWidth;
		_int	mCoverage;

		SpanInfo( )
		{
			mPos		= PointI::cZeroPoint;
			mWidth		= 0;
			mCoverage	= 0;
		}
		SpanInfo( const PointI& pos, _int width, _int coverage )
		{
			mPos		= pos;
			mWidth		= width;
			mCoverage	= coverage;
		}
	};
	typedef Array< SpanInfo > SpanInfoArray;

private:
	//!	The font stream reader
	IStreamReaderRef	mStreamReader;

	//!	The FreeType face handle
	FT_Face				mFTFace;
	//!	The font size
	_dword				mFontSize;

	//!	The character info page pool
	CharInfoPagePool	mCharInfoPagePool;

private:
	//!	Check whether it's control character (can't show) or not.
	_ubool IsControlCharCode( _dword id ) const;

	//!	Cache code info.
	_ubool GetCodeInfo( _dword code, _dword flags, FontFaceCodeInfoBase& char_info );
	const FontFaceCodeInfoBase* CacheCodeInfoIfNotExisting( _dword code, _dword flags );

	//!	Render spans.
	_void RenderSpans( FT_Outline* const outline, SpanInfoArray& spans );
	//!	Render to pixel buffer.
	_void RenderCharacterWithSpans( _dword stroke_size, _byte* pixel_buffer, const SpanInfoArray& spans, FontFaceCodeInfo& info );

private:
	//!	When render spins info.
	static _void OnRenderSpinsCallback( const _int y, const _int count, const FT_Span* const spans, void* const user );

public:
	FontFaceFreeType2( );
	virtual ~FontFaceFreeType2( );

public:
	//!	Initialize.
	//!	@param		stream_reader	The stream reader.
	//! @return		True indicates success, false indicates failure.
	_ubool Initialize( IStreamReader* stream_reader );

// IObject Interface
public:
	virtual IObject*		CloneTo( _ubool standalone ) const override;

// IFontFace Interface
public:
	virtual _FONT_FACE_TYPE	GetFaceType( ) const override;

	virtual _ubool			HasCharacter( _dword code ) const override;

	virtual PointU			GetCharSize( _dword code ) override;
	virtual _dword			GetCharMaxHeight( ) const override;

	virtual Vector2			GetUV( _dword x, _dword y ) const override;

	virtual _int			GetAmountBetweenCharacters( _dword first_code, _dword second_code ) const override;

	virtual _dword			GetFontSize( ) const override;
	virtual _ubool			SetFontSize( _dword size ) override;
	virtual _ubool			GetFontCodeInfo( _dword code, _dword flags, FontFaceCodeInfoBase& info ) override;

	virtual _ubool			RenderCharacter( _dword code, FontFaceCodeInfo& info ) override;
	virtual _ubool			RenderCharacterByStrokeInfo( _dword code, _dword stroke_size, FontFaceCodeInfo& stroke_info ) override;
	virtual _ubool			RenderCharacterByBlurInfo( _dword code, _dword blur_size, _float blur_factor, FontFaceCodeInfo& blur_info ) override;

	virtual _ubool			IsImageType( ) const override;
	virtual _dword			GetImageCodesNumber( ) const override;
	virtual _ubool			GetImageCodeInfoByIndex( _dword index, FontFaceCodeInfo& info ) const override;
	virtual const _dword*	GetImagePixelBuffer( PointU& size ) const override;
};

//----------------------------------------------------------------------------
// FontFaceFreeType2 Implementation
//----------------------------------------------------------------------------

}