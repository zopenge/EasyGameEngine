//! @file     script_callfunc_arm.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#if (EGE_SCRIPT_MAX_COMPATIBLE == 0)

//----------------------------------------------------------------------------
// The ASM functions declaration
//----------------------------------------------------------------------------

extern "C" _qword armFunc(const _dword*, int, size_t);
extern "C" _qword armFuncR0(const _dword*, int, size_t, _dword r0);
extern "C" _qword armFuncR0R1(const _dword*, int, size_t, _dword r0, _dword r1);
extern "C" _qword armFuncObjLast(const _dword*, int, size_t, _dword obj);
extern "C" _qword armFuncR0ObjLast(const _dword*, int, size_t, _dword r0, _dword obj);

//----------------------------------------------------------------------------
// _scriptCallFunc:ARM Implementation
//----------------------------------------------------------------------------

_qword _scriptCallFunc::CallNativeFunc( ScriptVMRegisters& vm_registers, const ScriptNativeFuncInfo& func_info, _void* object, _dword* args )
{    
	// The return value
	_qword ret = 0;

	// Call it
	switch ( func_info.mCallConv )
	{
		case _SCRIPT_FUNC_INTERNAL_CALL_CDECL:
		{
			ret = armFunc( args, func_info.mParamSize, (size_t) func_info.mFuncPointer );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_CDECL_RETURN_IN_MEM:
		{
			ret = armFuncR0( args, func_info.mParamSize, (size_t) func_info.mFuncPointer, (_dword) vm_registers.mObjectRegister );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_STDCALL:
		{
			ret = armFunc( args, func_info.mParamSize, (size_t) func_info.mFuncPointer );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_THISCALL:
		{
			ret = armFuncR0( args, func_info.mParamSize, (size_t) func_info.mFuncPointer, (_dword) object );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_THISCALL_RETURN_IN_MEM:
		{
			ret = armFuncR0R1( args, func_info.mParamSize, (size_t) func_info.mFuncPointer, (_dword) object, (_dword) vm_registers.mObjectRegister );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_VIRTUAL_THISCALL:
		{
			// Get virtual function table from the object pointer
			_dword* vftable = *(_dword**) object;

			ret = armFuncR0( args, func_info.mParamSize, vftable[ size_t( func_info.mFuncPointer ) >> 2 ], (_dword) object );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_VIRTUAL_THISCALL_RETURN_IN_MEM:
		{
			// Get virtual function table from the object pointer
			_dword* vftable = *(_dword**) object;
#ifndef __GNUC__
			ret = armFuncR0R1( args, (func_info.mParamSize + 1) << 2, vftable[ size_t( func_info.mFuncPointer ) >> 2 ], (_dword) vm_registers.mObjectRegister, (_dword) object );
#else
			ret = armFuncR0R1( args, (func_info.mParamSize + 1) << 2, vftable[ size_t( func_info.mFuncPointer ) >> 2 ], (_dword) object, (_dword) vm_registers.mObjectRegister );
#endif
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_CDECL_OBJLAST:
		{
			ret = armFuncObjLast( args, func_info.mParamSize, (size_t) func_info.mFuncPointer, (_dword) object );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_CDECL_OBJFIRST:
		{
			ret = armFuncR0( args, func_info.mParamSize, (size_t) func_info.mFuncPointer, (_dword) object );
		}
		break;

		default:
			EGE_ASSERT( 0 );
			break;
	}

	return ret;
}

#endif