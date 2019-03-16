//! @file     PhysxScene.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// PhysxScene Implementation
//----------------------------------------------------------------------------

PhysxScene::PhysxScene( ScenePHI* scene ) : mSceneResource( scene )
{
	mSoftWorldInfo = _null;
}

PhysxScene::~PhysxScene( )
{
	EGE_RELEASE( mSoftWorldInfo );
}

_ubool PhysxScene::Initialize( )
{
	// Create soft world info
	SoftWorldInfoPHIRef world_info = gDynamicPHI->CreateSoftWorldInfo( mSceneResource );
	if ( world_info.IsNull( ) )
		return _false;

	mSoftWorldInfo = new PhysxSoftWorldInfo( world_info );

	return _true;
}

_void PhysxScene::Tick( _dword limited_elapse, _dword elapse )
{
	mSoftWorldInfo->Tick( limited_elapse, elapse );

	gDynamicPHI->UpdateScene( mSceneResource, elapse );
}

IPhysxSoftWorldInfoRef PhysxScene::GetSoftWorldInfo( )
{
	return mSoftWorldInfo;
}

_void PhysxScene::Render( IPhysxRenderer* renderer )
{
	if ( renderer == _null )
		return;

	renderer->Begin( );
	{
		gDynamicPHI->DrawScene( mSceneResource, renderer );
	}
	renderer->End( );
}

_void PhysxScene::AddBody( IPhysxBody* body )
{
	EGE_ASSERT( body != _null );

	gDynamicPHI->AddBody( mSceneResource, body->GetBodyRes( ) );

	mPhysxBodies.Append( body );
}

_void PhysxScene::RemoveBody( IPhysxBody* body )
{
	gDynamicPHI->RemoveBody( mSceneResource, body->GetBodyRes( ) );

	mPhysxBodies.Remove( body );
}