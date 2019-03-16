//! @file     GraphicTextureCube.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicTextureCube
//----------------------------------------------------------------------------

class GraphicTextureCube : public INTERFACE_OBJECT_IMPL( IGraphicTextureCube )
{
private:
	//!	The RHI texture resource
	TextureCubeRHIRef	mResource;

private:

public:
	GraphicTextureCube( TextureCubeRHI* resource );
	virtual ~GraphicTextureCube( );

// IGraphicTextureCube Interface
public:
	virtual _void			SetResource( TextureCubeRHI* texture ) override;
	virtual TextureCubeRHI*	GetResource( ) const override;

	virtual _dword			GetWidth( ) const override;
	virtual _dword			GetHeight( ) const override;
};

//----------------------------------------------------------------------------
// GraphicTextureCube Implementation
//----------------------------------------------------------------------------

}