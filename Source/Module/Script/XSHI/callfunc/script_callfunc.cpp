//! @file     script_callfunc.cpp
//! @author   LiCode
//! @version  1.0.0.613
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

//!	Save the return object in registers.
static _void SaveReturnObject( _qword ret, const NativeFunctionInfoXSHI& function_info, VMRegisters& vm_registers )
{
#if defined(AS_BIG_ENDIAN) && AS_PTR_SIZE == 1
	// Since we're treating the system function as if it is returning a QWORD we are
	// actually receiving the value in the high DWORD of retQW.
	ret >>= 32;
#endif

	// Update the object register
	vm_registers.mObjectRegister = (void*)(size_t)ret;

	// Auto add referenced counter, do we really need this ?!
	//if ( sysFunc->returnAutoHandle && context->regs.objectRegister )
	//	engine->CallObjectMethod(context->regs.objectRegister, descr->returnType.GetObjectType()->beh.addref);
}

//!	Save the return value in registers.
static _void SaveReturnValue( _qword ret, const NativeFunctionInfoXSHI& function_info, VMRegisters& vm_registers )
{
	_dword return_size = function_info.mHostReturnSize;

	// 32 bits
	if ( return_size <= 4 )
	{
#if defined(AS_BIG_ENDIAN)
		// Since we're treating the system function as if it is returning a QWORD we are
		// actually receiving the value in the high DWORD of retQW.
		retQW >>= 32;

		// Due to endian issues we need to handle return values that are
		// less than a DWORD (32 bits) in size specially
		if ( function_info.HasFlags( NativeFunctionInfoXSHI::_FLAG_RETURN_AS_REFERENCE ) )
			return_size = 4;

		switch( return_size )
		{
			// 8 bits
			case 1:
			{
				_byte* val	= (_byte*)&vm_registers.mValueRegister;
				val[0]		= (_byte)ret;
				val[1]		= 0;
				val[2]		= 0;
				val[3]		= 0;
				val[4]		= 0;
				val[5]		= 0;
				val[6]		= 0;
				val[7]		= 0;
			}
			break;
	
			// 16 bits
			case 2:
			{
				_word* val	= (_word*)&vm_registers.mValueRegister;
				val[0]		= (_word)ret;
				val[1]		= 0;
				val[2]		= 0;
				val[3]		= 0;
			}
			break;

			// 32 bits
			default:
			{
				_dword* val = (_dword*)&vm_registers.mValueRegister;
				val[0]		= (_dword)ret;
				val[1]		= 0;
			}
			break;
		}
#else
		*(_dword*)&vm_registers.mValueRegister = (_dword)ret;
#endif
	}
	// 64 bits
	else
	{
		vm_registers.mValueRegister = ret;
	}
}

//!	Auto release parameters referenced counter.
static _void AutoReleaseParameters( _qword ret, const NativeFunctionInfoXSHI& function_info, VMRegisters& vm_registers )
{
	// .... Need to do ?!
//
//	// Release autohandles in the arguments
//	if ( sysFunc->hasAutoHandles )
//	{
//		args = context->regs.stackPointer;
//		if ( callConv >= ICC_THISCALL && !objectPointer )
//			args += AS_PTR_SIZE;
//
//		int spos = 0;
//		for( asUINT n = 0; n < descr->parameterTypes.GetLength(); n++ )
//		{
//			if ( sysFunc->paramAutoHandles[n] && *(size_t*)&args[spos] != 0 )
//			{
//				// Call the release method on the type
//				engine->CallObjectMethod((void*)*(size_t*)&args[spos], descr->parameterTypes[n].GetObjectType()->beh.release);
//				*(size_t*)&args[spos] = 0;
//			}
//
//			if ( descr->parameterTypes[n].IsObject() && !descr->parameterTypes[n].IsObjectHandle() && !descr->parameterTypes[n].IsReference() )
//				spos += AS_PTR_SIZE;
//			else
//				spos += descr->parameterTypes[n].GetSizeOnStackDWords();
//		}
//	}
//
}

//----------------------------------------------------------------------------
// ScriptCallFunc Implementation
//----------------------------------------------------------------------------

_dword ScriptCallFunc::CallFunction( VMRegisters& vm_registers, const NativeFunctionInfoXSHI& function_info )
{
	// Useful temporary variables for calling function
	_qword  ret         = 0;
	_dword* args		= vm_registers.mStackPointer;
	_void*	object      = _null;
	_dword	pop_size    = function_info.mParamSize;

	// Call native function
	ret = CallNativeFunc( _null, function_info, object, args );

	// If it returns object handle then save it to registers
	if ( function_info.HasFlags( NativeFunctionInfoXSHI::_FLAG_RETURN_AS_OBJECT_HANDLE ) )
	{
		SaveReturnObject( ret, function_info, vm_registers );
	}
	// Save the value to registers
	else
	{
		SaveReturnValue( ret, function_info, vm_registers );
	}

	return pop_size;
}

_dword ScriptCallFunc::CallFunction( VMXSHI* vm, const NativeFunctionInfoXSHI& function_info, _void* object_ptr )
{
	// Get the function call conversion
	_XSCRIPT_INTERNAL_CALL_CONV call_conv = function_info.mCallConv;

	// Call generic function
	if ( call_conv == _XICC_GENERIC_FUNC || call_conv == _XICC_GENERIC_METHOD )
		return gDynamicXSHI->CallGeneric( vm, function_info, object_ptr );

	// Get the VM register info
	VMRegisters& vm_registers = gDynamicXSHI->GetVMRegisters( vm );

	// Useful temporary variables for calling function
	_qword  ret         = 0;
	_dword* args		= vm_registers.mStackPointer;
	_void*	object      = _null;
	_dword	pop_size    = function_info.mParamSize;

	// Prepare to call function with object
	if ( call_conv >= _XICC_WITH_OBJECT_BEGIN && call_conv <= _XICC_WITH_OBJECT_END )
		PrepareCallFuncWithObject( function_info.mBaseOffset, args, object, pop_size, object_ptr );

	// Call native function
	gDynamicXSHI->BeginCallNativeFunc( vm );
	{
		ret = CallNativeFunc( vm, function_info, object, args );
	}
	gDynamicXSHI->EndCallNativeFunc( vm );

	// If it returns object handle then save it to registers
	if ( function_info.HasFlags( NativeFunctionInfoXSHI::_FLAG_RETURN_AS_OBJECT_HANDLE ) )
	{
		SaveReturnObject( ret, function_info, vm_registers );
	}
	// Save the value to registers
	else
	{
		SaveReturnValue( ret, function_info, vm_registers );
	}

	// Auto release parameters
	AutoReleaseParameters( ret, function_info, vm_registers );

	return pop_size;
}

_dword ScriptCallFunc::CallFunction( VMXSHI* vm, FunctionXSHI* function, _void* object_ptr )
{
	// Get the function info
	const NativeFunctionInfoXSHI& function_info = gDynamicXSHI->GetFunctionInfo( function );

	// Call it
	return CallFunction( vm, function_info, object_ptr );
}