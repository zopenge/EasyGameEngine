//! @file     GraphicPointLight.h
//! @author   LiCode
//! @version  1.0
//! @date     2015.6
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicPointLight
//----------------------------------------------------------------------------

class GraphicPointLight : public TGraphicLight< IGraphicPointLight >
{
public:
	typedef TGraphicLight< IGraphicPointLight >	BaseClass;
private:

public:
	GraphicPointLight( );
	virtual ~GraphicPointLight( );

// IObject Interface
public:
	virtual IObject*				CloneTo( ) const override;

// IGraphicLight Interface
public:
	virtual _GRAPHIC_LIGHT_TYPE		GetLightType( ) const override;
};

}