//! @file     GraphicSpotLight.h
//! @author   LiCode
//! @version  1.0
//! @date     2015.6
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicSpotLight
//----------------------------------------------------------------------------

class GraphicSpotLight : public TGraphicSpotLight< IGraphicSpotLight >
{
public:
	typedef TGraphicSpotLight< IGraphicSpotLight >	BaseClass;

public:
	GraphicSpotLight( );
	virtual ~GraphicSpotLight( );

// IObject Interface
public:
	virtual IObject*				CloneTo( ) const override;

// IGraphicLight Interface
public:
	virtual _GRAPHIC_LIGHT_TYPE		GetLightType( ) const override;
};

}