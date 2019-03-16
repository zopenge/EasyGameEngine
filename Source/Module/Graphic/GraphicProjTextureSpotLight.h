//! @file     GraphicProjTextureSpotLight.h
//! @author   LiCode
//! @version  1.0
//! @date     2015.6
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicProjTextureSpotLight
//----------------------------------------------------------------------------

class GraphicProjTextureSpotLight : public TGraphicSpotLight< IGraphicProjTextureSpotLight >
{
public:
	typedef TGraphicSpotLight< IGraphicProjTextureSpotLight >	BaseClass;

private:
	IGraphicTexture2DRef		mProjectiveTexture;
	_float						mProjectiveTexturePower;
	_GRAPHIC_COLOR_OPERATION	mColorOperation;

public:
	GraphicProjTextureSpotLight( );
	virtual ~GraphicProjTextureSpotLight( );

// IObject Interface
public:
	virtual IObject*					CloneTo( ) const override;

// IGraphicLight Interface
public:
	virtual _GRAPHIC_LIGHT_TYPE			GetLightType( ) const override;

// IGraphicProjTextureSpotLight Interface
public:
	virtual _void						SetProjectiveTexture( IGraphicTexture2D* texture ) override;
	virtual IGraphicTexture2D*			GetProjectiveTexture( ) const override;
	virtual _void						SetProjTexturePower( _float power ) override;
	virtual _float						GetProjTexturePower( ) const override;
	virtual _void						SetColorOperation( _GRAPHIC_COLOR_OPERATION power ) override;
	virtual _GRAPHIC_COLOR_OPERATION	GetColorOperation( ) const override;
};

}