//! @file     ScriptGeneric.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

//----------------------------------------------------------------------------
// ScriptGeneric Implementation
//----------------------------------------------------------------------------

ScriptGeneric::ScriptGeneric( )
{
	mObject = _null;
}

ScriptGeneric::~ScriptGeneric( )
{
}

_void ScriptGeneric::InitPars( const ScriptVMRegisters& vm_registers, const ScriptFuncDeclInfo& decl_info )
{
	const _byte* stack_ptr = (const _byte*) vm_registers.mStackPointer;
	EGE_ASSERT( stack_ptr != _null );

	mStringArgs.Resize( decl_info.mParametersDecls.Number( ) );
	mParameters.Resize( decl_info.mParametersDecls.Number( ) );

	for ( _dword i = 0; i < decl_info.mParametersDecls.Number( ); i ++ )
	{
		const ScriptVarDeclInfo& var_decl_info = decl_info.mParametersDecls[i];

		switch ( var_decl_info.mTypeID )
		{
			case ScriptVarDeclInfo::_TYPE_INT8:
			{
				_tiny value = *stack_ptr;
				stack_ptr += sizeof( value );

				mParameters.Append( value );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_INT16:
			{
				_short value = *(_short*) stack_ptr;
				stack_ptr += sizeof( value );

				mParameters.Append( value );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_INT32:
			{
				_int value = *(_int*) stack_ptr;
				stack_ptr += sizeof( value );

				mParameters.Append( value );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_UINT8:
			{
				_byte value = *(_byte*) stack_ptr;
				stack_ptr += sizeof( value );

				mParameters.Append( value );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_UINT16:
			{
				_word value = *(_word*) stack_ptr;
				stack_ptr += sizeof( value );

				mParameters.Append( value );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_UINT32:
			{
				_dword value = *(_dword*) stack_ptr;
				stack_ptr += sizeof( value );

				mParameters.Append( value );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_UBOOL:
			{
				_ubool value = *(_ubool*) stack_ptr;
				stack_ptr += sizeof( value );

				mParameters.Append( (_boolean)value );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_FLOAT:
			{
				_float value = *(_float*) stack_ptr;
				stack_ptr += sizeof( value );

				mParameters.Append( value );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_DOUBLE:
			{
				_double value = *(_double*) stack_ptr;
				stack_ptr += sizeof( value );

				mParameters.Append( value );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_CLASS:
			{
				size_t* value = (size_t*)stack_ptr;
				stack_ptr += sizeof( value );

				mParameters.Append( value );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_OBJECT:
			{
				// Save address of object
				size_t* value = (size_t*) stack_ptr;
				stack_ptr += sizeof( value );

				mParameters.Append( *value );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_BUFFER:
			{
				EGE_ASSERT( 0 );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_ASTRING_PTR:
			{
				AStringPtr value = *(AStringPtr*) *(size_t*) stack_ptr;
				stack_ptr += sizeof( AStringPtr* );

				mStringArgs.Append( WString( ).FromString( value ) );
				mParameters.Append( mStringArgs.GetTailElement( ).Str( ) );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_USTRING_PTR:
			{
				UStringPtr value = *(UStringPtr*) *(size_t*) stack_ptr;
				stack_ptr += sizeof( UStringPtr* );

				mStringArgs.Append( WString( ).FromString( value ) );
				mParameters.Append( mStringArgs.GetTailElement( ).Str( ) );
			}
			break;

			case ScriptVarDeclInfo::_TYPE_WSTRING_PTR:
			{
				WStringPtr value = *(WStringPtr*) *(size_t*) stack_ptr;
				stack_ptr += sizeof( WStringPtr* );

				mParameters.Append( value.Str( ) );
			}
			break;

			default:
				break;
		}
	}
}

_ubool ScriptGeneric::Invoke( ScriptVMRegisters& vm_registers, const ScriptFuncDeclInfo* decl_info, const ScriptNativeFuncInfo& func_info, _void* object )
{
	mObject = object;

	// Set arguments
	if ( decl_info != _null )
		InitPars( vm_registers, *decl_info );

	// Get the generic function pointer
	GENFUNC_t generic_func = (GENFUNC_t) func_info.mFuncPointer;
	EGE_ASSERT( generic_func != _null );

	// Invoke the generic function with self
	(*generic_func)( this );

	// If it returns object handle then save it to registers
	if ( func_info.mRetFlags.HasFlags( ScriptNativeFuncInfo::_RET_FLAG_AS_OBJECT_HANDLE ) )
	{
		vm_registers.mObjectRegister = (_byte*) (_void*) mRetValue;
	}
	// Save the value to registers
	else
	{
		vm_registers.mValueRegister = (_qword) mRetValue;
	}

	return _true;
}

_void* ScriptGeneric::GetObject( )
{
	return mObject;
}

const _void* ScriptGeneric::GetObject( ) const
{
	return mObject;
}

_void ScriptGeneric::SetRetValue( const Variable& value )
{
	mRetValue = value;
}

const Variable& ScriptGeneric::GetRetValue( ) const
{
	return mRetValue;
}

_dword ScriptGeneric::GetArgsNumber( ) const
{
	return mParameters.Number( );
}

const Variable& ScriptGeneric::GetArgByIndex( _dword index ) const
{
	return mParameters[ index ];
}