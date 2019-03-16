//! @file     script_callfunc.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// Helpful Functions Implementation
//----------------------------------------------------------------------------

static _void PrepareCallFuncWithObject( _dword base_offset, _dword*& args, _void*& object, _dword& pop_size, _void* object_ptr )
{
	if ( object_ptr )
	{
		object = object_ptr;
	}
	else
	{
		// The object pointer should be popped from the context stack
		pop_size += AS_PTR_SIZE;

		// Check for null pointer
		object = (void*)*(size_t*)(args);
		EGE_ASSERT( object != _null );

		// Add the base offset for multiple inheritance
#if defined(__GNUC__) && defined(AS_ARM)
		// On GNUC + ARM the lsb of the offset is used to indicate a virtual function
		// and the whole offset is thus shifted one bit left to keep the original
		// offset resolution
		object = (void*)(size_t(object) + (base_offset >> 1));
#else
		object = (void*)(size_t(object) + base_offset);
#endif

		// Skip the object pointer
		args += AS_PTR_SIZE;
	}
}

//----------------------------------------------------------------------------
// _scriptCallFunc Implementation
//----------------------------------------------------------------------------

_dword _scriptCallFunc::CallFunction( ScriptVMRegisters& vm_registers, const ScriptFuncDeclInfo* decl_info, const ScriptNativeFuncInfo& func_info )
{
	// The pop size in bytes when we finish call function
	_dword pop_size = func_info.mParamSize;

	// Call generic function
	ScriptGeneric script_generic;
	EGE_VERIFY( script_generic.Invoke( vm_registers, decl_info, func_info, _null ) );

	return pop_size;
}

_dword _scriptCallFunc::CallFunction( ScriptVMRegisters& vm_registers, const ScriptFuncDeclInfo* decl_info, const ScriptNativeFuncInfo& func_info, _void* object_ptr )
{
	// Get the function call conversion
	_SCRIPT_FUNC_INTERNAL_CALL call_conv = func_info.mCallConv;

	// Useful temporary variables for calling function
	_dword* args		= vm_registers.mStackPointer;
	_void*	object      = _null;
	_dword	pop_size    = func_info.mParamSize;

	// Prepare to call function with object
	if ( call_conv >= _SCRIPT_FUNC_INTERNAL_CALL_WITH_OBJECT_BEGIN && call_conv <= _SCRIPT_FUNC_INTERNAL_CALL_WITH_OBJECT_END )
		PrepareCallFuncWithObject( func_info.mBaseOffset, args, object, pop_size, object_ptr );

	// Call generic function
	ScriptGeneric script_generic;
	script_generic.Invoke( vm_registers, decl_info, func_info, object_ptr );

	return pop_size;
}