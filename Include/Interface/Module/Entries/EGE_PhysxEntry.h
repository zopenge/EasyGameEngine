//! @file     EGE_PhysxEntry.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

//! Get the physx module.
DEFINE_IMPORT_FUNC(EGE::IPhysxModule*, GetPhysxModule, ())
//! Get the physx shape factory.
DEFINE_IMPORT_FUNC(EGE::IPhysxResourceManager*, GetPhysxResourceManager, ())
//! Get the dynamic physx hardware information.
DEFINE_IMPORT_FUNC(EGE::IDynamicPHI*, GetDynamicPHI, ())

//!	Create the physx module.
DEFINE_IMPORT_FUNC(EGE::_boolean, CreatePhysxModule, ())