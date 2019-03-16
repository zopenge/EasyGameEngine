//! @file     IGraphicSubTexture2D.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicSubTexture2D
//----------------------------------------------------------------------------

class IGraphicSubTexture2D : public IGraphicTexture2D
{
public:
	//!	Get the region in pixel of whole texture.
	//!	@param		none.
	//!	@return		The region in pixel.
	virtual RectU GetSubRect( ) const PURE;

	//!	Set size.
	//!	@param		size		The size.
	//!	@return		none.
	virtual _void SetSize( const PointU& size ) PURE;

	//!	Update the uv-coordinate.
	//!	@param		uv1			The uv1-coordinate.
	//!	@param		uv2			The uv2-coordinate.
	//!	@return		none.
	virtual _void SetUV( const Vector2& uv1, const Vector2& uv2 ) PURE;
	//!	Get the uv-coordinate.
	//!	@param		uv1			The uv1-coordinate.
	//!	@param		uv2			The uv2-coordinate.
	//!	@return		none.
	virtual _void GetUV( Vector2& uv1, Vector2& uv2 ) const PURE;

	//!	Get the whole texture.
	//!	@param		none.
	//!	@return		The whole texture.
	virtual IGraphicTexture2D* GetWholeTexture( ) PURE;
};

}