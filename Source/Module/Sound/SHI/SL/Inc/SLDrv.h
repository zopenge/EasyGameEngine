//! @file     SLDrv.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
//----------------------------------------------------------------------------
// SLDrv
//----------------------------------------------------------------------------

class SLDrv : public INTERFACE_OBJECT_IMPL( IDynamicSHI )
{
private:
	//!	True indicates it's suspend
	_ubool						mHasSuspend;

	//!	Sound library object
	SLObjectItf					mSLLibObject;

	//!	Sound library engine
	SLEngineItf					mSLEngine;
	//!	Sound library capabilities
	SLEngineCapabilitiesItf		mSLEngineCapabilities;
	//!	Sound library mix object
	SLObjectItf					mSLOutputMixObject;

private:
	//!	Output the OpenSL version
	_void OutputSLVersion( ) const;

public:
	SLDrv( );
	virtual ~SLDrv( );

public:
	// The SHI methods are defined as virtual functions.
	#define DEFINE_SHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Sound/SHIMethods.h"
	#undef DEFINE_SHIMETHOD
};

}