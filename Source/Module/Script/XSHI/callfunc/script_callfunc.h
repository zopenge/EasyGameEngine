//! @file     script_callfunc.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
//----------------------------------------------------------------------------
// ScriptCallFunc
//----------------------------------------------------------------------------

class ScriptCallFunc
{
private:
	//!	Call native function.
	//!	@param		vm				The virtual machine.
	//!	@param		function_info	The native function info.
	//!	@param		object			The object.
	//!	@param		args			The arguments.
	//!	@return		The return value.
	static _qword CallNativeFunc( VMXSHI* vm, const NativeFunctionInfoXSHI& function_info, _void* object, _dword* args );

public:
	//!	Call function.
	//!	@param		vm_registers	The virtual machine registers.
	//!	@param		function_info	The native function info.
	//!	@return		The size of stack should be popped in bytes.
	static _dword CallFunction( VMRegisters& vm_registers, const NativeFunctionInfoXSHI& function_info );
	//!	Call function.
	//!	@param		vm				The virtual machine.
	//!	@param		function_info	The native function info.
	//!	@param		object_ptr		The object pointer.
	//!	@return		The size of stack should be popped in bytes.
	static _dword CallFunction( VMXSHI* vm, const NativeFunctionInfoXSHI& function_info, _void* object_ptr );
	//!	Call function.
	//!	@param		vm				The virtual machine.
	//!	@param		function		The native function.
	//!	@param		object_ptr		The object pointer.
	//!	@return		The size of stack should be popped in bytes.
	static _dword CallFunction( VMXSHI* vm, FunctionXSHI* function, _void* object_ptr );
};

}