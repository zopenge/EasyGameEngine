//! @file     EGE_StorageEntry.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

//! Check whether has resource in PE archive or asset module.
DEFINE_IMPORT_FUNC(EGE::_boolean, HasResourceInPEArchive, (EGE::WStringPtr filename))

//! Get the current storage working archive.
DEFINE_IMPORT_FUNC(EGE::IArchive*, GetStorageWorkingArchive, ())

//! Get the storage module.
DEFINE_IMPORT_FUNC(EGE::IStorageModule*, GetStorageModule, ())

//!	Create the storage module.
DEFINE_IMPORT_FUNC(EGE::_boolean, CreateStorageModule, (EGE::WStringPtr working_dir))