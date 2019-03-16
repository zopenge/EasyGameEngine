//! @file     RHIStatsDrv.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
//----------------------------------------------------------------------------
// RHIStatsDrv
//----------------------------------------------------------------------------

class RHIStatsDrv : public INTERFACE_OBJECT_IMPL( IDynamicRHI )
{
private:
	IDynamicRHIRef	mDynamicRHI;

	//!	The FPS timer
	FPSTimer		mFPSTimer;

	//!	The render stats
	RenderStatsRHI	mRenderStats;

private:
	//!	Get vertices number of primitive.
	static _dword GetVerticesNumber( _PRIMITIVE_TYPE type, _dword number );

public:
	RHIStatsDrv( IDynamicRHI* dynamic_rhi );
	virtual ~RHIStatsDrv( );

// IObject Interface
public:
	virtual _void	Tick( _dword limited_elapse, _dword elapse ) override;

public:
	// The RHI methods are defined as virtual functions.
	#define DEFINE_RHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Graphic/RHIMethods.h"
	#undef DEFINE_RHIMETHOD
};

}