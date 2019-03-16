//! @file     script_callfunc.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
//----------------------------------------------------------------------------
// _scriptCallFunc
//----------------------------------------------------------------------------

class _scriptCallFunc
{
private:
	//!	Call native function.
	//!	@param		vm_registers	The virtual machine registers.
	//!	@param		func_info		The native function info.
	//!	@param		object			The object.
	//!	@param		args			The arguments.
	//!	@return		The return value.
	static _qword CallNativeFunc( ScriptVMRegisters& vm_registers, const ScriptNativeFuncInfo& func_info, _void* object, _dword* args );

public:
	//!	Call function.
	//!	@param		vm_registers	The virtual machine registers.
	//!	@param		decl_info		The function declaration.
	//!	@param		func_info		The native function info.
	//!	@return		The size of stack should be popped in bytes.
	static _dword CallFunction( ScriptVMRegisters& vm_registers, const ScriptFuncDeclInfo* decl_info, const ScriptNativeFuncInfo& func_info );
	//!	Call function.
	//!	@param		vm_registers	The virtual machine registers.
	//!	@param		decl_info		The function declaration.
	//!	@param		func_info		The native function info.
	//!	@param		object_ptr		The object pointer.
	//!	@return		The size of stack should be popped in bytes.
	static _dword CallFunction( ScriptVMRegisters& vm_registers, const ScriptFuncDeclInfo* decl_info, const ScriptNativeFuncInfo& func_info, _void* object_ptr );
};

}