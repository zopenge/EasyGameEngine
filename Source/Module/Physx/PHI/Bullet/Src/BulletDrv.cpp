//! @file     BulletDrv.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

#if (_PHYSX_USE_BULLET_ == 1)

//----------------------------------------------------------------------------
// BulletDrv Implementation
//----------------------------------------------------------------------------

BulletDrv::BulletDrv( )
{
}

BulletDrv::~BulletDrv( )
{
}

void* BulletDrv::OnAllocFunc( size_t size )
{
	return Memory::GetInstance( ).Alloc( size, _null, 0 );
}

void BulletDrv::OnFreeFunc( void *memblock )
{
	Memory::GetInstance( ).Free( memblock, _null, 0 );
}

bool BulletDrv::OnContactAddedCallback( btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1 )
{
	return _true;
}

bool BulletDrv::OnContactDestroyedCallback( void* userPersistentData )
{
	return _true;
}

bool BulletDrv::OnContactProcessedCallback( btManifoldPoint& cp, void* body0, void* body1 )
{
	return _true;
}

_ubool BulletDrv::Initialize( )
{
	// Set the bullet SDK memory operation functions
	::btAlignedAllocSetCustom( OnAllocFunc, OnFreeFunc );

	// Hook contact global callback functions
	gContactAddedCallback		= OnContactAddedCallback;
	gContactDestroyedCallback	= OnContactDestroyedCallback;
	gContactProcessedCallback	= OnContactProcessedCallback;

	// Show the bullet version
	ALOG_TRACE_1( "Using Bullet SDK: v%d", ::btGetVersion( ) );

	return _true;
}

#endif