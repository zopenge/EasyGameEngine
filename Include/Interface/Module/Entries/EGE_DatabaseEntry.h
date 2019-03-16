//! @file     EGE_DatabaseEntry.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

//! Get the database module.
DEFINE_IMPORT_FUNC(EGE::IDatabaseModule*, GetDatabaseModule, ())

//!	Create the database module.
DEFINE_IMPORT_FUNC(EGE::_boolean, CreateDatabaseModule, ())