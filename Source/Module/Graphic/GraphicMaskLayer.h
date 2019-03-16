//! @file     GraphicMaskLayer.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicMaskLayer
//----------------------------------------------------------------------------

class GraphicMaskLayer : TObject< IGraphicMaskLayer >
{
private:
	//!	The mask layer info
	struct MaskLayerInfo
	{
		_dword				mMaskValue;
		RectF				mRegion;

		StencilStateRHIRef	mStencilState;
		StencilStateRHIRef	mStencilStateForEffect;

		MaskLayerInfo( )
		{
			mMaskValue	= 0;
			mRegion		= RectF::cNull;
		}
	};
	typedef Stack< MaskLayerInfo > MaskLayerInfoStack;

	//!	The sprite info
	struct MaskSpriteInfo
	{
		Matrix3					mTransform;
		Vector2					mOffset;
		Vector2					mSize;
		IGraphicTexture2DRef	mSprite;
		Color					mColor;
		GraphicUVInfo			mUVInfo;

		MaskSpriteInfo( )
		{
			mTransform	= Matrix3::cIdentity;
			mOffset		= Vector2::cOrigin;
			mSize		= Vector2::cOrigin;
			mColor		= Color::cWhite;
		}
	};
	typedef Stack< MaskSpriteInfo > MaskSpriteInfoStack;

private:
	GraphicGeometryProcessor*	mGeometryProcessor;

	IGraphicEffectRef			mStencilEffect;
	IGraphicEffectRef			mMaskSpriteEffect;

	MaskLayerInfoStack			mMaskLayers;
	MaskSpriteInfoStack			mMaskSprites;

	StencilStateRHIRef			mPrevStencilState;

private:
	//!	Update stencil buffer.
	_void UpdateStencilBuffer( const RectF& region, StencilStateRHI* stencil_state );

public:
	GraphicMaskLayer( GraphicGeometryProcessor* geometry_processor );
	virtual ~GraphicMaskLayer( );

public:
	_void BuildMaskLayer( const RectF& region, _dword mask_value, MaskLayerInfo& info );

	//!	Push/Pop mask sprite.
	_void PushMaskSprite( const Matrix3& transform, const Vector2& offset, const Vector2& size, IGraphicTexture2D* sprite, const Color& color, const GraphicUVInfo& uv_info );
	_void PopMaskSprite( );

	//!	Render sprite with mask.
	_void RenderSpriteWithMask( IGraphicEffect* effect, const Matrix3& transform, const Vector2& offset, const Vector2& size, IGraphicTexture2D* sprite, const Color& color, const GraphicUVInfo& uv_info );

// IGraphicMaskLayer Interface
public:
	virtual _ubool	Initialize( ) override;

	virtual _void	SetMaskLayer( const RectF& region, _dword mask_value ) override;
	virtual _void	PushMaskLayer( const RectF& region, _dword mask_value ) override;
	virtual _void	PopMaskLayer( ) override;

	virtual _void	PushEffect( IGraphicEffect* effect ) override;
	virtual _void	PopEffect( IGraphicEffect* effect ) override;

	virtual _dword	GetCurMaskValue( ) const override;
};

//----------------------------------------------------------------------------
// GraphicMaskLayer Implementation
//----------------------------------------------------------------------------

}