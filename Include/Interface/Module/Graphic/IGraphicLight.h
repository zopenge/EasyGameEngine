//! @file     IGraphicLight.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicLight
//----------------------------------------------------------------------------

class IGraphicLight : public IObject
{
public:
	//!	Set the position.
	//!	@param		position		The light position.
	//!	@return		none.
	virtual _void SetPosition( const Vector3& position ) PURE;
	//!	Get the position.
	//!	@param		none.
	//!	@return		The light position.
	virtual const Vector3& GetPosition( ) const PURE;

	//!	Set the light range.
	//!	@param		range		The light range.
	//!	@return		none.
	virtual _void SetRange( _float range ) PURE;
	//!	Get the light range.
	//!	@param		none.
	//!	@return		The light range.
	virtual _float GetRange( ) const PURE;

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

	virtual _void SetColor( const Color& color ) PURE;
	virtual const Color& GetColor( ) const PURE;

	virtual _void SetAttenuation( _float value ) PURE;
	virtual _float GetAttenuation( ) const PURE;

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
	virtual const Matrix4& GetProjTextureTransform( ) const PURE;

	//!	Set the projective texture.
	//!	@param		texture		The projective texture.
	//!	@return		none.
	virtual _void SetProjectiveTexture( IGraphicTexture2D* texture ) PURE;
	//!	Get the projective texture.
	//!	@param		none.
	//!	@return		The projective texture.
	virtual IGraphicTexture2D* GetProjectiveTexture( ) const PURE;

	virtual _void SetProjTexturePower( _float power ) PURE;
	virtual _float GetProjTexturePower( ) const PURE;
};

}