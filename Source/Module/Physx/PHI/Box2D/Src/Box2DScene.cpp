//! @file     Box2DScene.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// Box2DDrv-Scene Implementation
//----------------------------------------------------------------------------

ScenePHIPassRef Box2DDrv::CreateScene( const Vector3& gravity )
{
	b2World* world = new b2World( b2Vec2( gravity.x, gravity.y ) );

	return new Box2DScene( world );
}

_void Box2DDrv::UpdateScene( ScenePHI* scene, _dword elapse )
{
	DYNAMIC_CAST_BOX2D_RESOURCE( Scene, scene );

	static const _float cTimeStep			= 1.0f / 60.0f;
	static const _dword cVelocityIterations	= 6;
	static const _dword cPositionIterations	= 2;

	box2d_scene->GetResource( )->Step( cTimeStep, cVelocityIterations, cPositionIterations );
}

_void Box2DDrv::DrawScene( ScenePHI* scene, IPhysxRenderer* renderer )
{

}

//----------------------------------------------------------------------------
// Box2DScene Implementation
//----------------------------------------------------------------------------

Box2DScene::Box2DScene( b2World* resource ) : mResource( resource )
{
}

Box2DScene::~Box2DScene( )
{
	EGE_DELETE( mResource );
}