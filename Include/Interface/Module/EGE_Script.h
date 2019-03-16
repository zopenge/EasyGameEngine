//! @file     EGE_Script.h
//! @author   LiCode
//! @version  1.0.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

namespace EGE
{

// Script Interface
REF_OBJECT_DECL(IScriptValue);
REF_OBJECT_DECL(IScriptFunction);
REF_OBJECT_DECL(IScriptClass);
REF_OBJECT_DECL(IScriptGeneric);
REF_OBJECT_DECL(IScriptRegisteredClass);
REF_OBJECT_DECL(IScriptVM);
REF_OBJECT_DECL(IScriptResourceManager);
REF_OBJECT_DECL(IScriptModule);

}

// Script global files
#include "Interface/Module/Script/ScriptConfig.h"
#include "Interface/Module/Script/ScriptGlobals.h"
#include "Interface/Module/Script/ScriptSerialization.h"

// Module-Script Interface Files
#include "Interface/Module/Script/IScriptValue.h"
#include "Interface/Module/Script/IScriptFunction.h"
#include "Interface/Module/Script/IScriptClass.h"
#include "Interface/Module/Script/IScriptGeneric.h"
#include "Interface/Module/Script/IScriptRegisteredClass.h"
#include "Interface/Module/Script/IScriptVM.h"
#include "Interface/Module/Script/IScriptResourceManager.h"
#include "Interface/Module/Script/IScriptModule.h"
#include "Interface/Module/Entries/EGE_ScriptEntry.h"

namespace EGE
{

//!	The constructor invoking wrapper
template< typename Type >
_void ege_constructor( IScriptGeneric* script_generic )
{
	EGE_ASSERT( script_generic != _null );

	script_generic->SetRetValue( Variable( new Type( ) ) );
}
//!	The destructor invoking wrapper
template< typename Type >
_void ege_destructor( IScriptGeneric* script_generic )
{
	EGE_ASSERT( script_generic != _null );

	Type* object = (Type*) script_generic->GetObject( );
	EGE_DELETE( object ); 
}

}