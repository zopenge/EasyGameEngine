//! @file     GraphicLight.h
//! @author   LiCode
//! @version  1.0
//! @date     2015.6
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// GraphicLight
//----------------------------------------------------------------------------

class GraphicLight : public TObject< IGraphicLight >
{
private:
	_float					mRange;
	_float					mAttenuation;
	Color					mColor;

	Camera					mCamera;
	_float					mAspect;
	Frustum					mViewFrustum;
	Matrix4					mProjTextureTransform;

	_float					mProjectiveTexturePower;
	IGraphicTexture2DRef	mProjectiveTexture;

public:
	GraphicLight( );
	virtual ~GraphicLight( );

private:
	_float GetNear( _float f ) const;

	_void Update( );

// IObject Interface
public:
	virtual IObject*			CloneTo( _ubool standalone ) const override;

// IGraphicLight Interface
public:
	virtual _void				SetPosition( const Vector3& position ) override;
	virtual const Vector3&		GetPosition( ) const override;

	virtual _void				SetRange( _float range ) override;
	virtual _float				GetRange( ) const override;

	virtual _void				SetAspect( _float aspect ) override;
	virtual _float				GetAspect( ) const override;

	virtual _void				SetFovDegree( _float fov ) override;
	virtual _float				GetFovDegree( ) const override;

	virtual _void				SetColor( const Color& color ) override;
	virtual const Color&		GetColor( ) const override;

	virtual _void				SetAttenuation( _float value ) override;
	virtual _float				GetAttenuation( ) const override;

	virtual _void				SetCamera( const Camera& camera ) override;
	virtual _void				SetCamera( const Camera& camera, _float aspect, _float range ) override;
	virtual const Camera&		GetCamera( ) const override;

	virtual const Frustum&		GetViewFrustum( ) const override;

	virtual const Matrix4&		GetProjTextureTransform( ) const override;

	virtual _void				SetProjectiveTexture( IGraphicTexture2D* texture ) override;
	virtual IGraphicTexture2D*	GetProjectiveTexture( ) const override;
	virtual _void				SetProjTexturePower( _float power ) override;
	virtual _float				GetProjTexturePower( ) const override;
};

}