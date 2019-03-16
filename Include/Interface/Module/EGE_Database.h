//! @file     EGE_Database.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

namespace EGE
{

// Database Interface
REF_OBJECT_DECL(IDatabaseRecord);
REF_OBJECT_DECL(IDatabaseConnection);
REF_OBJECT_DECL(IDatabaseModule);

}

// Module-Database Interface Files
#include "Interface/Module/Database/IDatabaseRecord.h"
#include "Interface/Module/Database/IDatabaseConnection.h"
#include "Interface/Module/Database/IDatabaseModule.h"
#include "Interface/Module/Entries/EGE_DatabaseEntry.h"