//! @file     GLDrv.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
//----------------------------------------------------------------------------
// GLDrv
//----------------------------------------------------------------------------

class GLDrv : public INTERFACE_OBJECT_IMPL( IDynamicRHI )
{
private:
	//!	The allocator
	IStackAllocatorRef		mAllocator;

	//!	The resource manager
	IResourceManagerRHI*	mResourceManager;

	//!	The main viewport
	GLViewport*				mMainViewport;

private:
	//!	Initialize resource manager.
	_ubool InitResourceManager( );

	//!	Append render state.
	template< typename ArrayType, typename Type >
	Type* AppendRenderState( ArrayType& render_states, const Type& state );

	//!	Get the sampler state info from GL-Sampler State.
	SamplerStateInitializerRHI GetSamplerStateFromGL( const GLSamplerStateInfo& state ) const;

public:
	GLDrv( );
	virtual ~GLDrv( );

public:
	// The RHI methods are defined as virtual functions.
	#define DEFINE_RHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Graphic/RHIMethods.h"
	#undef DEFINE_RHIMETHOD
};

//----------------------------------------------------------------------------
// GLDrv Implementation
//----------------------------------------------------------------------------

}