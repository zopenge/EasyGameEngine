//! @file     GraphicTextureCube.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEGraphic.h"

//----------------------------------------------------------------------------
// GraphicTextureCube Implementation
//----------------------------------------------------------------------------

GraphicTextureCube::GraphicTextureCube( TextureCubeRHI* resource ) : mResource( resource )
{
}

GraphicTextureCube::~GraphicTextureCube( )
{
}

_void GraphicTextureCube::SetResource( TextureCubeRHI* texture )
{
	mResource = texture;
}

TextureCubeRHI* GraphicTextureCube::GetResource( ) const
{
	return mResource.GetPtr( );
}

_dword GraphicTextureCube::GetWidth( ) const
{
	return gDynamicRHI->GetTextureCubeSize( mResource.GetPtr( ) ).x;
}

_dword GraphicTextureCube::GetHeight( ) const
{
	return gDynamicRHI->GetTextureCubeSize( mResource.GetPtr( ) ).y;
}