//! @file     IGraphicSpotLight.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2015/06/15

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicSpotLight
//----------------------------------------------------------------------------

class IGraphicSpotLight : public IGraphicLight
{
public:
	//!	Set the light aspect.
	//!	@param		aspect		The light aspect.
	//!	@return		none.
	virtual _void SetAspect( _float aspect ) PURE;
	//!	Get the aspect.
	//!	@param		none.
	//!	@return		The light aspect.
	virtual _float GetAspect( ) const PURE;
	//!	Set the fov.
	//!	@param		fov		The fov.
	//!	@return		none.
	virtual _void SetFovDegree( _float fov ) PURE;
	//!	Get the fov.
	//!	@param		none.
	//!	@return		The light fov.
	virtual _float GetFovDegree( ) const PURE;
	//!	Set the light camera.
	//!	@param		camera		The light camera.
	//!	@return		none.
	virtual _void SetCamera( const Camera& camera ) PURE;
	virtual _void SetCamera( const Camera& camera, _float aspect, _float range ) PURE;
	//!	Get the camera.
	//!	@param		none.
	//!	@return		The light camera.
	virtual const Camera& GetCamera( ) const PURE;

	//!	Get the view frustum.
	//!	@param		none.
	//!	@return		The view frustum.
	virtual const Frustum& GetViewFrustum( ) const PURE;

	//!	Get the MVP(model * view * projection) transform.
	//!	@param		none.
	//!	@return		The transform.
	virtual const Matrix4& GetProjTextureMatrix( ) const PURE;
};

}