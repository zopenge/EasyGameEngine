//! @file     EasyDrv.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// EasyDrv
//----------------------------------------------------------------------------

class EasyDrv : public INTERFACE_OBJECT_IMPL( IDynamicXSHI )
{
private:

public:
	EasyDrv( );
	virtual ~EasyDrv( );

public:
	// The XSHI methods are defined as virtual functions.
	#define DEFINE_XSHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Script/XSHIMethods.h"
	#undef DEFINE_XSHIMETHOD
};

}