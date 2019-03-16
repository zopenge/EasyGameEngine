//! @file     BulletAction.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

#if (_PHYSX_USE_BULLET_ == 1)

//----------------------------------------------------------------------------
// BulletDrv-Action Implementation
//----------------------------------------------------------------------------

ActionPHIPassRef BulletDrv::CreateKinematicCharacterController( const Matrix4& transform, ShapePHI* shape, _float step_height, _PHYSX_UP_AXIS_TYPE up_axis )
{
	if ( shape == _null )
		return _null;

	//// Create ghost object
	//btPairCachingGhostObject* ghost_object = new btPairCachingGhostObject( );  
	//ghost_object->setWorldTransform( BulletHelper::Mat4x4ToBTTransform( transform ) );  
	//ghost_object->setCollisionShape( BulletHelper::GetBTCollisionShape( shape ) );  
	//ghost_object->setCollisionFlags( btCollisionObject::CF_CHARACTER_OBJECT ); 

	//// Create character controller
	//btKinematicCharacterController* character_controller = new btKinematicCharacterController( ghost_object, BulletHelper::GetBTCollisionShape( shape ), step_height ); 

	////向世界中添加碰撞对象  
	//physics->m_dynamicsWorld->addCollisionObject(  
	//	m_ghostObject,  
	//	btBroadphaseProxy::CharacterFilter,   
	//	btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);  
	//physics->m_dynamicsWorld->addAction(m_character);  
	//m_ghostObject = new btPairCachingGhostObject(); 
	//return new BulletCharacterControllerAction( new btKinematicCharacterController( ) );
	return _null;
}

//----------------------------------------------------------------------------
// BulletCharacterControllerAction Implementation
//----------------------------------------------------------------------------

BulletCharacterControllerAction::BulletCharacterControllerAction( btPairCachingGhostObject* ghost_object, ShapePHI* shape, btCharacterControllerInterface* character_controller ) : BaseClass( character_controller )
{
	mBTGhostObject	= ghost_object;
	mShape			= shape;
}

BulletCharacterControllerAction::~BulletCharacterControllerAction( )
{

}

#endif