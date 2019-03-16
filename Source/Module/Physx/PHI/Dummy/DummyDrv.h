//! @file     DummyDrv.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// DummyDrv
//----------------------------------------------------------------------------

class DummyDrv : public INTERFACE_OBJECT_IMPL( IDynamicPHI )
{
private:

public:
	DummyDrv( );
	virtual ~DummyDrv( );

public:
	// The PHI methods are defined as virtual functions.
	#define DEFINE_PHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames { NullImplementation }
	#include "Interface/Module/Physx/PHIMethods.h"
	#undef DEFINE_PHIMETHOD
};

}