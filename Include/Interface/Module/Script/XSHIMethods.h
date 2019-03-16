//! @file     XSHIMethods.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

// DEFINE_XSHIMETHOD is used by the includer to modify the XSHI method definitions.
#ifndef DEFINE_XSHIMETHOD
	#error "The DEFINE_XSHIMETHOD marco must be defined"
	#define DEFINE_XSHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) Type Name ParameterTypesAndNames
#endif

//----------------------------------------------------------------------------
// XSHI resource management
//----------------------------------------------------------------------------

DEFINE_XSHIMETHOD(
	_ubool,
	Initialize,
	(),
	return _false;
	)
DEFINE_XSHIMETHOD(
	_void,
	Tick,
	(_dword elapse),
	;
	)

//----------------------------------------------------------------------------
// XSHI class management
//----------------------------------------------------------------------------

DEFINE_XSHIMETHOD(
	ClassXSHIPassRef,
	RegisterClass,
	(const ClassDefXSHI& def),
	return _null;
	)
DEFINE_XSHIMETHOD(
	_ubool,
	RegisterClassProperty,
	(ClassXSHI* script_class, const ClassPropertyDefXSHI& def),
	return _false;
	)
DEFINE_XSHIMETHOD(
	_ubool,
	RegisterClassBehaviour,
	(ClassXSHI* script_class, _XSCRIPT_BEHAVIOUR behaviour, const FuncPtrXSHI& func),
	return _false;
	)
DEFINE_XSHIMETHOD(
	_dword,
	GetClassNumber,
	() const,
	return 0;
	)
DEFINE_XSHIMETHOD(
	ClassXSHIRef,
	GetClassByName,
	(AStringPtr name),
	return _null;
	)
DEFINE_XSHIMETHOD(
	ClassXSHIRef,
	GetClassByName,
	(WStringPtr name),
	return _null;
	)

//----------------------------------------------------------------------------
// XSHI function management
//----------------------------------------------------------------------------

DEFINE_XSHIMETHOD(
	_ubool,
	RegisterGlobalFunction,
	(const NativeFunctionDefXSHI& def),
	return _false;
	)
DEFINE_XSHIMETHOD(
	_dword,
	GetGlobalFunctionNumber,
	() const,
	return 0;
	)
DEFINE_XSHIMETHOD(
	FunctionXSHIRef,
	GetGlobalFunctionByIndex,
	(_dword index) const,
	return _null;
	)
//!	Get the function info.
DEFINE_XSHIMETHOD(
	const NativeFunctionInfoXSHI&,
	GetFunctionInfo,
	(FunctionXSHI* function) const,
	static NativeFunctionInfoXSHI sFunctionInfoXSHI; return sFunctionInfoXSHI;
	)
	
//----------------------------------------------------------------------------
// Virtual machine management
//----------------------------------------------------------------------------

//!	Load script.
DEFINE_XSHIMETHOD(
	VMXSHIPassRef,
	LoadScript,
	(const ScriptDataDefXSHI& def),
	return _null;
	)
//!	Execute.
DEFINE_XSHIMETHOD(
	_XSCRIPT_VM_STATUS,
	ExecuteVM,
	(VMXSHI* vm),
	return _XVMS_NO_ERROR;
	)
//!	Call generic function/method.
//!	@return		The size in bytes what should be popped from the stack.
DEFINE_XSHIMETHOD(
	_dword,
	CallGeneric,
	(VMXSHI* vm, const NativeFunctionInfoXSHI& function_info, _void* object),
	return 0;
	)
//!	Get the VM register info.
DEFINE_XSHIMETHOD(
	VMRegisters&,
	GetVMRegisters,
	(VMXSHI* vm),
	static VMRegisters sVMRegisters; return sVMRegisters;
	)
//!	Set the internal exception.
DEFINE_XSHIMETHOD(
	_void,
	SetVMInternalExceptionDesc,
	(VMXSHI* vm, WStringPtr exception),
	;
	)
//!	Get the internal exception.
DEFINE_XSHIMETHOD(
	WStringPtr,
	GetVMInternalExceptionDesc,
	(VMXSHI* vm),
	return WStringPtr::cEmptyString;
	)
//!	Begin to call native function
DEFINE_XSHIMETHOD(
	_void,
	BeginCallNativeFunc,
	(VMXSHI* vm),
	;
	)
//!	End to call native function
DEFINE_XSHIMETHOD(
	_void,
	EndCallNativeFunc,
	(VMXSHI* vm),
	;
	)
