//! @file     Variable.h
//! @author   LiCode
//! @version  1.1.0.695
//! @date     2011/02/13
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Variable
//----------------------------------------------------------------------------

class Variable
{
public:
	static const Variable cNull;

public:
	enum _TYPE
	{
		_TYPE_STRING	= 0x00000001, // 00000001
		_TYPE_FLOAT		= 0x00000002, // 00000010
		_TYPE_INTEGER	= 0x00000004, // 00000100

		// Type Mask
		_TYPE_MASK		= 0x0000FFFF,
	};

	enum _TYPE_ID
	{
		_TYPE_ID_UNKNOWN	= 0,											// Unknown
		_TYPE_ID_SIGNED		= 0x00010000,									// Signed integer
		_TYPE_ID_BOOLEAN	= 0x00020000,									// Boolean
		_TYPE_ID_INT8		= 0x00040000 | _TYPE_INTEGER | _TYPE_ID_SIGNED,	// Signed 8-bits integer
		_TYPE_ID_INT16		= 0x00080000 | _TYPE_INTEGER | _TYPE_ID_SIGNED,	// Signed 16-bits integer
		_TYPE_ID_INT32		= 0x00100000 | _TYPE_INTEGER | _TYPE_ID_SIGNED,	// Signed 32-bits integer
		_TYPE_ID_INT64		= 0x00200000 | _TYPE_INTEGER | _TYPE_ID_SIGNED,	// Signed 64-bits integer
		_TYPE_ID_UINT8		= 0x00400000 | _TYPE_INTEGER,					// Unsigned 8-bits integer
		_TYPE_ID_UINT16		= 0x00800000 | _TYPE_INTEGER,					// Unsigned 16-bits integer
		_TYPE_ID_UINT32		= 0x01000000 | _TYPE_INTEGER,					// Unsigned 32-bits integer
		_TYPE_ID_UINT64		= 0x02000000 | _TYPE_INTEGER,					// Unsigned 64-bits integer
		_TYPE_ID_FLOAT		= 0x04000000 | _TYPE_FLOAT,						// Float
		_TYPE_ID_DOUBLE		= 0x08000000 | _TYPE_FLOAT,						// Double
		_TYPE_ID_WSTRING	= 0x10000000 | _TYPE_STRING,					// UTF16-String
		_TYPE_ID_POINTER	= 0x20000000,									// Pointer

		// Type ID Mask
		_TYPE_ID_MASK		= 0xFFFF0000,
	};

private:
	// Value
	union
	{
		struct
		{
			_large	mSignedValue;
		};

		struct
		{
			_qword	mUnsignedValue;
		};

		struct
		{
			_double mDoubleValue;
		};

		struct
		{
			_int	mSignedValues[2];
		};

		struct
		{
			_dword	mUnsignedValues[2];
		};

		struct
		{
			_float	mFloatValues[2];
		};
	};

	// Type
	union
	{
		struct
		{
			_dword	mType;
		};

		struct
		{
			_word	mLowType;
			_word	mHighType;
		};
	};

private:
	//! Convert to signed value.
	template< typename Type >
	Type ConvertToSignedValue( ) const;

	//! Convert to unsigned value.
	template< typename Type >
	Type ConvertToUnsignedValue( ) const;

public:
	Variable( );
	Variable( _boolean value );
	Variable( _ubool value );
	Variable( _tiny value );
	Variable( _short value );
	Variable( _int value );
	Variable( _large value );
	Variable( _byte value );
	Variable( _word value );
	Variable( _dword value );
	Variable( _qword value );
	Variable( _float value );
	Variable( _double value );
	Variable( const _charw* string );
	Variable( WStringPtr string );
	Variable( const _void* pointer );
	Variable( const Variable& variable );
	~Variable( );

public:
	//! Convert to specified data type.
	operator _boolean( ) const;
	operator _ubool( ) const;
	operator _tiny( ) const;
	operator _short( ) const;
	operator _int( ) const;
	operator _large( ) const;
	operator _byte( ) const;
	operator _word( ) const;
	operator _dword( ) const;
	operator _qword( ) const;
	operator _float( ) const;
	operator _double( ) const;
	operator const _charw*( ) const;
	operator WStringPtr( ) const;
	operator _void*() const;

	//! operator = function.
	const Variable& operator = ( _boolean value );
	const Variable& operator = ( _ubool value );
	const Variable& operator = ( _tiny value );
	const Variable& operator = ( _short value );
	const Variable& operator = ( _int value );
	const Variable& operator = ( _large value );
	const Variable& operator = ( _byte value );
	const Variable& operator = ( _word value );
	const Variable& operator = ( _dword value );
	const Variable& operator = ( _qword value );
	const Variable& operator = ( _float value );
	const Variable& operator = ( _double value );
	const Variable& operator = ( const _charw* string );
	const Variable& operator = ( WStringPtr string );
	const Variable& operator = ( const _void* pointer );
	const Variable& operator = ( const Variable& variable );

	//! operator ++, -- function.
	const Variable& operator ++ ( _int );
	const Variable& operator -- ( _int );

	//! operator +=, -=, *=, /=, &=, |= function.
	const Variable& operator += ( const Variable& variable );
	const Variable& operator -= ( const Variable& variable );
	const Variable& operator *= ( const Variable& variable );
	const Variable& operator /= ( const Variable& variable );
	const Variable& operator &= ( const Variable& variable );
	const Variable& operator |= ( const Variable& variable );

	//! operator - function.
	Variable operator - ( ) const;

	//! operator <, <=, ==, !=, >, >= function.
	_boolean operator <  ( const Variable& variable ) const;
	_boolean operator <= ( const Variable& variable ) const;
	_boolean operator == ( const Variable& variable ) const;
	_boolean operator != ( const Variable& variable ) const;
	_boolean operator >  ( const Variable& variable ) const;
	_boolean operator >= ( const Variable& variable ) const;

	//! operator &&, || function.
	_boolean operator && ( const Variable& variable ) const;
	_boolean operator || ( const Variable& variable ) const;

	//! Clear.
	_void Clear( );

	//! Is boolean type.
	_boolean IsBoolean( ) const;
	//! Is pointer type.
	_boolean IsPointer( ) const;
	//! Is string type.
	_boolean IsString( ) const;
	//! Is float type.
	_boolean IsFloat( ) const;
	//! Is double type.
	_boolean IsDouble( ) const;
	//! Is number type.
	_boolean IsNumber( ) const;
	//! Is integer type.
	_boolean IsInteger( ) const;
	//! Is signed type.
	_boolean IsSigned( ) const;
	//! Is zero value.
	_boolean IsZero( ) const;

	//! Convert value to string.
	WString ToString( ) const;

	//! Get the value type ID.
	_dword GetTypeID( ) const;

	//! Get the string.
	WStringPtr GetString( ) const;
	//! Set the string.
	_void SetString( WStringPtr string );
	//! Set the string.
	_void SetString( const _charw* string );

public:
	//! Get the type ID from the type string.
	//! @param		typestring	The type string.
	//! @return		The type ID.
	static _dword GetTypeID( WStringPtr typestring );
	//! Get the type string from the type ID.
	//! @param		type		The type ID.
	//! @return		The type string.
	static WStringPtr GetTypeIDString( _dword type );

	//! Get the type size from the type ID.
	//! @param		type		The type ID.
	//! @return		The type size.
	static _dword GetTypeIDSize( _dword type );
};

//----------------------------------------------------------------------------
// Variable Implementation
//----------------------------------------------------------------------------

inline Variable::Variable( )
{
	mType			= _TYPE_ID_UNKNOWN;
	mUnsignedValue	= 0;
}

inline Variable::Variable( _boolean value )
{
	mType				= _TYPE_ID_BOOLEAN;
	mUnsignedValues[0]	= EGE_BOOLEAN( value );
	mUnsignedValues[1]	= 0;
}

inline Variable::Variable( _ubool value )
{
	mType				= _TYPE_ID_BOOLEAN;
	mUnsignedValues[0]	= EGE_BOOLEAN( value );
	mUnsignedValues[1]	= 0;
}

inline Variable::Variable( _tiny value )
{
	mType				= _TYPE_ID_INT8;
	mSignedValues[0]	= value;
	mSignedValues[1]	= 0;
}

inline Variable::Variable( _short value )
{
	mType				= _TYPE_ID_INT16;
	mSignedValues[0]	= value;
	mSignedValues[1]	= 0;
}

inline Variable::Variable( _int value )
{
	mType				= _TYPE_ID_INT32;
	mSignedValues[0]	= value;
	mSignedValues[1]	= 0;
}

inline Variable::Variable( _large value )
{
	mType			= _TYPE_ID_INT64;
	mSignedValue	= value;
}

inline Variable::Variable( _byte value )
{
	mType				= _TYPE_ID_UINT8;
	mUnsignedValues[0]	= value;
	mUnsignedValues[1]	= 0;
}

inline Variable::Variable( _word value )
{
	mType				= _TYPE_ID_UINT16;
	mUnsignedValues[0]	= value;
	mUnsignedValues[1]	= 0;
}

inline Variable::Variable( _dword value )
{
	mType				= _TYPE_ID_UINT32;
	mUnsignedValues[0]	= value;
	mUnsignedValues[1]	= 0;
}

inline Variable::Variable( _float value )
{
	mType			= _TYPE_ID_FLOAT;
	mFloatValues[0] = value;
	mFloatValues[1] = 0;
}

inline Variable::Variable( _double value )
{
	mType			= _TYPE_ID_DOUBLE;
	mDoubleValue	= value;
}

inline Variable::Variable( const _charw* string )
{
	SetString( string );
}

inline Variable::Variable( WStringPtr string )
{
	SetString( string );
}

inline Variable::Variable( const _void* pointer )
{
	mType			= _TYPE_ID_POINTER;
	mUnsignedValue  = (_qword)pointer;
}

inline Variable::Variable( const Variable& variable )
{
	mType			= variable.mType;
	mUnsignedValue	= variable.mUnsignedValue;
}

inline Variable::~Variable( )
{
}

template< typename Type >
inline Type Variable::ConvertToSignedValue( ) const
{
	if ( IsFloat( ) )
	{
		return (Type)mFloatValues[0];
	}
	else if ( IsDouble( ) )
	{
		return (Type)mDoubleValue;
	}
	else if ( IsString( ) )
	{
		return (Type)Platform::ConvertStringToLong( (const _charw*)mUnsignedValue, 10 );
	}
	else if ( mType == _TYPE_ID_INT64 )
	{
		return (Type)mSignedValue;
	}
	else if ( mType == _TYPE_ID_UINT64 )
	{
		return (Type)mUnsignedValue;
	}
	else
	{
		return (Type)mSignedValues[0];
	}
}

template<>
inline _large Variable::ConvertToSignedValue( ) const
{
	if ( IsFloat( ) )
	{
		return (_large)mFloatValues[0];
	}
	else if ( IsDouble( ) )
	{
		return (_large)mDoubleValue;
	}
	else if ( IsString( ) )
	{
		return Platform::ConvertStringToLarge( (const _charw*)mUnsignedValue, 10 );
	}
	else
	{
		switch ( mType )
		{
			case _TYPE_ID_INT8:
			case _TYPE_ID_INT16:
			case _TYPE_ID_INT32:
				return (_large)mSignedValues[0];

			case _TYPE_ID_UINT8:
			case _TYPE_ID_UINT16:
			case _TYPE_ID_UINT32:
				return (_large)mUnsignedValues[0];

			default:
				return mSignedValue;
		}
	}
}

template<>
inline _float Variable::ConvertToSignedValue( ) const
{
	if ( IsFloat( ) )
	{
		return mFloatValues[0];
	}
	else if ( IsDouble( ) )
	{
		return (_float)mDoubleValue;
	}
	else if ( IsString( ) )
	{
		return Platform::ConvertStringToFloat( (const _charw*)mUnsignedValue );
	}
	else
	{
		switch ( mType )
		{
			case _TYPE_ID_INT8:
			case _TYPE_ID_INT16:
			case _TYPE_ID_INT32:
				return (_float)mSignedValues[0];

			case _TYPE_ID_UINT8:
			case _TYPE_ID_UINT16:
			case _TYPE_ID_UINT32:
				return (_float)mUnsignedValues[0];

			default:
				return (_float)mSignedValue;
		}
	}
}

template<>
inline _double Variable::ConvertToSignedValue( ) const
{
	if ( IsFloat( ) )
	{
		return (_double)mFloatValues[0];
	}
	else if ( IsDouble( ) )
	{
		return mDoubleValue;
	}
	else if ( IsString( ) )
	{
		return Platform::ConvertStringToDouble( (const _charw*)mUnsignedValue );
	}
	else
	{
		switch ( mType )
		{
			case _TYPE_ID_INT8:
			case _TYPE_ID_INT16:
			case _TYPE_ID_INT32:
				return (_double)mSignedValues[0];

			case _TYPE_ID_UINT8:
			case _TYPE_ID_UINT16:
			case _TYPE_ID_UINT32:
				return (_double)mUnsignedValues[0];

			default:
				return (_double)mSignedValue;
		}
	}
}

template< typename Type >
inline Type Variable::ConvertToUnsignedValue( ) const
{
	if ( IsFloat( ) )
	{
		return (Type)mFloatValues[0];
	}
	else if ( IsDouble( ) )
	{
		return (Type)mDoubleValue;
	}
	else if ( IsString( ) )
	{
		return (Type)Platform::ConvertStringToDword( (const _charw*)mUnsignedValue, 10 );
	}
	else if ( mType == _TYPE_ID_INT64 )
	{
		return (Type)mSignedValue;
	}
	else if ( mType == _TYPE_ID_UINT64 )
	{
		return (Type)mUnsignedValue;
	}
	else
	{
		return (Type)mUnsignedValues[0];
	}
}

template<>
inline _qword Variable::ConvertToUnsignedValue( ) const
{
	if ( IsFloat( ) )
	{
		return (_qword)mFloatValues[0];
	}
	else if ( IsDouble( ) )
	{
		return (_qword)mDoubleValue;
	}
	else if ( IsString( ) )
	{
		return Platform::ConvertStringToQword( (const _charw*)mUnsignedValue, 10 );
	}
	else
	{
		switch ( mType )
		{
			case _TYPE_ID_INT8:
			case _TYPE_ID_INT16:
			case _TYPE_ID_INT32:
				return (_qword)mSignedValues[0];

			case _TYPE_ID_UINT8:
			case _TYPE_ID_UINT16:
			case _TYPE_ID_UINT32:
				return (_qword)mUnsignedValues[0];

			default:
				return mUnsignedValue;
		}
	}
}

template<>
inline _boolean Variable::ConvertToUnsignedValue( ) const
{
	if ( IsFloat( ) )
	{
		return (_boolean)EGE_BOOLEAN(mFloatValues[0]);
	}
	else if ( IsDouble( ) )
	{
		return (_boolean)EGE_BOOLEAN(mDoubleValue);
	}
	else if ( IsString( ) )
	{
		WStringPtr string = (const _charw*)mUnsignedValue;

		if ( string.IsEqual( L"true", _true ) )
			return _true;
		else
			return _false;
	}
	else
	{
		return EGE_BOOLEAN( mUnsignedValues[0] );
	}
}

inline Variable::operator _boolean( ) const
{
	return ConvertToUnsignedValue< _boolean >( );
}

inline Variable::operator _ubool( ) const
{
	return _boolean( *this );
}

inline Variable::operator _tiny( ) const
{
	return ConvertToSignedValue< _tiny >( );
}

inline Variable::operator _short( ) const
{
	return ConvertToSignedValue< _short >( );
}

inline Variable::operator _int( ) const
{
	return ConvertToSignedValue< _int >( );
}

inline Variable::operator _large( ) const
{
	return ConvertToSignedValue< _large >( );
}

inline Variable::operator _byte( ) const
{
	return ConvertToUnsignedValue< _byte >( );
}

inline Variable::operator _word( ) const
{
	return ConvertToUnsignedValue< _word >( );
}

inline Variable::operator _dword( ) const
{
	return ConvertToUnsignedValue< _dword >( );
}

inline Variable::operator _qword( ) const
{
	return ConvertToUnsignedValue< _qword >( );
}

inline Variable::operator _float( ) const
{
	return ConvertToSignedValue< _float >( );
}

inline Variable::operator _double( ) const
{
	return ConvertToSignedValue< _double >( );
}

inline Variable::operator const _charw*() const
{
	if ( IsString( ) )
		return (const _charw*)mUnsignedValue;
	else
		return L"";
}

inline Variable::operator WStringPtr( ) const
{
	if ( IsString( ) )
		return (const _charw*)mUnsignedValue;
	else
		return L"";
}

inline Variable::operator _void*( ) const
{
    return (_void*) mUnsignedValue;
}

inline const Variable& Variable::operator = ( _boolean value )
{
	mType				= _TYPE_ID_BOOLEAN;
	mUnsignedValues[0]	= EGE_BOOLEAN( value );
	mUnsignedValues[1]	= 0;

	return *this;
}

inline const Variable& Variable::operator = ( _ubool value )
{
	mType				= _TYPE_ID_BOOLEAN;
	mUnsignedValues[0]	= EGE_BOOLEAN( value );
	mUnsignedValues[1]	= 0;

	return *this;
}

inline const Variable& Variable::operator = ( _tiny value )
{
	mType				= _TYPE_ID_INT8;
	mSignedValues[0]	= value;
	mSignedValues[1]	= 0;

	return *this;
}

inline const Variable& Variable::operator = ( _short value )
{
	mType				= _TYPE_ID_INT16;
	mSignedValues[0]	= value;
	mSignedValues[1]	= 0;

	return *this;
}

inline const Variable& Variable::operator = ( _int value )
{
	mType				= _TYPE_ID_INT32;
	mSignedValues[0]	= value;
	mSignedValues[1]	= 0;

	return *this;
}

inline const Variable& Variable::operator = ( _byte value )
{
	mType				= _TYPE_ID_UINT8;
	mUnsignedValues[0]	= value;
	mUnsignedValues[1]	= 0;

	return *this;
}

inline const Variable& Variable::operator = ( _word value )
{
	mType				= _TYPE_ID_UINT16;
	mUnsignedValues[0]	= value;
	mUnsignedValues[1]	= 0;

	return *this;
}

inline const Variable& Variable::operator = ( _dword value )
{
	mType				= _TYPE_ID_UINT32;
	mUnsignedValues[0]	= value;
	mUnsignedValues[1]	= 0;

	return *this;
}

inline const Variable& Variable::operator = ( _float value )
{
	mType			= _TYPE_ID_FLOAT;
	mFloatValues[0]	= value;
	mFloatValues[1]	= 0.0f;

	return *this;
}

inline const Variable& Variable::operator = ( _double value )
{
	mType			= _TYPE_ID_DOUBLE;
	mDoubleValue	= value;

	return *this;
}

inline const Variable& Variable::operator = ( const _charw* string )
{
	SetString( string );

	return *this;
}

inline const Variable& Variable::operator = ( WStringPtr string )
{
	SetString( string );

	return *this;
}

inline const Variable& Variable::operator = ( const _void* pointer )
{
	mType			= _TYPE_ID_POINTER;
	mUnsignedValue	= _qword( pointer );

	return *this;
}

inline const Variable& Variable::operator = ( const Variable& variable )
{
	mType			= variable.mType;
	mUnsignedValue	= variable.mUnsignedValue;

	return *this;
}

inline const Variable& Variable::operator ++ ( _int )
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
		case _TYPE_ID_INT16:
		case _TYPE_ID_INT32:
			mSignedValues[0] ++;
			break;

		case _TYPE_ID_INT64:
			mSignedValue ++;
			break;

		case _TYPE_ID_UINT8:
		case _TYPE_ID_UINT16:
		case _TYPE_ID_UINT32:
			mUnsignedValues[0] ++;
			break;

		case _TYPE_ID_UINT64:
			mUnsignedValue ++;
			break;

		case _TYPE_ID_FLOAT:
			mFloatValues[0] = mFloatValues[0] + 1.0f;
			break;

		case _TYPE_ID_DOUBLE:
			mDoubleValue = mDoubleValue + 1.0;
			break;

		default:
			break;
	}

	return *this;
}

inline const Variable& Variable::operator -- ( _int )
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
		case _TYPE_ID_INT16:
		case _TYPE_ID_INT32:
			mSignedValues[0] --;
			break;

		case _TYPE_ID_INT64:
			mSignedValue --;
			break;

		case _TYPE_ID_UINT8:
		case _TYPE_ID_UINT16:
		case _TYPE_ID_UINT32:
			mUnsignedValues[0] --;
			break;

		case _TYPE_ID_UINT64:
			mUnsignedValue --;
			break;

		case _TYPE_ID_FLOAT:
			mFloatValues[0] = mFloatValues[0] - 1.0f;
			break;

		case _TYPE_ID_DOUBLE:
			mDoubleValue = mDoubleValue - 1.0;
			break;

		default:
			break;
	}

	return *this;
}

inline const Variable& Variable::operator += ( const Variable& variable )
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			mSignedValues[0] += (_tiny)variable;
			break;

		case _TYPE_ID_INT16:
			mSignedValues[0] += (_short)variable;
			break;

		case _TYPE_ID_INT32:
			mSignedValues[0] += (_int)variable;
			break;

		case _TYPE_ID_INT64:
			mSignedValue += (_large)variable;
			break;

		case _TYPE_ID_UINT8:
			mUnsignedValues[0] += (_byte)variable;
			break;

		case _TYPE_ID_UINT16:
			mUnsignedValues[0] += (_word)variable;
			break;

		case _TYPE_ID_UINT32:
			mUnsignedValues[0] += (_dword)variable;
			break;

		case _TYPE_ID_UINT64:
			mUnsignedValue += (_qword)variable;
			break;

		case _TYPE_ID_FLOAT:
			mFloatValues[0] = mFloatValues[0] + (_float)variable;
			break;

		case _TYPE_ID_DOUBLE:
			mDoubleValue = mDoubleValue + (_double)variable;
			break;

		default:
			break;
	}

	return *this;
}

inline const Variable& Variable::operator -= ( const Variable& variable )
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			mSignedValues[0] -= (_tiny)variable;
			break;

		case _TYPE_ID_INT16:
			mSignedValues[0] -= (_short)variable;
			break;

		case _TYPE_ID_INT32:
			mSignedValues[0] -= (_int)variable;
			break;

		case _TYPE_ID_INT64:
			mSignedValue -= (_large)variable;
			break;

		case _TYPE_ID_UINT8:
			mUnsignedValues[0] -= (_byte)variable;
			break;

		case _TYPE_ID_UINT16:
			mUnsignedValues[0] -= (_word)variable;
			break;

		case _TYPE_ID_UINT32:
			mUnsignedValues[0] -= (_dword)variable;
			break;

		case _TYPE_ID_UINT64:
			mUnsignedValue -= (_qword)variable;
			break;

		case _TYPE_ID_FLOAT:
			mFloatValues[0] = mFloatValues[0] - (_float)variable;
			break;

		case _TYPE_ID_DOUBLE:
			mDoubleValue = mDoubleValue - (_double)variable;
			break;

		default:
			break;
	}

	return *this;
}

inline const Variable& Variable::operator *= ( const Variable& variable )
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			mSignedValues[0] *= (_tiny)variable;
			break;

		case _TYPE_ID_INT16:
			mSignedValues[0] *= (_short)variable;
			break;

		case _TYPE_ID_INT32:
			mSignedValues[0] *= (_int)variable;
			break;

		case _TYPE_ID_INT64:
			mSignedValue *= (_large)variable;
			break;

		case _TYPE_ID_UINT8:
			mUnsignedValues[0] *= (_byte)variable;
			break;

		case _TYPE_ID_UINT16:
			mUnsignedValues[0] *= (_word)variable;
			break;

		case _TYPE_ID_UINT32:
			mUnsignedValues[0] *= (_dword)variable;
			break;

		case _TYPE_ID_UINT64:
			mUnsignedValue *= (_qword)variable;
			break;

		case _TYPE_ID_FLOAT:
			mFloatValues[0] = mFloatValues[0] * (_float)variable;
			break;

		case _TYPE_ID_DOUBLE:
			mDoubleValue = mDoubleValue * (_double)variable;
			break;

		default:
			break;
	}

	return *this;
}

inline const Variable& Variable::operator /= ( const Variable& variable )
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			mSignedValues[0] /= (_tiny)variable;
			break;

		case _TYPE_ID_INT16:
			mSignedValues[0] /= (_short)variable;
			break;

		case _TYPE_ID_INT32:
			mSignedValues[0] /= (_int)variable;
			break;

		case _TYPE_ID_INT64:
			mSignedValue /= (_large)variable;
			break;

		case _TYPE_ID_UINT8:
			mUnsignedValues[0] /= (_byte)variable;
			break;

		case _TYPE_ID_UINT16:
			mUnsignedValues[0] /= (_word)variable;
			break;

		case _TYPE_ID_UINT32:
			mUnsignedValues[0] /= (_dword)variable;
			break;

		case _TYPE_ID_UINT64:
			mUnsignedValue /= (_qword)variable;
			break;

		case _TYPE_ID_FLOAT:
			mFloatValues[0] = mFloatValues[0] / (_float)variable;
			break;

		case _TYPE_ID_DOUBLE:
			mDoubleValue = mDoubleValue / (_double)variable;
			break;

		default:
			break;
	}

	return *this;
}

inline const Variable& Variable::operator &= ( const Variable& variable )
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			mSignedValues[0] &= (_tiny)variable;
			break;

		case _TYPE_ID_INT16:
			mSignedValues[0] &= (_short)variable;
			break;

		case _TYPE_ID_INT32:
			mSignedValues[0] &= (_int)variable;
			break;

		case _TYPE_ID_INT64:
			mSignedValue &= (_large)variable;
			break;

		case _TYPE_ID_UINT8:
			mUnsignedValues[0] &= (_byte)variable;
			break;

		case _TYPE_ID_UINT16:
			mUnsignedValues[0] &= (_word)variable;
			break;

		case _TYPE_ID_UINT32:
			mUnsignedValues[0] &= (_dword)variable;
			break;

		case _TYPE_ID_UINT64:
			mUnsignedValue &= (_qword)variable;
			break;

		default:
			break;
	}

	return *this;
}

inline const Variable& Variable::operator |= ( const Variable& variable )
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			mSignedValues[0] |= (_tiny)variable;
			break;

		case _TYPE_ID_INT16:
			mSignedValues[0] |= (_short)variable;
			break;

		case _TYPE_ID_INT32:
			mSignedValues[0] |= (_int)variable;
			break;

		case _TYPE_ID_INT64:
			mSignedValue |= (_large)variable;
			break;

		case _TYPE_ID_UINT8:
			mUnsignedValues[0] |= (_byte)variable;
			break;

		case _TYPE_ID_UINT16:
			mUnsignedValues[0] |= (_word)variable;
			break;

		case _TYPE_ID_UINT32:
			mUnsignedValues[0] |= (_dword)variable;
			break;

		case _TYPE_ID_UINT64:
			mUnsignedValue |= (_qword)variable;
			break;

		default:
			break;
	}

	return *this;
}

inline Variable Variable::operator - ( ) const
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
		case _TYPE_ID_INT16:
		case _TYPE_ID_INT32:
			return -mSignedValues[0];

		case _TYPE_ID_INT64:
			return -mSignedValue;

		case _TYPE_ID_UINT8:
		case _TYPE_ID_UINT16:
		case _TYPE_ID_UINT32:
			return -(_int)mUnsignedValues[0];

		case _TYPE_ID_UINT64:
			return -(_large)mUnsignedValue;
			break;

		case _TYPE_ID_FLOAT:
			return -mFloatValues[0];

		case _TYPE_ID_DOUBLE:
			return -mDoubleValue;

		default:
			break;
	}

	return Variable::cNull;
}

inline _boolean Variable::operator < ( const Variable& variable ) const
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			return mSignedValues[0] < (_tiny)variable;

		case _TYPE_ID_INT16:
			return mSignedValues[0] < (_short)variable;

		case _TYPE_ID_INT32:
			return mSignedValues[0] < (_int)variable;

		case _TYPE_ID_INT64:
			return mSignedValue < (_large)variable;

		case _TYPE_ID_UINT8:
			return mUnsignedValues[0] < (_byte)variable;

		case _TYPE_ID_UINT16:
			return mUnsignedValues[0] < (_word)variable;

		case _TYPE_ID_UINT32:
			return mUnsignedValues[0] < (_dword)variable;

		case _TYPE_ID_UINT64:
			return mUnsignedValue < (_qword)variable;

		case _TYPE_ID_FLOAT:
			return mFloatValues[0] < (_float)variable;

		case _TYPE_ID_DOUBLE:
			return mDoubleValue < (_double)variable;

		case _TYPE_ID_WSTRING:
			return GetString( ) < variable.GetString( );

		default:
			break;
	}

	return _false;
}

inline _boolean Variable::operator <= ( const Variable& variable ) const
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			return mSignedValues[0] <= (_tiny)variable;

		case _TYPE_ID_INT16:
			return mSignedValues[0] <= (_short)variable;

		case _TYPE_ID_INT32:
			return mSignedValues[0] <= (_int)variable;

		case _TYPE_ID_INT64:
			return mSignedValue <= (_large)variable;

		case _TYPE_ID_UINT8:
			return mUnsignedValues[0] <= (_byte)variable;

		case _TYPE_ID_UINT16:
			return mUnsignedValues[0] <= (_word)variable;

		case _TYPE_ID_UINT32:
			return mUnsignedValues[0] <= (_dword)variable;

		case _TYPE_ID_UINT64:
			return mUnsignedValue <= (_qword)variable;

		case _TYPE_ID_FLOAT:
			return mFloatValues[0] <= (_float)variable;

		case _TYPE_ID_DOUBLE:
			return mDoubleValue <= (_double)variable;

		case _TYPE_ID_WSTRING:
			return GetString( ) <= variable.GetString( );

		default:
			break;
	}

	return _false;
}

inline _boolean Variable::operator == ( const Variable& variable ) const
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			return mSignedValues[0] == (_tiny)variable;

		case _TYPE_ID_INT16:
			return mSignedValues[0] == (_short)variable;

		case _TYPE_ID_INT32:
			return mSignedValues[0] == (_int)variable;

		case _TYPE_ID_INT64:
			return mSignedValue == (_large)variable;

		case _TYPE_ID_UINT8:
			return mUnsignedValues[0] == (_byte)variable;

		case _TYPE_ID_UINT16:
			return mUnsignedValues[0] == (_word)variable;

		case _TYPE_ID_UINT32:
			return mUnsignedValues[0] == (_dword)variable;

		case _TYPE_ID_UINT64:
			return mUnsignedValue == (_qword)variable;

		case _TYPE_ID_FLOAT:
			return mFloatValues[0] == (_float)variable;

		case _TYPE_ID_DOUBLE:
			return mDoubleValue == (_double)variable;

		case _TYPE_ID_WSTRING:
			return GetString( ) == variable.GetString( );

		default:
			break;
	}

	return _false;
}

inline _boolean Variable::operator != ( const Variable& variable ) const
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			return mSignedValues[0] != (_tiny)variable;

		case _TYPE_ID_INT16:
			return mSignedValues[0] != (_short)variable;

		case _TYPE_ID_INT32:
			return mSignedValues[0] != (_int)variable;

		case _TYPE_ID_INT64:
			return mSignedValue != (_large)variable;

		case _TYPE_ID_UINT8:
			return mUnsignedValues[0] != (_byte)variable;

		case _TYPE_ID_UINT16:
			return mUnsignedValues[0] != (_word)variable;

		case _TYPE_ID_UINT32:
			return mUnsignedValues[0] != (_dword)variable;

		case _TYPE_ID_UINT64:
			return mUnsignedValue != (_qword)variable;

		case _TYPE_ID_FLOAT:
			return mFloatValues[0] != (_float)variable;

		case _TYPE_ID_DOUBLE:
			return mDoubleValue != (_double)variable;

		case _TYPE_ID_WSTRING:
			return GetString( ) != variable.GetString( );

		default:
			break;
	}

	return _false;
}

inline _boolean Variable::operator > ( const Variable& variable ) const
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			return mSignedValues[0] > (_tiny)variable;

		case _TYPE_ID_INT16:
			return mSignedValues[0] > (_short)variable;

		case _TYPE_ID_INT32:
			return mSignedValues[0] > (_int)variable;

		case _TYPE_ID_INT64:
			return mSignedValue > (_large)variable;

		case _TYPE_ID_UINT8:
			return mUnsignedValues[0] > (_byte)variable;

		case _TYPE_ID_UINT16:
			return mUnsignedValues[0] > (_word)variable;

		case _TYPE_ID_UINT32:
			return mUnsignedValues[0] > (_dword)variable;

		case _TYPE_ID_UINT64:
			return mUnsignedValue > (_qword)variable;

		case _TYPE_ID_FLOAT:
			return mFloatValues[0] > (_float)variable;

		case _TYPE_ID_DOUBLE:
			return mDoubleValue > (_double)variable;

		case _TYPE_ID_WSTRING:
			return GetString( ) > variable.GetString( );

		default:
			break;
	}

	return _false;
}

inline _boolean Variable::operator >= ( const Variable& variable ) const
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			return mSignedValues[0] >= (_tiny)variable;

		case _TYPE_ID_INT16:
			return mSignedValues[0] >= (_short)variable;

		case _TYPE_ID_INT32:
			return mSignedValues[0] >= (_int)variable;

		case _TYPE_ID_INT64:
			return mSignedValue >= (_large)variable;

		case _TYPE_ID_UINT8:
			return mUnsignedValues[0] >= (_byte)variable;

		case _TYPE_ID_UINT16:
			return mUnsignedValues[0] >= (_word)variable;

		case _TYPE_ID_UINT32:
			return mUnsignedValues[0] >= (_dword)variable;

		case _TYPE_ID_UINT64:
			return mUnsignedValue >= (_qword)variable;

		case _TYPE_ID_FLOAT:
			return mFloatValues[0] >= (_float)variable;

		case _TYPE_ID_DOUBLE:
			return mDoubleValue >= (_double)variable;

		case _TYPE_ID_WSTRING:
			return GetString( ) >= variable.GetString( );

		default:
			break;
	}

	return _false;
}

inline _boolean Variable::operator && ( const Variable& variable ) const
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			return mSignedValues[0] && (_tiny)variable;

		case _TYPE_ID_INT16:
			return mSignedValues[0] && (_short)variable;

		case _TYPE_ID_INT32:
			return mSignedValues[0] && (_int)variable;

		case _TYPE_ID_INT64:
			return mSignedValue && (_large)variable;

		case _TYPE_ID_UINT8:
			return mUnsignedValues[0] && (_byte)variable;

		case _TYPE_ID_UINT16:
			return mUnsignedValues[0] && (_word)variable;

		case _TYPE_ID_UINT32:
			return mUnsignedValues[0] && (_dword)variable;

		case _TYPE_ID_UINT64:
			return mUnsignedValue && (_qword)variable;

		case _TYPE_ID_FLOAT:
			return mFloatValues[0] && (_float)variable;

		case _TYPE_ID_DOUBLE:
			return mDoubleValue && (_double)variable;

		case _TYPE_ID_WSTRING:
			return _true;

		default:
			break;
	}

	return _false;
}

inline _boolean Variable::operator || ( const Variable& variable ) const
{
	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
			return mSignedValues[0] || (_tiny)variable;

		case _TYPE_ID_INT16:
			return mSignedValues[0] || (_short)variable;

		case _TYPE_ID_INT32:
			return mSignedValues[0] || (_int)variable;

		case _TYPE_ID_INT64:
			return mSignedValue || (_large)variable;

		case _TYPE_ID_UINT8:
			return mUnsignedValues[0] || (_byte)variable;

		case _TYPE_ID_UINT16:
			return mUnsignedValues[0] || (_word)variable;

		case _TYPE_ID_UINT32:
			return mUnsignedValues[0] || (_dword)variable;

		case _TYPE_ID_UINT64:
			return mUnsignedValue || (_qword)variable;

		case _TYPE_ID_FLOAT:
			return mFloatValues[0] || (_float)variable;

		case _TYPE_ID_DOUBLE:
			return mDoubleValue || (_double)variable;

		case _TYPE_ID_WSTRING:
			return _true;

		default:
			break;
	}

	return _false;
}

inline _void Variable::Clear( )
{
	mType			= _TYPE_ID_UNKNOWN;
	mUnsignedValue	= 0;
}

inline _boolean Variable::IsBoolean() const
{
	return mType == _TYPE_ID_BOOLEAN;
}

inline _boolean Variable::IsPointer( ) const
{
	return mType == _TYPE_ID_POINTER;
}

inline _boolean Variable::IsString( ) const
{
	return EGE_BOOLEAN( mType & _TYPE_STRING );
}

inline _boolean Variable::IsFloat( ) const
{
	return mType == _TYPE_ID_FLOAT;
}

inline _boolean Variable::IsDouble( ) const
{
	return mType == _TYPE_ID_DOUBLE;
}

inline _boolean Variable::IsNumber( ) const
{
	return EGE_BOOLEAN( mType & (_TYPE_INTEGER | _TYPE_FLOAT) );
}

inline _boolean Variable::IsInteger( ) const
{
	return EGE_BOOLEAN( mType & _TYPE_INTEGER );
}

inline _boolean Variable::IsSigned( ) const
{
	return EGE_BOOLEAN( mType & _TYPE_ID_SIGNED );
}

inline _boolean Variable::IsZero( ) const
{
	return mUnsignedValue == 0;
}

inline WString Variable::ToString( ) const
{
	_charw string[1024];
	string[0] = 0;

	switch ( mType ) 
	{
		case _TYPE_ID_INT8:
		case _TYPE_ID_INT16:
		case _TYPE_ID_INT32:
			Platform::ConvertLongToString( mSignedValues[0], 10, string, 1024 );
			break;

		case _TYPE_ID_INT64:
			Platform::ConvertLargeToString( mSignedValue, 10, string, 1024 );
			break;

		case _TYPE_ID_UINT8:
		case _TYPE_ID_UINT16:
		case _TYPE_ID_UINT32:
			Platform::ConvertLongToString( mUnsignedValues[0], 10, string, 1024 );
			break;

		case _TYPE_ID_UINT64:
			Platform::ConvertQwordToString( mUnsignedValue, 10, string, 1024 );
			break;

		case _TYPE_ID_FLOAT:
			Platform::ConvertFloatToString( mFloatValues[0], string, 1024 );
			break;

		case _TYPE_ID_DOUBLE:
			Platform::ConvertDoubleToString( mDoubleValue, string, 1024 );
			break;

		case _TYPE_ID_WSTRING:
			return GetString( );

		default:
			break;
	}

	return string;
}

inline _dword Variable::GetTypeID( ) const
{
	return mType;
}

inline WStringPtr Variable::GetString( ) const
{
	if ( IsString( ) == _false )
		return L"";

	return (const _charw*) mUnsignedValue;
}

inline _void Variable::SetString( WStringPtr string )
{
	SetString( string.Str( ) );
}

inline _void Variable::SetString( const _charw* string )
{
	// Set to string mode
	mType = _TYPE_ID_WSTRING;

	// Copy string address
	mUnsignedValue = _qword( string );
}

}