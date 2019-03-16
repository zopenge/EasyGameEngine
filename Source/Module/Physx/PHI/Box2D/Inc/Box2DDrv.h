//! @file     Box2DDrv.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Box2DDrv
//----------------------------------------------------------------------------

class Box2DDrv : public INTERFACE_OBJECT_IMPL( IDynamicPHI )
{
private:

public:
	Box2DDrv( );
	virtual ~Box2DDrv( );

public:
	// The PHI methods are defined as virtual functions.
	#define DEFINE_PHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Physx/PHIMethods.h"
	#undef DEFINE_PHIMETHOD
};

}