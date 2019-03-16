//! @file     EGE_ScriptEntry.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

//! Get the script resource manager.
DEFINE_IMPORT_FUNC(EGE::IScriptResourceManager*, GetScriptResourceManager, ())
//! Get the script module.
DEFINE_IMPORT_FUNC(EGE::IScriptModule*, GetScriptModule, ())

//!	Create the script module.
//!	@param		type	The script type.
DEFINE_IMPORT_FUNC(EGE::_boolean, CreateScriptModule, (EGE::_SCRIPT type))