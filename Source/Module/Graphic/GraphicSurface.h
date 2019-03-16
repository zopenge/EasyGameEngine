//! @file     GraphicSurface.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicSurface
//----------------------------------------------------------------------------

class GraphicSurface : public INTERFACE_OBJECT_IMPL( IGraphicSurface )
{
private:
	//!	The RHI surface resource
	SurfaceRHIRef			mResource;

	//!	The texture 2D resource
	IGraphicTexture2DRef	mTexture2D;
	//!	The texture cube resource
	IGraphicTextureCubeRef	mTextureCube;

public:
	GraphicSurface( );
	virtual ~GraphicSurface( );

public:
	//!	Initialize.
	_ubool Initialize( SurfaceRHI* resource );

// IGraphicSurface Interface
public:
	virtual SurfaceRHI*				GetResource( ) override;

	virtual const PointU&			GetSize( ) const override;

	virtual _dword					GetTexture2DResID( ) const override;

	virtual IGraphicTexture2D*		GetTexture2D( ) const override;
	virtual IGraphicTextureCube*	GetTextureCube( ) const override;

	virtual _ubool					SetFaceIndex( _dword index ) override;
	virtual _dword					GetFaceIndex( ) const override;

	virtual _ubool					SaveToFile( _FILE_FORMAT fileformat, WStringPtr filename, _ubool is_vert_flip, _ubool swap_r_and_b ) override;
};

//----------------------------------------------------------------------------
// GraphicSurface Implementation
//----------------------------------------------------------------------------

}