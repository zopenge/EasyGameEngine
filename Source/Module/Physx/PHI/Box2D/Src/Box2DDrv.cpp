//! @file     Box2DDrv.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// Box2DDrv Implementation
//----------------------------------------------------------------------------

Box2DDrv::Box2DDrv( )
{
}

Box2DDrv::~Box2DDrv( )
{
}

_ubool Box2DDrv::Initialize( )
{
	// Show the box2d version
	ALOG_TRACE_3( "Using Box2D %d.%d.%d", b2_version.major, b2_version.minor, b2_version.revision );

	return _true;
}

StridingMeshPHIPassRef Box2DDrv::CreateStridingMesh( const Vector3* vertices_list, _dword vertices_number, const _word* index_list, _dword index_number )
{
	return _null;
}