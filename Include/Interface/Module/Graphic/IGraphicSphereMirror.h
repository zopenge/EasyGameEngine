//! @file     IGraphicMirror.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2015/06/17

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicMirror
//----------------------------------------------------------------------------

class IGraphicMirror : public IGraphicCanvas
{
public:
	virtual _GRAPHIC_MIRROR_TYPE GetType( ) const PURE;

	//! Set the plane.
	//! @param		plane		The plane.
	//! @return		none.
	virtual _void SetPlane( const Plane& plane ) PURE;
	//! Get the plane.
	//! @param		none.
	//! @return		The plane.
	virtual const Plane& GetPlane( ) const PURE;

	virtual const Viewport& GetMirrorViewport( ) const PURE;
};

}