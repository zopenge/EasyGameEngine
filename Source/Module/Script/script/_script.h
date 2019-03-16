//! @file     _script.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

REF_OBJECT_DECL(_scriptValue);
REF_OBJECT_DECL(_scriptFunction);
REF_OBJECT_DECL(_scriptModule);
REF_OBJECT_DECL(_scriptVM);
REF_OBJECT_DECL(_scriptSystem);

}

//!	The internal script system
extern EGE::_scriptSystem* gInternalScriptSystem;