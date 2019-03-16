//! @file     PPBDrv.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
//----------------------------------------------------------------------------
// PPBDrv
//----------------------------------------------------------------------------

class PPBDrv : public INTERFACE_OBJECT_IMPL( IDynamicSHI )
{
private:

public:
	PPBDrv( );
	virtual ~PPBDrv( );

public:

public:
	// The SHI methods are defined as virtual functions.
	#define DEFINE_SHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Sound/SHIMethods.h"
	#undef DEFINE_SHIMETHOD
};

}