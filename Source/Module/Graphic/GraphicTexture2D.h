//! @file     GraphicTexture2D.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicTexture2D
//----------------------------------------------------------------------------

class GraphicTexture2D : public INTERFACE_OBJECT_IMPL( IGraphicTexture2D )
{
	RTTI_CLASS( GraphicTexture2D )

private:
	//!	The transparent layer buffer
	OneBitArray		mTransparentLayer;

	//!	The RHI texture resource
	Texture2DRHIRef	mResource;

public:
	GraphicTexture2D( Texture2DRHI* resource );
	virtual ~GraphicTexture2D( );

// IObject Interface
public:
	virtual _ubool						CopyFrom( const IObject* obj ) override;

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
// GraphicTexture2D Implementation
//----------------------------------------------------------------------------

}