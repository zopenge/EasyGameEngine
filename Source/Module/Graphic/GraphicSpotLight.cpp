//! @file     GraphicSpotLight.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicSpotLight Implementation
//----------------------------------------------------------------------------

GraphicSpotLight::GraphicSpotLight( )
{

}

GraphicSpotLight::~GraphicSpotLight( )
{

}

IObject* GraphicSpotLight::CloneTo( ) const
{
	GraphicSpotLight* light = new GraphicSpotLight( );
	light->CopyFrom( this );

	return light;
}

_GRAPHIC_LIGHT_TYPE GraphicSpotLight::GetLightType( ) const
{
	return _GLT_SPOT_LIGHT;
}