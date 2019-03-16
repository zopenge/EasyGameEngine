//! @file     IGraphicMaskLayer.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2015/11/18

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicMirror
//----------------------------------------------------------------------------

class IGraphicMaskLayer : public IObject
{
public:
	//!	Initialize.
	virtual _ubool Initialize( ) PURE;

	//!	Set/Push/Pop mask rectangle.
	virtual _void SetMaskLayer( const RectF& region, _dword mask_value ) PURE;
	virtual _void PushMaskLayer( const RectF& region, _dword mask_value ) PURE;
	virtual _void PopMaskLayer( ) PURE;

	//!	Push/Pop effect with mask layer.
	virtual _void PushEffect( IGraphicEffect* effect ) PURE;
	virtual _void PopEffect( IGraphicEffect* effect ) PURE;

	//!	Get the current mask value.
	virtual _dword GetCurMaskValue( ) const PURE;
};

}