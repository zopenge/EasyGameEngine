//! @file     XSHIResource.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Common XSHI definitions
//----------------------------------------------------------------------------

//!	The function call type
enum _XSCRIPT_CALL_TYPE
{
	_XCT_CDECL,				//! CDECL
	_XCT_STDCALL,			//! StdCall
	_XCT_THISCALL,			//! ThisCall
	_XCT_CDECL_OBJ_LAST,	//!	The last parameter is object pointer 
	_XCT_CDECL_OBJ_FIRST,	//!	The first parameter is object pointer 
	_XCT_GENERIC,			//!	The generic function
};

//!	The internal call conversion
enum _XSCRIPT_INTERNAL_CALL_CONV
{
	_XICC_GENERIC_FUNC,
	_XICC_GENERIC_METHOD,
	_XICC_CDECL,
	_XICC_STDCALL,
	_XICC_WITH_OBJECT_BEGIN,
		_XICC_THISCALL,
		_XICC_VIRTUAL_THISCALL,
		_XICC_CDECL_OBJLAST,
		_XICC_CDECL_OBJFIRST,
	_XICC_WITH_OBJECT_END,
};

//!	The class behaviour
enum _XSCRIPT_BEHAVIOUR
{
	_XB_CONSTRUCTOR,	//! Constructor
	_XB_DESTRUCTOR,		//! Destructor
	_XB_MAXNUMBER,		//!	The max behaviours number
};

//!	The VM return status
enum _XSCRIPT_VM_STATUS
{
	_XVMS_NO_ERROR,
	_XVMS_FATAL_ERROR,
	_XVMS_PARSE_SCRIPT_ERROR,
	_XVMS_RUNTIME_ERROR,
};

//!	The script data type ID
enum _XSCRIPT_DATA_TYPE
{
	_XDT_BOOLEAN,
	_XDT_NUMBER,
	_XDT_STRING,
};

//!	The (XSRT, XScript Resource Type)
enum _XSCRIPT_RESOURCE_TYPE
{
	_XSRT_NONE,

	_XSRT_CLASS,
	_XSRT_FUNCTION,
	_XSRT_GENERIC,
	_XSRT_VM,
};

//----------------------------------------------------------------------------
// The XSHI resource types
//----------------------------------------------------------------------------

#define ENUM_XSHI_RESOURCE_TYPES(EnumerationMacro)			\
	EnumerationMacro(Class, _XSRT_CLASS, _XSRT_NONE)		\
	EnumerationMacro(Function, _XSRT_FUNCTION, _XSRT_NONE)	\
	EnumerationMacro(Generic, _XSRT_GENERIC, _XSRT_NONE)	\
	EnumerationMacro(VM, _XSRT_VM, _XSRT_NONE)	

template< _XSCRIPT_RESOURCE_TYPE ResourceType >
class TDynamicXSHIResource : public TObject< IObject >
{
protected:
	TDynamicXSHIResource( ) { }
	virtual ~TDynamicXSHIResource( ) { }
};
#define DEFINE_DYNAMICXSHI_REFERENCE_TYPE(Type, ResourceType, ParentResourceType)								\
template<> class TDynamicXSHIResource< ResourceType > : public TDynamicXSHIResource< ParentResourceType > {};	\
typedef TDynamicXSHIResource< ResourceType > Type##XSHI;														\
typedef RefPtr< Type##XSHI > Type##XSHIRef;																		\
typedef PassRefPtr< Type##XSHI > Type##XSHIPassRef;
ENUM_XSHI_RESOURCE_TYPES(DEFINE_DYNAMICXSHI_REFERENCE_TYPE)
#undef DEFINE_DYNAMICXSHI_REFERENCE_TYPE

//----------------------------------------------------------------------------
// Function definitions
//----------------------------------------------------------------------------

//!	The command function declaration
typedef _void (*FUNCTION_t)( );
//!	The generic function declaration
typedef _void (*GENFUNC_t)( GenericXSHI* );

//!	The constructor invoking wrapper
template< typename Type >
_void constructor( ) { new Type( ); }
//!	The destructor invoking wrapper
template< typename Type >
_void destructor( Type* object ) { delete object; }

//!	The function pointer without return value and parameters
#define EGE_FUNCTION( f, call_type )			FunctionPtr(f, call_type)
//!	The function pointer with return value and parameters
#define EGE_FUNCTION_PR( f, p, r, call_type )	FunctionPtr((void (*)())(static_cast<r (*)p>(f)), call_type)

//!	The method pointer without return value and parameters
#define EGE_METHOD( c, m )			MethodPtr<sizeof(void (c::*)())>::Convert((void (c::*)())(&c::m))
//!	The method pointer with return value and parameters
#define EGE_METHOD_PR( c, m, p, r ) MethodPtr<sizeof(void (c::*)())>::Convert(static_cast<r (c::*)p)>(&c::m))

//!	The constructor function
#define EGE_CONSTRUCTOR( t, call_type )	EGE_FUNCTION( constructor<t>, call_type )
//!	The destructor function
#define EGE_DESTRUCTOR( t, call_type )	EGE_FUNCTION( destructor<t>, call_type )

//!	The dummy unknown class
class UnknownClass;
typedef _void (UnknownClass::*METHOD_t)();

//!	The function pointer
struct FuncPtrXSHI
{
	//!	The function type
	enum _TYPE
	{
		_TYPE_GENERIC	= 1,
		_TYPE_GLOBAL	= 2,
		_TYPE_METHOD	= 3,
	};

	//!	The function type, @see _TYPE
	_word	type;
	//! The function call type, @see _XSCRIPT_CALL_TYPE
	_word	call_type;

	//! The largest known method point is 20 bytes (MSVC 64bit), but with 8byte alignment this becomes 24 bytes. 
	enum { _MAX_METHOD_POINT_SIZE = 24 };

	//!	The function pointer
	union
	{
		char dummy[ _MAX_METHOD_POINT_SIZE ]; 
		struct {METHOD_t   mthd; char dummy[_MAX_METHOD_POINT_SIZE - sizeof(METHOD_t)];} m;
		struct {FUNCTION_t func; char dummy[_MAX_METHOD_POINT_SIZE - sizeof(FUNCTION_t)];} f;
	} ptr;
};

//! Template function to capture all global functions
template< class T >
inline FuncPtrXSHI FunctionPtr( T func, _XSCRIPT_CALL_TYPE call_type )
{
	FuncPtrXSHI p;

	// Mark this as a global function
	p.type		= FuncPtrXSHI::_TYPE_GLOBAL;
	p.call_type = call_type;

	// Casting to PWORD to support constant 0 without compiler warnings
	p.ptr.f.func = (FUNCTION_t)(_uintptr_t) func;

	return p;
}

//! Specialization for functions using the generic calling convention
template<>
inline FuncPtrXSHI FunctionPtr< GENFUNC_t >( GENFUNC_t func, _XSCRIPT_CALL_TYPE call_type )
{
	FuncPtrXSHI p;

	// Mark this as a generic function
	p.type		= FuncPtrXSHI::_TYPE_GENERIC;
	p.call_type = call_type;

	// Casting the function pointer
	p.ptr.f.func = (FUNCTION_t) func;

	return p;
}

//! Declare a dummy class so that we can determine the size of a simple method pointer
class SimpleDummyClass {};
typedef _void (SimpleDummyClass::*SIMPLE_METHOD_t)( );

//!	The method size in bytes
const _dword SINGLE_PTR_SIZE = sizeof( SIMPLE_METHOD_t );

//! Define a method template
template< _dword N >
struct MethodPtr
{
	template< class M >
	static FuncPtrXSHI Convert( M method )
	{
		// This version of the function should never be executed, nor compiled,
		// as it would mean that the size of the method pointer cannot be determined.
		EGE_ASSERT( _false );

		return FuncPtrXSHI( );
	}
};

//!	Member function ( 4 bytes ) template specialization
template <>
struct MethodPtr< SINGLE_PTR_SIZE >
{
	template< class M >
	static FuncPtrXSHI Convert( M method )
	{
		FuncPtrXSHI p;

		// Mark this as a class method
		p.type		= FuncPtrXSHI::_TYPE_METHOD;
		p.call_type = _XCT_THISCALL;

		// Copy the method
		Platform::MemCpy( &p.ptr, &method, SINGLE_PTR_SIZE );

		return p;
	}
};

//!	Member function ( 8 bytes ) template specialization
template <>
struct MethodPtr< SINGLE_PTR_SIZE + 1 * sizeof( _dword ) >
{
	template <class M>
	static FuncPtrXSHI Convert( M method )
	{
		FuncPtrXSHI p;

		// Mark this as a class method
		p.type		= FuncPtrXSHI::_TYPE_METHOD;
		p.call_type = _XCT_THISCALL;

		// Copy the method
		Platform::MemCpy( &p.ptr, &method, SINGLE_PTR_SIZE + 1 * sizeof( _dword ) );

		return p;
	}
};

//!	Member function ( 12 bytes ) template specialization
template <>
struct MethodPtr< SINGLE_PTR_SIZE + 2 * sizeof( _dword ) >
{
	template <class M>
	static FuncPtrXSHI Convert( M method )
	{
		FuncPtrXSHI p;

		// Mark this as a class method
		p.type		= FuncPtrXSHI::_TYPE_METHOD;
		p.call_type = _XCT_THISCALL;

		// Copy the method
		Platform::MemCpy( &p.ptr, &method, SINGLE_PTR_SIZE + 2 * sizeof( _dword ) );

		return p;
	}
};

//!	Member function ( 16 bytes ) template specialization
template <>
struct MethodPtr< SINGLE_PTR_SIZE + 3 * sizeof( _dword ) >
{
	template <class M>
	static FuncPtrXSHI Convert( M method )
	{
		FuncPtrXSHI p;

		// Mark this as a class method
		p.type		= FuncPtrXSHI::_TYPE_METHOD;
		p.call_type = _XCT_THISCALL;

		// Copy the method
		Platform::MemCpy( &p.ptr, &method, SINGLE_PTR_SIZE + 3 * sizeof( _dword ) );

		return p;
	}
};

//!	Member function ( 20 bytes ) template specialization
template <>
struct MethodPtr< SINGLE_PTR_SIZE + 4 * sizeof( _dword ) >
{
	template <class M>
	static FuncPtrXSHI Convert( M method )
	{
		FuncPtrXSHI p;

		// Mark this as a class method
		p.type		= FuncPtrXSHI::_TYPE_METHOD;
		p.call_type = _XCT_THISCALL;

		// Copy the method
		Platform::MemCpy( &p.ptr, &method, SINGLE_PTR_SIZE + 4 * sizeof( _dword ) );

		return p;
	}
};

//----------------------------------------------------------------------------
// The Script Structures
//----------------------------------------------------------------------------

//!	The data type definition.
struct DataTypeDefXSHI : public FlagsObject
{
	//! The data type flags
	enum _FLAG
	{
		_FLAG_REFERENCE = 1 << 0,
		_FLAG_READ_ONLY = 1 << 1,
	};

	//!	The type name
	WString	mTypeName;
	//!	The type offset in bytes
	_dword	mOffset;

	DataTypeDefXSHI( )
		: mOffset( -1 ) { }
};
typedef Array< DataTypeDefXSHI > DataTypeDefXSHIArray;

//!	The class definition.
struct ClassDefXSHI
{
	//!	The class name
	WString	mName;

	ClassDefXSHI( WStringPtr name )
		: mName( name ) { }
};

//!	The property of class definition.
struct ClassPropertyDefXSHI
{
	//!	The member data type
	DataTypeDefXSHI	mDataTypeDef;
	//!	The property/variable name
	WString			mName;
};

//!	The native function definition.
struct NativeFunctionDefXSHI
{
	//!	The function return type
	WString					mRetType;
	//!	The function name
	WString					mName;
	//!	The function parameters
	DataTypeDefXSHIArray	mParameters;
	//!	The function pointer
	FuncPtrXSHI				mFuncPointer;
};

//!	The native function info.
struct NativeFunctionInfoXSHI : public FlagsObject
{
	enum _FLAG
	{
		_FLAG_HOST_RETURN_FLOAT			= 1 << 0, //! The function return float/double value
		_FLAG_RETURN_AS_OBJECT_HANDLE	= 1 << 1, //! The function return object handle
		_FLAG_RETURN_AS_REFERENCE		= 1 << 2, //! The function return reference
	};

	//!	The base offset in bytes ( to locate the object pointer position )
	_dword						mBaseOffset;
	//!	The argument/parameters size in bytes
	_dword						mParamSize;
	//!	The function pointer
	size_t						mFuncPointer;
	//!	The return value size in bytes
	_dword						mHostReturnSize;
	//!	The internal call conversion
	_XSCRIPT_INTERNAL_CALL_CONV	mCallConv;

	NativeFunctionInfoXSHI( )
		: mBaseOffset( 0 ), mParamSize( 0 ), mFuncPointer( 0 ), mHostReturnSize( 0 ), mCallConv( _XICC_GENERIC_FUNC ) { }

	NativeFunctionInfoXSHI( const FuncPtrXSHI& func )
		: mBaseOffset( 0 ), mParamSize( 0 ), mFuncPointer( 0 ), mHostReturnSize( 0 ), mCallConv( _XICC_GENERIC_FUNC ) 
	{
		mFuncPointer = (size_t) func.ptr.f.func;

		switch ( func.call_type )
		{
			case _XCT_CDECL:			mCallConv = _XICC_CDECL; break;
			case _XCT_STDCALL:			mCallConv = _XICC_STDCALL; break;
			case _XCT_THISCALL:			mCallConv = _XICC_THISCALL; break;
			case _XCT_CDECL_OBJ_LAST:	mCallConv = _XICC_CDECL_OBJLAST; break;
			case _XCT_CDECL_OBJ_FIRST:	mCallConv = _XICC_CDECL_OBJFIRST; break;
			case _XCT_GENERIC:
				if ( func.type == FuncPtrXSHI::_TYPE_METHOD )
					mCallConv = _XICC_GENERIC_METHOD;
				else
					mCallConv = _XICC_GENERIC_FUNC;
				break;
		}
	}
};

//!	The script data definition.
struct ScriptDataDefXSHI
{
	//!	The buffer data
	const _byte*	mBufferData;
	//!	The buffer size
	_dword			mBufferSize;
	//!	The source name
	WString			mSourceName;

	ScriptDataDefXSHI( )
		: mBufferData( _null ), mBufferSize( 0 ) { }
};

//!	The virtual machine registers info.
struct VMRegisters
{
	_dword*	mProgramPointer;	//! Points to current bytecode instruction
	_dword*	mStackPointer;      //! Top of stack (grows downward)
	_qword	mValueRegister;     //! Temp register for primitives
	_void*	mObjectRegister;    //! Temp register for objects and handles

	VMRegisters( )
		: mProgramPointer( _null ), mStackPointer( _null ), mValueRegister( 0 ), mObjectRegister( _null ) { }
};

//----------------------------------------------------------------------------
// IDynamicXSHI
//----------------------------------------------------------------------------

class IDynamicXSHI : public IObject
{
public:
	// The XSHI methods are defined as virtual functions.
	#define DEFINE_XSHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames PURE;
	#include "Interface/Module/Script/XSHIMethods.h"
	#undef DEFINE_XSHIMETHOD
};

//----------------------------------------------------------------------------
// NullDynamicXSHI
//----------------------------------------------------------------------------

//! A null implementation of the dynamically bound XSHI.
class NullDynamicXSHI : public INTERFACE_OBJECT_IMPL( IDynamicXSHI )
{
public:
	// The XSHI methods are defined as virtual functions.
	#define DEFINE_XSHIMETHOD(Type,Name,ParameterTypesAndNames,NullImplementation) virtual Type Name ParameterTypesAndNames { NullImplementation }
	#include "Interface/Module/Script/XSHIMethods.h"
	#undef DEFINE_XSHIMETHOD
};

}