//! @file     IGraphicProjTextureSpotLight.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2015/06/15

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicProjTextureSpotLight
//----------------------------------------------------------------------------

class IGraphicProjTextureSpotLight : public IGraphicSpotLight
{
public:
	//!	Set the projective texture.
	//!	@param		texture		The projective texture.
	//!	@return		none.
	virtual _void SetProjectiveTexture( IGraphicTexture2D* texture ) PURE;
	//!	Get the projective texture.
	//!	@param		none.
	//!	@return		The projective texture.
	virtual IGraphicTexture2D* GetProjectiveTexture( ) const PURE;

	virtual _void SetProjTexturePower( _float power ) PURE;
	virtual _float GetProjTexturePower( ) const PURE;
	virtual _void SetColorOperation( _GRAPHIC_COLOR_OPERATION power ) PURE;
	virtual _GRAPHIC_COLOR_OPERATION GetColorOperation( ) const PURE;
};

}