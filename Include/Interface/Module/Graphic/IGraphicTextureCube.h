//! @file     IGraphicTextureCube.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicTextureCube
//----------------------------------------------------------------------------

class IGraphicTextureCube : public IObject
{
public:
	//!	Set the resource handle.
	//!	@param		texture.
	//!	@return		none.
	virtual _void SetResource( TextureCubeRHI* texture ) PURE;
	//!	Get the resource handle.
	//!	@param		none.
	//!	@return		The texture resource handle.
	virtual TextureCubeRHI* GetResource( ) const PURE;

	//!	Get the width.
	//!	@param		none.
	//!	@return		The width of texture in pixel.
	virtual _dword GetWidth( ) const PURE;
	//!	Get the height.
	//!	@param		none.
	//!	@return		The height of texture in pixel.
	virtual _dword GetHeight( ) const PURE;
};

}