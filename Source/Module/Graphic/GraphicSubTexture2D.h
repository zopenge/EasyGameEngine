//! @file     GraphicSubTexture2D.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicSubTexture2D
//----------------------------------------------------------------------------

class GraphicSubTexture2D : public INTERFACE_OBJECT_IMPL( IGraphicTexture2D )
{
	RTTI_CLASS( GraphicSubTexture2D )

private:
	//!	The left-top texture coordinate.
	Vector2					mUV1;
	//!	The right-bottom texture coordinate.
	Vector2					mUV2;
	//!	The size in pixel
	PointU					mSize;

	//!	The transparent layer buffer
	OneBitArray				mTransparentLayer;

	//!	The texture interface of sub-image
	IGraphicTexture2DRef	mTexture2D;

private:
	//!	Get the left coordinate.
	_dword GetLeft( ) const;
	//!	Get the top coordinate.
	_dword GetTop( ) const;
	//!	Get the sub-rect.
	RectU GetSubRect( const RectU& rect ) const;

public:
	GraphicSubTexture2D( const Vector2& uv1, const Vector2& uv2, IGraphicTexture2D* texture );
	virtual ~GraphicSubTexture2D( );

public:
	_ubool Initialize( );

// IGraphicTexture2D Interface
public:
	virtual _ubool						IsDynamicTexture( ) const override;

	virtual _dword						GetMipmaps( ) const override;
	virtual _dword						GetSizeInBytes( ) const override;
	virtual _dword						GetWidth( ) const override;
	virtual _dword						GetHeight( ) const override;
	virtual const PointU&				GetSize( ) const override;
	virtual _dword						GetPixelSize( ) const override;
	virtual _PIXEL_FORMAT				GetPixelFormat( ) const override;
	virtual SamplerStateInitializerRHI	GetSamplerStateInfo( ) const override;
	virtual RectU						GetRect( ) const override;
	virtual const OneBitArray&			GetTransparentLayer( ) const override;

	virtual Texture2DRHI*				GetResource( ) const override;
	virtual _void						SetResource( Texture2DRHI* texture ) override;

	virtual _void						SetUV( const Vector2& uv1, const Vector2& uv2 ) override;
	virtual _void						GetUV( Vector2& uv1, Vector2& uv2 ) const override;

	virtual Vector2						FixUV( const Vector2& uv ) const override;
	virtual Vector2						FixUV( const PointU& pos ) const override;

	virtual _ubool						UpdatePixelBuffer( const RectU& rect, const _byte* buffer ) override;

	virtual _ubool						IsTransparentPixel( _dword x, _dword y ) const override;
	virtual _ubool						HasTransparentLayer( ) const override;
	virtual _ubool						SetTransparentLayer( _dword width, _dword height, const OneBitArray& layer ) override;

	virtual _void						UnloadResource( ) override;

	virtual _ubool						SaveToFile( _FILE_FORMAT fileformat, WStringPtr filename, _ubool is_vert_flip, _ubool swap_r_and_b ) const override;
};

//----------------------------------------------------------------------------
// GraphicSubTexture2D Implementation
//----------------------------------------------------------------------------

}