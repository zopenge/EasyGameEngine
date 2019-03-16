//! @file     EGE_Storage.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

namespace EGE
{

// Storage Interface
REF_OBJECT_DECL(IStorageModule);

}

// Storage global files
#include "Interface/Module/Storage/StorageGlobals.h"
#include "Interface/Module/Storage/StorageEvents.h"
using namespace EGE::StorageEvents;

// Module-Storage Interface Files
#include "Interface/Module/Storage/IStorageModule.h"
#include "Interface/Module/Entries/EGE_StorageEntry.h"