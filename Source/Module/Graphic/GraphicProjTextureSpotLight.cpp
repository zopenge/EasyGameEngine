//! @file     GraphicProjTextureSpotLight.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicProjTextureSpotLight Implementation
//----------------------------------------------------------------------------

GraphicProjTextureSpotLight::GraphicProjTextureSpotLight( )
{
	mProjectiveTexturePower = 1.0f;
	mColorOperation			= _GCO_ADD_;
}

GraphicProjTextureSpotLight::~GraphicProjTextureSpotLight( )
{

}

IObject* GraphicProjTextureSpotLight::CloneTo( ) const
{
	GraphicProjTextureSpotLight* light	= new GraphicProjTextureSpotLight( );
	light->CopyFrom( this );
	light->mProjectiveTexture			= mProjectiveTexture;
	light->mProjectiveTexturePower		= mProjectiveTexturePower;
	light->mColorOperation				= mColorOperation;

	return light;
}

_GRAPHIC_LIGHT_TYPE GraphicProjTextureSpotLight::GetLightType( ) const
{
	return _GLT_PROJTEX_SPOT_LIGHT;
}

_void GraphicProjTextureSpotLight::SetProjectiveTexture( IGraphicTexture2D* texture )
{
	mProjectiveTexture = texture;
}

IGraphicTexture2D* GraphicProjTextureSpotLight::GetProjectiveTexture( ) const
{
	return mProjectiveTexture.GetPtr( );
}

_void GraphicProjTextureSpotLight::SetProjTexturePower( _float power )
{
	mProjectiveTexturePower = power;
}

_float GraphicProjTextureSpotLight::GetProjTexturePower( ) const
{
	return mProjectiveTexturePower;
}

_void GraphicProjTextureSpotLight::SetColorOperation( _GRAPHIC_COLOR_OPERATION power )
{
	mColorOperation = power;
}

_GRAPHIC_COLOR_OPERATION GraphicProjTextureSpotLight::GetColorOperation( ) const
{
	return mColorOperation;
}