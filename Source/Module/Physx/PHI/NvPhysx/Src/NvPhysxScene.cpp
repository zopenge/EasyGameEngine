//! @file     NvPhysxScene.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEPhysx.h"

//----------------------------------------------------------------------------
// NvPhysx-Scene Implementation
//----------------------------------------------------------------------------

ScenePHIPassRef NvPhysxDrv::CreateScene( const Vector3& gravity )
{
	return _null;
}

_void NvPhysxDrv::UpdateScene( ScenePHI* scene, _dword elapse )
{
}

_void NvPhysxDrv::DrawScene( ScenePHI* scene, IPhysxRenderer* renderer )
{

}

//----------------------------------------------------------------------------
// NvPhysxScene Implementation
//----------------------------------------------------------------------------

NvPhysxScene::NvPhysxScene( )
{
}

NvPhysxScene::~NvPhysxScene( )
{
}