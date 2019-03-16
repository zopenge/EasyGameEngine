//! @file     EGE_GraphicEntry.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

//!	Get the graphic VR device.
DEFINE_IMPORT_FUNC(EGE::IGraphicVRDevice*, GetGraphicVRDevice, ())
//!	Get the graphic resource manager.
DEFINE_IMPORT_FUNC(EGE::IGraphicResourceManager*, GetGraphicResourceManager, ())
//! Get the graphic viewport.
DEFINE_IMPORT_FUNC(EGE::IGraphicViewport*, GetGraphicViewport, ())
//! Get the graphic module.
DEFINE_IMPORT_FUNC(EGE::IGraphicModule*, GetGraphicModule, ())
//! Get the dynamic render hardware information.
DEFINE_IMPORT_FUNC(EGE::IDynamicRHI*, GetDynamicRHI, ())
//! Get the dynamic render hardware's resource information.
DEFINE_IMPORT_FUNC(EGE::IResourceManagerRHI*, GetResourceManagerRHI, ())

//!	Create the graphic module.
//!	@param		app_handle	The application handle, support the viewbased application only.
//!	@param		size		The initial viewport size.
//!	@param		multisample	The multisample number.
DEFINE_IMPORT_FUNC(EGE::_boolean, CreateGraphicModule, (EGE::_handle app_handle, const EGE::PointU& size, EGE::_dword multisample))