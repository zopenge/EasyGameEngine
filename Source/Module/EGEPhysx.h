//! @file     EGEPhysx.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#ifndef _EGE_PHYSX_PCH_
#define _EGE_PHYSX_PCH_

// Windows Platform
#if defined _PLATFORM_WINDOWS_

	#include "Platform/OS/windows/Win32Headers.h"
	#include "Platform/OS/windows/Win32Macros.h"

// IOS Platform
#elif defined _PLATFORM_IOS_

// Android Platform
#elif defined _PLATFORM_ANDROID_

#endif

// Physx config file
#include "Module/Physx/PhysxConfig.h"

// This is a macro that casts a dynamically bound PHI reference to the appropriate Bullet type
#define DYNAMIC_CAST_BULLET_RESOURCE(Type,Name) \
	Bullet##Type* bt_##Name = static_cast< Bullet##Type* >( (Type##PHI*) Name )

// Get the PHI resource
#define GET_PHI_RESOURCE(var_type,var_name) \
	( (var_name) ? ( (var_type*) (var_name) )->GetResource( ) : _null )

// Bullet SDK
#if (_PHYSX_USE_BULLET_ == 1)
#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "BulletSoftBody/btSoftBody.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"
#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"
#endif

// EasyGameEngine Headers
#include "EGE_Always.h"
#include "EGE_Engine.h"
#include "EGE_Modules.h"
#include "Interface/Module/EGE_Physx.h"

// Log Files
#undef DEFINE_MODULE 
#define DEFINE_MODULE gPhysxModule->
#include "EGE_Logs.h"

// Null Classes
#include "Module/Physx/PhysxNullClasses.h"

// Global variables
extern EGE::IDynamicPHI*			gDynamicPHI;
extern EGE::IPhysxResourceManager*	gPhysxResourceManager;
extern EGE::IPhysxModule*			gPhysxModule;

// PHI Files
#if (_PHYSX_USE_BULLET_ == 1)
#include "Module/Physx/PHI/Bullet/Inc/BulletHelper.h"
#include "Module/Physx/PHI/Bullet/Inc/BulletDebugDrawer.h"
#include "Module/Physx/PHI/Bullet/Inc/BulletScene.h"
#include "Module/Physx/PHI/Bullet/Inc/BulletBody.h"
#include "Module/Physx/PHI/Bullet/Inc/BulletStridingMesh.h"
#include "Module/Physx/PHI/Bullet/Inc/BulletSoftWorldInfo.h"
#include "Module/Physx/PHI/Bullet/Inc/BulletShape.h"
#include "Module/Physx/PHI/Bullet/Inc/BulletAction.h"
#include "Module/Physx/PHI/Bullet/Inc/BulletDrv.h"
#elif (_PHYSX_USE_DUMMY_ == 1)
#include "Module/Physx/PHI/Dummy/DummyDrv.h"
#endif

// Template Files
#include "Module/Physx/Template/TPhysxShape.h"

// Physx Files
#include "Module/Physx/PhysxVersion.h"
#include "Module/Physx/PhysxWorldInfo.h"
#include "Module/Physx/PhysxShape.h"
#include "Module/Physx/PhysxResourceManager.h"
#include "Module/Physx/PhysxBody.h"
#include "Module/Physx/PhysxScene.h"
#include "Module/Physx/PhysxModule.h"

// Using namespace here to prevent some name conflict 
using namespace EGE;

// Link external libraries
#if defined _PLATFORM_WINDOWS_
	#pragma comment( lib, "libbullet.lib" )
#elif defined _PLATFORM_IOS_

#endif

#endif // _EGE_PHYSX_PCH_