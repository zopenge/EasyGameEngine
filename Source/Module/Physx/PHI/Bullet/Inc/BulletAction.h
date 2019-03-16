//! @file     BulletAction.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

#define BULLET_ACTION_CLASS_DECL_WITH_NAME_BEGIN( name, x, res ) \
class Bullet##name##Action : public TBulletAction< x##ActionPHI, res > \
{ \
private: \
	typedef TBulletAction< x##ActionPHI, res > BaseClass; \
public: \
	Bullet##name##Action( res* action ); \
	virtual ~Bullet##name##Action( );
#define BULLET_ACTION_CLASS_DECL_END( ) \
};
#define BULLET_ACTION_CLASS_DECL_BEGIN( x, res ) BULLET_ACTION_CLASS_DECL_WITH_NAME_BEGIN( x, x, res )
#define BULLET_ACTION_CLASS_IMPL( x, res ) \
Bullet##x##Action::Bullet##x##Action( res* action ) : BaseClass( action ) \
{ \
} \
Bullet##x##Action::~Bullet##x##Action( ) \
{ \
}

//----------------------------------------------------------------------------
// TBulletAction
//----------------------------------------------------------------------------

template< typename Type, typename ActionResourceType >
class TBulletAction : public Type
{
protected:
	//!	The action resource
	ActionResourceType*	mBTAction;

protected:
	TBulletAction( ActionResourceType* action ) { EGE_ASSERT( action != _null ); mBTAction = action; }
	virtual ~TBulletAction( ) { EGE_DELETE( mBTAction ); }

public:
	//!	Get the action resource
	EGE_GETR_ACCESSOR( ActionResourceType*, BTAction )
};

//----------------------------------------------------------------------------
// BulletCharacterControllerAction
//----------------------------------------------------------------------------

BULLET_ACTION_CLASS_DECL_BEGIN( CharacterController, btCharacterControllerInterface )
private:
	btPairCachingGhostObject*	mBTGhostObject;
	ShapePHIRef					mShape;
public:
	BulletCharacterControllerAction( btPairCachingGhostObject* ghost_object, ShapePHI* shape, btCharacterControllerInterface* character_controller );
BULLET_ACTION_CLASS_DECL_END( )

}