//! @file     IGraphicViewport.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicViewport
//----------------------------------------------------------------------------

class IGraphicViewport : public IGraphicScene
{
public:
	//!	Begin the back surface rendering.
	//!	@param		scale	The rendering scale.
	//! @return		none.
	virtual _void BeginBackSurfaceRendering( _float scale ) PURE;
	//!	End the back surface rendering.
	//!	@param		none.
	//! @return		none.
	virtual _void EndBackSurfaceRendering( ) PURE;
	//!	Clear the back surface.
	//!	@param		none.
	//! @return		none.
	virtual _void ClearBackSurface( ) PURE;
	//!	Create the back surface.
	//!	@param		size		The back surface size.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool CreateBackSurface( const PointU& size ) PURE;
	//!	Get the back surface.
	//!	@param		none.
	//! @return		none.
	virtual IGraphicBackSurface* GetBackSurface( ) PURE;

	//!	Bind.
	//!	@param		none.
	//!	@return		none.
	virtual _void Bind( ) PURE;

	//!	Present.
	//!	@param		none.
	//!	@return		none.
	virtual _void Present( ) PURE;

	//!	Set the scene proxy.
	//!	@param		scene	The scene interface.
	//!	@return		none.
	virtual _void SetSceneProxy( IGraphicScene* scene ) PURE;
	//!	Get the scene proxy.
	//!	@param		none.
	//!	@return		The scene interface.
	virtual IGraphicScene* GetSceneProxy( ) PURE;

};

}