//! @file     GraphicPointLight.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicPointLight Implementation
//----------------------------------------------------------------------------

GraphicPointLight::GraphicPointLight( )
{

}

GraphicPointLight::~GraphicPointLight( )
{
}

IObject* GraphicPointLight::CloneTo( ) const
{
	GraphicPointLight* light = new GraphicPointLight( );
	light->CopyFrom( this );

	return light;
}

_GRAPHIC_LIGHT_TYPE GraphicPointLight::GetLightType( ) const
{
	return _GLT_POINT_LIGHT;
}