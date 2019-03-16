//! @file     PhysxModule.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// PhysxModule Implementation
//----------------------------------------------------------------------------

PhysxModule::PhysxModule( ) : BaseClass( L"Physx", Version( PHYSX_FILEVER ) )
{
	mPhysxResourceManager	= _null;
}

PhysxModule::~PhysxModule( )
{
	Finalize( );
}

_ubool PhysxModule::CreateDynamicPHI( )
{
	// Create dynamic PHI driver
#if (_PHYSX_USE_BULLET_ == 1)
	mDynamicPHI = new BulletDrv( );
#elif (_PHYSX_USE_DUMMY_ == 1)
	mDynamicPHI = new DummyDrv( );
#else
	return _false;
#endif

	// Initialize dynamic PHI driver
	gDynamicPHI = mDynamicPHI.GetPtr( );
	return gDynamicPHI->Initialize( );
}

_ubool PhysxModule::CreateResourceManager( )
{
	WLOG_TRACE( L"Create pyhsx resource manager ..." );

	mPhysxResourceManager = new PhysxResourceManager( );
	gPhysxResourceManager = mPhysxResourceManager;

	WLOG_TRACE( L"Create pyhsx resource manager OK" );

	return _true;
}

_ubool PhysxModule::Initialize( )
{
	WLOG_TRACE( L"Create pyhsx module ..." );

	// Create PHI driver
	if ( CreateDynamicPHI( ) == _false )
		return _false;

	// Create resource manager
	if ( CreateResourceManager( ) == _false )
		return _false;

	WLOG_TRACE( L"Create pyhsx module DONE" );

	return _true;
}

_void PhysxModule::Finalize( )
{
	WLOG_TRACE( L"Release pyhsx module ..." );

	// Release resource manager
	EGE_DELETE( mPhysxResourceManager );

	// Release global resources
	mDynamicPHI.Clear( );

	WLOG_TRACE( L"Release pyhsx module DONE" );

	// Clear global modules
	gDynamicPHI				= &NullPhysx::GetInstance( ).GetDynamicPHI( );
	gPhysxResourceManager	= &NullPhysx::GetInstance( ).GetPhysxResourceManager( );
	gPhysxModule			= &NullPhysx::GetInstance( ).GetPhysxModule( );
}

_void PhysxModule::Tick( _dword limited_elapse, _dword elapse )
{
	gDynamicPHI->Tick( limited_elapse, elapse );
}

_void PhysxModule::HandleEvent( EventBase& event )
{
}