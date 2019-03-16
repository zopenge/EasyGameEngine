//! @file     EGE_Physx.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

namespace EGE
{

// Physx Renderer Interface
REF_OBJECT_DECL(IPhysxRenderer);

// Physx Interface
REF_OBJECT_DECL(IDynamicPHI);
REF_OBJECT_DECL(IPhysxSoftWorldInfo);
REF_OBJECT_DECL(IPhysxShape);
REF_OBJECT_DECL(IPhysxChainShape);
REF_OBJECT_DECL(IPhysxCircleShape);
REF_OBJECT_DECL(IPhysxEdgeShape);
REF_OBJECT_DECL(IPhysxPolygonShape);
REF_OBJECT_DECL(IPhysxPlaneShape);
REF_OBJECT_DECL(IPhysxBoxShape);
REF_OBJECT_DECL(IPhysxCylinderShape);
REF_OBJECT_DECL(IPhysxCapsuleShape);
REF_OBJECT_DECL(IPhysxConeShape);
REF_OBJECT_DECL(IPhysxSphereShape);
REF_OBJECT_DECL(IPhysxMultiSphereShape);
REF_OBJECT_DECL(IPhysxConvexHullShape);
REF_OBJECT_DECL(IPhysxConvexTriangleMeshShape);
REF_OBJECT_DECL(IPhysxHeightFieldTerrainShape);
REF_OBJECT_DECL(IPhysxCompoundShape);
REF_OBJECT_DECL(IPhysxAction);
REF_OBJECT_DECL(IPhysxCharacterControllerAction);
REF_OBJECT_DECL(IPhysxBody);
REF_OBJECT_DECL(IPhysxSoftBody);
REF_OBJECT_DECL(IPhysxRigidBody);
REF_OBJECT_DECL(IPhysxScene);
REF_OBJECT_DECL(IPhysxResourceManager);
REF_OBJECT_DECL(IPhysxModule);

}

// Physx global files
#include "Interface/Module/Physx/PhysxGlobals.h"

// Physx-Renderer Interface Files
#include "Interface/Module/Physx/IPhysxRenderer.h"

// Module-Physx Interface Files
#include "Interface/Module/Physx/PHIResource.h"
#include "Interface/Module/Physx/IPhysxWorldInfo.h"
#include "Interface/Module/Physx/IPhysxShape.h"
#include "Interface/Module/Physx/IPhysxBody.h"
#include "Interface/Module/Physx/IPhysxScene.h"
#include "Interface/Module/Physx/IPhysxResourceManager.h"
#include "Interface/Module/Physx/IPhysxModule.h"
#include "Interface/Module/Entries/EGE_PhysxEntry.h"