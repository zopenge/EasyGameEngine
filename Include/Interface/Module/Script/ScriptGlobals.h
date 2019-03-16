//! @file     ScriptGlobals.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// The easy script enumerations
//----------------------------------------------------------------------------

//!	@export_script_enum("ScriptType", "The script type")
enum _SCRIPT
{
	//!	@enum("UNKNOWN", "Unknown")
	_SCRIPT_UNKNOWN,
	//!	@enum("PYTHON", "Python")
	_SCRIPT_PYTHON,
	//!	@enum("JAVA_SCRIPT", "JavaScript")
	_SCRIPT_JAVA_SCRIPT,
	//!	@enum("LUA", "Lua")
	_SCRIPT_LUA,
};

//!	The script function call type
enum _SCRIPT_FUNC_CALL
{
	_SCRIPT_FUNC_CALL_UNKNOWN,	//!	Unknown call type

	_SCRIPT_FUNC_CALL_CDECL,	//! CDECL
	_SCRIPT_FUNC_CALL_STDCALL,	//! StdCall
	_SCRIPT_FUNC_CALL_THISCALL,	//! ThisCall
};

//!	The ES-Function internal call conversion
enum _SCRIPT_FUNC_INTERNAL_CALL
{
	_SCRIPT_FUNC_INTERNAL_CALL_UNKNOWN,

	_SCRIPT_FUNC_INTERNAL_CALL_CDECL,
	_SCRIPT_FUNC_INTERNAL_CALL_CDECL_RETURN_IN_MEM,
	_SCRIPT_FUNC_INTERNAL_CALL_STDCALL,
	_SCRIPT_FUNC_INTERNAL_CALL_STDCALL_RETURN_IN_MEM,
	_SCRIPT_FUNC_INTERNAL_CALL_WITH_OBJECT_BEGIN,
		_SCRIPT_FUNC_INTERNAL_CALL_THISCALL,
		_SCRIPT_FUNC_INTERNAL_CALL_THISCALL_RETURN_IN_MEM,
		_SCRIPT_FUNC_INTERNAL_CALL_VIRTUAL_THISCALL,
		_SCRIPT_FUNC_INTERNAL_CALL_VIRTUAL_THISCALL_RETURN_IN_MEM,
		_SCRIPT_FUNC_INTERNAL_CALL_CDECL_OBJLAST,
		_SCRIPT_FUNC_INTERNAL_CALL_CDECL_OBJLAST_RETURN_IN_MEM,
		_SCRIPT_FUNC_INTERNAL_CALL_CDECL_OBJFIRST,
		_SCRIPT_FUNC_INTERNAL_CALL_CDECL_OBJFIRST_RETURN_IN_MEM,
	_SCRIPT_FUNC_INTERNAL_CALL_WITH_OBJECT_END,
};

//!	The script VM status
enum _SCRIPT_VM_STATUS
{
	_SCRIPT_VM_NO_ERROR,
	_SCRIPT_VM_FATAL_ERROR,
	_SCRIPT_VM_PARSE_SCRIPT_ERROR,
	_SCRIPT_VM_RUNTIME_ERROR,
};

//!	The script class behaviour
enum _SCRIPT_CLASS_BEHAVIOUR
{
	_SCRIPT_CLASS_CONSTRUCTOR,			//! Constructor
	_SCRIPT_CLASS_DESTRUCTOR,			//! Destructor

	_SCRIPT_CLASS_BEHAVIOUR_MAXNUMBER,	//!	The max behaviours number
};

//----------------------------------------------------------------------------
// Easy function definitions
//----------------------------------------------------------------------------

//!	The constructor function
#define EGE_CONSTRUCTOR( t, call_type )	FunctionPtr( ege_constructor<t>, call_type )
//!	The destructor function
#define EGE_DESTRUCTOR( t, call_type )	FunctionPtr( ege_destructor<t>, call_type )

//!	The command function declaration
typedef _void (*FUNCTION_t)( );
typedef _void (*GENFUNC_t)( IScriptGeneric* );

//!	The generic function operation macros
#define GENERIC_METHOD( x, func_pointer ) _void Generic_##x##_##func_pointer( IScriptGeneric* script_generic )
#define GENERIC_GET_OBJ( x ) ((x*) script_generic->GetObject( ))
#define GENERIC_GET_OBJECT_ARG_0( x, var_name ) x var_name = (x) (_void*) script_generic->GetArgByIndex( 0 );
#define GENERIC_GET_OBJECT_ARG_1( x, var_name ) x var_name = (x) (_void*) script_generic->GetArgByIndex( 1 );
#define GENERIC_GET_OBJECT_ARG_2( x, var_name ) x var_name = (x) (_void*) script_generic->GetArgByIndex( 2 );
#define GENERIC_GET_OBJECT_ARG_3( x, var_name ) x var_name = (x) (_void*) script_generic->GetArgByIndex( 3 );
#define GENERIC_GET_OBJECT_ARG_4( x, var_name ) x var_name = (x) (_void*) script_generic->GetArgByIndex( 4 );
#define GENERIC_GET_OBJECT_ARG_5( x, var_name ) x var_name = (x) (_void*) script_generic->GetArgByIndex( 5 );
#define GENERIC_GET_OBJECT_ARG_6( x, var_name ) x var_name = (x) (_void*) script_generic->GetArgByIndex( 6 );
#define GENERIC_GET_OBJECT_ARG_7( x, var_name ) x var_name = (x) (_void*) script_generic->GetArgByIndex( 7 );
#define GENERIC_GET_OBJECT_ARG_8( x, var_name ) x var_name = (x) (_void*) script_generic->GetArgByIndex( 8 );
#define GENERIC_GET_OBJECT_ARG_9( x, var_name ) x var_name = (x) (_void*) script_generic->GetArgByIndex( 9 );
#define GENERIC_GET_NUMBER_ARG_0( x, var_name ) x var_name = (x) script_generic->GetArgByIndex( 0 );
#define GENERIC_GET_NUMBER_ARG_1( x, var_name ) x var_name = (x) script_generic->GetArgByIndex( 1 );
#define GENERIC_GET_NUMBER_ARG_2( x, var_name ) x var_name = (x) script_generic->GetArgByIndex( 2 );
#define GENERIC_GET_NUMBER_ARG_3( x, var_name ) x var_name = (x) script_generic->GetArgByIndex( 3 );
#define GENERIC_GET_NUMBER_ARG_4( x, var_name ) x var_name = (x) script_generic->GetArgByIndex( 4 );
#define GENERIC_GET_NUMBER_ARG_5( x, var_name ) x var_name = (x) script_generic->GetArgByIndex( 5 );
#define GENERIC_GET_NUMBER_ARG_6( x, var_name ) x var_name = (x) script_generic->GetArgByIndex( 6 );
#define GENERIC_GET_NUMBER_ARG_7( x, var_name ) x var_name = (x) script_generic->GetArgByIndex( 7 );
#define GENERIC_GET_NUMBER_ARG_8( x, var_name ) x var_name = (x) script_generic->GetArgByIndex( 8 );
#define GENERIC_GET_NUMBER_ARG_9( x, var_name ) x var_name = (x) script_generic->GetArgByIndex( 9 );
#define GENERIC_GET_ASTRING_ARG_0( var_name ) AString var_name = AString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 0 ) );
#define GENERIC_GET_ASTRING_ARG_1( var_name ) AString var_name = AString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 1 ) );
#define GENERIC_GET_ASTRING_ARG_2( var_name ) AString var_name = AString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 2 ) );
#define GENERIC_GET_ASTRING_ARG_3( var_name ) AString var_name = AString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 3 ) );
#define GENERIC_GET_ASTRING_ARG_4( var_name ) AString var_name = AString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 4 ) );
#define GENERIC_GET_ASTRING_ARG_5( var_name ) AString var_name = AString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 5 ) );
#define GENERIC_GET_ASTRING_ARG_6( var_name ) AString var_name = AString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 6 ) );
#define GENERIC_GET_ASTRING_ARG_7( var_name ) AString var_name = AString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 7 ) );
#define GENERIC_GET_ASTRING_ARG_8( var_name ) AString var_name = AString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 8 ) );
#define GENERIC_GET_ASTRING_ARG_9( var_name ) AString var_name = AString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 9 ) );
#define GENERIC_GET_USTRING_ARG_0( var_name ) UString var_name = UString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 0 ) );
#define GENERIC_GET_USTRING_ARG_1( var_name ) UString var_name = UString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 1 ) );
#define GENERIC_GET_USTRING_ARG_2( var_name ) UString var_name = UString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 2 ) );
#define GENERIC_GET_USTRING_ARG_3( var_name ) UString var_name = UString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 3 ) );
#define GENERIC_GET_USTRING_ARG_4( var_name ) UString var_name = UString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 4 ) );
#define GENERIC_GET_USTRING_ARG_5( var_name ) UString var_name = UString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 5 ) );
#define GENERIC_GET_USTRING_ARG_6( var_name ) UString var_name = UString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 6 ) );
#define GENERIC_GET_USTRING_ARG_7( var_name ) UString var_name = UString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 7 ) );
#define GENERIC_GET_USTRING_ARG_8( var_name ) UString var_name = UString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 8 ) );
#define GENERIC_GET_USTRING_ARG_9( var_name ) UString var_name = UString( ).FromString( _ENCODING_UTF16, (const _charw*) script_generic->GetArgByIndex( 9 ) );
#define GENERIC_GET_WSTRING_ARG_0( var_name ) WString var_name = (const _charw*) script_generic->GetArgByIndex( 0 );
#define GENERIC_GET_WSTRING_ARG_1( var_name ) WString var_name = (const _charw*) script_generic->GetArgByIndex( 1 );
#define GENERIC_GET_WSTRING_ARG_2( var_name ) WString var_name = (const _charw*) script_generic->GetArgByIndex( 2 );
#define GENERIC_GET_WSTRING_ARG_3( var_name ) WString var_name = (const _charw*) script_generic->GetArgByIndex( 3 );
#define GENERIC_GET_WSTRING_ARG_4( var_name ) WString var_name = (const _charw*) script_generic->GetArgByIndex( 4 );
#define GENERIC_GET_WSTRING_ARG_5( var_name ) WString var_name = (const _charw*) script_generic->GetArgByIndex( 5 );
#define GENERIC_GET_WSTRING_ARG_6( var_name ) WString var_name = (const _charw*) script_generic->GetArgByIndex( 6 );
#define GENERIC_GET_WSTRING_ARG_7( var_name ) WString var_name = (const _charw*) script_generic->GetArgByIndex( 7 );
#define GENERIC_GET_WSTRING_ARG_8( var_name ) WString var_name = (const _charw*) script_generic->GetArgByIndex( 8 );
#define GENERIC_GET_WSTRING_ARG_9( var_name ) WString var_name = (const _charw*) script_generic->GetArgByIndex( 9 );
#define GENERIC_SET_RET_OBJ( v ) script_generic->SetRetValue( Variable( v ) )

//!	The function size in bytes
const _dword FUNC_PTR_SIZE      = sizeof( FUNCTION_t );
const _dword GENFUNC_PTR_SIZE	= sizeof( GENFUNC_t );

//!	The function size should be ... I guess ...
#ifdef _PLATFORM_WINDOWS_
	#define FUNC_PTR_SIZE_SHOULD_BE		4
	#define GENFUNC_PTR_SIZE_SHOULD_BE	4
#elif defined(_PLATFORM_IOS_) || defined(_PLATFORM_ANDROID_)
	#if (_PLATFORM_ARCH_64 == 1)
		#define FUNC_PTR_SIZE_SHOULD_BE		8
		#define GENFUNC_PTR_SIZE_SHOULD_BE	8
	#else
		#define FUNC_PTR_SIZE_SHOULD_BE		4
		#define GENFUNC_PTR_SIZE_SHOULD_BE	4
    #endif
#elif _PLATFORM_OSX_
	#define FUNC_PTR_SIZE_SHOULD_BE		4
	#define GENFUNC_PTR_SIZE_SHOULD_BE	4
#elif _PLATFORM_CHROME_
	#define FUNC_PTR_SIZE_SHOULD_BE		4
	#define GENFUNC_PTR_SIZE_SHOULD_BE	4
#endif

// Check function pointer size
EGE_STATIC_ASSERT( FUNC_PTR_SIZE == FUNC_PTR_SIZE_SHOULD_BE, "Global Function pointer size check" );
EGE_STATIC_ASSERT( GENFUNC_PTR_SIZE == GENFUNC_PTR_SIZE_SHOULD_BE, "Generic Function pointer size check" );

//!	The function pointer
struct ScriptFuncPtr
{
	//!	The function type
	enum _TYPE
	{
		_TYPE_GENERIC	= 1,
		_TYPE_GLOBAL	= 2,
	};

	//! The largest known method point is 20 bytes (MSVC 64bit), but with 8byte alignment this becomes 24 bytes. 
	enum { _MAX_METHOD_POINT_SIZE = 24 };

	//!	The function pointer
	union
	{
		char dummy[ _MAX_METHOD_POINT_SIZE ]; 
		struct {FUNCTION_t func; char dummy[_MAX_METHOD_POINT_SIZE - sizeof(FUNCTION_t)];} f;
	} ptr;

	//!	We must define the member here to avoid the function VTABLE access problem (MULTI_BASE_OFFSET macro)

	//!	The function type, @see _TYPE
	_word	type;
	//! The function call type, @see _SCRIPT_FUNC_CALL
	_word	call_type;
};

//! Template function to capture all global functions
template< class T >
inline ScriptFuncPtr FunctionPtr( T func, _SCRIPT_FUNC_CALL call_type )
{
	ScriptFuncPtr p;
    EGE_INIT( p );

	// Mark this as a global function
	p.type		= ScriptFuncPtr::_TYPE_GLOBAL;
	p.call_type = call_type;

	// Casting to PWORD to support constant 0 without compiler warnings
	p.ptr.f.func = (FUNCTION_t)(_uintptr_t) func;

	return p;
}

// Specialization for functions using the generic calling convention
template<>
inline ScriptFuncPtr FunctionPtr<GENFUNC_t>( GENFUNC_t func, _SCRIPT_FUNC_CALL call_type )
{
	ScriptFuncPtr p;
	EGE_INIT( p );

	// Mark this as a global function
	p.type		= ScriptFuncPtr::_TYPE_GENERIC;
	p.call_type = call_type;
	p.ptr.f.func = (FUNCTION_t)func;

	return p;
}

//----------------------------------------------------------------------------
// The script structures
//----------------------------------------------------------------------------

//!	The Script native function info.
struct ScriptNativeFuncInfo
{
	enum _RETURN_FLAG
	{
		_RET_FLAG_AS_FLOAT			= 1 << 0, //! The function return float/double value
		_RET_FLAG_AS_OBJECT_HANDLE	= 1 << 1, //! The function return object handle
	};

	//!	The return flags, @see _RETURN_FLAGS ( 0 indicates none-return value )
	FlagsObject					mRetFlags;
	//!	The base offset in bytes ( to locate the object pointer position )
	_dword						mBaseOffset;
	//!	The argument/parameters size in bytes
	_dword						mParamSize;
	//!	The function pointer
	size_t						mFuncPointer;
	//!	The return value size in bytes
	_dword						mHostReturnSize;
	//!	The internal call conversion
	_SCRIPT_FUNC_INTERNAL_CALL	mCallConv;

	ScriptNativeFuncInfo( )
	{
		mBaseOffset		= 0;
		mParamSize		= 0;
		mFuncPointer	= 0;
		mHostReturnSize	= 0;
		mCallConv		= _SCRIPT_FUNC_INTERNAL_CALL_UNKNOWN;
	}
};

//!	The script variable declaration info
struct ScriptVarDeclInfo
{
	enum _TYPE
	{
		_TYPE_UNKNOWN,
		_TYPE_VOID,
		_TYPE_INT8,
		_TYPE_INT16,
		_TYPE_INT32,
		_TYPE_UINT8,
		_TYPE_UINT16,
		_TYPE_UINT32,
		_TYPE_UBOOL,
		_TYPE_FLOAT,
		_TYPE_DOUBLE,
		_TYPE_CLASS,
		_TYPE_OBJECT,
		_TYPE_BUFFER,
		_TYPE_ASTRING_PTR,
		_TYPE_USTRING_PTR,
		_TYPE_WSTRING_PTR,
	};

	//!	The variable type ID
	_TYPE		mTypeID;
	//!	The variable type name
	AStringObj	mTypeName;

	//!	Check whether has object/class resource.
	_ubool HasObj( ) const
	{
		return (mTypeID == _TYPE_CLASS) || (mTypeID == _TYPE_OBJECT);
	}
	//!	Check whether it's string pointer type.
	_ubool IsStringPtr( ) const
	{
		return (mTypeID >= _TYPE_ASTRING_PTR) && (mTypeID <= _TYPE_WSTRING_PTR);
	}
	//!	Check whether it return in memory.
	_ubool IsReturnInMem( ) const
	{
		return mTypeID == _TYPE_CLASS;
	}

	ScriptVarDeclInfo( )
	{
		mTypeID		= _TYPE_UNKNOWN;
	}
	ScriptVarDeclInfo( _TYPE type )
	{
		mTypeID		= type;
	}
	ScriptVarDeclInfo( _TYPE type, AStringPtr name )
	{
		mTypeID		= type;
		mTypeName	= name;
	}
};
typedef Array< ScriptVarDeclInfo > ScriptVarDeclInfoArray;

//!	The script property declaration info of class 
struct ScriptPropertyDeclInfo : public ScriptVarDeclInfo
{
	//!	The offset of member variable in bytes
	_dword		mOffset;
	//!	The property name
	AStringObj	mPropertyName;

	ScriptPropertyDeclInfo( )
	{
		mOffset	= -1;
	}
};
typedef Array< ScriptPropertyDeclInfo > ScriptPropertyDeclInfoArray;

//!	The script class declaration info
struct ScriptClassDeclInfo
{
	//!	The class size in bytes
	_dword						mSize;
	//!	The class name
	AStringObj					mName;
	//!	The class desc
	AStringObj					mDesc;

	//!	The member variables declaration
	ScriptPropertyDeclInfoArray	mProperties;

	ScriptClassDeclInfo( )
	{
		mSize = 0;
	}
};

//!	The script function declaration info
struct ScriptFuncDeclInfo
{
	//!	The call type
	_SCRIPT_FUNC_CALL		mCallType;

	//!	The function name
	AStringObj				mName;
	//!	The function description
	AString					mDesc;
	//!	The function return type declaration
	ScriptVarDeclInfo		mRetDecl;
	//!	The parameters declaration info
	ScriptVarDeclInfoArray	mParametersDecls;

	ScriptFuncDeclInfo( )
	{
		mCallType = _SCRIPT_FUNC_CALL_UNKNOWN;
	}
};

//!	The script VM registers info.
struct ScriptVMRegisters
{
	_dword*	mStackPointer;		//! Top of stack (grows downward)
	_qword	mValueRegister;		//! Temp register for return value
	_byte*	mObjectRegister;	//!	Temp register for return object

	ScriptVMRegisters( )
	{
		mStackPointer	= _null;
		mValueRegister	= 0;
		mObjectRegister	= _null;
	}
};

//!	The script VM exception info.
struct ScriptVMExceptionInfo
{
	//!	The description
	WString	mDesc;

	ScriptVMExceptionInfo( )
	{

	}
	ScriptVMExceptionInfo( WStringPtr desc )
	{
		mDesc = desc;
	}
};

//----------------------------------------------------------------------------
// The easy script macros
//----------------------------------------------------------------------------

// The registered class name
#define _SCRIPT_REGISTERED_CLASS_NAME( x ) ScriptRegistered##x
// The registered class declaration
#define _SCRIPT_REGISTERED_CLASS_DECL( x ) \
	class _SCRIPT_REGISTERED_CLASS_NAME( x ) : public TObject< IScriptRegisteredClass > \
	{ \
	public: \
		_SCRIPT_REGISTERED_CLASS_NAME( x )( ) { } \
		virtual ~_SCRIPT_REGISTERED_CLASS_NAME( x )( ) { } \
		\
	public: \
		virtual _ubool Register( ) override; \
	};
// Register class's constructor and destructor
#define _SCRIPT_REGISTERED_CLASS_REGISTER_CONSTRUCTOR_AND_DESTRUCTOR( x ) { \
	_ubool ret = _true; \
	ret = GetScriptResourceManager( )->RegisterBehaviourFunction( #x, _SCRIPT_CLASS_CONSTRUCTOR, EGE_CONSTRUCTOR( x, _SCRIPT_FUNC_CALL_CDECL ) ); EGE_ASSERT( ret ); \
	ret = GetScriptResourceManager( )->RegisterBehaviourFunction( #x, _SCRIPT_CLASS_DESTRUCTOR, EGE_DESTRUCTOR( x, _SCRIPT_FUNC_CALL_CDECL ) ); EGE_ASSERT( ret ); }
// The register class register interface implementation
#define _SCRIPT_REGISTERED_CLASS_IMPL_BEGIN( x, desc ) _ubool _SCRIPT_REGISTERED_CLASS_NAME( x )::Register( ) { \
	IScriptClassRef	script_class = GetScriptResourceManager( )->RegisterClass( #x, desc, sizeof( x ) ); \
	if ( script_class.IsNull( ) ) \
		return _false; \
	_SCRIPT_REGISTERED_CLASS_REGISTER_CONSTRUCTOR_AND_DESTRUCTOR( x )
#define _SCRIPT_REGISTERED_CLASS_IMPL_BEGIN_WITHOUT_CD( x, desc ) _ubool _SCRIPT_REGISTERED_CLASS_NAME( x )::Register( ) { \
	IScriptClassRef	script_class = GetScriptResourceManager( )->RegisterClass( #x, desc, 0 ); \
	if ( script_class.IsNull( ) ) \
		return _false;
#define _SCRIPT_REGISTERED_CLASS_IMPL_END( ) return _true; }
// Register class's enumeration value
#define _SCRIPT_REGISTERED_CLASS_REGISTER_ENUM_VALUE( enum_name, value, desc ) \
	EGE_VERIFY( script_class->RegisterEnumValue( enum_name, value, desc ) )
// Register class's property
#define _SCRIPT_REGISTERED_CLASS_REGISTER_PROPERTY( x, decl, property_name, desc ) \
	EGE_VERIFY( script_class->RegisterProperty( decl, EGE_OFFSET_OF( x, property_name ), desc ) )

// Register class's method
#define _SCRIPT_REGISTERED_CLASS_REGISTER_METHOD( owner, decl, func_pointer, desc ) \
	EGE_VERIFY( script_class->RegisterFunction( decl, FunctionPtr<GENFUNC_t>( Generic_##owner##_##func_pointer, _SCRIPT_FUNC_CALL_CDECL ), desc ) )

// The registered class register
#define _SCRIPT_REGISTERED_CLASS_REGISTER( x ) \
	{ static _SCRIPT_REGISTERED_CLASS_NAME( x ) _gScriptRegistered##x_; EGE_VERIFY( _gScriptRegistered##x_.Register( ) ); }

}