//! @file     IGraphicSurface.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicSurface
//----------------------------------------------------------------------------

class IGraphicSurface : public IObject
{
public:
	//!	Get the RHI surface resource.
	//!	@param		none.
	//!	@return		The surface resource.
	virtual SurfaceRHI* GetResource( ) PURE;

	//!	Get the size.
	//!	@param		none.
	//!	@return		The size.
	virtual const PointU& GetSize( ) const PURE;

	//!	Get the 2D texture resource ID.
	//!	@param		none.
	//!	@return		The 2D texture resource ID.
	virtual _dword GetTexture2DResID( ) const PURE;

	//!	Get the 2D texture.
	//!	@param		none.
	//!	@return		The 2D texture interface.
	virtual IGraphicTexture2D* GetTexture2D( ) const PURE;
	//!	Get the cube texture.
	//!	@param		none.
	//!	@return		The cube texture interface.
	virtual IGraphicTextureCube* GetTextureCube( ) const PURE;

	//!	Set the face index of cube.
	//!	@param		index		The face index, in [0, 5] bounds.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetFaceIndex( _dword index ) PURE;
	//!	Get the face index of cube.
	//!	@param		none.
	//! @return		The face index of cube.
	virtual _dword GetFaceIndex( ) const PURE;

	//!	Save to image file.
	//!	@param		fileformat		The file format.
	//!	@param		filename		The image file name.
	//!	@param		is_vert_flip	True indicates flip the vert.
	//!	@param		swap_r_and_b	True indicates swap red and blue channel.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SaveToFile( _FILE_FORMAT fileformat, WStringPtr filename, _ubool is_vert_flip, _ubool swap_r_and_b ) PURE;
};

}