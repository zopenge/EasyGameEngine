//! @file     EGE_NetworkEntry.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

//! Get the network resource manager.
DEFINE_IMPORT_FUNC(EGE::INetworkResourceManager*, GetNetworkResourceManager, ())
//! Get the network module.
DEFINE_IMPORT_FUNC(EGE::INetworkModule*, GetNetworkModule, ())

//!	Create the network module.
DEFINE_IMPORT_FUNC(EGE::_boolean, CreateNetworkModule, ())