//! @file     IGUIComponent3DRender.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2015/08/06
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGUIComponent3DRender
//----------------------------------------------------------------------------

class IGUIComponent3DRender : public IGUIComponent
{
public:
	CLASS_NAME_DECL( IGUIComponent3DRender )

public:
	virtual _void SetFOV( _float fov ) PURE;
	virtual _float GetFOV( ) const PURE;
	virtual const Frustum& GetFrustum( ) const PURE;
	virtual const Matrix4& GetScalingMatrix( ) const PURE;
	virtual const Matrix4& GetProjectionMatrix( ) const PURE;
	virtual const Matrix4& GetViewProjectionMatrix( ) const PURE;
	virtual Vector3 Get3DPosition( _float x, _float y ) const PURE;
};

}