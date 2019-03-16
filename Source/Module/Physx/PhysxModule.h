//! @file     PhysxModule.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PhysxModule
//----------------------------------------------------------------------------

class PhysxModule : public INTERFACE_MODULE_IMPL( IPhysxModule )
{
private:
	typedef INTERFACE_MODULE_IMPL( IPhysxModule ) BaseClass;

private:
	//!	The dynamic PHI
	IDynamicPHIPassRef		mDynamicPHI;

	//!	The physx resource manager
	PhysxResourceManager*	mPhysxResourceManager;

private:
	//!	Create dynamic PHI.
	_ubool CreateDynamicPHI( );

	//!	Create resource manager.
	_ubool CreateResourceManager( );

public:
	PhysxModule( );
	virtual ~PhysxModule( );

public:
	//!	Initialize.
	_ubool Initialize( );
	//!	Finalize.
	_void Finalize( );

// IObject Interface
public:
	virtual _void	Tick( _dword limited_elapse, _dword elapse ) override;

// IModule Interface
public:
	virtual _void	HandleEvent( EventBase& event ) override;

// IPhysxModule Interface
public:
};

}