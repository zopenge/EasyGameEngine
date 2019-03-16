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
	virtual _GRAPHIC_MIRROR_TYPE GetMirrorType( ) const PURE;

	virtual const PointU& GetMirrorSize( ) const PURE;

	virtual const Viewport& GetMirrorViewport( ) const PURE;
};

//----------------------------------------------------------------------------
// IGraphicFlatMirror
//----------------------------------------------------------------------------

class IGraphicFlatMirror : public IGraphicMirror
{
public:
	//!	Set the attenuation distance.
	//!	@param		distance	The distance, 0.0 indicates disable it.
	//!	@return		none.
	virtual _void SetAttenuationDistance( _float distance ) PURE;
	//!	Get the attenuation distance.
	//!	@param		none.
	//!	@return		The distance, 0.0 indicates disable it.
	virtual _float GetAttenuationDistance( ) const PURE;

	//! Set the plane.
	//! @param		plane		The plane.
	//! @return		none.
	virtual _void SetPlane( const Plane& plane ) PURE;
	//! Get the plane.
	//! @param		none.
	//! @return		The plane.
	virtual const Plane& GetPlane( ) const PURE;
};

//----------------------------------------------------------------------------
// IGraphicSphereMirror
//----------------------------------------------------------------------------

class IGraphicSphereMirror : public IGraphicMirror
{
public:
	virtual IGraphicSceneView* GetEnvironmentMapSceneView( ) PURE;
};

}