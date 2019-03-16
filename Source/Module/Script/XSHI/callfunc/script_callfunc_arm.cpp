//! @file     script_callfunc_arm.cpp
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// The ASM functions declaration
//----------------------------------------------------------------------------

extern "C" _qword armFunc(const _dword*, int, size_t);
extern "C" _qword armFuncR0(const _dword*, int, size_t, _dword r0);
extern "C" _qword armFuncR0R1(const _dword*, int, size_t, _dword r0, _dword r1);
extern "C" _qword armFuncObjLast(const _dword*, int, size_t, _dword obj);
extern "C" _qword armFuncR0ObjLast(const _dword*, int, size_t, _dword r0, _dword obj);

//----------------------------------------------------------------------------
// ScriptCallFunc:ARM Implementation
//----------------------------------------------------------------------------

_qword ScriptCallFunc::CallNativeFunc( VMXSHI* vm, const NativeFunctionInfoXSHI& function_info, _void* object, _dword* args )
{
//	asCScriptEngine *engine = context->engine;
//	asSSystemFunctionInterface *sysFunc = descr->sysFuncIntf;
//	int callConv = sysFunc->callConv;
//
//	asQWORD  retQW             = 0;
//	void    *func              = (void*)sysFunc->func;
//	int      paramSize         = sysFunc->paramSize;
//	_dword *vftable;
//
//	if( sysFunc->hostReturnInMemory )
//	{
//		// The return is made in memory
//		callConv++;
//	}
//
//	_dword paramBuffer[64];
//	if( sysFunc->takesObjByVal )
//	{
//		paramSize = 0;
//		int spos = 0;
//		int dpos = 1;
//		for( asUINT n = 0; n < descr->parameterTypes.GetLength(); n++ )
//		{
//            if( descr->parameterTypes[n].IsObject() && !descr->parameterTypes[n].IsObjectHandle() && !descr->parameterTypes[n].IsReference() )
//			{
//#ifdef COMPLEX_OBJS_PASSED_BY_REF
//				if( descr->parameterTypes[n].GetObjectType()->flags & COMPLEX_MASK )
//				{
//					paramBuffer[dpos++] = args[spos++];
//					paramSize++;
//				}
//				else
//#endif
//				{
//					// Copy the object's memory to the buffer
//					memcpy(&paramBuffer[dpos], *(void**)(args+spos), descr->parameterTypes[n].GetSizeInMemoryBytes());
//
//					// Delete the original memory
//					engine->CallFree(*(char**)(args+spos));
//					spos++;
//					dpos += descr->parameterTypes[n].GetSizeInMemoryDWords();
//					paramSize += descr->parameterTypes[n].GetSizeInMemoryDWords();
//				}
//			}
//			else
//			{
//				// Copy the value directly
//				paramBuffer[dpos++] = args[spos++];
//				if( descr->parameterTypes[n].GetSizeOnStackDWords() > 1 )
//					paramBuffer[dpos++] = args[spos++];
//				paramSize += descr->parameterTypes[n].GetSizeOnStackDWords();
//			}
//		}
//		// Keep a free location at the beginning
//		args = &paramBuffer[1];
//	}
//
//	context->isCallingSystemFunction = true;
//
//	switch( callConv )
//	{
//	case ICC_CDECL_RETURNINMEM:     // fall through
//	case ICC_STDCALL_RETURNINMEM:
//        retQW = armFuncR0(args, paramSize<<2, (_dword)func, (_dword) retPointer);
//        break;
//    case ICC_CDECL:     // fall through
//    case ICC_STDCALL:
//		retQW = armFunc(args, paramSize<<2, (_dword)func);
//		break;
//    case ICC_THISCALL:  // fall through
//	case ICC_CDECL_OBJFIRST:
//        retQW = armFuncR0(args, paramSize<<2, (_dword)func, (_dword) obj);
//        break;
//    case ICC_THISCALL_RETURNINMEM:
//#ifndef __GNUC__
//        retQW = armFuncR0R1(args, paramSize<<2, (_dword)func, (_dword) obj, (_dword) retPointer);
//		break;
//#endif
//    case ICC_CDECL_OBJFIRST_RETURNINMEM:
//        retQW = armFuncR0R1(args, paramSize<<2, (_dword)func, (_dword) retPointer, (_dword) obj);
//		break;
//	case ICC_VIRTUAL_THISCALL:
//		// Get virtual function table from the object pointer
//		vftable = *(_dword**)obj;
//        retQW = armFuncR0(args, paramSize<<2, vftable[_dword(func)>>2], (_dword) obj);
//        break;
//    case ICC_VIRTUAL_THISCALL_RETURNINMEM:
//		// Get virtual function table from the object pointer
//		vftable = *(_dword**)obj;
//#ifndef __GNUC__
//        retQW = armFuncR0R1(args, (paramSize+1)<<2, vftable[_dword(func)>>2], (_dword) retPointer, (_dword) obj);
//#else
//        retQW = armFuncR0R1(args, (paramSize+1)<<2, vftable[_dword(func)>>2], (_dword) obj, (_dword) retPointer);
//#endif
//		break;
//	case ICC_CDECL_OBJLAST:
//		retQW = armFuncObjLast(args, paramSize<<2, (_dword)func, (_dword) obj);
//        break;
//    case ICC_CDECL_OBJLAST_RETURNINMEM:
//		retQW = armFuncR0ObjLast(args, paramSize<<2, (_dword)func, (_dword) retPointer, (_dword) obj);
//		break;
//	default:
//		context->SetInternalException(TXT_INVALID_CALLING_CONVENTION);
//	}
//	context->isCallingSystemFunction = false;

//	return retQW;
	return 0;
}