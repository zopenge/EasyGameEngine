//! @file     FontFaceFNT.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FontFaceFNT
//----------------------------------------------------------------------------

class FontFaceFNT : public INTERFACE_OBJECT_IMPL( IFontFace )
{
private:
	IFNTFileRef	mFNTFile;

	_dword		mPixelWidth;
	_dword		mPixelHeight;
	_dword*		mPixelBuffer; // ARGB

public:
	FontFaceFNT( );
	virtual ~FontFaceFNT( );

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
// FontFaceFNT Implementation
//----------------------------------------------------------------------------

}