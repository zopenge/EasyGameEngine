//! @file     EasyVM.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// EasyDrv-VM Implementation
//----------------------------------------------------------------------------

_XSCRIPT_VM_STATUS EasyDrv::ExecuteVM( VMXSHI* vm )
{
	return _XVMS_NO_ERROR;
}

_dword EasyDrv::CallGeneric( VMXSHI* vm, const NativeFunctionInfoXSHI& function_info, _void* object )
{
	DYNAMIC_CAST_EASYRESOURCE( VM, vm );

	return 0;
}

VMRegisters& EasyDrv::GetVMRegisters( VMXSHI* vm )
{
	DYNAMIC_CAST_EASYRESOURCE( VM, vm );

	return easy_vm->GetRegisters( );
}

_void EasyDrv::SetVMInternalExceptionDesc( VMXSHI* vm, WStringPtr exception )
{
	DYNAMIC_CAST_EASYRESOURCE( VM, vm );

	easy_vm->SetExceptionDesc( exception );
}

WStringPtr EasyDrv::GetVMInternalExceptionDesc( VMXSHI* vm )
{
	DYNAMIC_CAST_EASYRESOURCE( VM, vm );

	return easy_vm->GetExceptionDesc( );
}

_void EasyDrv::BeginCallNativeFunc( VMXSHI* vm )
{
	DYNAMIC_CAST_EASYRESOURCE( VM, vm );

	easy_vm->GetFlags( ).CombineFlags( EasyVM::_FLAG_CALLING_NATIVE_FUNC );
}

_void EasyDrv::EndCallNativeFunc( VMXSHI* vm )
{
	DYNAMIC_CAST_EASYRESOURCE( VM, vm );

	easy_vm->GetFlags( ).ClearFlags( EasyVM::_FLAG_CALLING_NATIVE_FUNC );
}

//----------------------------------------------------------------------------
// EasyVM Implementation
//----------------------------------------------------------------------------

EasyVM::EasyVM( )
{

}

EasyVM::~EasyVM( )
{

}