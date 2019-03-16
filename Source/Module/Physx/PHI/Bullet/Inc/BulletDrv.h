//! @file     BulletDrv.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// BulletDrv
//----------------------------------------------------------------------------

class BulletDrv : public INTERFACE_OBJECT_IMPL( IDynamicPHI )
{
private:
	//!	The memory operation of bullet SDK.
	static void*	OnAllocFunc( size_t size );
	static void		OnFreeFunc( void *memblock );

	//!	The contact global callback functions.
	static bool		OnContactAddedCallback( btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1 );
	static bool		OnContactDestroyedCallback( void* userPersistentData );
	static bool		OnContactProcessedCallback( btManifoldPoint& cp, void* body0, void* body1 );

public:
	BulletDrv( );
	virtual ~BulletDrv( );

public:
	// The PHI methods are defined as virtual functions.
	#define DEFINE_PHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Physx/PHIMethods.h"
	#undef DEFINE_PHIMETHOD
};

}