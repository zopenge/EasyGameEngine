//! @file     ALDrv.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
//----------------------------------------------------------------------------
// ALDrv
//----------------------------------------------------------------------------

class ALDrv : public INTERFACE_OBJECT_IMPL( IDynamicSHI )
{
private:
	//!	True indicates it's suspend
	_ubool		mHasSuspend;

#if (_USE_OPENAL_EXT_ == 1)
	//!	The OpenAL effect slot
	ALuint		mEffectSlot;
#endif

	//!	The OpenAL device
	ALCdevice*	mDevice;
	//!	The OpenAL context
	ALCcontext*	mContext;

private:
	//!	Output the OpenAL version
	_void OutputALVersion( ) const;

	//!	Unqueue sound buffers.
	_void SourceUnqueueBuffers( SourceSHI* source, _dword& number, ALuint resource_id[] );

public:
	ALDrv( );
	virtual ~ALDrv( );

public:
#if (_USE_OPENAL_EXT_ == 1)
	EGE_GET_ACCESSOR( ALuint, EffectSlot )
#endif

public:
	// The SHI methods are defined as virtual functions.
	#define DEFINE_SHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames override;
	#include "Interface/Module/Sound/SHIMethods.h"
	#undef DEFINE_SHIMETHOD
};

}