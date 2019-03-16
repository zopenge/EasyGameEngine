//! @file     NvPhysxDrv.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// NvPhysxDrv Implementation
//----------------------------------------------------------------------------

NvPhysxDrv::NvPhysxDrv( )
{
}

NvPhysxDrv::~NvPhysxDrv( )
{
}

_ubool NvPhysxDrv::Initialize( )
{
	return _true;
}

StridingMeshPHIPassRef NvPhysxDrv::CreateStridingMesh( const Vector3* vertices_list, _dword vertices_number, const _word* index_list, _dword index_number )
{
	return _null;
}